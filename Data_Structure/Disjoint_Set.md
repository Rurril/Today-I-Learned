# 서로소 집합(Disjoint Set) - 유니온 파인드(Union-Find)

서로소 집합은 많은 서로소 부분 집합들로 나눠진 원소들에 대한 정보를 저장하고 조작하는 자료구조다.
- 서로소란 : 공통된 원소가 없는 집합으로, 교집합이 공집합인 집합이다.





아래의 그림의 A와 B가 서로소 집합이라고 할 수 있다.

![](https://encrypted-tbn0.gstatic.com/images?q=tbn%3AANd9GcR84uUFNVpdWOr2c2atYFd6TrylFZgPbZ4dkJGp1aahIlMrJ3Lo&usqp=CAU)


다른 말로 **유니온 파인드 자료구조**라고도 부르는 Disjoint set은 이름 그대로 union연산과 find연산, 기본적으로 2개의 연산을 지원하는 자료구조이다.

- `union(x, y)` : x가 속한 set과 y가 속한 set을 합친다.
- `find(x)` : x가 속한 set의 대표값(루트노드 값)을 반환한다.

서로 다른 서로소 집합에서 합치는 연산과 한 요소가 어느 집합에 속해있는 지를 판단할 수 있는 연산을 제공하는 자료구조라는 것이다. 

그렇다면 Union과 Find 연산을 어떻게 구현할까? 

기본적으로 Disjoint set은 각각의 집합을 트리 형태로 구현한다. 

## 파인드

**유니온을 설명하기 앞서 파인드는**

두 원소가 같은 집합에 속해 있는지 확인하는 연산이다. Disjoint set을 트리구조로 함으로써 각 집합은 **루트 노트**가 있으며, 연산을 통해서 임의의 요소의 정점에 있는 루트를 찾아준다. 

만약 자신이 루트라면 바로 자신을 리턴해주면 된다.

```c++
int find(int n){
    if(p[n] < 0)return n;
    return find(p[n]);
}
```

**아래 부분 수정 요함** 

자신의 부모를 가리키는 배열이 p이고, 자신이 루트라면 음수값(-1)을 리턴해주게 구현한다. 

헌데 한 가지 걸리는 점이 있습니다.

만약 여기서 find(6)을 수행한다면, 6부터 2까지의 경로가 일직선이라서 좀 많은 횟수의 재귀함수 호출이 이루어집니다.

게다가 find(6) 같이 이렇게 경로가 길 함수를 많이 부르면 그만큼 총 실행시간 합이 엄청 늘어나버리지 않을까요?

여기서 우리는 한 가지 개선안을 내놓을 수 있습니다. 만약 한 번 6의 루트가 2인 걸 알았다면, 왜 다음 번에 다시 그걸 구해야 하죠? 벌써 2라는 것을 알고 있는데!

이건 메모이제이션과도 비슷한 아이디어인데, 여기서는 트리가 추후 변형될 수도 있기 때문에 이런 일을 해봅시다. 6의 루트가 2인 걸 알았다면, 6을 떼어내서 바로 2의 아래에 이어버린다! 

그렇게 하면 2가 나중에 만약 루트가 아니라 다른 누군가의 자식이 되어도, 2부터 따라가서 새 루트를 찾으면 될 일입니다.

[출처] 유니온 파인드(Union-Find) (수정: 2019-11-12)|작성자 라이


## 유니온
**유니온은**

{0} 과 {1} 이라는 다른 요소를 갖는 서로 다른 집합이 있다고 할 때, 이 두가지 집합을 합쳐주는 연산이다.

연산의 결과로 {0, 1} 이라는 집합이 완성된다. 
```C++
void union(int a, int b){
    a = find(a);
    b = find(b);
    if(a == b) return;
    p[b] = a;
}
```

## 🤭 참고 문제

백준 온라인 저지
- [1717 - 집합의 표현](https://www.acmicpc.net/problem/1717)

```java
public class question1717 {

    static int n,m;
    static int[] parent;
    static BufferedWriter bw;
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        bw = new BufferedWriter(new OutputStreamWriter(System.out));

        String[] temp = br.readLine().split(" ");
        n = Integer.parseInt(temp[0]);
        m = Integer.parseInt(temp[1]);
        parent = new int[n+1];
        for(int i=0;i<=n;i++)parent[i] = i;

        for(int i=0;i<m;i++){
            temp = br.readLine().split(" ");
            int command = Integer.parseInt(temp[0]);
            int x = Integer.parseInt(temp[1]);
            int y = Integer.parseInt(temp[2]);

            if(command == 0){ // 합집합 연산
                union(x, y);
            }else if(command == 1){ // 확인 연산
                isSameParent(x, y);
            }
        }
        bw.flush();
    }

    public static void union(int x, int y){
        x = find(x);
        y = find(y);
        if(x != y)parent[y] = x;
    }

    public static int find(int x){
        if(x == parent[x])return x;
        else return parent[x] = find(parent[x]);
    }

    public static void isSameParent(int x, int y) throws IOException {
        x = find(x);
        y = find(y);
        if(x == y) bw.write("YES\n");
        else bw.write("NO\n");
    }

}
```


## 💌 참고 자료

1. [ratsgo's blog](https://ratsgo.github.io/data%20structure&algorithm/2017/11/12/disjointset/)
2. [위키피디아 - 서로소 집합 자료 구조](https://ko.wikipedia.org/wiki/%EC%84%9C%EB%A1%9C%EC%86%8C_%EC%A7%91%ED%95%A9_%EC%9E%90%EB%A3%8C_%EA%B5%AC%EC%A1%B0)
3. [Ries 마법의 슈퍼마리오](https://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220791837179&categoryNo=299&parentCategoryNo=0&viewDate=&currentPage=10&postListTopCurrentPage=1&from=menu&userTopListOpen=true&userTopListCount=5&userTopListManageOpen=false&userTopListCurrentPage=10)
4. [heejoeng Kwon's github-blog](https://gmlwjd9405.github.io/2018/08/31/algorithm-union-find.html)