#include <Arduino.h>
#include <S3B.h>

S3B module;

uint8_t transmitData[2] = {0x55};
//Set this to the address of the mating device
uint8_t destinationAddress[8] = {0x00,0x13,0xA2,0x00,0x01,0x02,0x03,0x04};


//S3B Module callbacks
void s3BReceiver(uint8_t* data, size_t len, uint8_t* transmitterAddress);
void s3BTransmitStatus(uint8_t status, uint8_t frameID);
void softwareS3BCommand();
void softwareATCommandResponse(uint8_t* data, size_t len);
void moduleSettingsLoaded();
void s3BRSSI(int rssi, uint8_t* transmitterAddress);
void parseBytes(const char* str, char sep, uint8_t* bytes, int maxBytes, int base);

void setup() {
  module.init();
  module.receiveDataCallback(s3BReceiver);
  module.rssiUpdateCallback(s3BRSSI);
  module.transmissionStatusCallback(s3BTransmitStatus);
  module.softwareATCallback(softwareATCommandResponse);
  module.settingsLoadedCallback(moduleSettingsLoaded);
}

void loop() {
  module.loop();
}

void s3BReceiver(uint8_t* data, size_t len, uint8_t* transmitterAddress){
  if(memcmp(transmitterAddress,destinationAddress,8)!=0){
    //ignore, transmission did not come from mating device
    return;
  }

  module.transmit(destinationAddress,transmitData,1);
}

void s3BTransmitStatus(uint8_t status, uint8_t frameID){
  // Serial.printf("Transmit Status: %i\n",status);
}

void softwareS3BCommand(){

}

void softwareATCommandResponse(uint8_t* data, size_t len){

}

void moduleSettingsLoaded(){

}

void s3BRSSI(int rssi, uint8_t* transmitterAddress){

}