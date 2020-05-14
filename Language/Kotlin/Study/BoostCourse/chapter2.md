
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

## 2-4 연산자를 조합해 다양한 식 만들기 (1) 기본연산자

## 2-4 연산자를 조합해 다양한 식 만들기 (2) 비트연산자
