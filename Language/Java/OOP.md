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


## Object 클래스

모든 클래스의 최상위 클래스

java.lang.Object 클래스

모든 클래스는 Object 클래스에서 상속 받음
모든 클래스는 Object 클래스에의 메서드를 사용할 수 있음
모든 클래스는 Object 클래스의 일부 메서드를 재정의 하여 사용할 수 있음. 

### equals() 메서드

두 객체의 동일함을 논리적으로 재정의 할 수 있음

> 물리적 동일함 : 같은 주소를 가지는 객체

> 논리적 동일함 : 같은 학번의 학생, 같은 주문 번호의 주문

물리적으로 다른 메모리에 위치한 객체라도 논리적으로 동일함을 구현하기 위해 사용하는 메서드

```java
String str1 = new String("ABC");
String str2 = new String("ABC");

System.out.println(str1 == str2); 
```

이것은 str1 과 str2가 같은 주소를 나타내는지를 물어보는 방식이다. 당연히 결과는 false가 나온다.

```java
System.out.println(str1.equals(str2));
```

위의 출력은 str1과 str2가 논리적으로 동일한지를 물어보는 것. 결과는 true
> String 클래스에서 equals 메서드를 구현해놓은 것을 사용한다.



### hashCode() 메서드

hashCode() 메서드의 반환 값 : 인스턴스가 저장된 가상머신의 주소를 10진수로 반환

두 개의 서로 다른 메모리에 위치한 인스턴스가 동일하다는 것은?
> 논리적으로 동일 : equals() 의 반환 값이 true

> 객체 해시코드란 객체를 실별할 하나의 정수값을 말한다. Object의 hashCode() 메소드는 객체의 메모리 번지를 이용해서 해시코드를 만들어 리턴하기 때문에 객체 마다 다른 값을 가지고 있다.

>> 만약에 hashCode()를 오버라이딩해서 구현하게 된다면, 메모리와 같이 그 객체를 구별할 수 있는 키로 등록을 해야하는 것


[hashCode()와 equals()의 차이점과 필요성](https://nesoy.github.io/articles/2018-06/Java-equals-hashcode)

**그럼 hashCode()와 equals()랑은 어떻게 쓰이는건가?**

equals는 두 객체가 논리적으로 같은지 비교하기 위해서 구현한다. 

hashCode() 또한 두 객체가 논리적으로 동일하다면 같은 hashCode를 반환하도록 구현해야하지만, 해쉬코드는 하나의 식별키로 사용되는 것이다.

대표적으로 쓰이는 것은 다음 아래와 같다. 

> 컬렉션 프레임워크에서 HashSet, HashMap, HashTable은 다음과 같은 방법으로 두 객체가 동등한지 비교한다.

우선 hashCode() 메소드를 실행해서 리턴된 해시코드 값이 같은지를 본다. 

해시 코드값이 다르면 다른 객체로 판단하고, 해시 코드값이 같으면 equals()메소드로 다시 비교한다. 이두개가 모두 맞아야 동등 객체로 판단한다.

즉, hashCode()를 정의해서 그 값이 맞는지 먼저 확인하고, 아니라면 바로 다른 객체로 인식하는 true or false 문제에서 빠르게 결정을 한 단계 내리는 점이다.

hashCode도 같다면, 그 다음에 equals 메서드의 구현을 통해서 같은 객체인지를 더 자세히 확인하는 것. 

### clone() 메서드

객체의 복사본을 만듦

기본 틀(prototype)으로 부터 같은 속성 값을 가진 객체의 복사본을 생성할 수 있음

**객체지향 프로그래밍의 정보은닉에 위배되는 가능성이 있으므로 복제할 객체는 `clonable` 인터페이스를 명시해야 함.**

> clonable 인터페이스 : 마크 인터페이스로, 사용하기 위해서 명시하는 용도로 사용.

native 코드를 사용해서, 객체의 주소에 있는 값을 그대로 복사한다.



## Class 클래스

자바의 모든 클래스와 인터페이스는 컴파일 후 class 파일로 생성됨

class 파일에는 객체의 정보(멤버변수, 메서드, 생성자 등)가 포함되어 있음

class 클래스는 컴파일된 class 파일에서 객체의 정보를 가져올 수 있음

### Class 클래스 가져오기

1. String s = new String();
    - Class c = s.getClass(); -> Object의 메서드
2. Class c = String.class;

3. Class c = Class.forName("java.lang.String"); -> 동적 로딩
    - 즉, 이 라인이 실행이 될 때, String클래스를 가져오는 것 (제일 많이 사용된다고 함)
    - 컴파일 타임이 아니라, 런타임에 내가 원하는 라이브러리를 매칭시킬 수 있다.
    - 단점 : 오타나 오류 나는 경우 런타임에 죽을 수 있다. 


### reflection 프로그래밍

Class 클래스로부터 객체의 정보를 가져와 프로그램이 하는 방식

로컬에 객체가 없고 자료형을 알 수 없는 경우 유용한 프로그래밍

java.lang.reflect 패키지에 있는 클래스 활용

```java
Class c = Class.forName("java.lang.String");

Constructor[] cons = c.getConstructors();
for(int Constructor con : cons){
    System.out.println(con);
}

Method[] methods = c.getMethods();
for(Method method : methods){
    System.out.println(method);
}
```

위와 같은 식으로 어떤 생성자 있고, 메소드들이 있는지 확인할 때 유용한 듯하다.

(솔직히 최고는, 그냥 그 라이브러리를 다 뜯어보는 게 최고라고 생각함)

### forName() 메서드와 동적 로딩

Class 클래스의 static 메서드

동적 로딩이란 ? 

> 컴파일 시에 데이터 타입이 모두 biding 되어 자료형이 로딩되는 것(static loading)이 아니라 실행 중에 데이터 타입을 알고 binding 되는 방식

실행 시에 로딩되므로 경우에 따라 다른 클래스가 사용될 수 있어 유용함

컴파일 타임에 체크 할 수 없으므로 해당 문자열에 대한 클래스가 없는 경우 예외(ClassNotFoundException)이 발생할 수 있음. 



## String, Wrapper 클래스

### String 클래스 선언하기

```java
String str1 = new String("abc"); // 인스턴스로 생성됨
String str2 = "abc" // 상수풀에 있는 문자열을 가리킴
String str3 = "abc" // 상수풀에 있는 문자열을 가리킴
```

2,3 번째는 상수풀에서 가져오므로, equals로 비교를 했을 때, 메모리가 같아서 true가 반환 될 수 있다.

1번째는 직접 힙에 인스턴스를 생성해서 주소값이 다를 수 있지만, str2와 str3는 같은 상수풀의 메모리를 가리킬 수 있다.

### String은 immutable

한 번 선언되거나 생성된 문자열을 변경할 수 없음

String 클래스의 concat() 메서드 혹은 "+"을 이용하여 String을 연결하는 경우 문자열은 새로 생성이 되는 것

- 계속해서 새로운 메모리에 객체가 만들어지므로, 메모리 낭비가 이루어진다. 

### StringBuilder와 StringBuffer

그러므로 동적으로 사용하기 위해서 위의 클래스들을 사용한다

가변적인 char[] 배열을 멤버변수로 가지고 있는 클래스

문자열을 변경하거나 연결하는 경우 사용하면 편리한 클래스

StringBuffer는 멀티 쓰레드프로그래밍에서 동기화(Synchronization)이 보장됨
> 단일 쓰레드 프로그래밍에서는 StringBuilder를 사용하는것이 더 좋음

toString() 메서드로 String 반환

### Wrapper 클래스

기본 자료형에 대한 클래스

|기본형|Wrapper 클래스|
|------|---|
|boolean|Boolean|
|byte|Byte|
|char|Character|
|short|Short|
|int|Integer|
|long|Long|
|float|Float|
|double|Double|

기본형을 클래스라는 이름으로 감싼 것

## 제네릭 프로그래밍

### 제네릭 프로그래밍이란

변수의 선언이나 메서드의 매개변수를 하나의 참조 자료형이 아닌 여러 자료형을 변환 될 수 있도록 프로그래밍 하나 방식

실제 사용되는 참조 자료형으로의 변환은 **컴파일러가 검증하므로 안정적인 프로그래밍 방식**

### 자료형 매개 변수 T

여러 참조 자료형으로 대체 될 수 있는 부분을 하나의 문자로 표현

type의 의미로 T 사용

```java
public class GenericPrinter<T>{
    private T material;

    public void setMaterial(T material){
        this.material = material;
    }

    public T getMaterial(){
        return material;
    }
}
```

### <T extends 클래스>

T 대신에 사용될 자료형을 제한하기 위해 사용

예를 들어 Car라는 클래스를 상속하는 SuperCar와 NormalCar 클래스가 있다고 할때

class RunningCar<T extends Car> 라고 선언하면 여기서 T에 들어갈 수 있는 것은 Car 클래스를 상속하는 SuperCar나 NormalCar로 제한된다는 것이다.

### 자료형 매개 변수가 두 개 이상일 때

```java
public class Point<T, V>{
    T x;
    V y;

    Point(T x, V y){
        this.x = x;
        this.y = y;
    }

    public T getX(){
        return x;
    }
    public V getY(){
        return y; 
    }
}
```

getX와 getY 같은 것을 제너릭 메서드라고 한다.

### 제너릭 메서드

메서드 내에서의 자료형 매개 변수는 메서드 내에서만 유효 함( 지역 변수와 같은 개념 )

```java
class Shape<T>{
    public static <T, V> double makeRectangle(Point<T,V> p1, Point<T,V> p2){
        ......
    }
}
```

Shape의 T와 makeRectangle의 T는 전혀 다른 의미 -- 지역 변수와 같은 개념이므로

## 컬렉션 프레임워크

### 컬렉션 프레임워크란

프로그램 구현에 필요한 자료구조와 알고리즘을 구현해 놓은 라이브러리

java.util 패키지에 구현되어 있음

개발에 소요되는 시간을 절약하고 최적화된 라이브러리를 사용할 수 있음

Collection 인터페이스와 Map 인터페이스로 구성됨

### Collection 인터페이스

하나의 객체의 관리를 위해 선언된 인터페이스로 필요한 기본 메서드가 선언되어 있음

하위에 List, Set 인터페이스가 있음

List 인터페이스
> 순서가 있는 자료 관리, 중복 허용.

> 이 인터페이스를 구현한 클래스는 ArrayList, Vectior, LinkedList, Stack, Queue 등이 있음

Set 인터페이스
> 순서가 정해져 있지 않음, 중복을 허용하지 않음. 

> 이 인터페이스를 구현한 클래스는 HashSet, TreeSet 등이 있음


### Map 인터페이스

쌍으로 이루어진 객체를 관리하는 데 필요한 여러 메서드가 선언되어 있음

Map을 사용하는 객체는 Key-Value 쌍으로 되어 있고 Key는 중복될 수 없음



## List 인터페이스
 

### ArrayList 와 Vector

객체 배열 클래스

Vector는 자바2부터 제공된 클래스

일반적으로 ArrayList를 더 많이 사용

Vector는 멀티 쓰레드 프로그래밍에서 동기화를 지원

동기화(Synchronization) : 두 개의 쓰레드가 동시에 하나의 리소스에 접근할 떄 순서를 맞추어서 데이터의 오류를 방지하기 위함

Capacity와 Size는 다른 의미이다.

### ArrayList와 LinkedList

둘 다 자료의 순차적 구조를 구현한 클래스

ArrayList는 배열을 구현한 클래스로 논리적 순서와 물리적 순서가 동일 함

LinkedList는 논리적으로 순차적인 구조지만, 물리적으로는 순차적이지 않을 수 있음

LinkedList
> 자료의 추가와 삭제가 빠름


## Set 인터페이스

### Iterator로 순회하기

Collection의 개체를 순회하는 인터페이스

iterator() 메서드 호출

`Iterator ir = memberArrayList.iterator();`

Iterator에 선언된 메서드

> boolean hasNext() : 이후에 요소가 더 있는지를 체크하는 메서드

> E next() : 다음에 있는 요소를 반환한다.

```java
while(ir.hasNext()){
    Member next = ir.next();
}
```

위와 같은 방식으로 Colection 개체를 순회한다.


> set을 사용하기 위해서는 제너릭 클래스에 hashCode와 equals를 오버라이딩 해주어야 한다.

> 아니면, 각 객체가 같은지 다른지, 인식하지 못할 수가 있다.


### Set 인터페이스

중복을 허용하지 않음

List는 순서기반의 인터페이스지만, Set은 순서가 없음

get(i) 메서드가 제공되지 않기 때문에 - Iterator로 순회한다.
- 저장된 순서와 출력순서는 다를 수 있음

아이디, 주민번호, 사번 등 유일한 값이나 객체를 관리할 때 사용

-> 구현 : HashSet, TreeSet 클래스

### TreeSet 클래스

객체의 정렬에 사용되는 클래스

중복을 허용하지 않으면서 오름차순이나 내림차순으로 객체를 정렬함

내부적으로 이진 검색 트리(Binary Search Tree)로 구현되어 있다.

- BST는 자료가 저장될 때 비교하여 저장될 위치를 정한다.
- 객체 비교를 위해서 Comparable이나 Comparator 인터페이스를 구현해야 함.


### Comparable 인터페이스와 Comparator 인터페이스

정렬 대상이 되는 클래스가 구현해야 하는 인터페이스

Comparable은 compareTo()메서드를 구현
- 매개 변수와 객체 자신(this)를 비교

Comparator는 compare()메서드를 구현
- 두 개의 매개 변수를 비교
- TreeSet 생성자에 Comparator가 구현된 객체를 매개변수로 전달
- `TreeSet<Member> treeSet = new TreeSet<Member>(new Member());`

> 일반적으로 Comparable을 더 많이 사용

> 이미 Comparable이 구현된 경우 Comparator를 이용하여 다른 정렬 방식을 정의할 수 있음


## Map 인터페이스

key-value pair의 객체를 관리하는데 필요한 메서드가 정의 됨

key는 중복될 수 없음

검색을 위한 자료 구조

key를 이용하여 값을 저장하거나 검색, 삭제 할 때 사용하면 편리함
- 내부적으로 hash 방식으로 구현된다.

`index = hash(key) // index는 저장 위치`

key가 되는 객체는 객체의 유일성함의 여부를 알기 위해 equals()와 hashCode() 메서드를 재정의 함 - set과 비슷

### HashMap 클래스

Map 인터페이스를 구현한 클래스 중 가장 일반적으로 사용하는 클래스

HashTable 클래스는 자바 2부터 제공된 클래스로 Vector처럼 동기화를 제공 함

pair 자료를 쉽고 빠르게 관리할 수 있음

### TreeMap 클래스

key 객체를 정렬하여 key-value를 pair로 관리하는 클래스

key에 사용되는 클래스에 Comparable, Comparator 인터페이스를 구현

java에 많은 클래스들은 이미 Comparable이 구현되어 있다. --> key로 사용하기 위함


## 내부 클래스

클래스 내부에 구현한 클래스(중첩된 클래스)

클래스 내부에서 사용하기 위해 선언하고 구현하는 클래스

주로 외부 클래스 생성자에서 내부 클래스 생성

|종류|구현 위치|사용할 수 있는 외부 클래스 변수|생성 방법|
|------|:---|:------|:-------|
|인스턴스 내부 클래스|외부 클래스 멤버 변수와 동일|외부 인스턴스 변수, 외부 전역 변수|외부 클래스를 먼저 만든 후 내부 클래스 생성|
|정적 내부 클래스|외부 클래스 멤버 변수와 동일|외부 전역 변수|외부 클래스와 무관하게 생성|
|지역 내부 클래스|메서드 내부에 구현|외부 인스턴스 변수, 외부 전역 변수|메서드를 호출할 때 생성|
|익명 내부 클래스|메서드 내부에 구현, 변수에 대입해서 직접 구현|외부 인스턴스 변수, 외부 전역 변수|메서드를 호출할 때 생성되거나, 인터페이스 타입변수에 대입할 때 new 예약어를 사용하여 생성|

이 중에서 익명 내부클래스를 많이 사용한다고 한다.



```java
class outer{

    int outNum = 100;
    static int sNum = 200;

    Runnable getRunnable(int i){

        // int num = 100; --> 안써도 final : 상수가 되어버린다. 

        class MyRunnable implements Runnable{

            @Override
            public void run(){
                // num += 10;  -- 그래서 run에서 num에 접근할 수 없다. 
                System.out.println(num); //--> 참조는 가능하다.
                System.out.println(outNum);
                System.out.println(Outer.sNum);
            }
        }
    };

    return new MyRunnable();
}
```

getRunnable() 메서드가 끝나고 지역변수인 num은 사라지므로, 접근할 수 없다.

```java
public class Main{

    public static void(String[] args){
        Outer outer = new Outer();
        Runnable runnable = outer.getRunnable(50);

        runnable.run(); // 이렇게 사용은 가능
    }
}
```

지금까지가 익명 내부 클래스였다.

## 람다식

자바에서 함수형 프로그래밍(functional programming)을 구현하는 방식

클래스를 생성하지 않고 함수의 호출만으로 기능을 수행

함수형 인터페이스를 선언함 - 자바 8부터 지원되는 기능

### 람다식 문법

매개 변수 하나인 경우 괄호 생략가능(두 개인 경우는 괄호를 생략할 수 없음)

> str ->{System.out.println(str);}

중괄호 안의 구현부가 한 문장인 경우 중괄호 생략
> str -> System.out.println(str);

중괄호 안의 구현부가 한 문장이라도 return문은 중괄호를 생략할 수 없음
> str -> return str.length(); // 오류

중괄호 안의 구현부가 반환문 하나라면 return과 중괄호를 모두 생략할 수 있음
> (x,y) -> x+y // 두 값을 더하여 반환

> str -> str.length() // 문자열 길이를 반환

```java

public class Main  {
    public static void main(String[] args) throws IOException {
        MyMaxNumber max = (x, y)->(x >= y)? x: y;
        System.out.println(max.getMaxNumber(3, 4));
    }
}

@FunctionalInterface // 람다식을 위한 인터페이스다라는 것을 위미
interface MyMaxNumber{
    int getMaxNumber(int x, int y);
}
```

람다식으로 인터페이스를 사용한 것

그리고 아래는 기존의 방식으로 사용한 것
```java
public class Main implements MyMaxNumber {
    public static void main(String[] args) throws IOException {
        
        System.out.println(getMaxNumber(3, 4));
    }

    @Override
    int getMaxNumber(int x, int y){
        return x >= y ? x: y;
    }
}

@FunctionalInterface // 람다식을 위한 인터페이스다라는 것을 위미
interface MyMaxNumber{
    int getMaxNumber(int x, int y);
}
```


람다식의 해석 --> 결국 자바는 객체지향이기 때문

익명 내부클래스 처럼

```java
StringConcat concat = (s, v) -> System.out.println(s + "," + v);
concat.makeString("hello", "world");
//--------------------------------------//
StringConcat concat2 = new StringConcat(){

    @Override
    public void makeString(String s1, String s2){
        System.out.println(s1 + "," + s2);
    }
}
concat2.makeString("hello", "world");
```

위와 아래의 코드는 동일한 기능을 수행한다. 

### 함수를 변수처럼 사용하는 람다식

프로그램에서 변수는...
- 자료형에 기반하여 선언하고 : int a
- 매개변수로 전달하고 : int add(int x, int y);
- 메서드의 반환 값으로 사용 : return num;

> 람다식은 프로그램내에서 변수처럼 사용할 수 있음

```java
interface PrintString{
    void showString(String str);
}

public class Main{

    public static void main(String[] args){
        PrintString lambdaStr = s->System.out.println(s);
        lambdaStr.showString("Test");

        showMyString(lambdaStr);

        PrintString test = returnString();
        test.showString("Test3");
    }

    public static void showMyString(PrintString p){
        p.showString("Test2");
    }

    public static PrintString returnString(){
        return s->System.out.println(s + "!!!");
    }
}
```

위와 같은 식으로 람다식을 하나의 매개변수, 변수처럼 사용할 수가 있다. 

`(선언, 매개변수 전달, 메서드의 반환 값으로 사용)`

## 스트림

스트림(Stream) - i/o에서 나오는 스트림과 다른 것!

자료의 대상과 관계없이 동일한 연산을 수행할 수 있는 기능(자료의 추상화)

배열, 컬렉션에 동일한 연산이 수행되어 일관성 있는 처리 가능

한번 생성하고 사용한 스트림은 재사용할 수 없음

스트림 연산은 기존 자료를 변경하지 않음

중간 연산과 최종 연산으로 구분 됨

**최종 연산이 수행되어야 모든 연산이 적용되는 지연 연산**

### 스트림 연산 - 중간 연산

중간 연산 - filter(), map()

조건에 맞는 요소를 추출(filter()) 하거나 요소를 변환함(map())

### 스트림 연산 - 최종 연산

스트림의 자료를 소모 하면서 연산을 수행

최종 연산 후에 스트림은 더 이상 다른 연산을 적용할 수 없음

- forEach() : 요소를 하나씩 꺼내 옴
- count() : 요소의 개수
- sum() : 요소의 합 

이 외에도 여러가지 최종 연산이 있다.


```java
int[] arr = {1,2,3,4,5};
int sum = Arrays.stream(arr).sum();
int count = (int)Arrays.stream(arr).count();

System.out.println(sum  + " " + count);

List<String> list = new ArrayList<>();
list.add("Tomas"); list.add("Edward"); list.add("Jack");

Stream<String> stream = list.stream();
stream.sorted().forEach(s->System.out.print(s + " "));
System.out.println();
list.stream().map(s -> s.length()).forEach(n -> System.out.println(n));
```

연산을 위해서 사용했다.

중간과 최종 연산을 람다식을 이용해서 구현했다. 

### reduce() 연산

정의된 연산이 아닌 프로그래머가 직접 지정하는 연산을 적용

최종 연산으로 스트림의 요소를 소모하며 연산 수행

배열의 모든 요소의 합을 구하는 reduce() 연산

`Arrays.stream(arr).reduce(0, (a, b) -> a + b));`
> 0 : 초기값, (a, b) : 전달되는 요소 , a + b : 각 요소가 수행해야 할 기능


스트림에 대한 내용은 크게 세 가지로 나눌 수 있습니다.

1. 생성하기 : 스트림 인스턴스 생성.
2. 가공하기 : 필터링(filtering) 및 맵핑(mapping) 등 원하는 결과를 만들어가는 중간 작업(intermediate operations).
3. 결과 만들기 : 최종적으로 결과를 만들어내는 작업(terminal operations).

> 전체 -> 맵핑 -> 필터링 1 -> 필터링 2 -> 결과 만들기 -> 결과물


스트림에 대한 것은 제대로 공부해서 사용법을 따로 익히도록 하자.

## 예외 처리

컴파일 오류 : 프로그램 코드 작성 중 발생하는 문법적 오류

실행 오류 : 실행 중인 프로그램이 의도하지 않은 동작을 하거나(bug) 프로그램이 중지 되는 오류(runtime error)

자바는 예외 처리를 통하여 프로그램의 비정상 종료를 막고 log를 남길 수 있음

### 오류와 예외 클래스

시스템 오류(error) : 가상 머신에서 발생, 프로그래머가 처리할 수 없음, 동적 메모리를 다 사용한 경우, stack over flow등

예외(Exception) : 프로그램에서 제어할 수 있는 오류. 읽으려는 파일이 없는 경우, 네트웍이나 소켓 연결 오류 등 자바 프로그램에서는 예외에 대한 처리를 수행 함.

### 예외 클래스

Exception
- 입출력 예외처리(IOException)
    - FileNotFoundException
    - SocketException
- 실행 오류 예외 처리(RuntimeException)
    - ArithmeticException
    - IndexOutofBoundsException


### try - catch 문으로 예외 처리하기

```java
try{
    // 예외가 발생 할 수 있는 코드 부분
}catch(처리할 예외 타입 e){
    try 블록 안에서 예외가 발생했을 때 수행되는 부분
}

```


### try - catch - finally 문으로 예외 처리하기

```java
try{
    // 예외가 발생 할 수 있는 코드 부분
}catch(처리할 예외 타입 e){

    try 블록 안에서 예외가 발생했을 때 수행되는 부분

}finally{
    예외 발생 여부와 상관 없이 항상 수행 되는 부분
    리소스를 정리하는 코드를 주로 씀
}
```


## 자바 입출력 스트림

### 입출력 스트림이란?

네트웍에서 자료의 흐름이 물과 같다는 의미에서 유래

다양한 입출력 장치에 독립적으로 일관성 있는 입출력 방식 제공

> I/O스트림 사용 -> 키보드, 파일 디스크, 메모리 등


### 입출력 스트림 구분?

- I/O 다생 기준 : 입력 스트림, 출력 스트림
- 자료의 종류 : 바이트 스트림, 문자 스트림
- 스트림의 기능 : 기반 스트림, 보조 스트림


### 입력 스트림과 출력 스트림

입력 스트림 : 대상으로부터 자료를 읽어들이는 스트림
- FileInputStream 등

출력 스트림 : 대상으로 자료를 출력하는 스트림
- FileOutputStream 등

### 바이트 단위 스트림과 문자 단위 스트림

바이트 단위 스트림 : 바이트 단위로 자료를 읽고 씀(동영상, 음악파일 등)
- FileInputStream

문자 단위 스트림 : 문자는 2바이트씩 처리 해야 함
- FileReader

### 기반 스트림과 보조 스트림

기반 스트림 : 대상에 직접 자료를 읽고 쓰는 기능의 스트림
- FileInputStream

보조 스트림 : 직접 읽고 쓰는 기능은 없고 추가적인 기능을 제공해주는 스트림
- 기반 스트림이나 또 다른 보조 스트림을 생성자의 매개변수로 포함함
- InputStreamReader 등


## 표준 입출력

System 클래스의 표준 입출력 멤버


### System.in 사용하여 입력 받기

한 바이트씩 읽어 들임

한글과 같은 여러 바이트로 된 문자를 읽기 위해서는 `InputStreamReader`와 같은 보조 스트림을 사용해야 함


### Scanner 클래스

java.util 패키지에 있는 입력 클래스

문자 뿐 아니라 정수, 실수 등 다양한 자료형을 읽을 수 있음

생성자가 다양하여 여러 소스로부터 자료를 읽을 수 있음

생성자들
- Scanner(File source) : 파일을 매개변수로 받아 Scanner를 생성합니다.
- Scanner(InputStream source) : 바이트 스트림을 매개변수로 받아 Scanner를 생성합니다.
- Scanner(String source) : String을 매개변수로 받아 Scanner를 생성합니다.

### Console 클래스

System.in을 사용하지 않고 콘솔에서 표준 입출력이 가능

이클립스와는 연동되지 않음


### 바이트 단위 스트림

InputStream : 바이트 단위 입력 스트림 최상위 클래스
OutputStream : 바이트 단위 출력 스트림 최상위 클래스

> 추상 메서드를 포함한 추상 클래스로 하위 클래스가 구현하여 사용

## FileInputStream 과 FileOutputStream 사용하기

파일에 한 바이트씩 자료를 읽고 쓰는데 사용

입력 스트림은 파일이 없는 경우 예외 발생

출력 스트림은 파일이 없는 경우 파일 생성하여 출력

## 문자 단위 입출력 스트림


Reader : 문자 단위로 읽는 최상위 스트림
Writer : 문자 단위로 쓰는 최상위 스트림

추상 메서드를 포함한 추상 클래스로 하위 클래스가 상속받아 구현

바이트 단위로 읽는 것과 다르게 말 그대로 문자단위로 읽게 됨. 

## 보조 스트림

읽고 쓰는 기능은 없지만, 기능을 추가시켜주는 스트림

FilterInputSTream과  FilterOutputStream이 보조스트림의 상위 클래스

생성자의 매개 변수로 또 다른 스트림을 가짐

데코레이터 패턴(Decorator pattern)
> 기반 스트림 + 보조 스트림 + 보조 스트림 

> 바이트 단위 파일 입력 스트림 + 문자로 변환 기능 추가 + 버퍼링 기능 추가 

### 여러가지 보조 스트림 사용하기

Buffered  스트림 : 내부에 8192 바이트 배열을 가지고 있음 - 읽거나 쓸 때 속도가 빠름

DataInputSteram / DataOutputStream : 자료가 저장된 상태 그대로 자료형을 유지하며 읽거나 쓰는 기능을 제공하는 스트림


## 직렬화(Serialization)

인스턴스의 상태를 그대로 저장하거나 네트워크로 전송하고 이를 다시 복원(Desrialization)하는 방식

ObjectInputStreasm과 ObjectOutputStream을 사용


### Seiralizable 인터페이스

직렬화는 인스턴스의 내용이 외부(파일, 네트웤)로 유출되는 것이므로 프로그래머가 객체의 직렬화 가능 여부를 명시함

> 구현 코드가 없는 Mark 인터페이스


```java
Class Person implements Serializable{
    String name;
    transient String job; // 직렬화 하지 마라는 키워드

    public Person(String name, String job){
        this.name = name;
        this.job = job;
    }

    public String toString(){
        return name + "," + job;
    }
}

public class Main{
    public static void main(String[] args){

        Person one = new Person("Avatar", "Student");
        Person two = new Person("Navi", "Professor");

        try(FileOutputStream fos = new FileOutputStream("serial.dat");
            ObjectOutputStream oos = new ObjectOutputStream(fos)){

            oos.writeObject(one);
            oos.writeObject(two);
        }catch(IOException e){}

        try(FileInputStream fis = new FileInputStream("serial.dat");
            ObjectInputStream ois = new ObjectInputStream(fis)){

            Person p1 = (Person)ois.readObject();
            Person p2 = (Person)ois.readObject();

            System.out.println(p1);
            System.out.println(p2);
        }catch(IOException e){}

    }
}

```

transient 키워드를 통해서 name은 직렬화되어 출력될 수 있지만, job을 출력하려고하면 null값이 나오게 된다.


Externalizable 인터페이스 

--> Serializable 인터페이스와는 다르게 구현할 메서드가 있다. 

> 직접 오브젝트를 Input하고 Output하는 메서드를 구현해야한다.

