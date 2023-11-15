#include "m_i2c.h"

/**
 * @brief Initialize the I2C driver
 * 
 * @param i2c_num I2C port number
 * @param sda_io_num SDA pin number
 * @param scl_io_num SCL pin number
 * @param clk_speed Clock speed for the I2C bus
 */
esp_err_t m_i2c_master_init(i2c_port_t i2c_num, gpio_num_t sda_io_num,
                            gpio_num_t scl_io_num, uint32_t clk_speed) {
  i2c_config_t conf;
  conf.mode = I2C_MODE_MASTER;
  conf.sda_io_num = sda_io_num;
  conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
  conf.scl_io_num = scl_io_num;
  conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
  conf.master.clk_speed = clk_speed;
  conf.clk_flags = 0;

  i2c_param_config(i2c_num, &conf);
  i2c_driver_install(i2c_num, conf.mode, 0, 0, 0);
  return ESP_OK;
}

esp_err_t m_i2c_master_write_slave(i2c_port_t i2c_num, uint8_t *data_wr,
                                   size_t size, uint8_t slave_addr) {
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, slave_addr << 1 | I2C_MASTER_WRITE, true);
  i2c_master_write(cmd, data_wr, size, true);
  i2c_master_stop(cmd);
  esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_PERIOD_MS);
  i2c_cmd_link_delete(cmd);
  return ret;
}

esp_err_t m_i2c_master_read_slave(uint8_t slave_addr, uint8_t *data_rd,
                                  size_t size) {
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, slave_addr << 1 | I2C_MASTER_READ, true);
  if (size > 1) {
    i2c_master_read(cmd, data_rd, size - 1, I2C_MASTER_ACK);
  }
  i2c_master_read_byte(cmd, data_rd + size - 1, I2C_MASTER_NACK);
  i2c_master_stop(cmd);
  esp_err_t ret =
      i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
  i2c_cmd_link_delete(cmd);
  return ret;
}
