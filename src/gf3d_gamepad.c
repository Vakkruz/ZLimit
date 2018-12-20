#pragma once
#include <gf3d_gamepad.h>
#include "simple_logger.h"

SDL_GameController *Xbonks;
const int DEAD_ZONE = 8000;
int deviceFound = 0;



void gamepad_start(SDL_JoystickID identifier) {
	//slog("hello?");

	if (SDL_NumJoysticks() < 1) {
		slog("No controllers plugged in");
		return;
	}
	else {
		//Xbonks = SDL_JoystickOpen(0);
		Xbonks = SDL_GameControllerOpen(identifier);
		if (Xbonks == NULL) {
			slog("Unable to open controller");
			return;
		}
		slog("Controller ready to roll!");
		atexit(SDL_GameControllerClose);
	}
}


/*
void gamepad_checker(SDL_Event eventer) {
	
	if (SDL_PollEvent(&eventer) != 0) {
	
		if (eventer.type == SDL_CONTROLLERDEVICEADDED && deviceFound == 0) {
			gamepad_start();
			deviceFound = 1;
			slog("Back in the game again!");
		}

		if (eventer.type == SDL_CONTROLLERDEVICEREMOVED) {
			slog("test 2");
			Xbonks = SDL_GameControllerFromInstanceID(eventer.cdevice.which);
			SDL_GameControllerClose(Xbonks);
			deviceFound = 0;
			slog("Unplugged....");
		}
			

	}
	
}
*/

void gamepad_controls(SDL_Event eventer) {
	
	if (SDL_PollEvent(&eventer) != 0) {
		
		if (eventer.type == SDL_JOYAXISMOTION) {
			//X axies

			if (eventer.caxis.axis == 0) {

				//Left of dead zone
				if (eventer.caxis.value < -DEAD_ZONE){
					slog("Moving left");
				}

				//Right of dead zone
				else if (eventer.caxis.value > DEAD_ZONE){
					slog("Moving right");
				}
				
			//Y axis
			}
			else if (eventer.caxis.axis == 1) {
				if (eventer.caxis.value < -DEAD_ZONE){
					slog("Moving Up");
				}
					
				else if (eventer.caxis.value > DEAD_ZONE){
					slog("Moving Down");
				}
			}
			
		}

		
		if (eventer.cbutton.state == SDL_PRESSED) {	
			switch (eventer.cbutton.button) {

				case SDL_CONTROLLER_BUTTON_A:
					slog("A button pressed");
					break;
				case SDL_CONTROLLER_BUTTON_B:
					slog("B button pressed");
					break;
				case SDL_CONTROLLER_BUTTON_X:
					slog("X button pressed");
					break;
				case SDL_CONTROLLER_BUTTON_Y:
					slog("Y button pressed");
					break;
				default:
					slog("Button pressed");
					break;
			}
		}
		
		if (eventer.type == SDL_JOYDEVICEADDED && deviceFound == 0) {
			//slog("hello?");
			gamepad_start(eventer.cdevice.which);
			deviceFound = 1;
			//slog("Back in the game again!");
		}

		if (eventer.type == SDL_JOYDEVICEREMOVED && deviceFound == 1) {
			SDL_GameControllerClose(Xbonks);
			Xbonks = NULL;
			deviceFound = 0;
			slog("Unplugged....");
		}

	}
}