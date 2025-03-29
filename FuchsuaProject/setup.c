#include"v.h"

int find_enter(char _strings[2048], int _count);


#define crdir(a) CreateDirectory(#a, NULL)
#define CRDIR(A) crdir(A)


int cdm_Setup() {
	CreateDirectoryW(L"C:\\CDM\\", NULL);
	CreateDirectoryW(L"C:\\CDM\\STARTPICK\\", NULL);
	CreateDirectoryW(L"C:\\CDM\\PROGRAMS\\", ((void*)0));
	CreateDirectoryW(L"C:\\CDM\\PROGRAMS\\UNZIPER\\", ((void*)0));
	CreateDirectoryW(L"C:\\CDM\\PROGRAMS\\PLUGGER\\", ((void*)0));

	FILE* pSetupDirectory = _wfopen(L".\\STORE\\Directory.list", L"r, ccs=UTF-16LE");
	wchar_t DirectoryWide[260] = {0,};

	while (1) {
		if(fgetws(DirectoryWide, 260, pSetupDirectory) != NULL)
		{
			DirectoryWide[wcscspn(DirectoryWide, L"\n")] = L'\0';
			CreateDirectory(DirectoryWide, NULL);
		}
		if (wcscmp(DirectoryWide, L"END") == 0) {
			break;
		}
	}

	fclose(pSetupDirectory);
	
	FILE* pSetupBatch = fopen("CDMSETUP.BAT", "r");
	if (pSetupBatch == NULL) {
		pSetupBatch = fopen("CDMSETUP.BAT", "w");
		fprintf(pSetupBatch, "@title CDM_SETUP_PROGRAM_1_0\n@color 17\n@echo %%cd%%\\* > baseDir.cdm\n@exit");
		fclose(pSetupBatch);
	}
	system("start CDMSETUP.BAT");
	system("powershell -command \"Install-Module -Name ps2exe -Force -SkipPublisherCheck\"");
	system("powershell -command \"Invoke-PS2EXE .\\STORE\\unziper.ps1 .\\unziper.exe\"");
	/*system("echo �� ���α׷��� ��ġ��θ� �Է��ϼ���.\n");
	system("set /p installD=>");*/
	system("echo %installD% > .\\STORE\\installD");
	FILE* FindFileSet = fopen(".\\STORE\\Library.list", "r");
	if (FindFileSet == NULL) {
		wprintf(L"setupdirectory/STORE/Library.list�� �������� �ʽ��ϴ�.\n");
		return 1;
	}
	else {
		char installD_Buffer[2048] = { 0, };
		installD_Buffer[0] = fgetc(FindFileSet);
		int ifor = 1;
		while (installD_Buffer[ifor] != EOF) {
			/// int it = 0;
			installD_Buffer[ifor] = fgetc(FindFileSet);
			putch(installD_Buffer[ifor]);
			if (installD_Buffer[ifor] == -1) {
				break;
			}
			ifor++;
		}
		for (int i = 1; find_enter(installD_Buffer, i + 3) != -1; i += 3) {
			char buffer1[260] = { 0, };
			char buffer2[260] = { 0, };
			for (int j = find_enter(installD_Buffer, i); j != (find_enter(installD_Buffer, i + 1) - 1); j++) {
				buffer1[j - find_enter(installD_Buffer, i)] = installD_Buffer[j];
			}
			for (int j = find_enter(installD_Buffer, i + 1); j != (find_enter(installD_Buffer, i + 2) - 1); j++) {
				buffer2[j - find_enter(installD_Buffer, i)] = installD_Buffer[j];
			}
			wchar_t wbuffer1[260] = { 0, };
			wchar_t wbuffer2[260] = { 0, };
			mbstowcs(wbuffer1, buffer1, 260);
			mbstowcs(wbuffer2, buffer2, 260);
			BOOL f = CopyFile(wbuffer1, wbuffer2, TRUE);
			if (!f) {
				wprintf(L"�����Ϸ��� ��ο� �̹� ������ �ְų�, ���� ����� �����ϴ�.\n");
				continue;
			}
			else {
				//
				wprintf(L"Copied The File\n");
			}
			wprintf(L"��ġ�� �����Ͽ����ϴ�.");
		}
		fclose(FindFileSet);
		system("start C:\\CDM\\STARTPICK\\CDM.EXE");
	}
	return 0;
}

int find_enter(char _strings[2048], int _count) {
	int _____ = 1;
	int count_ = 0;
	while (1) {
		if (count_ == 1) {
			return -1;
		}
		if (_strings[_____] == '\0') {
			count_++;
		}
		if (_strings[_____] == '\n') {
			_____ += 1;
		}
		if (_____ == _count) {
			return _____;
		}
	}
}

//print('dsfjaklsdjfkl' + 'asdfdsaf')
//dsfjaklsdjfklasdfdsaf

//printf("%s%s", "a", "A");
//aA

//%�� ����ϰ� ���������� %%�� ����.