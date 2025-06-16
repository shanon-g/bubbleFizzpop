#include <stdio.h>
#include <stdlib.h>
#include <conio.h>				// For _getch() and _kbhit()
#include <time.h>
#include <ctype.h>
#include <windows.h>			// For Sleep();

void leave() {
	system("cls");
	printf("============================================\n");
    printf("Thank You for Playing! :D\n");
    printf("Made by: Shanon\n");
    printf("============================================\n");
    
    Sleep(3000);				// Exits after 3 seconds
    return;
}

void tutorial(int page) {
    system("cls");

    if (page == 1) {
        printf("                Page 1-3                D ->                    Enter : Exit Tutorial\n\n");
        printf("Welcome to Bubble FizzPop! Your mission is to clear the game board\n");
        printf("by strategically shooting balls to destroy designated targets.\n\n");
        printf("All you have to do is destroy the specified number of balls to win the game.\n");
        printf("Be strategic and efficient in your shots to survive!\n");
    } 
	else if (page == 2) {
        printf("<- A            Page 2-3                D ->                    Enter : Exit Tutorial\n\n");
        printf("Controls\n\n");
        printf(" -------\n");
        printf("1. Use A and D keys to move your aiming cursor.\n");
        printf("2. Press the spacebar to shoot a ball towards the targeted position.\n");
    } 
	else if (page == 3) {
        printf("<- A            Page 3-3                                        Enter : Exit Tutorial\n\n");
        printf("Gameplay\n\n");
        printf(" ---------------------\n");
        printf("1. Launch the game and observe the game board filled with various colored balls.\n");
        printf("2. Navigate your aiming cursor using the arrow keys to position it over the desired target.\n");
        printf("3. Press the spacebar to shoot a ball towards the selected location.\n");
        printf("4. The numbers on the ball represents the amount of shots needed for it to be destroyed\n");
        printf("5. A new wave of balls will emerge after some time\n");
    }
}

void howTo() {
    int page = 1;
    char input;

    tutorial(page);

    while (1) {
        input = _getch();
            
        if (input == 'd' && page < 3) {
            page++;
            tutorial(page);
        } 
		else if (input == 'a' && page > 1) {
            page--;
            tutorial(page);
        } 
		else if (input == '\r') break;
    }

    return;
}

int radius(int i, int posX, int totPoint, char map[][21]) {
	if (map[i][posX - 1] == '3') {					// LEFT
		map[i][posX - 1] = '2';
		totPoint += 2;
	}
	else if (map[i][posX - 1] == '2') {
		map[i][posX - 1] = '1';
       	totPoint += 1;
	}
	else if (map[i][posX - 1] == '1') {
		map[i][posX - 1] = ' ';
		totPoint += 10;
	}
					
	if (map[i][posX + 1] == '3') {					// RIGHT
		map[i][posX + 1] = '2';
		totPoint += 2;
	}
	else if (map[i][posX + 1] == '2') { 
		map[i][posX + 1] = '1'; 
		totPoint += 1;
	}
	else if (map[i][posX + 1] == '1') {
		map[i][posX + 1] = ' ';
		totPoint += 10;
	}
					
	if (map[i + 1][posX - 1] == '3') {				// LOWER LEFT		
		map[i + 1][posX - 1] = '2';
		totPoint += 2;
	}
	else if (map[i + 1][posX - 1] == '2') {
		map[i + 1][posX - 1] = '1';
		totPoint += 1;
	}
	else if (map[i + 1][posX - 1] == '1') {
		map[i + 1][posX - 1] = ' ';
		totPoint += 10;
	}
					
	if (map[i + 1][posX + 1] == '3') {				// LOWER RIGHT
		map[i + 1][posX + 1] = '2';
		totPoint += 2;
	}
	else if (map[i + 1][posX + 1] == '2') {
		map[i + 1][posX + 1] = '1';
		totPoint += 1;
	}
	else if (map[i + 1][posX + 1] == '1') {
		map[i + 1][posX + 1] = ' ';
		totPoint += 10;
	}
	
	return totPoint;
}

int game()
{
	int sizeR = 20;
	int sizeC = 20;
	int posX = 10;
	int posY = 18;
	
    char map[20][21] = {
        "####################",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#         .        #",
        "#         .        #",
        "#         .        #",
        "#         .        #",
        "#         .        #",
        "#         .        #",
        "#         .        #",
        "#         .        #",
        "#         .        #",
        "#         .        #",
        "#         A        #",
        "####################"};
	
//	for (int i = 0; i < sizeR; i++){
//		for (int j = 0; j < sizeC; j++){
//			if (i == 0 || j == 0 || i == sizeR - 1 || j == sizeC - 1) map[i][j] = '#'; 
//			else map[i][j] = ' ';
//		}
//	}


//=========================================RANDOM NUMBER==============================================	
    srand(time(NULL));
    
	for (int i = 0; i < sizeR - 12; i++) {
        for (int j = 0; j < sizeC - 1; j++) {
            if (map[i][j] == ' ') {
                int randNum = rand() % 3 + 1; // Generate random number from 1-3
                map[i][j] = randNum + '0';    // Convert int to char and assign to map
            }
        }
    }

//====================================================================================================	
	
	map[posY][posX] = 'A';
	
	char move;
	int on = 1;
	int totPoint = 0;
	int shots = 0;
	
	while (on == 1) {
		system("cls");
		
//==========================================COUNT REMAINING============================================	
		int remaining = 0;
		for (int i = 1; i < sizeR - 1; i++){
			for (int j = 1; j < sizeC - 1; j++){
				int isNum = map[i][j] - '0';
				if (isNum >= 1 && isNum <= 3) remaining++;
			}
		}

//============================================MAP DISPLAY==============================================		
		for (int i = 0; i < sizeR; i++){
			for (int j = 0; j < sizeC; j++) printf("%c", map[i][j]);
			printf("\n");
		}
		
		printf("Score: %d\n", totPoint);
		printf("Remaining: %d\n", remaining);

//===========================================PLAYER MOVEMENT==============================================
		move = _getch();
	
		if (move == 'a' && map[posY][posX - 1] != '#') {
		    map[posY][posX] = ' ';
		    posX--;
		    map[posY][posX] = 'A';
		
		    for (int i = 1; i < sizeR - 1; i++) {					// Print '.' Trail
		        if (map[posY - i][posX] == ' ') {
		            map[posY - i][posX] = '.';
		            if (map[posY - i][posX + 1] == '.'){
		            	map[posY - i][posX + 1] = ' ';
					}
		        } 
		    }
		}
		
		else if (move == 'd' && map[posY][posX + 1] != '#') {
		    map[posY][posX] = ' ';
		    posX++;
		    map[posY][posX] = 'A';
		
		    for (int i = 1; i < sizeR - 1; i++) {					// Print '.' Trail
		        if (map[posY - i][posX] == ' ') {
		            map[posY - i][posX] = '.';
		            if (map[posY - i][posX - 1] == '.'){
		            	map[posY - i][posX - 1] = ' ';
					}
		        } 
		    }
		}

//===============================================SHOOTING================================================	
		else if (move == ' ') {
			shots++;
		    int temp = posY;
		    
		    for (int i = posY - 1; i >= 0; i--) { 
		        if (map[i][posX] == '3') {
		            map[i][posX] = '2';
		            map[i + 1][posX] = '.';
		            totPoint += 2;
		            totPoint = radius(i, posX, totPoint, map);
		            break;
		        } 
				else if (map[i][posX] == '2') {
		            map[i][posX] = '1';
		            map[i + 1][posX] = '.';
		            totPoint += 1;
		            totPoint = radius(i, posX, totPoint, map);
		            break;
		        } 
				else if (map[i][posX] == '1') {
		            map[i][posX] = '.';
		            map[i + 1][posX] = '.';
		            totPoint += 10;
		            totPoint = radius(i, posX, totPoint, map);
		            break;
		        } 
		        else if (map[i][posX] == '#') {
		            map[i + 1][posX] = '.';
		            totPoint += 10;
		            totPoint = radius(i, posX, totPoint, map);
		            break;
		        } 
				else if (map[i - 1][posX] == '.') {
		            system("cls");

		            map[posY - 1][posX] = '.';					// Update 'A' position
		            posY = i;
		            map[posY - 1][posX] = 'A';
		            
		            for (int j = 0; j < sizeR; j++) {			// Re-Display map for animation
		                printf("%s\n", map[j]);
		            }
		            printf("Score: %d\n", totPoint);
					printf("Remaining: %d\n", remaining);
					
		            Sleep(1);
		        }
		    }
		    posY = temp;
		}
//=================================GENERATE NEW LINE & SHIFT OLD MAP====================================
		if (shots == 10) {
		    for (int i = sizeR - 2; i > 0; i--) {
		        for (int j = 1; j < sizeC - 1; j++) {
		            if (map[i][j] != '#' && map[i - 1][j] != ' ') {
		                map[i][j] = map[i - 1][j]; 						// Shift down
		                map[i - 1][j] = ' ';       						// Clear the upper cell
		            }
		        }
		    }
		
		    for (int j = 1; j < sizeC - 1; j++) {
		        int randNum = rand() % 3 + 1; 							// Generate random number from 1-3
		        map[1][j] = randNum + '0';    							// Add new random number to the top line
		    }
		    shots = 0;
		    
		    for (int j = 0; j < sizeC; j++){
		    	map[0][j] = '#';
			}
		}
//========================================REMOVE EXTRA TRAILS===========================================
		for(int i = 1; i < sizeR; i++){
			for(int j = 1; j < sizeC; j++){
				if(map[i][j] == '.' && j != posX) map[i][j] = ' ';
			}
		}

//=======================================WIN & LOSE CONDITION===========================================
		if (remaining == 0) on = 2;						// Win
		
		for(int j = 1; j < sizeC - 1; j++) {			// Lose
			if(map[16][j] != ' ' && map[16][j] != '.' && map[16][j] != 'A') on = 0;
		}
	}
	
//============================================WIN SCREEN================================================
	if (on == 2) {
		printf("\nYou Win!\n");
		printf("Press Enter to Continue...");
		getchar();
	}
	
//===========================================LOSE SCREEN================================================
	if (on == 0) {
		for(int j = 1; j < sizeC - 1; j++) {			// Lose
			if(map[16][j] == 'A') map[16][j] = '.';
		}
		
		printf("\nGame Over!\n");
		printf("Press Enter to Continue...");
		getchar();
	}

	return 0;
}

int main() 
{
    printf("BUBBLE FIZZPOP\n\n");
    printf("Welcome to Bubble FizzPop!\n\n");
    printf("Press Enter to Continue...");
    getchar();

    b: system("cls");

    printf("BUBBLE FIZZPOP\n\n");
    printf("1. Play\n");
    printf("2. How to Play\n");
    printf("3. Exit\n");
    a: printf(">> ");

    int choice;

    if (scanf("%d", &choice) != 1) {
        printf("[!] Input must be a number!\n");
        while (getchar() != '\n'); // Clear input buffer
        goto a;
    }

    if (choice == 1) game();
    else if (choice == 2){
    	howTo();
    	goto b;
	} 
    else if (choice == 3) leave();
    else {
        printf("[!] Input must be between 1 and 3!\n");
        goto a;
    }

    return 0;
}


