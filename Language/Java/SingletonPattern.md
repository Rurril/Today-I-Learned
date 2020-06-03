# Singleton Pattern(싱글톤 패턴)

어플리케이션이 시작될 때 어떤 클래스가 **최초 한번만** 메모리를 할당하고(static) 그 메모리에 인스턴스를 만들어 사용하는 디자인 패턴

> 생성자가 여러 차례 호출되더라도 실제로 생성되는 객체는 하나고, 최초 생성 이후에 호출된 생성자는 최초에 생성한 객체를 반환한다.
>> 자바에서는 private로 선언해서 생성 불가능하게 하고 getInstance()로 받아쓰곤 함

## 싱글톤 패턴을 사용하는 이유

- 한 번의 객체 생성으로 재사용이 가능하기 때문에 메모리 낭비를 방지한다.
- 싱글톤으로 생성된 객체는 전역성을 띄기 때문에 다른 객체와 공유하기 좋다.
> 주로 공통된 객체를 여러개 생성해서 사용하는 DBCP(DataBase Connection Pool)와 같은 상황에서 많이 사용된다.

## 구현

```java
public class Company{

    private staitc Company instance = new Company(0);
    
    private Company(){} // 생성자를 private로 선언

    public static Company getInstance(){

        if(instance == null)
            instance = new Company();
        return instance;
    }
}
```

위와 같이 Company 클래스를 디자인한다면

다른 클래스에서 아무리 많은 Company 인스턴스를 생성
(`Company company1 = Company.getInstance()`) 하더라도 처음에 생성한 객체를 참조하게 된다. 

## 문제점

- 한 객체를 공유하는 몇 가지 케이스에서만 효율적이고 그 외에 문제점이 생길 수 있다.
- 싱글톤 패턴으로 생성된 객체가 간단한 역할이 아니라 복잡한 역할을 맡게 된다면, **다른 객체간의 결함도**가 높아져서 OOP의 설계 원칙에 어긋난다.(개방적이게 된다)
- 멀티 스레드 환경에서 안전하지 않아서, 동시에 여러 객체가 생성될 수 있다.

## 멀티쓰레드에서 안전한(Thread-safe) 싱글톤 클래스, 인스턴스 만드는 방법

@TODO 
더 공부해서 채워넣자

## 참조

[정아마추어 코딩블로그](https://jeong-pro.tistory.com/86)

