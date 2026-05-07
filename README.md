# Projet ESP32 – Communication Wi-Fi et Serveur Web

## Description
Ce projet met en place une communication entre une carte ESP32 et un serveur web.

Il permet :
- la connexion Wi-Fi
- l’envoi de données avec POST
- la récupération de données avec GET
- le stockage sur serveur PHP
- l’affichage sur une page web

# Matériel
## câble

### LED
- La LED est connectée à la broche GPIO 25 de l’ESP32 avec une résistance de protection de 220Ω.

### Buzzer
- Le buzzer est connecté à la broche GPIO 26 afin de produire un signal sonore.

# 1. Connexion Wi-Fi + affichage de l’adresse IP

## Fonctionnement
L’ESP32 se connecte au Wi-Fi et affiche son adresse IP pour confirmer la connexion Internet.

## Code ESP32

```cpp
#include <WiFi.h>

const char* ssid = "VOTRE_WIFI";
const char* password = "VOTRE_MOT_DE_PASSE";

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.print("Connexion au Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi connecté !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());
}

void loop() {}
```

---

# 2. Envoi de données vers le serveur (POST)

## Fonctionnement
La méthode POST envoie des données dans le corps de la requête HTTP vers un fichier PHP.

## Code ESP32

```cpp
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "VOTRE_WIFI";
const char* password = "*****";

const char* serverName = "http://192.168.1.100/data.php";

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    int valeur = random(10, 100);

    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String data = "valeur=" + String(valeur);

    int code = http.POST(data);

    Serial.print("Valeur envoyée (POST) : ");
    Serial.println(valeur);

    Serial.print("Code HTTP : ");
    Serial.println(code);

    http.end();
  }

  delay(5000);
}
```



# 3. Récupération des données (GET)

##  Fonctionnement
La méthode GET permet de récupérer les données stockées sur le serveur via une URL.

## Code ESP32

```cpp
#include <WiFi.h>
#include <HTTPClient.h>

const char* serverName = "http://192.168.1.100/data.php?read=1";

void setup() {
  Serial.begin(115200);
}

void loop() {

  HTTPClient http;

  http.begin(serverName);

  int code = http.GET();

  if (code > 0) {
    String response = http.getString();
    Serial.print("Données reçues (GET) : ");
    Serial.println(response);
  }

  http.end();

  delay(5000);
}
```


# 4. Serveur PHP (POST + GET)

## POST → enregistrement

```php
<?php

if (isset($_POST['valeur'])) {

    $valeur = $_POST['valeur'];

    file_put_contents("valeur.txt", $valeur . PHP_EOL, FILE_APPEND);

    echo "OK";
}

?>
```

## GET → lecture des données

```php
<?php

if (isset($_GET['read'])) {

    echo file_get_contents("valeur.txt");
}

?>
```



# 5. Affichage sur site web

## Fonctionnement
Le site affiche les données stockées dans le fichier `valeur.txt`.

```php
<?php

echo "<h1>Données ESP32</h1>";

if (file_exists("valeur.txt")) {
    echo "<pre>";
    echo file_get_contents("valeur.txt");
    echo "</pre>";
} else {
    echo "Aucune donnée disponible";
}

?>
```

---
# TP2 – ESP32 : Contrôle d’actionneurs via serveur Web

## Description
- Ce TP permet de contrôler des composants (LED et buzzer) à distance via une page web, en utilisant une carte une carte ESP32.

- L’ESP32 agit comme un serveur web et reçoit des commandes depuis un navigateur.



# 1. Connexion Wi-Fi + serveur Web

## Fonctionnement
L’ESP32 :
- se connecte au Wi-Fi
- démarre un serveur web
- attend les requêtes HTTP

## Code

```cpp
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "TON_WIFI";
const char* password = "*****";

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

  Serial.print("IP ESP32 : ");
  Serial.println(WiFi.localIP());

  // Routes HTTP
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
```


# 2. Interface Web (HTML + JavaScript)

## Fonctionnement
Une page web envoie des requêtes HTTP GET vers l’ESP32 pour contrôler les composants.


## Code HTML

```html
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title>TP2 ESP32</title>
</head>
<body>

<h1>Contrôle ESP32</h1>

<button onclick="fetch('http://192.168.100.55/ledon')">LED ON</button>
<button onclick="fetch('http://192.168.100.55/ledoff')">LED OFF</button>

<br><br>

<button onclick="fetch('http://192.168.100.55/buzzeron')">BUZZER ON</button>
<button onclick="fetch('http://192.168.100.55/buzzeroff')">BUZZER OFF</button>

</body>
</html>
```

# 3. Fonctionnement des requêtes (GET)

## Explication
Dans ce TP, toutes les commandes utilisent la méthode **GET**.

##  Exemple :
```
http://IP_ESP32/ledon
http://IP_ESP32/ledoff
http://IP_ESP32/buzzeron
http://IP_ESP32/buzzeroff
```



##  Rôle de GET dans ce TP

- envoyer une commande via URL
- déclencher une action immédiate
- contrôler les GPIO de l’ESP32



#  Conclusion TP2

Ce TP permet :
- de transformer l’ESP32 en serveur web
- de contrôler des actionneurs à distance
- d’utiliser des requêtes HTTP GET
- de créer une interface web simple



#  FIN DU PROJET

Le projet complet est composé de :
- TP1 : communication ESP32 ↔ serveur PHP (GET/POST)
- TP2 : contrôle ESP32 via serveur Web (GET uniquement)



# Conclusion
Ce projet permet :
- connexion Wi-Fi ESP32
- communication HTTP (GET / POST)
- stockage de données sur serveur PHP
- affichage web des données

