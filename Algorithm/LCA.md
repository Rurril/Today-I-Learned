# LCA(Lowest Common Ancestor) 



## 정의

최소 공통 조상 - LCA를 찾는 알고리즘이다. 

두 정점(u, v)에서 가장 가까운 공통 조상을 찾는 알고리즘.

![](https://i.ibb.co/cJyDMWK/28621841-E329-4-A2-F-83-EF-CE242-FF9-C53-B.jpg)

예를 들어 다음과 같은 트리가 있다고 할 때, 

(9)와 (6)의 가장 가까운 공통 조상은 (4)가 된다.


## 동작 과정

LCA 알고리즘을 먼저 DP를 통해서 구현함을 명시하겠다.

가장 단순하게(Naive)하게 구현하면, 각 노드를 기준으로 depth와 바로 위 parent를 구하면 된다.

`int[] parent, depth;`

위의 트리 그림을 기준으로 설명하면

|인덱스|깊이|부모|
|------|---|---|
|1|1|0|
|2|2|1|
|3|3|1|
|4|3|2|
|5|3|2|
|6|4|4|
|7|4|4|
|8|5|7|
|9|5|8|
|10|3|3|
|11|4|11|
|12|4|12|

이렇게 입력이 된다.

이렇게 입력된 정보를 바탕으로 LCA를 구할 수 있다.

**임의의 x, y값을 입력받고 두 정점의 LCA를 찾는다고 해보자**

> 여기서 y가 x보다 깊이가 더 깊거나 같다고 가정한다.

가장 먼저, x와 y를 같은 높이가 될때까지 올린다.

```java
while(depth[x] != depth[y]){
    y = parent[y];
}

```

여기서 x == y라면 두 정점의 LCA가 x라는 의미다.

하지만 아직 x != y라면

같은 공통부모를 찾을 때까지 한 칸씩 올린다.

```java
while(parent[x] != parent[y]){
    x = parent[x];
    y = parent[y];
}
```

최종적으로 x == y가 된다면, 그 값이 LCA가 된다!

## 좀 더 시간복잡도를 좋게하는 법

사실 위에 서술한 방식은 굉장히 단순한 방식으로 LCA를 구한 것이다.

위와 같이 LCA를 구현하게 된다면 N개의 노드와 M개의 쿼리가 있다고 했을 때, 한쪽으로 기울어진(skewed)된 최악의 트리의 경우, N = 높이가 되어 시간복잡도가 O(NM)이 되어 많은 노드와 쿼리를 처리하기 힘들게 된다.

그래서 좀 더 개선된 O(MlogN)의 방식을 설명하도록 하겠다.

논리는 거의 다 같지만, 부모를 갖는 값을 바로 위 뿐만 아니라 2^0번째 조상, 2^1번째 조상 ... 2^n번째 조상을 저장하도록 하는 것.

`int[][] parent = new int[N][20];` -- 2^19번째 조상까지 갖도록 임의로 설정

이와 같이 선언 후 값을 저장하게 된다면 한쪽으로 기울어진 트리라는 최악의 경우에도 O(logN)의 시간 복잡도로 처리가 가능하다.

```java
private static void BFS(){
    int start = 1;

    Queue<Integer> q = new LinkedList();
    q.add(start);

    //최초 시작점의 부모는 0
    parent[0][start] = 0;

    while(!q.isEmpty()){
        int current = q.poll();

        for(int next : adList[current]){
            if(next != parent[0][current]){ // 부모방향으로 갈 수 없음.
                depth[next] = depth[current] + 1;

                parent[0][next] = current;
                q.add(next);
            }
        }
    }
}
```

BFS를 통해서 depth와 바로 위 부모인 parent[0] => 2^0을 구해주고

```java
private static void setParent(){
    for(int i=1; i<=K; i++){
        for(int j=1; j<=N; j++){
            parent[i][j] = parent[i-1][parent[i-1][j]];
        }
    }
}
```

2^i번째 부모를 위의 방식과 같이 구할 수 있다.




## 💌 참고 자료

1. [BOJ 11437 - LCA](https://www.acmicpc.net/problem/11437)
2. [BOJ 11438 - LCA 2](https://www.acmicpc.net/problem/11438)
3. [BOJ 1761 - 정점들의 거리](https://www.acmicpc.net/problem/1761)