
# Projet BTS CIEL – ESP32 et Web

## Description
Ce projet met en place une communication entre une ESP32 et un serveur web.

Il est composé de deux travaux pratiques :
- TP1 : envoi et affichage de données
- TP2 : contrôle d’actionneurs (LED et buzzer)

---

# TP1 – ESP32 Web

## Objectif
Envoyer des données depuis une ESP32 vers un serveur web et les afficher.

## Fonctionnement
- L’ESP32 génère des valeurs
- Les valeurs sont envoyées au serveur via HTTP
- PHP stocke les données dans un fichier
- Une page web affiche les données

---

# TP2 – LED et Buzzer

## Objectif
Contrôler une LED et un buzzer depuis une page web.

## Fonctionnement
- Une interface web envoie des commandes
- L’ESP32 reçoit les commandes
- Elle active les GPIO :
  - GPIO 25 → LED
  - GPIO 26 → buzzer

void setup() {
  Serial.begin(115200);
}

void loop() {
  int valeur = random(0, 100);
  Serial.println(valeur);
  delay(2000);
}

<?php
$file = "valeur.txt";

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (isset($_POST['valeur'])) {
        file_put_contents($file, $_POST['valeur']);
    }
    exit;
}

$valeur = file_exists($file) ? file_get_contents($file) : "Aucune valeur";
?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title>TP1 ESP32</title>
    <meta http-equiv="refresh" content="5">
</head>
<body>

<h1>Données ESP32</h1>

<p><?php echo htmlspecialchars($valeur); ?></p>

</body>
</html>

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

  server.on("/led", []() {
    digitalWrite(led, HIGH);
    server.send(200, "text/plain", "LED ON");
  });

  server.on("/ledoff", []() {
    digitalWrite(led, LOW);
    server.send(200, "text/plain", "LED OFF");
  });

  server.on("/son", []() {
    digitalWrite(buzzer, HIGH);
    server.send(200, "text/plain", "BUZZER ON");
  });

  server.on("/sonoff", []() {
    digitalWrite(buzzer, LOW);
    server.send(200, "text/plain", "BUZZER OFF");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}

<?php
$file = "valeur.txt";

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (isset($_POST['valeur'])) {
        file_put_contents($file, $_POST['valeur']);
    }
    exit;
}

$valeur = file_exists($file) ? file_get_contents($file) : "Aucune commande";
?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title>TP2 ESP32</title>
    <meta http-equiv="refresh" content="5">
</head>
<body>

<h1>Contrôle LED et Buzzer</h1>

<p><?php echo htmlspecialchars($valeur); ?></p>

<button onclick="fetch('http://192.168.100.55/led')">LED ON</button>
<button onclick="fetch('http://192.168.100.55/ledoff')">LED OFF</button>

<button onclick="fetch('http://192.168.100.55/son')">BUZZER ON</button>
<button onclick="fetch('http://192.168.100.55/sonoff')">BUZZER OFF</button>

</body>
</html>

