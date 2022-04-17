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
 * @file      driver_pcf8574_basic.c
 * @brief     driver pcf8574 basic source file
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

#include "driver_pcf8574_basic.h"

static pcf8574_handle_t gs_handle;        /**< pcf8574 handle */

/**
 * @brief     basic example init
 * @param[in] addr is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t pcf8574_basic_init(pcf8574_address_t addr)
{
    uint8_t res;
    
    /* link functions */
    DRIVER_PCF8574_LINK_INIT(&gs_handle, pcf8574_handle_t);
    DRIVER_PCF8574_LINK_IIC_INIT(&gs_handle, pcf8574_interface_iic_init);
    DRIVER_PCF8574_LINK_IIC_DEINIT(&gs_handle, pcf8574_interface_iic_deinit);
    DRIVER_PCF8574_LINK_IIC_READ_COMMAND(&gs_handle, pcf8574_interface_iic_read_cmd);
    DRIVER_PCF8574_LINK_IIC_WRITE_COMMAND(&gs_handle, pcf8574_interface_iic_write_cmd);
    DRIVER_PCF8574_LINK_DELAY_MS(&gs_handle, pcf8574_interface_delay_ms);
    DRIVER_PCF8574_LINK_DEBUG_PRINT(&gs_handle, pcf8574_interface_debug_print);
    
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
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t pcf8574_basic_deinit(void)
{
    if (pcf8574_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief      basic example read
 * @param[in]  pin is the read pin
 * @param[out] *level points to a pin level buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t pcf8574_basic_read(pcf8574_pin_t pin, pcf8574_pin_level_t *level)
{
    if (pcf8574_read(&gs_handle, pin, level) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief     basic example write
 * @param[in] pin is the write pin
 * @param[in] level is the pin level
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
uint8_t pcf8574_basic_write(pcf8574_pin_t pin, pcf8574_pin_level_t level)
{
    if (pcf8574_write(&gs_handle, pin, level) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
