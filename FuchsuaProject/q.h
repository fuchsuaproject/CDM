#pragma once
#ifndef q_h
#define q_h
#define Q_version "1.0"
#define Q_Display_Number "112-118-189-001"

#include<stdio.h>
#include<windows.h>
#include<locale.h>

#pragma comment (lib, "winmm.lib")    //����
#include <mmsystem.h>                //����
#include <Digitalv.h>                //����

#pragma comment (lib, "gdiplus.lib")
#include<gdiPlus.h>

extern UINT16 memory[4096];

inline UINT16 QStart(UINT16 QStartSetup) {
	if (QStartSetup == 0x0000) {

	}
}

#endif
// FuchsuaProject QDisplay 112-118-189-001 1.0
//(c) FuchsuaProject 182
/*
���� 5:46�� ���带 ������...
========== ����: 0�� ����, 0�� ����, 1�� �ֽ� ����, 0�� �ǳʶ� ==========
========== ������(��) ���� 5:46�� �Ϸ�Ǿ�����, 00.046 ����(��) �ɸ� ==========

*/