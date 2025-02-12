// Fractals.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "LTimer.h"


#include <vector>
//#include <algorithm>


#define P1_KEY_MOVEUP SDLK_z
#define P1_KEY_MOVEDOWN SDLK_s
#define P2_KEY_MOVEUP SDLK_UP
#define P2_KEY_MOVEDOWN SDLK_DOWN

#define MAX_SCORE 10

extern const int SCREEN_WIDTH = 1920;
extern const int SCREEN_HEIGHT = 1080;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

struct Couple {
	Couple(int xPos, int yPos) : x(xPos), y(yPos) {}
	int x;
	int y;
};

std::vector<Couple> pixels;
int size = 0;

//Key press surfaces constants
enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;


	//Load Shrock ball
	/*if (!gShrockBall.loadFromFile("G:/Images/shrock.png", gRenderer))
	{
		printf("Unable to load ShrockBall!\n");
		success = false;
	}

	//Load Shrock bar
	if (!gShrockBar.loadFromFile("G:/Images/shrockbar.png", gRenderer))
	{
		printf("Unable to load ShrockBar!\n");
		success = false;
	}*/

	return success;
}

void close()
{
	//Deallocate surface

	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int newXCenter = 0;
int newYCenter = 0;

void fractal(int xCenter, int yCenter) {
	int newSize = size;

	for (std::vector<Couple>::size_type i = 0; i < size; ++i)
	{
		if (i == 0) {
			newXCenter = xCenter + yCenter - pixels[i].y;
			newYCenter = yCenter - xCenter + pixels[i].x;
		}

		//std::cout << "x: " << pixels[i].x << " y: " << pixels[i].y << std::endl;
		SDL_RenderDrawPoint(gRenderer, pixels[i].x, pixels[i].y);
		SDL_RenderPresent(gRenderer);
		pixels.push_back(Couple(xCenter + yCenter - pixels[i].y, yCenter - xCenter + pixels[i].x));
		++newSize;
	}

	//std::cout << "/////////////////" << std::endl;
	size = newSize;
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{


			/******************************/
			/***********  LOOP  ***********/
			/******************************/

			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The frames per second timer
			LTimer fpsTimer;

			//The frames per second cap timer
			LTimer capTimer;

			//Start counting frames per second
			int countedFrames = 0;
			fpsTimer.start();


			//INIT FRACTALS
			/*
			pixels.push_back(Couple((SCREEN_WIDTH / 2) - 1, (SCREEN_HEIGHT / 2) + 1));
			pixels.push_back(Couple((SCREEN_WIDTH / 2) - 1, (SCREEN_HEIGHT / 2)));
			pixels.push_back(Couple(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2)));
			pixels.push_back(Couple((SCREEN_WIDTH / 2) + 1, (SCREEN_HEIGHT / 2)));
			pixels.push_back(Couple((SCREEN_WIDTH / 2) + 1, (SCREEN_HEIGHT / 2) + 1));
			
			size = 5;
			*/

			/*
			pixels.push_back(Couple((SCREEN_WIDTH / 2) - 1, (SCREEN_HEIGHT / 2) + 1));
			pixels.push_back(Couple(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2)));
			pixels.push_back(Couple((SCREEN_WIDTH / 2) + 1, (SCREEN_HEIGHT / 2) + 1));
			pixels.push_back(Couple((SCREEN_WIDTH / 2) + 2, (SCREEN_HEIGHT / 2) + 2));
			pixels.push_back(Couple((SCREEN_WIDTH / 2) + 3, (SCREEN_HEIGHT / 2) + 3));

			size = 5;
			*/
			
			
			pixels.push_back(Couple((SCREEN_WIDTH / 2) - 3, (SCREEN_HEIGHT / 2) + 3));
			pixels.push_back(Couple((SCREEN_WIDTH / 2) - 2, (SCREEN_HEIGHT / 2) + 2));
			pixels.push_back(Couple((SCREEN_WIDTH / 2) - 1, (SCREEN_HEIGHT / 2) + 1));
			pixels.push_back(Couple(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2)));
			pixels.push_back(Couple((SCREEN_WIDTH / 2) + 1, (SCREEN_HEIGHT / 2) + 1));
			pixels.push_back(Couple((SCREEN_WIDTH / 2) + 2, (SCREEN_HEIGHT / 2) + 2));


			pixels.push_back(Couple((SCREEN_WIDTH / 2) - 2, (SCREEN_HEIGHT / 2) + 3));
			pixels.push_back(Couple((SCREEN_WIDTH / 2) - 1, (SCREEN_HEIGHT / 2) + 3));
			pixels.push_back(Couple((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 3));			
			pixels.push_back(Couple((SCREEN_WIDTH / 2) + 1, (SCREEN_HEIGHT / 2) + 3));
			pixels.push_back(Couple((SCREEN_WIDTH / 2) + 2, (SCREEN_HEIGHT / 2) + 3));
			pixels.push_back(Couple((SCREEN_WIDTH / 2) + 3, (SCREEN_HEIGHT / 2) + 3));
			
			size = 12;
			newXCenter = pixels[size - 1].x;
			newYCenter = pixels[size - 1].y;
			


			//While application is running
			while (!quit) {

				//Start cap timer
				capTimer.start();

				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					//User presses a key
					else if (e.type == SDL_KEYDOWN)
					{
						//Select surfaces based on key press
						switch (e.key.keysym.sym)
						{
						case P1_KEY_MOVEUP:
							break;

						case P1_KEY_MOVEDOWN:
							break;

						case P2_KEY_MOVEUP:
							break;

						case P2_KEY_MOVEDOWN:
							break;

						case SDLK_SPACE:
							break;

						default:
							// nothing
							break;
						}
					}
					if (e.type == SDL_KEYUP)
					{
						//Select surfaces based on key press
						switch (e.key.keysym.sym)
						{
						case P1_KEY_MOVEUP:
							break;

						case P1_KEY_MOVEDOWN:
							break;

						case P2_KEY_MOVEUP:
							break;

						case P2_KEY_MOVEDOWN:
							break;

						default:
							// nothing
							break;
						}
					}
				}

				//Calculate and correct fps
				float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
				if (avgFPS > 2000000)
				{
					avgFPS = 0;
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				//SDL_RenderClear(gRenderer);

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0, 0, 0xFF);
				fractal(newXCenter, newYCenter);
				//SDL_RenderDrawPoint(gRenderer, 1000, 300);

				//gShrockBar.render(0, 0, 0.5f, 0.5f, gRenderer);
				//gShrockBar.render(SCREEN_WIDTH - (gShrockBar.getWidth() * 0.5f), 0, 0.5f, 0.5f, gRenderer);

				//Render red filled quad
				/*SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderDrawRect(gRenderer, &fillRect);*/

				//Update screen
				SDL_RenderPresent(gRenderer);

				++countedFrames;

				//If frame finished early
				int frameTicks = capTimer.getTicks();
				if (frameTicks < SCREEN_TICKS_PER_FRAME)
				{
					//Wait remaining time
					SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
				}
			}


		}
	}

	//Free resources and close SDL
	close();

	return 0;
}