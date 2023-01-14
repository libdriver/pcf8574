### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(pcf8574 REQUIRED)
```


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
./pcf8574 -i

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
./pcf8574 -p

pcf8574: SCL connected to GPIO3(BCM).
pcf8574: SDA connected to GPIO2(BCM).
```

```shell
./pcf8574 -t readwrite --addr=0 --times=3

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
./pcf8574 -e input --addr=0 --pin=1

pcf8574: read 1 pin is 1.
```

```shell
./pcf8574 -e output --addr=0 --pin=7 --level=LOW

pcf8574: write 7 pin level 0.
```

```shell
./pcf8574 -h

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

