#pragma once
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define X 21
#define Y 41

int gameStatus = 1;
int refreshRate = 100;  //one refresh at 100 ms
int spawnRate = 1;  // 1 = 1/10  2 = 2/10  3 = 3/10  ...
int redRate = 6;  // 6 = 1/6   7 = 2/7   8 = 3/8 ... 

struct flake {
	int x;
	int y;
	int color;
}flakes[X][Y];

void setFlake(char matrix[][Y]) {
	int nr = rand() % 10;
	if (nr < spawnRate) {
		int color = rand() % redRate;
		int pozY = rand() % Y;
		if (color > 5) color = 0;
		matrix[0][pozY] = '*';
		flakes[0][pozY].x = 0;
		flakes[0][pozY].y = pozY;
		flakes[0][pozY].color = color;
	}
}

void moveFlakes(char matrix[][Y]) {
	for (int i = 0; i < Y; i++) { //41
		for (int j = 0; j < X; j++) { //21
			if (matrix[j][i] == '*') {
				matrix[j][i] = ' ';
				flakes[j + 1][i].color = flakes[j][i].color;
				flakes[j][i].x = 0;
				flakes[j][i].y = 0;

				matrix[j + 1][i] = '*';
				flakes[j + 1][i].x = j;
				flakes[j + 1][i].y = i;

				j = j + 1;
			}

		}
	}
}

void movePlayer(char matrix[][Y], int playerCenterPoz) {
	int direction = playerCenterPoz - (Y / 2);
	
	matrix[X - 1][(Y / 2) + direction] = '_';
	matrix[X - 1][(Y / 2) + 1 + direction] = '/';
	matrix[X - 1][(Y / 2) - 1 + direction] = '\\\\';
}

void setColor(int x, int y) {
	char* colors[16] = { "[0;31m", "[0;32m", "[0;33m", "[1;34m", "[1;35m", "[1;36m"};
	//                      red      green    yellow     blue     magenta    cyan      
	int color = flakes[x][y].color;
	printf("\033%s", colors[color]);
}

void setScore(char matrix[][Y], int playerCenterPoz, int *lives, int* d3, int* d2, int* d1) {
	int direction = playerCenterPoz - (Y / 2);

	if (matrix[X - 2][(Y / 2) + direction] == '*') {
		int color = flakes[X - 2][(Y / 2) + direction].color;
		switch (color) {
		case 0: *lives = *lives - 1; break;
		case 1: *d1 += 5; break;
		case 2: *d2 += 1; break;
		case 3: *d2 += 2; break;
		case 4: *d2 += 5; break;
		case 5: *d3 += 1; break;
		}
	}

	if (matrix[X - 2][(Y / 2) + 1 + direction] == '*') {
		int color = flakes[X - 2][(Y / 2) + 1 + direction].color;
		switch (color) {
		case 0: *lives = *lives - 1; break;
		case 1: *d1 += 5; break;
		case 2: *d2 += 1; break;
		case 3: *d2 += 2; break;
		case 4: *d2 += 5; break;
		case 5: *d3 += 1; break;
		}
	}

	if (matrix[X - 2][(Y / 2) - 1 + direction] == '*') {
		int color = flakes[X - 2][(Y / 2) - 1 + direction].color;
		switch (color) {
		case 0: *lives = *lives - 1; break;
		case 1: *d1 += 5; break;
		case 2: *d2 += 1; break;
		case 3: *d2 += 2; break;
		case 4: *d2 += 5; break;
		case 5: *d3 += 1; break;
		}
	}
}

void scorUpdate(int* d5, int* d4, int* d3, int* d2, int* d1) {
	if (*d1 > 9) {
		*d2 += 1;
		*d1 = *d1 % 10;
	}
	if (*d2 > 9) {
		*d3 += 1;
		*d2 = *d2 % 10;
	}
	if (*d3 > 9) {
		*d4 += 1;
		*d3 = *d3 % 10;
	}
	if (*d4 > 9) {
		*d5 += 1;
		*d4 = *d4 % 10;
	}
}

void increaseDifficulty(int d5, int d4, int d3, int d2, int d1) {
	static int activated = 0;

	if (gameStatus == 0) activated = 0;
	
	//40
	if (d2 >= 4 && activated == 0) {
		spawnRate++;
		redRate++;
		activated++;
	}
	//100
	if (d3 >= 1 && activated == 1) {
		spawnRate++;
		redRate++;
		activated++;
	}
	//200
	if (d3 >= 2 && activated == 2) {
		spawnRate++;
		redRate++;
		activated++;
	}
	//300
	if (d3 >= 3 && activated == 3) {
		spawnRate++;
		redRate++;
		activated++;
	}
	//500
	if (d3 >= 5 && activated == 4) {
		spawnRate++;
		redRate++;
		activated++;
	}
	//1000
	if (d4 == 1  && activated == 5) {
		spawnRate++;
		redRate++;
		activated++;
	}
	//1500
	if (d4 == 1 && d3 >= 5 && activated == 6) {
		spawnRate++;
		redRate++;
		activated++;
		refreshRate = refreshRate - 10;
	}
	//2000
	if (d4 == 2 && activated == 7) {
		spawnRate++;
		redRate++;
		activated++;
		refreshRate = refreshRate - 10;
	}
	//2500
	if (d4 == 2 && d3 >= 5 && activated == 8) {
		spawnRate++;
		redRate++;
		activated++;
		refreshRate = refreshRate - 10;
	}
	//3000
	if (d4 == 3 && activated == 9) {
		spawnRate++;
		redRate++;
		activated++;
		refreshRate = refreshRate - 20;
	}

}

void clearLastPlayerPoz(char matrix[][Y]) {
	for (int i = 0; i < Y; i++) {
		matrix[X - 1][i] = ' ';
	}
}

void updateSecondaryScore(char matrix[][Y], int playerCenterPoz, int *sd3, int *sd2, int *sd1) {
	int direction = playerCenterPoz - (Y / 2);
	static counter = 0, d3 = 0, d2 = 0, d1 = 0;

	if (d3 == *sd3 && d2 == *sd2 && d1 == *sd1 && (counter == 1 || counter == 2 || counter == 3)) {counter++;}
	else {
		*sd3 = 0;
		*sd2 = 0;
		*sd1 = 0;
		counter = 0;
	}

	if (matrix[X - 2][(Y / 2) + direction] == '*') {
		int color = flakes[X - 2][(Y / 2) + direction].color;
		switch (color) {
		case 1: *sd1 += 5; break;
		case 2: *sd2 += 1; break;
		case 3: *sd2 += 2; break;
		case 4: *sd2 += 5; break;
		case 5: *sd3 += 1; break;
		}
	}

	if (matrix[X - 2][(Y / 2) + 1 + direction] == '*') {
		int color = flakes[X - 2][(Y / 2) + 1 + direction].color;
		switch (color) {
		case 1: *sd1 += 5; break;
		case 2: *sd2 += 1; break;
		case 3: *sd2 += 2; break;
		case 4: *sd2 += 5; break;
		case 5: *sd3 += 1; break;
		}
	}

	if (matrix[X - 2][(Y / 2) - 1 + direction] == '*') {
		int color = flakes[X - 2][(Y / 2) - 1 + direction].color;
		switch (color) {
		case 1: *sd1 += 5; break;
		case 2: *sd2 += 1; break;
		case 3: *sd2 += 2; break;
		case 4: *sd2 += 5; break;
		case 5: *sd3 += 1; break;
		}
	}

	if (*sd1 > 9) {
		*sd2 += 1;
		*sd1 = *sd1 % 10;
	}
	if (*sd2 > 9) {
		*sd3 += 1;
		*sd2 = *sd2 % 10;
	}

	if (d3 != *sd3 || d2 != *sd2 || d1 != *sd1) {
		counter = 1;
		d3 = *sd3;
		d2 = *sd2;
		d1 = *sd1;
	}

}

void printScore(int d5, int d4, int d3, int d2, int d1, int sd3, int sd2, int sd1, int lives) {
	static int life = 3;
	if (sd1 != 0 || sd2 != 0 || sd3 != 0 && life == lives)
		printf("SCORE: %d%d%d%d%d       \033[0;32m +%d%d%d \033[0m        LIVES: %d", d5, d4, d3, d2, d1, sd3, sd2, sd1, lives);
	else if (life != lives) {
		printf("SCORE: %d%d%d%d%d       \033[0;31m  -1   \033[0m       LIVES: %d", d5, d4, d3, d2, d1, lives);
		life = lives;
	}
	else if(sd1 == 0 && sd2 == 0 && sd3 == 0)
		printf("SCORE: %d%d%d%d%d                     LIVES: %d", d5, d4, d3, d2, d1, lives);


}

void playGame() {
	gameStatus = 1;
	refreshRate = 100;
	spawnRate = 1;
	redRate = 6;

	char matrix[X][Y];
	int playerCenterPoz = 20;
	int d5 = 0, d4 = 0, d3 = 0, d2 = 0, d1 = 0;
	int sd3 = 0, sd2 = 0, sd1 = 0;
	int lives = 3;
	srand(time(0));


	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			matrix[i][j] = ' ';
		}
	}

	
	while (gameStatus) {
		system("cls");

		scorUpdate(&d5, &d4, &d3, &d2, &d1);
		printScore(d5, d4, d3, d2, d1, sd3, sd2, sd1, lives);

		setFlake(matrix);
		setScore(matrix, playerCenterPoz, &lives, &d3, &d2, &d1);
		updateSecondaryScore(matrix, playerCenterPoz, &sd3, &sd2, &sd1);
		moveFlakes(matrix);
		movePlayer(matrix, playerCenterPoz);
		increaseDifficulty(d5, d4, d3, d2, d1);

		//afisare matrice
		for (int i = 0; i < X; i++) {
			for (int j = 0; j < Y; j++) {
				if (matrix[i][j] == ' ') {
					printf("%c", matrix[i][j]);
				}
				else if(matrix[i][j] == '*') {
					setColor(i, j);
					printf("%c", matrix[i][j]);
					printf("\033[0m");
				}
				else
					printf("%c", matrix[i][j]);
			}
		}

		clearLastPlayerPoz(matrix);
		
		//inregistrare apasare taste
		while (kbhit()) {
			int key = getch();
			switch (key) {
			case 75: playerCenterPoz = playerCenterPoz - 2; if (playerCenterPoz < 1) playerCenterPoz = 1; break; //left arrow
			case 77: playerCenterPoz = playerCenterPoz + 2; if (playerCenterPoz > 39) playerCenterPoz = 39;  break; //right arrow
			case 27: return; //esc
			}
		}

		if (lives == 0) gameStatus = 0;

		Sleep(refreshRate);
	}
	system("cls");

	increaseDifficulty(d5, d4, d3, d2, d1); 

	printf("\n\n\n\n\n\n\n\n\n\n               GAME OVER                 ");
	scorUpdate(&d5, &d4, &d3, &d2, &d1);
	printf("                 %d%d%d%d%d     \n\n\n\n", d5, d4, d3, d2, d1);
	printf("          Press enter to exit     ");
	while (getch() != 13) {}

}

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}