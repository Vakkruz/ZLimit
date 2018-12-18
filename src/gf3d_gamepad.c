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
			if (eventer.jaxis.which == 0) {
				if (eventer.caxis.axis == 0) {
					//Left of dead zone
					if (eventer.jaxis.value < -DEAD_ZONE)
					{
						slog("Moving left");
					}
					//Right of dead zone
					else if (eventer.jaxis.value > DEAD_ZONE)
					{
						slog("Moving right");
					}
				}
			}
		}

	}
}