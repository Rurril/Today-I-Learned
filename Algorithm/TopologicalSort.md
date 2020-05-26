# 위상 정렬(Topological Sort)

## 정의

위상 정렬은 방향 그래프의 꼭짓점들(vertex)을 방향을 거스르지 않도록 나열하는 것을 의미한다. 



## 특징

![](https://t1.daumcdn.net/cfile/tistory/2516C04E58DE331006)

즉, '순서가 정해져있는 작업'을 차례로 수행해야 할 때 그 순서를 결정해주기 위해서 사용하는 알고리즘이다. 여러 경로가 있을 수 있으므로, 다양한 답이 나올 수 있는 알고리즘이다. 

> 한 과목을 듣기 위해선 전에 선수 과목을 들어야 하는 조건이 있는 것을 위상 정렬이 필요한 예로 들 수 있겠다. 

또한, 사이클(자기 자신으로 돌아오는 경로)이 없어야 한다는 조건이 있다. 

예를 들어 1 -> 2 -> 3 -> 4 의 순서로 진행된다면, 어떤 일을 먼저 시작해야 하는지 알 수 없게 된다. 

> 이러한 사이클이 없는 방향 그래프를 DAG(Directed Acyclic Graph)라고 한다. 

위상 정렬 알고리즘은 두 가지 결과를 만들어 낸다.
1. 현재 그래프가 위상 정렬이 가능한지에 대한 여부
2. 위상 정렬이 가능하다면, 그 결과는 무엇인지

## 구현 (추가 예정)

위상 정렬을 구현할 수 있는 방법은 크게 2가지가 있다.
- Stack
- Queue



## 🤭 참고 문제

백준 온라인 저지
- [2252 - 줄 세우기](https://www.acmicpc.net/problem/2252)


```java
public class question2252 {

    static int n; // 노드 개수
    static int e; // 간선 개수
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st = new StringTokenizer(br.readLine());

        n = Integer.parseInt(st.nextToken());
        e = Integer.parseInt(st.nextToken());
        List<List<Integer>> list = new ArrayList<List<Integer>>();
        int[] indegree = new int[n+1];

        for(int i=0;i<n+1;i++) list.add(new ArrayList<Integer>());

        for(int i=0;i<e;i++){
            st = new StringTokenizer(br.readLine());

            // v1 to v2
            int v1 = Integer.parseInt(st.nextToken());
            int v2 = Integer.parseInt(st.nextToken());

            list.get(v1).add(v2);
            indegree[v2]++;
        }

        topologicalSort(indegree, list);
    }

    public static void topologicalSort(int[] indegree, List<List<Integer>> list){

        Queue<Integer> q = new LinkedList<Integer>();
        Queue<Integer> result = new LinkedList<Integer>();

        // indegree가 0인 노드를 queue에 넣기
        for(int i=1;i<=n;i++) if(indegree[i] == 0)q.offer(i);

        // q에서 노드를 하나씩 뺴며 연결된 노드의 indegree 감소 시킨다.
        // indegree가 0이 된 노드를 result Queue에 넣기
        while(!q.isEmpty()){
            int node = q.poll();
            result.offer(node);

            for(Integer linked : list.get(node)){
                indegree[linked]--;
                // indegree가 0이 된 노드를 q에 넣고 작업.
                if(indegree[linked] == 0)q.offer(linked);
            }
        }

        // 결과 출력
        while(!result.isEmpty()){
            System.out.print(result.poll() + " ");
        }

    }
}
```

## 💌 참고 자료

1. [위키피디아 - 위상정렬](https://ko.wikipedia.org/wiki/%EC%9C%84%EC%83%81%EC%A0%95%EB%A0%AC)
2. [heejeong Kwon's github-blog](https://gmlwjd9405.github.io/2018/08/27/algorithm-topological-sort.html)
3. [안경잡이 개발자 블로그](https://m.blog.naver.com/ndb796/221236874984)
4. [max9106.log](https://velog.io/@max9106/Algorithm-%EC%9C%84%EC%83%81-%EC%A0%95%EB%A0%ACTopology-Sort)
5. [남남서의 블로그](https://namnamseo.tistory.com/entry/Topological-Sort-%EC%9C%84%EC%83%81%EC%A0%95%EB%A0%AC)