## 코틀린의 장점

**자료형에 대한 오류를 미리 잡을 수 있는 정적 언어(Statically typed)**
> 정적형식 컴파일러가 타입을 검증해준다. 

**널 포인터로 인한 프로그램의 중단을 예방할 수 있다.**
> 보통 개발자들은 코틀린의 이런 특징을 'NPE에서 자유롭다'라고 한다.

> NPE 는 Null Pointer Exception을 줄여 말한 것.

**데이터형 선언 시 널 가능한 형식과 불가능한 형식 지원**
> 변수는 Nullable과 NotNull로 나뉘어서 형식 지원. 

**자바와 완벽하게 상호운영이 가능하다**

**아주 간결하고 효율적**

**함수형 프로그래밍과 객체 지향 프로그래밍이 모두 가능**

**세미콜론을 생략할 수 있다**



## Hello Kotlin 분석

```kotlin
fun main(args: Array<String>) { // arguments가 있을 경우
    println("args[0] = ${args[0]}") // ${}는 변수를 그대로 입력을 해주도록 된것.
    println(args[1]) // 외부의 두번째 인자.
    println(args[2]) // 외부의 세번째 인자. 
    println(args[3])
}
```
- Class가 없는데 main 메서드 하나로 println을 콘솔에 실행하고 있다.
- 실제로는 main 메서드는 파일명을 기준으로 자동으로 클래스가 생성된다.
    - Tools > Kotlin > Show Kotlin Bytecode에서 Decompile을 해보면 알 수 있다. 

- main()은 최상위 함수로 실행 진입점이다. 
    - 자바와 같은 객체 지향 언어는 프로그램을 실행하기 위해 클래스와 그 안에 main()필요.
    - 코틀린은 클래스 없이 main()함수 하나로 실행 가능



**아래는 Decompile된 코틀린 코드**
```kotlin
public final class HelloworldKt {
   public static final void main(@NotNull String[] args) {
      Intrinsics.checkParameterIsNotNull(args, "args");
      String var1 = "args[0] = " + args[0];
      boolean var2 = false;
      System.out.println(var1);
      var1 = args[1];
      var2 = false;
      System.out.println(var1);
      var1 = args[2];
      var2 = false;
      System.out.println(var1);
      var1 = args[3];
      var2 = false;
      System.out.println(var1);
   }
}
```