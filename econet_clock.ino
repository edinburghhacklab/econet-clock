// ATtiny85 16MHz PLL

const int periodPin = A2; // pin 3 on IC
const int dutyPin = A3;   // pin 2 on IC
const int jumperPin = 0;  // pin 5 on IC

// With a 16MHz Clock and 1:1 prescaler, each clock tick will be 0.0625us
const int periodMin = 23;  // 23 ticks = 1.4us = 695khz
const int periodMax = 208; // 208 ticks = 13us = 77khz
const int dutyMin = 7;     // 7 ticks = 0.44us
const int dutyMax = 32;    // 32 ticks = 2us (will be capped at 50% duty cycle)

int period;
int duty;

void setup() {
  pinMode(periodPin, INPUT);
  pinMode(dutyPin, INPUT);
  pinMode(jumperPin, INPUT);
  digitalWrite(jumperPin, HIGH); // pull-up on the jumper pin

  // initial reading
  period = map(analogRead(periodPin), 0, 1023, periodMin, periodMax);
  duty = map(analogRead(dutyPin), 0, 1023, dutyMin, dutyMax);
  duty = min(duty, period/2); // limit the duty cycle to 50%
  
  OCR0A = period;
  OCR0B = duty; 
  
  TCCR0A = (1<<COM0B1)|(0<<COM0B0)|(1<<WGM01)|(1<<WGM00); // Fast PWM mode, toggle OC0A on compare match
  TCCR0B = (1<<WGM02)|(0<<CS02)|(0<<CS01)|(1<<CS00);
  DDRB |= (1<<DDB1); // pin 6 on IC
}

void loop() {
  
  // read the pots and update the clock signal,
  // but only if the jumper has been removed
  if (digitalRead(jumperPin) == HIGH) {
    period = map(analogRead(periodPin), 0, 1023, periodMin, periodMax);
    duty = map(analogRead(dutyPin), 0, 1023, dutyMin, dutyMax);
    duty = min(duty, period/2);
    OCR0A = period;
    OCR0B = duty;
  }

  delay(5);
}

