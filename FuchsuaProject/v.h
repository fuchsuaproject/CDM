#pragma once
#ifndef V_H
#define V_H
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
#include<io.h>
#include<stdlib.h>
//#include<Skout.h>

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
#define lineQ ¦£
#define lineE ¦¤
#define lineZ ¦¦
#define lineC ¦¥
#define lineW ¦¡
#define lineA ¦¢
#define lineD lineA
#define lineX lineW
#define lineAW ¦§
#define lineWA ¦¨
#define lineDW ¦©
#define linwWD ¦ª
#define jesusCrist ¦«
//#define ssang "
#define line2 f(x) fputc('#x')
//fputc(a, stdout)

// ¦¡¦¢¦£¦¤¦¥¦¦¦§¦¨¦©¦ª¦«

// h

int cdm_ShellMainCode(int eMode);
int cdm_DirectoryToChar(char directory[2048][260], char charChar[260]);
int cdm_CharToDirectory(char charChar[260], char directory[2048][260]);
int cdm_FindDirectorySize(char directory[2048][260]);
int cdm_Setup();
int cdm_FindStarInStringLast(char string[260]);
//inr
int cdm_CdZeomDugae(char string[260]);
int cdm_baseDir_Func();
int find_enter(char _strings[2048], int _count);
inline int yoany();
unsigned _stdcall Keyupdate_loop(void* arg);
unsigned _stdcall Keyboard_loop(void* arg);
unsigned _stdcall Display_loop(void* arg);
UINT16 QStart(UINT16 QStartSetup, UINT16 QStartOption1, UINT16 QStartOption2, UINT16 QStartOption3, UINT16 QStartOption4);
UINT16 cdmb_Parsing();

inline int yoany() {
	FILE* pSetupBatch = fopen("CDMSETUP.BAT", "r");
	if (pSetupBatch == NULL) {
		pSetupBatch = fopen("CDMSETUP.BAT", "w");
		fprintf(pSetupBatch, "@title CDM_SETUP_PROGRAM_1_0\n@color 17\n@echo %%cd%%\\* > baseDir.cdm\n@exit");
		fclose(pSetupBatch);
	}
	system("start CDMSETUP.BAT");
	return 0;
}

#endif