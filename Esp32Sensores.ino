#include <WiFi.h>
#include <FirebaseESP32.h>
#include "ConfgWifi.h"
#define RXp2 16
#define TXp2 17

#define FIREBASE_HOST "https://sensor-498f5-default-rtdb.firebaseio.com/"  //--> URL address of your Firebase Realtime Database.
#define FIREBASE_AUTH "Agl97GecPeCiOS3NWdd652nEODeEz3WNe44Nf9Ww"           //--> Your firebase database secret code.


// const char* ssid = "Galaxy"; //--> SSID de wifi
// const char* password = "Mama1234"; //--> contrasena de wifi

//CONSTANTES//
String Tipo_Sensor = "";
String Dato_Sensor = "";
String dato = "";
int indice;
const int Led = 32;
//Define FirebaseESP32 data object
FirebaseData firebaseData;
FirebaseJson json;
int Vresistor = A0;
int Vrdata = 0;



void setup() {

  Serial2.begin(115200, SERIAL_8N1, RXp2, TXp2);
  Serial.begin(115200);

  ConectarWifi();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Serial2.available()) {
    dato = Serial2.readString();
    indice = dato.indexOf(',');
    Tipo_Sensor = String(dato.substring(0, indice));
    Serial.println(Tipo_Sensor);
    Dato_Sensor = String(dato.substring(indice + 1, -1));
    Serial.println(Dato_Sensor);
  }

  if (Tipo_Sensor == "PH") {
    Serial.println("Sensor PH");
    Serial.println(Dato_Sensor);
    json.set("/Sensor", Dato_Sensor);
    Firebase.updateNode(firebaseData, "/PH", json);
    Dato_Sensor = "";
    Tipo_Sensor = "";
  } else if (Tipo_Sensor == "Temp") {
    Serial.println("Sensor Temp");
    Serial.println(Dato_Sensor);
    json.set("/Sensor", Dato_Sensor);
    Firebase.updateNode(firebaseData, "/Temp", json);
    Dato_Sensor = "";
    Tipo_Sensor = "";
  }
}


void ConectarWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");
    Serial.println("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(Led, 0);
      delay(500);
      digitalWrite(Led, 1);
      delay(500);
      Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected to: ");
    Serial.println(ssid);
    digitalWrite(Led, 1);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
}