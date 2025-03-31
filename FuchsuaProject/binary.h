/*
 ################
 # STACK�� ���� #
 ################
 �� ###############################################
 �� # 1 # // {                                    #
 �� # 2 #	���� ��뿡 ���� ����                 #
 �� # 3 #	���� ������ ������ ���� ����ֽ��ϴ�. #
 �� # 4 # }                                       #
 �� #                                             #
 �� ###############################################
 �� 
 �� #########
 �� #       #
 �� # #   # #
 �� # #   # #
 �� # #   # #
 �� # #   # #
 �� # #   # #
 �� # ##### #
 �� #       #
 �� #########
 �� 
 �� #############################################
 �� # 1 # // {                                  #
 �� # 2 #	���⿡�� ���ÿ� 2�� Ǫ���ϰڽ��ϴ�. #
 �� # 3 # }                                     #
 �� # 4 $                                       #
 �� # 5 # PUSH 1 2                              #
 �� #                                           #
 �� #############################################
 �� 
 �� #########
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
//#include<Skout.h>
//#include"v.h"

//
#pragma comment (lib, "winmm.lib")    //����
#include <mmsystem.h>                //����
#include <Digitalv.h>                //����

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
#define lineQ ��
#define lineE ��
#define lineZ ��
#define lineC ��
#define lineW ��
#define lineA ��
#define lineD lineA
#define lineX lineW
#define lineAW ��
#define lineWA ��
#define lineDW ��
#define linwWD ��
#define jesusCrist ��
//#define ssang "
#define line2 f(x) fputc('#x')
//fputc(a, stdout)

// ����������������������
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
#ifdef q_io
#if q_io == 0
#define print(n) wprintf(L"%s", n)
#define input(n) fgetws(n, 256, stdin);size_t len = wcslen(str);if(len > 0 && str[len - 1] == L'\n'){str[len - 1] = L'\0'}
#elif q_io == 1
#define print(n) q_output(n)
#define input(n) q_input(n)
#include<q_io.h>
#else
#error q_io�� 0�� 1�Դϴ�.
#endif
#else
#define q_io 0
#endif

//�� ���� �˾Ƽ� �м��Ͻð�
//�� �Ʒ��� ���� �����ϴ� ���Դϴ�.

static UINT16 memory[4096] = { 0, }; //�� ���α׷��� �޸��Դϴ�.
static UINT16 stack1_Count = 0; //�� ���α׷��� �⺻ ������ ī��Ʈ�Դϴ�.
/*
stackx_Count��(��) �� ���α׷��� ������ memory�� ������ �ʴ� �������Դϴ�. �� ������ ���ÿ� ���� ��� �׿��ִ��� ��Ÿ���ϴ�.

 #######################
 # STACK��(��) �����? #
 #######################

  stack�� ���Լ����� �ϴ� �ϳ��� ��������Դϴ�. �Ʒ��� �׸��� ������.

  #   #
  #####
  # 1 #
  #####
  # 2 #
  #####

  stack�� 2, 1 ������ �־����ϴ�. ��,���� �������� ���� ���� ������ �� �ֽ��ϴ�.
*/
static UINT16 stack2_Count = 0;
static UINT16 stack3_Count = 0;

/*
 ###################
 # memory�� ���൵ #
 ###################
 #
 ###################################################################################
 # 0: ����� ���� ó���� �ִ� �޸� ��ġ�̸�, ���⿡�� ����Ȱ��� ��ġ�����Դϴ�. #
 #    �ش���ġ�� �����ϰ� �� ��ġ���� ��ũ��Ʈ�� �����մϴ�.                       #
 ###################################################################################
 # 1: �� ���� ��ũ��Ʈ ���൵�� ������ ���� �����ڵ带 ��ȯ�մϴ�.                 #
 ###################################################################################
 # 16-271: �� ���� ���α׶��� �������� ���� ���� �����ϴ� ���Դϴ�.                #
 ###################################################################################
 # 272-2431: �� ���� ��¹��� �Դϴ�.                                              #
 ###################################################################################
 # 2432: �� ���� Ŀ���� ��ġ�Դϴ�.                                                #
 ###################################################################################
 # 2433-2868: ù ��° ������ �����Դϴ�.                                           #
 ###################################################################################
 # 2869-2944: �� ��° ������ �����Դϴ�.                                           #
 ###################################################################################
 # 2945-3200: �� ��° ������ �����Դϴ�.                                           #
 ###################################################################################

 * ����!!! {
	1. 3201 ���� ���������Դϴ�.
 }

 ��ƴϻǻ� �̸� ����
*/

inline UINT16 cdmb_Main(); //cdmb�� '����'�̶�°Ÿ� �����ϰ� ���ִ� cdmb �� ��ü 
inline UINT16 cdmb_Memory(); // cdmb���� ��Ʋ����� ������� ó�� ������ �ڵ带 �ҷ����ִ� ��
//
inline UINT16 cdmb_Parsing(); // Ŀ�ǵ��� �޸� ������ ���� ������
inline UINT16 cdmb_Command(UINT16* dPoint); // Ŀ�ǵ��� ���� ���� �Լ�

//���⼭ ���ʹ� ������ �ƴ� ���ǿ��� �ּ��� �ްڽ��ϴ�.
inline UINT16 cdmb_Push(UINT16 hPoint, UINT16* hCount, UINT16 _16bit);
inline UINT16 cdmb_Error(UINT16 rErrorCodes);
inline UINT16 cdmb_Pop(UINT16 pPoint, UINT16* pCount);
inline UINT16 cdmb_Safe(UINT16 ePoint, UINT16 eCount, UINT16 ePushTheMemory);
inline UINT16 cdmb_Load(UINT16 dPoint, UINT16* dCount, UINT16 dLoadTheMemory);

inline UINT16 cdmb_Main() {
	if(q_io == 0) //q_io��
		/*
		##########################################################################
		# q_io ���̺귯���� cdm�� �⺻ ���� ���̺귯���Դϴ�. �ڼ��� �˾ƺ�����. #
		# https://                                                               #
		##########################################################################D
		*/
	{
		setlocale(LC_ALL, "");
	}
	UINT16 cdmmb_t_1 = cdmb_Memory(); //�ڵ带 �޸𸮿� �ҷ�����
	if (cdmmb_t_1 == 0x41) { //�ҷ��� �� ������ ����
		return 0x41;
	}
	else { // �ҷ������� �ڵ尡 ����ɶ����� �ݺ�
		cdmb_Parsing();
	}
}

inline UINT16 cdmb_Memory() {
	FILE* cdm_t_WFILE1 = _wfopen(L"StartMemory", L"rb, ccs=UTF-16LE"); // ��Ʋ����� ������� UTF-16 ������ �ҷ�����
	if (!cdm_t_WFILE1) {
		return 0x41; // �ҷ����� ���ϸ� ����
	}
	fread(&memory[16], sizeof(UINT16), 256, cdm_t_WFILE1); // #E[16]���� õõ�� �޸𸮸� �ҷ���4��
}
static UINT16 cdmb_CommandFuncReturnen = 0x0; //�ڵ� ���ᰪ ���� ���� �� ����
inline UINT16 cdmb_Parsing() { // �ڵ� �ݺ����� �Լ�
	UINT16 cdm_t_MEMORYPOINTER = 0; // �޸� ������ ��ġ TODO: ���� ���� 0->0x0010
	cdm_t_MEMORYPOINTER = memory[cdm_t_MEMORYPOINTER]; // �޸� �̵�
	while(1)//�ݺ�
	{
		cdmb_CommandFuncReturnen = cdmb_Command(&cdm_t_MEMORYPOINTER); // �ڵ� ���پ� ����
		//
		if (cdmb_CommandFuncReturnen != 0) { // �ڵ忡�� 0�� �ƴѰ��� ��ȯ�ϸ� ����
			break;
		}
	}
	//
}
//todo: ����Ʈ �ڵ带 �����ϱ�
inline UINT16 cdmb_Command(UINT16* dPoint) {
	if (memory[*dPoint] == 0x0000) { //push
		/*
		PUSH �����

		 ###########
		 # PUSH��? #
		 ######################################################################################
		 # ���ÿ� ���� �ִ� ���� ���մϴ�. �� ��ɾ� ����(��) (��ɾ�) (�ɼ�1) (�ɼ�2)�Դϴ�. #
		 ######################################################################################
		*/
		//s
		switch (memory[*dPoint + 1]) { // �ش� (��ɾ�)�� (�ɼ�1)�� ���� �ޱ�
		case 0x0001: // 1��(��) �޾��� ���,
			cdmb_Push(2433, &stack1_Count, memory[*dPoint + 2]); // 1�� ���ÿ� PPUSH
			break;
		case 0x0002: // 2��(��) �޾��� ���,
			cdmb_Push(2689, &stack2_Count, memory[*dPoint + 2]); // 2�� ���ÿ� PUSH
			break;
		case 0x0003: // 3��(��) �޾��� ����
			cdmb_Push(2945, &stack3_Count, memory[*dPoint + 2]);// )
			break;
		default:
			cdmb_Error(0x0100);
			break;
		}
		*dPoint += 3;
	}
	else if (memory[*dPoint] == 0x0001) { //pop
		/*
		#######
		# POP #
		#######################################################
		# �� ��ɾ�� ������ �������� �־��� ���� ��Ʈ���ϴ�. #
		#######################################################
		*/
		switch (memory[*dPoint + 1]) {
		case 0x0001:
			cdmb_Pop(2433, &stack1_Count); // 1�� ���� ��Ʈ����
			break;
		case 0x0002:
			cdmb_Pop(2689, &stack2_Count); // 2�� ���� ��Ʈ����
			break;
		case 0x0003:
			cdmb_Pop(2945, &stack3_Count); // 3�� ���� ��Ʈ����
			break;
		default:
			cdmb_Error(0x0101);
			break;
		}
		*dPoint += 2;
	}
	else if (memory[*dPoint] == 0x0002) { //safe
		/*
		########
		# SAFE #
		################################################################
		# �� ��ɾ�� (�ɼ�1)��(��) �ش��ϴ� ������ ������ �����մϴ�. #
		################################################################
		*/
		switch (memory[*dPoint + 1]) {
		case 0x0001:
			cdmb_Safe(2433, stack1_Count, memory[*dPoint + 2]);
			break;
		case 0x0002:
			cdmb_Safe(2689, stack2_Count, memory[*dPoint + 2]);
			break;
		case 0x0003:
			cdmb_Safe(2945, stack3_Count, memory[*dPoint + 2]);
			break;
		default:
			cdmb_Error(0x0102);
			break;
		}
		//
		*dPoint += 3;
	}
	else if (memory[*dPoint] == 0x0003) { //load
		switch (memory[*dPoint + 1]) {
		case 0x0001:
			cdmb_Load(2433, &stack1_Count, memory[*dPoint + 2]);
			break;
		case 0x0002:
			cdmb_Load(2689, &stack2_Count, memory[*dPoint + 2]);
			break;
		case 0x0003:
			cdmb_Load(2945, &stack3_Count, memory[*dPoint + 2]);
			break;
		default:
			cdmb_Error(0x0103);
			break;
		}
		*dPoint += 3;
	}
	else if (memory[*dPoint] == 0x0004) { //echo
		printf("%04x %d", memory[*dPoint + 1], memory[*dPoint + 1]);
		*dPoint += 2;
	}
	else if (memory[*dPoint] == 0xFEFF) {
		return 1;
	}
	return 0;
}

inline UINT16 cdmb_Push(UINT16 hPoint, UINT16* hCount, UINT16 _16bit) {
	memory[hPoint + *hCount] = _16bit;
	*hCount += 1;
	return 0;
}

inline UINT16 cdmb_Error(UINT16 rErrorCodes) {
	memory[1] = rErrorCodes;
	return 0;
}

inline UINT16 cdmb_Pop(UINT16 pPoint, UINT16* pCount) {
	//memory[]
	*pCount += 1;
	return 0;
}

inline UINT16 cdmb_Safe(UINT16 ePoint, UINT16 eCount, UINT16 ePushTheMemory) { //
	memory[ePushTheMemory] = memory[ePoint + eCount];
	return 0;
}
inline UINT16 cdmb_Load(UINT16 dPoint, UINT16* dCount, UINT16 dLoadTheMemory) {
	cdmb_Push(dPoint, dCount, memory[dLoadTheMemory]);
	return 0;
}

//

#endif //NO_BANARY
#endif