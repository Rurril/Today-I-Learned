# Node 핵심 과정



## Node.js_Chapter1_강의소개

강의 특징
- Why? 탐구와 이해
- 문제해결 중심
- 개념적 접근을 통한 깊이 있으면서ㅓ도
- 이해하기 쉽고 자세하게
- 다양한 실습 프로젝트



## Node.js_Chapter1_개발환경설정(Windows)


## Node.js_Chapter1_개발환경설정(MAC)


## Node.js_Chapter1_레벨 테스트



## Node.js_Chapter1_IO와 프로그래밍 패러다임

웹 어플리케이션에서 속도와 성능이 가장 중요한 요소.

### 비동기 vs 동기

동기화 : 해당하는 기기와 다른 기기의 데이터를 일치화 시키는 것. 

그렇기 때문에 데이터를 일치화 시키는 것에 대해서 시간이 걸리기 때문에, 비동기를 적용한다면 속도가 빠르게 될 수 있다.

### Non-blocking vs blocking

Blocking : 해당하는 코드가 완료될 때까지 다른 코드를 진행하지 못하게 하는 것

Node.js에서 Non-blocking을 사용한다.
- JS가 웹 언어이기 때문에(애초에 JS가 Non-blocking 모델을 사용한다)
- JS는 이벤트 주도 방식의 개발 언어다 => 사용자 요청하는 작업이 이루어졌을 때 작동하도록 한다.

### 요약

컴퓨터 작업은 결국 입력을 받고(Input)과 결과물(Output)을 내놓는 것.

작업을 병렬적으로 해결하기 위해서 비동기와 Non-blocking 모델을 채택해서 사용함.


## Node.js_Chapter1_Node vs browser

`window` 라는 프론트 엔드의 JS의 기능 -> Node.js에서는 지원하지 않는다.
- 웹브라우저에서 작동하는 글로벌 객체 - 브라우저 상의 화면을 의미하기에
- 백 엔드에서는 웹 브라우저가 없기 때문에 사용할 수 없다. 


`import React from 'react'` --> JS에서 사용하는 방식

`const dns = require('dns')` --> Node에서 사용하는 방식


```
const - 특정한 상수로써 변하지 않는 값을 사용
let - 스코프(범위) 내에서만 작동하는 변수
var - 파일 내부 전에서 작동하는 변수
```



## Node.js_Chapter1_Node.js REPL


Node.js에 대해서 활용하는 방법

- Read – 유저의 값을 입력 받아 JavaScript 데이터 구조로 메모리에 저장합니다.
- Eval – 데이터를 처리(Evaluate) 합니다.
- Print – 결과값을 출력합니다.
- Loop – Read, Eval, Print 를 유저가 Ctrl+C를 두번 눌러 종료할때까지 반복합니다.

특정한 객체의 정보에 대해서 궁금할 때 간단하게 알아볼 수 있다. 

파일을 생성하지 않고, 한 줄씩 실행시키고 싶을 때 활용하면 된다. 


## Node.js_Chapter1_npm 기초

npx - 해당하는 패키지를 단순히 설치하는 것이 아니라 실행하는 것을 목표로 함.

npm install - 설치

npm uninstall - 삭제 (글로벌 옵션을 주었다면, 똑같이 -g를 넣어준다)



## Node.js_Chapter1_Semantic versioning

문맥적으로 의미가 있는 버저닝 체계

|Code status|Stage|Rule|Example Version|
|:---|---:|:---:|:---:|
|First release|New product|Start with 1.0.0|1.0.0|
|하위 호완이 가능한 버전|Patch release|Increment ths third digit|1.0.1|
|하위 호완이 가능(기능 추가)|Minor release|Increment the middle digit and reset last digit to zero|1.1.0|
|하위 호완이 불가능(중요한 변화)|Major release|Increment the first digit and reset middle and last digits to zero|2.0.0|


## Node.js_Chapter1_npx


스테이징 환경에서 테스트 용도로 사용하기 좋다. 

- npm은 컴퓨터, 서버에 설치를 해서 실행을 하는 방식
- npx는 저장해서 실행하는 것이 아닌, 한 번 실행해보는 것이 목적.
    - 임시 폴더에 설정이 되고, 모듈이 다운되면 실행한다. (ex - cowsay 모듈)


```
npx cowsay "hello" --의 결과 
 _______
< hello >
 -------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
```


## Node.js_Chapter1_nodemon (재촬영)


파일에 변화가 생기면, 파일의 변화를 감지하고 변화된 파일을 실행을 해준다. 


## Node.js_Chapter1_Module.exports

```js
function edit(){}
function write(){}

module.exports = {
    edit,
    write,
    fn : () => {
        console.log('this is a function')
    }
}
```

위와 같은 식으로 객체를 만들어서 export할 수도 있고 단일 객체로 보낼 수도 있다. 



## Node.js_Chapter1_Event Loop 자료구조 (재촬영)

```js

// 큐 FIFO
const queue = []
queue.push(1);
queue.push(2);
queue.push(3);

const a = queue.shift(); // pop인줄 알았는데, pop은 가장 나중에 넣은거 꺼내더라. 
console.log(a); // 1이 나오게 됨. 
```

```js
// 스택 FILO
const stack = []
queue.push(1);
queue.push(2);
queue.push(3);

const a = queue.pop(); 
console.log(a); // 3이 나오게 됨. 
```



## Node.js_Chapter1_Event Loop 실습 (재촬영)

---

## Node.js_Chapter2_every

특정한 배열이 있을 때, 해당하는 배열이 조건에 대해서 모두다 만족할 경우 체크하는 기능을 제공

```js
'use strict'

const arr = [2,3,4];

const isBiggerThanOne = arr.every(key => key > 1);

console.log(isBiggerThanOne);
```

true를 반환하는 것을 볼 수가 있다. 

key에 대해서 arrow function을 정의해서 모두 만족할 경우 true를 반환한 것을 볼 수 있다.




## Node.js_Chapter2_Find, includes

```js
'use strict'

const arr = ['node.js', '올인원'];

const ret = arr.find(key => key === '올인원')

console.log(ret);

```

배열에 두 가지의 요소가 있음에도, ret에 들어온 것은 '올인원'만 들어온 것을 확인할 수 있다. 

```js
const res = arr.includes('node.js');
console.log(res);
```

위에거에 이어서, 사용한다면 include는 그 값이 있는지 확인하는 경우를 리턴해준다.

위의 예시에서는 true를 반환해서 출력하는 것을 볼 수가 있다. 

데이터 조건만 필요할 경우에는 find가 아닌 include로 확인만 진행할 수 있다. 


## Node.js_Chapter2_forEach

```js
'use strict'

const arr = [1,2,3];

arr.forEach(item => console.log(item));
```

배열의 요소인 1,2,3이 순차적으로 출력됨을 볼 수가 있다. 

실제로 사용할 때는, arrow function을 통해서 출력 뿐만 아니라 다양한 방법을 적용할 수 있다. 

## Node.js_Chapter2_Map, Filter (재촬영)

```js
'use strict'

const a = [1,2,3];
const b = a.map(x => x + 1);

console.log(b);
```

a에 담긴 [1,2,3]에서 +1되어서 b는 [2,3,4]가 저장되는 것을 볼 수가 있다. 

배열의 요소에 정의한 콜백 함수를 적용해서 리턴하는 함수라고 볼 수 있겠다.

```js
'use strict'

const a = [1,2,3];
const b = a.filter(x => x > 1);

console.log(b);
```

Filter는 콜백 함수에 적합한 값을 가지는 배열의 요소들만을 리턴해주는 역할을 한다. 


## Node.js_Chapter2_Object.assign vs spread

```js
'use strict'
'use strict'

const obj = {
    title : 'node.js 올인원 패키지'
}

const newObj = {
    name : '패스트캠퍼스'
}

const res = Object.assign(obj, newObj);
const ret = {
    ...obj,
    ...newObj
}

console.log(res);
console.log(ret);
```

두 개의 오브젝트를 통합하는 2 가지 방식에 대해서 소개한다.

위의 Object.assign은 직접 선언해서 두 개를 통합해서 리턴해주었고

아래의 spread 방식은 좀 더 직관적이고 간단하게 두 개를 통합해서 주었다. 

spread는 말 그대로 나누는 것으로, 한 obj가 여러가지 요소들을 갖고 있더라도 나누어서 뿌려줄 수 있는 기능이다. 

## Node.js_Chapter2_Set

중복되지 않은 데이터 셋을 얻고 싶을 때 사용하는 자료구조

```js
'use strict'

const test = new Set()

test.add(1)
test.add(1)
test.add(2)
test.add(2)
test.add(3)
test.add(3)

for(const item of test){
    console.log(item)
}
```

데이터가 중복되지 않고 [1,2,3]만 갖고 있는 것을 알 수 있다. 

## Node.js_Chapter2_some

```js
'use strict'

const arr = [0,-1,-2]

const ret = arr.some(key => key < 0)

console.log(ret)

```

하나라도 콜백 함수에 대해서 만족하는 것이 있다면 true 아니면 false이다. 

여기서는 true라는 것을 알 수 있다. 

Every는 모든 조건을 만족시켜야 하지만, some은 하나라도 만족하면 된다.

## Node.js_Chapter2_Template String


Template String을 사용하게 되면 상수와 변수에 손쉽게 입력할 수 있다. 

단순히 연결하는 것 뿐만 아니라, 숫자 데이터도 String으로 변환이 쉽게 가능하다. 

```js
'use strict'


const details = '자세한 내용'
let str = 'node.js'

str += `올인원 패키지${details}`
const int = 1
str += `${str}의 값은 ${int}`

console.log(str)
```

모든 내용들을 간단하게 string으로 묶어서 출력할 수 있다. 

`node.js올인원 패키지자세한 내용node.js올인원 패키지자세한 내용의 값은 1`이 출력된다.

나중에 react 등에서 주로 쓰이는 기능 다음에 자세히 알아보자. 

## Node.js_Chapter2_String

```js
'use strict'

let string = 'node.js 올인원 패키지'

let isStartWith = string.startsWith('n')
let isIncludes = string.includes('올인원')
let isEndWith = string.endsWith('지')
console.log(isStartWith)
console.log(isIncludes)
console.log(isEndWith)
```

JS는 기본적으로 유니코드를 지원하기 때문에, 한 글자도 한 자로 인식할 수 있기 때문에 위의 세 변수들이 모두 true로 나오게 된다. 

시작 부분, 중간, 끝 에서 해당하는 문자가 있는지 확인할 수 있다. 

## Node.js_Chapter2_Type checking

```js
'use strict'

const string = 'node.js'
const array = []
const obj = {}

console.log(typeof string) // string
console.log(typeof array) // object
console.log(typeof obj) // object
```

array는 obj의 부분집합이므로, object로 나타나는 것을 알 수 있다. 

typeof를 통해서 해당하는 값의 타입을 확인할 수 있다. 

## Node.js_Chapter2_Hoisting (재촬영)

```js
'use strict'

say('hi')
function say(word){
    console.log(word)
}
```

함수를 정의하기 전에 미리 실행하고 그 다음에 정의해도 제대로 실행되는 것

이것이 JS의 Hoisting 특징이라고 한다.

JS는 함수 안에 있는 선언들을 모두 끌어올려서 해당 함수 유효 범위의 최상단에 선언하는 것을 말한다.

자바스크립트 함수는 실행되기 전에 함수 안에 필요한 변수값들을 모두 모아서 유효 범위의 최상단에 선언한다는 것.


## Node.js_Chapter2_IIFE (재촬영)

IIFE : 즉시 실행 함수 표현 - 정의되자 마자 즉시 실행되는 JS 함수를 말한다. 
- Immediately Invoked Function Expression

```js
'use strict'

(function () { console.log('Hello World') })(); // Hello World
```

위는, 함수의 이름이 없는 '익명 함수'로써 바로 정의되자마자 바로 실행한다. - 맨 마지막에 '()'을 통해서 즉시 실행하는 코드라는 것을 나타낸다. 

보편적으로는 전역 스코프를 오염시키지 않기 위해 사용하는 경우가 많다. 

```js
'use strict'

const add = (function(a, b) { return a + b })(1, 2); // 3

console.log(add)
```

위의 예시의 실행은 바로 '3'이 출력되는 것인데, 

선언하고서 바로 사용됨으로써 값으로서 평가되는 것이 IIFE 라는 것.


## Node.js_Chapter2_setInterval (재촬영)

특정 간격으로 실행시킬 수 있는 것이 setInterval 함수

```js
'use strict'

setInterval(() => {
    console.log('hi')
}, 1000);
```

위와 같이 실행시키면, 1000ms 즉, 1초마다 hi라는 문장을 무한대로 출력하는 결과를 볼 수 있다. 

----

## Node.js_Chapter3_Error handling (재촬영)

```js
try{
    a
}catch(e){
    console.log(e)
}
```

try를 실행시켰을 때, 에러가 난다면 확인할 수가 있다.

## Node.js_Chapter3_Error handling 연습문제 (재촬영)

에러가 발생하지 않고 제대로 찍히게 하는 문제 

## Node.js_Chapter3_Error handling 연습문제 해설 (재촬영)

```js
try{
    a
}catch(e){
    console.log(e)
}
console.log(a)
```

에러를 잡고 넘어가기 때문에 제대로 실행되는 것을 볼 수 있다. 

## Node.js_Chapter3_Arrow Functions

함수형 프로그래밍에 다가가고, 가독성이 좋아진다. 

```js
function add(var1, var2){
    return var1 + var2
}

const add = (var1, var2) => var1 + var2
```

위와 같이 평소처럼 함수를 선언해서 사용하는 것이 아닌

arrow function을 사용해서, 좀 더 간단하고 직관적으로 표현이 가능하다. 

## Node.js_Chapter3_Arrow Functions 연습문제

## Node.js_Chapter3_Arrow Functions 연습문제 해설

```js
'use strict'

//curried function(합성함수) - 두 가지 함수를 하나의 함수처럼 모아서 사용하는 것 
// const getDiscount = (price, rate) => price*rate
const getDiscount = price => rate => price*rate

// 위의 함수는 아래와 같다.

var getDiscount = function getDiscount(rate){
    return function(price){
        return rate * price
    }
}

getDiscount(10000, 0.1) // 위의 함수 실행
getDiscount(10000)(0.1) // 아래 함수 실행

const getTenPercentOff = getDiscount(0.1)
getTenPercentOff(10000) // 이 부분을 고객들에 대해서 모두 따로 적용한다면 편리하게 코드 작성이 가능하다, 재사용도 가능 
```

내부 closure 함수를 반환해서 사용하는 것. 

## Node.js_Chapter3_Class (1) (기존영상)

JS는 객체지향의 언어이기도 하다 -> 함수형 프로그래밍의 방식으로도 할 수 있다. 그리고 기본적으로 prototype 기반의 언어라서 언어의 자유도가 높다. 

## Node.js_Chapter3_Class Extends (기존영상)

```js
// cache.js
'use strict'

class cacheManager{
    constructor(){
        this.config = []
    }

    addConfig(obj = {}){
        this.config.push(obj)
    }

    getConfig(){
        return this.config
    }   
}

module.exports = cacheManager
```


```js
// session.js
'use strict'

const cacheManager = require('./cache')

class sessionManager extends cacheManager{

}

const SessionManager = new sessionManager()
SessionManager.addConfig({
    token : 'ran'
})

const config = SessionManager.getConfig()
console.log(config)
```

클래스를 확장해서 session에서 cache의 클래스의 함수를 사용할 수 있게 해주었다.

좀 더 객체지향적인 방법에 가깝게 활용할 수 있다. 

## Node.js_Chapter3_Class (1) (추가촬영)

```js
class Robot{
    constructor(name){
        this.name = name
    }

    speak(){
        console.log(`${this.name}`)
    }
}
const r = new Robot("이름")

r.speak()
```

이름이 출력되는 것을 확인할 수 있다. 
## Node.js_Chapter3_Class (2) (추가촬영)

```js
class Ai extends Robot{
    constructor(name){
        super(name)
    }

    walk(){
        console.log(`walk : ${this.name}`)
    }
}

const a = new Ai("다른이름")
a.walk()
```

Ai는 Robot의 speak도 사용할 수 있고, 따로 정의한 walk도 사용할 수 있다.

또한 constructor 상위 것을 받음으로써 name도 사용이 가능하다.

## Node.js_Chapter3_Static method

스테틱 메소드는 클래스를 생성하지 않고 사용이 가능하다. 

```js
class test{
    static call(){
        console.log('static method')
    }
}

test.call();
```

바로 클래스 객체를 생성하지 않고 사용이 가능하다.

## Node.js_Chapter3_Destructuring

비 구조화

```js
const obj ={
    title : 'node.js',
    value : '올인원 패키지'
}

arr = [0,1,2]

const {title, value} = obj
const [, a, b] = arr
```

위와 같이 구조화된 객체를 분해해서 넣을 수가 있다. 

title 상수에는 'node.js'가 그리고 value에는 '올인원 패키지'가 들어가게 된다.

또한 arr의 길이가 3이기 때문에

a,b에 각각 1,2를 넣기 위해서 [, a, b]로 넣어줌으로써 원하는 값을 넣을 수 있게 하였다. 


## Node.js_Chapter3_Generator 개념적 접근

async와 await의 등장으로 사용이 줄어들었지만, 아직도 사용되는 개념이다

react에서 side effect를 줄일 수 있다. 


```js
//yield : 해당하는 조건이 변화할때 마다 실행이 된다. 

// generator는 화살표함수를 사용하면 안되고, 명시적으로 선언해주고 *를 붙여준다.

function* log(){
    console.log(0, yield)
    console.log(1, yield)
    console.log(2, yield)
}

const gen = log()

gen.next('zero')
gen.next('first')
gen.next('second')
```
## Node.js_Chapter3_Generator 심화 (재촬영)

```js
const obj ={
    *gen() {
        let cnt = 0;
        yield ++cnt;
        yield ++cnt;
        yield ++cnt;
    }
}

const g = obj.gen()
console.log(g.next())
console.log(g.next())
console.log(g.next())
```

```
{ value: 1, done: false }
{ value: 2, done: false }
{ value: 3, done: false }
```

위와 같이 결과물이 0부터 시작해서 증가하는 것을 알 수 있다. 

## Node.js_Chapter3_Timers

외부의 환경적인 요소에 의해서 setTimeout의 실행의 딜레이가 있을 수 있다.

```js
const timeoutObj = setTimeout(() =>{
    console.log('first')
}, 1000) // 이 1초는, 최소 지연시간으로 더 늦춰질 수도 있다. 

const immediateObj = setImmediate(() => {
    console.log('second')
}) 

const intervalObj = setInterval(() => {
    console.log('third')
}, 1000) // 1초 간격으로 다음 함수를 실행시켜준다. 

// 각 객체의 종료 함수는 다르다. 
clearTimeout(timeoutObj)
clearImmediate(immediateObj)
clearInterval(intervalObj)

```

setTimeout을 0초로 준다면 immediate랑 똑같이 작동하는가 ? 

- 코드상에서 확인할 수 없는, cpu 점유율 등의 외부 조건을 통해서 어떤게 먼저 실행될지는 알 수 없다. 
- first, second가 실행시마다 순서가 다르게 나온다. 

## Node.js_Chapter3_Event Emitter

```js
'use strict'

// Event emitter - 기본 모듈

const EventEmitter = require('events')

class ChatManager extends EventEmitter{

}

const chatManager = new ChatManager()

chatManager.on("join", () =>{
    console.log("new user joined")
})

chatManager.emit("join") // join 을 실행시켜줌으로써 new user joined가 출력되는 것을 알 수 있다. 
```


## Node.js_Chapter3_DNS

```js
const dns = require('dns')

dns.lookup("test.com", (err, address, family) => {
    console.log(`address: ${address}, ${family}`)
})
```

```
address: 69.172.200.235, 4
```

family가 4라는건 IPv4를 사용한다는 것을 의미한다.

```js
dns.resolve4('archive.org', (err, addresses) => {
    if(err)throw err

    const res = JSON.stringify(addresses)
    console.log("res : " + res)

    addresses.forEach(a => {
        dns.reverse(a, (err, hostnames) => {
            if(err) throw err

            console.log(`reverse for ${a}; ${JSON.stringify(hostnames)}`)
        })
    })
})
```

여러개의 에러 케치문을 통해서 어디서 에러가 나는지를 확인할 수 있다.

## Node.js_Chapter3_file system (1)

```js
const fs = require('fs')

fs.readFile('test.txt', 'utf-8', (err, data) =>{
    if(err){
        console.error(err)
        return
    } 

    console.log(data)
})

const content = 'something to write'
fs.writeFile('test.txt', content, err =>{
    if(err){
        console.error(err)
        return
    }else{
        console.log('success')
    }
})
```

## Node.js_Chapter3_file system (2)

```js
'use strict'

const fs = require('fs')
const { promisify } = require('util') // 객체처럼 보이지만, 비 구조화를 사용하는 것
// const promisify  = require('util').promisify  // 랑 같은 것 

const read = promisify(fs.readFile) // 콜백함수가 promise로 바뀌는 것 
const write = promisify(fs.writeFile)

const writeAndRead = async(data = '') => {
    try{
        await write('test.txt', data) // promise로 변경했기 때문에, await를 사용할 수 있다는 점. 
        return (await read('test.txt'))
    }catch(e){
        // try 구문 안에 error가 있다면 이부분으로 넘어오게 된다. 
        console.error(e)
    }
}

writeAndRead('something to write')
```

콜백으로 이루었던 것을 더 간단하게 promise를 사용해서 만들었다. 

## Node.js_Chapter3_Promise.All

```js
'use strict'

// promise는 async, await의 근본이된다. 
// promise.all은 실무에서도 빈번하게 사용되는 중요한 방법
const promise1 = new Promise((resolve, reject) => resolve('즉시 호출 된 함수'))
const promise2 = new Promise((resolve, reject) => {
    setTimeout(() => {
        resolve('3초 뒤에 호출')
    }, 3000);
})

Promise.all([promise1, promise2]).then(values => console.log(values))
```

## Node.js_Chapter3_Promise.race

가장 먼저 resolve된 promise가 return되는, 마치 race를 하듯이 끝나는 방식 

```js
'use strict'

const promise1 = new Promise((resolve, reject) =>{
    setTimeout(() => resolve(2000), 2000)
})

const promise2 = new Promise((resolve, reject) =>{
    setTimeout(() => resolve('즉시'), 0)
})
Promise.race([promise1, promise2]).then(value => console.log(value))
```

결과로는 먼저 끝나는 promise2의 resolve 값인 '즉시'가 리턴되어서 출력되는 것을 알 수 있다. 


---


## Node.js_Chapter4_http

http 모듈 이해없이 express 같은 모듈을 사용하면, 실제로 서버를 운영할 때 low level의 단계에서 어떻게 작동하는지 알 수 없다. (문제가 생기더라도 알 수가 없다)


```js
'use strict'

const http = require('http')

const server = http.createServer((req, res)=>{
    res.statusCode = 200
    res.setHeader('Content-Type', 'text/html')
    res.end('<div>Hello World</div>')
})

const port = process.env.PORT; // 외부 환경변수로 선언해서 가져오는 것이 일반적이다. 
server.listen(port, ()=>{
    console.log(`Server running at port ${port}`)
})
```


## Node.js_Chapter4_https

hypertext protocol secure (SSL 보안 프로토콜을 사용한다)

- 모든 과정중에 SSL 프로토콜이 사용되어서, 데이터 처리과정이 암호화되서 안전하게 전송된다.
- http 모듈과 크게 다르지 않다

```js
'use strict'

const https = require('https')
const options = {
    hostname: 'google.com',
    port : 443, // 기본적인 https 포트는 443이다. 
    path : '/login',
    method : 'GET' // CREATE(POST) READ(GET) UPDATE(PUT) DELETE - CRUD
} 

const req = https.request(options, res =>{
    console.log(`statusCode : ${res.statusCode}`)

    res.on('data', d =>{
        process.stdout.write(e)
    })

    req.on('error', e =>{
        console.log(e)
    })
})

req.end() // request가 끝나면 end로 명시적으로 끝내주어야 한다. 
```

## Node.js_Chapter4_Class vs Prototype (1)

왜 더이상 Prototype이 아닌 class로 넘어가는 지 알아보도록 한다.

```js
'use strict'



function fullstack(backend, frontend){
    this.backend = backend
    this.frontend = frontend

    fullstack.prototype.getBackend = () => this.backend
    fullstack.prototype.setBackend = () => this.backend = backend

    fullstack.prototype.getFrontend = () => this.frontend
    fullstack.prototype.setFrontend = () => this.frontend = frontend
} //  프로토타입으로 내부 클로져 함수를 선언한 것 - 함수내부에서 함수 외부에 접근할 수 있는 것 
// error 함수의 this는 글로벌 객체의 this이기 때문에 이 점을 기억할 것 

const Fullstack = new fullstack('javascript', 'javascript')
Fullstack.getBackend()
fullstack.getFrontend()


```

## Node.js_Chapter4_Class vs Prototype (2)

프로토타입을 클래스 타입으로 리팩토링

```js
'use strict'



class fullstack{
    constructor(backend, frontend){
        this.backend = backend
        this.frontend = frontend
    }

    getBackend(){
        return this.backend
    }

    getFrontend(){
        return this.frontend
    }

    setBackend(backend){
        this.backend = backend
    }

    setFrontend(frontend){
        this.frontend = frontend
    }
}

const Fullstack = new fullstack('javascript', 'javascript')
Fullstack.getBackend()
Fullstack.getFrontend()
```

기능적으로도, 내부적으로 동작하는 것도 차이가 없다. 이렇게 방식을 바꾸는 것이 리펙토링

퍼포먼스 향상과 모듈화 그리고 유지보수성 개선을 위해서 리펙토링 과정을 진행했다. 

내부적으로 closure를 갖는 것보다 실제로 선언해서 갖고 있는 것이 더 직관적이다. 

## Node.js_Chapter4_Node.js TDD 프레임워크 소개


TDD 프레임워크 


MOCHA 노드 뿐만 아니라 프론트엔드에서도 사용할 수 있다. 

JEST - MOCK 개념을 활용한, 테스트를 위한 프레임워크 

Cypress - 코드로써 자동화해서 UI 테스트를 진행할 수 있다.


## Node.js_Chapter4_Memory Leaks 개념적 접근

메모리 누수

```js
'use strict'

function study(value1, value2){
    this.value1 = value1
    this.value2 = value2

    
    // this.prototype.func1 을 하지 않고 바로 함수를 정의하는 사람이 있다.
    this.func1 = () =>{
        // 함수 내이밍 없이 arrow function을 하면, 
        // arrow function으로 했기 때문에, 상위 객체에 접근해서 글로벌 this의
        // value1과 value2를 사용할 수 있다. 
        console.log()
    }  
}

const problem = new study(undefined, undefined)
problem.func1() 
// func1을 속성으로 갖고 있는 것은 괜찮다. - js에서 함수는 최상위 객체로 정의된다. 
// 여기서 problem.func1()을 로그로 찍어보면, 문제는 없다. 
// 초기화 할당이 된 후에, 할당 해제 과정이 없다면 이 function이 메모리에 계속 남아있고 계속해서 사용할 수록 누적된다. 
```

arrow 함수를 사용하지 않는다면, this라는 상위 객체에 접근할 수 없을 뿐더러 

## Node.js_Chapter4_Node.js core repo로 살펴보는 TDD 실무

node같은 대규모 오픈 소스에 대해서는 지금까지 개발한 것이 문제 없이 동작하는 것이 중요하다.

수정하고 개선하는 것도 중요하지만, 그 전의 기능들의 동작을 보장해야 한다.

다양한 사람들이 협업하다보니, TDD는 필수적이다. 

## Node.js_Chapter4_Node.js Design Patterns (1)

Functional Programming

```js
'use strict'

const numbers = [10,20,30,40]

const sum = numbers.reduce((total, value) => total + value)

console.log(sum);
```

결과는 total 값에 for문을 돌린 것처럼, 다 더해서 100이 나오게 된다. 

단순히 코드를 한 줄로 나타낼 수 있다는 점 말고도 다양한 기능을 통해서 reduce를 잘 활용할 수 있다. 

```js
'use strict'

const numbers = [10,20,30,40]

const avg = numbers.reduce((total, value, idx, arr) => {
  total += value
  if(idx === arr.length-1){
      return total/arr.length
  }else{
      return total
  }
})

console.log(avg);
```

위와 같이 평균 값을 구하는 것을 하도록하면 간단하게 함수형 프로그래밍 식으로 만들 수 있다. 

## Node.js_Chapter4_Node.js Design Patterns (2)

reduce가 현업에서 활용도가 높고, 복잡한 것을 깔끔하게 하는 Design pattern의 기초가 된다. 

```js
'use strict'

const numbers = [0,1,2,3,4,5,6]

const res = numbers.reduce((total, amount) =>{
    if(amount > 0)total.push(amount)
    return total
}, []) // [] 배열 값으로 total을 초기화(initial value)로 함으로써 push를 쓸수가 있다.

console.log(res);
```

원래 사용하려면, for문을 사용해서 해당 배열을 검색해서 0보다 큰 값들을 배열에 넣었을 것이다. 

reduce를 사용함으로써 여러번 수행해야하는 로직을 한 번에 끝낼 수 있는 장점을 가지고 있다. 

## Node.js_Chapter4_Node.js Design Patterns (3)


```js
'use strict'

const arr = ['pdf', 'html', 'html', 'gif', 'gif', 'gif']

const obj = {

}
// obj['name']  ==> undefined 

const res = arr.reduce((cnt, fileType) =>{
    cnt[fileType] = (cnt[fileType] || 0) + 1
    return cnt
}, {})

console.log(res);
```

```
{ pdf: 1, html: 2, gif: 3 }
```

위의 결과가 리턴되게 된다. 

위의 cnt[fileType]은 오브젝트의 요소에 접근하는 방식이고

아무것도 존재하지 않는다면, 값이 0이 되는 것이 아니라 'undefined'가 되게 되는 것. 

## Node.js_Chapter4_Node.js Design Patterns (4)


불필요한 overhead, operation이 발생되지 않게, 

최초 한 번만 생성됨을 보장하는 패턴이 singleton 패턴이다. -- 환경설정, 캐시관리 등 사용된다. 

```js
'use strict'

class CacheManager{
    constructor(){
        if(!CacheManager.instance){
            this._cache = []
            CacheManager.instance = this
        }
        
        return CacheManager.instance
    }
}

const instance = new CacheManager()
Object.freeze(instance) // 단일 최초에 한 번만 생성이 되는 객체, 싱글톤 패턴
```

## Node.js_Chapter4_Node.js Design Patterns (5) (추가촬영)

Adapter pattern 

호환성이 없는 interface 때문에, 함께 작동할 수 있도록 도와주는 패턴이다. 

```js
/*
Lion interface :

roar()
*/

class AfricanLion  {
    roar() {}
}

class AsianLion  {
    roar() {}
}
```

```js
class Hunter {
    hunt(lion) {
        // ... some code before
        lion.roar()
        //... some code after
    }
}
```


```js
// This needs to be added to the game
class WildDog {
    bark() {
    }
}

// Adapter around wild dog to make it compatible with our game
class WildDogAdapter {

    constructor(dog) {
        this.dog = dog;
    }
    
    roar() {
        this.dog.bark();
    }
}
```

wildDog는 다른 인터페이스 - bark를 사용하기 떄문에 hunt를 사용할 수 없다. 

그렇기 때문에 adapter 클래스를 사용해서 호환이 되게 만들어야 한다. 

```js
wildDog = new WildDog()
wildDogAdapter = new WildDogAdapter(wildDog)

hunter = new Hunter()
hunter.hunt(wildDogAdapter)
```

어뎁터 클래스를 도입하여, Hunter 클래스를 생성하여도 wildDogAdapter를 통해서 roar를 사용할 수 있게 만들어준다. 


## Node.js_Chapter4_Node.js Design Patterns (6) (추가촬영)

Bridge pattern

![](https://cloud.githubusercontent.com/assets/11269635/23065293/33b7aea0-f515-11e6-983f-98823c9845ee.png)

브릿지 패턴은 그림에 보듯이, 상속보다는 각 기능들을 분리를 해서 구성하는 것을 선호하는 패턴이다. 

```js
/*
Webpage interface :

constructor(theme)
getContent()
*/

class About{ 
    constructor(theme) {
        this.theme = theme
    }
    
    getContent() {
        return "About page in " + this.theme.getColor()
    }
}

class Careers{
   constructor(theme) {
       this.theme = theme
   }
   
   getContent() {
       return "Careers page in " + this.theme.getColor()
   } 
}
```

```js
/*
Theme interface :

getColor()
*/

class DarkTheme{
    getColor() {
        return 'Dark Black'
    }
}
class LightTheme{
    getColor() {
        return 'Off white'
    }
}
class AquaTheme{
    getColor() {
        return 'Light blue'
    }
}
```

2개의 웹 페이지와 3개의 Theme을 통해서 

웹페이지가 constructor에 Theme을 받음으로써, 상속이 아닌 구성을 선택해서 간단하게 나타낼 수 있다.

브릿지 패턴을 사용을 안하면, 상속을 받은 클래스들이 합쳐서 6개가 되지만, 굳이 모든 것을 코드로 작성할 필요가 없어졌다. 

```js
const darkTheme = new DarkTheme()

const about = new About(darkTheme)
const careers = new Careers(darkTheme)

console.log(about.getContent() )// "About page in Dark Black"
console.log(careers.getContent() )// "Careers page in Dark Black"
```

## Node.js_Chapter4_Node.js Design Patterns (7) (추가촬영)

Decorator pattern

```js
/*
Coffee interface:
getCost()
getDescription()
*/

class SimpleCoffee{

    getCost() {
        return 10
    }

    getDescription() {
        return 'Simple coffee'
    }
}
```

필요한 경우 코드를 수정할 수 있도록 

코드를 확장 가능하도록 만들고 싶다.

즉, 추가 기능(디코더)를 만드는 것이다.

```js
class MilkCoffee {


    constructor(coffee) {
        this.coffee = coffee
    }

    getCost() {
        return this.coffee.getCost() + 2
    }

    getDescription() {
        return this.coffee.getDescription() + ', milk'
    }
}

class WhipCoffee {

    constructor(coffee) {
        this.coffee = coffee
    }

    getCost() {
        return this.coffee.getCost() + 5
    }

    getDescription() {
        return this.coffee.getDescription() + ', whip'
    }
}

class VanillaCoffee {

    constructor(coffee) {
        this.coffee = coffee
    }

    getCost() {
        return this.coffee.getCost() + 3
    }

    getDescription() {
        return this.coffee.getDescription() + ', vanilla'
    }
}
```


```js
let someCoffee

someCoffee = new SimpleCoffee()
console.log(someCoffee.getCost())// 10
console.log(someCoffee.getDescription())// Simple Coffee

someCoffee = new MilkCoffee(someCoffee)
console.log(someCoffee.getCost())// 12
console.log(someCoffee.getDescription())// Simple Coffee, milk

someCoffee = new WhipCoffee(someCoffee)
console.log(someCoffee.getCost())// 17
console.log(someCoffee.getDescription())// Simple Coffee, milk, whip

someCoffee = new VanillaCoffee(someCoffee)
console.log(someCoffee.getCost())// 20
console.log(someCoffee.getDescription())// Simple Coffee, milk, whip, vanilla
```

상속을 이용한 데코레이터 패턴인 것 같다. 


`어떤 객체에 데코레이터 클래스의 객체로 감싸서 그 객체의 행동을 역동적으로 변화시킬 수 있게 해준다.`



## Node.js_Chapter4_Node.js Design Patterns (8) (추가촬영)

Composite pattern

```js
/*
Employee interface :

constructor(name, salary)
getName()
setSalary()
getSalary()
getRoles()
*/

class Developer {

    constructor(name, salary) {
        this.name = name
        this.salary = salary
    }

    getName() {
        return this.name
    }

    setSalary(salary) {
        this.salary = salary
    }

    getSalary() {
        return this.salary
    }

    getRoles() {
        return this.roles
    }

    develop() {
        /* */
    }
}

class Designer {

    constructor(name, salary) {
        this.name = name
        this.salary = salary
    }

    getName() {
        return this.name
    }

    setSalary(salary) {
        this.salary = salary
    }

    getSalary() {
        return this.salary
    }

    getRoles() {
        return this.roles
    }

    design() {
        /* */
    }
}
```

```js
class Organization {
    constructor(){
        this.employees = []
    }

    addEmployee(employee) {
        this.employees.push(employee)
    }

    getNetSalaries() {
        let netSalary = 0

        this.employees.forEach(employee => {
            netSalary += employee.getSalary()
        })

        return netSalary
    }
}
```

Organization에서 다른 타입의 employee들로 이루어진 객체를 구성할 수 있게 된다.

```js
// Prepare the employees
const john = new Developer('John Doe', 12000)
const jane = new Designer('Jane', 10000)

// Add them to organization
const organization = new Organization()
organization.addEmployee(john)
organization.addEmployee(jane)

console.log("Net salaries: " , organization.getNetSalaries()) // Net Salaries: 22000
```

위와 같이 organization에 다른 타입의 객체들을 엮어서 사용할 수 있게 되는 것. 

## Node.js_Chapter4_비동기 패턴(1)

클래스 내부에, Constructor에서 비동기적인 await를 사용할 수 없기 때문에, 아래와 같은 방법을 사용한다. 

```js
class Sample{
    *gen(){
        let cnt = 0
        yield ++cnt
    }
}
const fn = new Sample()
const gn = fn.gen()

console.log(gn.next())
console.log(gn.next())
```

```js
class Sample{
    *[Symbol.iterator](){
        let cnt = 0
        yield cnt++
    }
}
console.log(Array.from(Sample));


```

## Node.js_Chapter4_비동기 패턴(2)

static factory method 패턴 사용하기 위한 선행학습

```js
class DatabaseManager{
    async init(){ 
        // 최초 1회만 실행되는 것을 보장한다. -- Promise cache 개념
        
    }
}
```

즉, 아래에서 다음과 같이 init()을 여러번 해주어도 메모리 누수가 없다는 것. 

```js
async newMember(){
    await this.init()
}

async deleteMember(){
    await this.init()
}
```


## Node.js_Chapter4_비동기 패턴(3)

static factory method 의 포인트는 constructor의 생성자로써의 기능을 포기하는 것

static method를 이용해서 생성자의 역할을 하게 하는 것. -- factory에서 build하는 것. 

```js
'use strict'

class DatabaseManager{
    
    static async BUILD(settings){
        const config = await this.init(settings)
        //// 수행하고자 하는 모든 비동기 작업을 수행 
        // return new DatabaseManager([Promise]) // 비동기 작업의 결과를 리턴
        return new DatabaseManager(config)
    }

    query(){
        // QUERY('') Agnostic
    }

    async init(){ 
        // 최초 1회만 실행되는 것을 보장한다. -- Promise cache 개념
        // 즉, 

    }

    async newMember(){
       
    }

    async deleteMember(){

    }
}
```

Build를 이용해서 constructor의 역할을 한다. 
- 생성자에서 await를 할 수 없기 때문에 할 수 있는 static method를 만들어서 사용하는 것

## Node.js_Chapter4_비동기 패턴(4) (재촬영)

```js
'use strict'

const co = require('co')

co(function*(){
    const a = Promise.resolve(1)

    const b = Promise.resolve(2)

    const c = Promise.resolve(3)

    const res = yield[a,b,c]
    console.log(res)
})
```

resolve 되는 결과들이 차례대로 나오게 된다. 


---

## Node.js_Chapter5_Race Conditions (1)

## Node.js_Chapter5_Race Conditions (2)

## Node.js_Chapter5_Race Conditions (3)

## Node.js_Chapter5_Race Conditions 연습문제

## Node.js_Chapter5_Race Conditions 연습문제 해설

---

## Node.js_Chapter6_CPU Profiling에 대한 이해

## Node.js_Chapter6_CPU Profiling 분석 기법

## Node.js_Chapter6_CPU Profiling 분석 실무 프로젝트

## Node.js_Chapter6_Heap Snapshot에 대한 이해

## Node.js_Chapter6_Node.js Heap Snpashot 분석 프로젝트 (1)

## Node.js_Chapter6_Node.js Heap Snpashot 분석 프로젝트 (2)
