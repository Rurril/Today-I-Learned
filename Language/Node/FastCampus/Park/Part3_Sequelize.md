# Sequelize

## Sequelize 란

oRM(Object-Relational Mapping) nodejs로 mysql 또는 postgresql(db)를 제어할 수 있게 해준다.

모델들이 어떤 구조로 어떤 데이터로 되어있는지를 코드를 통해서도 알 수가 있다. 

## dotenv 설정

(닷 이엔뷔-라고 읽는다)

환경변수들을 따로 설정해놓아서 편하게 하는 것.

```
DATABASE = "데이터베이스명"
DB_USER = "root"
DB_PASSWORD = "패스워드"
DB_HOST = "DB호스트" 
```

위와 같이 설정해서 

`process.env.DB_PASSWORD`이렇게 접근이 가능하다고 한다. 

## Database 설정



## DB 접속


`npm install mysql2`

`npm install sequelize@4.42.0`

```js
const db = require('./models'); // 가장 먼저 index.js를 가져온다. 

// ---

dbConnection(){
    // DB authentication
    db.sequelize.authenticate()
    .then(() => {
        console.log('Connection has been established successfully.');
    })
    .then(() => {
        console.log('DB Sync complete.');
    })
    .catch(err => {
        console.error('Unable to connect to the database:', err);
    });
}
```

db를 연동해서 `.env` 파일을 통해서 참조해서 가져와서 DB에 연동하도록 한다. 

```js
//index.js

const sequelize = new Sequelize( process.env.DATABASE,
process.env.DB_USER, process.env.DB_PASSWORD,{
    host: process.env.DB_HOST,
    dialect: 'mysql',
    timezone: '+09:00', //한국 시간 셋팅
    operatorsAliases: Sequelize.Op,
    pool: {
        max: 5,
        min: 0,
        idle: 10000
    }
});
```

index.js에서 db로 연동하는 부분. Sequelize를 사용하였다. 


## 모델 작성

`create table Products`라고 직접 쿼리를 쓸 수도 있다. 

```js
// Products.js
module.exports = function(sequelize, DataTypes){
    const Products = sequelize.define('Products',
        {
            id: { type: DataTypes.INTEGER, primaryKey: true, autoIncrement: true },
            name : { type: DataTypes.STRING },
            price : { type: DataTypes.INTEGER },
            description : { type: DataTypes.TEXT }
        }
    );
    return Products;
} 
```

다음과 같이 테이블 모델을 만들어서 적용할 수도 있다. 

적용해서 실행시키면

```
Executing (default): CREATE TABLE IF NOT EXISTS `Products` (`id` INTEGER auto_increment , `name` VARCHAR(255), `price` INTEGER, `description` TEXT, `createdAt` DATETIME NOT NULL, `updatedAt` DATETIME NOT NULL, PRIMARY KEY (`id`)) ENGINE=InnoDB;
Executing (default): SHOW INDEX FROM `Products`
```

다음과 같이 실행되는 결과를 볼 수 있다. (존재하지 않기에)

## DB 입력

`INSERT` 쿼리를 사용하는 챕터

`GET / admin/products/write`

`POST / admin/products/write`

이렇게 두 부분을 작성

```js
exports.post_products_write = ( req , res ) => {
    models.Products.create({
        name : req.body.name,
        price : req.body.price ,
        description : req.body.description
    }).then( () => {
        res.redirect('/admin/products');
    });
}
```
POST를 통해서 필요한 정보들을 받고, 그것들을 통해서 redirect를 한다. 

```
Executing (default): INSERT INTO `Products` (`id`,`name`,`price`,`description`,`createdAt`,`updatedAt`) VALUES (DEFAULT,'사과','1000','먹음직스럽다. 지금 먹고싶다.','2020-07-15 15:43:59','2020-07-15 15:43:59');
POST /admin/products/write 302 122.552 ms - 74
GET /admin/products 304 2.333 ms - -
```

결과가 나온 것을 볼 수 있다. 

```m
+----+------+-------+------------------------------+---------------------+---------------------+
| id | name | price | description                  | createdAt           | updatedAt           |
+----+------+-------+------------------------------+---------------------+---------------------+
|  1 | 사과 |  1000 | 먹음직스럽다. 지금 먹고싶다. | 2020-07-15 15:43:59 | 2020-07-15 15:43:59 |
+----+------+-------+------------------------------+---------------------+---------------------+
```


## DB 조회

```js
// admin.ctrl.js
exports.get_products = ( _ , res) => {
    models.Products.findAll({

    }).then( (products) => {
        // DB에서 받은 products를 products변수명으로 내보냄

        res.render( 'admin/products.html' ,{ products : products });
        // res.render( 'admin/products.html' ,{ products }); // Key와 Value 값이 같다면 하나로 해도 된다. 
        
    });
}
```

## 상세 페이지 작성

```js
// admin.ctrl.js

exports.get_products_detail = ( req , res ) => {
    models.Products.findByPk(req.params.id).then( (product) => {
        res.render('admin/detail.html', { product: product });  
    });
}; 
```

{id}를 통해서 테이블에서 값을 꺼내올 수 있어야 하기에, 위와 같이 작성하였다.

findByPk라는 함수를 통해서 id가 pk이므로 꺼내올 수 있게 하였다. 또한, detail.html으로 render해서 출력하도록 !




## Moment.js 적용

```js
// Format Dates
moment().format('MMMM Do YYYY, h:mm:ss a'); // July 15th 2020, 5:22:12 pm
moment().format('dddd');                    // Wednesday
moment().format("MMM Do YY");               // Jul 15th 20
moment().format('YYYY [escaped] YYYY');     // 2020 escaped 2020
moment().format();                         
```

와 같이 사용해서 할 수가 있다.

## DB 수정

```js
//admin.ctrl.js

exports.get_products_edit = ( req , res ) => {
    //기존에 폼에 value안에 값을 셋팅하기 위해 만든다.
    models.Products.findByPk(req.params.id).then( (product) => {
        res.render('admin/write.html', { product : product });
    });
};
exports.post_products_edit = ( req , res ) => {

    models.Products.update(
        {
            name : req.body.name,
            price : req.body.price ,
            description : req.body.description
        }, 
        { 
            where : { id: req.params.id } 
        }
    ).then( () => {
        res.redirect('/admin/products/detail/' + req.params.id );
    });
} 
```

get_products_edit에서 write.html을 활용해서 그 부분에 대해서 폼을 작성하도록 하며, post에서 UPDATE를 통해서 말 그대로 값에 대한 업데이트를 진행한다. 

## DB 삭제

```js
// admin.ctrl.js
exports.get_products_delete = ( req , res ) => {
    models.Products.destroy({
        where: {
            id: req.params.id
        }
    }).then( () => {
        res.redirect('/admin/products');
    });
}; 
```

지금까지 해왔던 것과 마찬가지로, index.js에 routing을 위해서 작성하며, 

함수를 만들어서 destory를 하도록 만들었다. 

## 피드백

갑자기 아무런 설명도 없이 mysql을 시작하는데 좀 당황스럽네요.
