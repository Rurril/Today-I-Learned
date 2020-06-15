# Java Bean

자바빈즈(JavaBeans)는 자바로 작성된 컴포넌트.

자바빈즈의 사양은 썬 마이크로시스템즈에서 다음과 같이 정의되었다. 

> "빌더 형식의 개발도구에서 가시적으로 조작이 가능하고 또한 재사용이 가능한 소프트웨어 컴포넌트이다."


빈은 다음과 같은 규칙을 지키는 클래스다.

- 클래스는 직렬화되어야 한다.(클래스의 상태를 지속적으로 저장 혹은 복원 시키기 위해)
- 클래스는 기본 생성자를 가지고 있어야 한다.
- 클래스의 속성들은 get, set 혹은 표준 명명법을 따르는 메서드들을 사용해 접근할 수 있어야 한다.
- 클래스는 필요한 이벤트 처리 메서드들을 포함하고 있어야 한다

```java
/***********************************
* *
* PersonBean.java *
* *
************************************/
public class PersonBean implements java.io.Serializable
{
    private String name;
    private boolean coding;

    // 기본 생성자 (인자가 없는).
    public PersonBean()
    {

    }

    public String getName()
    {
        return this.name;
    }
    public void setName(String name)
    {
        this.name = name;
    }

    // Different semantics for a boolean field (is vs. get)

    public boolean isCoding()
    {
        return this.coding;
    }

    public void setCoding(boolean coding)
    {
        this.coding = coding;
    }
}
```

모든 변수들은 private 접근 제어자를 사용하며, 각 변수들에 대한 getter와 setter가 다 있는 이러한 정형화 되어있는 클래스를 빈이라고 한다.



## POJO ? Bean?

POJO는 Plain Old Java Object의 약자다.

번역하자면, 평범하고 오래된 자바 객체다. --> 순수한 Java Object

객체 지향의 중요한 개념 중 하나인 느슨한 의존관계를 중시하고 **가독성과 재사용성**을 중요시하게 하며 사용하는 것

POJO는 Bean보다 큰 개념이다. ( 빈이 포조에 속해있다. )

즉, 모든 Bean은 POJO지만, 모든 POJO가 Bean은 아니다.

빈이 좀 더 엄격한 규칙을 가지고 있는 개념으로

1. Serializable에 대한 인터페이스를 반드시 구현해야 한다.
2. Fields는 getter와 setter로만 접근할 수 있다.
3. Fields는 private 접근제어자로 되어있다.
4. Constructor에 argument를 가질 수 없다.

와 같은 엄격한 조건을 지켜야 한다.

## 빈을 사용해야 하는 이유

스프링에서는 기본적으로 bean을 싱글톤 디자인 패턴으로 관리한다.

- 의존성 주입을 통해서 **코드 수정이 용이하다**

> 아직 공부가 부족해서 여기까지 하지만, 일단 기본적으로 bean이 무엇인가, 그리고 왜, 어떻게 사용하는가에 대해서 기본적으로 공부를 해봤다.



## 참고자료

https://sanghye.tistory.com/13

https://www.hanumoka.net/2019/01/06/java-20190106-java-pojo-vs-bean/

https://pjh3749.tistory.com/75