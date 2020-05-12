# 트리

여러가지 트리에 대해서 배우고 그것들을 정리할 곳.

1. 계층 구조를 표현하는 일반적 트리의 구현 방법과 중요한 개념, 연산들을 정리
2. 가장 유명한 탐색형 자료 구조인 이진 검색 트리를 정리
  - 이진 검색 트리는 대소 관계를 갖는 자료들을 크기 순서로 정렬해 저장하는 자료 구조로, 항상 자료들을 정렬해 놓음으로써 원소의 추가와 삭제, 존재 여부 확인 등의 연산을 배열보다 훨씬 빠르게 수행할 수 있습니다.
  - 이진 검색 트리의 변종인 트립에 대해서도 정리
3. 큐의 변종인 우선 순위 큐에 대해서 정리.
  - 스택이나 큐와 달리, 우선 순위 큐에서는 자료를 넣은 순서가 아니라 자료의 대소 관게에 의해 꺼내는 순서를 결정한다.
  - 이들은 이진 검색 트리로도 구현할 수 있지만, 더 단순한 트리인 힙으로도 구현 가능하다.
  - 힙의 구현 방법에 대해서 정리
4. 특수한 형태의 트리인 구간 트리에 대해서 정리.
  - 구간 트리란 1차원 배열로 주어진 자료가 주어졌을 때, 이 배열의 구간들에 대한 질의에 빠르게 대답할 수 있도록 해 주는 자료 구조다.
  - 예를 들어 하나의 1차원 배열에 대해 특정 구간의 최소치를 구하는 연산을 여러 번 해야 한다면 구간 트리를 아주 유용하게 사용 가능하다.
5. 커다란 모집합이 여러 개 작은 집합들로 나뉘어 있는 상황을 표현하는 유니온-파인드 자료 구조에 대해 정리
6. 문자열을 표현하는 트리인 트라이를 정리
  - 트라이는 문자열의 각 글자를 노드로 갖는 자료 구조로, 굉장히 빠르게 문자열 검색을 하는 데 사용할 수 있다. 

## 1. 트리의 구현과 순회
---
### 1. 도입

선형자료구조로는 표현하기 힘든 것들이 많다.
표현하기 힘든 것 중에서 대표적으로 계층 구조가 있다. 자료 간의 상하위 관계나 포함 관계가 존재하는 경우 게층 구조가 생긴다.

예) 월드컵 본선 대진표, 회사나 학교의 조직도, 인터넷 상점의 상품 분류 기준 등

계층적 구조를 갖는 자료들을 표현하기 위한 자료 구조가 바로 트리(tree)이다.

![](https://1.bp.blogspot.com/-xIvY2zPVe0E/XDsYHAO93BI/AAAAAAAAKx8/pRmZ4xKdNkwzbdJDlzsI3UX-j57KiKLKwCLcBGAs/s1600/111.png)

위의 그림은 여러 자료 구조들의 관계를 잘 나타내고 있다. 
왼쪽에 위치할 수록 상위 개념을 그리고 오른쪽은 하위 개념을 나타낸다. 

![](https://lh3.googleusercontent.com/proxy/L-W4awAiQoqVwulaNv1hThrQktQywFqij6NHAuRIli46VIIfCsqjt9N1vB2nkoeUau0bgbXdrxmsHcTyfY1PCGhXe_Zd3GcEkKcCNMu-6w2IapNxpBIo4B9X8kjDxyO06gptIzIuga7phAFZcMFHvGjLiyvNfqhFSpu5m7BpTpxVl4-yBQVrbjoKmMrcA08)

위의 그림처럼 위에 있는 노드들이 아래있는 노드들로 가지를 뻗어나가는 모습이 실제 나무와 닮았다고 하여(상하반전이지만) 이 자료 구조를 트리라고 부른다.

계층 구조가 우리의 생활과 깊숙히 연관되어 있기 때문에 트리도 굉장히 널리 쓰이며, 자연스럽게 트리를 사용하는 프로그래밍 대회 문제도 흔히 출제된다.

**트리는 처음에 이와 같이 현실 세계의 개념을 추상화해 표현하는 자료 구조로 고안되었지만, 탐색형 자료 구조로도 유용하게 쓰인다. 특정한 조건을 지키도록 구성된 트리들을 이용하면 배열이나 리스트를 사용하는 것보다 같은 작업을 더 빠르게 할 수 있기 때문이다.**


**트리는 처음에 이와 같이 현실 세계의 개념을 추상화해 표현하는 자료 구조로 고안되었지만, 탐색형 자료 구조로도 유용하게 쓰인다. 특정한 조건을 지키도록 구성된 트리들을 이용하면 배열이나 리스트를 사용하는 것보다 같은 작업을 더 빠르게 할 수 있기 때문이다.**


#### 1.1 트리의 기초

##### 트리의 구성 요소

트리는 자료가 저장된 노드(node)들이 간선(edge)으로 서로 연결되어 있는 자료 구조를 말한다. 
노드 간에는 상/하위 관게가 있으며, 두 노드가 연결되었을 때 한 노드는 좀더 상위, 다른 노드는 좀 더 하위에 있어야 한다.

노드들의 상대적 관계를 지칭하기 위해서, 가계도에서 사용하는 용어를 흔히 사용한다. 
두 연결된 노드 중 상위 노드를 부모(parent), 하위 노드를 자식(child) 노드라고 부른다. 부모 노드가 같은 두 노드는 형제(sibling) 노드라고 부른다.
부모 노드와 그의 부모들을 통틀어 선조(ancestor)라고 부르고, 자식 노드와 그의 자식들을 통틀어 자손(descendant)이라고 부른다.

부모-자식 비유에서도 알 수 있듯이, 트리에서 한 노드는 여러 개의 자식을 가질 수 있어도 부모는 하나만 가질 수 있다. 이와 같은 속성 때문에 트리에는 다른 모든 노드들을 자손으로 갖는 노드가 딱 하나 있게 된다. 이 노드를 **트리의 뿌리 노드 혹은 루트(root)라고 부른다. ** 반대로 **자식이 하나도 없는 노드들을 트리의 잎 노드 혹은 리프(leaf)라고 부른다. 

##### 트리와 노드의 속성

루트에서 어떤 노드에 도달하기 위해 거쳐야 하는 간선의 수를 해당 노드의 깊이(depth)라고 한다. 따라서 깊이가 깊을수록 트리 아래쪽에 있는 노드를 지칭하게 된다. 이때 트리에서 가장 깊숙히 있는 노드의 깊이를 해당 트리의 높이(height)라고 한다. 

##### 트리의 재귀적 속성

트리가 유용하게 사용되는 큰 이유 중 하나는 트리가 재귀적인 성질을 갖고 있다는 것이다. 트리에서 한 노드와 그의 자손들을 모두 모으면 그들도 하나의 트리가 된다. 
이때 어떤 노드 t와 그 자손들로 구성된 트리를 't를 루트로 하는 서브트리(subtree)'라고 말한다. 
따라서 모든 트리는 루트와 루트 밑에 있는 서브트리들의 집합이라고 말할 수 있다. 
이와 같은 재귀적 속성 때문에 트리를 다루는 코드들은 대개 재귀 호출을 이용해 구현된다.

##### 트리의 표현

트리는 굉장히 다양한 방법으로 구현할 수 있지만, 그 중 가장 일반적인 형탠튼 각 노드를 하나의 구조체/객체로 표현하고, 이들을 서로의 포인터로 연결하는 것. 
이때 각 노드들은 자신의 부모와 모든 자손들에 대한 포인터를 갖고 있다. 

```c++
// 트리의 노드를 표현하는 객체의 구현
struct TreeNode{
  string label; // 저장할 자료( 꼭 문자열일 필요는 없다. )
  TreeNode* parent; // 부모 노드를 가리키는 포인터
  vector<TreeNode*> children; // 자손 노드들을 가리키는 포인터 배열
};

```

위의 객체 TreeNode는 특정 구조나 형태를 가정하지 않는다. 즉, 어떤 형태의 트리라도 트리의 가장 기초적인 조건을 충족하기만 한다면 표현할 수 있다는 것.


#### 1.2 트리의 순회

자료 구조의 가장 기초적인 연산 중 하나는 포함되어 있는 자료를 전부 순회하는 것이다. 그러나 선형으로 구성된 배열과 달리 트리는 그 구조가 일정하지 않기 때문에 포함된 모든 자료들을 순회하기가 쉽지 않다. 이와 같은 일을 쉽게 하기 위해서는 트리의 재귀적인 속성을 이용해야 한다. 



```c++
//주어진 트리의 각 노드에 저장된 값을 모두 출력한다.
void printLabels(TreeNode* root){
  // 루트에 저장된 값을 출력한다.
  cout << root->label << endl;
  // 각 자손들을 루트로 하는 서브트리에 포함된 값들을 재귀적으로 출력한다.
  for(int i=0; i<root->children.size(); ++i)
    printLabels(root->children[i]);
}
```


```c++
//root를 루트로 하는 트리의 높이를 구한다.
int height(TreeNode* root){
  int h = 0;
  for(int i=0; i<root->children.size(); ++i)
    h = max(h, 1 + height(root->children[i]));
  return h;
}
```

이러한 트리의 순회는 n개의 노드가 있다고 한다면 모두 순회하기 위해서 O(n)의 시간이 든다. 


## 2. 이진 검색 트리

### 2.1 도입

트리는 현실 세계의 계층적 구조를 표현하는 것 외에도 다양한 용도로 사용된다. 그 대표적인 것이 검색 트리(search tree)이다. 
검색 트리는 연결 리스트나 큐처럼 자료들을 담는 컨테이너지만, **자료들을 일정한 순서에 따라 정렬한 상태로 저장해 둔다.** 이것은 입력이 주어진 순서에 따라 자료들을 배치하는 리스트나 큐와는 다른 속성이다.

예) 검색 트리는 32비트 정수들을 작은 것부터 큰 것까지 정렬한 상태로 저장할 수도 있고, 문자열을 가나다 순으로 정렬해서 저장할 수도 있다.
검색트리는 이 점을 이용해 원소의 추가와 삭제만이 아니라 특정 원소의 존재 여부 확인 등의 다양한 연산을 빠르게 수행한다.

### 2.2 이진 검색 트리의 정의와 조작

#### 정의

우선 이진 트리(Binary tree)를 정의하면, 이진 트리란 각 노드가 왼쪽과 오른쪽, 최대 두 개의 자식 노드만을 가질 수 있는 트리를 의미한다.
따라서 이진 트리는 자식 노드들의 배열 대신 두 개의 포인터 left와 right를 담는 객체로 구현된다.

이진 검색 트리는 이진 탐색에서 아이디어를 가져와서 만든트리다. 우리가 N개의 원소 중에서 원하는 값을 찾는데, 매번 후보의 수를 절반씩 줄여갈 수 있다면 O(lgN)시간에 그 값을 찾을 수 있다. 

즉, 이진탐색의 효율적인 탐색 능력을 유지하면서도, **빈번한 자료 입력과 삭제를 가능하게끔 고안되었다. **

![](https://i.imgur.com/nCYjtI7.png)

- 각 노드의 왼쪽 서브트리에는 해당 노드의 값보다 작은 값을 지닌 노드들로 이루어져 있다.
- 각 노드의 오른쪽 서브트리에는 해당 노드의 값보다 큰 값을 지닌 노드들로 이루어져 있다.
- 중복된 노드가 없어야 한다.
- 왼쪽 서브트리, 오른쪽 서브트리 또한 이진탐색트리이다.

#### 순회

이진 검색 트리를 중위 순회하면 크기 순서로 정렬된 원소의 목록을 얻을 수 있다. (크게 전위 순회(DFT), 중위 순회, 후위 순회로 나눌 수 있다.)
위에서도 설명했듯이, 현재 노드가 가진 원소보다 작은 원소들을 모두 왼쪽 서브트리에 있고, 그보다 큰 원소들은 모두 오른쪽 서브트리에 있기 때문이다. 

![](https://i.imgur.com/SSusVoP.png)
>> 중위순회 : 1, 3, 5, 7, 8, 10 -- ( left, root, right ) 

중위 순회에서 가장 일찍 출력되는 노드는 루트에서 더이상 내려갈 수 없을 때까지 왼쪽 연결로 쭉 내려가서 만나는 노드다.
따라서 이 노드가 최소 원소를 갖고, 반대로 오른쪽 연결을 따라 쭉 내려갔을 때 만나는 노드가 최대 원소를 갖게 된다. 


```
preorder(node)
  print node.value
  if node.left ≠ null then preorder(node.left)
  if node.right ≠ null then preorder(node.right)

```

```
inorder(node)
  if node.left  ≠ null then inorder(node.left)
  print node.value
  if node.right ≠ null then inorder(node.right)

```

```
postorder(node)
  if node.left  ≠ null then postorder(node.left)
  if node.right ≠ null then postorder(node.right)
  print node.value

```

[참고 : 위키피디아 - 트리_순회](https://ko.wikipedia.org/wiki/%ED%8A%B8%EB%A6%AC_%EC%88%9C%ED%9A%8C)



#### 자료의 검색

한 번 원소를 교하는 것 만으로도 찾아야 할 전체 대상의 절반을 줄일 수 있으므로, 실질적으로는 이진 탐색과 비슷한 속도로 자료를 찾을 수 있게 된다.

#### 조작

이진 검색 트리가 정렬된 배열에 비해서 나은 점은, 집합에 원소를 추가하거나 삭제하는 조작 연산을 해야할 때이다.

배열에 새 원소를 삽이하기 위해서는 삽입할 위치를 찾고 그 이후에는 있는 원소들을 모두 한 칸씩 뒤로 옮겨야 한다. 하지만 이진 검색 트리에는 선형적인 구조의 제약이 없기 때문에, 새 원소가 들어갈 위치를 찾고 거기에 노드를 추가하기만 하면 간단히 새 원소를 추가할 수 있다.

이진 검색 트리에서 가장 까다로운 연산은 집합에서 원소를 삭제하는 것이다.

(원소를 삭제하는 연산은 다양한 방식이 있다. -- 책에서 추천해주는 방식은 '합치기' 연산이라고 하는데 다른 것을 정리하도록 하겠다.)

[이 블로그에서](https://mattlee.tistory.com/30) 설명하길, 삭제하기를 원하는 키 값이 트리 안에서 어떤 위치에 있는지를 알아야 한다고 한다.
삭제시 발생할 수 있는 상황 3가지는 다음과 같다.
- 삭제하려는 노드가 단말노드일 경우(자식 노드가 없을 경우)
- 삭제하려는 노드가 하나의 서브트리만 가지는 경우(왼쪽 혹은 오른쪽 둘 중 하나만)
- 삭제하려는 노드가 두 개의 서브트리를 모두 가지고 있는 경우

첫번째 경우는 매우 쉽다고 할 수 있다.
![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=http%3A%2F%2Fcfile10.uf.tistory.com%2Fimage%2F990B3B33598965B71DE855)

삭제하려는 단말 노드의 부모 노드를 찾아서 단말 노드를 가리키는 포인터를 NULL로 만들어서 연결을 끊어주면 된다. (동적으로 할당된 노드였을 경우, 메모리 반납을 하고 링크필드를 NULL로 만들어주면 된다.)

두번째 경우도 비교적 간단하다.
![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=http%3A%2F%2Fcfile6.uf.tistory.com%2Fimage%2F99594633598965C009C890)

사진에서 삭제하려는 68의 부모 노드의 오른쪽 링크를 99를 가리키게 하면 된다. 마찬가지로 동적할당된 노드였다면, 68을 반납해주고 부모의 오른쪽 링크에 99를 붙여주면 된다.

마지막이 가장 복잡한 경우라고 할 수 있다. 

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=http%3A%2F%2Fcfile3.uf.tistory.com%2Fimage%2F99CE0533598965C70117C3)

 18을 삭제하려 한다. 삭제한 이후에 35를 가지고 있는 부모 노드의 왼쪽 링크필드를 어떤 노드에 연결시켜야 할까? 결론부터 말하면 왼쪽 서브트리에 있는 값 중 가장 큰 값, 혹은 오른쪽 서브트리에 있는 값 중 가장 작은 값을 가지고 있는 노드를 연결시켜주면 된다.

 이러한 판단의 근거는 트리의 변동성을 최소화하기 위함에 있다. 18이 있는 상태에서 중위 순회를 한다고 가정해보자. 중위 순회의 순서는 우리가 알다시피 L V R이다. 순회를 하던 도중 12까지 이르렀다고 가정한다. 12 다음에는 어딜 방문할까? 그렇다. 18을 방문한다. 18다음에는 22를 방문한다. 즉, 12 - 18 - 22 순서로 방문하게 된다. 12와 22는 각각 삭제할 노드의 중위 선행자 후속자에 속한다. 이들을 선택해서 18자리를 대체하면 트리의 변동성을 최소로 할 수 있다. 딱 하나만 바꾸면 트리가 정상적으로 작동한다.
  
 22를 선택했다고 가정해보자. 그러면 우리가 할 일은 삭제되는 노드의 오른쪽 서브 트리에서 왼쪽 자식 링크를 타고 NULL이 나올 때까지 게속 진행하면 된다. 그렇게 찾아낸 값을 35의 왼쪽 링크 필드에 이어주고 22의 왼쪽 링크필드를 7에, 오른쪽 링크필드를 26에 연결해주면 된다.


출처: https://mattlee.tistory.com/30 [waca's field]

**(이부분은 더 공부가 필요한 듯 하다. 계산과 과정이 복잡하고 다양한 가능성들이 있어서 햇갈린다.)**


```
package 구현;

public class BinarySearchTree {
	
	public class Node{
		private int data;
		private Node left;
		private Node right;
		
		public Node(int data) {
			this.setData(data);
			setLeft(null);
			setRight(null);
		}
		
		public int getData() {
			return data;
		}
		
		public void setData(int data) {
			this.data = data;
		}
		
		public Node getLeft() {
			return left;
		}
		
		public void setLeft(Node left) {
			this.left = left;
		}
		
		public Node getRight() {
			return right;
		}
		
		public void setRight(Node right) {
			this.right = right;
		}		
	}
	
	public Node root;
	public BinarySearchTree() {
		this.root = null;
	}
	
	
	// 탐색 연산
	public boolean find(int id) {
		Node current = root;
		while(current!=null) {
			//현재 노드와 찾는 값이 같으면
			if(current.getData()==id)return true;
			// 찾는 값이 현재 노드보다 작으면
			else if(current.getData()>id) current = current.getLeft();
			// 찾는 값이 현재 노드보다 크면
			else current = current.getRight();
		}		
		return false;
	}
	
	// 삭제 연산
	public boolean delete(int id) {
		Node parent = root;
		Node current = root;
		boolean isLeftChild = false;
		while(current.getData()!=id) {
			parent = current;
			if(current.getData()>id) {
				isLeftChild = true;
				current = current.getLeft();
			}else {
				isLeftChild = false;
				current = current.getRight();
			}
			if(current == null)return false;  // 해당 노드가 없다면 삭제 실패
		}
		// Case 1 : 자식노드가 없는 경우
		if(current.getLeft()==null && current.getRight() == null) {
			System.out.println("Test");
			if(current==root) root = null;			
			if(isLeftChild = true)parent.setLeft(null);
			else parent.setRight(null);
		}
		// Case 2 : 자식노드가 하나인 경우.
		else if(current.getRight() == null) { // 자식 노드가 왼쪽인 경우.
			if(current==root) root = current.getLeft();
			else if(isLeftChild) parent.setLeft(current.getLeft());
			else parent.setRight(current.getLeft());
		}else if(current.getLeft() == null) { // 자식 노드가 오른쪽인 경우. 
			if(current==root) root = current.getRight();
			else if(isLeftChild) parent.setLeft(current.getRight());
			else parent.setRight(current.getRight());
		}
		// Case 3 : 두개의 자식을 갖는 경우
		else if(current.getLeft() != null && current.getRight() != null) {
			//오른쪽 서브트리의 최소값을 찾음
			Node successor = getSuccessor(current);
			if(current==root) {
				root = successor;
			}else if(isLeftChild) {
				parent.setLeft(successor);
			}else {
				parent.setRight(successor);
			}
			successor.setLeft(current.getLeft());
		}
		return true;
	}
	
	public Node getSuccessor(Node deleteNode) {
		Node successor = null;
		Node successorParent = null;
		Node current = deleteNode.getRight();
		while(current!=null) {
			successorParent = successor;
			successor = current;
			current = current.getLeft();
		}
		if(successor!=deleteNode.getRight()){
			successorParent.setLeft(successor.getRight());
			successor.setRight(deleteNode.getRight());			
		}
		return successor;
	}
	
	//삽입 연산. 
	public void insert(int id) {
		Node newNode = new Node(id);
		if(root==null) {
			root = newNode;
			return;
		}
		Node current = root;
		Node parent = null;
		while(true) {
			parent = current;
			if(id < current.getData()) {
				current = current.getLeft();
				if(current==null) {
					parent.setLeft(newNode);
					return;
				}
			}else {
				current = current.getRight();
				if(current ==null) {
					parent.setRight(newNode);
					return;
				}
			}
		}	
	}
	
	public void display(Node root) {
		if(root != null) {
			display(root.getLeft());
			System.out.print(" " + root.getData());
			display(root.getRight());
		}
	}
	
	public static void main(String[] args0) {
		
		BinarySearchTree b = new BinarySearchTree();
		
		b.insert(3);b.insert(8);
		b.insert(1);b.insert(4);
		b.insert(6);b.insert(2);
		b.insert(10);b.insert(9);
		b.insert(20);b.insert(25);
		b.insert(15);b.insert(16);
		
		b.display(b.root);
		System.out.println();
		System.out.println("4를 탐색 : " + b.find(4));
		System.out.println("2를 삭제 : " + b.delete(2));
		b.display(b.root);
//		System.out.println("4를 탐색 : " + b.find(4));
//		System.out.println("4를 탐색 : " + b.find(4));
	}
}


```
//위에 부분 제대로 코드가 작동안하던데... 공부 좀만 더해보겠음



### 2.3. 시간 복잡도 분석과 균형 잡힌 이진 검색 트리

이진 검색 트리에 대한 모든 연산은 모두 루트에서부터 한 단계씩 트리를 내려가며 재귀 호출을 통해 수행되므로, 최대 재귀 호출의 횟수는 트리의 높이 h와 같다.
따라서 모든 연산의 시간 복잡도가 트리의 높이 O(h)라고 할 수 있겠지만, 자료의 개수 N에 대해 트리의 높이 h가 어떻게 변하는지가 중요하다.

예를 들어 1부터 n까지의 숫자들을 차례대로 추가했다고 한다면 1의 오른쪽에 2, 그 오른쪽에 3 이런식으로 한쪽으로 기울어진 트리가 만들어진다.

이런 트리를 '기울어졌다'(skewed)고 한다. 이런 형태가 되어서는 트리를 사용하는 이유가 없다. 사실상 연결 리스트를 쓰는거랑 동일하게 된다.

그렇기에 우리가 원하는 가장 이상적인 케이스는 가급적 가로로 넓게 퍼지고 '평평한' 트리다.
트리의 높이가 1 높아질 때마다 트리에 들어갈 수 있는 원소의 수가 대략 두 배 늘어난다는 점을 고려하면 트리의 최소 높이는 O(lgN)이 된다. 앞의 기울어진 트리에 비교하면 엄청난 차이다.

최악의 기울어진 트리가 현실적으로 불가능한 것이 아니라는 것을 생각하면 그러한 것들을 대비해야할 필요도 있다.
그런 필요에 의해서 만들어진 것이 균형 잡힌 이진 검색 트리(balanced binary search tree)라고 부른다. 이들은 트리에 추가적인 제약을 걸어서 트리의 높이가 항상 O(lgN)이 되도록 유지한다. -- 레드-블랙 트리(red-black tree)

