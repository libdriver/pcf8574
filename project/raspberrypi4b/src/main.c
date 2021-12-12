/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-08-29
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/08/29  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_pcf8574_read_write_test.h"
#include "driver_pcf8574_basic.h"
#include <stdlib.h>

/**
 * @brief     pcf8574 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t pcf8574(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            pcf8574_info_t info;
            
            /* print pcf8574 info */
            pcf8574_info(&info);
            pcf8574_interface_debug_print("pcf8574: chip is %s.\n", info.chip_name);
            pcf8574_interface_debug_print("pcf8574: manufacturer is %s.\n", info.manufacturer_name);
            pcf8574_interface_debug_print("pcf8574: interface is %s.\n", info.interface);
            pcf8574_interface_debug_print("pcf8574: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
            pcf8574_interface_debug_print("pcf8574: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            pcf8574_interface_debug_print("pcf8574: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            pcf8574_interface_debug_print("pcf8574: max current is %0.2fmA.\n", info.max_current_ma);
            pcf8574_interface_debug_print("pcf8574: max temperature is %0.1fC.\n", info.temperature_max);
            pcf8574_interface_debug_print("pcf8574: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            pcf8574_interface_debug_print("pcf8574: SCL connected to GPIO3(BCM).\n");
            pcf8574_interface_debug_print("pcf8574: SDA connected to GPIO2(BCM).\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show pcf8574 help */
            
            help:
            
            pcf8574_interface_debug_print("pcf8574 -i\n\tshow pcf8574 chip and driver information.\n");
            pcf8574_interface_debug_print("pcf8574 -h\n\tshow pcf8574 help.\n");
            pcf8574_interface_debug_print("pcf8574 -p\n\tshow pcf8574 pin connections of the current board.\n");
            pcf8574_interface_debug_print("pcf8574 -t readwrite <times> -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)\n\t"
                                          "run pcf8574 read write test.times means test times.\n");
            pcf8574_interface_debug_print("pcf8574 -c basic -i -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -p (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)\n\t"
                                          "run pcf8574 read function.\n");
            pcf8574_interface_debug_print("pcf8574 -c basic -o (0 | 1) -a (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7) -p (0 | 1 | 2 | 3 | 4 | 5 | 6 | 7)\n\t"
                                          "run pcf8574 write function.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 6)
    {
        if (strcmp("-t", argv[1]) == 0)
        {
            if (strcmp("readwrite", argv[2]) == 0)
            {
                if (strcmp("-a", argv[4]) == 0)
                {
                    volatile uint8_t res;
                    volatile uint32_t times;
                    pcf8574_address_t addr;
                    
                    if (strcmp("0", argv[5]) == 0)
                    {
                        addr = PCF8574_ADDRESS_A000;
                    }
                    else if (strcmp("1", argv[5]) == 0)
                    {
                        addr = PCF8574_ADDRESS_A001;
                    }
                    else if (strcmp("2", argv[5]) == 0)
                    {
                        addr = PCF8574_ADDRESS_A010;
                    }
                    else if (strcmp("3", argv[5]) == 0)
                    {
                        addr = PCF8574_ADDRESS_A011;
                    }
                    else if (strcmp("4", argv[5]) == 0)
                    {
                        addr = PCF8574_ADDRESS_A100;
                    }
                    else if (strcmp("5", argv[5]) == 0)
                    {
                        addr = PCF8574_ADDRESS_A101;
                    }
                    else if (strcmp("6", argv[5]) == 0)
                    {
                        addr = PCF8574_ADDRESS_A110;
                    }
                    else if (strcmp("7", argv[5]) == 0)
                    {
                        addr = PCF8574_ADDRESS_A111;
                    }
                    else
                    {
                        return 5;
                    }
                    
                    /* get times */
                    times = atoi(argv[3]);
                    
                    /* run test */
                    res = pcf8574_read_write_test(addr, times);
                    if (res)
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 5;
                }
            }
            else
            {
                return 5;
            }
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 8)
    {
        if (strcmp("-c", argv[1]) == 0)
        {
            if (strcmp("basic", argv[2]) == 0)
            {
                if (strcmp("-i", argv[3]) == 0)
                {
                    if (strcmp("-a", argv[4]) == 0)
                    {
                        volatile uint8_t res;
                        pcf8574_address_t addr;
                        pcf8574_pin_t pin;
                        pcf8574_pin_level_t level;
                        
                        if (strcmp("0", argv[5]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A000;
                        }
                        else if (strcmp("1", argv[5]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A001;
                        }
                        else if (strcmp("2", argv[5]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A010;
                        }
                        else if (strcmp("3", argv[5]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A011;
                        }
                        else if (strcmp("4", argv[5]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A100;
                        }
                        else if (strcmp("5", argv[5]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A101;
                        }
                        else if (strcmp("6", argv[5]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A110;
                        }
                        else if (strcmp("7", argv[5]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A111;
                        }
                        else
                        {
                            return 5;
                        }
                        if (strcmp("-p", argv[6]) == 0)
                        {
                            if (strcmp("0", argv[7]) == 0)
                            {
                                pin = PCF8574_PIN_0;
                            }
                            else if (strcmp("1", argv[7]) == 0)
                            {
                                pin = PCF8574_PIN_1;
                            }
                            else if (strcmp("2", argv[7]) == 0)
                            {
                                pin = PCF8574_PIN_2;
                            }
                            else if (strcmp("3", argv[7]) == 0)
                            {
                                pin = PCF8574_PIN_3;
                            }
                            else if (strcmp("4", argv[7]) == 0)
                            {
                                pin = PCF8574_PIN_4;
                            }
                            else if (strcmp("5", argv[7]) == 0)
                            {
                                pin = PCF8574_PIN_5;
                            }
                            else if (strcmp("6", argv[7]) == 0)
                            {
                                pin = PCF8574_PIN_6;
                            }
                            else if (strcmp("7", argv[7]) == 0)
                            {
                                pin = PCF8574_PIN_7;
                            }
                            else
                            {
                                return 5;
                            }
                            
                            /* basic init */
                            res = pcf8574_basic_init(addr);
                            if (res)
                            {
                                return 1;
                            }
                            
                            /* read pin */
                            res = pcf8574_basic_read(pin, (pcf8574_pin_level_t *)&level);
                            if (res)
                            {
                                pcf8574_basic_deinit();
                                
                                return 1;
                            }
                            else
                            {
                                pcf8574_interface_debug_print("pcf8574: read %d pin is %d.\n", pin, level);
                                pcf8574_basic_deinit();
                                
                                return 0;
                            }
                        }
                        else
                        {
                            return 5;
                        }
                    }
                    else
                    {
                        return 5;
                    }
                }
                else
                {
                    return 5;
                }
            }
            else
            {
                return 5;
            }
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 9)
    {
        if (strcmp("-c", argv[1]) == 0)
        {
            if (strcmp("basic", argv[2]) == 0)
            {
                if (strcmp("-o", argv[3]) == 0)
                {
                    if (strcmp("-a", argv[5]) == 0)
                    {
                        volatile uint8_t res;
                        pcf8574_address_t addr;
                        pcf8574_pin_t pin;
                        pcf8574_pin_level_t level;
                        
                        if (strcmp("0", argv[6]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A000;
                        }
                        else if (strcmp("1", argv[6]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A001;
                        }
                        else if (strcmp("2", argv[6]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A010;
                        }
                        else if (strcmp("3", argv[6]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A011;
                        }
                        else if (strcmp("4", argv[6]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A100;
                        }
                        else if (strcmp("5", argv[6]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A101;
                        }
                        else if (strcmp("6", argv[6]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A110;
                        }
                        else if (strcmp("7", argv[6]) == 0)
                        {
                            addr = PCF8574_ADDRESS_A111;
                        }
                        else
                        {
                            return 5;
                        }
                        if (strcmp("-p", argv[7]) == 0)
                        {
                            if (strcmp("0", argv[8]) == 0)
                            {
                                pin = PCF8574_PIN_0;
                            }
                            else if (strcmp("1", argv[8]) == 0)
                            {
                                pin = PCF8574_PIN_1;
                            }
                            else if (strcmp("2", argv[8]) == 0)
                            {
                                pin = PCF8574_PIN_2;
                            }
                            else if (strcmp("3", argv[8]) == 0)
                            {
                                pin = PCF8574_PIN_3;
                            }
                            else if (strcmp("4", argv[8]) == 0)
                            {
                                pin = PCF8574_PIN_4;
                            }
                            else if (strcmp("5", argv[8]) == 0)
                            {
                                pin = PCF8574_PIN_5;
                            }
                            else if (strcmp("6", argv[8]) == 0)
                            {
                                pin = PCF8574_PIN_6;
                            }
                            else if (strcmp("7", argv[8]) == 0)
                            {
                                pin = PCF8574_PIN_7;
                            }
                            else
                            {
                                return 5;
                            }
                            if (strcmp("0", argv[4]) == 0)
                            {
                                level = PCF8574_PIN_LEVEL_LOW;
                            }
                            else if (strcmp("1", argv[4]) == 0)
                            {
                                level = PCF8574_PIN_LEVEL_HIGH;
                            }
                            else
                            {
                                return 5;
                            }
                            
                            /* basic init */
                            res = pcf8574_basic_init(addr);
                            if (res)
                            {
                                return 1;
                            }
                            
                            /* write pin */
                            res = pcf8574_basic_write(pin, level);
                            if (res)
                            {
                                pcf8574_basic_deinit();
                                
                                return 1;
                            }
                            else
                            {
                                pcf8574_interface_debug_print("pcf8574: write %d pin level %d.\n", pin, level);
                                pcf8574_basic_deinit();
                                
                                return 0;
                            }
                        }
                        else
                        {
                            return 5;
                        }
                    }
                    else
                    {
                        return 5;
                    }
                }
                else
                {
                    return 5;
                }
            }
            else
            {
                return 5;
            }
        }
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = pcf8574(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        pcf8574_interface_debug_print("pcf8574: run failed.\n");
    }
    else if (res == 5)
    {
        pcf8574_interface_debug_print("pcf8574: param is invalid.\n");
    }
    else
    {
        pcf8574_interface_debug_print("pcf8574: unknow status code.\n");
    }

    return 0;
}
