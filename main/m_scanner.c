#include "m_scanner.h"

void i2c_scan(i2c_port_t i2c_port) {
  int ret;
  int devices_found = 0;
  i2c_cmd_handle_t cmd;
  ESP_LOGI("SCANNER", "Scanning I2C bus...\n");
  for (int i = 0; i < 128; i++) {
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, i << 1 | I2C_MASTER_WRITE, true);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(i2c_port, cmd, 1000 / portTICK_PERIOD_MS);
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