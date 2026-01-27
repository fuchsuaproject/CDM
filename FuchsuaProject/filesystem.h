// CSFS(Cake Standard File System) 파일 시스템 헤더 파일

/*
CSFS란?
CSFS(Cake Standard File System)는 Cake 표준(QST-1001-4359)의 파일 시스템입니다.
이 파일 시스템은 QST(Q Standard Table)에서 정의한 규격을 준수하며,
Cake 표준을 따르는 운영 체제 및 관련 소프트웨어에서 사용됩니다.
CSFS는 FAT(File Allocation Table)와 유사한 구조를 가지고 있으며,
파일 및 디렉토리 관리를 위한 다양한 기능을 제공합니다.
CSFS의 주요 특징:
- 파일 및 디렉토리 관리: 파일 생성, 읽기, 쓰기, 삭제, 디렉토리 생성 및 탐색 기능을
제공합니다.
- 파일 할당 테이블: 파일의 저장 위치를 관리하는 할당 테이블을 사용하여,
효율적인 파일 관리를 지원합니다.
- 호환성: Cake 표준을 따르는 다양한 운영 체제 및 소프트웨어와 호환됩니다.
- 확장성: 향후 기능 추가 및 개선을 위한 확장성을 고려하여 설계되었습니다.
CSFS는 Cake 표준을 따르는 시스템에서 안정적이고 효율적인 파일 관리를
제공하기 위해 개발되었습니다.
작성자: FuchsuaProject lo99r

Q: 왜 NKB에서 CSFS를 사용하나요?
A: NKB는 Cake 표준을 준수하는 언어로, CSFS를 사용함으로써
Windows외 다양한 운영 체제에서 일관된 파일 시스템 접근 방식을 제공할 수 있습니다.
Q: CSFS의 주요 기능은 무엇인가요?
A: CSFS는 파일 및 디렉토리 관리, 파일 할당 테이블 관리,
호환성 및 확장성을 주요 기능으로 제공합니다.
*/

/*
CSPT란?
CSPT(Cake Standard Partition Table)는 Cake 표준(QST-1001-4359)의 파티션 테이블입니다.
이 파티션 테이블은 QST(Q Standard Table)에서 정의한 규격을 준수하며,
Cake 표준을 따르는 운영 체제 및 관련 소프트웨어에서 사용됩니다.
CSPT는 MBR(Master Boot Record) 및 GPT(GUID Partition Table)의 특징을
참고한 구조를 가지고 있으며, 디스크 파티션 관리를 위한 다양한 기능을 제공합니다.
CSPT의 주요 특징:
- 파티션 관리: 파티션 생성, 삭제, 크기 조정 및 탐색 기능을 제공합니다.
- 파티션 테이블: 디스크의 파티션 정보를 관리하는 테이블을 사용하여,
효율적인 파티션 관리를 지원합니다.
- 호환성: Cake 표준을 따르는 다양한 운영 체제 및 소프트웨어와 호환됩니다.
- 확장성: 향후 기능 추가 및 개선을 위한 확장성을 고려하여 설계되었습니다.
- 부팅: CSPT는 MBR과 같이 부팅 정보를 포함할 수 있어,
Maple Firmware가 이를 읽고 부팅할 수 있습니다.
- 디스크 레이블: CSPT는 디스크 라벨 정보를 포함하여,
사용자가 디스크를 쉽게 식별할 수 있도록 합니다.
CSPT는 Cake 표준을 따르는 시스템에서 안정적이고 효율적인 디스크 파티션 관리를
제공하기 위해 개발되었습니다.
작성자: FuchsuaProject lo99r
*/

// Table 목차
// 1. CSFS 오브셋 표
// 2. CSFS 클러스터 비트셋
// 3. CSFS 디렉토리 엔트리 구조체
// 4. CSFS 파일 엔트리 구조체
// 5. CSPT 오브셋 표

// ልፕዬ ቆት
// 1. ከቀሀተ ኦብሰት ቆት
// 2. ከቀሀተ ክላስተር ቢትሰት
// 3. ከቀሀተ ዲረክቶሪ ኤንትሪ ንብድከለ
// 4. ከቀሀተ ህዋይል ኤንትሪ ንብድከለ
// 5. ከቀፐቀ ኦብሰት ቆት

/*
CSFS 오브셋 표

Offset | Name                | Size (bytes) | Description
-------|---------------------|--------------|--------------------------------
0x0000 | Magic Nober         | 4            | 파일 시스템 식별자 (예: "CSFS")
0x0004 | Maple Start Claster | 4            | 파일 할당 테이블 시작 클러스터
0x0008 | Sector Size         | 2            | 섹터 크기 (바이트 단위)
0x000A | Claster Secter      | 1            | 클러스터당 섹터 수
0x000B | Reserved            | 7            | 예약 영역
0x0012 | Total Sectors       | 8            | 전체 섹터 수
0x001A | Partition GUID      | 16           | 파티션 고유 식별자
0x002A | Disk Label          | 11           | 디스크 라벨 (NULL 종료 문자열)
0x0035 | Reserved            | 1            | 예약 영역
0x0036 | File System Version | 4            | 파일 시스템 버전
0x003A | Used Sectors        | 8            | 사용된 섹터 수
0x0042 | Free Sectors        | 8            | 남은 섹터 수
0x004A | Total Clasters      | 8            | 전체 클러스터 수
0x0052 | RDC                 | 4            | 루트 디렉토리 클러스터
0x0056 | Reserved            | 202          | 예약 영역
* 총 크기: 256 바이트
*/

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

/*
CSFS Directory Entry Structure

Offset | Name              | Size (bytes) | Description
-------|-------------------|--------------|-------------------------------
0x00   | Directory Name    | 32           | 디렉토리 이름 (NULL 종료 문자열)
0x20   | Creation Time     | 8            | 디렉토리 생성 시간 (타임스탬프)
0x28   | Modification Time | 8            | 디렉토리 수정 시간 (타임스탬프)
0x30   | First Claster     | 4            | 디렉토리의 첫 번째 클러스터
0x34   | Reserved          | 4            | 예약 영역
* 총 크기: 56 바이트
*/

/*
CSFS File Entry Structure

Offset | Name              | Size (bytes) | Description
-------|-------------------|--------------|-------------------------------
0x00   | File Name         | 32           | 파일 이름 (NULL 종료 문자열)
0x20   | File Size         | 8            | 파일 크기 (바이트 단위)
0x28   | Creation Time     | 8            | 파일 생성 시간 (타임스탬프)
0x30   | Modification Time | 8            | 파일 수정 시간 (타임스탬프)
0x38   | First Claster     | 4            | 파일의 첫 번째 클러스터
0x3C   | Reserved          | 4            | 예약 영역
* 총 크기: 64 바이트
*/

/*
CSPT Offset Table

Offset | Name                 | Size (bytes) | Description
-------|----------------------|--------------|-------------------------------
0x0000 | Partition Table Sig  | 8            | 파티션 테이블 식별자 (예: "CSPTBL")
0x0008 | Total Partitions     | 4            | 전체 파티션 수
0x000C | Partition Entries    | 244          | 파티션 엔트리 배열 (8개 엔트리, 각 32바이트)
0x00FC | BOOT BINARY          | 256          | 부팅 바이너리 데이터
* 총 크기: 512 바이트
*/

/*
CSPT Partition Entry Structure

Offset | Name             | Size (bytes) | Description
-------|------------------|--------------|-------------------------------
0x00   | Partition Type   | 1            | 파티션 유형 (예: 0x01 = CSFS)
0x01   | Reserved         | 3            | 예약 영역
0x04   | Start Sector     | 8            | 파티션 시작 섹터
0x0C   | Total Sectors    | 8            | 파티션 전체 섹터 수
0x14   | Partition Label  | 11           | 파티션 라벨 (NULL 종료 문자열)
0x1F   | Reserved         | 1            | 예약 영역
* 총 크기: 32 바이트
*/

// CSFS 및 CSPT에 대한 자세한 내용은 FuchsuaProject의 공식 문서를 참고하시기 바랍니다.

/*
ከቀሀተ ኦብሰት ቆት

offset | Name                | Size (bytes) | Description
-------|---------------------|--------------|--------------------------------
0x0000 | Magic Nober         | 4            | hwåyl kråt (eg: "CSFS")
0x0004 | Maple Start Claster | 4            | hwåyl nuhh qot råśat klåstar
0x0008 | Sector Size         | 2            | såktar keberkala (xedyë båyt)
0x000A | Claster Secter      | 1            | klåstar saktar leb
0x000B | Reserved            | 7            | qot beh
0x0012 | Total Sectors       | 8            | kål saktar leb
0x001A | Partition GUID      | 16           | partiśurn taxad kråt
0x002A | Disk Label          | 11           | disk śem (NULL qemet medåt)
0x0035 | Reserved            | 1            | qot beh
0x0036 | File System Version | 4            | hwåyl tamaril barzurn
0x003A | Used Sectors        | 8            | saktar moshyum leb
0x0042 | Free Sectors        | 8            | saktar nbåm leb
0x004A | Total Clasters      | 8            | kål klåstar leb
0x0052 | RDC                 | 4            | rut diraktori klåstar
0x0056 | Reserved            | 202          | qot beh
* kål keberkala: 256 båyt
*/

#pragma once
// 여기에서는 Cake Standard를 따르는 가상 디스크를 관리하는 함수들을 선언합니다.
#ifndef filesystem_h
#define filesystem_h
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<io.h>
#include"v.h"
#include<malloc.h>

char cdm_FileExists(char* filename);// 파일 존재 여부 확인
char* cdm_ReadFile(char* filename);// 파일 읽기
void cdm_WriteFile(char* filename, char* data);// 파일 쓰기

// 파일 시스템 함수들
void formatDisk(FILE* diskFile, int totalSectors, int sectorSize);
int createFile(FILE* diskFile, char* filename, char* data);
char* readFile(FILE* diskFile, char* filename);
int deleteFile(FILE* diskFile, char* filename);
void listFiles(FILE* diskFile);
void defragmentDisk(FILE* diskFile);
void mountDisk(char* diskImagePath);
void createDirectory(char* dirName);

// Partition 함수들
char createPartition(FILE* diskFile, int partitionNumber, unsigned long long startSector, unsigned long long totalSectors, char* partitionLabels);
char deletePartition(FILE* diskFile, int partitionNumber, unsigned long long startSector);
char listPartitions(FILE* diskFile);
char resizePartition(FILE* diskFile, int partitionNumber, unsigned long long newTotalSectors);
char formatPartition(FILE* diskFile, int totalSectors, int partitionNumber, char* partitionLabel);

// 요아니 요요아니 요요요아니 요요요요아니 요요요요요아니



// 섹터 읽기/쓰기 함수들
char* ReadSector(FILE* diskFile, int sectorNumber);
char WriteSector(FILE* diskFile, int sectorNumber, char* data);
unsigned short getSectorSize(FILE* diskFile);
unsigned short getClusterSectorCount(FILE* diskFile, int partitionNumber);
unsigned long long getTotalSectors(FILE* diskFile, int partitionNumber);
unsigned long long getFreeSectors(FILE* diskFile);
unsigned int getRootDirectoryCluster(FILE* diskFile);

// 섹터 크기 임시
unsigned short sectorSizeTemp(unsigned short sectorSize, char* buffer);

// Functions about CSPT
char createCSPT(FILE* diskFile);
char deleteCSPT(FILE* diskFile);
char createCSPTPartition(FILE* diskFile, int partitionNumber, unsigned long long startSector, unsigned long long totalSectors, char* partitionLabel);
char deleteCSPTPartition(FILE* diskFile, int partitionNumber);
char listCSPTPartitions(FILE* diskFile, char* retuenStr);
char resizeCSPTPartition(FILE* diskFile, int partitionNumber, unsigned long long newTotalSectors);
char formatCSPTPartition(FILE* diskFile, int totalSectors, int partitionNumber, char* partitionLabel);
char setCSPTBootBinary(FILE* diskFile, char* bootBinaryPath);
char getCSPTBootBinary(FILE* diskFile, char* outputPath);
char setCSPTDiskLabel(FILE* diskFile, char* diskLabel);
char getCSPTDiskLabel(FILE* diskFile, char* buffer, int bufferSize);

// 추가적인 파일 시스템 함수들 선언
void changeDirectory(char* path);
void getCurrentDirectory(char* buffer, int bufferSize);
void deleteDirectory(char* dirName);
void listDirectories();
void logFileSystemOperation(const char* operation, const char* details);

// 파일 및 디렉토리 구조체 정의
// CSFS header
//#pragma pack(push, 1) // 구조체의 바이트 정렬을 1바이트로 설정
typedef struct {
	char magicNumber[4];          // 파일 시스템 식별자 (예: "CSFS")
	unsigned int mapleStartCluster; // 파일 할당 테이블 시작 클러스터
	unsigned short sectorSize;     // 섹터 크기 (바이트 단위)
	unsigned char clusterSector;   // 클러스터당 섹터 수
	char reserved1[7];            // 예약 영역
	unsigned long long totalSectors; // 전체 섹터 수
	unsigned char partitionGUID[16]; // 파티션 고유 식별자
	char diskLabel[11];           // 디스크 라벨 (NULL 종료 문자열)
	char reserved2[1];            // 예약 영역
	unsigned int fileSystemVersion; // 파일 시스템 버전
	unsigned long long usedSectors;  // 사용된 섹터 수
	unsigned long long freeSectors;  // 남은 섹터 수
	unsigned long long totalClusters; // 전체 클러스터 수
	unsigned int rdc;             // 루트 디렉토리 클러스터
	char reserved3[202];          // 예약 영역
}csfs_Header __attribute__((packed));

// CSFS Claster Bitset
typedef struct {
	unsigned long long nextCluster : 32; // 다음 클러스터 (32비트)
	unsigned long long endOfFile : 1;    // 파일의 끝을 나타내는 비트
	unsigned long long directory : 1;     // 디렉토리 여부를 나타내는 비트
	unsigned long long used : 1;          // 클러스터가 사용 중인지 여부
	unsigned long long reserved : 29;     // 예약 비트
}csfs_ClusterBitset __attribute__((packed));

// CSFS Directory Entry Structure
typedef struct {
	char directoryName[32];       // 디렉토리 이름 (NULL 종료 문자열)
	unsigned long long creationTime; // 디렉토리 생성 시간 (타임스탬프)
	unsigned long long modificationTime; // 디렉토리 수정 시간 (타임스탬프)
	unsigned int firstCluster;    // 디렉토리의 첫 번째 클러스터
	char reserved[4];             // 예약 영역
}csfs_DirectoryEntry __attribute__((packed));

// CSFS File Entry Structure
typedef struct {
	char fileName[32];           // 파일 이름 (NULL 종료 문자열)
	unsigned long long fileSize;  // 파일 크기 (바이트 단위)
	unsigned long long creationTime; // 파일 생성 시간 (타임스탬프)
	unsigned long long modificationTime; // 파일 수정 시간 (타임스탬프)
	unsigned int firstCluster;    // 파일의 첫 번째 클러스터
	char reserved[4];             // 예약 영역
}csfs_FileEntry __attribute__((packed));

// CSPT Offset Table
typedef struct {
	char partitionTableSig[8];   // 파티션 테이블 식별자 (예: "CSPTBL")
	unsigned int totalPartitions; // 전체 파티션 수
	char partitionEntries[244];   // 파티션 엔트리 배열 (8개 엔트리, 각 32바이트)
	char bootBinary[256];         // 부팅 바이너리 데이터
}cspt_OffsetTable __attribute__((packed));

// CSPT Partition Entry Structure
typedef struct {
	unsigned char partitionType;  // 파티션 유형 (예: 0x01 = CSFS)
	char reserved[3];             // 예약 영역
	unsigned long long startSector; // 파티션 시작 섹터
	unsigned long long totalSectors; // 파티션 전체 섹터 수
	char partitionLabel[11];      // 파티션 라벨 (NULL 종료 문자열)
	char reserved2[1];            // 예약 영역
}cspt_PartitionEntry __attribute__((packed));
//#pragma pack(pop) // 원래의 바이트 정렬로 복원

// 추가적인 구조체들 정의
typedef struct {
	char fileName[256];
	int fileDescriptor;
	unsigned long long fileSize;
	unsigned long long currentPosition;
	int isOpen;
} OpenFileEntry;
typedef struct {
	unsigned int clusterNumber;
	char* data;
	int isDirty;
} CacheEntry;

// 함수 선언
void initializeFileSystem();
void shutdownFileSystem();

// 기타 필요한 함수들 선언
void flushFileCache();

#endif