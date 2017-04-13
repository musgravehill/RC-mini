
#define ch1_pin 7
#define ch2_pin 6
#define ch3_pin 5
#define ch4_pin 4
#define ch5_pin 3
#define ch6_pin 2

#define out1_pin 9  //PWM
#define out2_pin 10 //PWM 
#define out3_pin 11 //PWM
#define out4_pin 12
#define out5_pin 13
#define out6_pin 8


int ch1, ch2, ch3, ch4, ch5, ch6;

void setup() {
  pinMode(ch1_pin, INPUT);
  pinMode(ch2_pin, INPUT);
  pinMode(ch3_pin, INPUT);
  pinMode(ch4_pin, INPUT);
  pinMode(ch5_pin, INPUT);
  pinMode(ch6_pin, INPUT);

  pinMode(out1_pin, OUTPUT);
  pinMode(out2_pin, OUTPUT);
  pinMode(out3_pin, OUTPUT);
  pinMode(out4_pin, OUTPUT);
  pinMode(out5_pin, OUTPUT);
  pinMode(out6_pin, OUTPUT);
}

void loop() {
  //PWM
  ch1 = pulseIn(ch1_pin, HIGH, 27000); //micro sec
  ch1 = (ch1 < 1000) ? 1000 : ch1;
  ch1 = (ch1 > 2000) ? 2000 : ch1;
  analogWrite(out1_pin, map(ch1, 1000, 2000, 0, 255));

  ch2 = pulseIn(ch2_pin, HIGH, 27000); //micro sec
  ch2 = (ch2 < 1000) ? 1000 : ch2;
  ch2 = (ch2 > 2000) ? 2000 : ch2;
  analogWrite(out2_pin, map(ch2, 1000, 2000, 0, 255));

  ch3 = pulseIn(ch3_pin, HIGH, 27000); //micro sec
  ch3 = (ch3 < 1000) ? 1000 : ch3;
  ch3 = (ch3 > 2000) ? 2000 : ch3;
  analogWrite(out3_pin, map(ch3, 1000, 2000, 0, 255));

  //switch
  ch4 = pulseIn(ch4_pin, HIGH, 27000);
  if (ch4 > 1700) {
    digitalWrite(out4_pin, 1);
  }
  else {
    digitalWrite(out4_pin, 0);
  }

  ch5 = pulseIn(ch5_pin, HIGH, 27000);
  if (ch5 > 1700) {
    digitalWrite(out5_pin, 1);
  }
  else {
    digitalWrite(out5_pin, 0);
  }

  ch6 = pulseIn(ch6_pin, HIGH, 27000);
  if (ch6 > 1700) {
    digitalWrite(out6_pin, 1);
  }
  else {
    digitalWrite(out6_pin, 0);
  }

}



