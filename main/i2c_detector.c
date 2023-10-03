#include "i2c_detector.h"

void i2c_scan() {
  i2c_config_t conf;
  conf.mode = I2C_MODE_MASTER;
  conf.sda_io_num = 22;
  conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
  conf.scl_io_num = 21;
  conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
  conf.master.clk_speed = 100000;
  conf.clk_flags = 0;

  i2c_param_config(I2C_NUM_0, &conf);
  i2c_driver_install(I2C_NUM_0, conf.mode, 0, 0, 0);

  int i;
  int ret;
  int devices_found = 0;
  uint8_t data[2];
  uint8_t addr;
  i2c_cmd_handle_t cmd;
  printf("Scanning I2C bus...\n");
  for (i = 0; i < 128; i++) {
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, i << 1 | I2C_MASTER_WRITE, true);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    if (ret == ESP_OK) {
      devices_found++;
      printf("- Device found at address 0x%02x\n", i);
    }
  }
  if (devices_found == 0) {
    printf("No I2C devices found\n");
  }
}