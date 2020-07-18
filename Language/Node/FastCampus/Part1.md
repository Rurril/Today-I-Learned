# Node.js 핵심과정

## nodejs란

Node.js란?

- 웹 브라우저에서 쓰이는 자바스크립트를 서버에서 사용가능 
- 무엇이 가능하게 했나?(V8 탑재)
- V8이란 - 크롬에 탑재된 자바스크립트 엔진
- 대용량 서비스를 위해 개발



## nodejs 설치




## 에디터 설치하기

## 모듈 패턴

내보낼땐 - `Module.exports` 변수

불러올 땐 - `require 파일명`

```js
// myvar.js
function Myvar(){
    this.name = "my instance";
    this.hello = "my hello";
}
module.exports = Myvar;
```


```js
// index.js
const myvar = require('./my');
const setVar = new myvar();

console.log(setVar.name);
console.log(setVar.hello);
```

위와 같이 다른 모듈에서 내보낸 값들을 가져와서 사용이 가능하다. 

결과물 :

`my instance` 

`my hello`

## npm

```json
"dependencies": {
    "express": "^4.17.1",
    "uuid4": "^2.0.2"
}
```

node.module들의 크기가 많이 커서 그것을 빼고 전달하더라도, package.json 파일에 이렇게 의존성이 적혀있다면, 어떤 버전의 모듈들이 필요하고 그것들을 적용하면 되는 구나라는 것을 바로 알 수가 있다.

> 그 모듈들이 없더라도, npm install 명령어를 통해서 그대로 다운로드 받을 수 있다. 

package-lock.json 

- 사용하는 각 모듈들의 하위 모듈들의 버전들이 명시되어, 다른 모듈들 간의 충돌을 방지하기 위해서 작성된다. 
- ex) express는 a 모듈이 v2를 사용하지만, uuid4는 a 모듈의 v1을 사용한다면 충돌이 일어날 수 있기 때문에 그것을 방지하기 위해서 따로 선언해주는 것. 


```json
// package.json
"scripts": {
    "test": "echo \"Error: no test specified\" && exit 1",
    "start": "node index.js" 
},
```

scripts를 사용한다면 `npm start` 를 cmd 혹은 terminal에서 사용한다면 해당하는 스크립트가 실행되게 된다. 





## nodemon



## 피드백

nodemon 설명파트에서 갑자기 chapter2의 express의 코드를 보고 진행하라고 하는 게 좀 말이 안되는데... 차근차근 진행해야하는건데 코드가 뒤쪽에 있다고 그것을 참고하라는 게 이상하지 않나요.