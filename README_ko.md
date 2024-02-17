[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PCF8574

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pcf8574/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PCF8574/74A는 2선 양방향 I2C 버스(직렬 클럭(SCL), 직렬 데이터(SDA))를 통해 범용 원격 I/O 확장을 제공합니다. 이 장치는 8개의 준 양방향 포트, 100kHz I2C- 버스 인터페이스, 3개의 하드웨어 주소 입력 및 2.5V와 6V 사이에서 작동하는 인터럽트 출력. 준 양방향 포트는 인터럽트 상태 또는 키패드를 모니터링하기 위한 입력으로 또는 LED와 같은 표시 장치를 활성화하기 위한 출력으로 독립적으로 할당될 수 있습니다. 시스템 마스터는 단일 레지스터를 통해 입력 포트에서 읽거나 출력 포트에 쓸 수 있습니다. 2.5uA(일반, 정적)의 낮은 소비 전류는 모바일 애플리케이션에 적합하며 래치된 출력 포트가 직접 LED를 구동합니다. PCF8574와 PCF8574A는 슬레이브 주소의 다른 고정 부분을 제외하고 동일합니다. 3개의 하드웨어 주소 핀을 통해 각 장치 중 8개가 동일한 I2C 버스에 있을 수 있으므로 동일한 I2C 버스에 최대 16개의 I/O 확장기 PCF8574/74A가 있을 수 있으며 최대 128개의 I/O를 지원합니다. (예: 128 LED). 활성 LOW 오픈 드레인 인터럽트 출력(INT)은 마이크로컨트롤러의 인터럽트 로직에 연결될 수 있으며 입력 상태가 해당 입력 포트 레지스터 상태와 다를 때 활성화됩니다. 마이크로컨트롤러에 입력 상태가 변경되었으며 마이크로컨트롤러가 I2C 버스를 통해 입력 레지스터를 지속적으로 폴링하지 않고 장치를 조사해야 함을 나타내는 데 사용됩니다. 내부 POR(Power-On Reset)은 다음과 같이 I/O를 초기화합니다. 약한 내부 풀업 100uA 전류 소스가 있는 입력. PCF8574는 LED 간판 및 디스플레이, 서버, 키 패드, 산업 제어, 의료 장비, PLC, 휴대 전화, 모바일 장치, 게임기 및 계측 테스트 측정에 사용됩니다.

LibDriver PCF8574는 LibDriver에서 출시한 PCF8574의 전체 기능 드라이버입니다. I/O 쓰기, I/O 읽기 및 기타 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver PCF8574의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver PCF8574용 플랫폼 독립적인 IIC버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver PCF8574드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver PCF8574프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver PCF8574오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 PCF8574데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인 IIC버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

#### example basic

```C
#include "driver_pcf8574_basic.h"

uint8_t res;
pcf8574_pin_level_t level;

/* basic init */
res = pcf8574_basic_init(PCF8574_ADDRESS_A000);
if (res != 0)
{
    return 1;
}

...

/* read pin */
res = pcf8574_basic_read(PCF8574_PIN_0, (pcf8574_pin_level_t *)&level);
if (res != 0)
{
    (void)pcf8574_basic_deinit();

    return 1;
}

/* write pin */
res = pcf8574_basic_write(PCF8574_PIN_0, PCF8574_PIN_LEVEL_HIGH);
if (res != 0)
{
    (void)pcf8574_basic_deinit();

    return 1;
}

...

(void)pcf8574_basic_deinit();

return 0;
```

### 문서

온라인 문서: [https://www.libdriver.com/docs/pcf8574/index.html](https://www.libdriver.com/docs/pcf8574/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.