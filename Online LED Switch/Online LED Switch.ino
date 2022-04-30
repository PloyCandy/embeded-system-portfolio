#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Ploy Candy";
const char* password = "86082000";
const char* mqtt_server = "mqtt.netpie.io";
const int mqtt_port = 1883;
const char* ClientID = "35f6bc7d-924c-475a-b785-2f7fb36956dc";
const char* mqtt_username = "ibvPCasNqFkHrCAwxZqJjW4KkUgYAZ5B";
const char* mqtt_password = "p8#BL*sW$nEuZVjQa1C!)O$eFMCxSTQa";
const char* Topic = "@msg/CSS452IoT/LED";

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
    
  ClientESP.setServer(mqtt_server, mqtt_port); //set the MQTT server and port.
  ClientESP.setCallback(callback);
  ConnectMQTT(); //Connect to the MQTT server.

  pinMode(26, OUTPUT); //Set the pin mode to the pin GPIO26
  digitalWrite(26, LOW);
}

void loop() {
  if (!ClientESP.connected()) {
    ConnectMQTT();
  }
  ClientESP.loop();  
}

void ConnectMQTT() {
  while (!ClientESP.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect to the broker
    if (ClientESP.connect(ClientID, mqtt_username, mqtt_password)) {
          Serial.println("connected");
          ClientESP.setCallback(callback);
          ClientESP.subscribe(Topic);         
    } else {
      Serial.print("failed, rc=");
      Serial.print(ClientESP.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }  
}

void callback(char* topic, byte* payload, unsigned int length) {
  String ValString;
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    ValString += (char)payload[i];
  }
  if (ValString == "ON" ) {
    digitalWrite(26, HIGH);   // Turn the LED on 
  } else {
    digitalWrite(26, LOW);  // Turn the LED off
  }
}
