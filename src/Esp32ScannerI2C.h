#ifndef _Esp32ScannerI2C_H__
#define _Esp32ScannerI2C_H__

#include <Arduino.h>
#include <Wire.h>

#define DEFAULT_UartSpeed 115200
#define DEFAULT_SdaPin 21
#define DEFAULT_SclPin 22


class Esp32ScannerI2C
{
  public:
  Esp32ScannerI2C();
  Esp32ScannerI2C(int sdaPin, int sclPin, int uartSpeed);
  ~Esp32ScannerI2C();

  int SdaPin;
  int SclPin;

  void SetUartSpeed (int value);                   
  void AttachI2CPins(int sdaPin, int sclPin);

  int UartSpeed;  

  byte **AddressesI2C;
  int AddressesCount;

  void Scan();  
  void Scan(int debug);  
  void PrintToUart();  

  private: 
  void clear();
}; 

#endif
