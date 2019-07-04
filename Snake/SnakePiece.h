// Snake piece is a rectangle of the snake
// Stores the position, and a pointer to the previous pice
class SnakePiece {
	int posX, posY;
	SnakePiece* prev;

public:
	// Constructor, setting the position
	SnakePiece(int x, int y) : posX(x), posY(y) {

	}

	SnakePiece* getPrev() { return prev; }
	void setPrev(SnakePiece* sp) { prev = sp; }

	// Checks if the piece is in the same positon as the given piece
	bool collision(SnakePiece* which) { return posX == which->posX && posY == which->posY; }

	// Checks if the piece is off map
	bool offMap() { return posX == -1 || posX == 15 || posY == -1 || posY == 15; }

	// Changes the position to the previous pice
	void setPosToPrev() { posX = prev->posX; posY = prev->posY; }

	// Moves the piece to the given direction
	void moveToDir(char dir) {
		switch (dir) {
		case 'u':
			posY--;
			break;
		case 'd':
			posY++;
			break;
		case 'l':
			posX--;
			break;
		case 'r':
			posX++;
			break;
		}
	}

	int getX() { return posX; }
	int getY() { return posY; }

	// Setting the posion the the given numbers
	void setPos(int x, int y) { posX = x; posY = y; }

	// Checks, if the piece collisions with one of the pieces
	bool collisionWithOneOfAll(SnakePiece* tail) {
		// Goes throught all the pieces
		while (tail != NULL) {
			if (collision(tail))
				return true;
			// Move back on the pieces
			tail = tail->prev;
		}
		return false;
	}
};