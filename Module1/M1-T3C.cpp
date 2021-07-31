const int LEDR = 5; // Red LED
const int LEDG = 4; // Green LED
const int PIR = 2; // PIR sensor
const int BTN = 3; // Push button
const int TEMP = A0; // Temperature sensor

void setup() {
  // set up the inputs and outputs
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(BTN, INPUT);
  pinMode(TEMP, INPUT);
  
  // Start the serial at 9600 bits per second
  Serial.begin(9600);
  
  // Attach interrupt functions
  attachInterrupt(digitalPinToInterrupt(PIR), pirInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BTN), btnInterrupt, FALLING);
}

void loop() {
}

void pirInterrupt() {
  // Read the PIR sensor
  int motionState = digitalRead(PIR);
  Serial.println(motionState);
  
  // Update the Red LED depending on the PIR reading
  digitalWrite(LEDG, motionState);
  Serial.println("Green LED: " + String(motionState));
}

void btnInterrupt() {
  int tempReading = analogRead(TEMP);
  int celsius = map(((tempReading - 20) * 3.04), 0, 1023, -40, 125);
  
  // Print the temprerature
  Serial.println(String(celsius) + "C");
    
  // If the temperature is above 30 degree turn on the red light
  if (celsius > 30) {
  	digitalWrite(LEDR, HIGH);
    Serial.println("It is hot");
  } else {
    digitalWrite(LEDR, LOW);
    Serial.println("It is normal");
  }
  
}

