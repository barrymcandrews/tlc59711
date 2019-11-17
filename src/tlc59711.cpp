#include <bcm2835.h>
#include <cstdio>
#include <cstring>
#include <ios>
#include <iomanip>
#include <iostream>
#include <bitset>
#include "tlc59711.h"


TLC59711::TLC59711(uint8_t n) {
  numdrivers = n;

  BCr = BCg = BCb = 0x7F; // default 100% brigthness
}

/*!
 *  @brief  Writes PWM buffer to board
 */
void TLC59711::write() {

  char command_buffer[28] = {0};
  uint32_t command;

  // Magic word for write
  command = 0x25;

  command <<= 5;
  // OUTTMG = 1, EXTGCK = 0, TMGRST = 1, DSPRPT = 1, BLANK = 0 -> 0x16
  command |= 0x16;

  command <<= 7;
  command |= BCr;

  command <<= 7;
  command |= BCg;

  command <<= 7;
  command |= BCb;

  command_buffer[0] = (char) ((command >> 24) & 0xff);
  command_buffer[1] = (char) ((command >> 16) & 0xff);
  command_buffer[2] = (char) ((command >> 8) & 0xff);
  command_buffer[3] = (char) ((command >> 0) & 0xff);

  uint8_t pwmbuffer_reversed[24];
  for (int i = 0; i < 24; i++) {
    pwmbuffer_reversed[i] = ((uint8_t *)pwmbuffer)[23 - i];
  }

  memcpy(command_buffer + 4, pwmbuffer_reversed, 24);
  bcm2835_spi_writenb(command_buffer, 28);

//  for (int i = 4; i < 6; i++) {
//    std::cout << i << "        ";
//  }
//  std::cout << std::endl;
//
//  for (int i = 4; i < 6; i++) {
//    std::bitset<8> x(command_buffer[i]);
//    std::cout << x << " ";
//  }
//  std::cout << std::endl;
}

/*!
 *  @brief  Set PWM value on selected channel
 *  @param  chan
 *          one from 12 channel (per driver) so there is 12 * number of drivers
 *  @param  pwm
 *          pwm value
 */
void TLC59711::setPWM(uint8_t chan, uint16_t pwm) {
  if (chan > 12 * numdrivers)
    return;
  pwmbuffer[chan] = pwm;
}

/*!
 *  @brief  Set RGB value for selected LED
 *  @param  lednum
 *          selected LED number that for which value will be set
 *  @param  r
 *          red value
 *  @param g
 *          green value
 *  @param b
 *          blue value
 */
void TLC59711::setLED(uint8_t lednum, uint16_t r, uint16_t g,
                               uint16_t b) {
  setPWM(lednum * 3, r);
  setPWM(lednum * 3 + 1, g);
  setPWM(lednum * 3 + 2, b);
}

/*!
 *  @brief  Set the brightness of LED channels to same value
 *  @param  BC
 *          Brightness Control value
 */
void TLC59711::simpleSetBrightness(uint8_t BC) {
  if (BC > 127) {
    BC = 127; // maximum possible value since BC can only be 7 bit
  } else if (BC < 0) {
    BC = 0;
  }

  BCr = BCg = BCb = BC;
}

/*!
 *  @brief  Set the brightness of LED channels to specific value
 *  @param  bcr
 *          Brightness Control Red value
 *  @param  bcg
 *          Brightness Control Green value
 *  @param  bcb
 *          Brightness Control Blue value
 */
void TLC59711::setBrightness(uint8_t bcr, uint8_t bcg, uint8_t bcb) {
  if (bcr > 127) {
    bcr = 127; // maximum possible value since BC can only be 7 bit
  } else if (bcr < 0) {
    bcr = 0;
  }

  BCr = bcr;

  if (bcg > 127) {
    bcg = 127; // maximum possible value since BC can only be 7 bit
  } else if (bcg < 0) {
    bcg = 0;
  }

  BCg = bcg;

  if (bcb > 127) {
    bcb = 127; // maximum possible value since BC can only be 7 bit
  } else if (bcb < 0) {
    bcb = 0;
  }

  BCb = bcb;
}

/*!
 *  @brief  Begins SPI connection if there is not empty PWM buffer
 *  @return If successful returns true, otherwise false
 */
bool TLC59711::begin() {

  if (!bcm2835_init()) {
    printf("bcm2835_init failed. Are you running as root???\n");
    return false;
  }

  if (!bcm2835_spi_begin()) {
    printf("bcm2835_spi_begin failed. Are you running as root????\n");
    return false;
  }

  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536);
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
  
  return true;
}

void TLC59711::end() {
  bcm2835_spi_end();
}
