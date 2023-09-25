#define THERMISTORPIN1 A0
#define THERMISTORNOMINAL 100000 // temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25 // how many samples to take and average, more takes longer
#define NUMSAMPLES 50 // The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
#define SERIESRESISTOR 4700
float samples[NUMSAMPLES];
float F;
char _buffer[150];


void setup(){
  Serial.begin(115200);
  analogReference(EXTERNAL);
}
void loop(){
  uint8_t i;
    float average;
    for (i=0; i< NUMSAMPLES; i++) {
      samples[i] = analogRead(THERMISTORPIN1);
      delay(10);
    }
    average = 0;
    for (i=0; i< NUMSAMPLES; i++) {
      average += samples[i];
    }
    average /= NUMSAMPLES;
    average = 1023 / average - 1;
    average = SERIESRESISTOR / average;
    float steinhart;
    steinhart = average / THERMISTORNOMINAL; 
    steinhart = log(steinhart);
    steinhart /= BCOEFFICIENT;
    steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);
    steinhart = 1.0 / steinhart;
    steinhart -= 273.15;
    F = ((steinhart * 9/5) + 32);
    Serial.print("  *C  ");
    Serial.println(steinhart);
    Serial.print("  *F  ");
    Serial.println(F);
}
