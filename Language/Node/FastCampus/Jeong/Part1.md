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


49. Node.js_Chapter4_http

50. Node.js_Chapter4_https

51. Node.js_Chapter4_Class vs Prototype (1)

52. Node.js_Chapter4_Class vs Prototype (2)

53. Node.js_Chapter4_Node.js TDD 프레임워크 소개

54. Node.js_Chapter4_Memory Leaks 개념적 접근

55. Node.js_Chapter4_Node.js core repo로 살펴보는 TDD 실무

56. Node.js_Chapter4_Node.js Design Patterns (1)

57. Node.js_Chapter4_Node.js Design Patterns (2)

58. Node.js_Chapter4_Node.js Design Patterns (3)

59. Node.js_Chapter4_Node.js Design Patterns (4)

60. Node.js_Chapter4_Node.js Design Patterns (5) (추가촬영)

61. Node.js_Chapter4_Node.js Design Patterns (6) (추가촬영)

62. Node.js_Chapter4_Node.js Design Patterns (7) (추가촬영)

63. Node.js_Chapter4_Node.js Design Patterns (8) (추가촬영)

64. Node.js_Chapter4_비동기 패턴(1)

65. Node.js_Chapter4_비동기 패턴(2)

66. Node.js_Chapter4_비동기 패턴(3)

67. Node.js_Chapter4_비동기 패턴(4) (재촬영)

---

68. Node.js_Chapter5_Race Conditions (1)

69. Node.js_Chapter5_Race Conditions (2)

70. Node.js_Chapter5_Race Conditions (3)

71. Node.js_Chapter5_Race Conditions 연습문제

72. Node.js_Chapter5_Race Conditions 연습문제 해설

---

73. Node.js_Chapter6_CPU Profiling에 대한 이해

74. Node.js_Chapter6_CPU Profiling 분석 기법

75. Node.js_Chapter6_CPU Profiling 분석 실무 프로젝트

76. Node.js_Chapter6_Heap Snapshot에 대한 이해

77. Node.js_Chapter6_Node.js Heap Snpashot 분석 프로젝트 (1)

78. Node.js_Chapter6_Node.js Heap Snpashot 분석 프로젝트 (2)