#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Ploy   2.4g";
const char* password = "p0874536770";
const char* mqtt_server = "192.168.2.37";
const int mqtt_port = 1883;
const char* ClientID = "ClientPubSub";
const char* Topic = "/IoT/Test1";
long lastMsg = 0;

WiFiClient ClientNode;
PubSubClient ClientESP(ClientNode);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
    
  ClientESP.setServer(mqtt_server, mqtt_port); //Set the MQTT server and port.
  ConnectMQTT(); //Connect to the MQTT server.
}

void loop() {
  if (!ClientESP.connected()) {
    ConnectMQTT();
  }
  
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    char Val[8];
    dtostrf(random(100), 1, 0, Val); 
    ClientESP.publish(Topic, Val);
    Serial.print("Pub: ");
    Serial.println(Val);
  }
}

void ConnectMQTT() {
  while (!ClientESP.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect to the broker
    if (ClientESP.connect(ClientID, NULL, NULL)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(ClientESP.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }  
}
