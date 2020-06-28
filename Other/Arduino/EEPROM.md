# Arduino EEPROM 사용

프로젝트 중에 Arduino Mega 2560을 사용해서 프로그램을 동작시키는 일을 하고 있다.

그 전에는 Arduino Nano 33 iot를 사용해서 프로그램을 실행시켰는데, 스펙에서 엄청난 차이가 난다.

간단하게 중요 스펙을 정리해 보자면

**Nano 33 iot**

- Microcontroller : SAMD21 Cortex®-M0+ 32bit low power ARM MCU 
- Flash Memory : 256KB
- SRAM : 32KB
- EEPROM : none


**Mega 2560**

- Microcontroller : ATmega2560 
- Flash Memory : 256KB
- SRAM : 8KB
- EEPROM : 4KB

플래시 메모리는 동이한 스펙을 가지고 있지만, 그것보다 중요한 것은 SRAM에서의 크기 차이가 4배나 난다는 것이다.

Nano 33 iot에서는 여유롭게 돌아가는 프로그램이지만, 전역변수를 거의 8KB 할당하기 때문에 Mega에서는 돌릴 생각조차 못하게 된다.

그렇기에 Mega의 EEPROM의 사용이 절실해졌다.

## EEPROM이란? 

EEPROM(Electrically Erasable PROM)은 On-Board 상태에서 사용자가 내용을 Byte 단위로 Read하거나 Write 할 수 있으므로 사실상 SRAM처럼 사용 할 수 있는 불휘발성 메모리이다. 

> PROM이란 Programmable Read Only Memory의 줄임말로 프로그래밍 가능한 ROM이라는 것

그러나, 이것의 Read 동작은 Access동작이 다소 느릴지라도 SRAM과 유사하므로 별 문제가 없는데 비하여, Wirte 동작을 수행하는 경우에는 1byte를 write 할 때마다 수 ms이상의 시간 지연이 필요하므로 SRAM과 동일하게 사용할 수는 없다. 

**따라서 EEPROM은 실시간으로 사용되는 변수를 저장하는 메모리나 스택 메모리로는 사용될 수 없으며, 한번 내용을 저장하면 비교적 오랫동안 이를 기억하고 있으면서 주로 이를 읽어 사용하기만** 하거나 전원을 꺼도 지워져서는 안되는 중요한 데이터를 백업하여 두어야 하는 설정값 저장용 메모리로 적합하다. 

즉, Read Only memory인 Flash Memory와는 다르게 Read & Write가 모두 가능한 점에서 큰 차이점이 있다. 

> 정리하면, SRAM의 대체로 사용할 수 있으나 RW(Read, Write)하는 속도가 매우 느리기 때문에 한 번 저장하고 읽어서 사용하기만 하면 되는 데이터를 저장하기 적합한 메모리라는 것


## Arduino EEPROM 라이브러리

- EEPROM Clear: EEPROM에서 바이트를 클리어한다.
- EEPROM Read: EEPROM을 읽고 값을 컴퓨터로 전송한다.
- EEPROM Write: 아날로그 입력에서 EEPROM으로 값을 저장한다.
- EEPROM Crc: EEPROM 콘텐츠의 CRC를 배열인 것처럼 계산한다.
- EEPROM Get: EEPROM에서 값을 가져와 직렬에 플로트로 인쇄한다.
- EEPROM Iteration: EEPROM 메모리 위치가 어떻게 진행되는 지 알 수 있다.
- EEPROM Put: 가변 의미론을 사용하여 EEPROM에 값을 넣는다.
- EEPROM Update: A0에서 읽은 값을 EEPROM에 저장하고, 다른 경우에만 값을 기록하여 EEPROM 수명을 증가시킨다.

사용법

1. `#include <EEPROM.h>` 를 포함시킨다.
2. EEPROM에 값을 저장하기 위해서는 EEPROM.write(Address, Data); 형태로 코드를 작성한다.
3. EEPROM에 값을 읽기 위해서는 EEPROM.read(Address); 형태로 코드를 읽는다. 

## Arduino EEPROM 사용


```C

#include <EEPROM.h>

int randomNumber;

void setup(){
  Serial.begin(9600); // 시리얼 통신 초기화
  for(int i = 0; i<4096; i++){
      EEPROM.write(i, i%256);
  }
}
```

Mega 2560의 경우 EEPROM의 크기는 4KB이므로 **[0, 4096)** 에 해당하는 주소값을 갖는다.

또한 주소에 1byte씩 저장하므로 가질 수 있는 값은 **[0, 256)** 에 해당한다.

EEPROM에 저장한 값들을 불러오는 코드를 아래에 작성해보겠다.


```C
  for(int i = 0; i<4096; i++){
      uint8_t number = EEPROM.read(i); 
      Serial.println(number);
  }
```

여기서는 일단 Read와 Write말고 다른 함수들은 다루지 않겠습니다.

