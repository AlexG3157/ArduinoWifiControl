#include <WiFi.h>
#include <WiFiUdp.h>

char* ssid = "SSID";      
char* password = "PASSWORD";  

WiFiUDP udp;
unsigned int localPort = 3158;  

int x_axis = 0;
int y_axis = 0;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  udp.begin(localPort);
  Serial.printf("Now listening on port %d\n", localPort);
}

void loop() {

  int packetSize = udp.parsePacket();
  if (packetSize) {
    char packetBuffer[255];  
    int len = udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;  
    }

    Serial.printf("Received: %s\n", packetBuffer);

    // expected format: "x_axis,y_axis"
    sscanf(packetBuffer, "%d,%d", &x_axis, &y_axis);

    Serial.printf("X: %d, Y: %d\n", x_axis, y_axis);
    
  }

  delay(10);  
}
