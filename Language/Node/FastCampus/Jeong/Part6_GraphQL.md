# GraphQL

## GraphQL 소개

Graph와 query language의 3개지 단어가 합쳐진 용어라고 보면 된다. 

명시적으로 원하는 데이터를 가져올 수 있는, 전체를 그래프로 보는...

SQL은 대용량 트래픽을 처리하는 과정중에 오버 패칭(더 많은 정보를 가져오는 것)이나 언더 패칭(정보를 덜 가져오는 것)이 빈번하게 일어난다. 

GraphQL은 이러한 단점을 보완한다. Domain specific language기 때문에 한 번의 API 호출로써 원하는 데이터를 정확하게 리턴한다.


## GraphQL vs REST

예를 들어 특정한 회원의 포스트와 팔로워를 가져오기 위해서는 

회원의 id, posts, followers에 대한 쿼리를 작성해서 3번의 반복을 통해서 가져온다.

또한 회원 정보의 id만 가져오고 싶어도 회원의 다른 정보들도 가져오는 비효율적인 오버 패칭들이 이루어진다. 

(기존의 REST API의 문제점들,,,)

버전 관리 - 유지보수가 어렵다.

---

모든 API가 하나의 그래프를 형성하는 듯 하게 호출한다. 모든 데이터가 그래프로 연결되있다. 

명백하게 쿼리에 적힌 데이터들만 반환해준다.

```query
query{
    user(id : asdfse){
        name
        posts{
            title
        }
        followers(last : 3){
            name
        }
    }
}


{
    "data":{
        "user":{
            "name": "Mary",
            "posts":[
                {title : "Learn GraphQL today"}
            ],
            "followers":[
                {name : "John"},
                {name : "Alice"},
                {name : "Sarah"}
            ]
        }
    }
}
```

## GraphQL 입문

```js
const express = require('express')
const bodyParser = require('body-parser')
const { graphExpress, graphiqlExpress } = require('apollo-server-express')
const { makeExecutableSchema } = require('graphql-tools')

const PORT = 8080
const server = express()

const typeDefs = `
    type Lang {
        id : Int,
        name : String! 
    }
    type Query {
        getLangs(name : String): [Lang]
    }
`
// !을 붙임으로써 not null이 보장된다. 
// 위의 것은 스키마이고 아래의 Query는 말 그대로 쿼리문이다. 

const langs = [{
    id:0,
    name: 'Node'
},{
    id:1,
    name: 'Python'
}]

const resolvers = { 
    Query:{
        getLangs: () => langs
    }
}

const schema = makeExecutableSchema({
    typeDefs,
    resolvers
})

server.use('/graphql', bodyParser.json(), graphExpress({
    schema
}))

server.use('/graphiql', graphiqlExpress({
    endpoint : '/graphiql'
}))

server.listen(PORT, () => console.log(`Running at ${PORT}`))
```

## Resolver

```js
const resolvers = {
    Query : {
        getCountries( , ...args){
            return countries.getCountriesByName(args.name)
        }
    }
}

export default resolvers 
```

