#include <XBee.h>

// ultralyd sensor for indadgående.
#define echoPinIn 51
#define trigPinIn 52

// ultralyd sensor for udadgående.
#define echoPinOut 41
#define trigPinOut 42

int LED_PIN = 30;

// XBee object
XBee xbee = XBee();

uint8_t payload[] = { 0, 0 };

XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x4155B959);
ZBTxRequest zbTx;

long durationIn;
int distanceIn;

long durationOut;
int distanceOut;

int entrance = 0;

void setup() {
  pinMode(trigPinIn, OUTPUT);
  pinMode(echoPinIn, INPUT);

  pinMode(trigPinOut, OUTPUT);
  pinMode(echoPinOut, INPUT);

  Serial.begin(9600);
  xbee.setSerial(Serial);

  pinMode(trigPinIn, OUTPUT);
  pinMode(echoPinIn, INPUT);

  pinMode(trigPinOut, OUTPUT);
  pinMode(echoPinOut, INPUT);

  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  if (entrance >= 1){
    digitalWrite(LED_PIN, HIGH);
  }

  digitalWrite(trigPinIn, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinIn, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinIn, LOW);
  durationIn = pulseIn(echoPinIn, HIGH);
  distanceIn = durationIn * 0.034 / 2;

  digitalWrite(trigPinOut, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinOut, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinOut, LOW);
  durationOut = pulseIn(echoPinOut, HIGH);
  distanceOut = durationOut * 0.034 / 2;
  if(distanceIn <= 20){
    digitalWrite(LED_PIN, HIGH);

    payload[0] = 1;
    payload[1] = 2;

    zbTx = ZBTxRequest(addr64, payload, sizeof(payload));

    xbee.send(zbTx);
    distanceIn = 1000;
    entrance++;
    delay(1000);

    Serial.println(" IN");
    Serial.print("Number of people in room: ");
    Serial.println(entrance);

  } else if(distanceOut <= 20){
    digitalWrite(LED_PIN, HIGH);

    payload[0] = 1;
    payload[1] = 2;

    zbTx = ZBTxRequest(addr64, payload, sizeof(payload));

    //xbee.send(zbTx);
    distanceOut = 1000;

    if(entrance >= 1){
      entrance--;
    }
    
    delay(1000);

    Serial.println(" OUT");
    Serial.print("Number of people in room: ");
    Serial.println(entrance);
  }
  else
   {
    digitalWrite(LED_PIN, LOW);
   }
}