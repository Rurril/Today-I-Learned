# Flash Memory 사용하기


Description
Store data in flash (program) memory instead of SRAM. There’s a description of the various types of memory available on an Arduino board.

The PROGMEM keyword is a variable modifier, it should be used only with the datatypes defined in pgmspace.h. It tells the compiler "put this information into flash memory", instead of into SRAM, where it would normally go.

PROGMEM is part of the pgmspace.h library. It is included automatically in modern versions of the IDE. However, if you are using an IDE version below 1.0 (2011), you’ll first need to include the library at the top of your sketch, like this:

#include <avr/pgmspace.h> While PROGMEM could be used on a single variable, it is really only worth the fuss if you have a larger block of data that needs to be stored, which is usually easiest in an array, (or another C++ data structure beyond our present discussion).

Using PROGMEM is also a two-step procedure. After getting the data into Flash memory, it requires special methods (functions), also defined in the pgmspace.h library, to read the data from program memory back into SRAM, so we can do something useful with it.

## 플래시 메모리를 사용하는 경우

변수가 아닌 상수로써 Read Only를 하더라도 상관이 없는 수들을 저장함으로써 불 필요하게 Ram을 쓰지 않아도 될때 사용한다.

아두이노의 RAM은 매우 한정적이므로 1byte 도 아쉬워서 찾게 된다.

Mega2560을 기준으로 플래시 메모리는 256KB이고 SRAM은 8KB, 마지막으로 EEPROM은 4KB이므로 모든 메모리를 굉장히 콤팩트하게 사용하지 않는다면, 조금이라도 큰 프로그램은 돌릴 수 없을 것이다.

(대체 왜 nano로 돌아가는 코드를 mega까지 구현해야 하는 거야...)

시행착오한 것들을 정리하기 위해서 이렇게 간단한 지식들과 내가 사용했던 방식들을 적어놓겠다.

최대한 상수들은 Flash memory를 사용함으로써 SRAM 사용량을 최대한 줄이자!

## 플래시 메모리 변수 타입

> Typedefs

`typedef void PROGMEM 	prog_void`
 
`typedef char PROGMEM 	prog_char`
 
`typedef unsigned char PROGMEM 	prog_uchar`
 
`typedef int8_t PROGMEM 	prog_int8_t`
 
`typedef uint8_t PROGMEM 	prog_uint8_t`
 
`typedef int16_t PROGMEM 	prog_int16_t`
 
`typedef uint16_t PROGMEM 	prog_uint16_t`
 
`typedef int32_t PROGMEM 	prog_int32_t`
 
`typedef uint32_t PROGMEM 	prog_uint32_t`
 
`typedef int64_t PROGMEM 	prog_int64_t`
 
`typedef uint64_t PROGMEM 	prog_uint64_t`

위에 보이는 것처럼 1byte부터 8bytes까지 담을 수 있는 것처럼 보인다.

하지만 메뉴얼을 찾아봐도 저장할 수는 있지만 8bytes의 수를 Read하는 함수는 찾을 수 없었다.


> 읽기

`pgm_read_byte_far(address_long)`
 
`pgm_read_word_far(address_long)`
 
`pgm_read_dword_far(address_long)`

차례대로 1byte, 2bytes, 4bytes를 읽어올 수 있다.

```c
const uint32_t PROGMEM constants[20] = {
    0x428a2f98, 0xd728ae22, 0x71374491, 0x23ef65cd,
    0xb5c0fbcf, 0xec4d3b2f, 0xe9b5dba5, 0x8189dbbc,
    0x3956c25b, 0xf348b538, 0x59f111f1, 0xb605d019,
    0x923f82a4, 0xaf194f9b, 0xab1c5ed5, 0xda6d8118,
    0xd807aa98, 0xa3030242, 0x12835b01, 0x45706fbe,
  };
```

이렇게 저장할 수 있으며

```c
uint64_t number = ((uint64_t)pgm_read_dword_far(constants)<<32) | (pgm_read_dword_far(constants + 1));
```

다음과 같은 방식을 4bytes를 꺼내고 또한 8bytes 크기의 `number`를 만들었다.

## ino파일이 아닌 다른 c파일에서 사용이 가능할까? 

**결론을 먼저 말하자면 가능하다.**

당연히 가능해야겠지만, 오류가 나서 햇갈린 나의 경우도 있고 혹시 궁금해할 사람들을 위해서 적어놓겠다.

나의 경우에는 라이브러리를 만들어서 사용할 때 

`#include <avr/pgmspace.h>`

먼저 위의 헤더파일을 포함시키고 사용했다. 

```c
uint64_t returnConstant(int i){
  return ((uint64_t)pgm_read_dword_far(constants + 2 * i)<<32) | (pgm_read_dword_far(constants + 2 * i + 1));
}
```

다음과 같이 함수를 작성해서 사용하기도 하였다. 



