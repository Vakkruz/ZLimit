#pragma once
#include <SDL.h>


/* CHECKS TO SEE IF GAMEPAD IS PLUGGED IN (AT STARTUP)*/
void gamepad_start();

/* CHECKS TO SEE IF GAMEPAD IS PLUGGED IN (DURING GAMEPLAY)*/
void gamepad_checker(SDL_Event *event);


