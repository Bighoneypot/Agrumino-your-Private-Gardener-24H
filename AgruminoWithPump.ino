//// Agrumino your personal gardener 
/// Created by gabriele.foddis@lifely.cc
#include <Agrumino.h>
#define PUMP 12
#define SLEEP_TIME_SEC 120 ///s Time
#define THRESHOLD 25 ///% soil moisture
#define THRESHOLDTEMP 22 ////°C
#define SERIALBAUD 115200
#define WATERINGTIME 1000 //// set Time in ms 
int counter = 0;
Agrumino agrumino;

void setup() {
  agrumino.setup();
  Serial.begin(SERIALBAUD); 
  pinMode(PUMP, OUTPUT);
  digitalWrite(PUMP, LOW);
}


void loop() {
  agrumino.turnBoardOn();
  counter ++;

  if (counter == 100) {
    wateringControl();
    delay(1200);
  }
  else if (counter == 2000) {
    int timetominutes = SLEEP_TIME_SEC / 60 ;
    Serial.print("Bye......I'm sleep for " + String(timetominutes) + " minutes");
    counter = 0;
    deepSleepSec(SLEEP_TIME_SEC);
    agrumino.turnBoardOff();
  }
}

void blinkLed() {
  agrumino.turnLedOn();
  delay(200);
  agrumino.turnLedOff();
}
void wateringLed() {
  agrumino.turnLedOn();
  delay(300);
  agrumino.turnLedOff();
  delay(100);
  agrumino.turnLedOn();
  delay(300);
  agrumino.turnLedOff();
  delay(100);
  agrumino.turnLedOn();
  delay(300);
  agrumino.turnLedOff();

}


void wateringControl() {

  int soilPerc = agrumino.readSoil();
  int temp = agrumino.readTempC();
  Serial.println("****************");
  Serial.println("Temperature = " + String(temp));
  Serial.println("Soil Moisture % = " + String(soilPerc));

  if (soilPerc < THRESHOLD && temp < THRESHOLDTEMP) {
    agrumino.turnLedOn();
    Serial.print("I'm Watering your plant");   
    agrumino.turnWateringOn();
    delay(WATERINGTIME);
    agrumino.turnWateringOff();
    delay(1000);
    agrumino.turnLedOff();
  }
  else if (soilPerc < THRESHOLD && temp > THRESHOLDTEMP) {
    Serial.println("Soil moisture is not ok, but temperature is very high....I'm waiting..");
  }

}

void delaySec(int sec) {
  delay (sec * 1000);
}

void deepSleepSec(int sec) {
  ESP.deepSleep(sec * 1000000); // microseconds
}
