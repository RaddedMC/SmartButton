//EasyButton.ino for ESP32 -- RaddedMC


// META
#include <WiFi.h>
#include <HTTPClient.h>
const int BUTTON_PIN = 4;
const int BUZZER_PIN = 5;
const String WIFI_SSD = "[YOUR WIFI SSID]"; // 2.4 Ghz recommended
const String WIFI_PWD = "[YOUR WIFI PWD]";
const int LED_PIN = 2;

void printline(int spacing) {
  for (int i = 0; i != 30; i++) {
    if (i % spacing == 0) {
      Serial.print('-');
    } else {
      Serial.print(' ');
    }
  }
  Serial.println();
}
void printline() {
  printline(1);
}

// USER RESPONSE
void beep(int soundNum) {
  switch (soundNum) {
    case 0:
      // generic boop
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      ledcWriteTone(0, 400);
      delay(100);
      ledcWriteTone(0, 0);
      delay(100);
      break;
    case 1:
      // success tone
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
      digitalWrite(LED_PIN, HIGH);
      delay(300);
      digitalWrite(LED_PIN, LOW);
      ledcWriteTone(0, 400);
      delay(100);
      ledcWriteTone(0, 0);
      delay(30);
      ledcWriteTone(0, 1000);
      delay(80);
      ledcWriteTone(0, 0);
      delay(100);
      break;
    case 2:
      // fail tone
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
      digitalWrite(LED_PIN, HIGH);
      delay(300);
      digitalWrite(LED_PIN, LOW);
      delay(100);
      ledcWriteTone(0, 1000);
      delay(80);
      ledcWriteTone(0, 0);
      delay(100);
      ledcWriteTone(0, 400);
      delay(400);
      ledcWriteTone(0, 0);
      delay(100);
      break;
    case 3:
      // boot tone
      digitalWrite(LED_PIN, HIGH);
      delay(300);
      digitalWrite(LED_PIN, LOW);
      //Megalovania?? yup https://github.com/AnonymousAlly/Arduino-Music-Codes/blob/master/Megalovania.ino
      ledcWriteTone(0,294);//D4
      delay(125);
      ledcWriteTone(0, 0);
      delay(125);
      ledcWriteTone(0,294);//D4
      delay(125);
      ledcWriteTone(0, 0);
      delay(125);
      ledcWriteTone(0,587);//D5
      delay(250);
      ledcWriteTone(0, 0);
      delay(250);
      ledcWriteTone(0,440);//A4
      delay(250);
      ledcWriteTone(0, 0);
      delay(250);
      break;
    case 4:
      // boop2
      digitalWrite(LED_PIN, HIGH);
      delay(50);
      digitalWrite(LED_PIN, LOW);
      ledcWriteTone(0, 800);
      delay(50);
      ledcWriteTone(0, 0);
      delay(100);
  }
}


// INIT
void setup() {
  // Begin startup
  Serial.begin(9600);
  Serial.println("Initializing SmartButton...");
  printline();

  // Set pins
  Serial.print("Setting pin ");
  Serial.print(BUTTON_PIN);
  Serial.println(" to button pin...");
  pinMode(BUTTON_PIN, INPUT);
  
  Serial.print("Setting pin ");
  Serial.print(BUZZER_PIN);
  Serial.println(" to buzzer pin...");
  pinMode(BUZZER_PIN, OUTPUT);
  ledcSetup(0, 400, 10);
  ledcAttachPin(BUZZER_PIN, 0);
  
  Serial.print("Setting pin ");
  Serial.print(LED_PIN);
  Serial.println(" to LED pin...");
  pinMode(LED_PIN, OUTPUT);

  // Connect Wi-Fi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSD);
  WiFi.begin(WIFI_SSD.c_str(), WIFI_PWD.c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Setup complete.
  Serial.println("Setup completed. SmartButton is ready!");
  beep(3);
  printline();
}


// INTERNET
// Interval handler -- what to do after X intervals?
bool CRLights = false;
bool HWLights = false;
bool CRGH = false;
bool CRHWDesk = false;
HTTPClient http;

int sendWebRequest(const char * url) {
  http.begin(url);
  int httpCode = http.GET();
  Serial.print("Web request returned code ");
  Serial.print(httpCode);
  Serial.println(".");
  return httpCode;
}

void toggleADevice(const char * urlOn, const char * urlOff, bool & state, const char * deviceName) {
  Serial.print("Toggling ");
  Serial.print(deviceName);
  Serial.println("...");
  if (state == false) {
    // Turn device ON
    Serial.println("Device is OFF.");
    Serial.print("Sending request to ");
    Serial.println(urlOn);
    if (sendWebRequest(urlOn) == 200) {
      beep(1);
    } else {
      beep(2);
    }
    state = true;
    Serial.print(deviceName);
    Serial.println(" should now be ON.");
  } else {
    // Turn device ON
    Serial.println("Device is ON.");
    Serial.print("Sending request to ");
    Serial.println(urlOff);
    if (sendWebRequest(urlOff) == 200) {
      beep(1);
    } else {
      beep(2);
    }
    state = false;
    Serial.print(deviceName);
    Serial.println(" should now be OFF.");
  }
}

// EDIT THIS BLOCK TO CHANGE WHAT THE BUTTON DOES
// CURRENTLY TOGGLES LIGHTS ON AND OFF WITH IFTTT WEBHOOKS
void determineAction(int intervals) {
  switch (intervals) {
    case 0:
      // CompRoom lights
      // turn_on_light
      // turn_off_light
      beep(4);
      toggleADevice("[WEBHOOK-URL-ON]", "[WEBHOOK-URL-OFF]", CRLights, "Computer Room Lights");
      break;
    case 1:
      // Hall lights
      //toggleADevice("on", "off", HWLights, "Basement Hallway Lights");
      for (int i = 1; i != 0; i--) {
        beep(4);
      }
      break;
    case 2:
      // CompRoom GH
      // CGH_On
      // CGH_Off
      for (int i = 2; i != 0; i--) {
        beep(4);
      }
      toggleADevice("[WEBHOOK-URL-ON]", "[WEBHOOK-URL-OFF]", CRGH, "Computer Room Google Home Switch");
      break;
    case 3:
      // CompRoom HWDesk
      // Just_Lamp_On
      // Just_Lamp_Off
      for (int i = 3; i != 0; i--) {
        beep(4);
      }
      toggleADevice("[WEBHOOK-URL-ON]", "[WEBHOOK-URL-OFF]", CRHWDesk, "Computer Room Homework Desk");
      break;
    case 4: default:
      // I'm leaving
        // Turn off comproom lights
        // Turn off comproom gh
        // Turn off comproom hw desk
        // Turn on hall lights
      for (int i = 4; i != 0; i--) {
        beep(4);
      }
      break;
  }
}


// MAINLOOP
// Interval counter
void loop() {
  int currentState = digitalRead(BUTTON_PIN);
  int timeHeld = 1; // To eliminate interval zero
  int interval = 1000000;
  int intervals = 0;
  if (currentState == HIGH) {
    while (currentState == HIGH) {
      timeHeld++;
      if (timeHeld % interval == 0) {
        beep(0);
        Serial.print("Held for ");
        intervals = timeHeld/interval;
        Serial.print(intervals);
        Serial.println(" intervals.");
      }
      currentState = digitalRead(BUTTON_PIN);
    }
    Serial.print("Released at ");
    Serial.print(intervals);
    Serial.println(" intervals.");
    printline(2);
    determineAction(intervals);
    printline();
  }
}
