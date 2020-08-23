# Redis

## Redis 소개와 개발 환경 설정

메모리 상에서 작동한다. 

REDIS - REmote Dictionary Server 의 줄임말

Key - Value 구조 데이터 관리 시스템이며 모든 데이터를 조회하고 관리하기에 빠른 W&R 속도를 보장하는 `비 관계형 데이터베이스`이다.

인 메모리 - RAM에서 작동할 수 있기 때문에 매우 빠른 속도를 자랑한다.



## Data types

```js
const redis = require('redis')
const client = redis.createClient()

client.on('connect', () =>{
    console.log('connected');
})

client.set('backend', 'node', (err, res) =>{
    console.log(res)
})

client.set('frontend', 'js')
client.expire('fronted', 20)

client.get('backend', (err, res) =>{
    console.log(res);
})
```

```
connected
OK
node
```

다음과 같은 결과를 얻을 수 있음을 볼 수 있다.   


```js

client.del('backend', (err, res) =>{
    if(err){
        console.error(err);
    }
    console.log(res);
})

client.set('frontend', 1, () =>{
    // Increment
    client.incr('frontend', (err, res) =>{ // RAM에 접근하는 IO작업이기 떄문에 비동기작업임
        if(err){
            console.error(err);
        }else{
            console.log(res);
        }
    })
})

client.set('full', 2, () =>{
    // Decrement 
    client.decr('full', (err, res) =>{
        if(err){
            console.error(err);
        }else{
            console.log(res);
        }
    })
})
```

```
1
2
1
```

delete 되어 1이 출력되고 increment를 통해서 1이 2가 되어 출력되고 decrement를 통해서 2가 1이 되어 출력되었다. 


## Publish

Publish - Subscribe 패턴

```js
const express = require('express')
const redis = require('redis')

const publisher = redis.createClient()

const app = express()

app.get('/', (req, res) =>{
    const data = {
        full : 'node'
    }
    publisher.publish("subscriber-notify", JSON.stringify(data))
    res.send("Publisher sent an event via Redis")
    
})

app.listen(8000, () => `Running at PORT 8000`)
```


## Subscribe

새로운 데이터를 구독자는 해당하는 피드에 대해서 받게 된다. 

이러한 받게 되는 것에 대해서 구현하도록 한다.

```js
const express = require('express')
const redis = require('redis')

const subscriber = redis.createClient()

subscriber.on('message', (channel, message) =>{
    console.log(`Received data : ${message}`)
}) 

subscriber.subscribe('subscriber-notify')

const app = express()
let count = 0

app.get('/', (req, res) =>{
    res.send(`Subscriber ${++count}`)
})

app.listen(6000, ()=>{
    console.log(`Running at port 6000`);
})
```

## 실무 프로젝트


```js
'use strict'
const express = require('express')
const fetch = require('node-fetch')
const redis = require('redis')

const app = express()

const client = redis.createClient()

client.on('message', (err) =>{
    console.error(`Error : ${err}`)
})

app.get('/cache', (req, res) =>{
    const redisKey = 'post:thumbnailUrl'

    return client.get(redisKey, (err, res) =>{
        if(err){
            console.error(err);
        }

        if(res){
            // 캐시가 존재한다 -
            return res.json({type : 'cached', data : JSON.parse(res)})
        }else{
            // 캐시가 없을 경우에, 캐시를 set하는 로직을 써주면 된다.
            fetch('https://jsonplaceholder.typicode.com/photo')
            .then(res => res.json())
            .then(res =>{
                // set + expire - 세팅하고 만료시키는 것 
                client.setex(redisKey, 3000, JSON.stringify(res))
                return res.json({type : 'onfly', data : res})
            })
        }
    })
})

const PORT = 3000
app.listen(PORT, () => console.log(`App running at ${PORT}`))
```

