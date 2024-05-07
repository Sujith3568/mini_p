#include <WiFi.h>

const char* ssid = "realme 7";
const char* password = "_sujith_";

WiFiServer server(80);
int val1 = 2;
int val2 = 4;
int mtr = 5;

void setup() {
    Serial.begin(115200);
    pinMode(val1, OUTPUT);
    pinMode(val2, OUTPUT);
    pinMode(mtr,OUTPUT);
    delay(10);

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.begin();
}

void loop() {
  
    WiFiClient client = server.available();

    if (client) {
        Serial.println("New Client.");
        String currentLine = "";

        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();
                        client.println("<!DOCTYPE HTML>");
                        client.println("<html>");
                        client.println("<head><title>Water Control</title>");
                        client.println("<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>");
                        client.println("<style>");
                        client.println("body { font-family: Arial, sans-serif; text-align: center; background-color: #a2bec2;}");
                        client.println("button { width :300px; height:100px ; margin-top:100px; background-color:#9aac0d; box-shadow:5px 5px 10px #00000026; font-size: 50px;}");
                        client.println("h1 { font-size: 50px; color: black;margin-top:100px;}");
                        client.println("a { text-decoration: none; color: #007bff; }");
                        client.println("</style>");
                        client.println("</head>");
                        client.println("<body>");
                        client.println("<h1>AgriWater</h1>");
                        client.println("<a href=\"/H\"><button onclick='showMotorStatus()'> ON </button> </a><br>");
                        client.println("<script>function showMotorStatus() { alert('The motor is on'); } </script>");
                        client.println("</body>");
                        client.println("</html>");
                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }
                if (currentLine.endsWith("GET /H")) {
                    digitalWrite(val2,LOW);
                    digitalWrite(val1, HIGH);
                    delay(100);
                    digitalWrite(mtr, HIGH);
                    delay(6000);
                    digitalWrite(val1,LOW);
                    digitalWrite(val2,HIGH);
                    delay(6000);
                    digitalWrite(mtr, LOW);
                    digitalWrite(val2, LOW); 
                     }
                }
            
        }
       client.stop();
        Serial.println("Client Disconnected.");
    
    }
}
