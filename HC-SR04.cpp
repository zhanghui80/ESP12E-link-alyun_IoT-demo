#include "HCSR04.h"

int cm_length;


void Waves(void)
{
  float temp;
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  temp = float(pulseIn(ECHO, HIGH));
  cm_length = (temp * 17) / 1000;
  if(cm_length > 4000)
    cm_length = 4000;
}
