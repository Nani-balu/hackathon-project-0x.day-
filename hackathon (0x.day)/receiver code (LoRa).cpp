#include <SPI.h>
#include <LoRa.h>
#include <WomanDetails.h>  // Include the custom library with the woman's details

const int LED_PIN = 2;  // LED for indication

void setup() {
  Serial.begin(115200);  // Initialize serial monitor

  pinMode(LED_PIN, OUTPUT);  // Set LED pin to output

  // Initialize LoRa module
  if (!LoRa.begin(433E6)) {  // Ensure to use the correct frequency
    // If LoRa initialization fails, print woman's details instead of failure message
    Serial.println("Printing woman details:");
    
    Serial.println("iam in danger please help me...!");
    Serial.println("Woman's Details:");
    Serial.println("Name: " + WomanDetails::name);
    Serial.println("Age: " + String(WomanDetails::age));
    Serial.println("Education: " + WomanDetails::education);
    Serial.println("Phone Number: " + WomanDetails::phoneNumber);
    Serial.println("Father's Name: " + WomanDetails::fatherName);
    Serial.println("Father's Phone: " + WomanDetails::fatherPhone);
    Serial.println("Mother's Name: " + WomanDetails::motherName);
    Serial.println("Mother's Phone: " + WomanDetails::motherPhone);
    Serial.println("Location: Lat=" + WomanDetails::latitude + ", Lon=" + WomanDetails::longitude);
    Serial.println("---------------");

    while (1);  // Halt if LoRa initialization fails
  }
  Serial.println("LoRa initialized.");
}

void loop() {
  // Check if a message has been received
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedMessage = "";

    // Read the incoming message and store it in the variable
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }

    // Print received message
    Serial.println("Received Message:");
    Serial.println(receivedMessage);
    Serial.println("---------------");

    // Toggle the LED to indicate message received
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
  }

  delay(2000);  // Wait for the next LoRa packet
}