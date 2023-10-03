#ifndef M_I2C_H_
#define M_I2C_H_

#include "driver/i2c.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdbool.h>

/**
 * @brief Initialize the I2C bus as master
 * @param i2c_num I2C port number
 * @param sda_io_num GPIO number for I2C SDA
 * @param scl_io_num GPIO number for I2C SCL
 * @param clk_speed I2C clock speed
 * @return ESP_OK if successful, otherwise return ERROR CODE
 */
esp_err_t m_i2c_master_init(i2c_port_t i2c_num, gpio_num_t sda_io_num,
                            gpio_num_t scl_io_num, uint32_t clk_speed);

esp_err_t m_i2c_master_write_slave(i2c_port_t i2c_num, uint8_t *data_wr,
                                   size_t size, uint8_t slave_addr);

esp_err_t m_i2c_master_read_slave(uint8_t slave_addr, uint8_t *data_rd,
                                  size_t size);
#endif // M_I2C_H_