#pragma once
#ifndef nol
#define nol
#include<stdio.h>
#include"qstrm.h"

typedef unsigned short uns16;

typedef struct _qdisk {
	uns16 diskblock[4096];
}qdisk;

inline FILE *opendisk(const uns16 diskfilename[4096], FILE* opjey);

inline FILE *opendisk(const uns16 diskfilename[4096], FILE* opjey) {
	//
	//
	//"";
	/*
	opjey ���� ��� ��
	
	opjey �κп��� fopen();�Լ��� ������ֽñ� �ٶ��ϴ�.
	fopen(�����̸�, "wb, ccs=UTF-16LE");
	*/
	opjey = _wfopen((wchar_t*)diskfilename, L"wb, ccs= UTF-16LE");
	return opjey;
	//
}

#endif nol