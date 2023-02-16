int photoPin = A0; // Photoresistor input pin
int ledPin1 = 13; // LED output pin
int ledPin2 = 12;
int ledPin3 = 11;
int maxLightLevel = 0; // variable to store the maximum light level seen so far
bool takeReadings = true; // boolean variable to control whether readings should be taken

void setup() {
  pinMode(photoPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (takeReadings) { // only take readings if takeReadings is true
    int lightLevel = analogRead(photoPin);
    if (lightLevel > maxLightLevel) {
      maxLightLevel = lightLevel; // update the maximum light level seen so far
    }

    if (lightLevel > 450) {
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin3, LOW);
      delay(100);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin1, LOW);
      delay(100);
      digitalWrite(ledPin3, HIGH);
      digitalWrite(ledPin2, LOW);
      delay(100);
    } else {
      Serial.println(lightLevel);
      digitalWrite(ledPin2, LOW);
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin3, LOW);
    }

    delay(100); // Delay for stability
  }
}

void serialEvent() {
  // read the incoming command and toggle takeReadings accordingly
  while (Serial.available()) {
    char command = Serial.read();
    if (command == 's') { // 's' for start
      takeReadings = true;
      Serial.println("Started taking readings.");
    } else if (command == 't') { // 't' for stop
      takeReadings = false;
      Serial.println("Stopped taking readings.");
    }
  }
  if (!takeReadings) {
    // if not taking readings, send the maximum light level to the serial monitor
    Serial.print("Maximum light level: ");
    Serial.println(maxLightLevel);
  }
}
