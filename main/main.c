#include "m_main.h"

void app_main(void) {
  esp_err_t e = m_i2c_master_init(I2C_NUM_0, GPIO_NUM_21 /*SDA*/,
                                  GPIO_NUM_22 /*SCL*/, 100000);

  printf("I2C init: %s.\n", esp_err_to_name(e));

  while (true) {
    i2c_scan();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
