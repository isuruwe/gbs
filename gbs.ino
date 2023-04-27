//For more Information visit www.aeq-web.com?ref=arduinoide

#include <SoftwareSerial.h>
#include <Wire.h>
#include <dht.h>

SoftwareSerial mySerial(10, 11);            // RX, TX Pins
String apn = "dialogbb";                       //APN
String apn_u = "";                     //APN-Username
String apn_p = "";                     //APN-Password
String url = "http://203.115.24.227:8888/gbs/gbs.ashx";  //URL for HTTP-POST-REQUEST
String name1;   //String for the first Paramter (e.g. Sensor1)
String description;   //String for the second Paramter (e.g. Sensor2)
const int trigPin = 9;
const int echoPin = 8;
String first2="";
String second2="0";
String third2="0";
 String four2="0";
 String first3="";
String second3="0";
String third3="0";
 String four3="0";
  String dev2="0";
   String dev3="0";
const byte numChars = 32;
char receivedChars[numChars];
 String strAr[30];
String inData;

boolean newData = false;
// defines variables
long duration;
int distance;
dht DHT;
#define DHT11_PIN 7
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
//Serial.begin(9600); // Starts the serial communication
  delay(10000);
}

void loop() { // run over and over
 int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: "+distance);
//description= Serial.readStringUntil('\r');
 //  Serial.println(description);
//String xval = getValue(myString, ':', 0);
 //dev2  = Serial.readString();
//dev3  = Serial.readStringUntil('\n');
strAr[0]=Serial.readString();
//Serial.println("dev2: "+dev2);


//Serial.println(strAr[0]);

dev2=getValue(getValue(strAr[0], '>', 0), '<', 1);
dev3=getValue(getValue(strAr[0], '>', 1), '<', 1);
Serial.println(dev2);
 first2   = getValue(dev2, ',', 0);

    
  second2 = getValue(dev2, ',', 1);
   
     third2  = getValue(dev2, ',', 2);

   four2  = getValue(dev2, ',', 3);

 //recvWithStartEndMarkers();
//Serial.println("dev2: "+dev2);
//Serial.println(receivedChars);

    first3   = getValue(dev3, ',', 0);

    
  second3 = getValue(dev3, ',', 1);
   
     third3  = getValue(dev3, ',', 2);

   four3  = getValue(dev3, ',', 3);

   Serial.println("dev2: "+four2);
   Serial.println("dev3: "+four3);
//(10000);
    name1 = "123";
    description = "ABC";
   
      gsm_sendhttp();
     //Start the GSM-Modul and start the transmisson
    delay(10000); //Wait one minute

}




void gsm_sendhttp() {
  
  
 
  mySerial.println("AT");
  runsl();//Print GSM Status an the Serial Output;
   Serial.println("1");
  delay(5000);
 
 mySerial.println("AT+CMEE=2");
    runsl();
 // mySerial.println("AT+CBAND=EGSM_DCS_MODE");
    //runsl();
   // delay(100);
  mySerial.println("AT+CBAND=EGSM_PCS_BAND");
    runsl();
    delay(5000);
mySerial.println("AT+CPIN?");
  runsl();
   Serial.println("6");
  delay(100);
 
  mySerial.println("AT+CREG=1");
  runsl();
   Serial.println("6");
  delay(100);
  mySerial.println(" AT+CREG?");
  runsl();
   Serial.println("6");
  delay(100);
  
  mySerial.println("AT+CGATT?");
  runsl();
   Serial.println("6");
  delay(100);
  
   mySerial.println("AT+CSQ");
  runsl();
   Serial.println("6");
  delay(100);
  mySerial.println("AT+SAPBR=3,1,Contype,GPRS");
  runsl();
   Serial.println("2");
  delay(100);
  mySerial.println("AT+SAPBR=3,1,APN," + apn);
  runsl();
   Serial.println("3");
  delay(100);
 // mySerial.println("AT+SAPBR=3,1,USER," + apn_u); //Comment out, if you need username
//  runsl();
  // Serial.println("4");
 // delay(100);
  //mySerial.println("AT+SAPBR=3,1,PWD," + apn_p); //Comment out, if you need password
 // runsl();
//   Serial.println("5");
//  delay(100);
 
 
  mySerial.println("AT+SAPBR =1,1");
  runsl();
   Serial.println("6");
  delay(100);
  mySerial.println("AT+SAPBR=2,1");
  runsl();
  delay(2000);

  
  mySerial.println("AT+HTTPINIT");
  runsl();
   Serial.println("8");
  delay(100);
  mySerial.println("AT+HTTPPARA=CID,1");
  runsl();
   Serial.println("9");
  delay(100);
  mySerial.println("AT+HTTPPARA=URL," + url+"?p1=1&tempi="+DHT.temperature+"&humi="+DHT.humidity+"&distan="+distance);
 //  mySerial.println("AT+HTTPPARA=URL," + url+"?p1="+first+"&tempi="+second1+"&humi="+third+"&distan="+four);
  runsl();
    Serial.println("10");
  delay(100);
 // mySerial.println("AT+HTTPPARA=CONTENT,application/x-www-form-urlencoded");
 //  mySerial.println("AT+HTTPPARA=name="+ String(name1) + "&description=" + String(description) +"");
// mySerial.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");  
 //mySerial.println("AT+HTTPPARA?");  
 // runsl();
 //  Serial.println("11");
//  delay(100);
 // mySerial.println("AT+HTTPDATA=19,10000");
//  runsl();
   // Serial.println("12");
 // delay(100);
//mySerial.println("name=" + name1 + "&description=" + description);
 runsl();
   Serial.println("13");
  delay(1000);
  mySerial.println("AT+HTTPACTION=0");
  runsl();
    Serial.println("14");
  delay(10000);
  mySerial.println("AT+HTTPREAD");
  runsl();


  
 if(first2!=" "){
 mySerial.println("AT+HTTPINIT");
  runsl();
   Serial.println("8");
  delay(100);
  mySerial.println("AT+HTTPPARA=CID,1");
  runsl();
   Serial.println("9");
  delay(100);
 
 // mySerial.println("AT+HTTPPARA=URL," + url+"?p1=1&tempi="+DHT.temperature+"&humi="+DHT.humidity+"&distan="+distance);

   mySerial.println("AT+HTTPPARA=URL," + url+"?p1="+first2+"&tempi="+second2+"&humi="+third2+"&distan="+four2);
   
  runsl();
    Serial.println("10");
  delay(100);
 // mySerial.println("AT+HTTPPARA=CONTENT,application/x-www-form-urlencoded");
 //  mySerial.println("AT+HTTPPARA=name="+ String(name1) + "&description=" + String(description) +"");
// mySerial.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");  
 //mySerial.println("AT+HTTPPARA?");  
 // runsl();
 //  Serial.println("11");
//  delay(100);
 // mySerial.println("AT+HTTPDATA=19,10000");
//  runsl();
   // Serial.println("12");
 // delay(100);
//mySerial.println("name=" + name1 + "&description=" + description);
 runsl();
   Serial.println("13");
  delay(1000);
  mySerial.println("AT+HTTPACTION=0");
  runsl();
    Serial.println("14");
  delay(10000);
  mySerial.println("AT+HTTPREAD");
  runsl();
 }



 if(first3!=" "){
  mySerial.println("AT+HTTPINIT");
  runsl();
   Serial.println("8");
  delay(100);
  mySerial.println("AT+HTTPPARA=CID,1");
  runsl();
   Serial.println("9");
  delay(100);
 // mySerial.println("AT+HTTPPARA=URL," + url+"?p1=1&tempi="+DHT.temperature+"&humi="+DHT.humidity+"&distan="+distance);
   mySerial.println("AT+HTTPPARA=URL," + url+"?p1="+first3+"&tempi="+second3+"&humi="+third3+"&distan="+four3);
  runsl();
    Serial.println("10");
  delay(100);
 // mySerial.println("AT+HTTPPARA=CONTENT,application/x-www-form-urlencoded");
 //  mySerial.println("AT+HTTPPARA=name="+ String(name1) + "&description=" + String(description) +"");
// mySerial.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");  
 //mySerial.println("AT+HTTPPARA?");  
 // runsl();
 //  Serial.println("11");
//  delay(100);
 // mySerial.println("AT+HTTPDATA=19,10000");
//  runsl();
   // Serial.println("12");
 // delay(100);
//mySerial.println("name=" + name1 + "&description=" + description);
 runsl();
   Serial.println("13");
  delay(1000);
  mySerial.println("AT+HTTPACTION=0");
  runsl();
    Serial.println("14");
  delay(10000);
  mySerial.println("AT+HTTPREAD");
  runsl();
 }
    Serial.println("15");
  delay(100);
  mySerial.println("AT+HTTPTERM");
  runsl(); 
    Serial.println("16");
}

//Print GSM Status
void runsl() {
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }

}

String recvWithStartEndMarkers() {
 while (Serial.available() > 0)
    {
        char recieved = Serial.read();
        inData += recieved; 

        // Process message when new line character is recieved
        if (recieved == '\n')
        {
           // Serial.print("Arduino Received: ");
            Serial.print(inData);

            // You can put some if and else here to process the message juste like that:

            if(inData == "+++\n"){ // DON'T forget to add "\n" at the end of the string.
              Serial.println("OK. Press h for help.");
            }   


            inData = ""; // Clear recieved buffer
        }
    }
    return inData;
}
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}




