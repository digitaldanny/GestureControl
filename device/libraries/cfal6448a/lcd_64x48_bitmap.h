#ifndef __bitmaps_h__
#define __bitmaps_h__

#include "build_switches.h"
#include "target_hw_common.h"
#include "spi_if.h"

#define _delay_ms(ms) delayMs(ms)
#define PROGMEM
#define pgm_read_byte(x) (*(const unsigned char *)(x))
#define pgm_read_word(x) (*(const unsigned long *)(x))

/*
 * LCD SPI & control lines
 *   HEADER   | Color  | LCD
 * -----------+--------+-------------------------
 *  P1.6      | Brown  | LCD_MOSI   (hardware SPI)
 *  P1.5      | Red    | LCD_SCK    (hardware SPI)
 *  P2.3      | Orange | LCD_RS     (gpio)
 *  P5.1      | Yellow | LCD_RESET  (gpio)
 *  P3.5      | Green  | LCD_CS_NOT (GPIO or SPI SS)
 *  P1.7      | N/A    | not used   (would be MISO)
 *
 */

#define CLR_MOSI  GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN6)  // P1.6
#define SET_MOSI  GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN6)
#define CLR_SCK   GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN5)  // P1.5
#define SET_SCK   GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN5)
#define CLR_RS    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN3)  // P2.3
#define SET_RS    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN3)
#define CLR_RESET GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1)  // P5.1
#define SET_RESET GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1)
#define CLR_CS    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN5)  // P3.5
#define SET_CS    GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN5)

typedef struct
  {
  unsigned char
    bitmap_data[6][64];
  } SCREEN_IMAGE;

/*
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
 * PROTOTYPES
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/

/*
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
 * DESCRIPTION: Spi_c
 * This class simply calls the SPI functions in "spi_if." The need for this class
 * comes from porting the Arduino drivers for this LCD to the MSP432. In an attempt
 * to modify as little code as possible, this file requires an object instantiation
 * called "SPI"
 * +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
*/
class Spi_c
{
public:
    void begin();
    uint8_t transfer(uint8_t data);
};
extern Spi_c SPI;

void lcd_setup( void );
void SPI_sendCommand(uint8_t command);
void SPI_sendData(uint8_t data);
void show_64_x_48_bitmap(const SCREEN_IMAGE *OLED_image);
void Set_Address(uint8_t column, uint8_t page);

/*
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
 * DEMO ONLY CODE / STRUCTURES
 * +=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+=====+
*/

#if ENABLE_UNIT_TEST_LCD_DEMO
void lcd_loop(void);
void lcd_test();

const SCREEN_IMAGE Logo_6448 PROGMEM =
  {
    {
      {0x00,0x00,0x00,0xC0,0xE0,0xF0,0xF8,0xFC,0x0E,0x07,0x03,0x03,0x07,0xCE,0xEC,0xF0,0xF8,0xFC,0xFE,0x07,0x03,0x03,0x07,0x0E,0xFC,0xF8,0xF0,0xE0,0xC0,0x00,0x00,0x00,0x00,0xF8,0xFE,0x17,0xF1,0xE0,0x00,0x78,0x7F,0x47,0xF8,0xF8,0x40,0x00,0x98,0xF8,0x60,0xF8,0x98,0x00,0x78,0x7F,0x47,0xF8,0xF8,0x40,0x00,0xEE,0xFF,0x11,0xFF,0xEE},
      {0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xB6,0xB6,0xB6,0xB6,0xB6,0xB6,0xB6,0xB6,0xB6,0xB6,0xB6,0xB6,0xB6,0x00,0x01,0x01,0x01,0x00,0x1C,0x8C,0xC4,0x74,0x3D,0x0D,0x0C,0x00,0x01,0x05,0xFC,0xFD,0x05,0x00,0x00,0x00,0x04,0xFD,0xFD,0x44,0x44,0xEC,0x1D,0x01,0x01,0x00},
      {0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x6D,0x00,0xC0,0xE0,0x30,0x10,0x16,0x37,0xE5,0xC4,0x04,0xF6,0xF7,0x00,0x00,0x04,0x07,0x07,0xF4,0xF0,0x10,0x10,0x14,0x17,0x07,0xF4,0xF0,0x10,0x10,0x70,0xE0,0x80},
      {0x00,0x00,0x00,0x03,0x07,0x0F,0x1F,0x3F,0x70,0xE0,0xC0,0xC0,0xE0,0x73,0x37,0x0F,0x1F,0x3F,0x7F,0xE0,0xC0,0xC0,0xE0,0x70,0x3F,0x1F,0x0F,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x04,0x04,0x04,0x00,0x00,0xFF,0xFF,0x00,0x00,0x80,0xFF,0x7F},
      {0xE0,0xF0,0x38,0x18,0x18,0x38,0x70,0x60,0x00,0xC0,0xC0,0x80,0xC0,0xC0,0xC0,0x00,0xC0,0xC0,0x00,0x80,0xC0,0x40,0xC0,0x80,0xC0,0xF0,0xF8,0xC0,0x00,0x80,0xC0,0x40,0xC0,0x80,0x00,0xF9,0xFB,0xC2,0xF2,0xFB,0xD9,0x00,0x80,0xC3,0xC3,0xC2,0x82,0x02,0xC2,0xC0,0x83,0xC3,0xC2,0x82,0xC2,0xF2,0xF8,0xC3,0x03,0xC2,0xC2,0xC3,0xC1,0xC0},
      {0x07,0x0F,0x1C,0x18,0x18,0x1C,0x0E,0x06,0x00,0x1F,0x1F,0x00,0x00,0xC1,0xDF,0x78,0x1F,0x01,0x00,0x0B,0x1B,0x12,0x1E,0x0E,0x00,0x0F,0x1F,0x18,0x00,0x0C,0x1E,0x12,0x1F,0x1F,0x00,0x1F,0x1F,0x00,0x1F,0x1F,0x00,0x00,0x0F,0x1F,0x18,0x1F,0x0F,0x00,0x1F,0x1F,0x00,0x00,0x1F,0x1F,0x00,0x0F,0x1F,0x18,0x00,0x18,0x1E,0x1F,0x1B,0x18},
    }
  };
  
const SCREEN_IMAGE Dimensions_6448 PROGMEM =
  {
    {
      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0x78,0x3E,0xFF,0xFF,0x3E,0x78,0xE0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
      {0x30,0x78,0x78,0xFC,0xFC,0xFE,0xB6,0x33,0x31,0x30,0x30,0x00,0xF0,0xFC,0x7E,0x37,0x33,0x31,0x30,0x30,0x70,0xE0,0xC0,0x00,0xF0,0xF8,0xDC,0xCE,0xC7,0xC3,0xC1,0xFF,0xFF,0xC0,0xC0,0x00,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x31,0x30,0x30,0x00,0xFF,0xFF,0x00,0x30,0x30,0x31,0x30,0x30,0x31,0x33,0xB6,0xFE,0xFC,0xFC,0x78,0x78,0x30},
      {0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x02,0x00,0x00,0x00,0x03,0x07,0x0E,0x0C,0x0C,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xC0,0x00,0x00,0x1F,0x1F,0x00,0x80,0xC0,0xC0,0xC0,0xC0,0xC2,0x83,0x01,0x01,0x00,0x00,0x00,0x00,0x00},
      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF8,0xDC,0xCE,0xC7,0xC3,0xC1,0xFF,0xFF,0xC0,0xC0,0x00,0xC0,0xEF,0x7F,0x39,0x30,0x30,0x30,0x39,0x7F,0xEF,0xC0,0x00,0x00,0x00,0x00,0x00},
      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x8F,0x0F,0x00,0x00,0xE0,0xE3,0x07,0x0E,0x0C,0x8C,0x0C,0x0C,0x0C,0x0E,0x07,0x03,0x00,0x00,0x00,0x00,0x00},
      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x1E,0x7C,0xFF,0xFF,0x7C,0x1E,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    }
  };

  
const SCREEN_IMAGE Left_Double_6448 PROGMEM =
  {
    {
      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
      {0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
      {0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    }
  };

const SCREEN_IMAGE Left_6448 PROGMEM =
  {
    {
      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
      {0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    }
  };

const SCREEN_IMAGE OLED_6448 PROGMEM =
  {
    {
      {0x00,0x00,0x00,0x00,0x80,0xE0,0xF0,0xFC,0x1E,0x07,0x07,0x07,0x1F,0xFE,0xF8,0xE0,0x00,0x00,0x00,0x00,0x00,0x02,0xFE,0xFE,0xFE,0xFE,0x7E,0x06,0x02,0x00,0x00,0x00,0x00,0x00,0x02,0x02,0xFE,0xFE,0xFE,0xFE,0x7E,0x0E,0x0E,0x0E,0x1E,0x7E,0xFE,0xFE,0x00,0x00,0x02,0x02,0xFE,0xFE,0xFE,0xFE,0x7E,0x0E,0x3C,0xFC,0xF8,0xE0,0x80,0x00},
      {0x00,0x00,0xE0,0xFC,0xFF,0xFF,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x80,0xE0,0x00,0x0F,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xF0},
      {0x80,0xFE,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xE0,0xE0,0xF0,0xF8,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0xFF,0x3F,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x01,0xFF,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x00,0x00,0xF0,0xFF,0xFF,0xFF,0x1F},
      {0x7F,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xFF,0xFF,0x3F,0x07,0x00,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00,0x80,0xF0,0x1C,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0x07,0x00,0x00,0x00,0x00,0x00,0x80,0xF0,0x1C,0x00,0x00,0x00,0xFE,0xFF,0xFF,0xFF,0x03,0x00,0x00,0x00,0x80,0xF8,0xFF,0xFF,0x1F,0x03,0x00},
      {0x00,0x07,0x3F,0x7F,0xFC,0xE0,0xE0,0xE0,0x78,0x3F,0x1F,0x07,0x01,0x00,0x00,0x00,0x40,0x60,0x7C,0x7F,0x7F,0x7F,0x7F,0x70,0x70,0x78,0x78,0x7E,0x7F,0x0F,0x40,0x60,0x7C,0x7F,0x7F,0x7F,0x7F,0x70,0x70,0x70,0x78,0x7C,0x7E,0x7F,0x0F,0x00,0x40,0x60,0x7C,0x7F,0x7F,0x7F,0x7F,0x70,0x70,0x38,0x3C,0x1F,0x0F,0x03,0x00,0x00,0x00,0x00},
    }
  };


const SCREEN_IMAGE Gear_0_6448 PROGMEM =
  {
    {
      {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xF8,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x07,0x0F,0x0F,0x1F,0x3F,0xBF,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xF0,0xF0,0xF0,0xF0,0xF0,0xF8,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE3,0xE0,0xC0,0xC0,0x80,0x80,0x80,0xC0,0xF0,0xF8,0xFC,0xFC,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0x1E,0x80,0x80,0xC0,0xC0,0xE3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8F,0x27,0xF3,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x3F,0x0F,0x07,0x07,0x0F,0x1F,0x1F,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x7F,0x3F},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xF9,0xF9,0xFC,0xFC,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0x7E,0x3E,0x18,0x00,0x7C,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x18,0x00,0x00,0x00,0x00,0x00},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0x07,0x07,0x07,0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0x0F,0x0F,0x0F,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF0,0xF0,0xE0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    }
  };

const SCREEN_IMAGE Gear_1_6448 PROGMEM =
  {
    {
      {0x00,0x00,0x00,0x00,0x80,0xF0,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC1,0xC1,0xC3,0x87,0x8F,0x0F,0x0F,0x0F,0x0F,0x0F,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xF0,0xF0,0xF0,0xF0,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xE0,0xE0,0xE0,0xC0,0xC0,0xC0,0xE0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x07,0xC0,0xE0,0xF0,0xF0,0xF0,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE7,0xC3,0x9D,0x3E,0x3F,0x3F,0x3F,0xBF,0xBF,0xBF,0xFF,0xDF,0xCF,0xCF,0xC7,0xC3,0xC3,0x87,0x0F,0x1F,0x9F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x0F,0x07,0x02,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x07,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xFC,0xF8,0xF8,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    }
  };

const SCREEN_IMAGE Gear_2_6448 PROGMEM =
  {
    {
      {0x00,0x00,0xE0,0xF8,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xE0,0xF0,0xE0,0xE0,0xC0,0x00,0x01,0x03,0x03,0x03,0x03,0x03,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xF0,0xF0,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xE0,0xE0,0xE0,0xE0,0xC0,0xF0,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0xC0,0xE0,0xF0,0xF8,0xFC,0xFC,0xFC,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF1,0xE0,0xC7,0x8F,0x8F,0x8F,0xCF,0xEF,0xEF,0xEF,0xF7,0xF7,0xF3,0xF3,0xF1,0xF1,0xF1,0xE3,0x07,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x3F,0x1F,0x1F,0x07,0x03,0x08,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x1F},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xC0,0x80,0xC0,0xC0,0xC0,0xC0,0xC0,0x80,0x83,0x03,0x07,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x3E,0x3E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    }
  };

const SCREEN_IMAGE Gear_3_6448 PROGMEM =
  {
    {
      {0xF0,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xF8,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xE0,0xF0,0xF8,0xF8,0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x81,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xF7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,0xF0,0xE0,0xE0,0xF8,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x0F,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF8,0xF0,0xE1,0xC1,0xC1,0xE1,0xF1,0xF9,0xF9,0xFF,0xFD,0xFD,0xFC,0xFC,0xFC,0xFE,0x7C,0x99,0xC3,0xE7,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x9F,0x1F,0x0F,0x0F,0x07,0x03,0x01,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x0F,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x3F,0x7F,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF1,0xF3,0xE3,0xE1,0xC0,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x1F,0x1F,0x0F,0x0F,0x07,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    }
  };

const SCREEN_IMAGE Gear_4_6448 PROGMEM =
  {
    {
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFC,0xFC,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xE0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xF8,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x07,0x00,0x3C,0x3E,0x7E,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x3F,0x3F,0xBF,0x9F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xF8,0xF0,0xF0,0xF0,0xF8,0xFC,0xFE,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0xCF,0xE4,0xF1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xEF,0x87,0x03,0x03,0x01,0x00,0x7F,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x1F,0x1F,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xF8,0xF8,0xF8,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x07,0x0F},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x1F,0x07,0x0F,0x0F,0x0F,0x07,0x07,0x07,0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    }
  };

const SCREEN_IMAGE Gear_5_6448 PROGMEM =
  {
    {
      {0xFF,0xFF,0xFC,0xF8,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFE,0xFE,0xFC,0x80,0x00,0x00,0x00,0x80,0xC0,0xC0,0xE0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0xF8,0xF8,0xF0,0xF0,0xF0,0xF0,0xF0,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xBF,0x0F,0x03,0x00,0x00,0x07,0x07,0x0F,0x0F,0x0F,0x9F,0x9F,0xDF,0xDF,0xDF,0xDF,0xEF,0xEF,0xCF,0x9F,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xF8,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x9F,0xE7,0xF1,0xF8,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x3F,0x7F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFB,0xE1,0x80,0x00,0x10,0x3F,0x7F,0xFF,0xBF,0xBF,0x9F,0x1F,0x0F,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x3E,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x07,0x0F,0x0F,0x0F,0x07},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x1F,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    }
  };

const SCREEN_IMAGE Gear_6_6448 PROGMEM =
  {
    {
      {0xF8,0xF0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0xF0,0xF8,0xFC,0xFF,0xFF,0xFF,0xFE,0xFC,0x80,0x00,0x00,0x00,0x00,0xE0,0xF0,0xF0,0xF8,0xFC,0xFC,0xFE,0xFE,0xFE,0xFE,0xFC,0xFC,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xF8,0xF8,0xF8,0xF8,0xF8,0xF0,0xF0,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x8F,0x80,0x00,0x00,0x00,0x00,0x00,0x01,0xC1,0xC3,0xE3,0xE3,0xF7,0xF7,0xF7,0xFF,0xFB,0xF3,0xE3,0x03,0x1F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,0xCF,0xF3,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,0x3F,0x3F,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xF8,0xE0,0x86,0xCF,0xDF,0xDF,0xEF,0xEF,0xE7,0xE7,0xE7,0xE3,0xC1,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x10,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7E,0x00},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x7F,0x7F,0x3F,0x3F,0x1F,0x0F,0x07,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x0F,0x0F,0x0F,0x0F,0x01,0x00,0x00},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xDF,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    }
  };

const SCREEN_IMAGE Gear_7_6448 PROGMEM =
  {
    {
      {0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xF0,0xF8,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x3E,0x3E,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xF8,0xF0,0xF0,0xF0,0xF8,0xF8,0xF8,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC7,0xC0,0x80,0x80,0x00,0x00,0x00,0xC0,0xE0,0xF0,0xF0,0xF8,0xF8,0xFC,0xFC,0xFF,0xFF,0xFC,0x38,0x00,0x00,0x83,0x9F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x1F,0x8F,0xE7,0xF9,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x1F,0x0F,0x1F,0x1F,0x3F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x3F},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xF9,0xE3,0xE7,0xF7,0xF3,0xFB,0xFB,0xF9,0xF9,0xF9,0xF8,0xF8,0xF8,0xF8,0xF0,0x40,0x00,0x00,0x38,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3C,0x00,0x00,0x00},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x1F,0x1F,0x1F,0x1F,0x0F,0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x0F,0x0F,0x0F,0x0F,0x03,0x00,0x00,0x00,0x00,0x00},
      {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xE0,0xE0,0xE0,0xE0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    }
  };
#endif // ENABLE_UNIT_TEST_LCD_DEMO

#endif // __bitmaps_h__


