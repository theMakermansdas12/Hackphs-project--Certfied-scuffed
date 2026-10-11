#include <WiFi.h>
#include <Network.h>

const char *ssid = "yourAP12345";
const char *password = "123456789";

NetworkServer server(80);

#include <ESP32SERVO.h>
#include <ESP32PWM.h>
int PropellorMotorA = 5;
int PropellorMotorB = 4;
int ENABLEMOTOR = 2;
Servo TServo;
Servo PServo;
ESP32PWM pwm(true); 
const int StartServoPosition = 90;
int value = 0; // servo position i think

if("D_KEY"){
  PServo.write(value-=5);
    server.send(200, "turning right", value);
}
else if("A_KEY"){
  PServo.write(value+=5));
    server.send(200, "turning left", value);
}
else{
  server.send(200, "not turning", "unknown command:" + command);
}

void setup() {
Serial.begin(115200);
if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while (1);
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  server.begin();
PServo.attach(26);
TServo.attach(27);
PServo.write(StartServoPosition);
pinMode(PropellorMotorA, OUTPUT);
pinMode(PropellorMotorB, OUTPUT);
pinMode(ENABLEMOTOR, OUTPUT);
digitalWrite(PropellorMotorA, LOW);
digitalWrite(PropellorMotorB, LOW);
digitalWrite(ENABLEMOTOR, HIGH);
}

void loop() {
NetworkClient client = server.accept();  // listen for incoming clients

  if (client) {                     // if you get a client,
    Serial.println("New Client.");  // print a message out the serial port
    String currentLine = "";        // make a String to hold incoming data from the client
    while (client.connected()) {    // loop while the client's connected
      if (client.available()) {     // if there's bytes to read from the client,
        char c = client.read();     // read a byte, then
        Serial.write(c);            // print it out the serial monitor
        if (c == '\n') {            // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {  // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, HIGH);  // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, LOW);  // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }


while(W-KEY) {
  digital.Write(PropellorMotorA, HIGH);
digital.Write(PropellorMotorB, LOW);
}
while("S_KEY") {
  digital.Write(PropellorMotorA, LOW);
digital.Write(PropellorMotorB, HIGH);
}
delay(100);
}
