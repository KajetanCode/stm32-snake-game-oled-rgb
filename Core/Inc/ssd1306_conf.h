#ifndef SSD1306_CONF_H
#define SSD1306_CONF_H

#include "i2c.h"

/* wybór interfejsu I2C */
#define SSD1306_I2C_PORT hi2c1

/* adres OLED (HAL używa 8-bit!) */
#define SSD1306_I2C_ADDR (0x3C << 1)

#define SSD1306_INCLUDE_FONT_6x8

#define SSD1306_USE_I2C

#endif
