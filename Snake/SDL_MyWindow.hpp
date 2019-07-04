#include "SDL.h"

// Class, that handleds the window, rendering
class SDL_MyWindow{
	SDL_Window* window;
	SDL_Renderer* renderer;
	// Size of the window, and size of one block (one block is square)
	int width, height;
	int blockSize;

public:
	// MyWindow constructor
	// Makes the necessary steps, to create a window
	SDL_MyWindow(int w = 600, int h = 400, const char* title = "title"): width(w), height(h) {
		// Inicializing
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		// Clearing the window
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);	
		SDL_RenderPresent(renderer);
		// Setting the block size
		blockSize = 30;
	}

	// Destuctor
	// Destroying variables
	~SDL_MyWindow() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	}

	// Clearing the whole window with white color
	void clear() {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
	}

	// Drawing a player piece, a rectangle
	void drawPlayerPiece(int x, int y) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);		// Setting black color
		SDL_Rect r;											// Setting the rectangle, player piece
		r.x = x * blockSize + 2;
		r.y = y * blockSize + 2;
		r.w = blockSize - 4;
		r.h = blockSize - 4;
		SDL_RenderFillRect(renderer, &r);					// Putting the rectangle to the renderer
	}

	// Drawing an apple, similar to the player piece (a bit smaller, and there is a white rect in the middle)
	void drawApple(int x, int y) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_Rect r;
		r.x = x * blockSize + 4;
		r.y = y * blockSize + 4;
		r.w = blockSize - 8;
		r.h = r.w;
		SDL_RenderFillRect(renderer, &r);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		r.x += 2;
		r.y += 2;
		r.w -= 4;
		r.h = r.w;
		SDL_RenderFillRect(renderer, &r);
	}

	// Putting the renderer to the screen
	void present() {
		SDL_RenderPresent(renderer);
	}
};