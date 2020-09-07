# dotenv 라이브러리

## 설치

`npm install dotenv --save`

## 왜 사용할까

Dotenv는 환경 변수를 .env 파일에서 process.env로 로드하는 모듈이다. 

다양한 OS에서의 환경변수 설정하는 방법이 다르기 때문에, dotenv를 사용하여 환경변수를 설정하는 방법을 통일하고 쉽게 사용할 수 있게 만들어주는 모듈인 것.

## 사용 방법

프로젝트 루트 경로에 `.env` 파일을 생성하고 

```txt
SERVER_PORT=3000
DB_HOST=localhost
DB_USER=root
DB_PASSWORD=password
```

이와 같이 환경변수들을 설정해줌으로써 다른 파일에서 사용할 수 있는 것.

```js
const dotenv = require('dotenv')

dotenv.config()

const db = require('db')
db.connect({
  host: process.env.DB_HOST,
  username: process.env.DB_USER,
  password: process.env.DB_PASS
})
```

config() 함수를 사용해줌으로써 

process.env에 .env 파일을 로드해준다. 

그럼으로써 환경변수들을 process.env.{환경변수} 로써 사용할 수 있는 것 !


## 환경변수 관리

환경변수는 Github과 같은 버전컨트롤시스템에서 관리하지 않는 것이 좋다. 

다른 곳에 노출될 수 있기 떄문에 gitingnore에 등록함으로써 제외하도록 하자.