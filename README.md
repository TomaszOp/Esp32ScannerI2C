# Esp32ScannerI2C

Scanner i2c Esp32 Library
tested arduino 2.0.4

use:

  Esp32ScannerI2C Scanner;

  Scanner.SetUartSpeed (115200); // default 115200                  
  Scanner.AttachI2CPins(4, 5); // default 21 22

  Scanner.Scan();
  
  <br>
  Scanner.PrintToUart();
  
  or
  
  for(int = i; i < Scanner->AddressesCount; i++)  <br>
    {  <br>
      // adress I2C = Scanner->AddressesCount[i][0];  <br>
      // if was error with address communication, Scanner->AddressesCount[i][1] = error,  0 without error <br>
    }  <br>
