#include "Arduino.h"

#include "Esp32ScannerI2C.h"

Esp32ScannerI2C::Esp32ScannerI2C()
{
    this->UartSpeed= DEFAULT_UartSpeed;
    this->SdaPin = DEFAULT_SdaPin;   
    this->SclPin = DEFAULT_SclPin;
    this->AddressesCount = 0;    
}

Esp32ScannerI2C::Esp32ScannerI2C(int sdaPin, int sclPin, int uartSpeed)
{
    this->UartSpeed= uartSpeed;
    this->SdaPin = sdaPin;   
    this->SclPin = sclPin;
    this->AddressesCount = 0;
}

Esp32ScannerI2C::~Esp32ScannerI2C() 
{

}

void Esp32ScannerI2C::SetUartSpeed(int value)
{
    this->UartSpeed = value;
}

void Esp32ScannerI2C::AttachI2CPins(int sdaPin, int sclPin)
{    
    this->SdaPin = sdaPin;   
    this->SclPin = sclPin;      
}
 
void Esp32ScannerI2C::clear()
{
  if(AddressesCount > 0)
  {
    for(int i = 0 ; i < this->AddressesCount ;i++)
    {
      free(AddressesI2C[i]);
    }

    free(AddressesI2C);

    this->AddressesCount = 0;
  }
}

void Esp32ScannerI2C::Scan()
{
  this->Scan(0);
}

void Esp32ScannerI2C::Scan(int debug)
{
  this->clear();

  Wire.begin();
  
  byte error, address;
  int nDevices;

  if(debug != 0)
  {
    Serial.begin(this->UartSpeed);
    while (!Serial);             
    Serial.println("\nScan I2C");
  }

  nDevices = 0;

  for(address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if(error == 0 || error==4)
    {
      if(this->AddressesCount == 0)
      {
          AddressesI2C = (byte**)malloc( (this->AddressesCount + 1 ) * sizeof(byte *));
          AddressesI2C[this->AddressesCount] = (byte*)malloc(2 * sizeof(byte)); 
      }
      else
      {
          AddressesI2C = (byte**)realloc(AddressesI2C, (this->AddressesCount + 1 ) * sizeof(byte *));
          AddressesI2C[this->AddressesCount] = (byte*)malloc(2 * sizeof(byte)); 
      }
      
      if (error == 0)
      {
        if(debug != 0)
        {
          Serial.print("I2C device found at address 0x");
          if (address<16)
            Serial.print("0");

          Serial.print(address, HEX);
          Serial.println("  !");
        }

        nDevices++;

        AddressesI2C[this->AddressesCount][0] = address;
        AddressesI2C[this->AddressesCount][1] = error;
      }
      else if (error==4)
      {
        if(debug != 0)
        {
          Serial.print("Unknown error at address 0x");
          if (address<16)
            Serial.print("0");

          Serial.println(address, HEX);
        }

        AddressesI2C[this->AddressesCount][0] = address;
        AddressesI2C[this->AddressesCount][1] = error;
      }   


      Wire.endTransmission();

      this->AddressesCount++; 
    }

     delay(1); 
  }

  if(debug != 0)
  {
    if (nDevices == 0)
      Serial.println("No I2C devices found\n");
  }

}

void Esp32ScannerI2C::PrintToUart()
{
  Serial.begin(this->UartSpeed);
  while (!Serial);             
  Serial.println("\nI2C list");

  for(int i = 0; i < this->AddressesCount; i++ )
  {
      if (AddressesI2C[i][1] == 0)
      {
        Serial.print("I2C device found at address 0x");
        if (AddressesI2C[i][0]<16)
          Serial.print("0");

        Serial.print(AddressesI2C[i][0], HEX);
        Serial.println("  !");
      }
      else if (AddressesI2C[i][1] == 4)
      {
        Serial.print("Unknown error at address 0x");
        if (AddressesI2C[i][0]<16)
          Serial.print("0");

        Serial.println(AddressesI2C[i][0], HEX);
      }   
  }

  if (this->AddressesCount == 0)
  {
    Serial.println("No I2C devices found\n");
  }
}
 


