# 안드로이드 Essential - Kotlin

## 01. 커리큘럼 소개, 지치지 않고, 완강을 위한 빅픽쳐

[강사님 깃헙 주소](https://github.com/changja88/)




## 07. 메소드 A

```kotlin
fun plus(first: Int, second: Int): Int {
    val result: Int = first + second

    return result
}

fun main() {

    // 함수를 호출하는 방법 
    val result = plus(5, 10)
    println(result)

    // 인자를 명시적으로 전달하는 방법
    val result2 = plus(first = 20, second = 30)
    val result3 = plus(second = 100, first = 10)

    println(result2)
    println(result3)
}

```

## 08. 메소드 B

```kotlin
fun plus(first: Int, second: Int): Int {
    val result: Int = first + second

    return result
}

// - 디폴트 값을 갖는 함수 만들기
fun plusFive(first: Int, second: Int = 5): Int {
    val result: Int = first + second
    return result
}


// - 반환값이 없는 함수 만들기 -- Unit -아무것도 리턴하지 않아도 괜찮다.
fun printPlus(first: Int, second: Int): Unit {
    val result: Int = first + second
    println(result)
}

fun printPlus2(first: Int, second: Int) {
    val result: Int = first + second
    println(result)
}

// - 간단하게 함수를 만드는 방법
// - plus 함수와 동일한 결과를 만들어 낸다.
// - 간단하게 내용이 적더라도 위의 형식에 따라서 하는 것을 선호할 수 있다.
fun plusShort(first: Int, second: Int) = first + second

// - 가변인자를 갖는 함수 선언하는 방법
// - 1개부터 n개까지 인자를 받을 수 있다.
fun plusMany(vararg numbers: Int): Int{
    var sum: Int = 0
    for(number in numbers){
        sum += number
    }
    return sum
}

fun main() {

    // 디폴트 값을 갖는 함수 호출하기
    val result4 = plusFive(10, 20)
    println("result4 : $result4")
    val result5 = plusFive(10)
    println("result5 : $result5")

    printPlus(10, 20)
    println("result of plusShort : ${plusShort(10, 20)}")
    println("result of plusMany : ${plusMany(10,20,30,40,50,60)}")
}
```


## 09. 메소드 - 실습


```kotlin
fun main() {
    println("result of plusThree : ${plusThree(10, 20, 30)}")
    println("result of minusThree : ${minusThree(10, 20, 30)}")
    println("result of multiplyThree : ${multiplyThree(10,20,30)}")
    println("result of default multiplyThree : ${multiplyThree()}")
    println("result of showMyPlus : ${showMyPlus(10, 20)}")
}

fun plusThree(first: Int, second: Int, third: Int): Int{
    val result: Int = first+second+third
    return result
}

fun minusThree(first: Int, second: Int, third: Int): Int = first - second - third

fun multiplyThree(first: Int = 1, second: Int = 1, third: Int = 1): Int{
    return first*second*third
}

// 내부 함수
// - 함수 안에 있는 함수
// - 간혹 쓸일이 있지만, 자주 사용하지는 않는 기능
fun showMyPlus(first: Int, second: Int): Int{
    println(first)
    println(second)

//    return first + second
    fun plus(first: Int, second: Int):Int{
        return first + second
    }
    return plus(first, second)

}
```


## 10. 연산자

## 11. 연산자  - 실습
## 12. 제어흐름 A

```kotlin
fun main() {

    // 흐름을 제어하는 뿐만 아니라
    // 값을 리턴하는 if 사용 방법
    val a: Int = 5
    val b: Int = 10
    val max = if(a > b){
        a
    }else{// 이렇게 else를 꼭 적는 것이 좋다, 안 그러면 예외를 통해서 max값이 입력되지 않을 수도 있기 때문.
        b
    }

    println(max)
}
```

## 13. 제어흐름 A - 실습

```kotlin
// 엘비스 연산자 - null safe하게 만드는 것 
val number:Int? = null
val number2 = number ?: 10 // 널이면 10을 넣는 것
```
## 14. 제어흐름 B

```kotlin
fun main(args : Array<String>){

    val value: Int = 3

    when(value){
        1 ->{
            println("value is 1")
        }2 ->{
            println("value is 2")
        }3 ->{
            println("value is 3")
        }else ->{
            println("I do not know a value")
        }
    }

}
```


## 15. 제어흐름 B - 실습

```kotlin
fun main(args : Array<String>){

    val value: Int? = null

    when(value){
        null -> println("value is null")
        else -> println("value is not null")
    }
    
    val value2: Boolean? : null
    
    //  when 구문은 조건으로 갖는 값의 모든 경우에 대응 해주는 것이 좋다. 
    when(value2){
        true -> println("is true")
        false -> println("is false")
        null -> println("is null") // 널 값을 꼭 넣어줘야 한다. 
    }

    // 값을 리턴하는 when 구문의 경우 반드시 값을 리턴해야 한다. 
    val value3 = when(value2){
        true -> 1
        false -> 2
        null -> 3
    }

    // when의 다양한 조건식(1)
    val value4: Int = 10
    when(valu4){
        // when에 조건을 적는 곳에는, true-false 연산, else 들이 올 수 있다. 
        is Int -> println("value4 is Int")
        else -> println("value4 is not Int")
    }
    // when의 다양한 조건식(2)
    val value5: Int = 87
    when(value5){
        in 60 .. 70 -> println("60<= value5 <=70")
        in 70 .. 80 -> println("70<= value5 <=80")
        in 80 .. 90 -> println("80<= value5 <=90")
        in 90 .. 100 -> println("90<= value5 <=100")
    }
    // when을 잘쓰면 if문보다 보기 쉬운 코드를 작성할 수 있다.  


}
```
## 16. 배열

```kotlin
// 배열이 필요한 이유
// - 그룹(모음집)이 필요할 때

fun main() {

    // 배열을 생성하는 방법(1)
    var number: Int = 10
    var group1 = arrayOf<Int>(1,2,3,4,5)
    println(group1 is Array)

    // 배열을 생성하는 방법(2)
    // 타입을 선언해주지 않으면, 여러가지 값이 들어가는 배열을 만들 수 있다 -- 추천하지 않음.
    var group2 = arrayOf(1,2, 3.5, "Hello")

    // 배열의 값을 꺼내는 방법(1)
    println(group1.get(0))

    // 배열의 값을 꺼내는 방법(2)
    println(group1[0])

    // 배열의 값을 바꾸는 방법(1)
    group1.set(0, 100)

    // 배열의 값을 바꾸는 방법(2)
    group1[0] = 200
}
```


## 17. 배열 실습



## 18. Collection
## 19. Collection - 실습
## 20. 반복문 - 1
## 21. 반복문 - 2
## 22. 반복문 - 3
## 23. 중간과제 - 설명
## 24. 중간과제 - 풀이
## 25. 클래스 - 1
## 26. 클래스 - 2
## 27. 클래스 - 3
## 28. 클래스 - 4
## 29. 클래스 - 5
## 30. 중간과제 2 - 설명
## 31. 중간과제 2 풀이 - 1
## 32. 중간과제 2 풀이 - 2
## 33. 중간과제 2 풀이 - 3
## 34. 중간과제 2 풀이 - 4
## 35. 전역, 지역 변수
## 36. 접근 제어자
## 37. 접근 제어자 - 실습
## 38. 상속 개념
## 40. 상속 과제 풀이
## 41. 인터페이스 - 1
## 42. 인퍼페이스 - 2
## 43. 제너릭
## 44. Java를 알아보자





