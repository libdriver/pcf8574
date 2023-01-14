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
 * @file      driver_pcf8574_read_write_test.c
 * @brief     driver pcf8574 read write test source file
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

static pcf8574_handle_t gs_handle;        /**< pcf8574 handle */

/**
 * @brief     read write test
 * @param[in] addr is the iic device address
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t pcf8574_read_write_test(pcf8574_address_t addr, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    pcf8574_info_t info;
    pcf8574_pin_level_t level;
    
    /* link functions */
    DRIVER_PCF8574_LINK_INIT(&gs_handle, pcf8574_handle_t);
    DRIVER_PCF8574_LINK_IIC_INIT(&gs_handle, pcf8574_interface_iic_init);
    DRIVER_PCF8574_LINK_IIC_DEINIT(&gs_handle, pcf8574_interface_iic_deinit);
    DRIVER_PCF8574_LINK_IIC_READ_COMMAND(&gs_handle, pcf8574_interface_iic_read_cmd);
    DRIVER_PCF8574_LINK_IIC_WRITE_COMMAND(&gs_handle, pcf8574_interface_iic_write_cmd);
    DRIVER_PCF8574_LINK_DELAY_MS(&gs_handle, pcf8574_interface_delay_ms);
    DRIVER_PCF8574_LINK_DEBUG_PRINT(&gs_handle, pcf8574_interface_debug_print);
    
    /* pcf8574 info */
    res = pcf8574_info(&info);
    if (res != 0)
    {
        pcf8574_interface_debug_print("pcf8574: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        pcf8574_interface_debug_print("pcf8574: chip is %s.\n", info.chip_name);
        pcf8574_interface_debug_print("pcf8574: manufacturer is %s.\n", info.manufacturer_name);
        pcf8574_interface_debug_print("pcf8574: interface is %s.\n", info.interface);
        pcf8574_interface_debug_print("pcf8574: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        pcf8574_interface_debug_print("pcf8574: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        pcf8574_interface_debug_print("pcf8574: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        pcf8574_interface_debug_print("pcf8574: max current is %0.2fmA.\n", info.max_current_ma);
        pcf8574_interface_debug_print("pcf8574: max temperature is %0.1fC.\n", info.temperature_max);
        pcf8574_interface_debug_print("pcf8574: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* set addr pin */
    res = pcf8574_set_addr_pin(&gs_handle, addr);
    if (res != 0)
    {
        pcf8574_interface_debug_print("pcf8574: set addr pin failed.\n");
       
        return 1;
    }
    
    /* pcf8574 init */
    res = pcf8574_init(&gs_handle);
    if (res != 0)
    {
        pcf8574_interface_debug_print("pcf8574: init failed.\n");
       
        return 1;
    }
    
    /* start read test */
    pcf8574_interface_debug_print("pcf8574: start read write test.\n");
    
    for (i = 0; i < times; i++)
    {
        /* read pin 0 */
        res = pcf8574_read(&gs_handle, PCF8574_PIN_0, &level);
        if (res != 0)
        {
            pcf8574_interface_debug_print("pcf8574: read failed.\n");
            (void)pcf8574_deinit(&gs_handle);
           
            return 1;
        }
        pcf8574_interface_debug_print("pcf8574: read PIN 0 is %d.\n", level);
        
        /* read pin 1 */
        res = pcf8574_read(&gs_handle, PCF8574_PIN_1, &level);
        if (res != 0)
        {
            pcf8574_interface_debug_print("pcf8574: read failed.\n");
            (void)pcf8574_deinit(&gs_handle);
           
            return 1;
        }
        pcf8574_interface_debug_print("pcf8574: read PIN 1 is %d.\n", level);
        
        /* read pin 2 */
        res = pcf8574_read(&gs_handle, PCF8574_PIN_2, &level);
        if (res != 0)
        {
            pcf8574_interface_debug_print("pcf8574: read failed.\n");
            (void)pcf8574_deinit(&gs_handle);
           
            return 1;
        }
        pcf8574_interface_debug_print("pcf8574: read PIN 2 is %d.\n", level);
        
        /* read pin 3 */
        res = pcf8574_read(&gs_handle, PCF8574_PIN_3, &level);
        if (res != 0)
        {
            pcf8574_interface_debug_print("pcf8574: read failed.\n");
            (void)pcf8574_deinit(&gs_handle);
           
            return 1;
        }
        pcf8574_interface_debug_print("pcf8574: read PIN 3 is %d.\n", level);
        
        /* write pin 4 */
        res = pcf8574_write(&gs_handle, PCF8574_PIN_4, PCF8574_PIN_LEVEL_LOW);
        if (res != 0)
        {
            pcf8574_interface_debug_print("pcf8574: write failed.\n");
            (void)pcf8574_deinit(&gs_handle);
           
            return 1;
        }
        pcf8574_interface_debug_print("pcf8574: write PIN 4 low.\n");
        
        /* write pin 5 */
        res = pcf8574_write(&gs_handle, PCF8574_PIN_5, PCF8574_PIN_LEVEL_HIGH);
        if (res != 0)
        {
            pcf8574_interface_debug_print("pcf8574: write failed.\n");
            (void)pcf8574_deinit(&gs_handle);
           
            return 1;
        }
        pcf8574_interface_debug_print("pcf8574: write PIN 5 high.\n");
        
        /* write pin 6 */
        res = pcf8574_write(&gs_handle, PCF8574_PIN_6, PCF8574_PIN_LEVEL_LOW);
        if (res != 0)
        {
            pcf8574_interface_debug_print("pcf8574: write failed.\n");
            (void)pcf8574_deinit(&gs_handle);
           
            return 1;
        }
        pcf8574_interface_debug_print("pcf8574: write PIN 6 low.\n");
        
        /* write pin 7 */
        res = pcf8574_write(&gs_handle, PCF8574_PIN_7, PCF8574_PIN_LEVEL_HIGH);
        if (res != 0)
        {
            pcf8574_interface_debug_print("pcf8574: write failed.\n");
            (void)pcf8574_deinit(&gs_handle);
           
            return 1;
        }
        pcf8574_interface_debug_print("pcf8574: write PIN 7 high.\n");
        
        /* delay 1000 ms */
        pcf8574_interface_delay_ms(1000);
    }
    
    /* finish read test */
    pcf8574_interface_debug_print("pcf8574: finish read write test.\n");  
    (void)pcf8574_deinit(&gs_handle);
    
    return 0;
}
