#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "TON_WIFI";
const char* password = "TON_MDP";

WebServer server(80);

int led = 25;
int buzzer = 26;

void setup() {
  Serial.begin(115200);

  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/ledon", []() {
    digitalWrite(led, HIGH);
    server.send(200, "text/plain", "LED ON");
  });

  server.on("/ledoff", []() {
    digitalWrite(led, LOW);
    server.send(200, "text/plain", "LED OFF");
  });

  server.on("/buzzeron", []() {
    digitalWrite(buzzer, HIGH);
    server.send(200, "text/plain", "BUZZER ON");
  });

  server.on("/buzzeroff", []() {
    digitalWrite(buzzer, LOW);
    server.send(200, "text/plain", "BUZZER OFF");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
