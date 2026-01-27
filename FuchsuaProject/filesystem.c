//여기에서는 변수만 선언합니다.
#include "filesystem.h"
#define SECTOR_SIZE 512
//필요한 변수 선언

char* sectorBuffer = NULL;

FILE* mountedDisk = NULL;
char* mountedDiskName = NULL;
char currentDirectory[256] = "/";
int sectorSize = 512;
int totalSectors = 1024;
int freeSectors = 0;
int usedSectors = 0;
int fileCount = 0;
FileEntry* fileEntries = NULL;
int directoryCount = 0;
DirectoryEntry* directoryEntries = NULL;
int isDiskMounted = 0;
char mountedDiskLabel[32] = "";
int mountedDiskTotalSectors = 0;
int mountedDiskSectorSize = 0;
int mountedDiskFreeSectors = 0;
int mountedDiskUsedSectors = 0;
int mountedDiskFileCount = 0;
FileEntry* mountedDiskFileEntries = NULL;
int mountedDiskDirectoryCount = 0;
DirectoryEntry* mountedDiskDirectoryEntries = NULL;
HANDLE diskMutex; // 디스크 접근 동기화를 위한 뮤텍스
int isDiskFormatted = 0; // 디스크 포맷 여부 확인 변수
int lastErrorCode = 0; // 마지막 오류 코드 저장 변수
char lastErrorMessage[256] = ""; // 마지막 오류 메시지 저장 변수
int autoSaveInterval = 0; // 자동 저장 간격 (초 단위)
int isAutoSaveEnabled = 0; // 자동 저장 활성화 여부
HANDLE autoSaveThreadHandle = NULL; // 자동 저장 스레드 핸들
DWORD autoSaveThreadId = 0; // 자동 저장 스레드 ID
char mountedDiskPath[260] = ""; // 마운트된 디스크 이미지 경로 저장 변수
int enableLogging = 0; // 로깅 활성화 여부
char logFilePath[260] = "filesystem.log"; // 로그 파일 경로
HANDLE logFileHandle = NULL; // 로그 파일 핸들
CRITICAL_SECTION logCriticalSection; // 로그 기록을 위한 크리티컬 섹션
int maxOpenFiles = 10; // 최대 열 수 있는 파일 수
OpenFileEntry* openFileTable = NULL; // 열린 파일 테이블
int openFileCount = 0; // 열린 파일 수
int nextFileDescriptor = 3; // 다음 파일 디스크립터 값 (0, 1, 2는 표준 입출력용 예약)
int enableCaching = 0; // 캐싱 활성화 여부
CacheEntry* fileCache = NULL; // 파일 캐시 테이블
int cacheEntryCount = 0; // 캐시 엔트리 수
int maxCacheEntries = 100; // 최대 캐시 엔트리 수
CRITICAL_SECTION cacheCriticalSection; // 캐시 접근을 위한 크리티컬 섹션
//#endif

// 함수 정의
unsigned short sectorSizeTemp(unsigned short sectorSize, char* buffer) {
	//malloc
	buffer = (char*)malloc(sizeof(char) * sectorSize);
}
char* getLastErrorMessage() {
	return lastErrorMessage;
}
char* fileSystem_GetLastErrorMessage() {
	return lastErrorMessage;
}
char cdm_FileExists(char* filename) {
	// 파일 존재 여부 확인
	FILE* file = fopen(filename, "rb");
	if (file) {
		fclose(file);
		return 1; // 파일이 존재함
	}
	return 0; // 파일이 존재하지 않음
}
char* cdm_ReadFile(char* filename) {
	// 파일 읽기
	FILE* file = fopen(filename, "rb");
	if (file) {
		// 파일 읽기 작업 수행
		fread(NULL, 1, 0, file); // 예시로 아무 데이터도 읽지 않음
		fclose(file);
		return NULL; // 읽은 데이터 반환 (예시에서는 NULL)
	}
	return NULL; // 파일 열기 실패 시 NULL 반환
}

char cdm_WriteFile(char* filename, char* data) {
	// 파일 쓰기\j
	FILE* file = fopen(filename, "wb");
	if (file) {
		// 파일 쓰기 작업 수행
		fwrite(data, 1, strlen(data), file); // 예시로 데이터 전체를 씀
		fclose(file);
		return 1; // 쓰기 성공
	}
	return 0; // 파일 열기 실패 시 0 반환
}

char* ReadSector(FILE* diskFile, int sectorNumber) {
	if (sectorBuffer == NULL) {
		sectorSizeTemp(SECTOR_SIZE, sectorBuffer);
	}
	fseek(diskFile, sectorNumber * sectorSize, SEEK_SET);
	fread(sectorBuffer, SECTOR_SIZE, sectorSize, diskFile);
	return sectorBuffer;
}
char WriteSector(FILE* diskFile, int sectorNumber, char* data) {
	if (mountedDiskName == NULL) {
		return 1;
	}
	char fileExistsTOF = NULL;
	fileExistsTOF = cdm_FileExists(mountedDiskName);
	if (fileExistsTOF = NULL || fileExistsTOF = 1) {
		return 1;
	}
	if (sectorBuffer == NULL) {
		sectorSizeTemp(SECTOR_SIZE, sectorBuffer);
	}
	fseek(diskFile, sectorNumber * sectorSize, SEEK_SET);
	fwrite(data, SECTOR_SIZE, sectorSize, diskFile);
	return 0;
}

char createCSPT(FILE* diskFile) {
	// CSPT 생성 로직 구현
	ReadSector(diskFile, 0); // CSPT 헤더 있는지 확인
	if (strncmp(sectorBuffer, "CSPTBL", 6) == 0) {
		// 이미 CSPT가 존재함
		return 1; // 오류 코드 반환
	}
	// CSPT 생성 작업 수행
	for (int i = 0; i < SECTOR_SIZE; i++) {
		sectorBuffer[i] = 0; // 버퍼 초기화
	}
	cspt_OffsetTable* cspt = (cspt_OffsetTable*)sectorBuffer;
	strncpy(cspt->partitionTableSig, "CSPTBL", 6);
	cspt->totalPartitions = 0;
	for (int i = 0; i < 244; i++) {
		cspt->partitionEntries[i] = 0;
	}
	for (int i = 0; i < 256; i++) {
		cspt->bootBinary[i] = 0;
	}
	fseek(diskFile, 0, SEEK_SET);
	fwrite(sectorBuffer, SECTOR_SIZE, 1, diskFile);
	return 0; // 성공 시 0 반환
}

char deleteCSPT(FILE* diskFile) {
	// CSPT 삭제 로직 구현
	ReadSector(diskFile, 0); // CSPT 헤더 있는지 확인
	if (strncmp(sectorBuffer, "CSPTBL", 6) != 0) {
		// CSPT가 존재하지 않음
		return 1; // 오류 코드 반환
	}
	// CSPT 삭제 작업 수행 (섹터 초기화)
	for (int i = 0; i < SECTOR_SIZE; i++) {
		sectorBuffer[i] = 0; // 버퍼 초기화
	}
	fseek(diskFile, 0, SEEK_SET);
	fwrite(sectorBuffer, SECTOR_SIZE, 1, diskFile);
	return 0; // 성공 시 0 반환
}

char createCSPTPartition(FILE* diskFile, int partitionNumber, unsigned long long startSector, unsigned long long totalSectors, char* partitionLabel) {
	// CSPT 파티션 생성 로직 구현
	ReadSector(diskFile, 0); // CSPT 헤더 읽기
	if (strncmp(sectorBuffer, "CSPTBL", 6) != 0) {
		// CSPT가 존재하지 않음
		return 1; // 오류 코드 반환
	}
	cspt_OffsetTable* cspt = (cspt_OffsetTable*)sectorBuffer;// CSPT 구조체 포인터 설정
	if (partitionNumber < 0 || partitionNumber >= 16) {
		// 잘못된 파티션 번호
		return 2; // 오류 코드 반환
	}
	cspt_PartitionEntry* entry = (cspt_PartitionEntry*)&cspt->partitionEntries[partitionNumber * 16];
	if (entry->partitionType != 0) {
		// 이미 파티션이 존재함
		return 3; // 오류 코드 반환
	}
	entry->partitionType = 0x01; // CSFS 파티션 타입 설정
	entry->startSector = startSector;
	entry->totalSectors = totalSectors;
	strncpy(entry->partitionLabel, partitionLabel, 10);
	fseek(diskFile, 0, SEEK_SET);
	fwrite(sectorBuffer, SECTOR_SIZE, 1, diskFile);
	return 0; // 성공 시 0 반환
}
char deleteCSPTPartition(FILE* diskFile, int partitionNumber) {
	// CSPT 파티션 삭제 로직 구현
	ReadSector(diskFile, 0); // CSPT 헤더 읽기
	if (strncmp(sectorBuffer, "CSPTBL", 6) != 0) {
		// CSPT가 존재하지 않음
		return 1; // 오류 코드 반환
	}
	cspt_OffsetTable* cspt = (cspt_OffsetTable*)sectorBuffer;// CSPT 구조체 포인터 설정
	if (partitionNumber < 0 || partitionNumber >= 16) {
		// 잘못된 파티션 번호
		return 2; // 오류 코드 반환
	}
	cspt_PartitionEntry* entry = (cspt_PartitionEntry*)&cspt->partitionEntries[partitionNumber * 16];
	if (entry->partitionType == 0) {
		// 파티션이 존재하지 않음
		return 3; // 오류 코드 반환
	}
	// 파티션 엔트리 초기화
	for (int i = 0; i < 16; i++) {
		cspt->partitionEntries[partitionNumber * 16 + i] = 0;
	}
	fseek(diskFile, 0, SEEK_SET);
	fwrite(sectorBuffer, SECTOR_SIZE, 1, diskFile);
	return 0; // 성공 시 0 반환
}

char listCSPTPartitions(FILE* diskFile, char* returnStr) {
	ReadSector(diskFile, 0); // CSPT 헤더 읽기
	if (strncmp(sectorBuffer, "CSFSYS", 6)) {
		return 1;
	}
	cspt_OffsetTable* cspt = (cspt_OffsetTable)sectorBuffer;
	cspt_PartitionEntry* partitionEntries[8] = (cspt_PartitionEntry)cspt->partitionEntries;
	for (int i = 0; i < 8; i++) {
		// 각 파티션 엔트리 출력
		sprintf(returnStr + strlen(returnStr), "Partition %d: Type: 0x%02X, Start Sector: %llu, Total Sectors: %llu, Label: %s\n",
			i,
			partitionEntries[i].partitionType,
			partitionEntries[i].startSector,
			partitionEntries[i].totalSectors,
			partitionEntries[i].partitionLabel);
	}
	return 0;
}

char resizeCSPTPartition(FILE* diskFile, int partitionNumber, unsigned long long newTotalSectors) {
	// CSPT 파티션 크기 조정 로직 구현
	ReadSector(diskFile, 0); // CSPT 헤더 읽기
	if (strncmp(sectorBuffer, "CSPTBL", 6) != 0) {
		// CSPT가 존재하지 않음
		return 1; // 오류 코드 반환
	}
	cspt_OffsetTable* cspt = (cspt_OffsetTable*)sectorBuffer;// CSPT 구조체 포인터 설정
	if (partitionNumber < 0 || partitionNumber >= 16) {
		// 잘못된 파티션 번호
		return 2; // 오류 코드 반환
	}
	cspt_PartitionEntry* entry[8] = (cspt_PartitionEntry)cspt->partitionEntries;
	if (entry[partitionNumber]->partitionType == 0) {
		// 파티션이 존재하지 않음
		return 3; // 오류 코드 반환
	}
	entry->totalSectors = newTotalSectors;
	fseek(diskFile, 0, SEEK_SET);
	fwrite(sectorBuffer, SECTOR_SIZE, 1, diskFile);
	return 0; // 성공 시 0 반환
}

char formatPartition(FILE* diskFile, int totalSectors, int partitionNumber, char* partitionLabel) {
	ReadSector(diskFile, 0); // CSPT 헤더 읽기
	if (strncmp(sectorBuffer, "CSPTBL", 6) != 0) {
		return 1;
	}
	cspt_OffsetTable* cspt = (cspt_OffsetTable*)sectorBuffer;// CSPT 구조체 포인터 설정
	if (partitionNumber < 0 || partitionNumber >= 16) {
		return 2;
	}
	// entry 포인터는 2중으로 해야한다. 왜냐하면
	// entry는 8개의 엔트리로 이루어져 있고,
	// 각 엔트리는 32바이트이기 때문이다.
	cspt_PartitionEntry* entry[8] = (cspt_PartitionEntry)cspt->partitionEntries;
	if (entry[partitionNumber]->partitionType == 0) {
		return 3;
	}
	// 파티션 포맷 작업 수행
	deletePartition(diskFile, partitionNumber, entry->startSector);
	createPartition(diskFile, partitionNumber, entry->startSector, totalSectors, partitionLabel);
	return 0;
}

char setCSPTBootBinary(FILE* diskFile, char* bootBinaryPath) {
	/*
	* 주의: 부팅 바이너리 크기는 256바이트를 초과할 수 없습니다.
	* 참고: 부팅 바이너리는 Maple Firmware에서 사용됩니다.
	* 원래 본 함수에서는 부팅 바이너리가 저장된 파일을 읽어서
	  CSPT에 포함되게 해야 하지만, 현재 Maple Firmware가
	  CDM이 미완성이므로 구현되지 아니하여서 나중에	구현할 예정입니다.
	*/
	return 0; // 성공 시 0 반환
}

char getCSPTBootBinary(FILE* diskFile, char* outputPath) {
	/*
	* 주의: 부팅 바이너리 크기는 256바이트를 초과할 수 없습니다.
	* 참고: 부팅 바이너리는 Maple Firmware에서 사용됩니다.
	* 원래 본 함수에서는 CSPT에서 부팅 바이너리를 읽어서
	  지정된 경로에 파일로 저장해야 하지만, 현재 Maple Firmware가
	  CDM이 미완성이므로 구현되지 아니하여서 나중에	구현할 예정입니다.
	*/
	return 0; // 성공 시 0 반환
}

char setCSPTDiskLabel(FILE* diskFile, char* diskLabel) {
	// CSPT 디스크 라벨 설정 로직 구현
	ReadSector(diskFile, 0); // CSPT 헤더 읽기
	if (strncmp(sectorBuffer, "CSPTBL", 6) != 0) {
		// CSPT가 존재하지 않음
		return 1; // 오류 코드 반환
	}
	cspt_OffsetTable* cspt = (cspt_OffsetTable*)sectorBuffer;// CSPT 구조체 포인터 설정
	cspt_PartitionEntry* entry[8] = (cspt_PartitionEntry)cspt->partitionEntries;
	strncpy(cspt->partitionEntries, diskLabel, 10);
	fseek(diskFile, 0, SEEK_SET);
	fwrite(sectorBuffer, SECTOR_SIZE, 1, diskFile);
	return 0; // 성공 시 0 반환
}

char getCSPTDiskLabel(FILE* diskFile, char* buffer, int bufferSize) {
	ReadSector(diskFile, 0); // CSPT 헤더 읽기
	if (strncmp(sectorBuffer, "CSPTBL", 6) != 0) {
		return 1;
	}
	cspt_OffsetTable* cspt = (cspt_OffsetTable*)sectorBuffer;// CSPT 구조체 포인터 설정
	cspt_PartitionEntry* entry[8] = (cspt_PartitionEntry)cspt->partitionEntries;
	strncpy(buffer, cspt->partitionEntries, bufferSize - 1);
	buffer[bufferSize - 1] = '\0'; // NULL 종료	
	return 0;
}

char createPartition(FILE* diskFile, int partitionNumber, unsigned long long startSector, unsigned long long totalSectors, char* partitionLabel) {
	// 파티션 생성 로직 구현
	// 현재 코드에서는 partitionNumber 인자를 사용하지 않음
	ReadSector(diskFile, startSector); // 파티션 시작 섹터 읽기
	if (strncmp(sectorBuffer, "CSFSYS", 6) == 0) {
		// 이미 파티션이 존재함
		return 1; // 오류 코드 반환
	}
	for (int i = 0; i < SECTOR_SIZE; i++) {
		sectorBuffer[i] = 0; // 버퍼 초기화
	}
	csfs_Header* csfs = (csfs_Header*)sectorBuffer;
	strncpy(csfs->fileSystemSig, "CSFSYS", 6);
	csfs->sectorSize = SECTOR_SIZE;
	csfs->clusterSector = 8; // 예시로 클러스터당 8섹터 설정
	csfs->totalSectors = totalSectors;
	strncpy(csfs->diskLabel, partitionLabel, 10);
	fseek(diskFile, startSector * SECTOR_SIZE, SEEK_SET);
	fwrite(sectorBuffer, SECTOR_SIZE, 1, diskFile);
	return 0; // 성공 시 0 반환
}
char deletePartition(FILE* diskFile, int partitionNumber, unsigned long long startSector) {
	// 파티션 삭제 로직 구현
	// 현재 코드에서는 partitionNumber 인자를 사용하지 않음
	ReadSector(diskFile, startSector); // 파티션 시작 섹터 읽기
	if (strncmp(sectorBuffer, "CSFSYS", 6) != 0) {
		// 파티션이 존재하지 않음
		return 1; // 오류 코드 반환
	}
	for (int i = 0; i < SECTOR_SIZE; i++) {
		sectorBuffer[i] = 0; // 버퍼 초기화
	}
	fseek(diskFile, startSector * SECTOR_SIZE, SEEK_SET);
	fwrite(sectorBuffer, SECTOR_SIZE, 1, diskFile);
	return 0; // 성공 시 0 반환
}
//todo: createPartition, deletePartition이 createCSPTPartition, deleteCSPTPartition를 사용해야합니다.