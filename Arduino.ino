
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial uno(7,8);
#define ONE_WIRE_BUS 2 // inisialisasi suhu di pin 2 digital
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27,16,2);

float TempC; // inisialisasi data sensor suhu
float pHValue; 
//deklarasi pin analog
float ntu;
int adc;
int adcPH;
int TempCx;
int pHValuex;
int ntux;
float ntufix;
// deklarasi komunikasi(uart) serial 2 arah 
String kirim;

float data;
float data1;
float data2;
float kosong=0;

void setup(){  
  Wire.begin();  // inisialisasi komunikasi
  sensors.begin();
  Serial.begin(9600);
  uno.begin(9600); //// inisialisasi komunikasi
  lcd.init();
  lcd.backlight();  
  lcd.clear();
 
 
  }


void loop(){
  Ntu();
  ph();
  suhu();
  tampilan();
  data = TempC ; // tipe data yg dioutputkan float
  data1= ntufix ;
  data2= pHValue ;

}
void Ntu(){
  adc = analogRead(A1);             
  ntu = (adc - 912.5)/0.279; // -0.27
  ntux = ntu*100.0;
  ntufix = ntux/100.0;
}
void ph(){  
  adcPH = analogRead(A0); //menggunakan pin A0 untuk membaca output sensor pH
  pHValue = (adcPH-762.19)/ 33.961;//-33.9
  
  pHValuex = pHValue * 100.0;
}
void suhu(){
   sensors.requestTemperatures();
   TempC = sensors.getTempCByIndex(0); // Celcius
   TempCx =  TempC * 100.0;
}
void tampilan(){  
    lcd.setCursor(0,1);
    lcd.print("NTU= ");
    lcd.print(ntufix,1);
    lcd.print("  ");
    
    lcd.setCursor(8,0);
    lcd.print("T:");
    lcd.print(TempC,1);
    lcd.print("C");
    lcd.setCursor(0,0);
    lcd.print("PH:");
    lcd.print(pHValue,2);
    lcd.print("  ");
    
    Serial.print("*");
    Serial.print(ntux);
    Serial.print(",");
    Serial.print(pHValuex);
    Serial.print(",");
    Serial.print(TempCx);
    Serial.println("#");
    kirimmcu();
    delay(1000);
  }
void kirimmcu(){
  kirim= String(kosong) + "#" + String(data) + "#" + String(data1) + "#" + String(data2);
uno.println(kirim);
  }
  
