#pragma warning(disable:4996)
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define SIZE1 1000
#define SIZE2 10000
#define SIZE3 100000

//����Ʈ �� 2���� �迭�� �������� ������ �� �迭 ��� �� �� �Լ� ���ο��� ������ �־ main�� �������� ����Ʈ

int **reverseData1000;
int **reverseData10000;
int **reverseData100000;
int **randomData1000;
int **randomData10000;
int **randomData100000;
int tmp[SIZE3];
double table[9][6];

//�Լ� ����
int partition(int data[], int p, int r, int pivotIndex);
double quickSort(int data[], int p, int r);
void merge(int data[], int p, int q, int r);
double mergeSort(int data[], int p, int r);
double insertionSort(int data[], int n);
double selectionSort(int data[], int n);
double bubbleSort(int data[], int n);
void makeReverseDatas();
void makeRandomDatas(int **data, int N);
void swap(int data[], int index1, int index2);
int middle(int data[], int index1, int index2, int index3);
double middlePivotQuickSort(int data[], int p, int r);
double randomPivotQuickSort(int data[], int p, int r);
void tableReset();
void freeDatas();
void gnerateDatas();
void sorting();
void tablePrint();
double librarySortHandle(int *data, int n, int size);
int compareNum(const void *p, const void *q);
double heapSort(int *data, int n);
void buildMaxHeapify(int *data, int n);
void maxHeapify(int *data, int n, int node);


void main() {
	printf("���� ����\n");
	tableReset();//���θ� ���� 0���� reset
	gnerateDatas();
	sorting();	//����
	tablePrint();	//��� ����Ʈ

	freeDatas();
}
//��� pirnt
void tablePrint() {
	printf(" \t\tRandom1000\tReverse1000\tRandom10000\tReverse10000\tRandom100000\tReverse100000\n");
	for (int j = 0; j < 9; j++) {
		switch (j) {
		case 0: printf("Bubble   \t");	break;
		case 1: printf("Selection\t");	break;
		case 2: printf("Insertion\t");	break;
		case 3: printf("Merge    \t");	break;
		case 4: printf("Quick1   \t");	break;
		case 5: printf("Quick2   \t");	break;
		case 6:	printf("Quick3   \t");	break;
		case 7: printf("Heap     \t");	break;
		case 8: printf("Library  \t");	break;
		}
		for (int i = 0; i < 6; i++) {
			if (i % 2 == 0)
				table[j][i] /= 10;
			printf("%lf  \t", table[j][i]);
		}
		printf("\n");
	}


}
//����
void sorting() {
	//���������� ����
	int N;	//�迭ũ��
	int **usingData;	//����� �迭
	for (int j = 0; j < 6; j = j + 2) {
		if (j == 0) {
			usingData = randomData1000;
			N = SIZE1;
		}
		else if (j == 2) {
			usingData = randomData10000;
			N = SIZE2;
		}
		else {
			usingData = randomData100000;
			N = SIZE3;
		}
		for (int i = 0; i < 10; i++) {
			makeRandomDatas(usingData, N);
			int tableXindex = 0;
			table[tableXindex++][j] += bubbleSort(usingData[tableXindex], N);
			table[tableXindex++][j] += selectionSort(usingData[tableXindex], N);
			table[tableXindex++][j] += insertionSort(usingData[tableXindex], N);
			table[tableXindex++][j] += mergeSort(usingData[tableXindex], 0, N - 1);
			table[tableXindex++][j] += quickSort(usingData[tableXindex], 0, N - 1);
			table[tableXindex++][j] += middlePivotQuickSort(usingData[tableXindex], 0, N - 1);
			table[tableXindex++][j] += randomPivotQuickSort(usingData[tableXindex], 0, N - 1);
			table[tableXindex++][j] += heapSort(usingData[tableXindex], N);
			table[tableXindex][j] += librarySortHandle(usingData[tableXindex],N,sizeof(int));
		}
	}
	//�Ųٷ� ���ĵ� ������ ����
	makeReverseDatas();

	//�Ųٷ� ���ĵ� ������ ����
	for (int j = 1; j < 6; j = j + 2) {
		if (j == 1) {
			usingData = reverseData1000;
			N = SIZE1;
		}
		else if (j == 3) {
			usingData = reverseData10000;
			N = SIZE2;
		}
		else {
			usingData = reverseData100000;
			N = SIZE3;
		}
		int tableXindex = 0;
		
		table[tableXindex++][j] = bubbleSort(usingData[tableXindex], N);
		table[tableXindex++][j] = selectionSort(usingData[tableXindex], N);
		table[tableXindex++][j] = insertionSort(usingData[tableXindex], N);
		table[tableXindex++][j] = mergeSort(usingData[tableXindex], 0, N - 1);
		table[tableXindex++][j] = quickSort(usingData[tableXindex], 0, N - 1);
		table[tableXindex++][j] = middlePivotQuickSort(usingData[tableXindex], 0, N - 1);
		table[tableXindex++][j] = randomPivotQuickSort(usingData[tableXindex], 0, N - 1);
		table[tableXindex++][j] = heapSort(usingData[tableXindex], N);
		table[tableXindex][j] = librarySortHandle(usingData[tableXindex], N, sizeof(int));
	}
}
void gnerateDatas() {
	reverseData1000 = (int **)malloc(9 * sizeof(int *));
	reverseData10000 = (int **)malloc(9 * sizeof(int *));
	reverseData100000 = (int **)malloc(9 * sizeof(int *));
	randomData1000 = (int **)malloc(9 * sizeof(int *));
	randomData10000 = (int **)malloc(9 * sizeof(int *));
	randomData100000 = (int **)malloc(9 * sizeof(int *));
	for (int i = 0; i < 9; i++) {
		reverseData1000[i] = (int *)malloc(SIZE1 * sizeof(int));
		reverseData10000[i] = (int *)malloc(SIZE2 * sizeof(int));
		reverseData100000[i] = (int *)malloc(SIZE3 * sizeof(int));
		randomData1000[i] = (int *)malloc(SIZE1 * sizeof(int));
		randomData10000[i] = (int *)malloc(SIZE2 * sizeof(int));
		randomData100000[i] = (int *)malloc(SIZE3 * sizeof(int));
	}
}
void freeDatas() {
	for (int i = 0; i < 9; i++) {
		free(reverseData1000[i]);
		free(reverseData10000[i]);
		free(reverseData100000[i]);
		free(randomData1000[i]);
		free(randomData10000[i]);
		free(randomData100000[i]);
	}
	free(reverseData1000);
	free(reverseData10000);
	free(reverseData100000);
	free(randomData1000);
	free(randomData10000);
	free(randomData100000);
}
void makeRandomDatas(int **data, int N) {
	srand((unsigned)time(NULL));

		for (int i = 0; i < N; i++) {
			int randNum = (rand() % N) + 1;
			for (int j = 0; j < 9; j++) {
				data[j][i] = randNum;
			}
		}
}
void makeReverseDatas() {
	for (int i = 0; i < SIZE3; i++) {
		if (i < SIZE1) {
			for (int k = 0; k < 9; k++)
				reverseData1000[k][i] = SIZE1 - i;
		}
		if (i < SIZE2) {
			for (int k = 0; k < 9; k++)
				reverseData10000[k][i] = SIZE2 - i;
		}
		for (int k = 0; k < 9; k++)
			reverseData100000[k][i] = SIZE3 - i;
	}
}
double bubbleSort(int data[], int n) {
	clock_t start, end;
	start = clock();
	for (int i = n - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (data[j] > data[j + 1]) {
				//swap(data, j, j + 1);
				int tmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = tmp;

			}
		}
	}
	end = clock();
	return (end - start) / (double)CLOCKS_PER_SEC;
}

double selectionSort(int data[], int n) {
	clock_t start, end;
	start = clock();
	for (int i = n - 1; i >= 1; i--) {
		int biggestIndex = 0;
		for (int j = 0; j <= i; j++) {
			if (data[biggestIndex] < data[j]) {
				biggestIndex = j;
			}
		}
		//swap(data, biggestIndex, i);
		int tmp = data[biggestIndex];
		data[biggestIndex] = data[i];
		data[i] = tmp;
	}
	end = clock();
	return (end - start) / (double)CLOCKS_PER_SEC;
}
double insertionSort(int data[], int n) {
	clock_t start, end;
	start = clock();
	for (int i = 1; i < n; i++) {
		int tmp = data[i];
		int j = i - 1;
		while (j >= 0 && data[j] > tmp) {
			data[j + 1] = data[j];
			j--;
		}
		data[j + 1] = tmp;
	}
	end = clock();
	return (end - start) / (double)CLOCKS_PER_SEC;
}
//r�� �迭�� ũ��-1, p�� ���� index(ó�� ������ p=0, r=�迭�� ũ��-1 �Է�)
double mergeSort(int data[], int p, int r) {
	clock_t start, end;
	start = clock();
	if (p < r) {
		int q = (p + r) / 2;	//p�� q�� �߰����� index
		mergeSort(data, p, q);	//���ݺ� ����
		mergeSort(data, q + 1, r);	//�Ĺݺ� ����
		merge(data, p, q, r);
	}
	end = clock();
	return (end - start) / (double)CLOCKS_PER_SEC;
}
void merge(int data[], int p, int q, int r) {
	int i = p, j = q + 1, k = p;
	while ((i <= q) && (j <= r)) {
		if (data[i] <= data[j])
			tmp[k++] = data[i++];
		else
			tmp[k++] = data[j++];
	}
	//�Ʒ� �� while���� ���� �迭, ���� �迭 �� ���� �κе��� �״�� tmp�ڿ� ���̴� �κ�.
	//�� �� �ϳ��� �۵��� �� �ۿ� ����.
	while (i <= q)
		tmp[k++] = data[i++];
	while (j <= r)
		tmp[k++] = data[j++];
	for (int i = p; i <= r; i++)
		data[i] = tmp[i];
}

//r�� �迭�� ũ�� -1(������ index)
double quickSort(int data[], int p, int r) {
	clock_t start, end;
	start = clock();
	if (p < r) {
		int q = partition(data, p, r, r);
		quickSort(data, p, q - 1);
		quickSort(data, q + 1, r);
	}
	end = clock();
	return (end - start) / (double)CLOCKS_PER_SEC;
}

//r�� ������ index
int partition(int data[], int p, int r, int pivotIndex) {
	int x = data[pivotIndex];
	//swap(data, pivotIndex, r);
	int tmp = data[pivotIndex];
	data[pivotIndex] = data[r];
	data[r] = tmp;
	int i = p - 1;
	for (int j = p; j <= r - 1; j++) {
		if (data[j] <= x) {
			i++;
			//swap(data, i, j);
			tmp = data[i];
			data[i] = data[j];
			data[j] = tmp;
		}
	}
	//swap(data, i + 1, r);
	tmp = data[i + 1];
	data[i + 1] = data[r];
	data[r] = tmp;
	return i + 1;
}

double middlePivotQuickSort(int data[], int p, int r) {
	clock_t start, end;
	start = clock();
	if (p < r) {
		int mid = middle(data, p, r, (p + r) / 2);
		int q = partition(data, p, r, mid);
		middlePivotQuickSort(data, p, q - 1);
		middlePivotQuickSort(data, q + 1, r);
	}
	end = clock();
	return (end - start) / (double)CLOCKS_PER_SEC;
}

double randomPivotQuickSort(int data[], int p, int r) {
	clock_t start, end;
	start = clock();
	srand((int)time(NULL));

	if (p < r) {
		int pivotIndex;
		if (p - r == 0)
			pivotIndex = p;
		else
			pivotIndex = (rand() % (r - p + 1)) + p;
		int q = partition(data, p, r, pivotIndex);
		randomPivotQuickSort(data, p, q - 1);
		randomPivotQuickSort(data, q + 1, r);
	}
	end = clock();
	return (end - start) /(double)CLOCKS_PER_SEC;
}
void swap(int data[], int index1, int index2) {
	int tmp = data[index1];
	data[index1] = data[index2];
	data[index2] = tmp;
}
int middle(int data[], int index1, int index2, int index3) {
	if (data[index1] > data[index2]) {
		if (data[index1] < data[index3])	//3 1 2
			return index1;
		else if (data[index3] < data[index2])	//1 2 3
			return index2;
		else
			return index3;		//1 3 2
	}
	else if (data[index2] > data[index3]) {	//2 3 1
		if (data[index3] > data[index1])
			return index3;
		else
			return index1;			//2 1 3
	}
	else
		return index2;				//3 2 1
}
void tableReset() {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 6; j++)
			table[i][j] = 0;
	}
}

//n:�迭(��)�� ũ��, node:node�� �������� ����Ʈ�� heapify�Ѵ�.
void maxHeapify(int *data, int n, int node) {
	//�ڽĳ�� ����.
	if ((node * 2 + 1) > n)
		return;
	int left = node * 2, right = node * 2 + 1;	//left:���� �ڽĳ�� index, right:������ �ڽĳ�� index
	int k;	//���� node�� �� ��(�� ū ���� �ִ� ��� index)
	if (right <= n) {
		if (data[left - 1] >= data[right - 1])
			k = left;
		else
			k = right;
	}
	else
		k = left;
	
	if (data[node - 1] >= data[k - 1])
		return;
	int tmp = data[node - 1];
	data[node - 1] = data[k - 1];
	data[k - 1] = tmp;

	maxHeapify(data, n, k);
}

void buildMaxHeapify(int *data, int n) {
	for (int i = n / 2; i > 0; i--)
		maxHeapify(data, n, i);
}

double heapSort(int *data, int n) {
	clock_t start, end;
	start = clock();

	buildMaxHeapify(data, n);
	int heapSize = n;
	for (int i = n; i >= 2; i--) {
		int tmp = data[0];
		data[0] = data[i - 1];
		data[i - 1] = tmp;
		heapSize--;
		maxHeapify(data, heapSize, 1);
	}

	end = clock();

	printf("[%d] [heap] %f\n", n, (end - start) / (double)CLOCKS_PER_SEC);
	return (end - start) / (double)CLOCKS_PER_SEC;
}

int compareNum(const void *p, const void *q) {
	return (*(int *)p) - (*(int *)q);
}

//data:�迭, n:������ ���� ����, size: ������ �� ������ ũ��(����Ʈ)
double librarySortHandle(int *data, int n, int size) {
	clock_t start, end;
	start = clock();

	qsort(data, n, size, compareNum);

	end = clock();

	printf("[%d] [lib] %f\n", n, (end - start) / (double)CLOCKS_PER_SEC);

	return (end - start) / (double)CLOCKS_PER_SEC;
}

