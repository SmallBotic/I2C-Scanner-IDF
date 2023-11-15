#ifndef I2C_DETECTOR_H_
#define I2C_DETECTOR_H_

#include <driver/gpio.h>

#include "esp_err.h"
#include "m_i2c.h"

/**
 * @brief Scan for I2C devices on the bus
 * @param i2c_port I2C port number to scan
 */
void i2c_scan(i2c_port_t i2c_port);

#endif  // I2C_DETECTOR_H_