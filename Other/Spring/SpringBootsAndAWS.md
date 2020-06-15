# 스프링 부트와 AWS로 혼자 구현하는 웹서비스

## 목차.

> [1장. 인텔리제이로 스프링 부트 시작하기](#1장.-인텔리제이로-스프링-부트-시작하기)

> [2장. 스프링 부트에서 테스트 코드를 작성하자](#2장.-스프링-부트에서-테스트-코드를-작성하자)

> [3장. 스프링 부트에서 JPA로 데이터베이스 다뤄보자](#3장.-스프링-부트에서-JPA로-데이터베이스-다뤄보자)

> [4장. 머스테치로 화면 구성하기](#4장.-머스테치로-화면-구성하기)

> [5장. 스프링 시큐리티와 OAuth 2.0으로 로그인 기능 구현하기](#5장.-스프링-시큐리티와-OAuth-2.0으로-로그인-기능-구현하기)

> [6장. AWS 서버 환경을 만들어보자 - AWS EC2](#6장.-AWS-서버-환경을-만들어보자---AWS-EC2)

> [7장. AWS에 데이터베이스 환경을 만들어보자 - AWS RDS](#7장.-AWS에-데이터베이스-환경을-만들어보자---AWS-RDS)

> [8장. EC2 서버에 프로젝트를 배포해 보자](#8장.-EC2-서버에-프로젝트를-배포해-보자)

> [9장. 코드가 푸시되면 자동으로 배포해 보자 - Travis CI 배포 자동화](#9장.-코드가-푸시되면-자동으로-배포해-보자---Travis-CI-배포-자동화)

> [10장. 24시간 365일 중단 없는 서비스를 만들자](#10장.-24시간-365일-중단-없는-서비스를-만들자)

> [11장. 1인 개발시 도움이 될 도구와 조언들](#11장.-1인-개발시-도움이-될-도구와-조언들)

## 1장. 인텔리제이로 스프링 부트 시작하기

기본적인 build.gradle에서 스프링 부트에 필요한 설정들을 하나씩 추가하겠다.

```gradle
buildscript{
    ext{
        springBootVersion = '2.1.7.RELEASE'
    }
    repositories{
        mavenCentral()
        jcenter()
    }
    dependencies{
        classpath("org.springframework.boot:spring-boot-gradle-plugin:${springBootVersion}")
    }
}
```

플러그인 의존성 관리를 위한 설정

> ext 키워드 : build.gradle에서 사용하는 전역변수를 설정한 것 

>> 여기서는 springBootVersion 전역변수 생성 후 그 값을 '2.1.7.RELEASE'로 설정한 것

> 


```gradle
    apply plugin: 'java'
    apply plugin: 'eclipse'
    apply plugin: 'org.springframework.boot'
    apply plugin: 'io.spring.dependency-management'
```

4번째 플러그인은 스프링 부트의 의존성을 관리해주는 플러그인이라 꼭 추가해야함

앞 4개의 플러그인은 자바와 스프링 부트를 사용하기 위해서는 필수 플러그인이라고 함



```gradle

group 'org.example'
version '1.0-SNAPSHOT'
sourceCompatibility = 1.8
```
```gradle
repositories {
    mavenCentral()
    jcenter()
}
```

repositories는 각종 의존성(라이브러리)들을 어떤 원격 저장소에서 받을지를 정한다.

기본적으로 mavenCentral을 많이 사용하지만, 최근에는 라이브러리 업로드 난이도 때문에 jcenter도 많이 사용한다고 한다.



```
dependencies {
    compile('org.springframework.boot:spring-boot-starter-web')
    testCompile('org.springframework.boot:spring-boot-starter-test')
}

```

```
Download https://services.gradle.org/distributions/gradle-6.1-all.zip (138.51 MB)
Download https://services.gradle.org/distributions/gradle-6.1-all.zip finished succeeded, took 12 s 195 ms
> Task :prepareKotlinBuildScriptModel UP-TO-DATE
KotlinDslScriptsParameter(correlationId=350594233582438, scriptFiles=[]) => StandardKotlinDslScriptsModel(scripts=[], commonModel=CommonKotlinDslScriptModel(classPath=[], sourcePath=[], implicitImports=[]), dehydratedScriptModels={}) - took 0.001 secs

Deprecated Gradle features were used in this build, making it incompatible with Gradle 7.0.
Use '--warning-mode all' to show the individual deprecation warnings.
See https://docs.gradle.org/6.1/userguide/command_line_interface.html#sec:command_line_warnings

BUILD SUCCESSFUL in 1m 7s

```

빌드가 완료되었다. 


배운 것

- mavenCentral, jcenter 비교
- 스프링 부트 프로젝트와 그레이들 연동 방법



## 2장. 스프링 부트에서 테스트 코드를 작성하자


```java
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class Application {
    public static void main(String[] args){
        SpringApplication.run(Application.class, args);
    }
}
```

만든 Application 클래스는 앞으로 만들 프로젝트의 **메인 클래스**가 된다.

@SpringBootApplication -- Annotaion으로 인해서 스프링 부트의 자동 설정, 스프링 Bean 읽기와 생성을 모두 자동으로 설정한다.

이 어노테이션이 있는 위치부터 설정을 읽어가기 때문에 이 클래스는 항상 프로젝트의 최상단에 위치해야 한다.

> SpringApplication.run

위의 메소드를 통해서 내장 WAS(Web Application Server)를 실행합니다.

- 내장 WAS란 외부 WAS를 두지 않고 애플리케이션을 실행할 때 내부에서 WAS를 실행하는 것을 말한다.

```java
package com.jojoldu.book.springboot.web;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController // 1
public class HelloController {
    
    @GetMapping("/hello") // 2
    public String hello(){
        return "hello";
    }
    
}
```

> 1 : RestController
- 컨트롤러를 JSON을 반환하는 컨트롤러로 만ㄷ르어 준다.
- 과거에는 @ResponseBody를 각 메소드마다 선언했던 것을 한번에 사용할 수 있게 해준다고 한다.

> 2 : GetMapping
- HTTP Method인 Get의 요청을 받을 수 있는 API를 만들어 준다.
- 이 메소드는 /hello로 요청이 오면 문자열 hello를 반환하는 기능을 갖게 된 것


```java
package com.jojoldu.book.springboot.web.web;
import com.jojoldu.book.springboot.web.HelloController;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowire;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.ResultActions;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;

@RunWith(SpringRunner.class) // 1
@WebMvcTest(controllers = HelloController.class) // 2
public class HelloControllerTest {

    @Autowired // 3
    private MockMvc mvc; // 4

    @Test
    public void hello() throws Exception{
        String hello = "hello";

        mvc.perform(MockMvcRequestBuilders.get("/hello"))  // 5
                .andExpect(MockMvcResultMatchers.status().isOk()) // 6
                .andExpect(MockMvcResultMatchers.content().string(hello)); // 7
    }

}
```

HelloControllerTest.java의 코드들

1. @RunWith(SpringRunner.class)
    - 테스트를 진행할 때 JUnit에 내장된 실행자 외에 다른 실행자를 실행시킨다.
    - 여기서는 SpringRunner라는 스프링 실행자를 사용한다.
    - 즉, 스프링 부트 테스트와 JUnit 사이에 연결자 역할을 한다.

    


## 3장. 스프링 부트에서 JPA로 데이터베이스 다뤄보자
## 4장. 머스테치로 화면 구성하기
## 5장. 스프링 시큐리티와 OAuth 2.0으로 로그인 기능 구현하기
## 6장. AWS 서버 환경을 만들어보자 - AWS EC2
## 7장. AWS에 데이터베이스 환경을 만들어보자 - AWS RDS
## 8장. EC2 서버에 프로젝트를 배포해 보자
## 9장. 코드가 푸시되면 자동으로 배포해 보자 - Travis CI 배포 자동화
## 10장. 24시간 365일 중단 없는 서비스를 만들자
## 11장. 1인 개발시 도움이 될 도구와 조언들

