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
 * @file      driver_pcf8574.h
 * @brief     driver pcf8574 header file
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

#ifndef DRIVER_PCF8574_H
#define DRIVER_PCF8574_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup pcf8574_driver pcf8574 driver function
 * @brief    pcf8574 driver modules
 * @{
 */

/**
 * @addtogroup pcf8574_base_driver
 * @{
 */

/**
 * @brief pcf8574 address enumeration definition
 */
typedef enum
{
    PCF8574_ADDRESS_A000 = 0,        /**< A2A1A0 000 */
    PCF8574_ADDRESS_A001 = 1,        /**< A2A1A0 001 */
    PCF8574_ADDRESS_A010 = 2,        /**< A2A1A0 010 */
    PCF8574_ADDRESS_A011 = 3,        /**< A2A1A0 011 */
    PCF8574_ADDRESS_A100 = 4,        /**< A2A1A0 100 */
    PCF8574_ADDRESS_A101 = 5,        /**< A2A1A0 101 */
    PCF8574_ADDRESS_A110 = 6,        /**< A2A1A0 110 */
    PCF8574_ADDRESS_A111 = 7,        /**< A2A1A0 111 */
} pcf8574_address_t;

/**
 * @brief pcf8574 pin enumeration definition
 */
typedef enum
{
    PCF8574_PIN_0 = 0x00,        /**< pin 0 */
    PCF8574_PIN_1 = 0x01,        /**< pin 1 */
    PCF8574_PIN_2 = 0x02,        /**< pin 2 */
    PCF8574_PIN_3 = 0x03,        /**< pin 3 */
    PCF8574_PIN_4 = 0x04,        /**< pin 4 */
    PCF8574_PIN_5 = 0x05,        /**< pin 5 */
    PCF8574_PIN_6 = 0x06,        /**< pin 6 */
    PCF8574_PIN_7 = 0x07,        /**< pin 7 */
} pcf8574_pin_t;

/**
 * @brief pcf8574 pin enumeration definition
 */
typedef enum
{
    PCF8574_PIN_LEVEL_LOW  = 0x00,        /**< low level */
    PCF8574_PIN_LEVEL_HIGH = 0x01,        /**< high level */
} pcf8574_pin_level_t;

/**
 * @brief pcf8574 handle structure definition
 */
typedef struct pcf8574_handle_s
{
    uint8_t iic_addr;                                                          /**< iic device address */
    uint8_t (*iic_init)(void);                                                 /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                               /**< point to an iic_deinit function address */
    uint8_t (*iic_read_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);         /**< point to an iic_read_cmd function address */
    uint8_t (*iic_write_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);        /**< point to an iic_write_cmd function address */
    void (*delay_ms)(uint32_t ms);                                             /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                           /**< point to a debug_print function address */
    uint8_t inited;                                                            /**< inited flag */
} pcf8574_handle_t;

/**
 * @brief pcf8574 information structure definition
 */
typedef struct pcf8574_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} pcf8574_info_t;

/**
 * @}
 */

/**
 * @defgroup pcf8574_link_driver pcf8574 link driver function
 * @brief    pcf8574 link driver modules
 * @ingroup  pcf8574_driver
 * @{
 */

/**
 * @brief     initialize pcf8574_handle_t structure
 * @param[in] HANDLE points to a pcf8574 handle structure
 * @param[in] STRUCTURE is pcf8574_handle_t
 * @note      none
 */
#define DRIVER_PCF8574_LINK_INIT(HANDLE, STRUCTURE)           memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to a pcf8574 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_PCF8574_LINK_IIC_INIT(HANDLE, FUC)            (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to a pcf8574 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_PCF8574_LINK_IIC_DEINIT(HANDLE, FUC)          (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read_cmd function
 * @param[in] HANDLE points to a pcf8574 handle structure
 * @param[in] FUC points to an iic_read_cmd function address
 * @note      none
 */
#define DRIVER_PCF8574_LINK_IIC_READ_COMMAND(HANDLE, FUC)    (HANDLE)->iic_read_cmd = FUC

/**
 * @brief     link iic_write_cmd function
 * @param[in] HANDLE points to a pcf8574 handle structure
 * @param[in] FUC points to an iic_write_cmd function address
 * @note      none
 */
#define DRIVER_PCF8574_LINK_IIC_WRITE_COMMAND(HANDLE, FUC)   (HANDLE)->iic_write_cmd = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to a pcf8574 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_PCF8574_LINK_DELAY_MS(HANDLE, FUC)            (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to a pcf8574 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_PCF8574_LINK_DEBUG_PRINT(HANDLE, FUC)         (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup pcf8574_base_driver pcf8574 base driver function
 * @brief    pcf8574 base driver modules
 * @ingroup  pcf8574_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to a pcf8574 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pcf8574_info(pcf8574_info_t *info);

/**
 * @brief     set the address pin
 * @param[in] *handle points to a pcf8574 handle structure
 * @param[in] addr_pin is the chip address pins
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t pcf8574_set_addr_pin(pcf8574_handle_t *handle, pcf8574_address_t addr_pin);

/**
 * @brief      get the address pin
 * @param[in]  *handle points to a pcf8574 handle structure
 * @param[out] *addr_pin points to a chip address pins buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pcf8574_get_addr_pin(pcf8574_handle_t *handle, pcf8574_address_t *addr_pin);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to a pcf8574 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 iic write failed
 * @note      none
 */
uint8_t pcf8574_init(pcf8574_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to a pcf8574 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pcf8574_deinit(pcf8574_handle_t *handle);

/**
 * @brief      read the pin
 * @param[in]  *handle points to a pcf8574 handle structure
 * @param[in]  pin is the read pin
 * @param[out] *level points to a level buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pcf8574_read(pcf8574_handle_t *handle, pcf8574_pin_t pin, pcf8574_pin_level_t *level);

/**
 * @brief     write the pin
 * @param[in] *handle points to a pcf8574 handle structure
 * @param[in] pin is the read pin
 * @param[in] level is the pin level
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pcf8574_write(pcf8574_handle_t *handle, pcf8574_pin_t pin, pcf8574_pin_level_t level);

/**
 * @brief     set the chip register
 * @param[in] *handle points to a pcf8574 handle structure
 * @param[in] *buf points to a data buffer.
 * @param[in] len is the data buffer
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t pcf8574_set_reg(pcf8574_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to a pcf8574 handle structure
 * @param[out] *buf points to a data buffer.
 * @param[in]  len is the data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t pcf8574_get_reg(pcf8574_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
