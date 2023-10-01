### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. PCF8574

#### 3.1 Command Instruction

1. Show pcf8574 chip and driver information.

   ```shell
   pcf8574 (-i | --information)
   ```

2. Show pcf8574 help.

   ```shell
   pcf8574 (-h | --help)
   ```

3. Show pcf8574 pin connections of the current board.

   ```shell
   pcf8574 (-p | --port)
   ```

4. Run pcf8574 read write test, num means test times.

   ```shell
   pcf8574 (-t readwrite | --test=readwrite) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]
   ```

5. Run pcf8574 read function.

   ```shell
   pcf8574 (-e input | --example=input) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--pin=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
   ```

6. Run pcf8574 write function.

   ```shell
   pcf8574 (-e output | --example=output) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--pin=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--level=<low | high>]
   ```

#### 3.2 Command Example

```shell
pcf8574 -i

pcf8574: chip is NXP PCF8574.
pcf8574: manufacturer is NXP.
pcf8574: interface is IIC.
pcf8574: driver version is 1.0.
pcf8574: min supply voltage is 2.5V.
pcf8574: max supply voltage is 6.0V.
pcf8574: max current is 200.00mA.
pcf8574: max temperature is 85.0C.
pcf8574: min temperature is -40.0C.
```

```shell
pcf8574 -p

pcf8574: SCL connected to GPIOB PIN8.
pcf8574: SDA connected to GPIOB PIN9.
```

```shell
pcf8574 -t readwrite --addr=0 --times=3

pcf8574: chip is NXP PCF8574.
pcf8574: manufacturer is NXP.
pcf8574: interface is IIC.
pcf8574: driver version is 1.0.
pcf8574: min supply voltage is 2.5V.
pcf8574: max supply voltage is 6.0V.
pcf8574: max current is 200.00mA.
pcf8574: max temperature is 85.0C.
pcf8574: min temperature is -40.0C.
pcf8574: start read write test.
pcf8574: read PIN 0 is 1.
pcf8574: read PIN 1 is 1.
pcf8574: read PIN 2 is 1.
pcf8574: read PIN 3 is 1.
pcf8574: write PIN 4 low.
pcf8574: write PIN 5 high.
pcf8574: write PIN 6 low.
pcf8574: write PIN 7 high.
pcf8574: read PIN 0 is 1.
pcf8574: read PIN 1 is 1.
pcf8574: read PIN 2 is 1.
pcf8574: read PIN 3 is 1.
pcf8574: write PIN 4 low.
pcf8574: write PIN 5 high.
pcf8574: write PIN 6 low.
pcf8574: write PIN 7 high.
pcf8574: read PIN 0 is 1.
pcf8574: read PIN 1 is 1.
pcf8574: read PIN 2 is 1.
pcf8574: read PIN 3 is 1.
pcf8574: write PIN 4 low.
pcf8574: write PIN 5 high.
pcf8574: write PIN 6 low.
pcf8574: write PIN 7 high.
pcf8574: finish read write test.
```

```shell
pcf8574 -e input --addr=0 --pin=1

pcf8574: read 1 pin is 1.
```

```shell
pcf8574 -e output --addr=0 --pin=7 --level=LOW

pcf8574: write 7 pin level 0.
```

```shell
pcf8574 -h

Usage:
  pcf8574 (-i | --information)
  pcf8574 (-h | --help)
  pcf8574 (-p | --port)
  pcf8574 (-t readwrite | --test=readwrite) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]
  pcf8574 (-e input | --example=input) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--pin=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
  pcf8574 (-e output | --example=output) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--pin=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]
          [--level=<LOW | HIGH>]

Options:
      --addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>
                              Set the addr pin.([default: 0])
  -e <input | outoput>, --example=<input | output>
                              Run the driver example.
  -h, --help                  Show the help.
  -i, --information           Show the chip information.
  -p, --port                  Display the pin connections of the current board.
      --pin=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>
                              Set the used pin.([default: 0])
      --level=<LOW | HIGH>    Set the output level.([default: LOW])
  -t <readwrite>, --test=<readwrite>
                              Run the driver test.
      --times=<num>           Set the running times.([default: 3])
```
