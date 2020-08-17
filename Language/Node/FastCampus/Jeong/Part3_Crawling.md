# Crawling

## Puppeteer

- 구글의 크롬팀에서 개발하였기 때문에 사용하기 좋다. 
- headless - 웹 브라우저 상에서 랜더링되는 과정을 생략하고, 
- 코드로써 적용한다면 puppeteer가 자동화해준다. 
- 스크린샷 + 스크롤링 되는 이벤트까지 다양한 기능을 편리하게 해준다.

[깃헙주소 : Puppeteer](https://github.com/puppeteer/puppeteer)


npm i puppeteer --save와 npm i puppeteer --save-dev의 차이점을 알아야한다.


--save : package.json 파일의 dependencies 항목에 플러그인 정보가 저장된다. 

--save-dev : package.json 파일의 devDependencies 항목에 플러그인 정보가 저장된다. 

이 점은  --production으로 빌드 시 해당 플러그인이 포함되지 않는다는 점에서 차이가 있다. 즉, 개발 외적으로 배포할 때는 필요하지 않은 플러그인들을 따로 분류하는 것. 


## Data Automation 스크린 캡쳐 자동화

```js
const puppeteer = require('puppeteer')

const main = async () =>{
    const browser = await puppeteer.launch()
    const page = await browser.newPage()
    await page.goto('http://google.com') // 스크린샷의 전 단계 
    await page.screenshot({path : 'screenshot.png'}) // 경로를 상대경로로 설정
    await browser.close()
}

main()
```

해당 경로에 스크린샷이 만들어졌다. 


## Data Automation 크롤링

```js
const puppeteer = require('puppeteer')
const fs = require('fs')

const main = async () =>{
    const browser = await puppeteer.launch()
    const page = await browser.newPage()
    await page.goto('https://example.com', {waitUntil : 'networkidle2'})
    await page.waitFor(6000) // 6second 기다린다.
    const html = await page.content() // html 데이터를 가져온다.
    fs.writeFileSync("example.html", html) 
    
    await browser.close() // 브라우저 종료까지 기다리는 비동기 작업 
}

main()
```

동일한 디렉토리에 'example.html'이 파싱해서 완성된 것을 볼 수 있다. 


## 실무 활용 PDF 생성 자동화

```js
const puppeteer = require('puppeteer')

const main = async() =>{
    const browser = await puppeteer.launch()
    const page = await browser.newPage()
    await page.goto('https://google.com', { waitUntil : 'networkidle2'}) // 예상하지 못한 외부변수로 무한정 기다릴 수도 있다. -- 네트워크 상태가 idle될 때까지만 기다린다. 
    await page.pdf({path : 'test.pdf', format : 'A4'})
    await browser.close() // 메모리 누수를 막기 위해서 브라우저 종료
}

main()
```

