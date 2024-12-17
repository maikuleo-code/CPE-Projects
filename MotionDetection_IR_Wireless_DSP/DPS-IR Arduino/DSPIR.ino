#include <WiFiS3.h>
#include <ArduinoHttpClient.h>

// WiFi credentials
const char* ssid = "Mike";
const char* password = "12345678";

// Server details
const char* server = "192.168.13.153"; // Your server's IP address
int port = 80; // HTTP port
String resource = "/DSP/save_motion.php"; // PHP script path

WiFiClient wifiClient;
HttpClient httpClient(wifiClient, server, port);

#define IR_SENSOR 5  // Pin for IR sensor

bool irSensorPrevState = LOW;  // Previous state of the IR sensor

void setup() {
  Serial.begin(9600);
  pinMode(IR_SENSOR, INPUT);

  connectWiFi();
}

void loop() {
  handleIRSensor();
}

void handleIRSensor() {
  // Read the current state of the IR sensor
  bool irSensorCurrentState = digitalRead(IR_SENSOR);

  String postData;

  if (irSensorPrevState == HIGH && irSensorCurrentState == LOW) {
    // Motion detected
    Serial.println("Motion Detected");
    postData = "motion_status=Motion Detected";
    sendDataToServer(postData);
  } else if (irSensorPrevState == LOW && irSensorCurrentState == HIGH) {
    // No motion detected
    Serial.println("No Motion Detected");
    postData = "motion_status=No Motion Detected";
    sendDataToServer(postData);
  }

  // Update the previous state
  irSensorPrevState = irSensorCurrentState;
}

void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void sendDataToServer(String postData) {
  if (WiFi.status() == WL_CONNECTED) {
    // Begin the request
    httpClient.beginRequest();
    httpClient.post(resource);

    // Set the correct content type for form data
    httpClient.sendHeader("Content-Type", "application/x-www-form-urlencoded");
    httpClient.sendHeader("Content-Length", postData.length());

    // Send the data in the correct format
    httpClient.print(postData);

    // End the request
    httpClient.endRequest();

    // Get and print the response
    int statusCode = httpClient.responseStatusCode();
    String response = httpClient.responseBody();
    Serial.print("Status Code: ");
    Serial.println(statusCode);  // Print the HTTP status code
    Serial.print("Response: ");
    Serial.println(response);    // Print the server's response
  } else {
    Serial.println("WiFi Disconnected");
  }
}
