# 구조체 참조

```C++
#include <stdio.h>


typedef struct _Person{
    int age;
    char name[32];
}Person;

int main()
{
    Person p1 = {25, "Jeon Jin Kwan"};
    Person *pUser = NULL;
    pUser = &p1;
    
    printf("%d\n", pUser->age); // 이런식으로 pointer 구조체 안으로 화살표 연산자를 통해서 확인할 수 있다.
    printf("%d\n", p1.age); // 도트 연산자를 통해서 직접 확인
    return 0;
}
```