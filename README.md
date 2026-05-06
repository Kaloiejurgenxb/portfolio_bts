
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

