# Express

## Express 기본


## Express Middlewares

사용하는 미들웨어들

body-parser 
- 다양한 타입에 대해서 파싱을 제공하는 모듈 : 익스프레스에 사용되는 미들웨어로써 사용된다. 

cookie-parser

helmet 
- 익스프레스에서 필요한 보안 옵션에 대해서 최적의 보안 세팅을 제공한다. 

```js
'use strict'

const express = require('express')
const cookieParser = require('cookie-parser')
const bodyParser = require('body-parser')
const http = require('http')
const helmet = require('helmet')

class ApiServer extends http.Server{
    constructor(config){
        const app = express()
        super(app)
    }

    async start(){
        this.app.use(helmet()) // 가장 먼저 보안 세팅을 위해서 설정
        this.app.use(cookieParser())
        this.app.use(bodyParser())
    }
}
```


## Custom Middlewares

직접 미들웨어를 작성하는 챕터

```js
// this.app 은 exprees
this.app.use((err, req, res, next) =>{ // custom middle 웨어의 기본적인 구조 
            console.error(`Internal error`, err)
            if(req){
                console.log(req);
            }
            if(res){
                console.log(res);
            }

            next() // 그 다음 미들웨어를 작동하도록 next해준다.
        })
```

## Express 정적 파일 처리

이미지 파일과 같은 정적 파일 handling 
- static file은 express에서 바로 서빙하는 것보다 리버스 프록시 서버에서 처리하는 것이 성능이 우수하다. 
- 하지만 그럼에도 꼭 express에서 해야한다고 할 경우의 방법을 알려준다
- (절대로 권장하지 않는다) - 방법론 적인 측면에서 알려준다. nginx를 사용하는 것이 더 좋다. 

```js
 constructor(config){
        const app = express()
        super(app)
        this.app.static = static // 미들웨어로 사용한다는 것을 처리
}

 this.app.use(this.app.static(path.join(__dirname, 'dist'), {
    setHeaders : (res, path) => {
        // 어디에서 접근하더라도 허용하도록 
        res.setHeaders('Access-Control-Allow-Origin', '*')
        // 특정한 헤더 조건 없이, 모든 헤더를 허용해주도록 
        res.setHeaders('Access-Control-Allow-Headers', '*')
        res.setHeaders('Access-Control-Allow-Methods', 'GET')
    }
}))
```
## REST API 

test.com/user [POST]
test.com/user [PUT]
test.com/user [DELETE]
test.com/user [PATCH]

액션에 대해서는 url에 명시하는 것이 아니라 CRUD method를 사용함으로써 차이를 만드는 것.

POSTMAN
- REST API를 개발하면서 테스트하기 위해서 사용함

## 템플릿 엔진 소개

기존의 데이터와 랜더링하는 데이트러르 뷰라고 했을 때, 이러한 과정을 쉽게 만들어주는 것이 템플릿 엔진이다

- html 페이지를 리턴해야할 때, 템플릿 엔진을 사용하는 목적은 - html 태그를 모두 작성하고 가공된 데이터를 맞추는 반복된 작업을 생략하기 위함. 
- UI를 편리하게 구성할 수 있다. 
- 직접 html 코드를 작성하지 않음으로써 나타날 수 있는 버그를 방지할 수 있다. 

다른 미들웨어와는 다르게 

app.use가 아닌 app.set으로 사용한다.

`app.set('view engine', 'hbs')` <- 예시

일반적으로 싱글페이지 어플리케이션 -spa는 리엑트를 기반으로 작성

하지만 단순한 웹페이지를 작성할 때는 템플릿 엔진을 활용하면 된다. 
- 실무에서는 활용도가 높지 않다(리엑트로 풀스택 어플리케이션을 개발할 수 있기 때문)
- 그럼에도 언제 활용되고 어떻게 활용되는지 정확하게 이해하는 것은 중요하다. 

## Caching Layers

redis

redis-cluster 다운

```js
'use strict'

const RedisCluster = require('redis-cluster')
const RedisClient = require('redis')
const config = require('./config') // config파일에 설정했던 것을 가져온다. 

const { promisify } = require('util')

let redis, redisSub
let subCallbacks = new Map()

async function getRedisClient(sub){
    const conf = await config.getConfig()

    if(sub && redisSub) return redisSub
    if(!sub && redis) return redis    

    const options = {}
    let newClient

    if(conf.redisUseCluster){ // 레이어  - 계층적으로 이루어진 경우 
        newClient = new RedisCluster({
            servers : [
                {
                    host: conf.redisHost,
                    port: conf.redisPort
                }
            ],
            createClient: (port, host) => RedisClient.createClient(port, host, options)
        })
    }else{ // 단일 클라이언트로 구성되는 경우
        newClient = RedisClient.createClient(conf.redisPort, conf.redisHost, options)
    }

    if(sub){ // 클라이언트는 구독자, 서버는 퍼블리셔 - 지금은 클라이언트 부분에 대해서 생각
        redisSub = newClient
        newClient.on('message', (topic, message) => {
            if(subCallbacks.has(topic)){
                const callback = subCallbacks.get(topic)
                callback(message)
            }
        }) // 메시지 큐를 이용하게 되면, 서버가 재시작되도 남아있는 작업을 알 수 있다. - 비정상적으로 다운이되도 가져올 수 있다.

        newClient.on('error', err =>{ // 에러에 대해서도 처리할 수 있어야 한다. 
            console.error(err)
            newClient.end()
        })
    }else{ // 구독자가 없을 때 
        redis = newClient
    }

    newClient.on('connect', () =>{
        console.log(`${sub} connected`);
    })

    // 재접속인 경우에 캐시를 만들필요 없이 진행하면 된다.

    newClient.on('reconnect', () =>{
        console.log(`Redis ${sub} reconnected`);
    })

    promisifyClient(newClient) // 아직 정의하지 않음. -- 

    return newClient
}

function promisifyClient(redis){
    redis.get = util.promisify(redis.get.bind(redis))
}
```

## Express Singleton Pattern

```js
'use strict'

const {init} require('./server.js')
const { getConfig } = require('./lib/config')

const env = process.env.NODE_ENV

const main = async () =>{
    const config = await getConfig()

    const server = await init()
    server.listen(confg.port, () =>{
        console.log(`Server listening on port ${config.port}`)
    })

    process.on('SIGTERM', () => server.shutdown())
    process.on('SIGINT', () => server.shutdown())
}
```


## Express Failover(동시접속 장애처리)



```js
shutdown(){
    if(this.stopping)return
    this.stopping = true
    this.close(() => {
        process.exit(0)
    })

    setTimeout(() =>{
        console.error('비정상적인 종료(강제 종료)');
        process.exit(1)
    }, this.config.shutdownTimeout).unref()

    if(this.currentConns.size > 0){
        console.log(`현재  동시접속중인 연결(${this.currrentConns.size})을 대기중입니다`);
    }

    for(const con of this.currentConns){
        if(!this.busy.has(con)){
            con.end()
        }
    }
}
```

## Express Classify(클래스 패턴)

```js
async start(){
        this.app.use((req, res, next) =>{
            this.busy.add(req.socket)
            res.on('finish', () =>{
                if(this.stopping)req.socket.end()
                this.busy.delete(req.socket)
            })
            next()
        })

        this.app.use(cookieParser())

        this.app.get('/_health', (req, res) => {
            res.sendStatus(200)
        })
        
        this.app.use((err, req, res, next) =>{
            res.status(500).send(generateApiError('Api::Error'))
        })
    }
```



## Xss Filter

```js
app.use(helmet.xssFilter())
app.use(helmet.framegaurd())
```

