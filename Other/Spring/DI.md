# DI(Dependency Injection) - 의존성 주입

먼저 스프링이라는 프래임워크를 공부하는 과정에서, 아직 많은 부분을 모르는 것이 많고 실수도 있을 수 있다는 것을 알리고 시작함.

> 의존성 주입이 뭔데?

스프링의 주요 모듈 중 하나라고 하는 DI, 근데 의존성이라는 것도 제대로 이해가 되지 않는데 의존성을 주입한다고 하니까 더더욱 이해가 안되는 용어였다.

DI가 어떤 특성을 갖는지 보다는 어떤 용어인지 먼저 이해하고 넘어가는 것이 맞는 것 같다.

**의존성 : 의존 관계를 의미한다.**
- 둘 이상의 객체가 서로 협력하는 방법에 대한 것

Ex) A는 B에 의존 -- B의 변화가 A에 영향을 미친다. (관리가 필요)
- Controller가 Repository에 의존
- Controller에 Repository에 연결

간단하게 설명한 것처럼 의존한다는 것은 연결된다는 것을 의미한다.'

역시 개발 공부하는 사람들은 이렇게 애매한 설명보다는 코드로 설명하는 것이 가장 이해가 잘 되는 것 같다.

### 의존성 주입 X = 클레스에 의존

```java
class Study {...} // 클레스 혹은 인터페이스

// Study 클래스를 상속
class Algorithm extends Study {...}
class Java extends Study {...}

class Student {
    private Study study;

    public Student() {
    	this.study = new Algorithm(); // 직접 수정
        // 또는 
        this.study = new Java(); // 직접 수정
    }
    ...
}
```

어떤 걸 공부하고 싶으냐에 따라서, study라는 객체를 직접 선언, 수정해주어야 한다.

study에 직접적으로 Algorithm이냐 Java냐를 수정해야 한다.   

처음에는 Algorithm이었다가, Java를 공부하고 싶다면, 직접 Java로 수정해야하는 것을 의미한다.

### 의존성 주입 O = 객체간의 결합도를 줄인다.

```java
class Student {
    private Study study;

    // 중간고사때 공부할 과목을 고를 수 있게 된다. 
    public Study(Study study) {
    	this.study = study;
    }
    
    public startStudy() {
    	this.study.start();
        ...
    }
}
```

하지만, 위와 같이 의존성을 주입한다고 한다면, Algorithm을 Java로 직접 수정할 필요없이 들어갈 객체를 변경하면 되는 유연한 코드 작성이 가능한 것! (결합도를 낮추고, 유연성을 높인다)

>  한 클래스를 수정하였을 때, 다른 클래스도 수정해야 하는 상황을 막아줄 수 있다!


가장 이해가 쉽게 된 이미지를 링크하겠다.

![](https://t1.daumcdn.net/cfile/tistory/21373937580AEF9B37)

[https://private.tistory.com/39]




