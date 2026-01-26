// Created by Fuchsua on 2022-10-13 22:23:28.
#pragma once
#ifndef binary_hh
#define binary_hh

// NKB에 대한 기본적인 설명

// NKB는 "Neo Kompiler Bahasa"의 약자로, Fuchsua 프로젝트에서 개발한
// 함수형 프로그래밍 언어입니다. NKB는 간결하고 효율적인 문법을 제공하여
// 개발자가 복잡한 알고리즘과 로직을 쉽게 구현할 수 있도록 설계되었습니다.

// NKB의 주요 특징은 다음과 같습니다:
// 1. 함수형 프로그래밍: NKB는 함수형 프로그래밍 패러다임을 따르며,
//	고차 함수, 익명 함수, 재귀 등을 지원합니다.
// 2. 간결한 문법: NKB는 직관적이고 간결한 문법을 제공하여,
//	개발자가 빠르게 코드를 작성할 수 있도록 돕습니다.
// 3. 강력한 타입 시스템: NKB는 정적 타입 시스템을 채택하여,
//	컴파일 타임에 타입 오류를 검출할 수 있습니다.
// 4. 확장성: NKB는 다양한 라이브러리와 모듈을 지원하여,
//	개발자가 필요에 따라 기능을 확장할 수 있습니다.
// 5. 적은 컴파일러 옵션: NKB는 코드 내부에서 옵션을 설정할 수 있어,
//	컴파일러 옵션을 최소화합니다.

/* 예제(Hello world + arg printing) */
// export bin/exemple/a
// import lib/std/std
// Public Class Main {
//     Public Naneged void main(Class arg) {
//         print("Hello world"%+arg.str[1]);
//     }
// }

// NKB Compile
// NKB는 소스 코드를 파싱하여 중간 표현(IR)으로 변환한 후,
// 기계어로 컴파일합니다. NKB 컴파일러는 최적화된 코드를 생성하여,
// 효율적인 실행을 보장합니다.

// NKB Windows로 쓰여진 어플리케이션 설치 과정
// 1. NKB 패키지 파일을 다운로드한다. (예: nkb_package.np)
// 2. 패키지 파일을 CDM 셸에서 설치 명령어를 사용하여 설치한다.
//   예: install nkb_package.np
// 3. 설치가 완료되면, NKB 어플리케이션을 실행할 수 있다.

// Q: 그러면 설치된 패키지는 어디에 저장되나요?
// A: 기본적으로 C:\CDM\NKB\windows.np나 사용자가 지정한 경로에 저장됩니다.
// Q: 설치된 패키지를 제거하려면 어떻게 하나요?
// A: CDM 셸에서 제거 명령어를 사용하여 패키지를 제거할 수 있습니다.
//   예: uninstall nkb_package.np

// 자세한 내용은 Fuchsua 프로젝트의 공식 문서를 참고하시기 바랍니다.

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


char** compiler_option;

inline unsigned char cdmb_Memory(char Register1, char Register2, char Register3, char Register4);

extern char* option;
inline unsigned char cdmb_Main(char* a) {
	// NKB 컴파일러 메인 함수
	// 컴파일러	초기화
	cdmb_Memory(0x00, 0x00, 0x00, 0x00);
	// 옵션 파싱 시작
	// 옵션 예시: "directory=src/com/example/example;output=bin/;type=package"
	// 옵션 종류
	// 1. directory: 소스 코드 디렉토리 지정
	// 2. output: 출력 디렉토리 지정
	// 3. type: 컴파일 타입 지정 (예: executable, library, package)
	// 4. optimize: 최적화 레벨 지정 (예: none, basic, full)
	// 5. debug: 디버그 정보 포함 여부 (예: true, false)

	// 세미클론(;)을 기준으로 옵션 분리 및 중복 제거
	int i = 0;
	while (1) { // 세미클론(;) 개수 세어보기
		if (a[i] == ';') {
			i++;
			continue;
		}
		else if (a[i] == '\0') {
			break;
		}
		else {
			continue;
		}
	}
	compiler_option = (char**)malloc(sizeof(char*) * i); // 최대 i개 옵션 저장
	int option_index = 0;// 옵션 인덱스
	char* token_ptr = strtok(a, ";");// 첫 번째 토큰 추출
	while (token_ptr != NULL) {// 토큰이 NULL이 아닐 때까지 반복
		compiler_option[option_index] = (char*)malloc(sizeof(char) * (strlen(token_ptr) + 1));// 메모리 할당
		strcpy(compiler_option[option_index], token_ptr);// 토큰 복사
		option_index++;// 옵션 인덱스 증가
		token_ptr = strtok(NULL, ";");// 다음 토큰 추출
	}

	// 옵션 처리
	// directory, output, type, optimize, debug 등

	// 처리 반복문
	for (int count = 0; count > i; count++) {
		// directory 옵션 처리
		if (strncmp(compiler_option[count], "directory=", 10) == 0) {
			// 디렉토리 경로 추출
			char* directory_path = compiler_option[count] + 10;
			// 디렉토리 설정 로직 구현
		}
		// output 옵션 처리
		else if (strncmp(compiler_option[count], "output=", 7) == 0) {
			// 출력 경로 추출
			char* output_path = compiler_option[count] + 7;
			// 출력 경로 설정 로직 구현
		}
		// type 옵션 처리
		else if (strncmp(compiler_option[count], "type=", 5) == 0) {
			// 타입 추출
			char* type_value = compiler_option[count] + 5;
			// 타입 설정 로직 구현
		}
		// optimize 옵션 처리
		else if (strncmp(compiler_option[count], "optimize=", 9) == 0) {
			// 최적화 레벨 추출
			char* optimize_level = compiler_option[count] + 9;
			// 문자열을 숫자로 변환하기
			int opt_level = 0;
			if (strcmp(optimize_level, "none") == 0) {
				opt_level = 0;
			}
			else if (strcmp(optimize_level, "basic") == 0) {
				opt_level = 1;
			}
			else if (strcmp(optimize_level, "full") == 0) {
				opt_level = 2;
			}

			// 최적화 설정 로직 구현
		}
		// debug 옵션 처리
		else if (strncmp(compiler_option[count], "debug=", 6) == 0) {
			// 디버그 정보 포함 여부 추출
			char* debug_value = compiler_option[count] + 6;
			int debug_flag = (strcmp(debug_value, "true") == 0) ? 1 : 0;
			// 디버그 설정 로직 구현
		}
		else{
			// 알 수 없는 옵션 처리
		}
	}
	// todo: 옵션 처리 로직 구현

	return 0;

	//
}

#endif //NO_BANARY
#endif



// Created by Fuchsua on 2022-10-13 22:23:28.