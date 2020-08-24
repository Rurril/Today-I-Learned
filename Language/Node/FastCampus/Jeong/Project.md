# 실무 프로젝트 1

## Microservices에 대한 이해

비즈니스 로직 별 기능 별로 서비스를 구성하는 것이 Microservices 아키텍쳐의 기본

## Serverless에 대한 이해

물리적인 서버에 대해서 고민하지 않아도 된다.

해당하는 코드를, 함수 단위, 비즈니스 로직 단위로 구성하는 것을 고민하면 된다.


## Serverless Framework 기초

특정한 프로젝트 단위로 설치하는 것보다 -g 로 시스템 전역에서 사용할 수 있도록 사용하는 것이 편리하다.

Serverless Framework를 사용하면 굳이 express를 사용하지 않아도 된다. 

무조건 적으로 모든 데이터를 serverless function을 사용하면 좋지 않을 수도 있다. 

## Websocket vs socket.io

Websocket은 브라우저에서 구현되어 있지 않으면 사용할 수 없다.

socket.io는 Websocket의 구현체는 아니지만, 기본적인 폴링 방식으로 대체제로써 사용할 수 있다.

`const socketIO = websocket || polling` 이런 느낌

## 프로젝트

```js
// server.js
const express = require('express')
const path = require('path')
const fs = require('fs')
const http = require('http')
const https = require('https')
const sio = require('socket.io')
const favicon = require('serve-favicon')
const compression = require('compression')

const app = express(),
    options = { 
        key: fs.readFileSync(__dirname + '/rtc-video-room-key.pem'),
        cert: fs.readFileSync(__dirname + '/rtc-video-room-cert.pem')
    },
    port = process.env.PORT || 3000,
    server = process.env.NODE_ENV === 'production' ?
        https.createServer(app).listen(port)
        : http.createServer(options, app).listen(port),
    io = sio(server)

app.use(compression())  
app.use(express.static(path.join(__dirname, 'dist')))
app.use((req, res) => res.sendfile(__dirname + '/dist/index.html'))
app.use(favicon('./dist/favicon.ico'))
app.disable('x-powered-by')
io.sockets.on('connection', socket =>{
    let room = ''

    // 채널의 클라이언트들에게 보낸다. 
    socket.on('message', message => socket.broadcast.to(room).emit('message', message))
    socket.on('find', ()=>{
        const url = socket.request.headers.referer.split('/')
        room = url[url.length - 1]
        const sr = io.sockets.adapter.rooms[room]
        if(sr === undefined){
            // 만들어진 방이 없을 때 
            socket.join(room)
            socket.emit('create')
        }else if(sr.length === 1){ 
            socket.emit('join')
        }else{
            socket.emit('full', room)
        }
    })
    socket.on('auth', data =>{
        data.sid = socket.id
        socket.broadcast.to(room).emit('approve', data)
    })
    socket.on('accept', id =>{
        io.sockets.connected[id].join(room)
        io.in(room).emit('bridge')
    })
    socket.on('reject', () => socket.emit('full')) // 가득 찼으므로 거절
    socket.on('leave', () => { // 방을 떠나는 기능
        socket.broadcast.to(room).emit('hangup')
        socket.leave(room)
    })
})
```

```js
// /src/index.js
import React from 'react'
import { render } from 'react-dom'
import { Provider } from 'react-redux'
import store from './store'
import { BrowserRouter, Switch, Route } from 'react-router-dom'
import Home from './containers/HomePage'
import Room from './containers/RoomPage'
import NotFound from './components/NotFound' // 홈페이지를 찾을 수 없을 때 표시하기 위함
import styles from './app.css'


//각각의 경로에 대해서 표시할 컴포넌트를 랜더링해준다. 
render(
    <Provider store={store}>
        <BrowserRouter>
            <Switch>
                <Route exact path="/" component={Home}/>
                <Route path="/r/:room" component={Room}/>
                <Route path="*" component={NotFound}/>
            </Switch>
        </BrowserRouter>
    </Provider>
    document.getElementById('app')
)
```

```js
// /src/components/Home.js 
import React from 'react';
import { PropTypes } from 'prop-types';
import { connect } from 'react-redux';
import { Link } from 'react-router-dom';

const Home = props =>
  <div className="home">
    <div>
      <h1 itemProp="headline">Webrtc Video Room</h1>
      <p>Please enter a room name.</p>
      <input type="text" name="room" value={ props.roomId } onChange={props.handleChange} pattern="^\w+$" maxLength="10" required autoFocus title="Room name should only contain letters or numbers."/>
      <Link className="primary-button" to={ '/r/' + props.roomId }>Join</Link>
      <Link className="primary-button" to={ '/r/' + props.defaultRoomId }>Random</Link>
      { props.rooms.length !== 0 && <div>Recently used rooms:</div> }
      { props.rooms.map(room => <Link key={room} className="recent-room" to={ '/r/' + room }>{ room }</Link>) }
    </div>
  </div>;

Home.propTypes = {
  handleChange: PropTypes.func.isRequired,
  defaultRoomId: PropTypes.string.isRequired,
  roomId: PropTypes.string.isRequired,
  rooms: PropTypes.array.isRequired
};

const mapStateToProps = store => ({rooms: store.rooms});

export default connect(mapStateToProps)(Home);
```

```js
///src/containers/Homepage.js
import React, { Component } from 'react'
import { PropTypes } from 'prop-types';
import Home from '../components/Home';

class HomePage extends Component {
  constructor(props) {
    super(props);
    this.defaultRoomId = String(new Date() - new Date().setHours(0, 0, 0, 0));
    this.state = { roomId: this.defaultRoomId };
    this.handleChange = this.handleChange.bind(this);
  }
  handleChange(e) {
    this.setState({ roomId: e.target.value });
  }
  render(){
    return (
      <Home
        defaultRoomId={this.defaultRoomId}
        roomId={this.state.roomId}
        handleChange={this.handleChange}
      />
    );
  }
}

HomePage.contextTypes = {
  router: PropTypes.object
};

export default HomePage;
```

```js
// /src/container/Roompage.js
import React, { Component } from 'react';
import MediaContainer from './MediaContainer'
import CommunicationContainer from './CommunicationContainer'
import { connect } from 'react-redux'
import store from '../store'
import io from 'socket.io-client'

class RoomPage extends Component {
  constructor(props) {
    super(props);
    this.getUserMedia = navigator.mediaDevices.getUserMedia({
      audio: true,
      video: true
    }).catch(e => alert('getUserMedia() error: ' + e.name))
    this.socket = io.connect();
  }
  componentDidMount() {
    this.props.addRoom();
  }
  render(){
    return (
      <div>
        <MediaContainer media={media => this.media = media} socket={this.socket} getUserMedia={this.getUserMedia} />
        <CommunicationContainer socket={this.socket} media={this.media} getUserMedia={this.getUserMedia} />
      </div>
    );
  }
}
const mapStateToProps = store => ({rooms: new Set([...store.rooms])});
const mapDispatchToProps = (dispatch, ownProps) => (
    {
      addRoom: () => store.dispatch({ type: 'ADD_ROOM', room: ownProps.match.params.room })
    }
  );
export default connect(mapStateToProps, mapDispatchToProps)(RoomPage);
```

```js
// /src/components/Communication.js
import React from 'react';
import { PropTypes } from 'prop-types';
import { Link } from 'react-router-dom';
import ToggleFullScreen from './ToggleFullScreen';

const Communication = props =>
  <div className="auth">
    <div className="media-controls">
      <Link className="call-exit-button" to="/">
        <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 36 36"  className="svg">
          <path d="M30 16.5h-18.26l8.38-8.38-2.12-2.12-12 12 12 12 2.12-2.12-8.38-8.38h18.26v-3z" fill="white"/>
        </svg>
      </Link>
      <button onClick={props.toggleAudio} className={'audio-button-' + props.audio}>
        <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 50 50" className="svg">
          <path className="on" d="M38 22h-3.4c0 1.49-.31 2.87-.87 4.1l2.46 2.46C37.33 26.61 38 24.38 38 22zm-8.03.33c0-.11.03-.22.03-.33V10c0-3.32-2.69-6-6-6s-6 2.68-6 6v.37l11.97 11.96zM8.55 6L6 8.55l12.02 12.02v1.44c0 3.31 2.67 6 5.98 6 .45 0 .88-.06 1.3-.15l3.32 3.32c-1.43.66-3 1.03-4.62 1.03-5.52 0-10.6-4.2-10.6-10.2H10c0 6.83 5.44 12.47 12 13.44V42h4v-6.56c1.81-.27 3.53-.9 5.08-1.81L39.45 42 42 39.46 8.55 6z" fill="white"></path>
          <path className="off" d="M24 28c3.31 0 5.98-2.69 5.98-6L30 10c0-3.32-2.68-6-6-6-3.31 0-6 2.68-6 6v12c0 3.31 2.69 6 6 6zm10.6-6c0 6-5.07 10.2-10.6 10.2-5.52 0-10.6-4.2-10.6-10.2H10c0 6.83 5.44 12.47 12 13.44V42h4v-6.56c6.56-.97 12-6.61 12-13.44h-3.4z" fill="white"></path>
        </svg>
      </button>
      <button onClick={props.toggleVideo} className={'video-button-' + props.video}>
        <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 50 50" className="svg">
          <path className="on" d="M40 8H15.64l8 8H28v4.36l1.13 1.13L36 16v12.36l7.97 7.97L44 36V12c0-2.21-1.79-4-4-4zM4.55 2L2 4.55l4.01 4.01C4.81 9.24 4 10.52 4 12v24c0 2.21 1.79 4 4 4h29.45l4 4L44 41.46 4.55 2zM12 16h1.45L28 30.55V32H12V16z" fill="white"></path>
          <path className="off" d="M40 8H8c-2.21 0-4 1.79-4 4v24c0 2.21 1.79 4 4 4h32c2.21 0 4-1.79 4-4V12c0-2.21-1.79-4-4-4zm-4 24l-8-6.4V32H12V16h16v6.4l8-6.4v16z" fill="white"></path>
        </svg>
      </button>
      <button onClick={ToggleFullScreen} className="fullscreen-button">
        <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 50 50" className="svg">
          <path className="on" d="M10 32h6v6h4V28H10v4zm6-16h-6v4h10V10h-4v6zm12 22h4v-6h6v-4H28v10zm4-22v-6h-4v10h10v-4h-6z" fill="white"></path>
          <path className="off" d="M14 28h-4v10h10v-4h-6v-6zm-4-8h4v-6h6v-4H10v10zm24 14h-6v4h10V28h-4v6zm-6-24v4h6v6h4V10H28z" fill="white"></path>
        </svg>
      </button>
      <button onClick={props.handleHangup} className="hangup-button">
        <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 50 50" className="svg">
          <path d="M24 18c-3.21 0-6.3.5-9.2 1.44v6.21c0 .79-.46 1.47-1.12 1.8-1.95.98-3.74 2.23-5.33 3.7-.36.35-.85.57-1.4.57-.55 0-1.05-.22-1.41-.59L.59 26.18c-.37-.37-.59-.87-.59-1.42 0-.55.22-1.05.59-1.42C6.68 17.55 14.93 14 24 14s17.32 3.55 23.41 9.34c.37.36.59.87.59 1.42 0 .55-.22 1.05-.59 1.41l-4.95 4.95c-.36.36-.86.59-1.41.59-.54 0-1.04-.22-1.4-.57-1.59-1.47-3.38-2.72-5.33-3.7-.66-.33-1.12-1.01-1.12-1.8v-6.21C30.3 18.5 27.21 18 24 18z" fill="white"></path>
        </svg>
      </button>
    </div>
    <div className="request-access">
      <p><span className="you-left">You hung up.&nbsp;</span>Send an invitation to join the room.</p>
      <form onSubmit={props.send}>
        <input type="text" autoFocus onChange={props.handleInput} data-ref="message"  maxLength="30" required placeholder="Hi, I'm John Doe." />
        <button className="primary-button">Send</button>
      </form>
    </div>
    <div className="grant-access">
      <p>A peer has sent you a message to join the room:</p>
      <div>{props.message}</div>
      <button onClick={props.handleInvitation} data-ref="reject" className="primary-button">Reject</button>
      <button onClick={props.handleInvitation} data-ref="accept" className="primary-button">Accept</button>
    </div>
    <div className="room-occupied">
      <p>Please, try another room!</p>
      <Link  className="primary-button" to="/">OK</Link>
    </div>
    <div className="waiting">
      <p><span>Waiting for someone to join this room:&nbsp;</span><a href={window.location.href}>{window.location.href}</a><br/>
      <span className="remote-left">The remote side hung up.</span></p>
    </div>
  </div>

Communication.propTypes = {
  message: PropTypes.string.isRequired,
  audio: PropTypes.bool.isRequired,
  video: PropTypes.bool.isRequired,
  toggleVideo: PropTypes.func.isRequired,
  toggleAudio: PropTypes.func.isRequired,
  getContent: PropTypes.func.isRequired,
  send: PropTypes.func.isRequired,
  handleHangup: PropTypes.func.isRequired,
  handleInput: PropTypes.func.isRequired,
  handleInvitation: PropTypes.func.isRequired
};

export default Communication;
```

```js
// /src/reducers/index.js
import { combineReducers } from 'redux';
// Reducers
import roomReducer from './room-reducer';
import audioReducer from './audio-reducer';
import videoReducer from './video-reducer';
// Combine Reducers
const reducers = combineReducers({
  rooms: roomReducer,
  video: videoReducer,
  audio: audioReducer
});
export default reducers;
```

```js
// /src/reducers/room-reducer.js
const updateRooms = (state = [], action) => {
  if (action.type === 'ADD_ROOM') {
    return [...new Set([...state, action.room])];
  }
  return state;
};
export default updateRooms;
```
```js
// /src/reducers/audio-reducer.js
const setAudio = (state = true, action) => (action.type === 'SET_AUDIO' ? action.audio : state);
export default setAudio;
```

```js
// /src/reducers/video-reducer.js
const setVideo = (state = true, action) => (action.type === 'SET_VIDEO' ? action.video : state);
export default setVideo;
```

```js
// /src/components/NotFound.js
import React from 'react';
export default () => <h1>404.. This page is not found!</h1>;
```

```js
// src/components/ToggleFullScreen.js
const el = document.documentElement;
document.fullscreenEnabled = document.fullscreenEnabled ||
document.webkitFullscreenEnabled ||
document.mozFullScreenEnabled ||
document.msFullscreenEnabled;
document.exitFullscreen = document.exitFullscreen ||
document.webkitExitFullscreen ||
document.mozCancelFullScreen ||
document.msExitFullscreen;
el.requestFullscreen = el.requestFullscreen ||
el.webkitRequestFullscreen ||
el.mozRequestFullScreen ||
el.msRequestFullScreen;
const ToggleFullScreen = () => {
  // full-screen available?
  if (document.fullscreenEnabled) {
    // are we full-screen?
    document.fullscreenElement ||
    document.webkitFullscreenElement ||
    document.mozFullScreenElement ||
    document.msFullscreenElement ? document.exitFullscreen() : el.requestFullscreen();
  }
};
export default ToggleFullScreen;
```

## PostgreSQL

```js
// /src/db/users.js
const pool = require('./pool')

const getUsers = (req, res) =>{
    pool.query(`SELECT * FROM users ORDER BY id ASC`, (err, results) =>{
        if(err){
            console.error(err);
            return
        }
        res.status(200).json(results.rows)
    })
}
```

```js
// /src/db/create.js
const pool = require('./pool')

const createUser = (req, res) =>{
    const { name, email } = req.body

    // $1은 name에 $2는 email에 연결된다.
    pool.query(`INSERT INTO users (name, email) VALUES ($1, $2)` , [name, email], (error, results) =>{
        if(error){
            console.error(error);
            return
        }
        res.status(200).send(`New user added`)
    })
}
```

```js
// /src/db/update.js
const pool = require('./pool')

const updateUser = (req, res) =>{
    const { id } = parseInt(req.body)
    const { name, email } = req.body

    pool.query('UPDATE users SET name = $1, email = $2, WHERE id = $3', [name, email, id], (err, results) =>{
        if(err){
            console.error(err);
            return
        }
        res.status(200).send('USER was updated')
    })

}
```

```js
// /src/db/delete.js
const pool = require('./pool')

const deleteUser = (req, res) =>{
    const id = parseInt(req.params.id)

    pool.query(`DELETE FROM users WHERE id = $1`, [id], (err, results) =>{
        if(err){
            console.error(err)
            return
        }
        res.status(200).send('User was delted')
    })
}
```

```js
// /src/db/condselect.js
const pool = require('./pool')

const condSelect = (req, res) =>{ // 조건적으로 선택
    const id = parseInt(req.params.id)

    pool.query(`SELECT * FROM users WHERE id = $1`, [id], (err, results) =>{
        if(err){
            console.error(err);
            return
        }
        res.status(200).send(results.rows)
    })
}
```





