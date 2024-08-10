[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PCF8574

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pcf8574/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The PCF8574/74A provides general-purpose remote I/O expansion via the two-wire bidirectional I2C-bus (serial clock (SCL), serial data (SDA)).The devices consist of eight quasi-bidirectional ports, 100 kHz I2C-bus interface, three hardware address inputs and interrupt output operating between 2.5 V and 6 V. The quasi-bidirectional port can be independently assigned as an input to monitor interrupt status or keypads, or as an output to activate indicator devices such as LEDs. System master can read from the input port or write to the output port through a single register. The low current consumption of 2.5 uA (typical, static) is great for mobile applications and the latched output ports directly drive LEDs.The PCF8574 and PCF8574A are identical, except for the different fixed portion of the slave address. The three hardware address pins allow eight of each device to be on the same I2C-bus, so there can be up to 16 of these I/O expanders PCF8574/74A together on the same I2C-bus, supporting up to 128 I/Os (for example, 128 LEDs).The active LOW open-drain interrupt output (INT) can be connected to the interrupt logic of the microcontroller and is activated when any input state differs from its corresponding input port register state. It is used to indicate to the microcontroller that an input state has changed and the device needs to be interrogated without the microcontroller continuously polling the input register via the I2C-bus.The internal Power-On Reset (POR) initializes the I/Os as inputs with a weak internal pull-up 100 uA current source. PCF8574 is used in LED signs and displays, servers, key pads, industrial control, medical equipment, PLC, cellular telephones, mobile devices, gaming machines and instrumentation test measurement.

LibDriver PCF8574 is a full function driver of PCF8574 launched by LibDriver.It provides I/O writing, I/O reading and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver PCF8574 source files.

/interface includes LibDriver PCF8574 IIC platform independent template.

/test includes LibDriver PCF8574 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver PCF8574 sample code.

/doc includes LibDriver PCF8574 offline document.

/datasheet includes PCF8574 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

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

### Document

Online documents: [https://www.libdriver.com/docs/pcf8574/index.html](https://www.libdriver.com/docs/pcf8574/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.