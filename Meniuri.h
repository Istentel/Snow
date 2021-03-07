#pragma once
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "Joc.h"
//22
//41

void info() {
	system("cls");
	printf("\033[0;31m");
	printf("*\033[0m = -1 life\n");

	printf("\033[0;32m");
	printf("*\033[0m = 5 points\n");

	printf("\033[0;33m");
	printf("*\033[0m = 10 points\n");

	printf("\033[1;34m");
	printf("*\033[0m = 20 points\n");

	printf("\033[1;35m");
	printf("*\033[0m = 50 points\n");

	printf("\033[1;36m");
	printf("*\033[0m = 100 points\n");

	printf("Difficulty increase after: 40-100-200-500-1000-1500-2000-2500-3000 points");

	getch();
}

void startMeniu() {
	char* meniu[3] = { "                PLAY GAME                ", "                   INFO                  ", "                   EXIT                  " };

	//"                PLAY GAME               "
	//"                 OPTIONS                "
	//"                  EXIT                  "

	int poz = 0;

	while (1) {
		system("cls");
		printf("\n\n\n\n\n\n\n");
		for (int i = 0; i < 3; i++) {
			if (i == poz) {
				printf("\033[0;31m");
				printf("%s", meniu[i]);
				printf("\033[0m");
			}
			else
				printf("%s", meniu[i]);

		}

		while (kbhit()) {
			int key = getch();
			if (key == 72) {
				poz--;
				if (poz < 0)
					poz = 2;
				break;
			}
			else if (key == 80) {
				poz++;
				if (poz > 2)
					poz = 0;
				break;
			}
			else if (key == 13) {
				switch (poz) {
				case 0: playGame(); break;
				case 1: info(); break;
				case 2: return;
				}
			}
		}
		Sleep(80);
	}

}

