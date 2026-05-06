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
