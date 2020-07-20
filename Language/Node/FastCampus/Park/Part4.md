# Promise

## Promise란

promise 만들기

1. resolve와 reject를 인자로 가지는 함수를 만든다.
2. 내가 원하는 시점을 resolve로 받아온다. 

```js
const aa = new Promise((resolve, reject) =>{
    resolve(console.log('프라미스 이행!'));
});

aa.then(() => {
    console.log("프라미스 실행 완료");
});
```

```
프라미스 이행!
프라미스 실행 완료
```

의 순서대로 출력이 된 것을 볼 수 있다. 

조금 변형해서 인자를 받아온다면

```js
const aa = new Promise((resolve, reject) =>{
    resolve("Promise 123");
});

aa.then((result) => {
    console.log(result);
});
```

result로 인자를 받아서 출력하는 코드가 가능해진다. 

resolve를 기다리고 그 다음에 then()이 실행이 되는 것. 

> `reject`는 에러처리를 위한 인자.




## Promise Chaining, Promise all

```js
const aa = new Promise((resolve, reject) =>{
    reject("ERROR");
});

aa.then((result) => {
    console.log(result);
}).catch((err) =>{
    console.log(err);
});
```

reject를 통해서 에러를 발생시킨다면, catch를 통해서 에러만 따로 잡아서 출력해주는 등 다양한 방식으로 에러처리를 할 수 있다. 


또한 프로미스들을 동시에 실행시키기 위해서 promise all을 사용한다.

```js
p1.then( result1 => {
    console.log("p1 = " + result1.p1_text);
    return p2; // 리턴으로 promise 객체를 넘겨줌으로써 then으로 사용할 수 있게 한다. 
}).then( result2 =>{
    console.log("p2 = " + result2.p2_text);
});

// ----
Promise.all([ p1,p2 ]).then((result)=>{
    console.log("p1 = " + result[0].p1_text);
    console.log("p2 = " + result[1].p2_text);
})
```

윗부분의 코드를 통해서 실행시켜도 되지만, 아래 부분의 코드처럼 한 번에 인자로 받아서 실행시킬 수도 있다. 

## async await

2개의 Product를 동시에 받아오기 위해서 동기화를 진행해서 실행한다.

```js
const models = require('./models');

async function getProducts(){
    const product1 = await models.Products.findByPk(1);
    console.log(product1.dataValues);

    const product3 = await models.Products.findByPk(3);
    console.log(product3.dataValues);

}

getProducts();
```

이렇게 실행시키면, id가 1과 3인 제품을 가져와서 출력해주는 것을 볼 수 있다.

> 참고로, 가져와서 사용하기 위해서는 sequalize 특성상 .dataValues를 사용해야한다고 한다. 

직접 찍어보니까, json 형식으로 

Products안에 {dataValues, _previousDataValues, _changed, _modelOptions .. 등} 다양하게 있기 때문에 원하는 값인 dataValues만 가져와서 출력하는 것.


```js
exports.get_products = async( _ , res) => {
    // models.Products.findAll({

    // }).then( (products) => {
    //     res.render( 'admin/products.html' ,{ products : products });
    // });

    try{
        const products = await models.Products.findAll();
        res.render( 'admin/products.html' ,{ products : products });
    }catch(e){

    }
}
```

위의 주석 처리된 방식에서 아래처럼 바꿀 수 있다. (보기가 깔끔하다)

실행과 과정 간의 관계를 좀 더 직관적으로 볼 수가 있다. 

## 피드벡

await가 무엇인지, 동기화 비동기화 프로그래밍에 대해서 제대로 알지도 못하고 그냥 사용만 하고 따라가는 것이라서 무엇이 어떻게 다른지 원리가 무엇인지에 대해서 하나도 모르겠습니다.

