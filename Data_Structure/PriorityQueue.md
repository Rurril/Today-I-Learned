# 우선순위 큐

CS(Computer Science)에서, 우선순위 큐는 평범한 큐나 스택과 비슷한 축약 자료형이다. **그러나 각 원소들은 우선순위를 갖고**있다. 

우선순위 큐에서, 높은 우선순위를 가진 원소는 낮은 우선순위를 가진 원소보다 먼저 처리된다. 

이러한 성질을 이용해서 우선순위 큐는 운영체제의 `작업 스케쥴링`, `정렬`, `네트워크 관리` 등의 다양한 기술에 적용되고 있다. 


우선순위 큐는 최소한 다음의 연산이 지원 되어야 한다.
- `insert_with_priority` : 하나의 원소를 우선순위를 지정하여 큐에 추가한다.
- `pull_highest_priority_element` : 가장 높은 우선순위를 가진 원소를 큐에서 제거하고 이를 반환한다.

> 우선순위 큐는 일반적으로 힙을 이용하여 구현한다. 

우선순위 큐를 구현하는 방법 중 하나는 `Linked List`나 `Array`를 이용해 원소를 꺼낼 때마다 모든 원소를 순회해 우선순위가 가장 높은 원소를 찾는 방법이다. 
- 원소를 추가하는 데는  O(1)이, 원소를 꺼내는 데에는 O(n)의 시간이 걸린다.

하지만 Heap이라는 트리를 이용하면 훨씬 간단하고 성능 좋게 우선순위 큐를 구현할 수 있다. 


## 힙(Heap)

힙은 최댓값 및 최솟값을 찾아내는 연산을 빠르게 하기 위해 고안된 완전이진트리(Complete binary tree)를 기본으로 한 자료구조다.

- A가 B의 부모노드(parent node)이면 A의 키(key)값과 B의 키값 사이에는 대소관계가 성립한다.

> Parent >= Child

힙에는 두가지 종류가 있으며, 부모노드의 키값이 자식노드의 키값보다 항상 큰 힙을 '최대 힙', 부모노드의 키값이 자식노드의 키값보다 항상 작은 힙을 '최소 힙'이라고 부른다. 
- 키값의 대소관계는 오로지 부모노드와 자식노드 간에만 성립하며, 형제 사이에는 대소관계가 정해지지 않는다. 

### 힙의 모양

**힙은 완전 이진 트리(Complete binary tree)** 형태여야 한다.

이진 검색 트리에서 한쪽으로 기울어진 트리(skewed tree) 때문에 생기는 검색 시에 시간적 비효율을 해결하기 위해 균형잡힌 이진 검색 트리(Balanced Binary Search Tree)가 등장했듯이, 

힙에서도 기울어진 트리 문제를 간과할 수 없기 때문에 힙도 트리의 구조에 제약을 두어 트리의 높이를 항상 일정하게 유지한다. 

(힙은 트리의 높이를 O(logN) 으로 유지한다.)

힙에서 트리 높이를 항상 일정하게 유지하기 위해 두 가지의 조건으로 트리의 모양을 제한하고 있다.


1. 마지막 레벨을 제외한 모든 레벨에 노드가 꽉 차 있어야 한다.
2. 마지막 레벨에 노드가 있을 때는 항상 왼쪽부터 순서대로 채워져 있어야 한다.

![](https://miro.medium.com/max/1400/1*0Y4oWrfOyI5ZlE2lDJxQ0w.png)
--최대 힙 트리--

## 🤭 참고 문제

백준 온라인 저지
- [11279 - 최대힙](https://www.acmicpc.net/problem/11279)
- [1927 - 최소힙](https://www.acmicpc.net/problem/1927)
- [11286 - 절대값 힙](https://www.acmicpc.net/problem/11286)
- [1655 - 가운데를 말해요](https://www.acmicpc.net/problem/1655)

아래는 나중에 백준 문제 정리하는 문서로 옮길 것.
```java
// BOJ 1655 - 가운데를 말해요

public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		int n = Integer.parseInt(br.readLine());
		PriorityQueue<Integer> Maxqueue = new PriorityQueue<>(Comparator.reverseOrder());
		PriorityQueue<Integer> Minqueue = new PriorityQueue<>();

		int swap = 0;

		for (int i = 0; i < n; i++) {
			int num = Integer.parseInt(br.readLine());
			if (Maxqueue.isEmpty()) {
				Maxqueue.add(num);
			} else if (Maxqueue.size() == Minqueue.size())
				Maxqueue.add(num);
			else {
				Minqueue.add(num);
			}

			if (!Minqueue.isEmpty() && !Maxqueue.isEmpty()) {
                // 최대힙 value > 최소힙 value 일때 
				if ((Maxqueue.peek()<= Minqueue.peek())==false) {
                    // 최댓값을 -> 최소힙으로, 최솟값을 -> 최대힙으로 보냄으로 
                    // 최댓값의 가장 높은 우선순위에 중간값이 위치하게 한다.
                    
                    // 이러한 연산을 통해서 max_heap(낮은 우선순위) -> max_heap(높은 우선순위) -> min_heap(높은 우선순위) -> min_heap(낮은 우선순위) 의 순서대로 오름차순 정렬이 이루어진다. 
					swap = Maxqueue.peek();
					Maxqueue.poll();
					Maxqueue.add(Minqueue.peek());
					Minqueue.poll();
					Minqueue.add(swap);
				}
			}
			sb.append(Maxqueue.peek() + "\n");
		}
		System.out.println(sb);
	}

```

## 💌 참고자료

1. [Studing](https://hannom.tistory.com/36)
2. [pa324.log](https://velog.io/@pa324/%EC%9A%B0%EC%84%A0%EC%88%9C%EC%9C%84-%ED%81%90-1xk1cw46t2)
3. [위키피디아 - 우선순위 큐](https://ko.wikipedia.org/wiki/%EC%9A%B0%EC%84%A0%EC%88%9C%EC%9C%84_%ED%81%90)
4. [위키피디아 - 힙](https://ko.wikipedia.org/wiki/%ED%9E%99_(%EC%9E%90%EB%A3%8C_%EA%B5%AC%EC%A1%B0))
4. [Jiwon Bae의 블로그](https://medium.com/jiwon-bae/data-structure-%EC%9A%B0%EC%84%A0%EC%88%9C%EC%9C%84-%ED%81%90%EC%99%80-%ED%9E%99-c01947539d3d)