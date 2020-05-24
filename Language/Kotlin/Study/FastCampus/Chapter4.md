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
## 06. Linearlayout 실습
## 07.
## 08.
## 09.
## 10.
## 11.
## 12.
## 13.
## 14.
## 15.
## 16.
## 17.
## 18.
## 19.
## 20.
## 21.
## 22.
## 23.
## 24.
## 25.
## 26.
## 27.
## 28.
## 29.
## 30.
## 31.
## 32.
## 33.
## 34.
## 35.
## 36.
## 37.
## 38.
## 39.
## 40.
## 41.
## 42.
## 43.
## 44.
## 45.
## 46.
## 47.
## 48.
## 49.
## 50.
