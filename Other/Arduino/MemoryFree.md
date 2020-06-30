# MemoryFree 함수 사용

MemoryFree - 

AVR Libc commands provided with avr/pgmspace.h : avr 라이브러리에서 제공되는 커멘드 대신 사용하기 쉽고 단순한 라이브러리를 제공한다.

MemoryFree는 RAM이 얼마나 사용되고 있는지 알기에 유용하다.

> 아두이노는 기본적으로 램이 매우 적으므로, 프로그래밍을 하다가 RAM이 부족한 경우가 생길 가능성이 매우 크다. 그래서 중간중간마다 글로벌 정적 메모리 사용량을 확인하는 것이 (체감상) 필수다.

[메모리 프리 라이브러리](https://github.com/mpflaga/Arduino-MemoryFree)

위의 링크에서 라이브러리를 다운받아서 사용할 수 있다. 

과거 프로세서와는 달리 

Arduino 33 iot를 사용하는데 기존에 있던 다른 라이브러리인 [https://github.com/McNeight/MemoryFree]는 프로세서가 달라서 적용이 안되는 것을 알 수 있었다.

위의 라이브러리는 최신 프로세서에서도 적용가능하니 참고 바람. (MEGA 2560에서도 잘 작동되네요)

```Arduino
#include <MemoryFree.h>
// ---
Serial.print((String)freeMemory());
```

위의 방식으로 적용하면 남은 RAM이 얼마나 되는지 알 수 있다. 

