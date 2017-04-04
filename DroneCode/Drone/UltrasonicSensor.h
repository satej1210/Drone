#ifndef UltrasonicSensor
//UStrig# = Ultrasonic sensor trigger pin #x
#define US_Trig_0 23
#define US_Trig_1 25
#define US_Trig_2 27
#define US_Trig_3 29
#define US_Trig_4 31
#define US_Trig_5 33

#define US_Echo_0 22
#define US_Echo_1 24
#define US_Echo_2 26
#define US_Echo_3 28
#define US_Echo_4 30
#define US_Echo_5 32

long distance[] = { 0, 0, 0, 0, 0, 0 };

int X = 0;
int Y = 0;
int Z = 0;

long duration;

void USSetup(){
  pinMode(US_Trig_0, OUTPUT);
pinMode(US_Trig_1, OUTPUT);
pinMode(US_Trig_2, OUTPUT);
pinMode(US_Trig_3, OUTPUT);
pinMode(US_Trig_4, OUTPUT);
pinMode(US_Trig_5, OUTPUT);

pinMode(US_Echo_0, INPUT);
pinMode(US_Echo_1, INPUT);
pinMode(US_Echo_2, INPUT);
pinMode(US_Echo_3, INPUT);
pinMode(US_Echo_4, INPUT);
pinMode(US_Echo_5, INPUT);
}
long distanceInCentimeters(int trigPin, int echoPin)
{
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH, 10000);
	return (duration / 2) / 29.1;

}
void readDistances() {
	distance[0] = distanceInCentimeters(US_Trig_0, US_Echo_0);
	distance[1] = distanceInCentimeters(US_Trig_1, US_Echo_1);
	distance[2] = distanceInCentimeters(US_Trig_2, US_Echo_2);
	distance[3] = distanceInCentimeters(US_Trig_3, US_Echo_3);
	distance[4] = distanceInCentimeters(US_Trig_4, US_Echo_4);
	distance[5] = distanceInCentimeters(US_Trig_5, US_Echo_5);
	for (int i = 0; i < 6; i++) {
    char test[20];
    String x = "\"US";
    x += i;
    x += "\": ";
    x += floatToString(test, float(distance[i]), 1, 5);
    //Serial.println(distance[i]);
    appendSerialData(x);
	}
}


#endif
