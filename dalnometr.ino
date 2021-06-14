//#include <DigiKeyboard.h>

#include <DNSServer.h>
#include <dummy.h>
int delayTime = 10 * 1000; //задержка для отключения в милисекундах
int distanceMax = 140; //Расстояние, на которое нужно подойти к датчику
int distanceMin = 30;//Минимальное расстояние, нужно чтобы не было пустых срабатываний при закрытой двери

long last; //время последнего срабатывания датчика
int treshCount = 0;
int treshCountToOn = 4; //Количество циклов по 100 мс для избежания шумов

int echoPin = 2;
int trigPin = 0;
int ledPin = 1;
void setup() {
	//DigiKeyboard.println("Start");
	pinMode(ledPin, OUTPUT);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	digitalWrite(ledPin, 0);
}
void loop() {
	int cm = getCm();
	if (cm < distanceMax && cm > distanceMin)
	{
		treshCount++;
		if (treshCount >= treshCountToOn) {
			digitalWrite(ledPin, 1);
			last = millis();
		}
	}
	else {
		treshCount = 0;
		if (millis() - last > delayTime || millis() < last) {
			digitalWrite(ledPin, 0);
		}
	}
	delay(100);
	/*DigiKeyboard.print(cm);
	DigiKeyboard.println(" cm");
	DigiKeyboard.print(last);
	DigiKeyboard.print(" ms; ");
	DigiKeyboard.print(millis());
	DigiKeyboard.println(" ms");
	DigiKeyboard.delay(1000); */
}

int getCm() {
	int duration, cm;
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	cm = duration / 58;
	return cm;
}
