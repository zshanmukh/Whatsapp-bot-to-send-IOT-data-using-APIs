zfloat temp;
int mint = 24; //defining minimum temperature for which fan must turned on
int maxt = 50;
#define dht_dpin A0

#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include<WiFiClientSecure.h>
#include <DHT.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
dht DHT;

DHT dht(A0, DHT11);//dht  (dhtpin, dht type=dht11)
float humidity, temp_f;
const char* ssid =",";
const char* password="1234567899";
#define HOSTIFTTT "maker.ifttt.com"
#define EVENT0 "whatsapp_bot"
#define IFTTTKEY "1Gqafn9c40o6PDLoDbfNr"
String temperature, humidity;
String fingerprint, WebHook, id, token, message, from, to;
WiFiClientSecure client;
void setup() {



Serial.begin(15200);
delay(10);
dht.begin();
delay(2000);
  lcd.begin(16, 2);
  lcd.print("hello!"); //welcome message
  delay(1000); //delays for 1000ms
  lcd.clear(); // clears the LCD screen
temp_f=dht.readTemperature();
humidity=dht.readHumidity();
WiFi.begin(sssid,password);
Serial.println("");
Serial.print("waiting to connect....");
while (WiFi.status() !=WL_CONNECTED){
  delay(500);
  Serial.print(".");}
  Serial.println("");
  Serial.print("connected to");
  Serial.println(ssid);
  Serial.print("IP address:");
  Serial.println(WiFi.localIP());
  delay(1000);
  Serial.print("Initial Temp");
  Serial.println(temp_f);
  Serial.print("Initial humidity:");
  Serial.println(humidity);
  //close any previous connection
  if  (client.connected())

  {client.stop();}
  //wait till data is sent
  client.flush();
   if (client.connected(HOSTIFTTT,433))
   Serial.println("connected");
   //build the HTTP request
   String toSend="GET/trigger/";
   toSend+= EVENT0;
   toSend+= "/with/key/";
   toSend+= humidity;
   toSend+= "HTTP/1.1\r\n";
   toSend+= "Host: ";
   toSend+=HOSTIFTTT;
   toSend+="\r\n";
   toSend+= "connection: close\r\n\r\n";
   Client.print(toSend);

  id= "ACfbfad2ee8918acf077bab27a36ac3ac8";
  token = "6d76c2a4f9ac79c370162a136730dae9";
  from = "12019756599";
  to = "919381374776";

  // Create message,use %0A to start a new line.
  message = "Status:+Data+Obtained+😃+👍%0A%0ATemperature:+" + temperature + "°C%0A%0AHumidity:+" + humidity + "%%0A%0AMovement:+" + trespass + "%0A%0AWaiting...";

  // Create the webhook path.
  WebHook = "";

  // Create HTTP object to make a request.
  HTTPClient http;

  // Send a request.
  http.begin(WebHook, fingerprint);

  int httpCode = http.GET();
  String payload = http.getString();

  if(httpCode == 200){ Serial.println("\n Message Sent Successfully..."); }else{ Serial.println("\n Not Working! Error Code: " + httpCode); }

  // End HTTP Get Request.
  http.end();

}
//wait untill the data has been sent
client.flush();
//disconnect from the client
client.stop();
delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:

   DHT.read11(dht_dpin);
  int temp=DHT.temperature;
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.print(temp);   // Printing temperature on LCD
  lcd.write(1);
  lcd.print("C");
  lcd.setCursor(0,1);

   delay(1000);// delaying for better performance of microcontroller

  if(temp < mint) // if the room temperature falls below minimum temperature the fan turns off
  {

digitalWrite(6, LOW); // pin no. 6(which can operate PWM to vary fan speed) is connected to servo motor and is set to digital off position
lcd.setCursor(0, 0); //sets cursor to 1st row, first column to starts printing there
lcd.print("TEMPERATURE = "); //prints string as follows in LCD
lcd.print(temp);
lcd.print("*C");

delay(100);// delay for 100ms for better operation
 lcd.setCursor(0, 1); //sets cursor to 2nd row, first column to starts printing there

  lcd.print("fan state=off");//prints string as follows in LCD

}

if((temp >= mint) && (temp <= maxt))  //if the temperature of room is in between minimum temp and maximum temperature (max temperature is defined for scaling the output)
{

int s=map(temp, mint, maxt, 100, 255); //scaling the output signal to operate fan at minimum speed and maximum possible speed
  analogWrite(6,s);// gives the scaled value as proportionate to the temperature detected as analog value by PWM
  Serial.println();
  Serial.print(s); //prints the value in serial mnitor
  lcd.setCursor(0, 0);
lcd.print("TEMPERATURE = "); ////prints string as follows in LCD
lcd.print(temp);
lcd.print("*C");

delay(100);// delay 100ms for better operation
 lcd.setCursor(0, 1);

  lcd.print("fan state=on");



}
