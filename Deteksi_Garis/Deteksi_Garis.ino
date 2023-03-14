#include <LowPower.h>

int sensorPin = A0;    // select the input pin for the potentiometer
int buzzer = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int kecepatan_sensing, kecepatan_sensing_2, kecepatan_kaki;
int offset_kecepatan = 6000;
int offset = 1000;
void setup() {
  // declare the ledPin as an OUTPUT:
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);
}

void loop() {

  //cek_kecepatan();
  cek_nilai_cahaya();
  //kirim_data();



}

void kirim_data() {
  sensorValue = analogRead(sensorPin);
  //Serial.println(sensorValue);
  if (sensorValue > offset) {
    digitalWrite(buzzer, LOW);
    Serial.print("1");
    digitalWrite(buzzer, HIGH);
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  }
  if (sensorValue < offset) {
    digitalWrite(buzzer, HIGH);
    Serial.print("2");
    kecepatan_sensing++;
  }
}

void cek_nilai_cahaya() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
}



void cek_kecepatan() {

  sensorValue = analogRead(sensorPin);

  if (sensorValue > offset) {
    digitalWrite(buzzer, LOW);
    kecepatan_sensing_2 = offset_kecepatan;
    while (sensorValue > offset) {
      sensorValue = analogRead(sensorPin);
      kecepatan_sensing++;
    }
    kecepatan_kaki = kecepatan_sensing / kecepatan_sensing_2;
    kecepatan_sensing = 0;
    kecepatan_sensing_2 = 0;

    Serial.print(kecepatan_kaki);
    Serial.println(" m/detik");
    delay(5000);
  }
  else {
    digitalWrite(buzzer, HIGH);
    kecepatan_sensing++;
    //Serial.println(kecepatan_sensing);
  }
}
