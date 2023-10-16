#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <conio.h>
#include <Windows.h>


const int WIDTH = 25; // ширина  - - -  x
const int HEIGHT = 40; // высота | y

bool gameOver;

int snakeX = HEIGHT / 2;
int snakeY = WIDTH / 2;

int foodX = std::rand() % (HEIGHT - 4) + 2;
int foodY = std::rand() % (WIDTH - 4) + 2;

enum button_Log { STOP = 0, UP, DOWN, LEFT, RIGHT };
int dif = STOP;

int snake_lenght = 0;

int snake_tailX[1000];
int snake_tailY[1000];

int score{};

void Setup() {
	gameOver = false;
}

void Draw() {
	system("cls");

	for (int i = 0; i < WIDTH - 1; ++i) {
		for (int j = 0; j < HEIGHT - 1; ++j) {
			if (i == 0 || i == WIDTH - 2) {
				std::cout << "#";
			}
			else if (j == 0) {
				std::cout << "#";
			}
			else if (j == HEIGHT - 2) {
				std::cout << "#";
			}
			else if (i == snakeY && j == snakeX) {
				std::cout << "0";
			}
			else if (i == foodY && j == foodX) {
				std::cout << "*";
			}
			else {
				bool print = false;
				for (int k = 0; k < snake_lenght; ++k) {

					if (snake_tailX[k] == j && snake_tailY[k] == i) {
						print = true;
						std::cout << "o";
					}
				}
				if (!print)
					std::cout << " ";
			}
		}
		std::cout << "\n";
	}
	std::cout << "Score: " << score;
}

void Click() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			if (dif == DOWN) {
				break;
			}
			dif = UP;
			break;

		case 'd':
			if (dif == LEFT) {
				break;
			}
			dif = RIGHT;
			break;

		case 's':
			if (dif == UP) {
				break;
			}
			dif = DOWN;
			break;

		case 'a':
			if (dif == RIGHT) {
				break;
			}
			dif = LEFT;
			break;
		}
	}
}

void Logic() {

	if (snakeX == foodX && snakeY == foodY) {
		foodX = std::rand() % (HEIGHT - 4) + 2;
		foodY = std::rand() % (WIDTH - 4) + 2;
		snake_lenght++;
		score += 5;
	}

	int prevX = snake_tailX[0];
	int prevY = snake_tailY[0];
	int prev2X;
	int prev2Y;

	for (int i = 1; i < snake_lenght; ++i) {
		prev2X = snake_tailX[i];
		prev2Y = snake_tailY[i];
		snake_tailX[i] = prevX;
		snake_tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

		if (snakeX == snake_tailX[i] && snakeY == snake_tailY[i]) {
			gameOver = true;
		}
	}

	snake_tailX[0] = snakeX;
	snake_tailY[0] = snakeY;

	switch (dif) {
	case 1:
		snakeY--;
		break;
	case 2:
		snakeY++;
		break;
	case 3:
		snakeX--;
		break;
	case 4:
		snakeX++;
		break;
	}

	if (snakeX == HEIGHT - 2 || snakeY == WIDTH - 2 || snakeX == -1 || snakeY == -1) {
		gameOver = true;
	}
}

int main() {
	std::srand(std::time(NULL));

	int a = 5;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);

	Setup();

	while (!gameOver)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
		Draw();
		Click();
		Logic();
	}
	return 0;
}