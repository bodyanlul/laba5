#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

typedef int (*callback)(int a, int b); // ������ �� ������� ���������� 2 ����� <,> � ����������� �� ������ � ������

typedef struct File_s { //��������� ���������� ����������� ����, ��� ��������(1)-���������(0), � ��� ���������� � ������ �� ������ ������ (1 �����)
	FILE* name;
	int type;
	int number;
}File;

File arr[4]; // ������ �������� ���� "File"
char temp[255]; //������ ��� ������ �������� ������ � inc/dec

int cmpI(int a, int b) //���������� �����������
{
	if (a < b) return a;
	else return b;
}

int cmpD(int a, int b)//���������� ��������
{
	if (a > b) return a;
	else return b;
}

int Find(callback cmp, int N, int first, ...) //����� ������������ �� N ���������, � �������������� ������� �������� �����������
{
	int ans = first;
	int* ptr = &first;
	++ptr;
	for (int i = 1; i < N; ++i)
	{
		ans = cmp(ans, *ptr);
		++ptr;
	}
	return ans;
}


int Get_Elem(File f, int bound) //���� ����� ����� �� ����� ��������� � �������� number ��������� "File", ���� � ����� ��������� ����� - ��������� �������
{
	int temp;
	int flag;
	if (f.type == 0) flag = fscanf(f.name, "%d", &temp);
	if (f.type == 1) flag = fread(&temp, 4, 1, f.name);
	if (flag != -1 && flag != 0) return temp;
	else return bound;
}

void Find_Min(int N, callback cmp, int bound) {
	int flag = 1; // �������� ����� ��� �������
	while (N) //���� ����� �� �����
	{
		int ans; // ���������� ������ (����� - ��������� �����)
		int NULLflag = 0; //���� ��� �������� ����� ����� ������� ��� ���������
		if (N == 1) ans = Find(cmp, N, arr[0].number); //������������� ������� � �������� ����� cmp, � ������ ���-��� ��������
		if (N == 2) ans = Find(cmp, N, arr[0].number, arr[1].number);
		if (N == 3) ans = Find(cmp, N, arr[0].number, arr[1].number, arr[2].number);
		if (flag) //������ �������
		{
			bound = ans;
			--flag;
		}
		for (int i = 0; i < N; ++i)
		{
			if (arr[i].number == ans) //���� ������� �����������, ������ ����� �������
			{
				arr[i].number = Get_Elem(arr[i], bound);
				if (arr[i].number == bound) //���� ��������� ������ ���(�� ���� ����� = �������(��. Get_Elem)), ��������� ���-�� ������, � ������ ��� ����� �������� 1
				{
					NULLflag = 1;
					--N;
				}
				break;
			}
		}
		if (NULLflag) //���� ���� ���� �������� 
			for (int i = 0; i < N; ++i)
				for (int j = i + 1; j < N + 1; ++j) //������ ������� ��������� ���, ����� ����������� ���� ��� � �����
					if (arr[i].number == bound)
					{
						File t;
						t = arr[i];
						arr[i] = arr[j];
						arr[j] = t;
					}
		printf("%d ", ans); //����� �����
	}
}

void Open_File(int N) {
	for (int i = 0; i < N; ++i)
	{
		scanf("%s", temp);
		if (temp[strlen(temp) - 1] == 't')  //���������� � �������� ������. �������� ������ (txt ��� bin).
		{
			arr[i].type = 0;
			arr[i].name = fopen(temp, "rt");
		}
		else
		{
			arr[i].type = 1;
			arr[i].name = fopen(temp, "rb");
		}
		if (arr[i].name == NULL)  //���� ����� �� ����������
		{
			printf("��������� ���� �� ���������� \"%s\"", temp);
			return 2;
		}
		strcpy(temp, "\0");
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");

	int N = 0; //���-�� ������

	printf("��������� ���������� ����� ����� �� �������� ������� ���� ���������, �������� �� �� �����������/��������.\n");
	printf("� ����� ������� ����������� �����? (Dec - ��������, Inc - �����������)\n");
	scanf("%s", &temp);

	callback cmp; // �������� �����������        

	if (strcmp(temp, "Inc") == 0) cmp = cmpI; //����� ����������� Inc
	else if (strcmp(temp, "Dec") == 0) cmp = cmpD; //����� ����������� Dec
	else
	{
		printf("������� Dec ��� Inc");
		return 2;
	}
	strcpy(temp, "\0"); //�������� ������ �� ������
	printf("������� ���������� ������(1-3)\n");
	scanf("%d", &N);

	if (N > 3 || N < 1)
	{
		printf("������� ���������� ���������� ������.");
		return 2;
	}
	printf("������� ����� � ������� *���*.txt ��� *���*.bin\n");
	Open_File(N);
	int bound = NULL; //����������� �������
	for (int i = 0; i < N; ++i) arr[i].number = Get_Elem(arr[i], bound); // ������ ���������� ��������� � �������
	Find_Min(N, cmp, bound);
	printf("\n");
	for (int i = 0; i < N; ++i) //�������� ������.
		fclose(arr[i].name);

	printf("��� ����� �������.\n��������� ������� ��������� ������\n");
	return 0;
}



/*#pragma comment(linker, "/STACK:50000000")
#define _CRT_SECURE_NO_WARNINGS
#define MAX_VALUE 200001
#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
	int from;
	int to;
}Edge;


typedef struct Vector_s {
	int cnt;
	int maxCnt;
	Edge* arr;
	int dist;
	int col;
}Vector;

void adder(Vector* vect, Edge edg, int point) {
	if (vect[point].maxCnt == 0) {
		vect[point].arr = malloc(sizeof(Edge) + 1);
		++vect[point].maxCnt;
	}
	else if (vect[point].maxCnt == vect[point].cnt) {
		vect[point].arr = realloc(vect[point].arr, (vect[point].maxCnt * 2) * sizeof(Edge));
		vect[point].maxCnt *= 2;
	}
	vect[point].arr[vect[point].cnt] = edg;
	++vect[point].cnt;
}

Vector a[MAX_VALUE];
int b[MAX_VALUE];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int N, M; Edge temp;
	scanf("%ld", &N);
	scanf("%ld", &M);

	for (int i = 0; i < M; i++) {
		scanf("%ld", &temp.from);
		scanf("%ld", &temp.to);
		adder(&a, temp, temp.from);
	}
	int s = 0, e = 1;
	b[0] = 1;
	a[b[s]].dist = 0;
	while (s != e) {
		a[b[s]].col = 1;
		for (int i = 0; i < a[b[s]].cnt; i++)
		{
			int next = a[b[s]].arr[i].to;
			if (a[next].col == 0) {
				a[next].col = 1;
				a[next].dist = a[b[s]].dist + 1;
				b[e] = next;
				++e;
			}
		}
		++s;
	}

	printf("0\n");
	for (int i = 2; i <= N; i++) {
		if (a[i].dist == 0) printf("-1\n");
		else printf("%ld\n", a[i].dist);
	}

	return 0;
}


/*
typedef struct Graph_s {
	int color;
	struct Graph_s* p;
	int d;
	int num;
} Graph;

Graph u[200000];

void Enqueue(Q, s) {
	//�������� s � Q
}
void Dequeue(Q) {
	//��������� �� Q
}

void BFS(G, s, N) {
	
	s.color = 1;
	s.d = 0;
	s.p = NULL;
	Q = NULL;
	Enqueue(Q, s);
	while (Q != NULL) {
		u = Dequeue(Q);
		for (int v = 1; v <= G.Adj[u]; ++v) {
			if (v.color == 0) {
				v.color = 1;
				v.d = u.d + 1;
				v.p = u;
				Enqueue(Q, v);
			}
		}
		u.color = 2;
	}

}

int main() {

	Graph first;
	for (int i = 0; i <= N; ++i) {
		if (u[i].num != s.num) {
			u[i].color = 0;
			u[i].d = -1; //Inf
			u[i].p = NULL;
			u[i].num = i;
		}
	}
	first.color = 0;
	first.d = 0;
	first.num = 1;
	first.p = NULL;

	return 0;
}
	

/*
double fcount(double *a, double l, double t){
return a[0] + 2 * a[1] * (t - l) + 3 * a[2] * (t - l) * (t - l);
}

double fInPoint (double *x, double *y, double *z, double l, double point){
double preRes = 0;
double preRes1 = fcount(x, l, point) ;
preRes += preRes1 * preRes1;
double preRes2 = fcount(y, l, point) ;
preRes += preRes2 * preRes2;
double preRes3 = fcount(z, l, point) ;
preRes += preRes3 * preRes3;

preRes = sqrt(preRes);
return preRes;
}

int main() {
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
int n;
double x[3], y[3], z[3], res = 0, l, r;
scanf("%d", &n);
for(int i = 0; i < n; i++) {
double preResult = 0;
scanf("%lf %lf", &l, &r);
scanf("%lf", &x[0]); // ���������� �� ���������, ����� �� �����������
for (int j = 0; j < 3; j++) {
scanf("%lf", &x[j]);
}

scanf("%lf", &y[0]); // ���������� �� ���������, ����� �� �����������
for (int j = 0; j < 3; j++) {
scanf("%lf", &y[j]);
}

scanf("%lf", &z[0]); // ���������� �� ���������, ����� �� �����������
for (int j = 0; j < 3; j++) {
scanf("%lf", &z[j]);
}
double h = (r - l) / 150;
for (int k = 1; k < 150; k++){
double preRes = fInPoint(x, y, z, l, l + (h * (double)k));
if(k % 2 == 1) preResult += (preRes * 4);
else preResult += (preRes * 2);
}
preResult += fInPoint(x, y, z, l, l);
preResult += fInPoint(x, y, z, l, r);
preResult *= h / 3;
res += preResult;
}
printf("%0.15lf", res);
return 0;
}
*/