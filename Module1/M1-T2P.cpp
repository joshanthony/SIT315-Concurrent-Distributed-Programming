const int LED = 3; 
const int PIR = 2;

void setup() {
  // set up the inputs and outputs
  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);
  
  // Start the serial at 9600 bits per second
  Serial.begin(9600);
  
  // Attach interrupt function
  attachInterrupt(digitalPinToInterrupt(PIR), pirInterrupt, CHANGE);
}

void loop() {
}

void pirInterrupt() {
  // Read the PIR sensor
  int motionState = digitalRead(PIR);
  Serial.println(motionState);
  
  // Update the LED depending on the PIR reading
  digitalWrite(LED, motionState);
  Serial.println("LED: " + String(motionState));
}
