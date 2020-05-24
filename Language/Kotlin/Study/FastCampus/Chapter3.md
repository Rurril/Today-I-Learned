# 안드로이드 Essential - Kotlin

## 목차 
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
```kotlin
fun main() {

    // List
    //Immutable collection -- 한 번 만들면 바꿀 수 없다.
    // -> 중복을 허용한다.
    val numberList = listOf<Int>(1,2,3)
    println(numberList)

    // Set
    // -> 중복을 허용하지 않는다.
    // -> 순서가 없다!
    val numberSet = setOf<Int>(1,2,3,3,3) // set은 중복을 허용하지 않는다.
    numberSet.forEach {
        print(it)
    }
    println()


    val numberMap = mapOf<String, Int>("one" to 1, "two" to 2)
    println(numberMap)
    for(key in numberMap.keys){
        print("${numberMap.get(key)} ")
    }
    println()


    // Mutable collection (변경가능)
    val mNumberList = mutableListOf<Int>(1,2,3)
    mNumberList.add(3, 4)
    println("mNumberList : $mNumberList")

    val mNumberSet = mutableSetOf<Int>(1,2,3,4,5,4,4)
    mNumberSet.add(10)
    println("mNumberSet : $mNumberSet")

    val mNumberMap = mutableMapOf<String, Int>("one" to 1)
    mNumberMap.put("two", 2)

    println("mNumberMap : $mNumberMap")
}
```

## 19. Collection - 실습

## 20. 반복문 - 1
```kotlin
fun main() {

    // 하나 씩 반복해서 할 수 있는 것을 iterable하다 라고 할 수 있다.
    val a = mutableListOf<Int>(1,2,3,4,5,6,7,8,9)

    // 반복하는 방법 (1)
    for(item in a){ // a의 값이 하나하나 item에 들어가게 된다.
        println(item)
    }

    // 반복하는 방법 (2)
    for((index, item) in a.withIndex()){
        println("index : $index, value : $item")
    }
    
}
```


## 21. 반복문 - 2

```kotlin
    // 반복하는 방법 (3)
    a.forEach{ item->
        // 람다라는 문법이랍니다. 다른 것과는 다르게 forEach 구문이 it으로 정해버린다.
        println(item)
    }

    // 반복하는 방법 (4)
    a.forEach{ item->
        // it이 싫을 때는 item -> 이런 식으로 하면 된다.
        println(item)
    }

    // 반복하는 방법 (5) - 강사님 기준 제일 깔끔
    a.forEachIndexed { index, item ->
        println("index : $index, value : $item")
    }

    // 반복하는 방법 (6)
    for( i in 0 until a.size){
        // until은 마지막을 포함하지 않는다.
        println("${a.get(i)}")
    }

    // 반복하는 방법 (7)
    for( i in 0 until a.size step (2)){
        // 2칸씩 뛰면서 간다.
        println(a.get(i))
    }

    // 반복하는 방법 (8)
    for(i in a.size-1 downTo (0)){
        // a.size-1 (8)부터 0까지 반복한다.
        println(a.get(i))
    }

    // 반복하는 방법 (9)
    for(i in a.size-1 downTo (0) step (2)){
        println(a.get(i))
    }

    // 반복하는 방법 (10)
    for(i in 0..10){
        // 0부터 10까지 간다.
        // ..과 until의 차이점을 알아야 한다.
        println(i)
```


## 22. 반복문 - 3

```kotlin
// 반복하는 방법 (11)
    var b: Int = 0
    var c: Int = 4

    while(b < c){
        b++
        println(b)
    }

    // 반복하는 방법 (12)
    var d: Int = 0
    var e: Int = 4
    do{
        println("Hello")
        d++
    }while(d < e)
```
## 23. 중간과제 - 설명




## 24. 중간과제 - 풀이
```kotlin
fun main() {
    solution4()

}

fun solution1(){

    val list1 = mutableListOf<Int>()
    for(i in 0 until 10){
        list1.add(i)
    }
    val list2 = mutableListOf<Boolean>()
    for(i in 0 until list1.size){
        if(list1.get(i) % 2 == 0)list2.add(true)
        else if(list1.get(i) % 2 == 1)list2.add(false)
    }

}

fun solution2(score: Int):String{

//    if(score >= 80 && score <= 90) return "A"
//    else if(score >= 70) return "B"
//    else if(score >= 70) return "C"
//    else return "F"

    when(score){
        in 90..100 ->{
            return "A"
        }
        in 80..89 -> {
            return "B"
        }
        in 70..79 ->{
            return "C"
        }
        else ->{
            return "F"
        }

    }
}

fun solution3(number: Int): Int{
    return (number/10) + (number % 10)
}

fun solution4(){

    for(i in 1..9){
        for(j in 1..9){
            println("$i * $j = ${i*j}")
        }
    }
}
```

## 25. 클래스 - 1


OOP -> Object Oriented Programming : 객체지향 프로그래밍
객체란 뭘까?
- 이름이 있는 모든 것

절차지향 프로그래밍 문제 해결 방법
- 코드를 위에서부터 아래로 실행을 하면 문제가 해결된다!

객체지향 프로그래밍 문제 해결 방법
- 객체를 만들어서, 객체에게 일을 시켜서 문제를 해결한다.
- 선수, 심판, 경기장, 관중 -> 축구 게임

객체를 만드는 방법
- 설명서가 있어야 합니다.

## 26. 클래스 - 2

```kotlin
fun main() {
    Car("V8 engine", "Big")
    val bigCar = Car("V8 engine", "Big")

    // 우리가 만든 클래스(설명서)는 자료형이 된다.
    val bigCar1 : Car = Car("V8 engine", "Big")

    val superCar: SuperCar = SuperCar("good engine", "big", "white")
}
// 클래스(설명서) 만드는 방법(1)
class Car(var engine: String, var body: String){}

// 클래스(설명서) 만드는 방법(2)

class SuperCar{
    var engine: String
    var body: String
    var door: String

    constructor(engine: String, body: String, door: String){
        this.engine = engine
        this.body = body
        this.door = door

    }
}
```

## 27. 클래스 - 3


```kotlin
// 클래스(설명서) 만드는 방법(3) -> 1번 방법의 확장
class Car1 constructor(engine: String, body: String){ // 생성자 키워드를 써도 되고 생략 가능
    var door: String = ""

    // 생성자
    constructor(engine: String, body: String, door: String): this(engine, body){
        // 필요한 것은 engine, body였고 추가적인 부분을 여기에 넘기도록 하는 것.
        this.door = door
    }
}

// 클래스(설명서) 만드는 방법(4) -> 2번 방법의 확장
class Car2{
    var engine: String = ""
    var body: String = ""
    var door: String = ""

    constructor(engine: String, body: String){
        this.engine = engine
        this.body = body
    }
    
    constructor(engine: String, body: String, door: String){
        this.engine = engine
        this.body = body
        this.door = door
    }

}
```
## 28. 클래스 - 4

```kotlin
fun main() {

    // 인스턴스가 가지고 있는 기능을 사용하는 방법
    val car: RunnableCar = RunnableCar("simple engine", "short body")
    car.ride()
    car.drive()
    car.navi("집")

    // 인스턴스의 맴버 변수에 접근하는 방법
    val car2: Runnable2 = Runnable2("simple engine", "short body")
    car2.engine = "nice engine"
    println(car2.engine)

}

class RunnableCar(engine: String, body: String){

    fun ride(){
        println("탑승 완료했습니다.")
    }
    fun drive(){
        println("달립니다 !")
    }
    fun navi(destination: String){
        println("$destination 으로 목적지가 설정되었습니다.")
    }
}

class Runnable2{
    var engine: String
    var body: String

    constructor(engine: String, body: String){
        this.engine = engine
        this.body = body
    }

    init {// 이 객체를 만들게 되면, 무조건 실행되는 부분
        // 초기 세팅을 할 때 유용하다.
        println("객체가 생성되었습니다.")
    }

    fun ride(){
        println("탑승 완료했습니다.")
    }
    fun drive(){
        println("달립니다 !")
    }
    fun navi(destination: String){
        println("$destination 으로 목적지가 설정되었습니다.")
    }
}
```
## 29. 클래스 - 5

```kotlin
fun main() {
    val test: TestClass = TestClass()
    test.test(1)
    test.test(2,3)

}

//오버로딩 -> 이름이 같지만 받는 파라미터가 다른 함수
class TestClass{
    val a: Int = 10
    val b: Int = 10

    fun test(a: Int){
        println("up")
    }
    fun test(a: Int, b: Int){
        println("down")
    }

}
```

## 30. 중간과제 2 - 설명

1. 사칙 연산을 수행할 수 있는 클래스
2. 이행 계좌 만들기
    - 계좌 생성 기능(이름, 생년월일)
    - 잔고를 확인하는 기능
    - 출금 기능
    - 예금 기능
3. TV 클래스
    - on/off 기능
    - 채널을 돌리는 기능
    - 초기 채널은(S사, M사, K사 3개)

## 31. 중간과제 2 풀이 - 1
## 32. 중간과제 2 풀이 - 2
## 33. 중간과제 2 풀이 - 3
## 34. 중간과제 2 풀이 - 4
## 35. 전역, 지역 변수

```kotlin
package Kotlin

var number: Int = 10

fun main() {
    val test = TestClass("myName")
    test.testFun()
    println(test.name)

}
// 변수의 접근 범위
// 1. 전역 변수
// 2. 지역 변수

class TestClass(var name: String){

    fun testFun(){
        name = "JK"
    }
}
```

## 36. 접근 제어자
```kotlin
package Kotlin

fun main() {

    val testAccess: TestAccess = TestAccess("Amugae")
    // private 키워드 때문에 외부에서 사용할 수 없다.
    // 오직 그 객체 안에서 다른 함수를 통해서만 사용할 수 있도록 만드는 것.
//    testAccess.test()
    println(testAccess.name)
    testAccess.name = "Amugae2"
    println(testAccess.name)

    val reward: Reward = Reward()
    // private로 선언을 함으로써 클래스 외부에서 접근할 수 없고 그 안의 키워드를 통해서만 접근할 수 있도록 만들 수 있다.
//    reward.rewardAmount = 2000
    reward.changeReward(2000)

}

class Reward{
    private var rewardAmount: Int = 1000

    fun changeReward(value: Int){
        this.rewardAmount = value
    }
}

class TestAccess{
    var name:String = "Gil Dong"

    constructor(name: String){
        this.name = name
    }

    private fun test(){
        println("test")
    }

}
```

## 37. 접근 제어자 - 실습
```kotlin
package Kotlin

fun main() {

    val knight = Knight(20, 4)
    val monster = Monster(15, 5)

    knight.attack(monster)
    monster.attack(knight)

//    knight.hp = 100
//    println(knight.hp) // 이런식으로 직접 접근해버리는 해킹이 발생한다고 한다면, 임의로 체력이 증가하는 말도안되는 코드가 나올 수 있다.
    // 그래서 접근제어자를 활용해서 private를 통해서 접근할 수 없도록 한다.

}

class Knight(private var hp: Int, private var power: Int){

    fun attack(monster: Monster){
        monster.defense(power)
    }
    fun defense(damage: Int){
        hp -= damage
        if(hp > 0){
            heal()
            println("Knight's hp is : $hp")
        }
        else println("Knight is dead")
    }
    private fun heal(){
        // 아무때나 사용하는 것이 아니라
        // 공격을 당했을 때 힐을 사용하는 것이므로 이것 또한 defense에 종속되게 된다.
        hp += 3
    }
}

class Monster(private var hp: Int, private var power: Int){

    fun attack(knight: Knight){
        knight.defense(power)
    }
    fun defense(damage: Int){
        hp -= damage
        if(hp > 0)println("Monster's hp is : $hp")
        else println("Monster is dead")
    }
}
```

## 38. 상속 개념
```kotlin
package Kotlin

fun main() {

    // 두번까지는 봐준다.
    // 두번 이상이 넘어가면 리펙토링 해라 - (같은 기능을 여러번)

    // 25. 상속
    // 부모로부터 설명서를 물려받는다.
    val supercar: SuperCar1 = SuperCar1("good", "nice")
    // 부모로부터 받은 기능을 사용할 수 있다. 
    supercar.drive()
    supercar.stop()
}
// private가 기본 default 설정이다.
// 그래서 외부에서의 접근(상속)을 위해서 open 키워드를 써준다.
open class Car(engine: String, body: String){
    fun drive(){

    }fun stop(){

    }
}

// 부모 : Car
// 자식 : SuperCar1
class SuperCar1(engine: String, body: String) : Car() { // Car를 상속한다.

}
```
## 39. 상속 실습
```kotlin
open class Car(engine: String, body: String){
    // open을 통해서 오버라이드를 가능하게 한다.
    open fun drive(): String{
        return "Run"
    }
    fun stop(){

    }
}

class SuperCar1(engine: String, body: String) : Car(engine, body) {
    override fun drive(): String { // override 덮어쓰다.
//        super.drive()
        // 부모의 기능을 사용하지 않고 수정해서 사용하는 것 -- 이용해도 가능.
        val run = super.drive()
        return("$run fast")
    }
    //'stop' in 'Car' is final and cannot be overridden
//    override fun stop() {
//        super.stop()
//    }
}
```
## 40. 상속 과제 풀이
## 41. 인터페이스 - 1
```kotlin
// interface가 가지고 있는 것들을 구현해주어야 한다. - 인터페이스는 약속
// 생성자가 없다 -> 인스턴스화 시킬 수 없다. -> 설명서가 아니다.
// 지침서 -> 이것을 구현하고 싶다면, 반드시 아래 기능을 구현해라.

// 상속이(& Interface) 만들어내는 특징
// - 자식 클래스는 부모 클래스의 타입이다
// - 부모 클래스는 자식 클래스의 타입이 아니다.

// 상속은 자식 클래스가 공통으로 가지고 있는 기능을 부모가 가지고 있는 경우, 사용하면 편하다.
// 인터페이스는 그 기능이 있으면 되지만, 방법이나 구현 방식이 많이 다른 경우 사용하면 편하다.
interface Person_{
    fun eat()
    fun sleep()
}

class Student_ : Person_ {
    override fun eat() {
        TODO("Not yet implemented")
    }
    override fun sleep() {
        TODO("Not yet implemented")
    }
}
open class Person(){
    open fun eat(){

    }
    fun sleep(){

    }
}
```
## 42. 인퍼페이스 - 2
```kotlin
interface Person_{
    fun eat()

    // 인터페이스도 구현이 있는 함수를 만들 수 있다.
    // 인터페이스에 구현이 있는 함수는 그 인터페이스를 구현 하는 클래스에서 그 함수를 구현할 필요가 없다.
    // 인터페이스에 구현이 없는 함수는 그 인터페이스를 구현하는 클래스에서 그 함수를 반드시 구현해야 한다.
    fun sleep(){
        println("let's study")
    }
    abstract fun study()// abstract를 통해서 반드시 구현을 해줘야하는 함수로 만든다.
}

class Student_ : Person_ {
    override fun eat() {
        TODO("Not yet implemented")
    }

    override fun study() {
        TODO("Not yet implemented")
    }
}
```
## 43. 제너릭
```kotlin
// Generic(제너릭)
    // 목적 : 다양한 타입의 객체들을 다루는 메서드나 컬렉션
    //       클래스에서 컴파일 시에 타입을 체크해주는 기능
    // - 제너릭은 만들기 어렵고 실제로 만들 일이 거의 없기 때문에 사용하는 방법만 숙지

    // 제너릭을 사용하지 않은 경우
    // 형 변환을 해줘야 한다.
    val list1 = listOf<>(1,2,3, "가")
    val b: String = list1[2].toString() // 형변환(타입 변환)

    // 제너릭을 사용하는 경우
    val list2 = listOf<String>("a","b","c")
    val c: String = list2[2] // 어느 인자를 가져오더라도 String이라는 것이 보장이 된다.

    // 제너릭을 사용하지 않은 경우
    val lsit5 = listOf<>(1,2,3,1.0,"가")
    // --> Int , Float, String의 최고 부모 클래스로 올라가면, 'Any'라는 클래스가 된다. 즉, 이 리스트의 타입은 Any가 된다.
```
## 44. Java를 알아보자





