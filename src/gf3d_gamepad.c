#pragma once
#include <gf3d_gamepad.h>
#include "simple_logger.h"

SDL_GameController *Xbonks = NULL;
const int DEAD_ZONE = 8000;


void gamepad_start() {
	//slog("hello?");

	if (SDL_NumJoysticks() < 1) {
		slog("No controllers plugged in");
		return;
	}
	else {
		//Xbonks = SDL_JoystickOpen(0);
		Xbonks = SDL_GameControllerOpen(0);
		if (Xbonks == NULL) {
			slog("Unable to open controller");
			return;
		}
		slog("Controller ready to roll!");
		atexit(SDL_GameControllerClose);
	}
}

void gamepad_checker(SDL_Event eventer) {
	if (SDL_PollEvent(&eventer) != 0) {
		if (eventer.type == SDL_CONTROLLERDEVICEREMOVED) {
			Xbonks = SDL_GameControllerFromInstanceID(eventer.cdevice.which);
			SDL_GameControllerClose(Xbonks);
			slog("Unplugged....");
		}
		else if (eventer.type == SDL_CONTROLLERDEVICEADDED) {
			Xbonks = SDL_GameControllerOpen(eventer.cdevice.which);
			slog("Back in the game again!");
			
		}
	}
}

void gamepad_controls(SDL_Event eventer) {
	if (SDL_PollEvent(&eventer) != 0) {
		
		if (eventer.type == SDL_CONTROLLERAXISMOTION) {
			if (eventer.caxis.which == 0) {
				//Left and right axies
				if (eventer.caxis.axis == 0) {
					//Left of dead zone
					if (eventer.caxis.value < -DEAD_ZONE)
					{
						slog("Moving left");
					}
					//Right of dead zone
					else if (eventer.caxis.value > DEAD_ZONE)
					{
						slog("Moving right");
					}
				//Up and down axies
				}
				else if (eventer.caxis.axis == 1) {
					if (eventer.caxis.value < -DEAD_ZONE)
					{
						slog("Moving Up");
					}
					
					else if (eventer.caxis.value > DEAD_ZONE)
					{
						slog("Moving Down");
					}
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
		}else if (eventer.cbutton.state == SDL_RELEASED) {
			switch (eventer.cbutton.button) {

				case SDL_CONTROLLER_BUTTON_A:
					slog("A button released");
					break;
				case SDL_CONTROLLER_BUTTON_B:
					slog("B button released");
					break;
				case SDL_CONTROLLER_BUTTON_X:
					slog("X button released");
					break;
				case SDL_CONTROLLER_BUTTON_Y:
					slog("Y button released");
					break;
				default:
					slog("Button released");
					break;

			}
		}


	}
}