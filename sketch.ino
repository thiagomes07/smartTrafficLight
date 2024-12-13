#include <WiFi.h>
#include <HTTPClient.h>

// wifi credentials and the url to make a request
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* serverUrl = "http://www.google.com.br/";

#define GREEN_LED 38 // Pin used to control the green LED
#define RED_LED 36 // Pin used to control the red LED
#define YELLOW_LED 37 // Pin used to control the yellow LED

#define BUTTON 12  // the number of the pushbutton pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

int isRed = 0;   // state if signal is red

#define LDR 4 // the number of the ldr pin
// LDR Characteristics
const float GAMMA = 0.7;
const float RL10 = 50;

void setup() {
  // Initial configuration of the pins to control the LEDs as OUTPUTs of the ESP32
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);

  // Initializing inputs
  pinMode(BUTTON, INPUT_PULLUP); // Initialize the pushbutton pin as an input

  pinMode(LDR, INPUT); // Initialize the ldr pin as an input

  Serial.begin(115200); // Configuration for debugging via serial interface between ESP and computer with baud rate of 115200

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  int analogValue = analogRead(LDR);
  float voltage = analogValue / 1024. * 5;
  float resistance = 2000 * voltage / (1 - voltage / 5);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));

  if (lux > 50) {
    Serial.println("white");

    // green timer
    digitalWrite(GREEN_LED, HIGH);
    delay(3000);
    digitalWrite(GREEN_LED, LOW);

    // yellow timer
    digitalWrite(YELLOW_LED, HIGH);
    delay(2000);
    digitalWrite(YELLOW_LED, LOW);

    // red timer
    isRed = 1;
    digitalWrite(RED_LED, HIGH);
    delay(5000);
    send a http request to google if the wifi is connected and the light is red
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;

      // Specify the URL to fetch data from
      http.begin(serverUrl);

      // Send the GET request
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        String payload = http.getString();
        Serial.println("HTTP Response code: " + String(httpResponseCode));
        Serial.println("Response data: " + payload);
      } else {
        Serial.println("Error on HTTP request");
      }

      http.end();
    }
    isRed = 0;
    digitalWrite(RED_LED, LOW);
  } else {
    Serial.println("dark");
    digitalWrite(YELLOW_LED, HIGH);
    delay(1000);
    digitalWrite(YELLOW_LED, LOW);
    delay(1000);
  }

  // debounce button logic
  // read the state of the switch into a local variable:
  int reading = digitalRead(BUTTON);
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH && isRed == 1) {
        delay(1000); // add 1 second delay if the light is red
      }
    }
  }
  lastButtonState = reading;
}
