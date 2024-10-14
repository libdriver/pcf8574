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
 * @file      driver_pcf8574.c
 * @brief     driver pcf8574 source file
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

#include "driver_pcf8574.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "NXP PCF8574"        /**< chip name */
#define MANUFACTURER_NAME         "NXP"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.5f                 /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        6.0f                 /**< chip max supply voltage */
#define MAX_CURRENT               200.0f               /**< chip max current */
#define TEMPERATURE_MIN           -40.0f               /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                /**< chip max operating temperature */
#define DRIVER_VERSION            1000                 /**< driver version */

/**
 * @brief     set the address pin
 * @param[in] *handle points to a pcf8574 handle structure
 * @param[in] addr_pin is the chip address pins
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t pcf8574_set_addr_pin(pcf8574_handle_t *handle, pcf8574_address_t addr_pin)
{
    if (handle == NULL)                                  /* check handle */
    {
        return 2;                                        /* return error */
    }

    handle->iic_addr = 0x40;                             /* set iic addr */
    handle->iic_addr |= (uint8_t)(addr_pin << 1);        /* set iic address */
    
    return 0;                                            /* success return 0 */
}

/**
 * @brief      get the address pin
 * @param[in]  *handle points to a pcf8574 handle structure
 * @param[out] *addr_pin points to a chip address pins buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pcf8574_get_addr_pin(pcf8574_handle_t *handle, pcf8574_address_t *addr_pin)
{
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }

    *addr_pin = (pcf8574_address_t)((handle->iic_addr & (~0x40)) >> 1);        /*get iic address */
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t pcf8574_init(pcf8574_handle_t *handle)
{
    uint8_t data;
    
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->debug_print == NULL)                                     /* check debug_print */
    {
        return 3;                                                        /* return error */
    }
    if (handle->iic_init == NULL)                                        /* check iic_init */
    {
        handle->debug_print("pcf8574: iic_init is null.\n");             /* iic_init is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->iic_deinit == NULL)                                      /* check iic_deinit */
    {
        handle->debug_print("pcf8574: iic_deinit is null.\n");           /* iic_deinit is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->iic_read_cmd == NULL)                                    /* check iic_read_cmd */
    {
        handle->debug_print("pcf8574: iic_read_cmd is null.\n");         /* iic_read_cmd is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->iic_write_cmd == NULL)                                   /* check iic_write_cmd */
    {
        handle->debug_print("pcf8574: iic_write_cmd is null.\n");        /* iic_write_cmd is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->delay_ms == NULL)                                        /* check delay_ms */
    {
        handle->debug_print("pcf8574: delay_ms is null.\n");             /* delay_ms is null */
       
        return 3;                                                        /* return error */
    }
    
    if (handle->iic_init() != 0)                                         /* iic init */
    {
        handle->debug_print("pcf8574: iic init failed.\n");              /* iic init failed */
       
        return 1;                                                        /* return error */
    }
    data = 0xFF;                                                         /* set 0xFF */
    if (handle->iic_write_cmd(handle->iic_addr, 
                             (uint8_t *)&data, 1) != 0)                  /* write all pin high level */
    {
        handle->debug_print("pcf8574: iic write failed.\n");             /* iic write failed */
        (void)handle->iic_deinit();                                      /* iic deinit */
        
        return 4;                                                        /* return error */
    }
    handle->inited = 1;                                                  /* flag finish initialization */
    
    return 0;                                                            /* success return 0 */
}

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
uint8_t pcf8574_deinit(pcf8574_handle_t *handle)
{
    uint8_t res;
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    res = handle->iic_deinit();                                      /* iic deinit */
    if (res != 0)                                                    /* check error */
    {
        handle->debug_print("pcf8574: iic deinit failed.\n");        /* iic deinit failed */
       
        return 1;                                                    /* return error */
    }
    handle->inited = 0;                                              /* flag closed */
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t pcf8574_read(pcf8574_handle_t *handle, pcf8574_pin_t pin, pcf8574_pin_level_t *level)
{
    uint8_t res;
    uint8_t data;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = handle->iic_read_cmd(handle->iic_addr, (uint8_t *)&data, 1);        /* read data */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("pcf8574: iic read failed.\n");                   /* iic read failed */
       
        return 1;                                                             /* return error */
    }
    *level = (pcf8574_pin_level_t)((data >> pin) & 0x01);                     /* get level */
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t pcf8574_write(pcf8574_handle_t *handle, pcf8574_pin_t pin, pcf8574_pin_level_t level)
{
    uint8_t res;
    uint8_t data;
    
    if (handle == NULL)                                                       /* check handle */
    {
        return 2;                                                             /* return error */
    }
    if (handle->inited != 1)                                                  /* check handle initialization */
    {
        return 3;                                                             /* return error */
    }
    
    res = handle->iic_read_cmd(handle->iic_addr, (uint8_t *)&data, 1);        /* read data */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("pcf8574: iic read failed.\n");                   /* iic read failed */
       
        return 1;                                                             /* return error */
    }
    data &= ~(1 << pin);                                                      /* clear 0 */
    data |= level << pin;                                                     /* set data */
    res = handle->iic_write_cmd(handle->iic_addr, (uint8_t *)&data, 1);       /* write data */
    if (res != 0)                                                             /* check error */
    {
        handle->debug_print("pcf8574: iic write failed.\n");                  /* iic write failed */
       
        return 1;                                                             /* return error */
    }
    
    return 0;                                                                 /* success return 0 */
}

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
uint8_t pcf8574_set_reg(pcf8574_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    if (handle->iic_write_cmd(handle->iic_addr, buf, len) != 0)        /* write command */
    {
        return 1;                                                      /* return error */
    }
    else
    {
        return 0;                                                      /* success return 0 */
    }
}

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
uint8_t pcf8574_get_reg(pcf8574_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    if (handle->iic_read_cmd(handle->iic_addr, buf, len) != 0)        /* read command */
    {
        return 1;                                                     /* return error */
    }
    else
    {
        return 0;                                                     /* success return 0 */
    }
}

/**
 * @brief      get chip's information
 * @param[out] *info points to a pcf8574 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t pcf8574_info(pcf8574_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(pcf8574_info_t));                        /* initialize pcf8574 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
