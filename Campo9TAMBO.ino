//---SISTEMAS | GUARANI----04/11/2019
#include <Thermistor3.h>
#include "RTClib.h"
RTC_DS1307 rtc;
//begin object Thermistor in pin 0
Thermistor temp(0);
//value of resistor in ohms
double resistor = 10000;
//variable to store the average of read
double average = 0;
//number of samples
int sample = 5000;
int tonepin = 8;
int buttonstop = 9;
int count = 0;
int tempMax = 10;
int i = 0;
void setup() {
  delay(500);
  Serial.begin(9600);
  pinMode (tonepin, OUTPUT);
  rtc.begin();
  pinMode(buttonstop, INPUT_PULLUP);


  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}
void loop() {
  DateTime time = rtc.now();
  String hora = time.timestamp(DateTime::TIMESTAMP_TIME);
  char buf1[] = "mm";
  char buf2[] = "hh";
  String minutos = time.toString(buf1);
  String horario = time.toString(buf2);
  int mm = minutos.toInt();
  int hh = horario.toInt();

  //Serial.println(mm % 5);

  //Read the data and plus to variable average
  for (int index = 0; index < sample; index++) {
    double temperature = temp.getTemp(resistor);
    average += temperature;
    // a small delay for read again
    delayMicroseconds(1);
  }
  // get the average
  average = average / sample;
  Serial.print("Temperatura in Sensor is : ");
  Serial.print( average );
  Serial.println(" Celsius");


  Serial.println(hora);

  if (hh >= 8 && hh <= 13) {//NO
    //5min
    Serial.println("Cada 5 ");
    if (mm % 5 == 0) {
      Serial.println("Cada 5 minutos");
      SensorTemperature();
    }
  }
  else if (hh >= 16 && hh <= 21) { //NO
    //5min
    if (mm % 5 == 0) {
      Serial.println("Cada 5 minutos");
      SensorTemperature();
    }
  }
  else if (hh >= 00 && hh <= 5) { //NO
    //5min
    if (mm % 5 == 0) {
      Serial.println("Cada 5 minutos");
      SensorTemperature();

    }else{
      if(average > 40 ||average < 0 )
      alarm() ;
      }
  }

  /** if (hora == "15:41:00" || hora == "15:41:01" || hora == "15:41:02") {
     Serial.println("Alarm");
     SensorTemperature();
    } else if (hora == "16:00:00" || hora == "16:00:01" || hora == "16:00:02") {
     SensorTemperature();
    } else if (hora == "00:00:00" || hora == "00:00:01" || hora == "00:00:02") {
     SensorTemperature();
    }**/
}

void alarm() {
  for (i = 2; i < 240; i++) {
    tone(tonepin, 400.100, 300);
    delay(500);
    if (digitalRead(buttonstop) == 0) {
      i = 240;
      Serial.println("button ON");
      delay(62000);
      
    }
    
  }
}
void SensorTemperature() {
  if (average > tempMax)
    alarm();
}
