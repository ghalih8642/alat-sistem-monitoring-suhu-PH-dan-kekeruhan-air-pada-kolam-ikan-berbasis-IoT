#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D5, D6); // RX, TX pin yang digunakan utk komunikasi uart 

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "8p9nVTXd5NpEzVYypOwXgxB5z8l5iDUK"; // token blynk

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "vivo 1907";
char pass[] = "1123456789";

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
mySerial.begin(9600);
Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);// pengiriman data dalam 1s
}
String data; //deklarasi variabel 
char c;
int Index1,Index2,Index3,Index4,Index5,Index6;
String secondValue, thirdValue, fourthValue, fifthValue, firstValue;

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, secondValue);
  Blynk.virtualWrite(V1, thirdValue);
  Blynk.virtualWrite(V2, fourthValue);
}
void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run(); 
while(mySerial.available()>0){
  c=mySerial.read();
  delay(10);
  data+=c;
  }
  if (data.length()>0) //looping komunikasi uart
{
Index1 = data.indexOf('#');
Index2 = data.indexOf('#', Index1+1);
Index3 = data.indexOf('#', Index2+1);
Index4 = data.indexOf('#', Index3+1);
Index5 = data.indexOf('#', Index4+1);
Index6 = data.indexOf('#', Index5+1);
secondValue = data.substring(Index1+1, Index2);
thirdValue = data.substring(Index2+1, Index3);
fourthValue = data.substring(Index3+1, Index4);
/*fifthValue = data.substring(Index4+1, Index5);
firstValue = data.substring(Index5+1, Index6);
//Serial.println(Index1);*/
Serial.print("data 1:");Serial.println(secondValue);
Serial.print("data 2:");Serial.println(thirdValue);
Serial.print("data 3:");Serial.println(fourthValue);
/*Serial.print("data 4:");Serial.println(fifthValue);
Serial.print("data 5:");Serial.println(firstValue);*/
data="";
}
Serial.println(data);
//delay(1000);
}
