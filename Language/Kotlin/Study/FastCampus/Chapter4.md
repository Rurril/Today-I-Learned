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

클라이언트 개발자 - GUI를 만드는 사람이기 때문에 인터페이스를 잘 받을 수 있도록, 디자이너의 요구를 제대로 반영할 수 있도록 해야한다.

> 화면을 그리는 것이 별거 아닌 것처럼 보이지만 정말 중요하다. 



## 09. Relative layout 개념 (1)

뷰를 부모 혹은 다른 뷰를 기준으로 배치할 수 있다.

`android:layout_centerInParent="true"`

> 부모를 기준으로 가운데에 위치하게 함 True

layout_alignParentRight 등 다양한 정렬 속성들이 있다. 

## 10. Relative layout 개념 (2)

```XML
android:id="@+id/view2"
android:layout_toRightOf="@id/view1"
```

> 각 컴포넌트마다 id를 넣을 수 있고, Relative layout에서는 다른 컴포넌트를 기준으로 컴포넌트를 배치할 수 있다. 

## 11. Relative layout 과제 설명

정사각형 크기 100dp 씩으로 해서 한다.


## 12. Relative layout 과제 풀이
## 13. Padding, Margin
```XML
android:layout_marginTop="20dp"
android:layout_marginLeft="50dp"
```

> 마진은 부모 컴포넌트로부터 얼마나 떨어지는 지를 나타내는 속성이다. 
```XML
android:paddingLeft="10dp"
android:paddingTop="10dp"
```

패딩은 안에 있는 컨텐츠의 여백을 정하는 것이다.(따지자면, 자식과의 여백을 나타내는 것)

> Top , Left같은 값이 아닌 그냥 margin 혹은 padding이면 4방향 전부를 포함한다. 


## 14. Frame Layout
```XML
<FrameLayout>
    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="hello"
        android:textSize="200dp"
        android:background="#509E79"/>
    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="hello"
        android:textSize="100dp"
        android:background="#00F78D"/>
    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:text="hello"
        android:textSize="60dp"
        android:background="#123122"/>
</FrameLayout>
```

> 프레임 뷰는 컴포넌트들을 곂칠 때 사용한다.

> 가장 먼저 적은 컴포넌트가 아래로 내려가게 된다. 

> Relative layout또한 뷰를 곂칠 수 있다. 

>> 하지만 목적에 맞게 사용하기 위해서, 곂칠 땐 프레임이 사용에 적합하다.

>> 상대적인 배치는 연산을 해야하므로, 속도나 성능에서 차이가 날 수 있다.

> Linear layout은 orientation을 통해서 수직이나 수평을 선언해주어야 하고 곂칠 수 없다. 

## 15. Frame Layout 과제 설명
## 16. Frame Layout 과제 풀이
## 17. Scrollview

> 스크롤뷰는 자식 컴포넌트를 하나만 가질 수 있다.

>> 그렇기에 자식 컴포넌트를 레이아웃 과 같은 것을 넣어서 다른 자식 컴포넌트 여러개를 포함하도록 만든다. 

```java
<ScrollView
        android:layout_width="match_parent"
        android:layout_height="match_parent"
        android:fillViewport="true"
        android:scrollbars="none">
```

> fillViewport는 스크롤 뷰를 잘만들었을 때 오류가 조금 있을 수 있어서, 항상 true속성을 넣어주도록 하자.

> scrollbars도 넣어주자.


## 18. Imageview

```XML
<ImageView
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:src="@drawable/ic_launcher_foreground"/>

```

> src는 @로 시작해서 경로를 나타낸다. 

> 이미지를 보여줄때는 해상도를 정할 수 있다. --> 저, 중, 고해상도

확장팩을 Android Drawable Importer를 사용한다. 

> new -> Batch Drawable Importer를 사용해서 파일을 넣으면 해상도 별로 정리를해준다. (꿀팁)

> 해상도별로 준비를 해놓는다면, 자동으로 핸드폰에 맞는 해상도의 파일을 선택해서 넣어준다. 


이미지를 쓰고 싶은데, 여백이 있을 수 있고 - 그 여백은 제거를 하고 싶다. 

> `android:scaleType="centerCrop"` 

centerCrop을 가장 많이 사용하고, 다른 스케일타입의 값들을 사용해서 다양한 비율로 이미지를 사용할 수 있다. (이미지의 잘림은 있을 수 있다)

## 19. 파이널 과제 설명

> https://www.flaticon.com/kr/

무료 이미지 다운로드, 필요한 이미지를 사용하자.

## 20. 파이널 과제 풀이
## 21. Drawable


> `xmlns:android="http://schemas.android.com/apk/res/android"`

android : <- 라는 옵션을 사용하기 위해서 최상위 컴포넌트에다가 저 문자를 선언함으로써 안드로이드의 컴포넌트를 사용하는 것. 

```XML
<shape xmlns:android="http://schemas.android.com/apk/res/android"
    android:shape="rectangle">

    <gradient
        android:centerColor="#E44949"
        android:endColor="#23CAE2"
        android:startColor="#EB77F7"
        android:angle="45"/>
</shape>

```

> 그라데이션은 파일로 받으면 깨질 수 있기 때문에 직접 하는 것이 괜찮을 수도 있다. 


```XML
<shape xmlns:android="http://schemas.android.com/apk/res/android"
    android:shape="rectangle">

    <stroke
        android:width="20dp"
        android:color="#2196F3"/>
</shape>

```

```XML
<shape xmlns:android="http://schemas.android.com/apk/res/android"
    android:shape="oval">

    <solid
        android:color="#2196F3"/>
    <stroke
        android:width="30dp"
        android:color="#FFFFFF"

</shape>
```

```XML
<?xml version="1.0" encoding="utf-8"?>
<shape xmlns:android="http://schemas.android.com/apk/res/android"
    android:shape="rectangle">

    <solid
        android:color="#03A9F4"/>
    <corners
        android:radius="30dp"/>



</shape>
```

> corners의 radius를 옵션을 줌으로써 직사각형이 아니라 조금은 깎아서 사용할 수도 있다. 


> 간단한 그림은 디자이너들이 만들어주시는 것보다 직접하는 게 나을 수도 있다.
>> radius값 같은 것만 넘겨주면 되는 것!
