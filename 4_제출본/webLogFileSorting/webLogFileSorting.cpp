#pragma warning(disable:4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define BUFFER_LEN 200
#define MAX_LENGTH 200
#define MAX_BREADTH 20000
#define SIZE 50
#define TIME_SIZE 10

typedef struct time {
	char day[TIME_SIZE];
	int month;	//1~12�� ����� �����ؼ� ����.
	char year[TIME_SIZE];
	char hour[TIME_SIZE];
	char min[TIME_SIZE];
	char second[TIME_SIZE];
}Time;
typedef struct webLog {
	char ipAddress[SIZE];
	char time[SIZE];
	char url[SIZE];
	char status[SIZE];
}WebLog;

char buffer[BUFFER_LEN];
char delim[] = ",[\0\n";
WebLog data[MAX_BREADTH];
int printFirst[4] = { 1,0,0,0 };	//1�� �Ǹ� ���� ���� ���. (������� ip,time,url,status)
int webLogCount = 0;	//���α��� ���� count
char category[4][SIZE];	//�ڷῡ ����ִ� ī�װ���(Ip,Time,URL,Status)

//�Լ� ����
void commandControl();
int read(char *fileName);
void print();
void printWebLog(WebLog log);
int separateMonth(char *month);
void copyTimeData(const void *p, Time *pTime);
int compareTime(const void *p, const void *q);
int compareIp(const void *p, const void *q);


void main() {
	commandControl();
}

void commandControl() {
	char buffer1[BUFFER_LEN];
	char *command = NULL, *token;
	while (1) {
		//�ʱ�ȭ
		if (command != NULL) {
			free(command);
			command = NULL;
		}
		printf("$ ");
		fgets(buffer1, SIZE, stdin);
		//�Է� ������ continue;
		if (strcmp(buffer1, "\n") == 0)
			continue;
		//fgets������ \n������ �о�鿩 �����Ƿ�, �������� \0�ٿ���
		buffer1[strlen(buffer1) - 1] = '\0';
		command = strdup(strtok(buffer1, " "));
		if (strcmp(command, "read") == 0) {
			token = strtok(NULL, "\n");
			char *fileName = strdup(token);
			if (read(fileName) == -1) {//-1������ ���� ���� ����
				free(fileName);
				continue;
			}
			free(fileName);
		}
		else if (strcmp(command, "sort") == 0) {
			char *operand = strdup(strtok(NULL, "\n"));
			//���� �����ϸ� print�ϴ� ���� �ٲ�.
			for (int i = 0; i < 4; i++)
				printFirst[i] = 0;
			//���� ����
			if (strcmp(operand, "-t") == 0) {
				printFirst[1] = 1;
				qsort(data, webLogCount, sizeof(WebLog), compareTime);
			}
			else if (strcmp(operand, "-ip") == 0) {
				printFirst[0] = 1;
				qsort(data, webLogCount, sizeof(WebLog), compareIp);
			}
			free(operand);
		}
		else if (strcmp(command, "print") == 0) {
			print();
		}
		else if (strcmp(command, "exit") == 0)
			break;
		else {
			printf("Not defined command.\n");
			continue;
		}
	}
	free(command);
}

int read(char *fileName) {
	FILE *fp = fopen(fileName, "r");
	//���� ���� ���ϸ� -1��ȯ�ϰ� ����
	if (fp == NULL) {
		printf("file open is failed.\n");
		return -1;
	}

	//ù ���� ip, time, url, status�� �̸��� ����ִ�.
	fgets(buffer, MAX_LENGTH, fp);
	buffer[strlen(buffer) - 1] = '\0';

	char *token = strtok(buffer, delim);
	strcpy(category[0], token);
	token = strtok(NULL, delim);
	strcpy(category[1], token);
	token = strtok(NULL, delim);
	strcpy(category[2], token);
	token = strtok(NULL, delim);
	strcpy(category[3], token);

	//���� ����
	while (!feof(fp)) {
		fgets(buffer, BUFFER_LEN, fp);
		buffer[strlen(buffer) - 1] = '\0';

		token = strtok(buffer, delim);
		strcpy(data[webLogCount].ipAddress, token);
		token = strtok(NULL, delim);
		strcpy(data[webLogCount].time, token);
		token = strtok(NULL, delim);
		strcpy(data[webLogCount].url, token);
		token = strtok(NULL, delim);
		strcpy(data[webLogCount].status, token);

		webLogCount++;
	}
	fclose(fp);
	return 1;
}

void print() {
	for (int i = 0; i < webLogCount; i++)
		printWebLog(data[i]);
}

void printWebLog(WebLog log) {
	for (int i = 0; i < 4; i++) {
		if (printFirst[i] == 1) {
			switch (i) {
			case 0: printf("%s\n", log.ipAddress);	break;
			case 1: printf("%s\n", log.time);	break;
			case 2: printf("%s\n", log.url);	break;
			case 3: printf("%s\n", log.status);	break;
			}
			break;
		}
	}
	for (int i = 0; i < 4; i++) {
		if(printFirst[i]!=1)
			switch (i) {
			case 0: printf("\t%s: %s\n", category[i], log.ipAddress);	break;
			case 1: printf("\t%s: %s\n", category[i], log.time);	break;
			case 2: printf("\t%s: %s\n", category[i], log.url);	break;
			case 3: printf("\t%s: %s\n", category[i], log.status);	break;
			}
	}
	

}

//Jan(1), Feb(2), Mar(3), Apr(4), May(5), Jun(6), Jul(7), Aug(8), Sep(9), Oct(10), Nov(11), Dec(12)
int separateMonth(char *month) {
	if (strcmp(month, "Jan") == 0)		return 1;
	else if (strcmp(month, "Feb") == 0)		return 2;
	else if (strcmp(month, "Mar") == 0)		return 3;
	else if (strcmp(month, "Apr") == 0)		return 4;
	else if (strcmp(month, "May") == 0)		return 5;
	else if (strcmp(month, "Jun") == 0)		return 6;
	else if (strcmp(month, "Jul") == 0)		return 7;
	else if (strcmp(month, "Aug") == 0)		return 8;
	else if (strcmp(month, "Sep") == 0)		return 9;
	else if (strcmp(month, "Oct") == 0)		return 10;
	else if (strcmp(month, "Nov") == 0)		return 11;
	else if (strcmp(month, "Dec") == 0)		return 12;
	return -1;
}

//��ũ����¡ �ؼ� �ð� ������ ī���ؼ� �ֱ�
void copyTimeData(const void *p, Time *pTime) {
	char *timeData = strdup(((WebLog *)p)->time);
	char *token = strtok(timeData, "/");
	strcpy(pTime->day, token);
	token = strtok(NULL, "/");
	pTime->month = separateMonth(token);
	token = strtok(NULL, ":");
	strcpy(pTime->year, token);
	token = strtok(NULL, ":");
	strcpy(pTime->hour, token);
	token = strtok(NULL, ":");
	strcpy(pTime->min, token);
	token = strtok(NULL, "\0");
	strcpy(pTime->second, token);

	free(timeData);
}

//time�� �������� ����,��ũ����¡ �ؼ� hour���� 
int compareTime(const void *p, const void *q) {
	Time pTime = { "",0,"","","","" };
	Time qTime = { "",0,"","","","" };
	copyTimeData(p, &pTime);
	copyTimeData(q, &qTime);
	//year, month, day, hour, min, sec
	if (strcmp(pTime.year, qTime.year) != 0)
		return strcmp(pTime.year, qTime.year);
	if (pTime.month != qTime.month)
		return pTime.month - qTime.month;
	if (strcmp(pTime.day, qTime.day) != 0)
		return strcmp(pTime.day, qTime.day);
	if (strcmp(pTime.hour, qTime.hour) != 0)
		return strcmp(pTime.hour, qTime.hour);
	if (strcmp(pTime.min, qTime.min) != 0)
		return strcmp(pTime.min, qTime.min);
	if (strcmp(pTime.second, qTime.second) != 0)
		return strcmp(pTime.second, qTime.second);
	return 0;	
}

//ip�ּҷ� ����, ���� ip�ּҶ�� �ð������� ����
int compareIp(const void *p, const void *q) {
	if (strcmp(((WebLog *)p)->ipAddress, ((WebLog *)q)->ipAddress) != 0)
		return (strcmp(((WebLog *)p)->ipAddress, ((WebLog *)q)->ipAddress));
	return compareTime(p, q);
}

