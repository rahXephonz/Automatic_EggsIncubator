/* Note SDA = A4 SCL = A5 , OUT = 3" */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN A2
#define DHTTYPE DHT11
#define r1 A3
#define r2 A1

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  
  Serial.begin(9600);
  lcd.begin();
  dht.begin();

  pinMode(r1, OUTPUT); // Stepper
  pinMode(r2, OUTPUT); // Fan DC
  
  digitalWrite(r1, LOW); // Stepper Motor Menyala terlebih dahulu
  digitalWrite(r2, HIGH); // Fan DC Mati terlebih dahulu
}

void loop()
{
  lcd.clear();
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  lcd.setCursor(0,0);
  lcd.print("Suhu   : ");
  lcd.print(t);
  lcd.print((char)223);

  lcd.setCursor(0,1);
  lcd.print("Lembab : ");
  lcd.print(h);
  lcd.print("%");
  delay(5000);

  if(t >= 38){ // Jika suhu lebih dari 38 maka Fan DC menyala
    digitalWrite(r2, LOW);
  }

  else if(t <= 35){ // Jika suhu kurang dari 35 maka Fan DC mati
    digitalWrite(r2, HIGH);
  }
}
