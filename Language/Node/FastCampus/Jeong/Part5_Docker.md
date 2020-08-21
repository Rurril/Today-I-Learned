# Docker

## Docker 소개

LXC(리눅스 컨테이너스)라는 커널 컨테이너 기술을 이용하여 만든 컨테이너 기술 중 하나.

## Docker 특징

- 운영체제를 가상화하지 않는 컨테이너 기술인 만큼 가상머신에 비해서 가벼우며, VM을 포함하여 한대의 서버에 여러개의 서비스를 구동하기 좋다.
- 보안상, 서비스가 털리더라도 원래의 서버에 영향을 미치기가 쉽지 않은 격리된 구조인 만큼, 가상화의 장점을 상당 부분 활용할 수 있다.
- 가상머신(VM)들과 달리, 기존 리눅스 자원(디스크, 네트워크 등)을 그대로 활용할 수 있어서 여러 서비스들을 한 서버에서 돌리기가 좋은 편이다.

## Docker 설치와 개발 환경 설정

`sudo apt-get install docker.io`

## Docker 기초와 Docker CLI

```
docker -v // 도커 버전 확인
docker search node // 노드의 키워드를 갖는 이미지를 검색
docker pull ubuntu // ubuntu라는 이름의 이미지를 가져온다 - 버전을 지정하지 않으면 최신버전의 이미지를 pull한다
docker node images // node라는 이미지에 대해서 같은 이름을 갖고 있지만 태그가 다른 이미지들을 출력한다
docker run --name ubuntu -d -it ubuntu:latest /bin/bash // 백그라운드 + 터미널 옵션에서 우분투 실행
docker ps -a // 현재 실행중인 컨테이너를 보여줌. 
docker stop {container_id} // 해당하는 컨테이너 아이디의 컨테이너가 중지된다. 


```

## Docker Compose와 Dockerfile

```dockerfile
FROM node:latest

WORKDIR /usr/src/app

COPY package.json ./

RUN npm install 

COPY . .

EXPOSE 8080
CMD ["node","server.js"] 
```

도커 파일을 작성한다. 

CMD에 해당하는 명령어는 `node server.js` 랑 동일한 명령어를 입력하게 되는 것. 

