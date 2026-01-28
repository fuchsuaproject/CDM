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

// sas

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
	fwrite(data, SECTOR_SIZE, 1, diskFile);
	// 여기에서 잘못된 것은?
	// fwrite(data, SECTOR_SIZE, sectorSize, diskFile);
	// 첫 번째 인자는 버퍼 포인터
	// 아니 일단 그래서 3번째 인자를 1로 수정해야함?
	// 맞아 3번째 인자는 블록 개수임
	// 즉, 한 번에 몇 블록을 쓸 것인지
	// 그래서 1로 해야지
	// 그러면 전체 코드 보면 이렇게 잘못된 부분이 있나?
	// 아니면 for문의 <, >, <=, >= 이런 부분이 잘못된 것이 있나?
	// A: 지금까지 본 바로는 없어 보임
	// Q: 아 그래? 그럼 다행이다
	// A: 응응
	// Q: 고마워
	// A: 천만에
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
	//entry[0]->partitionLabel
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
//todo: 파일 생성, 삭제, 수정 및 디렉토리 생성, 삭제, 수정에 관한 함수 정의

char testCreateFile() {
	mountDisk(mountedDisk, "test.np");
	// 몰라 이거 버려어어어...
	return 0;
}

char mountDisk(FILE* diskFile, char* diskImagePath) {
	char exists = cdm_FileExists(diskImagePath);
	// if문
	if (!exists) {
		return 1;
	}
	diskFile = fopen(diskImagePath, "wb+");
	return 0;
}

char formatDisk(FILE* diskFile, int totalSectors, int sectorSize) {
	// 디스크 포맷 로직 구현
	for (int i = 0; i < totalSectors; i++) {
		// 섹터 초기화
		for (int j = 0; j < sectorSize; j++) {
			sectorBuffer[j] = 0; // 버퍼 초기화
		}
		fseek(diskFile, i * sectorSize, SEEK_SET);
		fwrite(sectorBuffer, sectorSize, 1, diskFile);
		// Q: 왜 1인가?
		// A: fwrite 함수의 세 번째 인자는 쓰기 횟수입니다. 여기서는 한 번에 하나의 섹터를 쓰므로 1로 설정합니다.
		// Q: 그러면 512로 쓰면 죽나요?
		// A: 아니요, 죽지 않습니다. 하지만 그렇게 하면 512개의 섹터를 한 번에 쓰게 되어 디스크 공간을 초과할 수 있습니다.
		// Q: fwrite 함수의 두 번째 인자는 무엇인가?
		// A: fwrite 함수의 두 번째 인자는 쓰기 단위 크기입니다. 여기서는 섹터 크기만큼 씁니다.
	}
	return 0; // 성공 시 0 반환
}

/*
CSFS Claster Bitset

Bitset  | Name			         | Size (bits) | Description
--------|------------------------|-------------|-----------------------------
b0      | Cracked                | 1           | 클러스터가 손상되었는지 여부
b1-b3   | Reserved               | 3           | 예약 비트
b4-b19  | Next Cluster Top 16bit | 16          | 다음 클러스터의 상위 16비트
b20     | End of File (EOF)      | 1           | 파일의 끝을 나타내는 비트
b21     | Directory              | 1           | 디렉토리 여부를 나타내는 비트
b22     | Used                   | 1           | 클러스터가 사용 중인지 여부
b23-b47 | Reserved               | 25          | 예약 비트
b48-b63 | Next Cluster Low 9bit  | 16          | 다음 클러스터의 하위 16비트
* 총 크기: 64 비트 (8 바이트)
*/

unsigned int findPath(char* path, int* sector) {
	// 경로 파싱 전 파티션 번호 확인
	char* token = strtok(path, "/");
	if (token == NULL) {
		return 1; // 잘못된 경로
	}
	else if (strlen(token) != 1 || token[0] < '0' || token[0] > '7') {
		return 2; // 잘못된 파티션 번호
	}
	int partitionNumber = token[0] - '0';
	// 파티션 시작 섹터 계산
	unsigned long long partitionStartSector = 0;
	cspt_OffsetTable* cspt = NULL;
	ReadSector(mountedDisk, 0); // CSPT 헤더 읽기
	if (strncmp(sectorBuffer, "CSPTBL", 6) != 0) {
		return 3; // CSPT가 존재하지 않음
	}
	cspt = (cspt_OffsetTable*)sectorBuffer;// CSPT 구조체 포인터 설정
	cspt_PartitionEntry* entry = (cspt_PartitionEntry*)&cspt->partitionEntries[partitionNumber * 16];// 파티션 엔트리 포인터 설정
	partitionStartSector = entry->startSector;// 파티션 시작 섹터 설정
	unsigned long long rootDirCluster = 0;
	rootDircluster = getRootDirectoryCluster(partitionNumber, mountedDisk);
	csfs_Header* csfs = NULL;
	ReadSector(mountedDisk, partitionStartSector); // 파티션 헤더 읽기
	if (strncmp(sectorBuffer, "CSFSYS", 6) != 0) {
		return 3; // CSFS 파티션이 아님
	}
	csfs = (csfs_Header*)sectorBuffer;// CSFS 구조체 포인터 설정
	unsigned long long clusterBitSector = csfs->clusterSector / 16; // 클러스터 비트 섹터 수 계산
	unsigned long long currentSector = partitionStartSector + clusterBitSector + (rootDirCluster * getClusterSectorCount(mountedDisk, partitionNumber));// 루트 디렉터리 섹터 계산
	
	// 루트 디렉터리 클러스터 번호 가져오기 및 섹터 계산
	unsigned int rootDirCluster = getRootDirectoryCluster(partitionNumber, mountedDisk);// 루트 디렉터리 클러스터 번호 가져오기
	//unsigned long long currentSector = partitionStartSector + (rootDirCluster * getClusterSectorCount(mountedDisk, partitionNumber));// 루트 디렉터리 섹터 계산
	// 경로 파싱 및 디렉터리 탐색
	// * 모든 디렉토리 클러스터는 2개의 클러스터로 구성되어 있다.(출처: QST-1001-4359 공식 문서)
	// 1. 디렉토리 구조체가 있는 클러스터에서 FirstCluster를 읽어서 그 클러스터로
	// 2. 그 공간에는 배열이 있음
	// 3. 배열에는 디렉터리 엔트리와 파일 엔트리를 가리키는 포인터들이 있음
	// 4. 디렉터리 엔트리와 파일 엔트리를 읽어서 토큰과 비교
	// 5. 일치하는 디렉터리가 있으면 해당 디렉터리의 시작 섹터로 이동
	// 6. 없으면 오류 반환
	// 7. 다음 토큰으로 이동
	// 8. 토큰이 없을 때까지 반복
	// 9. 마지막 토큰이 파일이면 해당 파일의 시작 섹터 반환
	// 10. 마지막 토큰이 디렉터리이면 해당 디렉터리의 시작 섹터 반환
	// 11. 오류 발생 시 적절한 오류 코드 반환
	// lo99r
	ReadSector(mountedDisk, currentSector);
	csfs_DirectoryEntry* directoryEntry = (csfs_DirectoryEntry*)sectorBuffer;
	unsigned int firstCluster = directoryEntry->firstCluster; // 첫 번째 클러스터 번호
	unsigned long long firstClusterSector = partitionStartSector + clusterBitSector + (firstCluster * getClusterSectorCount(mountedDisk, partitionNumber));
	ReadSector(mountedDisk, firstClusterSector);
	unsigned int entriesClusterArray* = NULL;
	entriesClusterArray = (unsigned int)malloc(sizeof(unsigned int) * (unsigned int)sectorBuffer[0]);
	for (unsigned int i = 0; i < ((unsigned int)secterBuffer[0] / 512 + ((unsigned int)secterBuffer[1] % 512 == 0) 0 : 1); i++) {
		for (unsigned int j = 0; j < 512; j++) {
			entriesClusterArray[i * 512 + j] = sectorBuffer[j]; // 클러스터 배열에 디렉터리 및 파일 엔트리 포인터 저장
		}
	}

	// 디렉터리 탐색
	while ((token = strtok(NULL, "/")) != NULL) {
		// 디렉터리 엔트리 검색 로직 구현
		// 현재 섹터에서 디렉터리 엔트리를 읽고 토큰과 비교
		// 일치하는 디렉터리가 있으면 해당 디렉터리의 시작 섹터로 이동
		// 없으면 오류 반환

		// 초기화
		/*firstCluster = 0;
		firstClusterSector = 0;*/
		
		// if문으로 token이 NULL인지 확인
		if (token == NULL) {
			// currentSector 반환
			return currentSector;
			break; // 토큰이 없으면 종료
		}

		// for문으로 디렉터리 엔트리 검색
		for (int i = 0; i < ((unsigned int)secterBuffer[0]; i++)
		{
			// 요아니
			// 이제 배열의 포인터가 가리키는 클러스터 번호에 해당하는
			// 클러스터 비트를 읽겠습니다.
			
			// 클러스터 비트 얻기
			unsigned int entryClusterNumber = entriesClusterArray[i];
			unsigned long long entryClusterBitSector = partitionStartSector + (entryClusterNumber / (sectorSize * 8)) + clusterBitSector;
			ReadSector(mountedDisk, entryClusterBitSector);
			csfs_ClusterBit* clusterBit = (csfs_ClusterBit*)sectorBuffer;
			// 클러스터 비트에서 디렉터리 엔트리 정보 얻기
			unsigned int entryFirstCluster = (clusterBit->nextClusterTop16bit << 16) | clusterBit->nextClusterLow16bit;
			BOOL entryIsDirectory = clusterBit->directory;
			// if문으로	디렉터리인지 파일인지 확인
			if (entryIsDirectory) {
				// 디렉터리인 경우
				// 디렉터리 엔트리 읽기
				unsigned long long entryFirstClusterSector = partitionStartSector + clusterBitSector + (entryFirstCluster * getClusterSectorCount(mountedDisk, partitionNumber));
				ReadSector(mountedDisk, entryFirstClusterSector);
				csfs_DirectoryEntry* entryDirectory = (csfs_DirectoryEntry*)sectorBuffer;
				// 이름 비교
				if (strncmp(entryDirectory->fileName, token, 20) == 0) {
					// 일치하는 디렉터리 발견
					firstCluster = entryFirstCluster;
					currentSector = partitionStartSector + clusterBitSector + (firstCluster * getClusterSectorCount(mountedDisk, partitionNumber));
					ReadSector(mountedDisk, currentSector);
					break; // 다음 토큰으로 이동
				}
			}
			else {
				// 파일인 경우
				// 파일 엔트리 읽기
				unsigned long long entryFirstClusterSector = partitionStartSector + clusterBitSector + (entryFirstCluster * getClusterSectorCount(mountedDisk, partitionNumber));
				ReadSector(mountedDisk, entryFirstClusterSector);
				csfs_FileEntry* entryFile = (csfs_FileEntry*)sectorBuffer;
				// 이름 비교
				if (strncmp(entryFile->fileName, token, 20) == 0) {
					// 일치하는 파일 발견
					firstCluster = entryFirstCluster;
					currentSector = partitionStartSector + clusterBitSector + (firstCluster * getClusterSectorCount(mountedDisk, partitionNumber));
					return currentSector;
				}
			}
			// 요아니
		}
		// 이제	다음 토큰으로 이동
	}
	*sector = currentSector;
	return 0; // 성공 시 0 반환
}

// Q: 해야할일은?
// A: 1. findPath 함수 디버깅
//    2. 파일 및 디렉토리 생성, 삭제, 수정 함수 정의
//    3. 파일 및 디렉토리 관련 함수 디버깅
//    4. 전체 파일시스템 테스트
// Q: PathFind 함수 디버깅은 어떻게 하나요?
// A: 1. 다양한 경로를 입력하여 함수 호출
//    2. 반환된 섹터 번호가 올바른지 확인
//    3. 디버깅 출력을 통해 내부 상태 확인
// Q: 이제 위 PathFind 함수에서 쓰인 함수를 정의할 필요가 있나?
// A: 응, getRootDirectoryCluster, getClusterSectorCount 함수 정의 필요
// Q: 또 있어어어어???
// A: 음... 일단은 그게 다인 것 같아
unsigned int getRootDirectoryCluster(int partitionNumber, FILE* diskFile) {
	// 파티션 시작 섹터 계산
	unsigned long long partitionStartSector = 0;
	cspt_OffsetTable* cspt = NULL;
	ReadSector(diskFile, 0); // CSPT 헤더 읽기
	if (strncmp(sectorBuffer, "CSPTBL", 6) != 0) {
		return 0; // CSPT가 존재하지 않음
	}
	cspt = (cspt_OffsetTable*)sectorBuffer;// CSPT 구조체 포인터 설정
	cspt_PartitionEntry* entry = (cspt_PartitionEntry*)&cspt->partitionEntries[partitionNumber * 16];// 파티션 엔트리 포인터 설정
	partitionStartSector = entry->startSector;// 파티션 시작 섹터 설정
	csfs_Header* csfs = NULL;
	ReadSector(diskFile, partitionStartSector); // 파티션 헤더 읽기
	if (strncmp(sectorBuffer, "CSFSYS", 6) != 0) {
		return 0; // CSFS 파티션이 아님
	}
	csfs = (csfs_Header*)sectorBuffer;// CSFS 구조체 포인터 설정
	return csfs->rootDirectoryCluster; // 루트 디렉터리 클러스터 번호 반환
}
unsigned int getNextClusterNumber(FILE* diskFile, int partitionNumber, unsigned int currentCluster) {
	// 파티션 시작 섹터 계산
	unsigned long long partitionStartSector = 0;
	cspt_OffsetTable* cspt = NULL;
	ReadSector(diskFile, 0); // CSPT 헤더 읽기
	if (strncmp(sectorBuffer, "CSPTBL", 6) != 0) {
		return 0; // CSPT가 존재하지 않음
	}
	cspt = (cspt_OffsetTable*)sectorBuffer;// CSPT 구조체 포인터 설정
	cspt_PartitionEntry* entry = (cspt_PartitionEntry*)&cspt->partitionEntries[partitionNumber * 16];// 파티션 엔트리 포인터 설정
	partitionStartSector = entry->startSector;// 파티션 시작 섹터 설정
	csfs_Header* csfs = NULL;
	ReadSector(diskFile, partitionStartSector); // 파티션 헤더 읽기
	if (strncmp(sectorBuffer, "CSFSYS", 6) != 0) {
		return 0; // CSFS 파티션이 아님
	}
	csfs = (csfs_Header*)sectorBuffer;// CSFS 구조체 포인터 설정
	unsigned long long clusterBitSector = csfs->clusterSector / 16; // 클러스터 비트 섹터 수 계산
	unsigned long long clusterBitOffsetSector = partitionStartSector + clusterBitSector + (currentCluster / (sectorSize * 8));
	ReadSector(diskFile, clusterBitOffsetSector);
	csfs_ClusterBit* clusterBit = (csfs_ClusterBit*)sectorBuffer;
	unsigned int nextClusterNumber = (clusterBit->nextClusterTop16bit << 16) | clusterBit->nextClusterLow16bit;
	return nextClusterNumber;
}