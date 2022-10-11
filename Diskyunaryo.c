#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <dos.h>

#define DATABASE "MyDictionary.db" /* DATABASE filename */
#define TDATABASE "MyDictionary.tmp" /* TEMPORARY DATABASE filename */

void color(int code) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, code);
}

void clrscr(){
	
	int i;
	color(129);
	for (i = 0; i <= 4299; i++) printf("%c", 176);
	
}

void drawbox() {
	int x, y;
	
	color(112);
	for (y = 3; y <= 20; y++) {	
		for (x = 2; x <= 77; x++) {
			gotoxy(x + 1, y + 1); printf("%c", 176);
		}
	}
	
	color(0);
	for (y = 3; y <= 20; y++) {	
		for (x = 2; x <= 77; x++) {
			gotoxy(x, y); puts(" ");
		}
	}
}

void gotoxy(int x, int y) {
	
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void noscroll() {
	
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    COORD new_size =
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
    SetConsoleScreenBufferSize(handle, new_size);
}

struct myDictionary{
	char word[32];
	char meaning[512];
	
} myD;

int wordExists(char word[30]){ //check if the word is exist.
	FILE *db = fopen(DATABASE, "rb");
	int see = 0;
	
	while(fread(&myD, sizeof(struct myDictionary), 1, db)){
		if(!strcasecmp(myD.word, word)){
			return see;
		}else{
			see = 1;
		}
	}
	
	fclose(db);
	return see;
}

void search() {
	FILE *db; //Database
	char sWord[32]; //Words
	char sMeaning[512]; //Meaning


	if((db = fopen(DATABASE, "rb")) == NULL){ //check if there is existing database.
		
	gotoxy(3,20); color(6);	
	printf("Babala: Hindi mabuksan ang database");
	Sleep(500);
	printf(". ");
	Sleep(500);
	printf(". ");
	Sleep(500);
	printf(". ");
	Sleep(1000);
		
	}else{

	drawbox();
		gotoxy(3,3); color(9); printf("Ano ang salita na nais mong malaman? ");
		color(4); gets(sWord);
		
		if(wordExists(sWord) == 1){ //check if the word is existing
			while(fread(&myD, sizeof(struct myDictionary), 1, db) == 1){
				if(!strcasecmp(myD.word, sWord)){ //compare the word that the user input and to the word in the database.
				gotoxy(3,8); color(4);	printf("Kahulugan:");
				gotoxy(3,9); color(4);	puts(myD.meaning);
				
				}
			}
			gotoxy(3,20); color(6);
			printf("Pumindot ng kahit anong letra para magpatuloy. . .");
			getch();
			fclose(db);
		}else{
			gotoxy(3,20); color(6);
			printf("Babala: Hindi mahanap ang salitang %s", sWord);
			Sleep(500);
			printf(". ");
			Sleep(500);
			printf(". ");
			Sleep(500);
			printf(". ");
			Sleep(1000);
		}
		gotoxy(3,20); color(6);
		printf("Pumindot ng kahit anong letra para magpatuloy. . .");
		getch();
		fclose(db);
	}
}

void insert(){
	FILE *db;
	char sWord[32];
	char answer = 'h';

REPEAT:


	if((db = fopen(DATABASE, "ab")) == NULL){ //append word to the database.
		gotoxy(3,20); color(6);	
		printf("Babala: Hindi mabuksan ang database");
		Sleep(500);
		printf(". ");
		Sleep(500);
		printf(". ");
		Sleep(500);
		printf(". ");
		Sleep(1000);
	}else {
		clrscr();
		drawbox();
		
		color(9); gotoxy(2,4); printf("Bagong Salita na nais idagdag: ");
		color(4); gotoxy(2,5); gets(sWord);
		
		if(wordExists(sWord) == 1){
			color(6); gotoxy(2,13); printf("Babala: Ang salitang nais mong idagdag ay kasalukuyan nang nakalagay.");
			goto REPEAT;
		} else {
			strcpy(sWord, myD.word);
		}
		color(9); gotoxy(2,7);printf("Ilagay ang Kahulugan ng bagong Salita: ");
		color(4); gotoxy(2,8);gets(myD.meaning);
			
		color(6); gotoxy(2,10);	printf("Nais mo ba itong idagdag? (o/h) ");
			answer = getch();
		
		if(answer == 'o'){
		color(6); gotoxy(3,19);	
		printf("Idinadagdag");
		Sleep(500);
		printf(". ");
		Sleep(500);
		printf(". ");
		Sleep(500);
		printf(". ");
		Sleep(1000);
			
			if(fwrite(sWord, sizeof(struct myDictionary), 1, db) != 1){
			color(6); gotoxy(3,20);	
			printf("Babala: Hindi mabuksan ang database");
			Sleep(500);
			printf(". ");
			Sleep(500);
			printf(". ");
			Sleep(500);
			printf(". ");
			Sleep(1000);
			} else {
			color(6); gotoxy(3,20);	printf("Tagumpay ang pagdadagdag!");
			Sleep(500);
			}
			
			fclose(db);
		} else {
			gotoxy(3,20); color(6);
			printf("Binubura ang pansamantalang data ");
			Sleep(500);
			printf(". ");
			Sleep(500);
			printf(". ");
			Sleep(500);
			printf(". ");
			Sleep(1000);
			
			fclose(db);
		}
	}
}

void view_list(){
	FILE *db;
	
	clrscr();

		if((db = fopen(DATABASE, "rb")) == NULL){
			gotoxy(3,20); color(6);	
			printf("Babala: Hindi mabuksan ang database");
			Sleep(500);
			printf(". ");
			Sleep(500);
			printf(". ");
			Sleep(500);
			printf(". ");
			Sleep(1000);
			
	}else{
	REPEAT:
		
		clrscr();
		drawbox();
		
		gotoxy(3, 4); color(4); printf("Mga salita:");
		
			int words;
			char key;
		
		while(fread(&myD, sizeof(struct myDictionary), 1, db)){
			gotoxy(3, 5); color(9);	printf("%s", myD.word);
			words++;

			
			
		}

		gotoxy(3,20); color(6);
		printf("Pumindot ng kahit anong letra para magpatuloy. . .");
		getch();
		fclose(db);
		
	}
}

void remove_word(){
	FILE *db, *tdb;
	char answer = 'o';
	char sWord[32];
	
	clrscr();
	
	if((db = fopen(DATABASE, "rb")) == NULL){
			gotoxy(3,20); color(6);	
			printf("Babala: Hindi mabuksan ang database");
			Sleep(500);
			printf(". ");
			Sleep(500);
			printf(". ");
			Sleep(500);
			printf(". ");
			Sleep(1000);
	} else {
		clrscr();
		drawbox();
		color(9); gotoxy(2,4); printf("Salita na nais tanggalin: ");
		color(4); gotoxy(2,5); gets(sWord);
		
		if(wordExists(sWord) == 1){
			if((tdb = fopen(DATABASE, "wb")) == NULL){
				gotoxy(3,20); color(6);	
				printf("Babala: Hindi mabuksan ang database");
				Sleep(500);
				printf(". ");
				Sleep(500);
				printf(". ");
				Sleep(500);
				printf(". ");
				Sleep(1000);
			} else {
				while(fread(&myD, sizeof(struct myDictionary), 1, db) == 1){
					if(!strcasecmp(myD.word, sWord)){
						fwrite(&myD, sizeof(struct myDictionary), 1, tdb);
					}
				}
					color(6); gotoxy(3,10);	printf("Nais mo ba itong tanggalin? (o/h) ");
					answer  = getch();
					
					fclose(db);
					fclose(tdb);
					
					if(answer == 'o'){
					color(6); gotoxy(3,20);	
					printf("Tinatanggal");
					Sleep(500);
					printf(". ");
					Sleep(500);
					printf(". ");
					Sleep(500);
					printf(". ");
					Sleep(1000);
					
					remove(DATABASE);
					rename(TDATABASE, DATABASE);
					
					color(6); gotoxy(3,20);	printf("Tagumpay ang pagtatanggal!");
					sleep(300);
			
				} else {
					color(6); gotoxy(3,20);	
					printf("Binubura ang pansamantalang data!");
					Sleep(500);
					printf(". ");
					Sleep(500);
					printf(". ");
					Sleep(500);
					printf(". ");
					Sleep(1000);
					remove(TDATABASE);
			}
		}
	} else {
			color(6); gotoxy(3,20);	printf("Babala: Ang salita ay hindi nakalagay sa data.");
			Sleep(1000);
		}
	}
}

void front(){
	char choices;
	
	clrscr();
	noscroll();
	drawbox();
	
		color(9); gotoxy(8,4); printf("********** MAKABAGONG DIKSYONARYO SA WIKANG TAGALOG ***********");
		color(14);
		gotoxy (3,6); printf("M");
		gotoxy (3,7); printf("B");
		gotoxy (3,8); printf("L");
		gotoxy (3,9); printf("T");
		gotoxy (3,10); printf("W");
		color(4); gotoxy(4,6); printf("aghanap");
		color(4); gotoxy(4,7); printf("agong Salita ang idadagdag.");
		color(4); gotoxy(4,8); printf("istahan ng mga Salita.");
		color(4); gotoxy(4,9); printf("anggalin ang salita.");
		color(4); gotoxy(4,10); printf("akas");
		color(14); gotoxy(0,23); printf("Likha ni Wilster Dela Cruz");
	
		while(choices != 'w') {
		choices = getch();
	
			switch(choices){
				case 'm':
					search();
					front();
					break;
				
				case 'b':
					insert();
					front();
					break;
				
				case 'l':
					view_list();
					front();
					break;
				
				case 't':
					remove_word();
					front();
					break;
				default:
					color(4); gotoxy (3,14); printf("Mali ang iyong iniligay!");
					Sleep(200);
					color(0); gotoxy (3,14); printf("                        ");
					gotoxy(58,23);
					break;
				case 'w':
					clrscr();
					exit(0);
		}
	}
}

int main(void){
		
	front();
	

	return 0;
}
