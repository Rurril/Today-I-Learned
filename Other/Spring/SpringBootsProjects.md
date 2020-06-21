# 스프링 부트 프로젝트(레스토랑 예약 사이트 만들기)

## Test Driven Development

테스트 주도 개발 -> 목표 중심 개발

올바르게 작동하는 깔끔한 코드를 만드는 것이 목표

--

만들고 -> Refactoring 한다.

> 올바르게 작동한다는 것을 보장해주는 Test Code가 필요하다

> Test first --> Test Driven Development

- Red : 메서드를 만든다. 
- Green : 메서드를 실행시켜본다.
- Refactoring : 테스트를 한다.



```java
package kr.co.fastcampus.eatgo.domain;

import org.junit.Test;

import static org.hamcrest.core.Is.is;
import static org.junit.Assert.*;

public class RestaurantTests {

    @Test
    public void creation(){
        Restaurant restaurant = new Restaurant();
        assertThat(restaurant.getName(), is("Bob zip"));
    }
}
```

```
Expected: is "Bob zip"
     but: was ""
Expected :Bob zip
Actual   :
<Click to see difference>
```

위와 같이 테스트 코드를 작성해서 사용하려고 했지만, 

getName()에는 ""를 return해주기 때문에 기대값과는 다르게 출력되었다고, 테스트 결과가 나오는 것을 알 수 있다. 



```java
public class RestaurantTests {

    @Test
    public void creation(){
        Restaurant restaurant = new Restaurant("Bob zip", "");
        assertThat(restaurant.getName(), is("Bob zip"));
    }

    @Test
    public void information(){
        Restaurant restaurant = new Restaurant("Bob zip", "Seoul");

        assertThat(restaurant.getInformation(), is("Bob zip in Seoul"));
    }
}
```

creation 메소드를 제대로 작성하게 고쳐준 뒤, 새로운 테스트 코드를 추가했을 때



`2 tests completed, 1 failed` 와 같이 결과를 볼 수 있다.

--> creation은 성공했지만, information은 실패한 것



--

해보니까

테스트 코드를 먼저 작성하고(RED), 그 테스트 코드에 맞게 구현코드를 작성(GREEN)했다.

--> RED - GREEN - Refactoring 하는 것... 

위의 예시는 그냥 바로 구현이 가능할 정도로 쉬운 코드들이었지만, 코드가 길어지고 복잡해진다면 이러한 식의 코드는 미래에 복잡해서 고통받을 것들을 미리가져와서

예방 접종 개념으로 미리 아픈것이라고 강사님은 소개했다.

## REST API

서로 다른 Front -end를 통해서 

하나의 Back-end를 통해서 지원한다.

> REST : REpresentational State Transfer

자원에 대해서 처리하는 것을 말한다.(CRUD)

1. Create
2. Read
3. Update
4. Delete

이 네가지는 HTTP 표준으로 주어지는 메소드와 연결이 된다.

1. POST
2. GET
3. PUT/PATCH
4. DELETE

리소스 지정 - URI (Uniform Resource Identifier)
혹은 URL(Uniform Resource Locator)

리소스는 두 개로 분류 가능하다.
1. Collection
   - Read, Creat가 가능하다.
2. Member
   - Read(Detail), Update, Delete


> 강의 진행하고 있는 Restaurants를 기준으로 설명

Collection
- http://host/restaurants

Member
- http://host/restaurants/1
- 개별 리소스에 접근하게 된다.
- 여기서 1은 개별 리소스의 id를 의미한다.

### JSON - Javascript Object Notation

```json
{
    "id" : 2019
    "name" : "식당"
    "address" : "골목"
}
```

와 같은 형식으로 사용된다.

목록과 같은 것은 다음과 같이 사용된다.

```json
{
    {
    "id" : 2019
    "name" : "식당"
    "address" : "골목"
    },
    {
    "id" : 2020
    "name" : "식당"
    "address" : "골목"
    }
}
```

### REST API

가게 목록
- GET/restaurants

가게 상세
- GET/restaurants/1
- GET/restaurants/{id}

가게 추가
- POST/restaurants

가게 수정
- PATCH/restaurants/{id}

가게 삭제
- DELETE/restaurants/{id}




## 가게 목록

```java
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.web.servlet.MockMvc;

import static org.junit.Assert.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.get;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.status;

@RunWith(SpringRunner.class) // 스프링을 이용해서 테스트를 실행할 수 있게 한다. (CRUD에 관한)
@WebMvcTest(RestaurantController.class) // 무엇에 대한 테스트인지.
public class RestaurantControllerTest {

    @Autowired // 다음에 알아본다고 한다. 일단 이렇게 자동으로 spring에서 사용하도록 한다고 한다.
    private MockMvc mvc;

    // 꿀팁 ctrl + alt(option) + o 면 쓸모 없는 import들을 지울 수 있다.
   @Test
    public void list() throws Exception {
        mvc.perform(get("/restaurant"))
                .andExpect(status().isOk());
    }

}
```

그냥 TDD이기에 RED를 먼저했고 실행시키면 오류가 나게 된다.

```
Status expected:<200> but was:<404>
Expected :200
Actual   :404
```

왜냐하면, 아무것도 구현되어있지 않기 때문...


```java
mvc.perform(get("/restaurants"))
                .andExpect(status().isOk())
                .andExpect(content().string(containsString("Bob zip")));
```

```java
mvc.perform(get("/restaurants"))
                .andExpect(status().isOk())
                .andExpect(content().string(
                        containsString("\"name\":\"Bob zip\"")));
```

위와 같이 해도 되지만, JSON 형태로 GET하길 원하기 때문에 

```json
{
    name : "Bob zip"
}
```

과 같이 보내도록 하였다.



> http://localhost:8080/restaurants
> 
```
[{"name":"Bob zip","address":"Seoul","id":1004,"information":"Bob zip in Seoul"}]
```

접속하게 되면, 지금까지 했던 결과를 얻을 수 있다!

## 세부 목록

```java
@GetMapping("/restaurants/{id}")
public Restaurant detail(@PathVariable("id") Long id){
    List<Restaurant> restaurants = new ArrayList<>();

    restaurants.add(new Restaurant(1004L, "Bob zip", "Seoul"));
    restaurants.add(new Restaurant(2020L, "Cyber Food", "Seoul"));

    Restaurant restaurant = restaurants.stream()
            .filter(r -> Objects.equals(r.getId(), id))
            .findFirst()
            .orElse(null);

    return restaurant;
}
```

{id} 를 중괄호에 넣어줌으로써 들어오는 값을 id로 취급한다.

그리고 그 id를 @PathVariable("id") Long id)로 함으로써 변수 id에 집어넣는 식으로 진행한다.


## 저장소 : Repository
```java
@RestController
public class RestaurantController {

    private RestaurantRepository respository = new RestaurantRepository();

    @GetMapping("/restaurants")
    public List<Restaurant> list(){
        return respository.findAll();
    }

    @GetMapping("/restaurants/{id}")
    public Restaurant detail(@PathVariable("id") Long id){
        return respository.findById(id);
    }
}
```

하나의 메소드에 모든 코드들을 넣은 지저분한 것과는 다르게

Repository라는 새로운 도메인 영역의 클래스를 활용해서 각 메소드를 인라인함수로 만들어버렸다.

```java
public class RestaurantRepository {

    private List<Restaurant> restaurants = new ArrayList<>();

    public RestaurantRepository(){
        restaurants.add(new Restaurant(1004L, "Bob zip", "Seoul"));
        restaurants.add(new Restaurant(2020L, "Cyber Food", "Seoul"));
    }

    public List<Restaurant> findAll() {
        return restaurants;
    }

    public Restaurant findById(Long id) {
        return restaurants.stream()
                .filter(r -> Objects.equals(r.getId(), id))
                .findFirst()
                .orElse(null);
    }
}
```

위와 같이 영역을 나누어서 하게 되면, 이렇게 깔끔하고 어떤 클래스가 무슨 역할을하고 나누어서 더 깔끔하고 보기 쉽게 될 수 있었다.


## 의존성 주입

> DI (Dependency Injection) - 의존성 주입

의존성 : 의존 관계를 의미한다.
- 둘 이상의 객체가 서로 협력하는 방법에 대한 것

Ex) A는 B에 의존 -- B의 변화가 A에 영향을 미친다. (관리가 필요)
- Controller가 Repository에 의존
- Controller에 Repository에 연결


Spring IoC Container - 스프링에서 의존성을 관리해준다.


> @Component

> @AutoWired


@Component 

컴포넌트 어노테이션을 Repository에 추가한 뒤 그 객체를 사용하는 곳에 Autowired를 넣음으로써 스프링이 관리해주게 된다.

```java
private RestaurantRepository respository = new RestaurantRepository();

// ----
@Autowired
private RestaurantRepository respository;
```

아래와 같이 해도 잘 작동하는 이유는, 스프링에서 repository 객체를 알아서 생성해서 관리를 해주기 때문이다.

지금까지 만든 Controller 객체들을 다른 곳에서 (특히 메인 Application)에서 객체를 선언하지 않았음에도 잘 사용한 이유는, 스프링에서 관리를 해줬기 때문이다.


위에서 만든 레포지토리를 사용한 다음에 ControllerTest를 사용하려고 하면, 

의존성을 읽지 못해서 Test가 제대로 이루어지지 않는다. 그렇기에 직접 스프링에 의존성을 넣어줘야 한다.

```java
@SpyBean // 컨트롤러에 원하는 객체를 주입할 수 있다.
private RestaurantRepository restaurantRepository;
```

이렇게 의존성을 주입해줌으로써 Test도 무사히 마칠 수 있는 것



```java
@SpyBean(RestaurantRepositoryImpl.class) // 컨트롤러에 원하는 객체를 주입할 수 있다.
private RestaurantRepository restaurantRepository;
```

Repository에서 실행시키는 부분을 interface로 바꿔줌으로써 실현시킨 impl 부분을 따로 만들었다.

그럼으로써 Controller와 repository의 강한 의존 관계를 조금은 유연하게 만들어 주는 이득을 얻을 수 있다고 한다.



**솔직히 아직은 의존성 주입을 통해서 얼마나 큰 이득을 보는지 와닿지는 않는다, 그리고 실현 부분을 만들어놨을 뿐, 그 부분을 인터페이스로 바꿈으로써 보는 이득이 어떤것인지 잘 모르겠다.**

다양한 객체를 RestaurantRepositoryImpl 말고 다른것을 사용할 수 있다고 말하는 건가?

확실히 인터페이스로 바꾼다면, 그것을 implements한 다른 클레스 객체도 사용할 수 있으니까 조금은 유연하게 만들었다는 게 이해는 되지만 아직 와닿지는 않는다.




## 레이어 분리

Layered Architecture

지금까지는 두 가지 레이어를 사용했다.

1. UI Layer(Interfaces)
   - Controller
2. Domain Layer(Domain)
   - Restaurant
   - Repository

이 사이에 Application Layer를 추가해보도록 하겠다.


+ Menu, Iterm - Domain

복잡한 로직

그렇기에 Application - Restaurant service를 넣겠다.



```java
Restaurant restaurant = restaurantRepository.findById(id);
```

기존에 이렇게 restaurant에 대해서 얻었다면, 이제 그에 대한 메뉴를 따로 분리했으므로 그것에 대한 모든 기본적인 정보를 얻기 위해서 하나의 계층을 만들어서 거기서 가져오도록 한다면 보기도 깔끔하고 연결관계가 명확할 것이다.




```java
@GetMapping(“/restaurants/{id}“)
public Restaurant detail(@PathVariable(“id”) Long id){
    Restaurant restaurant = restaurantService.getRestaurant(id);
    restaurant.addMenuItem(new MenuItem(“Kimchi”));
    return restaurant;
}
```
레스토랑의 정보와 매뉴들을 restaurantService로 집어넣음으로서 신뢰할 수 있고 간단하게 표현이 가능해졌다.

## 가짜 객체

Mock Object
하나의 테스트를 통과시키기 위해서, 그것이 의존하는 모든 것을 만들어줘야하는 번거로운 점들이 존재한다.
Mock Object - 따라하는 객체
Mockito - 스프링이 사용하는 프레임워크

```java
@Autowired // 다음에 알아본다고 한다. 일단 이렇게 자동으로 spring에서 사용하도록 한다고 한다.
private MockMvc mvc;
@SpyBean(RestaurantService.class)
private RestaurantService restaurantService;
@SpyBean(RestaurantRepositoryImpl.class)
private RestaurantRepositoryImpl restaurantRepository;
@SpyBean(MenuItemRepositoryImpl.class)
private MenuItemRepository menuItemRepository;
```
모든 것을 Mock 개체로 바꾸려고 한다.


```java
@Autowired // 다음에 알아본다고 한다. 일단 이렇게 자동으로 spring에서 사용하도록 한다고 한다.
private MockMvc mvc;

@MockBean
private RestaurantService restaurantService;

@Test
public void list() throws Exception {
    List<Restaurant> restaurants = new ArrayList();
    restaurants.add(new Restaurant(1004L, "Joker house", "Seoul"));

    given(restaurantService.getRestaurants()).willReturn(restaurants);

    mvc.perform(get("/restaurants"))
            .andExpect(status().isOk())
            .andExpect(content().string(
                    containsString("\"id\":1004")))
            .andExpect(content().string(
                    containsString("\"name\":\"Joker house\"")));
    }
```

테스트 할려는 대상은 Service를 사용하지, 그 service가 어떻게 작동하는지는 관심 밖이라고 한다.

그래서  MockBean이라는 가짜 객체를 이용해서, 직접 given을 통해서 직접 줘서 테스트를 해보는 것이 목적이지, 진짜 객체를 불러오고 가져와서 할 필요까지 없다는 것

`given(restaurantService.getRestaurants()).willReturn(restaurants);`

그래서 위의 코드와 같이, 직접 입력한 것을 돌려줄 수 있느냐라고 물어보고 mvc객체는 가능하다고 그것을 확인하고 테스트를 통과시켜 주는 것 같다. 

(직접 입력해서 사용하기에)

```java
@Autowired
RestaurantRepository restaurantRepository;

@Autowired
MenuItemRepository menuItemRepository;
```

RestaurantService에 의존되어 있는 두 객체들을 사용할 필요가 없다. 

그저 테스트하고자 하는, Service만 있으면 되는 것


```java
package kr.co.fastcampus.eatgo.application;

import kr.co.fastcampus.eatgo.domain.*;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

import java.util.ArrayList;
import java.util.List;

import static org.hamcrest.core.Is.is;
import static org.junit.Assert.*;
import static org.mockito.BDDMockito.given;

public class RestaurantServiceTest {

    private RestaurantService restaurantService;

    @Mock
    private RestaurantRepository restaurantRepository;

    @Mock // 가짜 객체로 만들어도 상관 없는 것들이므로
    private MenuItemRepository menuItemRepository;

    @Before // 모든 테스트를 실행하기전에 setUp을 시켜주는 것이므로, Before 주석을 사용하는 것.
    public void setUp(){
        MockitoAnnotations.initMocks(this); // 위에 선언한 Mock객체들을 말해주는 것
        // Spring Annotation을 선언 안했으므로, 자동으로 해주지 않기 때문

        mockRestaurantRepository();
        mockMenuItemRepository();

        restaurantService = new RestaurantService(restaurantRepository, menuItemRepository);

    }

    private void mockMenuItemRepository() {
        List<MenuItem> menuItems = new ArrayList();
        menuItems.add(new MenuItem("Kimchi"));
        given(menuItemRepository.findAllByRestaurantId(1004L)).willReturn(menuItems);
    }

    private void mockRestaurantRepository() {
        List<Restaurant> restaurants = new ArrayList();
        Restaurant restaurant = new Restaurant(1004L, "Bob zip", "Seoul");
        restaurants.add(restaurant);

        given(restaurantRepository.findAll()).willReturn(restaurants);
        given(restaurantRepository.findById(1004L)).willReturn(restaurant);
    }

    @Test
    public void getRestaurants(){
        List<Restaurant> restaurants = restaurantService.getRestaurants();
        assertThat(restaurants.get(0).getId(), is(1004L));
    }

    @Test
    public void getRestaurant(){
        Restaurant restaurant = restaurantService.getRestaurant(1004L);
        assertThat(restaurant.getId(), is(1004L));
        MenuItem menuItem = restaurant.getMenuItems().get(0);
        assertThat(menuItem.getName(), is("Kimchi"));
    }

}
```

실제 서비스가 어떤지와는 관계 없이, repository들을 가짜 객체로 만들어서 사용하므로써 테스트용으로만 사용하고, 어떻게 작동되는지는 위의 테스트 코드들을 통해서 확인할 수 있다. 

확실히 코드를 작성하는 것에는 시간이 오래걸리고 추가적으로 테스트 코드를 위해서 예제 객체(가짜 객체)를 생성해서 확인하는 것이 오래걸리지만, 어떻게 작동하는지 그리고 작동하는게 무사히 되는 것인지를 진행과정에서 확인할 수 있으므로 (DB같은 것에 넣지 않고도) 실제 현장에서 사용한다면 좋지 않을까 생각한다. 



## 가게 추가 (1)

POST/restaurants

HTTP Status 201(Created)

Header Location - 정보를 헤더에 담아서 전해줌


클라이언트에서 보내준 것을 JSON Parser가 받는다.

HTTPie를 사용해서!

Controller Service

### 1 - Controller

`http POST localhost:8080/restaurants name=BeRyong address=Busan`

를 Httpie를 이용해서 입력했지만
```
"error": "Method Not Allowed",
"message": "Request method 'POST' not supported",
"path": "/restaurants",
"status": 405,
"timestamp": "2020-06-17T14:58:45.700+0000",
```

POST가 지원하지 않는다고 나온다.

이제 포스트를 지원하게 만들어보겠다.

```java
@Test
public void create() throws Exception {
    Restaurant restaurant = new Restaurant(1234L, "BeRyong", "Busan");

    mvc.perform(post("/restaurants"))
            .andExpect(status().isCreated())
            .andExpect(header().string("location", "/restaurants/1234"))
            .andExpect(content().string("{}"));

    //verify(restaurantService).addRestaurant(any()); // 아무 객체나 들어가도 통과되도록 구성된다.
    verify(restaurantService).addRestaurant(restaurant);
}
```

mvc.perform 을 통해서 post를 보내면 해당하는 객체가 제대로 생성되는지 확인한다. 

```java
@PostMapping("/restaurants")
public ResponseEntity<?> create() throws URISyntaxException {
    String name = "BeRyong";
    String address = "Busan";
    Restaurant restaurant = new Restaurant(1234L, name, address);
    restaurantService.addRestaurant(restaurant);

    URI location = new URI("/restaurants/" + restaurant.getId());
    return ResponseEntity.created(location).body("{}");
}
```

실제 create() 메소드에서 보면, 생성되었고, 헤더에 location(name)에 restaurants/1234(value)가 값이 제대로 들어가는 것을 볼 수 있다.

하지만 아직 

`verify(restaurantService).addRestaurant(restaurant);` 는 일단 any() 메소드를 통해서 아무거나 들어가도 통과되도록 해놓는다.


```java
@PostMapping("/restaurants")
public ResponseEntity<?> create(@RequestBody Restaurant resource) throws URISyntaxException {
    String name = resource.getName();
    String address = resource.getAddress();

    Restaurant restaurant = new Restaurant(1234L, name, address);
    restaurantService.addRestaurant(restaurant);

    URI location = new URI("/restaurants/" + restaurant.getId());
    return ResponseEntity.created(location).body("{}");
    }
```

Request로 요청했을 때 - 그 값이 Restaurant 객체로 들어갈 수 있도록 한다. 

`http POST localhost:8080/restaurants name=BeRyong address=Busan`

위의 명령어를 통해서 확인을 해보면

```
HTTP/1.1 201
Connection: keep-alive
Content-Length: 2
Content-Type: application/json;charset=UTF-8
Date: Wed, 17 Jun 2020 15:46:28 GMT
Keep-Alive: timeout=60
Location: /restaurants/1234

{}
```

위와 같이 잘 작동한다는 결과를 얻을 수 있다.


## 가게 추가 (2)




```java
public class RestaurantRepositoryImplTest {

    @Test
    public void save(){
        RestaurantRepository respository = new RestaurantRepositoryImpl();

        int oldCount = respository.findAll().size();

        Restaurant restaurant = new Restaurant("BeRyong", "Seoul");
        respository.save(restaurant);

        assertThat(restaurant.getId(), is(1234L));

        int newCount = respository.findAll().size();

        assertThat(newCount - oldCount, is(1));
    }
}
```

save를 테스트하는 코드를 만들었다.

```java
 @Override
public Restaurant save(Restaurant restaurant) {
    restaurant.setId(1234L);
    restaurants.add(restaurant);
    return restaurant;
}
```

실제로는 restaurant 객체를 받아서 id를 set하고, 리스트에다가 더해서 넘겨주는 것이 끝이다.

테스트도 잘 작동되는 것을 확인할 수 있고

실제로 httpie를 통해서 POST를 넣어봤다.

```
http GET localhost:8080/restaurants
```
```
HTTP/1.1 200
Connection: keep-alive
Content-Type: application/json;charset=UTF-8
Date: Wed, 17 Jun 2020 16:06:15 GMT
Keep-Alive: timeout=60
Transfer-Encoding: chunked

[
    {
        "address": "Seoul",
        "id": 1004,
        "information": "Bob zip in Seoul",
        "menuItems": [],
        "name": "Bob zip"
    },
    {
        "address": "Seoul",
        "id": 2020,
        "information": "Cyber Food in Seoul",
        "menuItems": [],
        "name": "Cyber Food"
    }
]
```

처음에는 그대로 2개인 것을 확인할 수 있지만,

```
http POST localhost:8080/restaurants name=BeRyong address=Busan
```

```
http GET localhost:8080/restaurants
```
```
HTTP/1.1 200
Connection: keep-alive
Content-Type: application/json;charset=UTF-8
Date: Wed, 17 Jun 2020 16:06:35 GMT
Keep-Alive: timeout=60
Transfer-Encoding: chunked

[
    {
        "address": "Seoul",
        "id": 1004,
        "information": "Bob zip in Seoul",
        "menuItems": [],
        "name": "Bob zip"
    },
    {
        "address": "Seoul",
        "id": 2020,
        "information": "Cyber Food in Seoul",
        "menuItems": [],
        "name": "Cyber Food"
    },
    {
        "address": "Busan",
        "id": 1234,
        "information": "BeRyong in Busan",
        "menuItems": [],
        "name": "BeRyong"
    }
]
```

이제 3개가 제대로 나오는 것을 볼 수 있다. 


레이어 분리 

1. UI Layer(Interfaces)
   - Controller
2. Application Layer(Application)
   - Service
3. Domain Layer(Domain)
   - Restaurant
   - Repository

이제 다시 보면, 레이어가 어떻게 이루어져 있고, 실제로 어떻게 적용되는 것인지를 볼 수 있다. 

사용자 계층부터 점점 아래로 내려가면서 사용이 된다... wow.

## JPA

데이터를 유지하기 위해서 영속화 - Persistence가 필요하다

JPA(Java persistence API)가 있다고 한다.

- Hibernate 

@Entity : 가장 중요한 anotation

Spring Data JPA

H2 Database
- In-memory 방식을 사용한다.

```java
@Entity
public class MenuItem {
    @Id
    @GeneratedValue
    private Long id;
    ...
}
```

와 같이 `import javax.persistence`를 사용해서 JPA를 사용해준다. 

```java
public interface RestaurantRepository extends CrudRepository<Restaurant, Long> {
    List<Restaurant> findAll();

    Optional<Restaurant> findById(Long id); // Optiional은 널 값이 들어왔을때 문제점을 해결하게 도와준다.

    Restaurant save(Restaurant restaurant);
}
```

위에 코드처럼, 이제는 구현부분 impl부분을 다 삭제했음에도, 이상없이 get, post등 모두 제대로 작동하는 것을 볼 수 있다.

존재하는 것은 Interface뿐이고 구현부가 하나도 없는데 이게 가능하다고?

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=http%3A%2F%2Fcfile28.uf.tistory.com%2Fimage%2F992A2B445AE809E2213070)

위의 그림처럼 , JpaRepository가 아니라 CrudRepository지만 원리는 같을 것이라고 생각한다. 

Spring Data JPA와 같은 API가 그 인터페이스를 받아서 클래스를 구현해서 사용하는 것 

위의 
- findAll
- findById
- save

는 @Override만 안적혀 있었지, 상속받은 인터페이스에서 선언한 메소드들이었던 것

**지금까지 구현했던, Repository들을 모두 힘들게 힘들게 만들었는데, 다 삭제하고 새롭게 API를 사용해서 하는 것에 10분도 안걸리는 시간에 끝내버렸다...**


## 프론트엔드

Front-end

Web - Mobile - Desktop

이것들이 우리가 작성한 Bakc-end, REST-API를 사용해서 작동한다.

이 중에서 Web에 대해서 이야기해보자.

> HTML - CSS - JavaScript 프론트엔드의 기본

Node.js --> 서버사이드 자바스크립트

- Webpack을 활용해서, Front-end 처리를 할 예정

프론트엔드 사이드 서버를 따로 실행시킬 예정.
(CORS) - Cross-Origin Resource Sharing

이것을 스프링에서 @CrossOrigin 이라는 어노테이션을 사용해서 진행한다.






`npm install --save-dev webpack-cli webpack-dev-server`

dev 키워드를 통해서 개발용으로만 설치를 할 수 있다. 

```java
@CrossOrigin
@RestController
public class RestaurantController
```

CrossOrigin 어노테이션을 붙임으로써, 웹쪽 서버에서도 서버쪽 서버에 접근할 수 있도록 허용해준다.

`<script src="./main.js"></script>`

webpack 서버는 index.js를 main.js로 해서 실행시킨다고 한다(?)

`"main": "src/index.js"`

package.json에서 위와 같이 등록되어 있는 것을 볼 수 있다. 




```javascript
element.innerHTML = `
    ${restaurants[0].id}
    ${restaurants[0].name}
`;
```
```
1 CyberFood
```

결과가 위아래가 다른 것을 볼 수 있다. 참고해서 사용하자 


```javascript
element.innerHTML = JSON.stringify(restaurants);
```

```
[{"id":1,"name":"CyberFood","address":"Seoul","menuItems":[],"information":"CyberFood in Seoul"}]
```


```javascript
element.innerHTML = `
    ${restaurants.map(restaurants => `
        <p>
            ${restaurants.id}
            ${restaurants.name}
            ${restaurants.address}
        </p>
    `).join('')}
`;
```

한번에 처리도 가능하다고 한다... 

일단 이번 강의까지 만든 index.js
```javascript
(async () =>{
    const url = 'http://localhost:8080/restaurants';
    const response = await fetch(url);
    const restaurants = await response.json();

    const element = document.getElementById('app');
    element.innerHTML = `
        ${restaurants.map(restaurants => `
            <p>
                ${restaurants.id}
                ${restaurants.name}
                ${restaurants.address}
            </p>
        `).join('')}
    `;
})();
```

## 가게 수정

CURD 에서 UPDATE 혹은 PATCH를 사용!

PATCH/restaurants/{id}

@Transactional 어노테이션, 데이터를 고치기만해도 DB에 반영되는 것

```java
@Transactional
public Restaurant updateRestaurant(Long id, String name, String address) {
    Restaurant restaurant = restaurantRepository.findById(id).orElse(null);

    restaurant.updateInformation(name, address);
    return restaurant;
}
```

실제로 이 메서드의 실행을 통해서 DB에 적용되게 어노테이션을 적용시킴으로써


```
[
    {
        "address": "Seoul",
        "id": 1,
        "information": "Test in Seoul",
        "menuItems": [],
        "name": "Test"
    },
    {
        "address": "Seoul",
        "id": 2,
        "information": "JJK in Seoul",
        "menuItems": [],
        "name": "JJK"
    }
]
```

이렇게 되어있던 것이

`http PATCH localhost:8080/restaurants/1 name=BeRyong address=Busan`

를 통해서

```
[
    {
        "address": "Busan",
        "id": 1,
        "information": "BeRyong in Busan",
        "menuItems": [],
        "name": "BeRyong"
    },
    {
        "address": "Seoul",
        "id": 2,
        "information": "JJK in Seoul",
        "menuItems": [],
        "name": "JJK"
    }
]
```

가 되었습니다

## Lombok

Annotation Processor를 사용해서 자동으로 코드를 만들어주는 프로젝트

--> @Setter @Getter , @Builder 도 제공

```java
@Getter
public class Restaurant 
```

를 통해서 앞서 만들었던 getId, getAddress getName 등 모두 직접 선언할 필요가 없어졌다.


@Setter도 마찬가지로 클래스 앞에 선언을 해준다면, restaurant 객체를 이용해서 메소드를 부를 때 자동으로 생성되어있어서 사용할 수 있음을 볼 수 있다. 

(혹은 클래스말고 각 요소들에 선언을 해주어도 된다) -- 

```java
@Setter 
private int id;
```


```java
public Restaurant() {

}
```

이렇게 선언해주는 생성자도

```java
@NoArgsConstructor
```

이렇게 클래스에 선언해주는 것으로 해결할 수 있다. 

### 빌더 패턴

```java
Restaurant restaurant = new Restaurant(1004L, "Bob zip", "Seoul");
// --- // 
Restaurant restaurant = Restaurant.builder()
        .id(1004L)
        .name("Bob zip")
        .address("Seoul")
        .build(); // 위에보다 아래쪽이 빌더패턴이라는 것
```

위에처럼 레스토랑 객체를 생성하면, 각 담기는 요소가 무엇을 의미하는지 직관적으로 알 수가 없다. 

그래서 코드가 조금 길어지기는 하지만, 빌더패턴을 사용하여 아래와 같이 각 요소의 이름을 적어줌으로써 코드를 직관적으로 볼 수 있게 해준다. 

> @Builder 어노테이션을 클래스에 추가해준다. 

생성자, 요소들이 많아질 수록 점점 더 햇갈려지는 데, 다음과 같이 빌더를 통해서 순서와 상관없이 넣을 수 있게 해줌으로써 더 간단하고 직관적이게 만들어준다.

> 빌더, 그리고 이러한 디자인 패턴을 사용함으로써 다양한 생성자들을 만들어 줄 필요가 없어졌다.


```java
@Entity
@Getter
@NoArgsConstructor
@Builder
@AllArgsConstructor
public class Restaurant {
    
    @Id
    @GeneratedValue
    @Setter
    private long id;

    private String name;
    private String address;

    @Transient // 임의로 만들어서, DB처리를 하거나 하지 않을 것이라는 것
    private List<MenuItem> menuItems;

    public String getInformation(){
        return name + " in " + address;
    }

    public List<MenuItem> getMenuItems(){
        return menuItems;
    }

    public void setMenuItems(List<MenuItem> menuItems) {
        this.menuItems = new ArrayList<>(menuItems);
    }

    public void updateInformation(String name, String address) {
        this.name = name;
        this.address = address;
    }
}
```

생성자들과 getter와 setter로 많았을 클래스가 가벼워진 것처럼 보인다. 


아래의 MenuItem의 변화가 극적이다..

```java
@Entity
@Getter
@Builder
@NoArgsConstructor
@AllArgsConstructor
public class MenuItem {

    @Id
    @GeneratedValue
    private Long id;

    private Long restaurantId;

    private String name;

}
```

## Validation

검증하는 작업, 말 그대로

@NotNull
@NotEmpty
@Size(max=10)

이런 것들을 한 번에 @Valid 로 한다. 

HTTP Staus 400 (Bad Request)

```java
@Test
public void createWithInvalidData() throws Exception {
    given(restaurantService.addRestaurant(any())).will(invocation -> {
        Restaurant restaurant = invocation.getArgument(0);
        return Restaurant.builder()
                .id(1234L)
                .name(restaurant.getName())
                .address((restaurant.getAddress()))
                .build();
    });

    mvc.perform(post("/restaurants")
            .contentType(MediaType.APPLICATION_JSON)
            .content("{\"name\":\"\",\"address\":\"\"}"))
            .andExpect(status().isBadRequest());
}
```

실제 컨트롤러에서 created로 받는 @Valid로 요소에 어노테이션 해주고, 

Restaurant가 받는 인자드를 @NotEmpty 어노테이션을 넣어줌으로서 받드시 들어가야함을 나타내게 한다.   

그럼으로써 위의 테스트가 통과가 되는 것을 볼 수 있다. 

```java
@Test
public void updateWithoutName() throws Exception {
    mvc.perform(patch("/restaurants/1004")
            .contentType(MediaType.APPLICATION_JSON)
            .content("{\"name\":\"\",\"address\":\"Busan\"}"))
            .andExpect(status().isBadRequest());
}
```

조금이라도 미심쩍은 상황, 케이스들이 있다면, 직접 이렇게 Name만 없이 입력해보고 예상하던 값이 나오는지를 확인할 수가 있다.

