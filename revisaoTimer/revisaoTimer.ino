hw_timer_t *timer = NULL;
int a = 0;
int b = 0;

void IRAM_ATTR onTimer(){
  b++;
}
void setup() {
  Serial.begin(9600);
  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 3250000, true, 0);
}

void loop() {
  a++;
  Serial.println("a: " + String(a));
  Serial.println("b: " + String(b));
}
