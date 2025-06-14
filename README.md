# ArduBlocklyAndroid
Android app using Arduino-Blockly.

구글의 스크래치 언어를 사용한 ‘android-blockly’를 기반으로 안드로이드 상에서 실행하는 앱이다. 안드로이도와 아두이노를 블루투스를 통해 연결하여, 안드로이드 실행과 연계하여 아두이노를 제어할 수 있다.
앱에서 스크래치 코딩을 하고 실행 시작하면, 안드로이드 상에서 실행하면서 아두이노 연결을 통해 입출력 장치의 제어가 가능하다.

# 설명서 및 파일
사용 설명서:
-	documents/Blockly+Arduino 블럭 코드 사용설명서.pdf
- documents/따라하기 Blockly+Arduino앱.pdf

앱:
-	apk 설치파일: android/apk/arduino_blockly.apk <br />
  앱 설치를 위한 파일로 안드로이드에서 ‘apk 설치’를 통해 앱을 설치할 수 있다.

아두이노:
- ino 실행 파일: arduino/ArduBlockly/ArduBlockly.ino

전체적인 사용이해는 '따라하기 Blockly+Arduino앱.pdf' 문서를 통해 쉽게 이해할 수 있다.

<br />

# 전체 시스템 구성

안드로이드 앱에서 작동하는 blockly 기반의 편집기에 아두이노와 연동하는 Javascript 기반의 대응 동작을 통해 작동한다.

<!-- ![AndroidBlocklyCodeProc](https://github.com/iblockly/ArduBlocklyAndroid/assets/160044072/c8da7f1f-efea-42f0-a339-6e526d9d4c7f)-->
<img src="assets/images/AndroidBlocklyCodeProc.png" width="70%" height="70%"  alt="AndroidBlocklyCodeProc" />

안드로이드와 아두이노 사이에는 블루투스 통신을 통해 스크래치 코드의 실행을 연동한다. 스크래치 코드의 실행은 안드로이드에서 하고 아두이노에는 포트의 읽기와 쓰기를 주로 담당한다.

<!-- ![ArduBlockly_SysConfig](https://github.com/iblockly/ArduBlocklyAndroid/assets/160044072/f9204ce7-a21e-4e3c-8ff1-1af2e2717b5c)-->
<img src="assets/images/ArduBlockly_SysConfig.png" width="70%" height="70%"  alt="ArduBlockly_SysConfig" />


## 안드로이드
- 'Blockly' 기반의 스크레치 기반의 블럭 코드를 입력하면
- 실행 시, Javascript 언어로 변환하여 코드를 생성한다.
- 자바스크립트 언어는 인터프리터에 의해 실행되면서 블루투스를 통해 아두이노와 상태 및 포트 명령을 전송하여 동작한다.

### Blockly

Blockly는 안드로이드에서 실행되는 블록을 사용하여 코딩하고 여러가지 언어를 생성할 수 있다.<br>

안드로이드 blockly 프로젝트: https://github.com/google/blockly-android<br>
안드로이드 blockly 개발: https://developers.google.com<br>

blockly-android는 안드로이드 앱으로 블록코드 입력 및 실행 소스코드 생성 오픈소스이다.
다양한 언어로 코드를 생성할 수 있다. 이중에 코드 생성 언어는 JS(JavaScript)를 생성하는 선택을 하였다. 
생성된 자바스크립트 코드소스를 JS-인터프리터를 이용하여 실행하고 아두이노 데이터를 송수신을 통해 아두이노 상태제어 한다.  

# 안드로이드 앱 실행을 위한 준비 

안드로이드 앱을 설치하고, 이 앱을 실행 전에 아두이노의 준비가 되어야 한다.

1. 안드로이드 앱을 설치한다. 
2. 아두이노에 블루투스 연결 전에 ‘arduino’ 폴더의 아두이노 코드를 업로드 한다.
3. 아두이노에 블루투스 모듈을 연결한다.
4. 안드로이드 앱을 실행하여 다음과 같은 실행과정을 통해 동작 시킨다.
- 원하는 블럭 코드를 입력하고 필요에 따라 저장을 한다.
- 클럭 코드를 완성했다면, 실행 버튼을 누른다.
- 블럭 코드에 따라 앱의 입출력 및 아두이노 입출력을 통해 원하는 기능이 작동하는지 확인한다.

<br />
<br />

## 안드로이드 앱 설치


구글 플레이 앱 등록은 진행 중이라 구글플레이에서 설치가 불가능하다.

구글 플레이 앱 동록 전에 사용하기 위해서는 ‘android/apk’ 폴더에 apk 파일을 사용하여 설치할 수 있다.<br />
‘documents’ 폴더의 ‘Blockly+Arduino 블럭 코드 및 사용설명서’을 참고할 수 있다.

----

<p style="color: red;"> --- 현재 구글의 ‘Play 스토어’에 안드로이드 앱을 등록 진행 중 ---</p>

앱 설치 (Google Play): https://play.google.com/store/apps/details?id=kr.icom.blockly.app

웹에서 참여:
[https://play.google.com/store/apps/details?id=kr.icom.blockly.app](https://play.google.com/apps/testing/kr.icom.blockly.app)


-----

<br />
<br />

## 아두이노

- 아두이노에서 안드로이드와 연결하기 위해 블루투스를 사용한다. 
- 블두투스는 클래스 버전을 기반으로 연결하고 아두이노의 포트 상태를 연동한다.

### 아두이노-블루투스 연결

<!-- ![ArduinoUNO-Bluetooth_Sch](https://github.com/iblockly/ArduBlocklyAndroid/assets/160044072/1f93ddc7-d7be-47df-a6eb-ad3d746f6047)-->
<img src="assets/images/ArduinoUNO-Bluetooth_Sch.jpg" width="60%" height="60%"  alt="ArduinoUNO-Bluetooth_Sch" />

아두이노 UNO를 사용할 경우 그림과 같이 연결한다.  블루투스 전원은 사용하는 모듈의 전원을 확인하고 5V인가를 확인하고 다르다면 적당한 Vcc 전원을 선택하여 연결한다.<br>
아두이노의 블루투스 연결에서 소프트웨어의 선택에서 ‘SoftwareSerial’ 라브러리를 사용할 경우 가끔 오류가 발생할 가능성이 있다. 따라서 USB 쪽에서 사용하는 포트0(RX),1(TX)와 중복 되므로 실행 과정에서 USB에 시리얼 통신을 사용하면 블루투스와 충돌이 일어나므로 통신을 사용하면 안된다. ‘arduino’ 폴더에 제공하는 코드에서는 블루투스 통신은 ‘Serial’ 클래스를 사용하였다.

<!-- ![Arduino_SerialPort](https://github.com/iblockly/ArduBlocklyAndroid/assets/160044072/30cfeab5-0d97-4c75-935a-7fe2bc82f49c)-->
<img src="assets/images/Arduino_SerialPort.png" width="50%" height="50%"  alt="Arduino_SerialPort" />

```c++
// arduboard.h
#if defined (__AVR_ATmega328__)
 #define UNO
#elif defined (__AVR_ATmega328P__) 
 #define UNO
#elif defined (__AVR_ATmega2560__)
 #define MEGA
#endif
```
‘보드’ 선택을 하면 2가지의 요소가 결정되는데, 각각의 시리얼 통신은 다른 시리얼포트를 사용한다.

```c++
#ifdef UNO
 #define SerialBt Serial
#elif defined(MEGA)
 #define SerialBt Serial1
#endif
```

![Arduino_Serial](https://github.com/iblockly/ArduBlocklyAndroid/assets/160044072/07e7e573-e2c7-41bf-b23c-cbacca62bd23)


# 안드로이드앱 실행

설치된 앱을 실행하면 다음 그림과 같다.


![ArduBlockly_Run](https://github.com/iblockly/ArduBlocklyAndroid/assets/160044072/dda9a48c-f8ee-4964-86fb-a849c9147c3c)

원하는 기능의 프로그램은 안드로이드의 스크래치를 변경하면 인터프리터를 사용하여 코드를 안드로이드에서 실행하므로 아두이노에는 변경된 코드는 전송하지는 않는다. 아두이노에서는 안드로이드에서 요구하는 입출력을 담당하는 방식으로 동작한다. 따라서 아두이노에서는 입출력 상태를 제어하는 코드를 미리 업로드 해야한다.

## 스크래치 프로그래밍
스크래치 프로그램은 다음과 같은 화면에서 입력한다.


<img src="https://github.com/iblockly/ArduBlocklyAndroid/assets/160044072/93fd1a96-a8a6-4a51-a438-30ed941f38c5" width="40%" height="40%" alt="ArduBlockly_block_code" />


### 블록코드 종류 및 기능

#### 이벤트: 아두이노 방식으로 만들어진 이벤트이다.

하드웨어 아두이노에 사용하기 위한 블록 이므로 아두이노의 2개의 함수는 다음 2개의 블록에 의해 수행된다. 따라서 어느 블록 코드이든 2개가 필수적이다.

아두이노와 비교하면:
'초기화(setup)' 블록: setup()
'반복(loop)' 블록: loop()
와 해당되는 실행 구조를 갖는다.

  
- 초기화: 전체 프로그램 실행에서 처음으로 실행되는 초기화 함수이고, 처음에 한번 실행되는 블럭이다.<br>
변수의 초기화, 아두이노 상태의 초기화 등에 사용하면 된다. JS의 변수를 사용할 때 블록 코드에서는 전역변수로 처리한다. 따라서 같은 이름의 변수는 전역으로 적용된다. 이때 초기화 등을 이 블록에서 할 수 있다.

- 반복: 무한 루프로 반복되는 블럭이다. 아두이노의 loop() 함수와 비슷한 실행 구조로 멈춤을 누를 때까지 반복한다.<br>
무한 반복이므로 전체 기능 구현의 대부분이 여기에서 작성하여 사용한다.

- 조이스틱: 안드로이드의 아래/오른쪽에 나타나는 조이스틱의 움직임에 대응하는 블럭이다.<br>
조이스틱을 움직이면 좌표 x,y 값과 원점에서의 거리 d와 각도 r의 값이 전달되어 실행되는 블럭이다. 조이스틱의 좌표값을 활용하여 원하는 기능을 구현한다.

- 스위치: 아두이노의 디지털 포트 입력에 의해 발생하는 이벤트 처리 블럭이다.<br>
이 블록의 숫자는 아두이노의 디지털 숫자로 아두이노에서 보내는 디지털 상태를 판단하여 실행되는 블록이다.

- 버튼: 안드로이드 앱의 조이스틱 옆의 4개의 버튼을 눌렀을 때 발생하는 이벤트 처리 블럭이다.<br>
안드로이드 앱에서 사용하는 버튼이 눌렸을 때 JS 인터프러터로 전송되어 실행되는 블록이다.
U, D, L, R의 이름이 부여되어 있어 블록에서 선택하면 된다.

- 메뉴: 안드로이드 앱의 메뉴를 실행하면 실행되는 이벤트 처리 블럭이다.<br>
안드로이드 앱의 메뉴에 실행되는 메뉴1, 메뉴2를 실행하면 JS 인터프러터로 전송되어 실행되는 블록이다.

- 지연(delay): 실행을 입력된 시간동안 중지된다. JS 인터프러터로 반복 실행을 일정 시간 멈춘다.<br>
인터프러터로 실행을 ms 동안 중지한다.

-	I2C 데이터 수신 이벤트: I2C의 레지스터 읽기가 아두이노에 전송되면, 아두이노는 I2C 레지스터를 읽고 앱으로 전송한다.
  이를 받은 앱에서는 이벤트로 처리한다. 앱 입장에서는 실시간 실행 입장에서 언제 읽혀 올지 모르기 때문이다.

I2C의 처리 과정은 다음과 같다.

  ![image](https://github.com/user-attachments/assets/4278de6b-02ca-4fe6-92e9-d43ae54ead08)


#### 아두이노: 아두이노와 연동하여 포트의 상태 및 제어를 위한 입 출력 블럭이다.
  
- 디지털 출력: 디지털 출력을 위한 블록이다.

- 디지털 입력: 디지털 입력을 위한 블록이로, 아두이노에서 읽어 블루투스로 전송되면 JS 변수로 설정되어 저장된다.

- 아날로그 입력: 아두이노의 아날로그 포트에서 읽어 블루투스로 전송되면 JS 변수로 설정되어 저장된다.

- PWM 출력: 아두이노의 포트 중에 PWM 출력을 위한 설정값을 쓰기한다.

- I2C 처리 블록: I2C의 초기 설정, 레지스터 쓰고 읽기 등의 블록으로 I2C 인터페이스를 제공한다.
  앱의 블록 실행으로 설정 명령이 아두이노에 전송하면 아두이노는 I2C을 제어한다.  

#### GUI: 그림, 사운드, 문자, 도형 등의 처리 블록이다.
  
- 움직이기: 그림의 위치로 이동하는 블록이다.

-	문자 박스, 도형 (타원, 사각형, 삼각형) 블록으로 도형을 그린다.

-	상태바 표시 블록으로 상태를 표시할 수 있고, 수평, 수직으로 표현한다.

- 사운드: 사운드 출력을 위한 블록이다.

#### 로직: 프로그램의 로직을 판단하기 위한 블럭이다.
  
- 만약(if~else): 조건 처리를 위한 블록이다.

- 로직 판단: 로직 판단을 위한 블록 들이다.<br>
비교, 부정 등의 처리를 한다

#### 루프: 프로그램의 반복 처리 로직을 위한 블럭이다.

- 반복로직: 반복 처리를 위한 블록 들이다. <br>
repeat, while, for 처리를 한다

#### 수학: 숫자처리를 위한 블럭이다.
- 숫자처리로 상수, 사칙연산, 삼각함수, 로그 등의 숫자 처리를 한다.

#### 문자: 문자(스트링) 처리를 위한 블럭이다.

#### 리스트: 리스트 처리를 위한 블럭이다.

#### 변수: 변수 처리를 위한 블럭이다. 변수 추가, 변수 선택 등 처리하는 블록이다.

## 스크래치 실행
엡에서 실행 버튼을 누르면 다음과 같은 화면으로 표시되면서 JS 코드가 실행된다.

<img src="https://github.com/iblockly/ArduBlocklyAndroid/assets/160044072/11b65fdd-e65a-4ea6-830a-ec264c996823" width="40%" height="40%"  alt="ArduinoBlockly_run_st" />

위의 화면은 portrait 모드로 동작하는 실행 화면이다. 아래쪽에 버튼 및 조이스틱 인터페이스가 실행된다. 이 인터페이스는 블록 이벤트를 코딩하면 연계되어 실행된다.

실행화면에서 위 부분은 실행화면이다. 물체 이동 코딩이 되면 물체 이동 등을 표시할 수 있다.

## 블루투스 연결
엡에서 ‘연결’ 메뉴에 의해 블루투스 선택 및 연결을 시도한다. 연결 다이얼로그에서 선택하고 연결하면 된다.

현재 블루투스 버전 2을 지원하는 클래스 블루투스 모듈과 BLE(저전력 블루투스, 버전4,5)를 사용하여 연결할 수 있다.
다이얼로그에서 선택을 하면 연결과정이 진행하여 페어링 된다.
앱과 아두이노 간의 데이터 송수신을 통해 수신 데이터는 JS 변수에 실시간으로 저장되고 이를 활용한다. 
블록코드 실행이 없어도 아두이노로 부터  데이터는 JS 변수에 저장된다.

만약 블루투스 연결없이 ‘실행’ 메뉴를 실행하면, 아두이노 데이터 송수신없이 실행된다. 
따라서 일부 블록의 경우 하드웨어의 제외 명령은 무시되고 상태읽기는 불가능한 상태로 실행이 진행된다.

## 안드로이드 앱 메뉴

앱을 실행하면 메뉴 바가 상단에 있고, 스크래치 입력 화면이 나타난다.
메뉴의 종류는 다음과 같다.
- 실행: 입력한 블록 코드를 실행한다.
- 메뉴1: 앱 실행 시, 메뉴1 이벤트를 JS에  보낸다.
- 메뉴2: 앱 실행 시, 메뉴2 이벤트를 JS에  보낸다.
- 연결: 블루투스 연결을 위해 블루투스 연결 용 다이얼로를 표시하고 선택한다.
- 저장: 입력된 스크래치 코드를 파일로 저장한다. 이 메뉴는 앱의 코드에 정해진 파일이름으로 저장한다.<br>
여기서 저장된 폴더의 앱의 내부저장 공간이다.
- 가져오기: 메뉴 ‘저장’에서 저장된 스크래치 코드를 읽어 화면에 표시한다.
- 초기화: 블록코드를 초기화한다. 입력된 스크래치 코드를 삭제한다.

내부 저장소 스크래치 코드 저장하기
- 파일 저장: 스크래치 블록코드를 파일로 저장한다.
- 파일 가져오기: 저장된 스크래치 블록코드를 파일로부터 읽어 화면에 표시한다.
- 파일 지우기: 저장된 스크래치 블록코드를 파일을 지운다.

외부 저장소 스크래치 코드 저장하기<br>
외부 저장소에 파일을 저장하여 윈도우 등의 컴퓨터에서 읽고 쓸수 있다. 폴더는 ‘Download’ 이다. 스크래치 코드는 XML 텍스트 파일 이므로 쉽게 코드를 볼 수 있다.
- 외부 저장소: 스크래치 블록코드를 외부 저장 공간에 파일로 저장/로드할 수 있다.
- 끝내기: 앱을 정지한다.

# 스케치 프로그래밍의 예

## 초기화 예 
‘실행’ 메뉴에 의해 프로그램이 시작되면 실행되는 ‘이벤트’ 가 이 블럭이다. 따라서 실행 처음 한번 실행되고 ‘반복’ 블록으로 무한 반복 실행된다.
‘초기화’ 블록 코드의 경우 변수 초기, 아두이노 초기 설정 등을 코딩할 수 있다.

<img src="https://github.com/iblockly/ArduBlocklyAndroid/assets/160044072/276c79c3-c338-4e89-a7ca-74e377d5bc77" width="30%" height="30%" alt="blockly_exam_init" />

1.	아두이노에 내장된 LED 끄기
2.	변수 ‘item’ 초기화
3.	PWM 포트 3에 초기값 설정

## 아두이노 LED 
아두이노의 LED는 13 포트에 자체에 연결되어 있다.

## 아두이노 디지털 입력 
아두이노의 디지털 포트로부터 상태를 읽어 전달되는 값이다. 보트 숫자는 아두이노의 포트 번호이다.

<img src="https://github.com/iblockly/ArduBlocklyAndroid/assets/160044072/20a35659-b883-4a1a-a487-032b07f5b9f4" width="40%" height="40%"  alt="blockly_exam_loop" />

1.	만약 아두이노 디지털 포트 7 핀의 상태가 LOW이면
2.	LED을 끄고, 포트 3의 PWM 포트에 200을 설정한다. 
3.	500ms 지연한다.

## 아두이노 아날로그 입력과 PWM 출력

아두이노의 아날로그 입력으로 ADC의 값을 읽어 어 전달되는 값이다. 아두이노 보드에 따라 아날로그의 입력 핀은 결정되어 있다.

<img src="assets/images/analog_pwm_led.png" width="40%" height="40%"  alt="analog_pwm_led" />

아날로그 입력 핀은 UNO의 경우 A0~A5까지이며, 모델에 입력 수는 다르다.
아날로그의 입력은 10비트이고, PWM는 8비트 출력이다. 쉬프트 연산자를 통해 값을 조정하여 출력하였다.

## I2C 사용
많은 센서에서 I2C을 사용한다. 예로 조도센서 BH1750FVI 사용 예이다.
초기화 과정:
‘I2C 설정’에서 아이디를 임의의 숫자로 10으로 사용 센서를 지정하고 35는 BH1750FVI I2C 주소값이다. 아이디는 여러 개의 I2C 연결 시 각각을 구별한다.

<img src="assets/images/i2c_pwm_char.png" width="40%" height="40%"  alt="i2c_pwm_char" />


‘I2C ID 10’ 이벤트는 레지스터 명령에 의해 의해 아두이노가 읽어 앱으로 전송하면 동작하는 이벤트 이다.

<img src="assets/images/i2c_read_reg.png" width="30%" height="30%"  alt="i2c_read_reg" />

‘I2C 읽기’ 블록에 의해 1초에 한번씩 읽기 명령을 아두이노 전송한다.
아래는 버튼 이벤트에 의해 읽기를 전송한다.


## 조이스틱

조이스틱에서 작동되는 좌표를 이벤트 블록에 전달하여 코드에 따라 기능 구현을 할 수 있다.<br>
조이스틱의 좌표값은 두가지로 보내진다.
- (x,y) : 조이스틱의 원점으로부터 x, y 값으로 전달
- d,a: d는 원점으로부터 거리값이고, a는 각도값이며, 360도 값이다.
위의 두값 모두 전달되므로 선택적으로 사용할 수 있다. 4개의 값은 JS의 전역변수로 처리된다.

<img src="https://github.com/iblockly/ArduBlocklyAndroid/assets/160044072/0a209e23-e766-4e5c-bb30-eb28176d6bb6" width="50%" height="50%"  alt="blockly_exam_joystick" />

조이스틱이 움직일 때, 좌표값 x,y에 그림을 움직인다.

### 조이스틱과 위치 정보 문자 표시

조이스틱의 움직임에 따라 ‘문자’ 표시 블록으로 그림의 위치를 화면에 표시한다. 

<img src="assets/images/joystick_char_pos.png" width="40%" height="40%"  alt="joystick_char_pos" />

동작은 결과는 다음과 같다.

<img src="assets/images/joystick_char_pos_result.jpg" width="40%" height="40%"  alt="joystick_char_pos_result" />

## 문자 표현

실행화면에 정보를 표현하기 위한 문자, 도형, 상태바 등을 지원한다. 
다음 예는 문자를 표현한 예 이다.

<img src="assets/images/charbox_color_time.png" width="40%" height="40%"  alt="charbox_color_time" />

‘현재 시간’ 블록은 앱의 현재 시간을 읽어 표시한 것이다. 아두이노 실시간 RTC와 상관없다.

<img src="assets/images/charbox_color_time_result.png" width="40%" height="40%"  alt="charbox_color_time_result" />

## 도형 그리기

실행화면에 정보를 표현하기 위한 문자, 도형, 상태바 등을 지원한다. 

<!--![shape_attri_set](assets/images/shape_attri_set.png)-->
<img src="assets/images/shape_attri_set.png" width="40%" height="40%"  alt="shape_attri_set" />

다음의 결과에서 문자는 맨위에 표시하고 도형은 아래 층에 표시한다.

<!-- ![shape_attri_set_run](assets/images/shape_attri_set_run.png)-->
<img src="assets/images/shape_attri_set_run.png" width="40%" height="40%"  alt="shape_attri_set_run" />

<br />

### 상태바와 조이스틱의 결합

![statebar_shape_joystick](assets/images/statebar_shape_joystick.png)

조이스틱 이벤트가 발생하면 상태바의 속성값 중, 현재 진행 상태 값을 조이스틱 위치값을 활용하여 상태바의 진행을 변화 시킨다.

문자 표시에서 x축 위치값에서 처리한 상태값과 녹색 좌표값은 조이스틱 좌표값 (x,y) 이다.



<img src="assets/images/statebar_shape_joystick_run.png" width="40%" height="40%"  alt="statebar_shape_joystick_run" />


조이스틱의 x축의 값과 상태바의 진행 상태값을 변화 시킨다. 조이스틱fmf x축으로 움직이면 상태바가 변화한다. 
<br />
<br />
<br />

# 마무리

이 프로젝트는 현재 개발이 진행되고 있는 앱이며, 문제점을 내포할 수 있다. 

기초적인 기능만이 구현된 상황이므로 시험을 통해 블록 등은 추가 또는 변경이 필요할 수 있다.


## 개발자

#### 개발 및 사용 문의

이 앱은 개발이 진행되고 있고, 기초적인 기능을 구현한 버전이 진행되고 있다.
실제 적용에 적합하지, 실행에서 문제가 있는지를 검토하고 업데이트가 필요하다. 

기능 추가 및 앱 문제는 다음 연락처로 문의 바랍니다:

이메일: icblockly@gmail.com  &nbsp;&nbsp; dolicom@naver.com<br />
Phone: 010-5423-7659
