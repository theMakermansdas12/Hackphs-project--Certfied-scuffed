
#include <WiFi.h>
#include <ESP32Servo.h>
#include <Network.h>
NetworkServer server(80);

const char* ssid = "yourAP12345";
const char* password = "123456789";

const int PropellorMotorA = 5;
const int PropellorMotorB = 4;
const int ENABLEMOTOR = 2;

const int SERVO_PIN = 26;
const int TILT_SERVO_PIN = 27;

Servo TServo;
Servo PServo;

int servoPosition = 90;
int tiltPosition = 90;

unsigned long lastCommandTime = 0;
const unsigned long MOTOR_TIMEOUT = 3000;

bool motorRunning = false;

void stopMotor() {
  digitalWrite(PropellorMotorA, LOW);
  digitalWrite(PropellorMotorB, LOW);
  motorRunning = false;
}


void sendResponse(NetworkClient& client,
                  const String& message,
                  const char* contentType = "text/plain") {
  client.println("HTTP/1.1 200 OK");
  client.print("Content-Type: ");
  client.println(contentType);
  client.println("Connection: close");
  client.println();
  client.print(message);
}


void handleRequest(String requestLine, NetworkClient& client) {
  requestLine.trim();

  Serial.println(requestLine);

  if (requestLine.startsWith("GET /forward ")) {
    digitalWrite(PropellorMotorA, HIGH);
    digitalWrite(PropellorMotorB, LOW);
    motorRunning = true;
    lastCommandTime = millis();

    sendResponse(client, "Moving forward");
  }
  else if (requestLine.startsWith("GET /backward ")) {
    digitalWrite(PropellorMotorA, LOW);
    digitalWrite(PropellorMotorB, HIGH);
    motorRunning = true;
    lastCommandTime = millis();

    sendResponse(client, "Moving backward");
  }
  else if (requestLine.startsWith("GET /left ")) {
    servoPosition = constrain(servoPosition + 5, 0, 180);
    PServo.write(servoPosition);

    sendResponse(client, "Servo position: " + String(servoPosition));
  }
  else if (requestLine.startsWith("GET /right ")) {
    servoPosition = constrain(servoPosition - 5, 0, 180);
    PServo.write(servoPosition);

    sendResponse(client, "Servo position: " + String(servoPosition));
  }
  else if (requestLine.startsWith("GET /tiltup ")) {
    tiltPosition = constrain(tiltPosition + 5, 0, 180);
    TServo.write(tiltPosition);

    sendResponse(client, "Tilt position: " + String(tiltPosition));
  }
  else if (requestLine.startsWith("GET /tiltdown ")) {
    tiltPosition = constrain(tiltPosition - 5, 0, 180);
    TServo.write(tiltPosition);

    sendResponse(client, "Tilt position: " + String(tiltPosition));
  }
  else if (requestLine.startsWith("GET /off ")) {
    stopMotor();
    sendResponse(client, "Motor stopped");
  }
  else if (requestLine.startsWith("GET / ")) {
    stopMotor();

    String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>ESP32 Robot Control</title>
<style>
body {
  font-family: Arial, sans-serif;
  text-align: center;
  background: #172033;
  color: white;
  margin: 0;
  padding: 20px;
}
h1 { font-size: 27px; }
p { color: #cbd5e1; }
.grid {
  display: grid;
  grid-template-columns: repeat(3, minmax(75px, 110px));
  justify-content: center;
  gap: 10px;
  margin: 22px auto;
}
button {
  padding: 18px 8px;
  font-size: 16px;
  border: none;
  border-radius: 12px;
  color: white;
  background: #2563eb;
  cursor: pointer;
  touch-action: manipulation;
}
button:active { background: #1d4ed8; }
.stop { background: #dc2626; }
.empty { visibility: hidden; }
.status { margin: 20px; min-height: 24px; }
</style>
</head>
<body>
<h1>ESP32 Robot Control</h1>
<p>Connect to the ESP32 Wi-Fi network to control your robot.</p>

<h3>Drive</h3>
<div class="grid">
  <button class="empty"> </button>
  <button onclick="cmd('forward')">Forward</button>
  <button class="empty"> </button>
  <button onclick="cmd('left')">Left</button>
  <button class="stop" onclick="cmd('off')">STOP</button>
  <button onclick="cmd('right')">Right</button>
  <button class="empty"> </button>
  <button onclick="cmd('backward')">Backward</button>
  <button class="empty"> </button>
</div>

<h3>Camera / Tilt</h3>
<div class="grid">
  <button class="empty"> </button>
  <button onclick="cmd('tiltup')">Tilt Up</button>
  <button class="empty"> </button>
  <button class="empty"> </button>
  <button onclick="cmd('tiltdown')">Tilt Down</button>
  <button class="empty"> </button>
</div>

<div class="status" id="status">Ready</div>

<script>
async function cmd(action) {
  const status = document.getElementById('status');
  status.textContent = 'Sending: ' + action;
  try {
    const response = await fetch('/' + action, {
      cache: 'no-store'
    });
    status.textContent = await response.text();
  } catch (e) {
    status.textContent = 'Connection error';
  }
}
</script>
</body>
</html>
)rawliteral";

    sendResponse(client, page, "text/html");
  }
  else {
    client.println("HTTP/1.1 404 Not Found");
    client.println("Content-Type: text/plain");
    client.println("Connection: close");
    client.println();
    client.println("Unknown command");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(PropellorMotorA, OUTPUT);
  pinMode(PropellorMotorB, OUTPUT);
  pinMode(ENABLEMOTOR, OUTPUT);

  stopMotor();
  digitalWrite(ENABLEMOTOR, HIGH);

  PServo.attach(SERVO_PIN);
  TServo.attach(TILT_SERVO_PIN);

  PServo.write(servoPosition);
  TServo.write(tiltPosition);

  WiFi.mode(WIFI_AP);

  if (!WiFi.softAP(ssid, password)) {
    Serial.println("Failed to start Wi-Fi AP");
    while (true) {
      stopMotor();
      delay(1000);
    }
  }

  Serial.println();
  Serial.print("Wi-Fi network: ");
  Serial.println(ssid);
  Serial.print("Open this address: http://");
  Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop() {
  // Safety timeout: stop the motor if no new drive
  // command arrives for three seconds.
  if (motorRunning &&
      millis() - lastCommandTime >= MOTOR_TIMEOUT) {
    stopMotor();
    Serial.println("Motor timeout: stopped");
  }
  NetworkClient client = server.accept();

  if (!client) {
    return;
  }

  client.setTimeout(1000);

  String requestLine = client.readStringUntil('\n');
  requestLine.trim();

  if (requestLine.length() > 0) {
    handleRequest(requestLine, client);
  }

  client.flush();
  delay(1);
  client.stop();
}
