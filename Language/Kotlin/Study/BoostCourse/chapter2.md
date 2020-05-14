
# Chapter 2. 변수와 자료형, 연산자

## 2-1 기본 자료형과 변수 선언방법 (1) 불변형, 기본형

**자료형**
- Int : 정수 -- 1, 2, 3
- String : 문자열 -- "Hello"
- Float : 실수 -- 1.2 
- ...

**변수**
- val (value) - 불변형 (immutable)
- var (variable) - 가변형 (mutable)

선언 키워드, 변수 이름, 자료형, 값👇

`val username: String = "Kildong"`


**변수 선언 예**
- `val username = "Kildong"`  -- 자료형을 추론하여 String으로 결정
- `val username`  -- 자료형을 지정하지 않은 변수는 사용할 수 없다. 
- `val init: Int` -- 사용전 혹은 생성자 시점에서 init 변수를 초기화 해야함
- `val number = 10` -- number 변수는 Int형으로 추론

**변수 이름 규칙**
- 변수 이름은 123abc같이 숫자로 시작하면 안된다.
- 변수 이름에는 while, if 같이 예약어를 사용하면 안된다.
- 변수 이름은 의미 있는 단어를 사용해서 만드는 게 좋다.
- 여러 단어를 사용하여 변수 이름을 지을 경우 카멜 표기법(낙타 등)을 사용한다.
    - CamelCase, numberOfBooks


**자료형 알아보기**
1. 기본형(Primitive data type)
    - 가공되지 않은 순수한 자료형으로 프로그래밍 언어에 내장
    - 데이터를 다룰 때 객체에 쌓아서가 아니라, 직접 입력할 수 있는 것
    - 성능으로 보자면, 기본형으로 직접 다루는 것이 좋다. 
    - int, long, float, double 등
2. 참조형(Reference type)
    - 동적 공간에 데이터를 둔 다음 이것을 참조하는 자료형
    - 코틀린에서는 코딩할 때는 참조형만 사용하며 이것은 다시 코틀린의 성능 최적화에 따라 JVM에 실행하기 위해 코틀린 컴파일러에서 기본형으로 대체된다.
    - Int, Long, Float, Double 등 



## 2-1 기본 자료형과 변수 선언방법 (2) 정수형과 실수형

![](https://mblogthumb-phinf.pstatic.net/20110405_277/satyee_1301935253810WAMll_JPEG/%C0%DA%B9%D9_%B1%E2%C3%CA_005_02.jpg?type=w2)

**자료형 생략**

`val num05 = 127` -- Int형으로 추론

`val num06 = -32768` -- Int형으로 추론

`val num07 = 2147483647` -- Int형으로 추론

`val num08 = 92222212312321` -- Long형으로 추론 

**접미사 접두사 사용**

`val exp01 = 123` -- Int형으로 추론

`val exp02 = 123L` -- 접미사 L을 사용해 Long형으로 추론

`val exp03 = 0x0F` -- 접두사 0x를 사용해 16진 표기가 사용된 Int형으로 추론

`val exp04 = 0b00001011` -- 접두사 0b를 사용해 2진 표기가 사용된 Int형으로 추론

**작은 값의 사용**

`val exp08: Byte = 127` -- 명시적으로 자료형을 지정(Byte)

`val exp09 = 32767` -- 명시적으로 자료형을 지정하지 않으면 Short형 범위의 값도 Int형으로 추론

`val exp10: Short = 32767` -- 명시적으로 자료형을 지정(Short)

**부호 없는 정수 자료형**

`val uint: UInt = 153u`

`val ushort: UShort = 65535u`

`val ulong: ULong = 46322342uL`

`val ubyte: UByte = 255u` 

**큰 수 읽기 쉽게 하기**

`val val1 = 1_000_000_000`

**실수 자료형**

`val exp01 = 3.14` -- Double형으로 추론(기본)

`val exp02 = 3.14F` -- 식별자 F에 의해 Float형으로 추론

**공간 제약에 따른 부동 소수점 연산의 단점**
```kotlin
fun main() {
    var num :Double = 0.1

    for(x in 0..999){
        num += 0.1
    }

    println(num) //100.09999999999859
}
```



## 2-1 기본 자료형과 변수 선언방법 (3) 크기 범위와 기타 자료형

> 팁 : Alt + Shift + 클릭이면 여러개를 클릭할 수 있다...

**2의 보수**

음수는 2의 보수 표현을 사용해 연산됨
- 절댓값의 이진수에 값을 뒤집고 1을 더함 -- 모든 자리가 더해서 2가 되는 값을 만드는 것.

**논리 자료형**

`val isOpen = true` -- isOpen은 Boolean으로 추론
`val isUploaded: Boolean` -- 선언만 한 경우 자료형을 반드시 명시

**문자 자료형**
`val ch = 'c'` -- ch는 Char로 추론
`val ch2: Char`  
`var str1: String = "Hello`
- var로 선언된 str1의 참조 주소는 가변형으로 바뀔 수 있다.(다른 것 지정 가능)
- 하지만 선언되 생성된 메모리 공간의 Hello는 변경되지 않는다.(변경 불가능)

`var str2 = "World"`

`== 는 값만 비교 가능, === 은 값과 참조까지 비교 가능` - 자바랑은 다른점.

```kotlin
var str1: String = "Hello"
var str2 = "World"
var str3 = "Hello"
println("str1 === str2 ${str1 === str2}") // false
println("str1 === str3 ${str1 === str3}") // true 
```



**표현식과 $기호를 사용하여 문자열 출력하기**

```kotlin
var a = 1
var str4 = "a = $a"
var str5 = "a = ${a + 2}" // 문자열에 표현식 사용

println("str4: \"$str4\", str5: \"$str5\"") // str4: "a = 1", str5: "a = 3"
```
## 2-2 나를 괴롭히는 널(Null)!

**코틀린의 변수 선언은 기본적으로 null을 허용하지 않는다.**

`val a: Int = 30`

`var b: String = "Hello"`

**null 가능한 선언**

`val a: Int? = null`

`var b: String? = null`

**NPE(NullPointerExeption)**
- 사용할 수 없는 null인 변수에 접근하면서 발생하는 예외
- Kotlin에서는 기본적으로 NotNull이고 Nullable 표현에만 '?'가 사용된다.

```kotlin
var str1: String?
str1 = null
//Only safe (?.) or non-null asserted (!!.) calls are allowed on a nullable receiver of type String?

val len = if(str1 != null)str1.length else -1
//val len = str1?.length ?: -1 // elvis expression으로 변환이 된 것 

println("str1: $str1, length: ${str1?.length}")
println("str1: $str1, length: $len")
// ?. --> str1 이 혹시라도 null이면 뒤에것을 실행하지 않는다. 세이프 콜이라고 부른다.
// !! --> null일리 없다고, 그대로 실행시키는 것. 위험한 코드. -- kotlin.KotlinNullPointerException
```

```kotlin
fun set(a: String, b: String?) // a는 null이 안되지만 b는 null값을 허용한다. 
```

**세이프 콜(Safe-call)**

- `str1?.length`

**non-null 단정 기호**

- `str1!!.length` -- NPE 날 가능성이 있다

**더 안전하게 사용하는 방법**
- `str1?.length ?: -1` -- str1.length를 반환하거나, null값이면 -1을 반환. 

## 2-3 검사와 자료형을 변환해보기

**자료형 비교, 검사, 변환**

**코틀린의 자료형 변환**

- 기본형을 사요하지 않고 참조형만 사용
- 서로 다른 자료형은 변환 과정을 거친 후 비교

`val a: Int = 1` -- 정수형 변수 a를 선언하고 1을 할당
`val b: Double = a` -- 자료형 불일치 오류 발생

- 변환 메서드 이용

`val b: Double = a.toDouble()` -- 변환 메서드 사용

- 표현식에서 자료형의 자동 변환

`val result = 1L + 3` -- Long + Int -> 큰 자료형 Long

**변환 메서드의 종류**
- toByte, toLong, toShort, toFloat... 등

**기본형과 참조형 자료형의 비교 원리**
- == 값만 비교하는 경우
- === 값과 참조 주소를 비교할 때 (자바의 == )

**참조 주소가 달라지는 경우

```kotlin
val a: Int = 128
val b: Int = 128
println(a == b) // true
println(a === b) // true

val a: Int = 128 // 기본형
val b: Int? = 128 // 객체 - 동적으로 
println(a == b) // true
println(a === b) // false 

```

기본형 자료형은 값이 그대로 stack에 저장이 되지만, 참조형은(ex- Int?) 힙에 적힌 객체의 주소를 stack에 저장하게 된다.(객체의 값은 힙에- 동적공간)

> 참고 : 코틀린에서는 참조형으로 선언한 변수의 값이 -128~127 (1byte) 범위에 있으면 캐시에 그 값을 저장함. 

**구체적으로 명시되지 않은 자료형을 자동 변환**
- 값에 따라 자료형을 결정
- Number형은 숫자를 저장하기 위한 특수한 자료형으로 스마트 캐스트됨
    - Number -> Int, Long 등으로 가능.
```kotlin
fun main() {

    var test: Number = 12.2 // Float형으로 스마트 캐스트
    println("$test")

    test = 12
    println("$test")

    test = 120L
    println("$test")

    test += 12.0f
    println("$test")

    // 다만 String형 과 같은 문자열, 다른 형식으로 캐스팅은 안됨. 
}
```

**is 키워드를 사용한 검사**

`if(num is Int)` -- num이 Int형인지 검사. 
`if(num !is Int)` -- num이 Int형이 아닌지 검사. 

**Any**
- 자료형이 정해지지 않은 경우
- 모든 클래스의 뿌리 - Int나 String은 Any형의 자식 클래스이다.
- Any는 언제든 필요한 자료형으로 자동 변환 (스마트 캐스트)
- 함수의 매개변수 또한 Any로 받을 수 있다. 
    - 함수 안에서 각 변수의 형식에 따라서 처리를 해주도록 지시할 수 있다. 

`println("a: $a type: ${a.javaClass}")` -- a의 자바 기본형을 출력한다. 

## 2-4 연산자를 조합해 다양한 식 만들기 (1) 기본연산자

**기본 연산자**
- 산술, 대입, 증가, 감소, 비교, 논리 연산자 등


## 2-4 연산자를 조합해 다양한 식 만들기 (2) 비트연산자

**비트와 비트 연산 이해하기**
- 1010(2) = 2^1 + 2^3 = 10(10)
- 가장 왼쪽에 있는 비트는 양(+), 음(-)을 판단하는 데 사용

|표현식|설명|
|:---|:---:|
|4.shl(bits)|4를 표현하는 비트를 bits만큼 왼쪽으로 이동(부호 있음)|
|7.shr(bits)|7을 표현하는 비트를 bits만큼 오른쪽으로 이동(부호 있음)|
|12.ushr(bits)|12를 표현하는 비트를 bits만큼 오른쪽 이동(부호 없음)|
|9.and(bits)|9를 표현하는 비트와 bits를 표현하는 비트로 논리곱 연산|
|4.or(bits)|4를 표현하는 비트와 bits를 표현하는 비트로 논리합 연산|
|24.xor(bits)|24를 표현하는 비트와 bits를 표현하는 비트의 배타적 연산|
|78.inv()|78을 표현하는 비트를 모두 뒤집음|


아래와 같은 식으로 중위 표현식도 가능 

`println(0x0F and 0xF0)` 

`println(0x0F or 0xF0) `

`println(0x1 shl 4)`

