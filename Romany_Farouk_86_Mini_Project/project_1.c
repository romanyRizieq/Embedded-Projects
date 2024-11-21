/*
 * project_1.c
 *
 *  Created on: 19 Apr 2024
 *      Author: Romany Farouk
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1 /* Set to 1 to include engine

/* functions decalerations */
char displayMenuInput();
void SensorReadings(char input2, int *vehicleSpeed, int *roomTemp, int *ac,
		int *engineTemp, int *engineTempControllerState, int *engineState);
void displayVehicleState(int engineState, int acState, int vehicleSpeed,
		int roomTemp, int engineTempControllerState, int engineTemp);
///////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
	struct eng {
		int engineState;
		int acState;
		int vehicleSpeed;
		int roomTemp;
		int engineTempControllerState;
		int engineTemp;
	} engine = { }; //Initial Value =0 due to Engine State is OFF//
//	engine.acState = 0, engine.engineState = 0, engine.engineTemp = 0, engine.engineTempControllerState =
//			0,  engine.vehicleSpeed = 0;
	engine.roomTemp = 15;
	char input = 'm', input2 = 'm';

	while (input != 'c') {
		input = displayMenuInput();
		switch (input) {
		case 'a': // Turn on the vehicle engine
			engine.engineState = 1;
			printf("Sensors set menu:\n");
			puts(
					"a. Turn off the engine\n"
							"b. Set the traffic light color\n"
							"c. Set the room temperature (Temperature Sensor)\n"
							"d. Set the engine temperature (Engine Temperature Sensor)\n");
			fflush(stdout);
			scanf(" %c", &input2);
			SensorReadings(input2, &engine.vehicleSpeed, &engine.roomTemp,
					&engine.acState, &engine.engineTemp,
					&engine.engineTempControllerState, &engine.engineState);
			displayVehicleState(engine.engineState, engine.acState,
					engine.vehicleSpeed, engine.roomTemp,
					engine.engineTempControllerState, engine.engineTemp);
			break;
		case 'b': // Turn off the vehicle engine
//			struct eng engine = { };
			engine.engineState = 0, engine.engineTempControllerState = 0, engine.acState =
					0, engine.vehicleSpeed = 0;
			displayVehicleState(engine.engineState, engine.acState,
					engine.vehicleSpeed, engine.roomTemp,
					engine.engineTempControllerState, engine.engineTemp);
			break;
		}
	}
	if (input == 'c') {
		printf("Quitting the system.\n");
		return 0;
		// Display current vehicle state
		displayVehicleState(engine.engineState, engine.acState,
				engine.vehicleSpeed, engine.roomTemp,
				engine.engineTempControllerState, engine.engineTemp);
		input = displayMenuInput();

	}

	return 0;
}

/* functions defnations */

/* Function to display the menu and get user input */
char displayMenuInput() {
	char input;
	puts("please Enter your Request: ");
	puts("a. Turn on the vehicle engine\n"
			"b. Turn off the vehicle engine\n"
			"c. Quit the system \n");
	fflush(stdout);
	scanf(" %c", &input);
	return input;
}

/* Function to  sensor readings and set vehicle parameters */
void SensorReadings(char input2, int *vehicleSpeed, int *roomTemp, int *ac,
		int *engineTemp, int *engineTempControllerState, int *engineState) {
	char trafficLight;
	int room, engine;
	switch (input2) {
	case 'a': // Turn off the vehicle engine
		*engineState = 0, *engineTempControllerState = 0, *ac = 0, *vehicleSpeed =
				0;
		break;
	case 'b':
		printf("Enter traffic light color (G/O/R): ");
		fflush(stdout);
		scanf(" %c", &trafficLight);
		if (trafficLight == 'G' || trafficLight == 'g') {
			*vehicleSpeed = 100;
		} else if (trafficLight == 'O' || trafficLight == 'o') {
			*vehicleSpeed = 30;
		} else if (trafficLight == 'R' || trafficLight == 'r') {
			*vehicleSpeed = 0;
		}
		break;
	case 'c':
		printf("Enter room temperature: ");
		fflush(stdout);
		scanf(" %d", &room);
		if (room < 10 || room > 30) {
			*ac = 1;
			*roomTemp = 20;
		} else {
			*ac = 0;
			*roomTemp = room;
		}
		break;

	case 'd':
		printf("Enter engine temperature: ");
		fflush(stdout);
		scanf(" %d", &engine);
		if (engine < 100 || engine > 150) {
			*engineTempControllerState = 1;
			*engineTemp = 125;
		} else {
			*engineTempControllerState = 0;
			*engineTemp = engine;
		}
		break;
	}
}

/* Function to display current vehicle state */
void displayVehicleState(int engineState, int acState, int vehicleSpeed,
		int roomTemp, int engineTempControllerState, int engineTemp) {
	printf("\nCurrent Vehicle State:\n");
	printf("Engine state: %s\n", engineState ? "ON" : "OFF");
	printf("AC: %s\n", acState ? "ON" : "OFF");
	printf("Vehicle Speed: %d km/hr\n", vehicleSpeed);
	printf("Room Temperature: %d\n", roomTemp);
	printf("Engine Temperature Controller State: %s\n",
			engineTempControllerState ? "ON" : "OFF");
	printf("Engine Temperature: %d\n\n", engineTemp);
}
