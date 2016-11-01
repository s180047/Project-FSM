// Statemachine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"

int Example = 0;
int Humidity = 100;
int Heat = 50;
int Wind = 30;
bool Tru = true;
int Number = 5;

void Rain() {
	Humidity = Humidity + 10;
	Heat = Heat + 2;
	Wind = Wind + 4;
}

void Sunny() {
	Humidity = Humidity - 10;
	Heat = Heat + 5;
	Wind = Wind + 3;
}

void Cloudy() {
	Humidity = Humidity + 10;
	Heat = Heat + 2;
	Wind = Wind + 4;
}

void Weather() {
	if (Humidity > 200) { Humidity = 10; }
	if (Heat > 200) { Heat = 5; }
	if (Wind > 200) { Wind = 3; }

	if (Humidity >= 10 && Wind >=4 && Heat <=2) {
		Example = 0;
	}
	else if (Heat >= 5 && Humidity <= 10 && Wind <=3) {
		Example = 1;
	}
	else if (Humidity >= 10 && Heat >= 2 && Wind >=4) {
		Example = 2;
	}

	else { Example = 3; }

	switch (Example) {
	case 0: {
		Rain();
		printf("It is raining! When would it stop?!");
		break;
	}
	case 1: {
		Sunny();
		printf("It is sunny! I wish there was a bit of wind!");
		break;
	}
	case 2: {
		Cloudy();
		printf("It is cloudy! The rain is comming!");
		break;
	}
	case 3: {
		Humidity = 10;
		Heat = 5;
		Wind = 3;
		printf("Variables were too low, reset to initial values.");
		break;
	}

	}

}
int main()
{
	while (1 + 1 == 2) {
		Weather();
		printf("\n\r Humidity is %u, Heat is %u, Wind is %u, State is %u \n\r", Humidity, Heat, Wind, Example);
		Sleep(1000);
	}
	return 0;
}
