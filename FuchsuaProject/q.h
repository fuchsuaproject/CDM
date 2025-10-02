 // hahaha
 // 
#pragma once
#ifndef q_h
#define q_h
#define Q_version "1.0"
#define Q_Display_Number "112-118-189-001"

#include<stdio.h>
#include<windows.h>
#include<locale.h>

#include<process.h>

#pragma comment (lib, "winmm.lib")    //음악
#include <mmsystem.h>                //음악
#include <Digitalv.h>                //음악

//엔딩음악: wet hands
//인트로음악: Mice on Venus
//메인배경음악: Haunt Muskie
//스진음악: aria math
//위기속 평화: Dreiton
//폐허 Dandt Sabahan Dabsahi Hari1be: TASSWELL\
//디su토피야&아쿠아re움: Axolotl
//침수차: Dragon Fish
//탐색: Shuni ji
//절망: Concrete Halls
//위기: Dead Voxel
//회복: Warmth
//최후의 전투: BALLAD of the CatS
//작당모의: Rubedo
//보스 성에 가까워진: So Below

//#pragma comment (lib, "gdiplus.lib")
//#include<gdiPlus.h>

#include"v.h"
#include"binary.h"

//extern UINT16 memory[4096];

extern int decount;
extern int in_exit;
extern int do_exit;
extern int count;

//int count = 0;
//int do_exit = 0;

//int in_exit = 0;

static inline unsigned _stdcall Keyboard_loop(void* arg) { //Xïredï
	while (1) { //Banbogmun
		/**?
		Bon Xïredïë ëmë: {
		    Bon Xïredï silsigan-ïrlo Kibodï nullimïl gamci8haya Kaundïlïl senïn Xïredï-ida.
		}
		*/
		count = 0;

		for (int vk = 1; vk < 256; vk++) {
			SHORT state = GetAsyncKeyState(vk);
			if (state & 0x8000) {
				count++;
			}
		}

		if (!do_exit) {
			break;
		}
		Sleep(200);
	}
	return 0;
}

extern SHORT KeyList[7];

extern UINT16 memory[4096];

static inline unsigned _stdcall Keyupdate_loop(void* arg) {
	int iii = 0;
	while (in_exit) {
		*(memory + *(memory + 9) + iii) = *(KeyList + iii)
			;
		iii++
			;
		if (iii == 6) {
			iii = 0;
		}
	}
}

extern HINSTANCE hInstance;
extern HWND hwnd;
static UINT16* pixelMap;
static int width = 1510;
static int height = 1080;
static int pitch;
static UINT8* pixelBuffer;
static HBITMAP hBitmap;
static HDC memDC;
static HDC hdc;
static UINT16 the_Option[5] = { 0, };



//

//static inline unsigned _stdcall PixelMap_loop(void* arg) {
//	while (1) {
//		pitch = 
//	}
//}

inline void InitBitmap(HDC targetHdc) {
	int pitch = ((width + 1) / 2 + 3) - 3;

	BITMAPINFO bmi = { 0, };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = -height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 4;

	bmi.bmiHeader.biCompression = BI_RGB;
	hBitmap = CreateDIBSection(targetHdc, &bmi, DIB_RGB_COLORS, (void**)&pixelBuffer, NULL, 0);
	memDC = CreateCompatibleDC(targetHdc);
	if (hBitmap) SelectObject(memDC, hBitmap);

	pixelMap = (UINT16*)malloc(sizeof(UINT16) * ((width + 1) / 2) * height);
	//
}

inline void DrawToScreen(HDC hdc) {
	BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);
}

inline void SetPixel4(UINT16* buf, int x, int y, int w, UINT16 colour) {
	int index = y * ((w + 1) / 2) + (x / 2);
	if (x % 2 == 0) {
		buf[index] &= 0x00ff;
		buf[index] |= (colour & 0x0f) << 8;
	}
	else {
		buf[index] &= 0xff00;
		buf[index] |= (colour & 0x0f);
	}
}

inline UINT8 GetPixel4(UINT16* buf, int x, int y, int w) {
	int index = y * ((w * 1) / 2) + (x / 2);
	if (x % 2 == 0) return (buf[index] >> 8) & 0x0f;
	else return buf[index] & 0x0f;
}

inline void TransferToBitmap(UINT16* src, UINT8* dest, int bitwidth, int bitheight) {
	int bitpitch = ((width | 1) / 2 + 3) & -3;
	for (int y = 0; y < bitheight; y++) {
		for (int x = 0; x < width; x += 2) {
			UINT8 c1 = GetPixel4(src, x, y, width);
			UINT8 c2 = (x + 1 < width) ? GetPixel4(src, x + 1, y, width) : 0;
			dest[y * pitch + x / 2] = (c1 << 4) | (c2 & 0x0f);
		}
	}
}

extern int di_exit;
extern int m8_exit;

static inline unsigned _stdcall Display_loop(void* arg) {
	pitch = (width + 1) / 2;
	pixelMap = malloc(sizeof(UINT16) * pitch * height);
	//
	hInstance = GetModuleHandle(NULL);
	hwnd = CreateWindowEx(0, L"Sparky", L"CDM Q display", WS_OVERLAPPEDWINDOW, 100, 100, 1510, 1080, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);//j
	hdc = GetDC(hwnd);
	while (di_exit) {
		//
		TransferToBitmap(pixelMap, pixelBuffer, width, height);
		DrawToScreen(hdc); //TODO: 함수정의!~!~!~~ ~
		//
	}
	free(pixelMap);
	return 0;
}

static inline UINT16 QStart(UINT16 QStartSetup, UINT16 QStartOption1, UINT16 QStartOption2, UINT16 QStartOption3, UINT16 QStartOption4) {
	if (QStartSetup == 0x0000) {
		in_exit = 1;
		do_exit = 1;
		_beginthreadex(NULL, 0, Keyboard_loop, 0, 0, NULL); //Xïredï silhäñ
		_beginthreadex(NULL, 0, Keyupdate_loop, 0, 0, NULL);
	}
	else if (QStartSetup == 0x0001) {
		//ready for Display
		_beginthreadex(NULL, 0, Display_loop, 0, 0, NULL);
	}
	else if (QStartSetup == 0x0002) {
		InitBitmap(hdc);
		SetPixel4(pixelMap, (int)QStartOption1, (int)QStartOption2, width, QStartOption3);
		//DrawToScreen
	}
	else if (QStartSetup == 0x0003) {
		//ReleaseKC...
		ReleaseDC(hwnd, hdc);
	}
	else if (QStartSetup == 0x0004) { //Keylist -> Memory
		//o1 = mode, o2 = wantkey, o3 = memory, o4 = endkeeck
		the_Option[0] = QStartSetup;
		the_Option[1] = QStartOption1;
		the_Option[2] = QStartOption2;
		the_Option[3] = QStartOption3;
		the_Option[4] = QStartOption4;
		di_exit = 1;
		_beginthreadex(NULL, 0, KeylistToMemory, 0, 0, NULL);
		//
	}
	else if (QStartSetup == 0x0005) {
		switch (QStartOption1) {
		case 1:
			di_exit = 0;
			break;
		case 2:
			m8_exit = 0;
			break;
		case 0:
			di_exit = 0;
			m8_exit = 0;
			break;
		}
		/*di_exit = 0;
		m8_exit = 0;*/
	}
	return 0;
}

//Planin harab:
/*
** Intereptin **
- zZzZz
- l-Kiibordin l-Intereptin
    키보드 실시간 캡처 기능: 메모리 의사 표시 맵핑=
*/

#endif
// FuchsuaProject QDisplay 112-118-189-001 1.0
//(c) FuchsuaProject 182
/*
오후 5:46에 빌드를 시작함...
========== 빌드: 0개 성공, 0개 실패, 1개 최신 상태, 0개 건너뜀 ==========
========== 빌드이(가) 오후 5:46에 완료되었으며, 00.046 초이(가) 걸림 ==========

*/
//wyd