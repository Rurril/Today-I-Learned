# OOP - Object Oriented Programming(객체지향 프로그래밍)

> 인스턴스 - 클래스로부터 생성된 객체, 힙 메모리에 멤버 변수의 크기에 따라 메모리가 생성

클래스를 기반으로 new 키워드를 이용하여 여러개의 인스턴스 생성


## 참조 자료형

자료형 
1. 기본 자료형(Primitive type)
    - int, long, boolean, char 등
2. 참조 자료형(Reference type)
    - 클래스를 기반으로 사용


## This

자기 자신의 메모리를 가리키는 this

생성자에서 다른 생성자를 호출

```java
public Person(){
    this("이름없음", 1);
}

public Person(String name, int num){
    this.name = name;
    this.num = num;
}
```
다음과 같은 식으로 자신의 다른 생성자를 호출해서 사용하기도 한다. 

## static 변수

여러 인스턴스가 하나의 값을 공유할 필요가 있음

static 변수는 처음 프로그램이 로드 될 때 데이터 영역에 생성 됨

인스턴스의 생성과 상관 없이 사용할 수 있으므로 클래스 이름으로 참조

```java
public class Student{

    public static int serialNum = 1000;

    public Student(){
        serialNum++;
    }

}
```

위와 같이 Student 클래스의 static 변수 serialNum은 다른 클래스에서 여러 Student 인스턴스를 생성하더라도 동일한 값을 같도록 되어있다. 

> 데이터 영역에 위치한 동일한 메모리를 참조하기 때문 (스택이나 힙이 아님)

**변수 유형**

지역 변수(로컬 변수)
- 선언 위치 : 함수 내부에 선언
- 사용 범위 : 함수 내부에서만 사용
- 메모리 : 스택
- 생성과 소멸 : 함수가 호출될 때 생성되고 함수가 끝나면 소멸함


멤버 변수(인스턴스 변수)
- 선언 위치 : 클래스 멤버 변수로 선언
- 사용 범위 : 클래스 내부에서 사용하고 private가 아니면 참조 변수로 다른 클래스에서 사용 가능
- 메모리 : 힙
- 생성과 소멸 : 인스턴스가 생성될 때 힙에 생성되고, 가비지 컬렉터가 메모리를 수거할 때 소멸됨

static 변수(클래스 변수)
- 선언 위치 : static 예약어를 사용하여 클래스 내부에 선언
- 사용 범위 : 클래스 내부에서 사용하고 private이 아니면 클래스 이름으로 다른 클래스에서 사용 가능
- 메모리 : 데이터 영역
- 생성과 소멸 : 프로그램이 처음 시작할 떄 상수와 함께 데이터 영역에 생성되고 프로그램이 끝나고 메모리를 해제할 때 소멸됨



## 상속과 다형성

### 상위 클래스로의 묵시적 형 변환(업 캐스팅)

상위 클래스 형으로 변수를 선언하고 하위 클래스 인스턴스를 생성할 수 있음

하위 클래스는 상위 클래스의 타입을 내포하고 있으므로, 상위 클래스로 묵시적 형변환이 가능함

> 상속관계에서 모든 하위 클래스는 상위클래스로 묵시적 형 변환이 됨. 하지만, 그 역은 성립하지 않는다.

- `Customer vc = new VIPCustomer()`
- 선언된 클래스형(상위 클래스형) - 생성된 인스턴스의 클래스형(하위 클래스형)

> 위의 Customer vc에서 vc가 가리키는 것은?

힙 메모리에는 VIPCustomer() 생성자의 호출로 인스턴스들은 모두 생성되었지만, 타입이 Customer이므로 접근할 수 있는 변수는 Customer의 변수와 메서드만 가능하다.


## 인터페이스 선언과 구현

```java
public interface Clac{
    double PI = 3.14
    int ERROR = -99999999;

    int add(int num1, int num2);
    int substract(int num1, int num2);
    int multiply(int num1, int num2);
    int divide(int num1, int num2);
}
```

> 인터페이스애서 선언한 변수는 컴파일 과정에서 상수로 변환된다(static final)

> 마찬가지로 인터페이스에서 선언한 메서드는 컴파일 과정에서 추상 메서드로 변환된다. 

```java
public abstract class Calulator implements Calc{
    @Override
    public int add(int num1, int num2){
        return num1 + num2;
    }

    @Override
    public int substract(int num1, int num2){
        return num1 - num2;
    }
}
```

> 이렇게 Calc 인터페이스의 모든 메서드를 구현하지 않는다면 추상 클래스가 되는 것이고.


```java
public class CompleteCalc extends Calculator{
    @Override
    public int multiply(int num1, int num2){
        return num1 * num2;
    }

    @Override
    public int divide(int num1, int num2{
        return num1 / num2; 
    })

    public void showInfor(){
        System.out.println("모두 구현하였습니다.");
    }
}
```

> 이렇게 상속받아서 모든 클래스를 구현하면 구체적인 클래스가(Concrete class)가 되는 것. 


`Calc calc = new CompleteCalc()`로 선언해서 사용도 가능하지만, 실제로 사용한 메서드는 Calc 인터페이스에서 구현된 메서드 뿐인 것이다.

> add, subtract, multiply, divide 모두 사용 가능하지만, showInfo라는 CmopleteCalc에서 구현된 메서드는 사용할 수 없다는 것.





**인터페이스를 구현한 클래스는 인터페이스 타입으로 변수를 선언하여 인스턴스를 생성할 수 있음**

인터페이스는 구현 코드가 없기 때문에 타입 상속이라고도 함!



## 인터페이스를 활용한 다형성 구현

### 인터페이스의 역할은?

인터페이스는 클라이언트 프로그램에 어떤 메서드를 제공하는지 알려주는 명세(Specification) 또는 약속

한 객체가 어떤 인터페이스의 타입이라 함은 그 인터페이스의 메서드를 구현했다는 의미

클라이언트 프로그램은 실제 구현내용을 몰라도 인터페이스의 정의만 알면 그 객체를 사용할 수 있음

인터페이스를 구현해 놓은 다양한 객체를 사용함 - 다형성 : 
> JDBC를 구현한 오라클, MSSQL 라이브러리 등

오라클이나, MSSQL의 라이브러리를 사용하기 위해서 우리는 그들이 JDBC(Java Database Connection)을 구현하기 위해서 가져다가 쓴 interface를 참고하여서 이렇게 구현했겠구나를 참고하고 확인하고 사용할 수 있다. 


### 인터페이스 활용


인터페이스를 활용하면 다양한 정책이나 알고리즘을 프로그램의 큰 수정 없이 적용, 확장할 수 있다.

> 예를 들어, Sorting이라는 인터페이스를 만들어 놓고

>> 그 아래에 Bubble sort, Quick sort, Merge sort 등 인터페이스를 구현한 클래스들을 만들어서 활용할 수 있다. 다른 방식의 sort를 사용하고 싶다면 구현한 메서드의 내용만 조금 수정해서 사용하면 되는 것


## 인터페이스의 요소들

- 상수 : 선언된 모든 변수는 상수로 처리 됨
- 메서드 : 모든 메서드는 추상 메서드
- 디폴트 메서드 : 기본 구현을 가지는 메서드
  - 구현하는 클래스에서 재정의 할 수 있음(java 8)
- 정적 메서드 : 인스턴스 생성과 상관없이 인터페이스 타입으로 호출하는 메서드(java 8)
- private 메서드 : 인터페이스 내에서 사용하기 위해 구현한 메서드
  - 구현하는 클래스에서 재정의 할 수 없음(java 9)


### 여러 개의 인터페이스 구현하기

인터페이스는 구현 코드가 없으므로 하나의 클래스가 여러 인터페이스를 구현할 수 있음

**디폴트 메서드의 이름이 중복 되는 경우에는 재정의 함**

`Customer(실제 구현 클래스) <- Buy(인터페이스) +  Sell(인터페이스)` 


```java
public class Main {

    public static void main(String[] args) {

        MyClass mc = new MyClass("JinKwan");

        mc.getName();
        mc.printName();
    }
}

interface MyInterface{

    default void getName(){
        System.out.println("JJK");
    }
}

class MyClass implements MyInterface{


    // 아래와 같이 Override해서 사용해도 되고 그대로 사용해도 된다.
//    @Override
//    public void getName() {
//
//    }

    private String name;

    MyClass(String name){
        this.name = name;
    }

    void printName(){
        System.out.println(this.name);
    }
}

```

위와 같이 default 인터페이스를 상속-구현함으로써 MyObject 타입의 객체가 getName을 사용할 수 있게 되었다. 

 

```java

public class Customer implements Buy, Sell{

    @Override
    public void order(){
        // 재정의 혹은 어떤 인터페이스의 것을 사용할지 정의할 수 있다.
        // Buy.super.order();
    }
}
```

만약에 Buy, Sell 인터페이스에서 둘다 order라는 default 메서드들이 있었다면, 이름이 중복되므로 재정의를 해주거나 어떤 인터페이스에서 사용할지 직접 정의를 해서 사용해야 한다. 


### 인터페이스 상속

인터페이스 간에도 상속이 가능함

구현이 없으므로 extends 뒤에 여러 인터페이스를 상속받을 수 있음
> 구현 내용이 없으므로 타입 상속(type inheritance)라고 함

### 인터페이스 구현과 클래스 상속 함께 사용하기


```java

public class BookShelf extends Shelf implements Queue{
    @Override
    public void enQueue(String title){
        shelf.add(title);
    }

    @Override
    public String deQueue(){
        return shelf.remove(0);
    }

    @Override
    public int getSize(){
        return getCount();
    }
}
```


### 인터페이스를 왜 사용하는가?

인터페이스를 이용하여 클래스를 구현하면 다른 클래스와 대체가 유연해서 유지보수가 편해진다는 장점이 있다. 마치 규격만 맞으면 다른 부품으로 바꿀 수 있는 것처럼 쉽게 변경할 수 있기 때문.

디자인의 측면에서, Client 입장에서는 자신이 사용하는 구체적인 클래스를 몰라도, 인터페이스에 정의된 메서드를 사용하는 객체라는 것이 보장되어 있기 때문에 구체적인 클레스의 변경이 일어나더라도 Client의 코드 수정은 불필요하게 된다.

> 클래스간의 결합도를 줄임으로써 얻는 효과고 유지보수성의 향상이라는 이득을 취할 수 있다.

> 결합도가 높은 클래스의 문제점
> - 연관된 다른 클래스가 변경되면 같이 변경해야 한다.
> - 수정하려는 클래스를 이해하기 위해서 연관된 다른 클래스를 같이 이해해야 한다.
> - 다른 프로그램에서 클래스를 재사용하기도 힘들다
> - **결론적으로 독립적으로 프로그래밍하기가 힘들어 진다.**


