#include <Servo.h>
#include <DHT.h> // Include the DHT library

// Create Servo Objects
Servo mg995_1, mg995_2, mg995_3;
Servo servo_1, servo_2, servo_3;

// Define Servo Pins
const int mg995_pins[] = {3, 5, 6};
const int simple_servo_pins[] = {9, 10, 11};

// DHT11 Sensor
#define DHTPIN 2     // Digital pin connected to the DHT data pin
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin(); // Initialize the DHT sensor

  // Attach Servos
  mg995_1.attach(mg995_pins[0]);
  mg995_2.attach(mg995_pins[1]);
  mg995_3.attach(mg995_pins[2]);

  servo_1.attach(simple_servo_pins[0]);
  servo_2.attach(simple_servo_pins[1]);
  servo_3.attach(simple_servo_pins[2]);

  Serial.println("Robotic Arm Initialized with DHT11");
}

void loop() {
  // Read temperature as Celsius (the default)
  float tempC = dht.readTemperature();

  // Check if reading was successful
  if (isnan(tempC)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.println(" °C");

  if (tempC < 25) { // Adjust temperature thresholds as needed
    moveArm(0);
  } else if (tempC >= 25 && tempC < 35) {
    moveArm(1);
  } else {
    moveArm(2);
  }

  delay(2000);
}

void moveArm(int category) {
  if (category == 0) {
    Serial.println("Cold - Moving to Position 1");
    mg995_1.write(45);
    servo_1.write(45);
  } else if (category == 1) {
    Serial.println("Warm - Moving to Position 2");
    mg995_2.write(90);
    servo_2.write(90);
  } else {
    Serial.println("Hot - Moving to Position 3");
    mg995_3.write(135);
    servo_3.write(135);
  }
  delay(1000);
}