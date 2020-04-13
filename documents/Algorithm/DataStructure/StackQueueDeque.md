# 큐와 스택, 데크

## 1.1 도입

큐와 스택, 데크는 일렬로 늘어선 같은 형태의 자료들을 저장한다. 이때 세 자료 구조들을 구분하는 것은 어느 쪽 끝에서 자료를 넣고 뺄 수 있는가다.

- **큐(queue)에서는 한쪽 끝에서 자료를 넣고 반대 쪽 끝에서 자료를 꺼낼 수 있습니다.** 
  - 이와 같은 속성에 따라, 가장 먼저 들어간 자료를 가장 먼저 꺼내게 된다. 이 속성을 선입선출(FIFO, First In First Out)이라고 부른다. 
  - 너비 우선 탐색(BFS)에서 사용한다.
  - 컴퓨터 버퍼에서 주로 사용
![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2FzHUPa%2Fbtqx60VRYdp%2FQPMF62rkahGSL5tzl5TYbK%2Fimg.png)


- **스택(stack)에서는 한쪽 끝에서만 자료를 넣고 뺼 수 있다.**
  - 따라서 가장 늦게 들어간 자료를 가장 먼저 꺼내게 되며, 이 속성을 후입선출(LIFO, Last In First Out)이라고 부른다.
  - 스택은 전산학 전반적으로 사용한다. 함수 호출이 끝나고 이전 함수로 돌아갈 때, 이 함수 바로 이전의 함수로 돌아가기 위해서 컴퓨터 내부적으로 스택을 사용해 문맥(context)을 관리한다.
  - 깊이 우선 탐색(DFS)에서 사용한다.
  - 재귀적(Recursion) 함수를 호출 할 때 사용한다.
![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fk.kakaocdn.net%2Fdn%2FchSIl3%2Fbtqx60O47Om%2Fg4dMrq8KSyobAkspK6JLJ0%2Fimg.png)

- **덱(deque)는 양쪽 끝에서 자료들을 넣고 뺄 수 있는 자료 구조를 말한다.**
  - 따라서 덱을 이용하면 스택과 큐를 모두 구현할 수 있다.

![](https://m.blog.naver.com/c_18/10184053861?view=img_1)
  
자료구조에 자료를 넣는 작업을 푸쉬(push) 그리고 자료를 꺼내는 작업을 팝(pop)이라고 한다.
큐와 스택은 각각 넣고 빼는 방향에 따라 푸쉬와 팝 연산을, 그리고 덱은 앞과 뒤에서 모두 푸쉬와 팝 연산을 지원한다. 특정 쪽에서만 삽입 삭제 연산이 이루어지므로 **연결 리스트**로 구현해야 한다. **이들 연산은 모두 상수 시간, 즉 O(1)에 이루어져야 하기 때문이다.**


## 참고 자료
[더넬의 알짜정보!](https://m.blog.naver.com/c_18/10184053861)

[IT 내맘대로 끄적끄적](http://itnovice1.blogspot.com/2019/01/blog-post.html)

[자주 참고하는 블로그](https://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220781557098&categoryNo=299&parentCategoryNo=0&viewDate=&currentPage=12&postListTopCurrentPage=1&from=menu&userTopListOpen=true&userTopListCount=5&userTopListManageOpen=false&userTopListCurrentPage=12)

