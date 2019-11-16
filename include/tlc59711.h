#ifndef _TLC59711_H
#define _TLC59711_H


/*!
 *  @brief  Class that stores state and functions for interacting with
 *          TLC59711 Senor
 */
class TLC59711 {
public:
  explicit TLC59711(uint8_t n);

  bool begin();
  void end();

  void setPWM(uint8_t chan, uint16_t pwm);
  void setLED(uint8_t lednum, uint16_t r, uint16_t g, uint16_t b);
  void write();
  void setBrightness(uint8_t bcr, uint8_t bcg, uint8_t bcb);
  void simpleSetBrightness(uint8_t BC);

private:
  uint16_t pwmbuffer[12] = {0};

  uint8_t BCr, BCg, BCb;
  int8_t numdrivers;
  bool initialized = false;
};

#endif
