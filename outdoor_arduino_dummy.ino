#include "SoftwareSerial.h"
#include "XBee.h"
//#include <cstdlib>
#include <stdio.h>

// create the XBee object
XBee xbee = XBee();

// we are going to send two floats of 4 bytes each
uint8_t payload[28] = {0, 0, 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// union to convery float to byte string
union u_tag {
  uint8_t b[4];
  float fval;
} u;

XBeeAddress64 addr64 = XBeeAddress64(0x00000000, 0x00000000); //masukkan alamat xbee coordinator
//XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x40A7DB96);
//create the packet
//Serial.println(addr64, HEX);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
//ZBTxRequest zbTx = ZBTxRequest(addr64, (uint8_t *)buff, strlen(buff));
//create the Tx request

//Dummy
float lat = -7.766052;
float lon = 110.3715927;
float temp = random(20, 40);
float hum = random(50, 60);
float co2 = random(300, 700);
float co = random(50, 100);
float batere = 30.3;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  xbee.setSerial(Serial);
}

void sendPacket() {
  // convert humidity into a byte array and copy it into the payload array
  u.fval = lat;
  for (int i = 0; i < 4; i++) {
    payload[i] = u.b[i];
  }
  u.fval = lon;
  for (int i = 0; i < 4; i++) {
    payload[i + 4] = u.b[i];
  }
  u.fval = temp;
  for (int i = 0; i < 4; i++) {
    payload[i + 8] = u.b[i];
  }
  u.fval = hum;
  for (int i = 0; i < 4; i++) {
    payload[i + 12] = u.b[i];
  }
  u.fval = co2;
  for (int i = 0; i < 4; i++) {
    payload[i + 16] = u.b[i];
  }
  u.fval = co;
  for (int i = 0; i < 4; i++) {
    payload[i + 20] = u.b[i];
  }
  u.fval = batere;
  for (int i = 0; i < 4; i++) {
    payload[i + 24] = u.b[i];
  }
  
  ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
  xbee.send(zbTx);
}

void loop() {
  sendPacket();
  delay(300000);
}


