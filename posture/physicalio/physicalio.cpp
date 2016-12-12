#include <unistd.h>
#include <math.h>
#include <mraa/i2c.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "physicalio.hpp"

using namespace yamax;

const uint8_t servos::MODE1 = 0x00;
const uint8_t servos::PRESCALE = 0xFE;
const uint8_t servos::LED0 = 0x06;

servo::servo(uint16_t num, servos* servos){
  _servos = servos;
  _number = num;
  minPulseWidth = 0.5;
  maxPulseWidth = 2.5;
}

uint16_t servo::getNumber(void){
  return _number;
}

void servo::setDegrees(float degrees){
  _servos->setServoPulse(_number, minPulseWidth, maxPulseWidth, degrees);
  _degrees = degrees;
}

float servo::getDegrees(void){
  return _degrees;
}

servos::servos(uint8_t bus, uint16_t num, uint8_t baseadd){
  _pwmfreq = 50;
  setPWMFreq(_pwmfreq);
  if (!(_i2cc = new mraa::I2c(bus)))
    throw "I2C initialization failed";

  for(int i=0; i<ceil((double)(num-1)/16); i++)
    _boards.push_back(baseadd+i);

  for(uint8_t board : _boards){
    _i2cc->address(board);
    _i2cc->writeReg(MODE1, 0);
  }
  for(int i=0; i<num; i++)
    _servos.push_back(std::unique_ptr<servo>(new servo(i, this)));
  _number = num;
}

servos::servos(uint8_t bus, uint16_t num, uint8_t baseadd, float smin, float smax){
  _pwmfreq = 50;
  setPWMFreq(_pwmfreq);
  if (!(_i2cc = new mraa::I2c(bus)))
    throw "I2C initialization failed";

  for(int i=0; i<ceil((double)(num-1)/16); i++)
    _boards.push_back(baseadd+i);

  for(uint8_t board : _boards){
    _i2cc->address(board);
    _i2cc->writeReg(MODE1, 0);
  }
  for(int i=0; i<num; i++){
    servo* s = new servo(i, this);
    s->minPulseWidth = smin;
    s->maxPulseWidth = smax;
    _servos.push_back(std::unique_ptr<servo>(s));
  }
  _number = num;
}

void servos::setPWMFreq(float freq) {
    _pwmfreq = freq;
    uint8_t prescale = roundf(6103.515625 / (freq * 0.899683334F) - 1);
    for(uint8_t board : _boards){
      _i2cc->address(board);

      _i2cc->writeReg(MODE1, 0x10);  //sleep
      _i2cc->writeReg(PRESCALE, prescale);
      _i2cc->writeReg(MODE1, 0x00);  //wake up
      usleep(5000);
      _i2cc->writeReg(MODE1, 0xa1);  //enable auto increment
    }
}

uint8_t servos::setServoPulse(uint8_t n, float smin, float smax, float degrees) {
  if (degrees > 180)
    degrees = 180;
  if(degrees < 0)
    degrees = 0;
  //same as map(degress, 0, 180, SERVOMINP, SERVOMAXP);
  double pulse = 0.5 + ((smax - smin) / 180) * degrees;
  //same as roundf(map(pulse/(1000/PWMFREQ), 0.0, 1.0, 0.0, 4095.0));
  //std::cout << "requested board " << floor(n/16) << " among " << _boards.size() << std::endl;
  uint16_t d = roundf(4095.0 * (pulse/(1000/_pwmfreq)));
  _i2cc->address(_boards[floor(n/16)]);
  _i2cc->writeWordReg(LED0+4*(n%16)+2, d);
  return pulse;
}

uint16_t servos::getNumber(void){
  return _number;
}

servo servos::operator[](uint16_t num){
  return *_servos[num].get();
}
