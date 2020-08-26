# 실무프로젝트 2

## Headerless

UI가 없이 핵심 요소만 있다는 것

Headerless CMS 

strapi

`npx create-strapi-app project --quickstart`

## MongoDB

```js
// pool.js
const { MongoClient } = require('mongodb')
const url = 'mongodb://localhost:27107'

const client = new Promise((resolve, reject) =>{
    MongoClient.connect(url, {
        useNewUrlParser: true,
        useUnifiedTopology: true
    }, (err, client) =>{
        if(err){
            reject(err)
        }
        resolve(client)
    })
})

module.exports = client
```


```js
// insert.js
const pool = require('./pool')

const insert = async () =>{
    const db = (await client).db('study')
    const collection = db.collection('mongo')
    collection.insertOne({title : 'node'}, (err, result) =>{
        if(err){
            throw err
        }
        console.log(result);
    })
}
```

```js
// update.js
const client = require('./pool')

const update = async () =>{
    const db = (await client).db('study')
    const collection = db.collection('mongo')
    collection.updateOne({title:'node'},{'$set': {title:'react'}}, (err, result) =>{
        if(err){
            throw err
        }
        console.log(result)
    })
}

module.exports = update
```

```js
// delete.js
const client = require('./pool')

const deleteOne = async () =>{
    const db = (await client).db('study')
    const collection = db.collection('mongo')
    collection.deleteOne({title:'node'}, (err, item) =>{
        if(err){
            throw err
        }
        console.log(item)
    })
}

module.exports = deleteOne
```

```js
// find.js
const client = require('./pool')

const finde = async () =>{
    const db = (await client).db('study')
    const collection = db.collection('mongo')
    collection.finde({title:'node'}, (err, item) =>{
        if(err){
            throw err
        }
        console.log(item)
    })
}

module.exports = find
```


## TDD(Test Driven Development)

npm i mocha --save-dev

```js
// /test/db.js
const assert = require('assert')
const insert = require('../db/insert')
const find = require('../db/find')
const update = require('../db/update')
const deleteOne = require('../db/delete')
const insertMany = require('../db/insertMany')

describe('MongoDB Test', () =>{
    it('#insert', async () =>{
        const res = await insert({test : 'something else'})
        assert(res) // res가 제대로 리턴이 되었는지 
    })

    it('#insertMany', async () =>{
        const res = await insertMany([
            {test : 'something else'},
            {anotherTest : 'this is an another test'}
        ])
        assert(res) // res가 제대로 리턴이 되었는지 
    })

    it("#find All" ,async () =>{
        const res = await find()
        assert(res)
    })

    it("#find Specific" ,async () =>{
        const res = await find({test : 'something else'})
        // console.log(res);
        assert(res)
    })

    it("#update", async () =>{
        const res = await update({test: 'something else'}, {test : 'new data'})
        // console.log(res.result);
        assert(res)
    })

    it("#deleteOne", async () =>{
        const res = await deleteOne({test: 'new data'})
        // console.log(res.result);
        assert(res)
    })
})
```

`npm test => "test": "./node_modules/mocha/bin/mocha"` test를 mocha를 실행시키게 하였다. 

결과는 다음과 같다. 

```
  MongoDB Test
    ✓ #insert
    ✓ #insertMany
    ✓ #find All
    ✓ #find Specific
    ✓ #update
    ✓ #deleteOne
```

## CMS


`npm i express cookie-parser --save`

`npm i express-async-errors`

'use strict'

```js
// server.js
'use strict'

const http = require('http')
const express = require('express')
const cookieParser = require('cookie-parser')
const { finished } = require('stream')

const { find, insert, insertMany, delete: deeleteOne, update } = require('./db')
require('express-async-errors')

class ApiServer extends http.Server{
    constructor(config){
        const app = express()
        super(app)
        this.config = config
        this.app = app
    }

    async start (){
        this.app.post('/:collection/:item', async (req, res) =>{// Create
            const { colleciton } = req.params
            const { newData } = req.body
            const result = await insert(newData, colleciton)
            res.send(result)
        }) 
        this.app.get('/:collection/:data', async (req, res) =>{ // Read
            const { collection, data } = req.params
            const { c } = req.query
            const result = await find(c, collection)
            res.send(result)
        })
        this.app.put('/:collection/:id', async (req, res) =>{// Update
            const { collection, id } = req.params
            const { newData } = req.body
            const result = await update(id, newData, collection)
            res.send(result)
        }) 
        this.app.delete('/:collection:id', async (req, res) =>{// Delete
            const { collection, id } = req.params
            const { condition } = req.body
            const result = await deeleteOne(id, collection)
            res.send(result)
        }) 
    
        return this
    }
}

module.exports = ApiServer
```


## main

`npm i body-parser --save`

```js
// main.js
'use strict'

const { createServer } = require('./server')

async function main(config){
    const server = await createServer(config)
    const port = config.port || 3000
    server.listen(port, () =>{
        console.log(`Running at ${port}`);
    })
}

main()
```

## JSON Data Migration

```js
// init.js
const path = require('path')
const fs = require('fs');

const dirPath = path.join(__dirname, 'json') // 현재와 json 디렉토리를 조인한다.

fs.readdir(dirPath, (err, files) =>{
    if(err){
        console.error(err);
        return
    }

    files.forEach(file => {
        const { collection, data } = require(`${dirPath}//${file}`)
        console.log(collection);
    })

})
```

비동기적으로 데이터베이스와 연동하기 위해서 좀 더 개선!

```js
const path = require('path')
const fs = require('fs');
const insert = require('./db/insert')

const dirPath = path.join(__dirname, 'json') // 현재와 json 디렉토리를 조인한다.

fs.readdir(dirPath, async (err, files) =>{
    if(err){
        console.error(err);
        return
    }

    for(const file of files){ // forEach에서는 비동기를 사용할 수 없으므로 for of 구문을 사용한다.
        const { collection, data } = require(`${dirPath}//${file}`)
        await insert(data, collection)
    }
})
```