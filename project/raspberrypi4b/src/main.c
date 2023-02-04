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
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief     pcf8574 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t pcf8574(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"pin", required_argument, NULL, 2},
        {"level", required_argument, NULL, 3},
        {"times", required_argument, NULL, 4},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    pcf8574_address_t addr = PCF8574_ADDRESS_A000;
    pcf8574_pin_t pin = PCF8574_PIN_0;
    pcf8574_pin_level_t level = PCF8574_PIN_LEVEL_LOW;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                /* set the addr pin */
                if (strcmp("0", optarg) == 0)
                {
                    addr = PCF8574_ADDRESS_A000;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    addr = PCF8574_ADDRESS_A001;
                }
                else if (strcmp("2", optarg) == 0)
                {
                    addr = PCF8574_ADDRESS_A010;
                }
                else if (strcmp("3", optarg) == 0)
                {
                    addr = PCF8574_ADDRESS_A011;
                }
                else if (strcmp("4", optarg) == 0)
                {
                    addr = PCF8574_ADDRESS_A100;
                }
                else if (strcmp("5", optarg) == 0)
                {
                    addr = PCF8574_ADDRESS_A101;
                }
                else if (strcmp("6", optarg) == 0)
                {
                    addr = PCF8574_ADDRESS_A110;
                }
                else if (strcmp("7", optarg) == 0)
                {
                    addr = PCF8574_ADDRESS_A111;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* pin */
            case 2 :
            {
                /* set the pin */
                if (strcmp("0", optarg) == 0)
                {
                    pin = PCF8574_PIN_0;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    pin = PCF8574_PIN_1;
                }
                else if (strcmp("2", optarg) == 0)
                {
                    pin = PCF8574_PIN_2;
                }
                else if (strcmp("3", optarg) == 0)
                {
                    pin = PCF8574_PIN_3;
                }
                else if (strcmp("4", optarg) == 0)
                {
                    pin = PCF8574_PIN_4;
                }
                else if (strcmp("5", optarg) == 0)
                {
                    pin = PCF8574_PIN_5;
                }
                else if (strcmp("6", optarg) == 0)
                {
                    pin = PCF8574_PIN_6;
                }
                else if (strcmp("7", optarg) == 0)
                {
                    pin = PCF8574_PIN_7;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* level */
            case 3 :
            {
                /* set the level */
                if (strcmp("LOW", optarg) == 0)
                {
                    level = PCF8574_PIN_LEVEL_LOW;
                }
                else if (strcmp("HIGH", optarg) == 0)
                {
                    level = PCF8574_PIN_LEVEL_HIGH;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* running times */
            case 4 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_readwrite", type) == 0)
    {
        uint8_t res;
        
        /* run test */
        res = pcf8574_read_write_test(addr, times);
        if (res != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_input", type) == 0)
    {
        uint8_t res;
        
        /* basic init */
        res = pcf8574_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* read pin */
        res = pcf8574_basic_read(pin, (pcf8574_pin_level_t *)&level);
        if (res != 0)
        {
            (void)pcf8574_basic_deinit();
            
            return 1;
        }
        
        /* output */
        pcf8574_interface_debug_print("pcf8574: read %d pin is %d.\n", pin, level);
        
        /* basic deinit */
        (void)pcf8574_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_output", type) == 0)
    {
        uint8_t res;
        
        /* basic init */
        res = pcf8574_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* write pin */
        res = pcf8574_basic_write(pin, level);
        if (res != 0)
        {
            (void)pcf8574_basic_deinit();
            
            return 1;
        }
        
        /* output */
        pcf8574_interface_debug_print("pcf8574: write %d pin level %d.\n", pin, level);
        
        /* basic deinit */
        (void)pcf8574_basic_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        pcf8574_interface_debug_print("Usage:\n");
        pcf8574_interface_debug_print("  pcf8574 (-i | --information)\n");
        pcf8574_interface_debug_print("  pcf8574 (-h | --help)\n");
        pcf8574_interface_debug_print("  pcf8574 (-p | --port)\n");
        pcf8574_interface_debug_print("  pcf8574 (-t readwrite | --test=readwrite) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--times=<num>]\n");
        pcf8574_interface_debug_print("  pcf8574 (-e input | --example=input) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--pin=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        pcf8574_interface_debug_print("  pcf8574 (-e output | --example=output) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>] [--pin=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>]\n");
        pcf8574_interface_debug_print("          [--level=<LOW | HIGH>]\n");
        pcf8574_interface_debug_print("\n");
        pcf8574_interface_debug_print("Options:\n");
        pcf8574_interface_debug_print("      --addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>\n");
        pcf8574_interface_debug_print("                              Set the addr pin.([default: 0])\n");
        pcf8574_interface_debug_print("  -e <input | output>, --example=<input | output>\n");
        pcf8574_interface_debug_print("                              Run the driver example.\n");
        pcf8574_interface_debug_print("  -h, --help                  Show the help.\n");
        pcf8574_interface_debug_print("  -i, --information           Show the chip information.\n");
        pcf8574_interface_debug_print("  -p, --port                  Display the pin connections of the current board.\n");
        pcf8574_interface_debug_print("      --pin=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7>\n");
        pcf8574_interface_debug_print("                              Set the used pin.([default: 0])\n");
        pcf8574_interface_debug_print("      --level=<LOW | HIGH>    Set the output level.([default: LOW])\n");
        pcf8574_interface_debug_print("  -t <readwrite>, --test=<readwrite>\n");
        pcf8574_interface_debug_print("                              Run the driver test.\n");
        pcf8574_interface_debug_print("      --times=<num>           Set the running times.([default: 3])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
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
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        pcf8574_interface_debug_print("pcf8574: SCL connected to GPIO3(BCM).\n");
        pcf8574_interface_debug_print("pcf8574: SDA connected to GPIO2(BCM).\n");
        
        return 0;
    }
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
        pcf8574_interface_debug_print("pcf8574: unknown status code.\n");
    }

    return 0;
}
