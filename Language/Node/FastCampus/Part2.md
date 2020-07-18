# Express

## express 시작

### 왜 Express를 사용해야 하는가

1. 웹서비스 관점
2. 프레임워크 선정시 고려해야 될점
    - 제일 많이 사용하는, 대중적인 솔루션
    - 따라서, 오류 혹은 고민들에 대한 해결책들이 많이 구글링을 통해서 찾을 수 있다.

http 상태코드 ( 약속 )
- 100번대 : 조건부응답 
- 200번대 : 응답성공
- 300번대 : 리다이렉션
- 400번대 : 요청오류(ex - 404 Not Found)
- 500번대 : 서버오류

```js
var http = require('http');

http.createServer(function (request, response){

    response.writeHead(200, {'Content-Type' : 'text/plain'});
    response.write('Hello Nodejs1111');
    response.end();
}).listen(3000);
```

Express를 사용하지 않고 웹서버를 사용해본 간단한 코드 
 

nodemon - 사용을 통해서 코드의 변화를 확인해서 다시 자동으로 서버를 작동시키고 적용시켜주는 좋은 패키지를 사용할 수 있다.



## Routing

### npx 

npx란?
npx는 자바스크립트 패키지 관리 모듈인 npm의 5.2.0버전부터 추가된 툴이다. (새로운 패키지 매니저 개념이 아니다! )

패키지를 설치하지 않고, npm 패키지를 1회성으로 즉석 실행해볼 수 있는 도구이다.

#### 배경

npm으로 모듈을 설치 시 두가지 방안이 있다.

```
1) 전역으로 설치하여 의존성 라이브러리들이 PC에 남게 하는 것

2) 현재 프로젝트에만 개발 의존성 모듈로 설치하는 것
```

최근 npm으로 설치하는 모듈들은 자바스크립트 개발시 사용하는 단순한 모듈 라이브러리의 개념을 넘어 Tool 그 자체의 성격도 지니게 된 듯하다. INTRO에서 언급한 CRA나 vue-cli 처럼 프로젝트 생성도구 처럼 말이다.


그리고 사실 실제 개발이나 테스트를 하다보면 global 설치보다는 devDependency에 설치하는 경향이 더 많은 것 같다. (개인적인 생각일 수 있음..)


그리고 하루가 멀다하고 개선되고, 업데이트되는 이런 툴이나 의존성 라이브러리들을 한번 전역으로 설치해 PC에 남기고, 변경사항이 있으면 다시 삭제 후 설치하는게 번거로울 수 있다.
 

그리고 테스트가 빈번하게 일어나는 상황에서 일일이 설치, 실행, 필요없을 시 제거를 반복하기보단 1회성으로 실행하기 위한 도구가 있으면 좋겠다의 취지에서 나온 것이 'npx' 이다!

[From : yunzema.tistory.com](https://yunzema.tistory.com/270)

`npx nodemon app.js` 따라서 이렇게 스크립트를 저장하고 사용하면 편리하게 이용할 수 있다.

> npm install -g 를 통해서 글로벌 적으로 저장을 해서 npx를 사용한다면

> package.json에 dependency에 기록되지 않아서 어떤 라이브러리를 의존하는지 알 수 없게 되는 것 같다. 


### routing

```js
// admin.js
const express = require('express');
const router = express.Router();

router.get('/', (req, res) =>{
    res.send('After admin url');
});

router.get('/products', (req, res) =>{
    res.send('admin products');
});

module.exports = router;
```

한 app.js에서 모든 url을 받아서 사용한다면, 너무나 지저분한 코드가 완성될 수 있다. 

따라서 새로운 폴더들을 만들고 나누어서 url을 받아서 사용한다면 비교적 깔끔한 코드를 완성할 수 있다.

```js
const admin = require('./routes/admin');
//---
app.use('/admin', admin); // admin 이후의 url은 admin을 사용해서 확인해라 .
```

따라서 따로 분리한 admin을 app.js에서 가져와서 app.use()라는 간단하게 함수를 사용함으로써 분리시켜서 실행시킬 수 있다. 


## View engine


`"start": "npx nodemon -e js,html app.js"` 로 옵션을 js, html을 걸어줌으로써 template가 바뀌더라도 다시 실행해서 적용되도록 설정했다.

```js
//app.js
const nunjucks = require('nunjucks');
//---

// html 해당하는 경로를 그대로 만들어 주는 것. 
nunjucks.configure('template', {
    autoescape : true,
    express : app
});
```

nunjucks라는 view engine을 추가해서 html과 연결하기 편리하게 만들어준다. 

> js파일과 html 연결되는 폴더를 나누더라도 연결되도록. 

```js
// admin.js
router.get('/products', (req, res) =>{
    // res.send('admin products');
    res.render('admin/products.html', {
        message : 'hello!!!',
        online : 'express'
    });
});
```

res.send가 아닌 render를 이용해서 admin/products.html 로 연결되도록 설정했다.

연결하는 것은 앞에서 적용한 nunjucks에서 연결을 해준다. 



## 템플릿 상속

```js
nunjucks.configure('template', {
    autoescape : false, 
    express : app
});
```

autoescape 를 true를 해놓는다면 html 태그가 적용이 안되고 

`<h1>태그가 출력됩니다.</h1>` 그대로 나오고

반대로 false를 하면 

```js
res.render('admin/products.html', {
    message : '<h1>태그가 출력됩니다.</h1>',
    online : 'express'
});
```
를 적용했을 때, 실제로 message가 뜬다면 태그가 적용이 되어 나온다. 

`태그가 출력됩니다.` 만 출력되어 나온다 (h1 태그가 적용이 되어서) 

아니면 html 파일에 {{ message | true }}라고 해놓는 다면, 옵션을 true로 하더라도 이 부분만 html 코드가 적용되어 나올 수가 있다 .



## 미들웨어

`npm install morgan` -- 사용자가 어떤 url을 호출했는지 알 수 있는 것

```js
const logger = require('morgan');
app.use(logger('dev'));
```

이렇게 적용하고, url으로 접근을 한다면, 콘솔에 `GET /admin/products 304 9.130 ms - -`와 같은 메시지가 나오게 된다. 

```js
//admin.js

function testMiddleware(req, res, next){
    console.log('첫번째 미들웨어');
    next();
}

function testMiddleware2(req, res, next){
    console.log('두번째 미들웨어');
    next();
}

router.get('/', testMiddleware, testMiddleware2, (req, res) =>{
    res.send('After admin url');
});
```

다음과 같이 만들어서 사용하게 된다면, admin이라는 url을 접근하게 될 때, 

정의한 두 개의 미들웨어를 거치고 나서야 그 다음 화살표 함수로 이어지게 된다. 

next()는 제어권을 그 다음으로 넘기는 것. 


URL을 실행시켰을 때, 중간 단계들을 거치고서 실행이 되는 것인데 이것들을 미들웨어라고 한다.

예를 들어서, 홈페이지에서 무언가 기능을 사용하기 위해서 로그인이 필요하다면, 로그인을 진행해야한다. 이러한 절차 또한 미들웨어인 것. 



## form(body-parser)

REST API
```
GET /users => 사용자정보
POST /users => 사용자추가
GET /users/(id) => 한명만 볼때
PUT /users/(id) => 한명만 수정하기
DELETE /users/(id) => 한명 삭제 
```
위와 같은 형식으로 개발자들 간에 규약으로 지키는 것. 

## 정적파일

```js
// 앞의 uploads는 URL 뒤의 uploads는 폴더명을 의미한다. 
app.use('/uploads', express.static('uploads')); // 이미지와 같은 이미지 폴더 세팅 
```

위의 코드를 app.js에 추가 후 

`http://localhost:3000/uploads/1.png` 을 통해서 접근을 하면 해당하는 이미지 파일이 불러와져서 나오게 된다. 


## Global View Variable

```js
app.use((req, res, next) =>{
    app.locals.isLogin = true;
    next();
});
```

local 변수에 isLogin을 추가함으로써 모든 페이지에서 이것을 사용해서 접근할 수가 있다. 


## 404, 500 error handling

404 : Not Found 에러 응답

500 : 서버 에러 응답

## nunjucks macro

```js
{# 
    href : 태그안의 링크
    text : 링크안에 들어갈 텍스트
    current_url : 현재 url
 #}
{% macro link(  href , text , current_url ) %}
    <li {% if href == current_url  %} class="active" {% endif %}>
        <a href="{{ href }}">{{ text }}</a>
    </li>
{% endmacro %} 
```

nunjucks 매크로 작성 기능을 이용해서 위와 같이 정의한다면, 

```js
{% from "macro/link.html" import link %}
{{ link('/admin/products', "List", req_path)}}
{{ link('/admin/products/write', "Write", req_path)}}

//  위 아래 비교 

<li class="active">
    <a href="/admin/products">List</a>
</li>
<li>
    <a href="/admin/products/write">Write</a>
</li>
```

위와 같이 사용한다면, 아래와 같이 일일히 계속 넣어줄 필요가 없게 된다. 

## Express 권장 구조

controllers/index : 모든 폴더(대분류)
controllers/admin/index.js : admin url + 미들웨어
controllers/admin/admin.ctrl.js : 컨트롤러 역할 

## 피드백

앞 챕터에서 강의했던 부분들을 다시 알려주는 부분들이 있네요.

npx에 대해서 너무 간단하게 알려주고 어떤게 다른건지 어떻게 사용하는 건지는 알 수가 없어서 따로 공부할 수 밖에 없는 것 같습니다.


