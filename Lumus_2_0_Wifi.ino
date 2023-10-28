#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>  
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Vinny"
#define WIFI_PASSWORD "LUMUS123"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDCHtPqYDINIEQ33E0zl47ABvCyrANKtqY"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "lumus-18c48-default-rtdb.firebaseio.com" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

//some importent variables
String sValue, sValue2, sValue3, sValue4, s1Value, s2Value, s3Value, s4Value;

bool signupOK = false;

#define Led1 4
#define Led2 5

#define Led3 0
#define Led4 2

#define Led5 14
#define Led6 12

#define Led7 13
#define Led8 15 

void setup() {
  Serial.begin(115200);

  pinMode(Led1,OUTPUT);
  pinMode(Led2, OUTPUT); 
// sala 1

  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);

// sala 2

  pinMode(Led5, OUTPUT);
  pinMode(Led6, OUTPUT);

// lab 1

  pinMode(Led7, OUTPUT);
  pinMode(Led8, OUTPUT);

  // lab 2

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
    Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.ready() && signupOK ) {

  // Sala 01

    if (Firebase.RTDB.getString(&fbdo, "/Lumus/FMM/Salas de Aula/Sala 01/Status Lâmpada")) {
      if (fbdo.dataType() == "string") {
        
        sValue = fbdo.stringData();

        int a = sValue.toInt();

        Serial.println("Status Led 1:"); 
        Serial.println(a);

        if (a == 1){

            if (Firebase.RTDB.getString(&fbdo, "/Lumus/FMM/Salas de Aula/Sala 01/Potência")) {
              if (fbdo.dataType() == "string") {
                 s1Value = fbdo.stringData();
                  
                  int pwmValue = s1Value.toInt();
                  
                  Serial.println("Potência da Sala 01:");
                  Serial.println(pwmValue);
                  analogWrite(Led1, pwmValue);
                  analogWrite(Led2, pwmValue);
              }
            }

        }else{
          digitalWrite(Led1, LOW);
          digitalWrite(Led2, LOW);
        }
      }
    }

    else {
      Serial.println(fbdo.errorReason());
    }
    
    if (Firebase.RTDB.getString(&fbdo, "/Lumus/FMM/Salas de Aula/Sala 02/Status Lâmpada")) {
      if (fbdo.dataType() == "string") {
        sValue2 = fbdo.stringData();

        int b = sValue2.toInt();

        Serial.println("Status da Sala 02:");
        Serial.println(b);

        if (b == 1){

          if (Firebase.RTDB.getString(&fbdo, "/Lumus/FMM/Salas de Aula/Sala 02/Potência")) {
              if (fbdo.dataType() == "string") {
                 s2Value = fbdo.stringData();
                  
                  int pwmValue2 = s2Value.toInt();

                  Serial.println("Potência Led 2:");
                  Serial.println(pwmValue2);
                  analogWrite(Led3, pwmValue2);
                  analogWrite(Led4, pwmValue2);
              }
            }
        }else{
          digitalWrite(Led3, LOW);
          digitalWrite(Led4, LOW);
        }
      }
    }
    if (Firebase.RTDB.getString(&fbdo, "/Lumus/FMM/Salas de Aula/lab 01/Status Lâmpada")) {
      if (fbdo.dataType() == "string") {
        
        s3Value = fbdo.stringData();

        int c = s3Value.toInt();

        Serial.println("Status do Laboratório 01:"); 
        Serial.println(c);

        if (c == 1){  

            if (Firebase.RTDB.getString(&fbdo, "/Lumus/FMM/Salas de Aula/lab 01/Potência")) {
              if (fbdo.dataType() == "string") {
                 s3Value = fbdo.stringData();
                  
                  int pwmValue3 = s3Value.toInt();
                  
                  Serial.println("Potência do Laboratório 01:");
                  Serial.println(pwmValue3);
                  analogWrite(Led5, pwmValue3);
                  analogWrite(Led6, pwmValue3);
              }
            }

        }else{
          digitalWrite(Led5, LOW);
          digitalWrite(Led6, LOW);
        }
      }
    }

    if (Firebase.RTDB.getString(&fbdo, "/Lumus/FMM/Salas de Aula/lab 02/Status Lâmpada")) {
      if (fbdo.dataType() == "string") {
        
        s4Value = fbdo.stringData();

        int d = s4Value.toInt();

        Serial.println("Status do Laboratório 02:"); 
        Serial.println(d);

        if (d == 1){  

            if (Firebase.RTDB.getString(&fbdo, "/Lumus/FMM/Salas de Aula/lab 02/Potência")) {
              if (fbdo.dataType() == "string") {
                 s4Value = fbdo.stringData();
                  
                  int pwmValue4 = s4Value.toInt();
                  
                  Serial.println("Potência do Laboratório 02:");
                  Serial.println(pwmValue4);
                  analogWrite(Led7, pwmValue4);
                  analogWrite(Led8, pwmValue4);
              }
            }

        }else{
          digitalWrite(Led7, LOW);
          digitalWrite(Led8, LOW);
        }
      }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  }
}