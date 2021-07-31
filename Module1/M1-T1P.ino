const int LED = 3; 
const int PIR = 2;

void setup() {
  // set up the inputs and outputs
  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);
  
  // Start the serial at 9600 bits per second
  Serial.begin(9600);
}

void loop() {
  // Read the PIR sensor
  int motion = digitalRead(PIR);
  Serial.println(motion);
  
  // Update the LED depending on the PIR reading
  if (motion == HIGH) {
    digitalWrite(LED, HIGH);
    Serial.println("LED ON");
  } else {
  	digitalWrite(LED, LOW);
    Serial.println("LED OFF");
  }
  
  // Wait before reading again
  delay(2000);
}