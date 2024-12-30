#include <LoRa.h>

const int LED_PIN = 13;    // LED for indication

// Woman's details
String name = "Priya";
int age = 20;
String education = "SA Engineering College";
String phoneNumber = "6302246557";
String fatherName = "Krishna";
String fatherPhone = "9491597450";
String motherName = "Kavitha";
String motherPhone = "9490023833";

String latitude = "11.914694";  
String longitude = "79.634569"; 

void setup() {
  Serial.begin(115200);  // Initialize serial monitor
  while (!Serial);

  pinMode(LED_PIN, OUTPUT);  // Set LED pin to output

  // Attempt to initialize LoRa module
  if (!LoRa.begin(475E6)) {  // Ensure correct frequency (915 MHz in this case)
    Serial.println("LoRa initialization failed. Continuing to transmit details...");
  } else {
    Serial.println("LoRa initialized.");
  }
}

void loop() {
  // Transmit the woman's details every 2 seconds
  transmitDetails();
  delay(2000);  // Wait for 2 seconds before sending again
}

// Function to transmit the woman's details
void transmitDetails() {
  // Combine woman's and family details with latitude and longitude
  String message = "I am in danger!\n";
  message += "Name: " + name + "\n";
  message += "Age: " + String(age) + "\n";
  message += "Education: " + education + "\n";
  message += "Phone: " + phoneNumber + "\n";
  message += "Father: " + fatherName + ", Father's Phone: " + fatherPhone + "\n";
  message += "Mother: " + motherName + ", Mother's Phone: " + motherPhone + "\n";
  message += "GPS Coordinates: Lat=" + latitude + ", Lon=" + longitude + "\n";
  message += "----------------------\n";

  // Check if LoRa is initialized, and transmit via LoRa if possible
  if (LoRa.begin(475E6)) {
    // Transmit message via LoRa
    digitalWrite(LED_PIN, HIGH); // Turn on LED while transmitting
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket();
    digitalWrite(LED_PIN, LOW); // Turn off LED after transmission
    Serial.println("Transmitted via LoRa: ");
    Serial.println(message); // Print the transmitted message to the Serial Monitor
  } else {
    Serial.println(message); // Print the details in the Serial Monitor
  }
}