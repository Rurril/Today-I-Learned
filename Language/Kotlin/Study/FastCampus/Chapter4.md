# 안드로이드 Essential - UI

## 목차 

## 01. 화면은 어떻게 그리는 걸까

### 안드로이드에서 화면을 그리는 방법
- XML을 이용한다.
- XML - DSL Language -> Domain Specific Language
    - 어떠한 범주에 특화되어있는 언어
    - 안드로이드 UI를 그리기 위해 특화된 언어

## 02. 핸드폰마다 화면 크기가 다 다른데 화면을 그려야 할까

픽셀, dpi, dp단위를 알아야 한다.

- 픽셀 -> 핸드폰 화면에서 빛이 나오는 전구 -> 가장 작은 단위
- dpi -> dot per inch : 정사각형 범위에서 픽셀이 얼마나 있나.
    - ldpi -> 120 (1인치에 120픽셀)
    - mdpi -> 160
    - hdpi -> 240
    - xhdpi -> 320
    - xxhdpi -> 480
    - xxxhdpi -> 640
- dp -> Density Independent Pixel
    - 픽셀 독립적인 단위
    - 어느 핸드폰에서든 똑같은 것을 보여주고 싶다면, DP를 이용해서 화면을 그리면 된다.


## 03. View component 개념

Design 탭은 컴포넌트가 무엇이 있는지 확인하기 위해서 사용할 때, 참고하기 좋다. 

하지만 실제로 원하는 대로 다루기가 어렵고, XML로 타이핑해서 작성하는 편이 좋다. 

## 04. View component 실습




```XML
    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"/>
    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content">
    </TextView>
```
위와 아래의 코드는 동일하다. 

<열고 닫는 것에 이름이 동일해야 한다.>

다양한 속성들이 있고, Design 탭에서 그 component의 속성들 중에서 원하는 것이 있는지를 확인해보고 적용할 수 있다. 

- 단위 적용에서는 dp가 범용적으로 사용되는 것이 좋다. 
## 05. Linearlayout 개념

> 뷰 컴포넌트 간에 부모 자식 관계가 존재한다.

> 부모 컴포넌트가 될 수 없는 것들도 존재한다. 

Layouts <- 부모 컴포넌트들이 될 수 있는 것들

Comtainers <- 부모 컴포넌트가 될 수 있는 것들

부모 컴포넌트 : 주로 화면에 나오지 않고, 화면을 구성하는 역할을 한다.
자식 컴포넌트 : 주로 화면에 나와서 보여주는 역할. 

> 부모 컴포넌트는 자식 컴포넌트들의 배치를 정할 수 있다.

> 같은 속성들을 적용할 때는, 작은 범위의 속성이 우선 적용된다. (자식 컴포넌트의 속성이 먼저 적용이라는 것)

> 속성 - match_parent : 부모 컴포넌트에 꽉 맞추겠다.

> 속성 - wrap_parent : 해당 뷰가 그려질 수 있게 **필요한 길이만** 사용한다.


## 06. Linearlayout 실습

```xml
android:gravity="right | center"
android:layout_gravity="center"
```

> 그냥 gravity는 부모의 것을 layout_gravity에서 적용하고 자신한테 적용할 것을 말하는 것. 

> '|'를 통해서 속성 2가지를 동시에 적용시켰다.


`android:layout_weight="1"`

> weight 속성을 통해서 동일 항렬 컴포넌트끼리의 비율을 정해줄 수 있다. 


```xml
android:layout_width="wrap_content"
android:layout_height="0dp"
android:layout_weight="1"
```

> 높이를 0dp로 했기 때문에, weight의 비율이 높이에 적용된다. 

`android:weightSum="5"``

> 부모 컴포넌트의 비율을 전체 5등분을 했다는 것을 의미 : 최대 비율 (5)까지 자식 컴포넌트 끼리 나눌 수 있는 것. 


## 07. Linear layout 설명

리니어레이아웃을 기준으로 9가지로 나누어서 각기 다른색으로 표현

## 08. Linear layout 풀이


## 09. Relative layout 개념 (1)
## 10. Relative layout 개념 (2)
## 11. Relative layout 과제 설명
## 12. Relative layout 과제 풀이
## 13. Padding, Margin
## 14. Frame Layout
## 15. Frame Layout 과제 설명
## 16. Frame Layout 과제 풀이
## 17. Scrollview
## 18. Imageview
## 19. 파이널 과제 설명
## 20. 파이널 과제 풀이
## 21. Drawable
