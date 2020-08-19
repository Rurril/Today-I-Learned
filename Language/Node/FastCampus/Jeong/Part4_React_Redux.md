# React & Redux

## React 개발 환경 설정

사용할 것은 npx다.

npm과 npx의 차이점은 중요하다 

- npm은 node_modules라는 폴더를 만들어서 설치한다.
- npx는 실행하는 것이 목적이기 때문에, 해당하는 디렉토리에 설치하지 않고 실행할 수 있는 것이 장점이다. 

`npx create-react-app study` 를 터미널에 입력
- study는 다른 이름으로 설정해도 무방(프로젝트 이름)

이제 study - 폴더로 이동해서 `npm start`를 입력하면 react 프로젝트가 실행된다. 


## 개발을 위한 ES6+

ES6 이후의 문법 

JSX : Javascript + XML

템플릿 언어를 사용하면, 모듈에 독립적으로 사용하기 어려워진다.

## React 소개

대용량 서비스를 운영하기 적합하다고 평가받고, 널리 쓰이는 React

장점 !
1. Virtual DOM - Document Object Model
2. Onl View, NO MVC(feat. 단방향 데이터 흐름) - Model View Controller : 기존의 angular가 이 방식을 사용한다. 
3. Reusable Components
4. Hot reloading
5. Server Side Rendering(feat. SEO)

--- 

SPA : Single Page Application - 사용자가 링크를 클릭하거나 데이터를 조회하기 위해서 페이지를 이동하는 작업 없이, 현재 페이지에서 모든 작업이 이루어지는 것.

SPA가 아니라면, 리로드 될 때마다 모든 DOM 객체들이 새롭게 랜더링된다.

예를 들어 instagram이 SPA가 아닌 경우다. 업데이트 된 DOM만(전체를 바꿀 필요가 없다) 바뀌는 방법이라면 client의 관점에서 매우 큰 성능차이가 체감된다. 

---

MVC 방식은 확장이 어렵다고 페이스북에서 결론을 내려서 '데이터 흐름이 단방향인 방식'을 적용한 것. 

## React 특징

> Reusable Components

Library와 Framework는 많이 다르다.

리엑트가 라이브러리이기 때문에 갖는 장점
1. 퍼포먼스가 좋다.
2. 최소한의 기능을 제공하고 필요한 부분에 대해서는 다른 것을 사용할 수 있다.
3. 경량화가 가능한 라이브러리라는 것은 큰 장점이다.

재사용 가능한 컴포넌트라는 것은 매우 중요하다. 
- 최소한의 기능만 코어 모듈로 만들어놓고, 사용자 층에서 재사용 가능하도록 함으로써 유저들이 만든 다양한 기능이 있다. 

> Hot reloading

코딩한 결과를 확인하기 위해서 새로고침 할 필요없이, 웹 페이지가 자동으로 갱신이 되는 것.

> Server Side Rendering

기존에 SPA가 갖는 검색 최적화 문제 SEO를 해결할 수 있다.

랜더링을 일반적으로 클라이언트에서 하지만, 서버 - node.js 에서 할 수 있게 해주는 것. 

## JSX와 Fragment


표현하고자 하는 데이터를 넘길 때, props를 통해서 전달 할 수 있다. 

```js
const Head = props => <h1>{props.title}</h1>
```

<> 와 </> 를 통해서 아무것도 적히지 않은 것으로 감싸는 것. 이것이 Fragment

JSX는 하나의 랩으로 감싸져 있어야 하므로 fragment를 사용해서 감싸준다.

```js
import React from 'react';
import "./App.css";

const Head = props => <h1>{props.title}</h1>

function App(){
    return (
        <>
            <Head title = "this is a title" name = "this is a name"/>
            <Head title = "this is a title" name = "this is a name"/>
        </>
    )
}

export default App;
```

## Rendering & 심화

```js
import React from 'react';
import "./App.css";

// 랜더는 함수를 반환한다.
// 리엑트 컴포넌트 또한 함수를 반환한다.
const Loading = () =>{ // 이름의 첫 글자를 대문자로 해야한다. 
    <div>Loading...</div>
}

class LoadingComponent extends React.Component{
    constructor(props){
        super(props)
        this.state ={
            loading : false
        }

    }

    comment(){
        const con = 1
        const res = con > 0 ? true : false
        const and = loading && (<div>loading...</div>)

    }
    render(){
        const { loading } = this.state
        return (
            <> 
                {
                    loading && <Loading />
                }
            </>
        )
    }
}
```

## React Lifecycle

상태가 있는 리엑트 컴포넌트에 대해서 이해하고 넘어갈 것

모든 요소를 view로 받기 때문에 데이터의 단방향성을 보장하면서, 단일적으로 관리하기 위한 로직이 있다. 

리엑트는 모두 View이다. 

컴포넌트를 생성 할 때는 constructor -> componentWillMount -> render -> componentDidMount 순으로 진행된다. 

컴포넌트를 제거 할 때는 componentWillUnmount 만 실행된다. 

```js
import React from 'react';
import "./App.css";

class LifeCycle extends React.Component{
    constructor(props){
        super(props)
    }

    componentWillMount(){

    }

    render(){
        return(<></>)
    }

    componentDidMount(){

    }

    componentWillUnmount(){
        // 해당하는 모든 로직이 필요없기 때문에 초기화하는 곳 
        // 더 이상 setState에 접근할 수 없다. 
    }
}
```


## Props vs State

```js
import React from 'react';

// Stateless : 상태가 없는
// State : 상태 state class - 해당하는 컴포넌트 안에서만 사용하기 위한 것
// props : 상위 계층의 컴포넌트와 데이터 교환을 위해서 사용 

class Fast extends React.Component{
    constructor(props){
        super(props)
        this.state = { // props의 것을 state에서도 사용할 수 있게 한다. 
            props, 
            lang : 'javascript',
            date : new Date()
        }
    }

    render(){
        const { lang, date } = this.state
        return (
            <div>{lang}</div>
        )
    }
}

export default App;
```

## Event Handling

```js
import React from 'react';

function App(){
    const handleClick = (e) =>{
        e.preventDefault() // 중복된 실행이 될 수 있기 때문에 
        console.log('button is clicked')
    }
    return (
        <button onClick={handleClick}>this is a button</button>
    )
}
```

## Key Warnings

```js
function App(){
  const iter = [0,1,2]
  return (
    // 키 값을 어떤 조건, 분기에서 업데이트 하는지 설정할 수 있도록 기회를 주는 것. - 데이터의 중복성이 없는 유일한 값으로 설정해주어야 한다. 
    // map에서 주어지는 index를 key값으로 사용하는 것은 매우 위험하다.
    // 똑같은 iteration이 두 번 이상 이어질 수 있기 때문에, index가 중복될 가능성이 매우 높다 - key와 같은 고유값으로 사용되기 어렵다. 
    <div>
      {
      iter.map(item => <h1 key={item}>item</h1>)
      }
    </div>
    
  )
}
```

키 중복으로 인한 경고... 

## setState 실무 테크닉

```js
class Timer extends React.Component{
  constructor(props){
    super(props)
    this.state = {
      time : new Date()
    }
  }

  componentDidMount(){
    // Mount가 된다 - UI가 초기화 된다.
    this.tick() // 초당 업데이트 되는 UI 구현 
  }

  tick(){
    this.setState({ // 비동기적이기 때문에, 코드 실행 순서가 보장되지 않는다. 
      time : new Date()
    }, () =>{
      console.log(this.state)
    }) // callback이 있다 ? 비동기 코드이다. 
  }

  render(){
    const { time } = this.state
    return (
      <div>
        {time.date.toLocaleTimeSTring()}
      </div>
    )
  }
}
```

## React - state hook

모든 것은 함수로 시작해서 함수르 끝을 낼 수 있다.

react hook - 클래스 사용없이 상태 값과 여러가지 react의 기능들을 사용할 수 있다. 

```js
import React, { useState } from 'react';
import logo from './logo.svg';
import './App.css';


function App(){
  // 관행적으로, 변수가 나오고 그것에 대한 set으로 함수를 적는다. -- code convention
  const [count, setCount] = useState(0) // 초기값으로 0으로 설정 
  return (
    <div className = "App">
      <header className = "App-header">      
        <button onClick={() => setCount(count + 1)}>{count}</button>
      </header>
    </div>
  )
}
```

버튼을 누르면 카운트가 1씩 추가되는 코드 


## state hook 실습 프로젝트

```js
import React, { useState } from 'react';
import logo from './logo.svg';
import './App.css';

const Todo = ({ todo, index, completeTodo, removeTodo }) =>{
  return (
    <>
      <div 
        className="todo"
        style={{ textDecoration: todo.isCompleted ? 'line-through' : ''}}  
      >
        {todo.text}
      </div>
      <div>
        <button onClick={() => completeTodo(index)}>Complete</button>
        <button onClick={() => removeTodo(index)}>X</button>
      </div>
    </>
  )
}

const TodoForm = ({ addTodo }) =>{
  const [value, setValue] = useState('') // undefined가 아닌 아무것도 없는 값으로 설정. - undefined는 유저가 그것을 알 수 없기 때문 
  const handleSubmit = e =>{
    e.preventDefault(); // Event bubbling을 방지 - 해당 이벤트가 중첩되어 발생될 수 있기 때문 
    if(!value)return
    addTodo(value)
    setValue('')
  }
  return(
    <form onSubmit={handleSubmit}>
      <input
        type="text"
        className="input"
        value={value}
        onChange={e => setValue(e.target.value)}
      />
    </form>
  )
}

const App = () => {
  const [todo, setTodo] = useState([]) // 비어있는 array로 초기화 
  
  const addTodo = text =>{
    const newTodos = [...todo, { text }]
    setTodo(newTodos)
  }

  const completeTodo = index =>{
    const newTodos = [...todo]
    newTodos[index].isCompleted = true
    setTodo(newTodos)
  }

  const removeTodo = index =>{
    const newTodos = [...todo] // 기존의 todo를 복제 
    newTodos.splice(index, 1)
    setTodo(newTodos)
  }

  return (
    <div className = "App">
      <div className="todo-list">
        {
          todo.map((item, index) =>(
            <Todo 
              key={item}
              index={index}
              todo={todo}
              completeTodo={completeTodo}
              removeTodo={removeTodo}
            />
          ))
        }
        <TodoForm addTodo={addTodo}/>
        
      </div>
    </div>
  )
}
```

## Effect Hook 실무 활용

먼저 npm install --save axios 

```js
import React, { useState, useEffect } from 'react';
import axios from 'axios'
// import logo from './logo.svg';
// import './App.css';

const App = () =>{
  const [data, setData] = useState({ hits : [] })
  const [query, setQuery] = useState('react')
  
  useEffect(() =>{ 
    let completed = false
    
    async function get(){
      const result = await axios(`https://hn.algolia.com/api/v1/search?query=${query}`)
      if(!completed)setData(result.data)
    }

    get()

    return () =>{
      completed = true
    };
  }, [query]) // 감시에 대한 대상이 query를 할당 
  return(
    <>
      <input value={query} onChange={e => setQuery(e.target.value)}/>
      <ul>
        {data.hits.map(item => (
          <li key={item.objectId}>
            <a herf={item.url}>{item.title}</a>
          </li>
        ))}
      </ul>
    </>
  )
}
```

input value인 query가 바뀜으로써 virtual DOM이 랜더링된다!

## Flux 아키텍처에 대한 이해

Action > Store > React > Action

데이터가 단방향으로 진행된다.

Store <-> Reducers

프로그래밍에서 side effect는 상태를 변경하는 것이다. - 데이터 흐름의 변화를 유발하는 것



## Redux 설치

## Redux 개념적 접근

## Redux 기본

## Redux Component

## React Router

## styled-components

## Side effects 개념적 접근

## Redux 실습 프로젝트