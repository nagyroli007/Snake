#include "SDL_MyWindow.hpp"
#include "SDL.h"
#undef main

#include "SnakePiece.h"

#include <stdlib.h>

int main() {

	SDL_MyWindow window(450, 450, "Snake");
	// Creaating a head, and a tail pice, so the snake has 2 pieces at the start
	SnakePiece* head = new SnakePiece(3, 7);
	head->setPrev(NULL);
	SnakePiece* tail = new SnakePiece(2, 7);
	tail->setPrev(head);

	SDL_Event ev;

	// Apple
	SnakePiece* apple = new SnakePiece(6, 6);

	bool end = false;
	char dir = 'n';

	// Infinite loop
	while (!end) {
		// Hanling imput
		while (SDL_PollEvent(&ev)) {
			// Quitting
			if (ev.type == SDL_QUIT)
				end = true;
			// Keypress
			if (ev.type == SDL_KEYDOWN) {
				switch (ev.key.keysym.sym) {
				// Left
				case SDLK_a:
					dir = 'l';
					break;
				// Left
				case SDLK_d:	
					dir = 'r';
					break;
				// Up
				case SDLK_w:
					dir = 'u';
					break;
				// Down
				case SDLK_s:
					dir = 'd';
					break;
				}
			}
		}

		window.clear();

		// New snake piece
		SnakePiece* newTail = NULL;

		// If the direction isn't none
		if (dir != 'n') {
			// Going through the pieces
			SnakePiece* moving = tail;
			while (moving->getPrev() != NULL) {
				// If the current piece collisions with the head, then the game ends
				if (moving->collision(head)) {
					end = true;
				}
				// Setting the position, and drawing the piece
				moving->setPosToPrev();
				window.drawPlayerPiece(moving->getX(), moving->getY());
				// Moving to the next piece
				moving = moving->getPrev();
			}
		}
		// Moving the head to the direction
		head->moveToDir(dir);
		// If the player goes off the map
		if (head->offMap())
			end = true;
		// If still in map, the the game hasn't ended, then draw the head
		else if (!end)
			window.drawPlayerPiece(head->getX(), head->getY());

		// If the head collisions with the apple
		if (head->collision(apple)) {
			// Create the new piece, to the tail
			newTail = new SnakePiece(tail->getX(), tail->getY());
			newTail->setPrev(tail);			// The new piece is the last

			// Placing a new apple to a random posiotion, which if empty
			int x = rand() % 15, y = rand() % 15;
			apple->setPos(x, y);
			while (apple->collisionWithOneOfAll(tail))
			{
				x = rand() % 15; y = rand() % 15;
				apple->setPos(x, y);
			}
		}
		window.drawApple(apple->getX(), apple->getY());

		// Drawing, and setting the new tail to tail
		if (newTail != NULL) {
			window.drawPlayerPiece(newTail->getX(), head->getY());
			tail = newTail;
		}
		window.present();

		SDL_Delay(150);
	}

	// Deleting the piecess
	SnakePiece* moving = tail;
	while (moving != NULL) {
		SnakePiece* next = moving->getPrev();
		delete moving;
		moving = next;
	}
	delete apple;

	return 0;
}