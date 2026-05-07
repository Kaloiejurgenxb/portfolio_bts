# 1. Affichage de l'adresse IP et connecte la carte ESP32 à internet
```cpp
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "VOTRE_WIFI";
const char* password = "VOTRE_MOT_DE_PASSE";

const char* serverName = "http://192.168.1.100/data.php";

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}
```
