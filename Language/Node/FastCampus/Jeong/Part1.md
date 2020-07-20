# Node 핵심 과정



## Node.js_Chapter1_강의소개

강의 특징
- Why? 탐구와 이해
- 문제해결 중심
- 개념적 접근을 통한 깊이 있으면서ㅓ도
- 이해하기 쉽고 자세하게
- 다양한 실습 프로젝트



## Node.js_Chapter1_개발환경설정(Windows)


## Node.js_Chapter1_개발환경설정(MAC)


## Node.js_Chapter1_레벨 테스트



## Node.js_Chapter1_IO와 프로그래밍 패러다임

웹 어플리케이션에서 속도와 성능이 가장 중요한 요소.

### 비동기 vs 동기

동기화 : 해당하는 기기와 다른 기기의 데이터를 일치화 시키는 것. 

그렇기 때문에 데이터를 일치화 시키는 것에 대해서 시간이 걸리기 때문에, 비동기를 적용한다면 속도가 빠르게 될 수 있다.

### Non-blocking vs blocking

Blocking : 해당하는 코드가 완료될 때까지 다른 코드를 진행하지 못하게 하는 것

Node.js에서 Non-blocking을 사용한다.
- JS가 웹 언어이기 때문에(애초에 JS가 Non-blocking 모델을 사용한다)
- JS는 이벤트 주도 방식의 개발 언어다 => 사용자 요청하는 작업이 이루어졌을 때 작동하도록 한다.

### 요약

컴퓨터 작업은 결국 입력을 받고(Input)과 결과물(Output)을 내놓는 것.

작업을 병렬적으로 해결하기 위해서 비동기와 Non-blocking 모델을 채택해서 사용함.


## Node.js_Chapter1_Node vs browser

`window` 라는 프론트 엔드의 JS의 기능 -> Node.js에서는 지원하지 않는다.
- 웹브라우저에서 작동하는 글로벌 객체 - 브라우저 상의 화면을 의미하기에
- 백 엔드에서는 웹 브라우저가 없기 때문에 사용할 수 없다. 


`import React from 'react'` --> JS에서 사용하는 방식

`const dns = require('dns')` --> Node에서 사용하는 방식


```
const - 특정한 상수로써 변하지 않는 값을 사용
let - 스코프(범위) 내에서만 작동하는 변수
var - 파일 내부 전에서 작동하는 변수
```



## Node.js_Chapter1_Node.js REPL


Node.js에 대해서 활용하는 방법

- Read – 유저의 값을 입력 받아 JavaScript 데이터 구조로 메모리에 저장합니다.
- Eval – 데이터를 처리(Evaluate) 합니다.
- Print – 결과값을 출력합니다.
- Loop – Read, Eval, Print 를 유저가 Ctrl+C를 두번 눌러 종료할때까지 반복합니다.

특정한 객체의 정보에 대해서 궁금할 때 간단하게 알아볼 수 있다. 

파일을 생성하지 않고, 한 줄씩 실행시키고 싶을 때 활용하면 된다. 


## Node.js_Chapter1_npm 기초

npx - 해당하는 패키지를 단순히 설치하는 것이 아니라 실행하는 것을 목표로 함.

npm install - 설치

npm uninstall - 삭제 (글로벌 옵션을 주었다면, 똑같이 -g를 넣어준다)



## Node.js_Chapter1_Semantic versioning


## Node.js_Chapter1_npx


## Node.js_Chapter1_nodemon (재촬영)


## Node.js_Chapter1_Module.exports


## Node.js_Chapter1_Event Loop 자료구조 (재촬영)


## Node.js_Chapter1_Event Loop 실습 (재촬영)

---

## Node.js_Chapter2_every


## Node.js_Chapter2_Find, includes


## Node.js_Chapter2_forEach


18. Node.js_Chapter2_Map, Filter (재촬영)
2:49

19. Node.js_Chapter2_Object.assign vs spread
6:46

20. Node.js_Chapter2_Set
4:53

21. Node.js_Chapter2_some
5:33

22. Node.js_Chapter2_Template String
6:29

23. Node.js_Chapter2_String
11:24

24. Node.js_Chapter2_Type checking
3:50

25. Node.js_Chapter2_Hoisting (재촬영)
3:17

26. Node.js_Chapter2_IIFE (재촬영)
5:11

27. Node.js_Chapter2_setInterval (재촬영)
1:24

28. Node.js_Chapter3_Error handling (재촬영)
1:32

29. Node.js_Chapter3_Error handling 연습문제 (재촬영)
1:27

30. Node.js_Chapter3_Error handling 연습문제 해설 (재촬영)
1:27

31. Node.js_Chapter3_Arrow Functions
8:45

32. Node.js_Chapter3_Arrow Functions 연습문제
9:37

33. Node.js_Chapter3_Arrow Functions 연습문제 해설
17:07

34. Node.js_Chapter3_Class (1) (기존영상)
15:05

35. Node.js_Chapter3_Class Extends (기존영상)
9:35

36. Node.js_Chapter3_Class (1) (추가촬영)
2:34

37. Node.js_Chapter3_Class (2) (추가촬영)
3:50

38. Node.js_Chapter3_Static method
5:44

39. Node.js_Chapter3_Destructuring
6:39

40. Node.js_Chapter3_Generator 개념적 접근
8:46

41. Node.js_Chapter3_Generator 심화 (재촬영)
1:55

42. Node.js_Chapter3_Timers
13:07

43. Node.js_Chapter3_Event Emitter
8:30

44. Node.js_Chapter3_DNS
10:01

45. Node.js_Chapter3_file system (1)
11:10

46. Node.js_Chapter3_file system (2)
15:12

47. Node.js_Chapter3_Promise.All
7:07

48. Node.js_Chapter3_Promise.race
6:24

49. Node.js_Chapter4_http
8:02

50. Node.js_Chapter4_https
13:02

51. Node.js_Chapter4_Class vs Prototype (1)
9:56

52. Node.js_Chapter4_Class vs Prototype (2)
11:48

53. Node.js_Chapter4_Node.js TDD 프레임워크 소개
14:28

54. Node.js_Chapter4_Memory Leaks 개념적 접근
12:21

55. Node.js_Chapter4_Node.js core repo로 살펴보는 TDD 실무
12:30

56. Node.js_Chapter4_Node.js Design Patterns (1)
9:53

57. Node.js_Chapter4_Node.js Design Patterns (2)
9:26

58. Node.js_Chapter4_Node.js Design Patterns (3)
7:36

59. Node.js_Chapter4_Node.js Design Patterns (4)
8:07

60. Node.js_Chapter4_Node.js Design Patterns (5) (추가촬영)
2:39

61. Node.js_Chapter4_Node.js Design Patterns (6) (추가촬영)
3:03

62. Node.js_Chapter4_Node.js Design Patterns (7) (추가촬영)
3:15

63. Node.js_Chapter4_Node.js Design Patterns (8) (추가촬영)
1:39

64. Node.js_Chapter4_비동기 패턴(1)
14:49

65. Node.js_Chapter4_비동기 패턴(2)
17:25

66. Node.js_Chapter4_비동기 패턴(3)
11:32

67. Node.js_Chapter4_비동기 패턴(4) (재촬영)
2:16

68. Node.js_Chapter5_Race Conditions (1)
13:08

69. Node.js_Chapter5_Race Conditions (2)
11:06

70. Node.js_Chapter5_Race Conditions (3)
13:42

71. Node.js_Chapter5_Race Conditions 연습문제
5:25

72. Node.js_Chapter5_Race Conditions 연습문제 해설
13:57

73. Node.js_Chapter6_CPU Profiling에 대한 이해
8:47

74. Node.js_Chapter6_CPU Profiling 분석 기법
14:50

75. Node.js_Chapter6_CPU Profiling 분석 실무 프로젝트
5:46

76. Node.js_Chapter6_Heap Snapshot에 대한 이해
8:09

77. Node.js_Chapter6_Node.js Heap Snpashot 분석 프로젝트 (1)
5:16

78. Node.js_Chapter6_Node.js Heap Snpashot 분석 프로젝트 (2)
5:55