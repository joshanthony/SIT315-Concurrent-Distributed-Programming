const int LEDR = 12; // Red LED
const int LEDB = 11; // Blue LED
const int LEDG = 10; // Green LED
const int LEDO = 13; // Orange LED
const int PIR = 2; // PIR sensor
const int BTN = 3; // Push button
const int TEMP = A1; // Temperature sensor
const int FORCE = A0; // Force sensor
const int TILT = 5; // Tilt sensor

void setup() {
  // set up the inputs and outputs
  pinMode(LEDR, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDO, OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(BTN, INPUT_PULLUP);
  pinMode(TEMP, INPUT);
  pinMode(FORCE, INPUT);
  pinMode(TILT, INPUT_PULLUP);

  // Enable interrupt pin D5 at the PCI mask register
  PCMSK2 |= B00100000;
  // Clear interrupts
  PCIFR = B00000000;
  // Enable pin change interrupt control register for pins D0-D7
  PCICR |= B00000100;
  
  // Start the serial at 9600 bits per second
  Serial.begin(9600);
  
  // Start the timer
  startTimer();
  
  // Attach interrupt functions
  attachInterrupt(digitalPinToInterrupt(PIR), pirInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BTN), btnInterrupt, FALLING);
}

void loop() {
}

void startTimer(){
  noInterrupts();
  
  // Reset the registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // Every 3 seconds at 1024 prescaler
  OCR1A = 46874;

  // 1024 prescaler value
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // Compare match interrupt
  TIMSK1 |= (1 << OCIE1A);
  TCCR1B |= (1 << WGM12);
  
  interrupts();
}


void pirInterrupt() {
  // Read the PIR sensor
  int motionState = digitalRead(PIR);
  Serial.println(motionState);
  
  // Enable yellow LED if there is motion
  digitalWrite(LEDG, motionState);
  digitalWrite(LEDB, LOW);
  digitalWrite(LEDR, motionState);
  Serial.println("Green LED: " + String(motionState));
}

void btnInterrupt() {
  int celsius = map(((analogRead(TEMP) - 20) * 3.04), 0, 1023, -40, 125);
  
  // Print the temprerature
  Serial.println(String(celsius) + "C");
    
  // If 30C or above turn on the red light, if less than 30C show green light
  if (celsius >= 30) {
    // Show red LED
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDB, LOW);
    digitalWrite(LEDG, LOW);
    Serial.println("It is hot");
  } else {
    // Show green LED
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDB, LOW);
    digitalWrite(LEDG, HIGH);

    Serial.println("It is normal");
  }
  
}

ISR(PCINT2_vect){
  // Show blue LED if tilt sensor is triggered
  digitalWrite(LEDB, !digitalRead(TILT));
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDR, LOW);
}

ISR(TIMER1_COMPA_vect){
  // Read the level of force applied to the force sensor and print to serial
  int force = analogRead(FORCE);
  Serial.println("Force applied: " + String(force));
  // Blink the orange LED to indicate a reading was taken
  digitalWrite(LEDO, digitalRead(LEDO) ^ 1);
}