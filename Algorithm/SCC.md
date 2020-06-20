# SCC(Strongly Connected Component) 



## 정의

기본적으로 방향이 있는 유향 그래프에서 적용되는 개념이다.

유향 그래프에서 모든 정점에서 모든 다른 정점에 도달 가능한 경우, 그래프는 **강하게 연결되었다** 라고 말한다. 

예를 들어서 설명하면, 그래프 요소 (a, b, c)가 있다고 할 때 

어느 요소에서 시작하더라도 모든 다른 정점에 도달할 수 있어야 한다. 

- a -> b -> c
- b -> c -> a
- c -> a -> b

만약에 이러한 과정속에서 하나라도 다른 정점에 도달하지 못하면 SCC를 만족하지 못한다.

좀 더 정의하듯이 정리하면

1. SCC내에서 임의의 두 점점 (u, v)사이의 u -> v경로와 v -> u 경로가 항상 존재한다.
2. SCC내의 임의의 정점 u와 외부의 임의의 정점 v 사이에 u -> v 경로와 v -> u 경로가 동시에 존재하는 경우는 없다.

1번이 성립된다면 SCC라고 할 수 있겠고, 2번이 성립되지 않는다면, SCC 결합을 잘못한 경우가 되겠다.

(혹은 코딩을 잘못했거나...)

### 무향 그래프

위의 예시에서 설명했던 것처럼, 무향 그래프 - 서로 연결되어 있는 정점들이라면 모든 그래프 내의 정점들은 사이클을 이루고 SCC도 성립한다. 

즉, 사이클을 이루면 SCC도 성립한다고 볼 수 있다. 

> SCC는 사이클과 밀접하게 연관되어 있다.

## 왜 쓰는 것일까?

그래프에서 SCC를 이루는 정점들 끼리는 하나의 그룹으로 묶을 수 있고, 그렇게 함으로써 그래프를 사이클을 이루지 않는 여러 개의 그룹으로 나눌 수 있다. 

--> 그룹을 한 정점으로 하는 새로운 그래프(DAG - Directed Acyclic Graph)로 만드는 **압축(Condensation)**할 수 있다. 

## SCC를 구하는 방법

크게 알려진 알고리즘은 아래의 2가지 이다.

1. 코사라주 알고리즘(Kosaraju's Algorithm)
2. 타잔 알고리즘(Tarjan's Algorithm)

현재(2020.06.20) 기준으로 막 공부를 시작한 타이밍이어서, 정리중이기 때문에 문제를 통해서 배운 코사라주 알고리즘을 먼저 정리해보도록 하겠다.

### 코사라주 알고리즘 

이 알고리즘은 원래 방향 그래프에서 역방향(간선의 방향을 뒤집은) 그래프가 원래 그래프와 정확히 같은 강한 연결 요소(SCC)를 갖는다는 사실을 이용한다.


이 알고리즘은 3가지 단계를 통해서 진행된다.

1. 주어진 유향 그래프에서 임의의 정점에서 스택을 이용해서 DFS를 수행한다.
2. 역방향 그래프를 만들고, 1번에서 만든 DFS 순서대로 정점을 탐색한다.
3. pop이된 정점은 DFS를 수행하는데, 정점 u에서 시행해서 u로 돌아온다면 DFS를 끝낸다.
4. 3의 과정을 반복

구현 과정을 코드로 보여주도록 하겠다.

```java
// 1번 과정 : 주어진 유향 그래프에서 임의의 정점에서 스택을 이용해서 DFS를 수행한다.
st = new Stack<Integer>();
for(int i=1; i<=V; i++){
    if(visited[i] == 0)dfs(i);
}
// ...
private static void dfs(int number){
    visited[number] = cnt++;
    for(int i=0; i < con[number].size(); i++){
        int n = con[number].get(i);
        if(visited[n] == 0)
            dfs(n);
    }
    st.push(number);
}
```

방문 순서대로 (cnt) 인덱스를 부여하고 

DFS로 전부 탐색하고 아직 탐색하지 않은 정점이 있을 수 있으므로, 전체에 대해서 DFS로 탐색해준다.

위의 과정을 통해서 

1. 각 정점에 visited 배열을 통해서 인덱싱을 진행했다.
2. 인덱싱한 순서대로 stack에 정점들을 넣었다.


```java
// 2,3번 과정 : 역방향 그래프를 만들고, 1번에서 만든 DFS 순서대로 정점을 탐색한다.
checked = new boolean[V+1];
answer = new ArrayList<ArrayList<Integer>>();

while(!st.isEmpty()){ 
    ans = new ArrayList<Integer>(); // 전역 변수 
    int current = st.pop();
    if(!checked[current]){
        SCC(current); 
        if(ans.size() > 0){
            ans.sort(null);
            answer.add(ans);
        }
    }
}
// ...
private static void SCC(int number){
    ans.add(number);
    checked[number] = true;
    for(int j=0; j< revcon[number].size(); j++){
        int n = revcon[number].get(j);
        if(!checked[n])
            SCC(n);
    }
}
```

한 번의 SCC 메소드를 통해서 나오게 된 ans 배열에는 SCC로써 묶인 객체가 저장되게 된다.

ans.size() == 0이라면, 그 정점을 통해서 아무런 SCC를 이루지 않는다는 뜻이 된다.

(SCC를 이루지 않는 정점이 있을 수 있음)

그리고 저장된 ans 배열을 정렬하고 answer 배열에 저장한다.

> SCC 메소드는 DFS방식으로 방문한 적이 있는 곳이라면 진행하지 않음으로써 사이클이 있을 때 혹은 이미 SCC를 이루고 있는 다른 집단이라면 종료한다.


위까지의 과정을 마친다면, 원하는 SCC들이 담긴 answer 객체가 완성된다.

[https://www.acmicpc.net/problem/2150](https://www.acmicpc.net/problem/2150) 문제를 풀면서 진행하였다.



### 타잔 알고리즘

예정








## 💌 참고 자료

1. [BOJ 2150 - Strongly Connected Component](https://www.acmicpc.net/problem/2150)
