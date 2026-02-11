// hw_timer_t *timer = NULL;
// int a = 0;
// int b = 0;

// void IRAM_ATTR onTimer(){
//   b++;
// }
// void setup() {
//   Serial.begin(9600);
//   timer = timerBegin(1000000);
//   timerAttachInterrupt(timer, &onTimer);
//   timerAlarm(timer, 3250000, true, 0);

// }

// void loop() {
//   a++;
//   Serial.println("a: " + String(a));
//   Serial.println("b: " + String(b));
// }

hw_timer_t *timer = NULL; 
int led = 23;
int seg = 1000;
volatile bool blink = false;
volatile int freq = 0;
volatile int f = 1000;
volatile int count = 0;

// ta em milissegundo

void IRAM_ATTR onTimer() {
  count++;   // 5000
  freq++;    // 200

  if (count >= 5000) {
    if (f == 1000){
      f = 200;
    }
    else{
      f = 1000;
    }
    count = 0;
  }

  if (freq >= f){
    blink = true;
    freq = 0;
  }
}


void setup(){
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, seg, true, 0);
}

void loop(){
  if(blink){
    digitalWrite(led, !digitalRead(led));
    blink = false;
  }
  Serial.println("Frequência: " + String(f) + "hz");
  Serial.println("Segundos: " + String(count) + "s");
}