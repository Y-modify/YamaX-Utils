#pragma once

#include <unistd.h>
#include <vector>
#include <memory>
#include <mraa/i2c.hpp>

namespace yamax
{
  class servos;
  class servo;

  class servo
  {
  public:
      servo(uint16_t num, servos* servos);
      uint16_t getNumber(void);
      void setDegrees(float degrees);
      float getDegrees(void);
      float minPulseWidth;
      float maxPulseWidth;
  private:
      float _degrees;
      servos* _servos;
      uint16_t _number;
  };

  class servos
  {
  public:
      servos(uint8_t bus, uint16_t num, uint8_t baseadd=0x40);
      servos(uint8_t bus, uint16_t num, uint8_t baseadd, float smin, float smax);
      uint16_t getNumber(void);
      void setPWMFreq(float freq);
      uint8_t setServoPulse(uint8_t n, float smin, float smax, float degrees);
      servo operator[](uint16_t num);
  private:
      std::vector<uint8_t> _boards;
      std::vector<std::unique_ptr<servo>> _servos;
      mraa::I2c* _i2cc;
      uint16_t _number;
      float _pwmfreq;

      static const uint8_t MODE1;
      static const uint8_t PRESCALE;
      static const uint8_t LED0;
  };

  /*
  class IMU
  {
  public:
      IMU(uint8_t busnum, uint8_t address);
      uint8_t* gyro(void);
      uint8_t* compass(void);
      uint8_t* accel(void);
  };
  */
}
