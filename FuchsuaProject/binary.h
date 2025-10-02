/*
 ################
 # STACK의 예제 #
 ################
 └ ###############################################
 │ # 1 # // {                                    #
 │ # 2 #	스택 사용에 대한 예제                 #
 │ # 3 #	현재 스택은 다음과 같이 비어있습니다. #
 │ # 4 # }                                       #
 │ #                                             #
 │ ###############################################
 │ 
 └ #########
 │ #       #
 │ # #   # #
 │ # #   # #
 │ # #   # #
 │ # #   # #
 │ # #   # #
 │ # ##### #
 │ #       #
 │ #########
 │ 
 └ #############################################
 │ # 1 # // {                                  #
 │ # 2 #	여기에서 스택에 2를 푸쉬하겠습니다. #
 │ # 3 # }                                     #
 │ # 4 $                                       #
 │ # 5 # PUSH 1 2                              #
 │ #                                           #
 │ #############################################
 │ 
 └ #########
    #       #
	# #   # #
	# #   # #
	# #   # #
	# ##### #
	# # 2 # #
	# ##### #
	#       #
	#########
*/
#pragma once
#ifndef binary_hh
#define binary_hh

#include"version.h"

#define da 1

#define _CRT_SECURE_NO_WARNINGS

//made in china

#include<stdio.h>//include "stdio.h"
#include<stdlib.h>
#include<conio.h>//include "conio.h"
//#include<stdlib.h>//include "stdlib.h"
#include<math.h>//include "math.h"
#include<string.h>//include "string.h"
#include<windows.h>//include "windows.h"
#include<process.h>
#ifndef binary_h
#define binary_h
#include<io.h>
#include<time.h>
#include<locale.h>
//#include"qmach/qdisk.h"
//#include<Skout.h>
//#include"v.h"

//
#pragma comment (lib, "winmm.lib")    //음악
#include <mmsystem.h>                //음악
#include <Digitalv.h>                //음악

#include"q.h"
#include"v.h"
#include<malloc.h>

#endif

#ifdef def_binary_helper

#define clss system("cls")
#define colors(backer, downer) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (backer * 16) + downer)
#define darkmodes system("0f")
#define whitemodes system("f0")
#define token(kokk) printf("%02x", kokk)
//#define typers 0x18//1319
#define curposgens(x, y) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)x, (short)y})
#define ands(hexbinn) (hexbinn == 0) ? 0 : ((hexbinn == 1) ? 0 : ((hexbinn == 2) ? 0 : 1)))
#define ors(hexbinn) (hexbinn == 0) ? 0 : ((hexbinn == 1) ? 1 : ((hexbinn == 2) ? 1 : 1)))
#define threads(toroop) _beginthreadex(NULL, 0, toroop, 0, 0, NULL)
#define LString(x) L##x
#define FIE ;
#define start {
#define theEnd }
#define lineQ ┌
#define lineE ┐
#define lineZ └
#define lineC ┘
#define lineW ─
#define lineA │
#define lineD lineA
#define lineX lineW
#define lineAW ├
#define lineWA ┬
#define lineDW ┤
#define linwWD ┴
#define jesusCrist ┼
//#define ssang "
#define line2 f(x) fputc('#x')
//fputc(a, stdout)

// ─│┌┐┘└├┬┤┴┼
#endif

#ifndef seoneon
typedef enum {NOCURSOR, SOLIDCURSOR, NOMALCURSOR} CURSOR_TYPE;
#define clrscr() system("cls");
inline void gotoxy(int x, int y);
inline int wherex();
inline int wherey();
inline void setcursortype(CURSOR_TYPE c);
#define delay(n) Sleep(n)
#define _delay(n) Sleep(n * 1000)
#define randomize srand((unsigned)time(NULL))
#define random(n) (rand() % (n))
#ifndef jeong_eui
inline void gotoxy(int x, int y) {
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	//
}
inline int wherex() {
	CONSOLE_SCREEN_BUFFER_INFO cdm_ConsoleBufferInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cdm_ConsoleBufferInfo);
	return cdm_ConsoleBufferInfo.dwCursorPosition.X;
}
inline int wherey() {
	CONSOLE_SCREEN_BUFFER_INFO cdm_ConsoleBufferInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cdm_ConsoleBufferInfo);
	return cdm_ConsoleBufferInfo.dwCursorPosition.Y;
}
inline void setcursortype(CURSOR_TYPE c) {
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NOMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
	}
}
#endif//001
#endif

//#define q_io 0

#ifndef NO_BINARY
#define NO_BINARY

unsigned char K0, K1, K2, K3, K4, K5 = 0;

unsigned char MAR0, MAR1, MAR2, MAR3 = 0;
unsigned char MDR = 0;

char StackSize = 0x01;
char* Stack = NULL;

FILE* Memory = NULL;
FILE* PCI = NULL;
FILE** Disk = ((FILE**)0);

int count = 1;

inline unsigned char cdmb_Memory(char Register1, char Register2, char Register3, char Register4) {
	unsigned int MemoryAddress = 0x00000000;
	MemoryAddress += ((int)Register1) << 32;
	MemoryAddress += ((int)Register2) << 24;
	MemoryAddress += ((int)Register3) << 16;
	MemoryAddress += ((int)Register4) << 8;
	Memory = fopen("RRM", "wb+");
	//fseek(Memory, (long)MemoryAddress, SEEK_SET);
	MDR = fgetc((Memory + MemoryAddress));
	fclose(Memory);
}

inline unsigned char cdmb_Push();
inline unsigned char cdmb_Pop();

inline unsigned char cdmb_MemoryMap();
inline unsigned char cdmb_Parsing();

inline unsigned char cdmb_Main() {
	Stack = malloc(sizeof(char) * StackSize);
	count++;
	Disk = malloc(sizeof(FILE*) * count);
	//Memory = fopen("RM", "wb+");

	*(Disk) = fopen("ROM", "rb");
	
	cdmb_MemoryMap();
	cdmb_Parsing();

	//
}

inline unsigned int cdmb_MemoryAddressShift(char a, char b, char c, char d) {
	unsigned int MemoryAddress = 0x00000000;
	MemoryAddress += (int)a << 32;
	MemoryAddress += (int)b << 24;
	MemoryAddress += (int)c << 16;
	MemoryAddress += (int)d << 8;
	return MemoryAddress;
}

inline unsigned char cdmb_MemoryMap() {
	unsigned int MemoryAddress = 0x00000000;
	char FA1, FA2, FA3, FA4, MA1, MA2, MA3, MA4 = 0;
	//cdmb_MemoryAddressShift(FA1, FA2, FA3, FA4);

	Memory = fopen("RRM", "wb+");
	char data = 0;
	//qwertyuiopasdfghjkl;zxcvbnm,.
	data = fgetc(Memory + 0x00000001);
	if (data == 0x01) {
		if (fgetc(Memory + 0x00000003) == 0x01) { //읽기
			fputc(
				fgetc(
					(
						*(Disk + fgetc(Memory + 0x00000002)) + cdmb_MemoryAddressShift(
							fgetc(Memory + 0x00000004),
							fgetc(Memory + 0x00000005),
							fgetc(Memory + 0x00000006),
							fgetc(Memory + 0x00000007)
						)
					)
				),
				Memory + cdmb_MemoryAddressShift(
					fgetc(Memory + 0x00000008),
					fgetc(Memory + 0x00000009),
					fgetc(Memory + 0x0000000a),
					fgetc(Memory + 0x0000000b)
				)
			);
		}
	}
}

#endif //NO_BANARY
#endif