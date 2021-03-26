#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int num[500001];
int same_arr[8001];  // 빈도 수 배열(해당 인덱스의 숫자가 나오면 배열에 있는 값을 ++)
                     // 빈도수 배열의 인덱스를 해당 숫자+4000으로 (+4000 하는 이유: 인덱스 음수일 수는 없다)
int compare(void*first, void*second)
{
	if (*(int*)first > *(int*)second)
		return 1;
	else if (*(int*)first < *(int*)second)
		return - 1;
	else
		return 0;
}

//산술평균: N개의 수들의 합을 N으로 나눈 값
int average( int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
		sum += num[i];

	return sum;
}

int findMax(int arr[], int n)
{
	int max = arr[0];
	for (int i = 0; i < n; i++)
	{
		if (max < arr[i])
			max = arr[i];
	}
	return max;
}

//최빈값: N개의 수들 중 가장 많이 나타나는 값, 여러개 있을 경우는 두 번째로 작은 수
//안풀리는 이유: 해당빈도수에 대한 숫자값을 알지 못함  --> 해결 : 빈도수 배열의 인덱스를 해당 숫자+4000으로 !!!
int mostAppearNumber(int n)
{
	int max_same; // 최대 빈도수

	// 최대빈도수 구하기
	max_same=findMax(same_arr, 8001);
	// 최대빈도수가 몇 번나오는지 구하기
	int count_1 = 0;
	for (int i = 0; i < 8001; i++)
	{
		if (same_arr[i] == max_same)
			count_1++;
	}
	//printf("==%d==\n", count_1);
	//qsort(same_arr, 8001, sizeof(int), compare);  --------> 정렬하는 순간 same_arr 순서 바뀜
	int flag_1 = 0;
	for (int i = 0; i < 8001; i++)
	{
		// 최대빈도수가 한 번만 나오면, 그 것이 정답
		if (count_1 == 1)
		{
			// 최댓값과 같은 값 찾으면
			if (max_same == same_arr[i])
				return i - 4000;
		}

		// 최대빈도수가 여러개이면
		else
		{
				// 최대빈도수를 가진 두 번째로 작은 수를 만나면(첫 번째로 작은 수는 넘어감)
			if (flag_1 == 1 && max_same == same_arr[i])
			{
				return i - 4000;
			}

				// 최대빈도수를 가진 제일 작은 수 만나면
			        // 배열의 처음부터 돌다가 최대빈도수와 같은 값 만나면, 그것은 제일 작은 
			if (flag_1==0 && max_same == same_arr[i])
					flag_1 = 1;
		}
	}
}

//범위 : N개의 수들 중 최댓값과 최솟값의 차이
int range(int n)
{
	int difference_large_small;
	qsort(num, n, sizeof(int), compare);

	difference_large_small = num[n - 1] - num[0];
	return difference_large_small;
}

// n은 홀수
void answer(int n)
{
//산술평균
	double avg = (double)average(n)/(double)n;

//최빈값
	int mostAppear = mostAppearNumber(n);

//범위 
	int ran = range(n);

//중앙값 : N개의 수들을 증가하는 순서로 나열했을 경우 그 중앙에 위치하는 값
//-----> 범위를 구할 때 이미 정렬함

	// n이 홀수니까
	int middle = num[n / 2];

	printf("%.0f\n%d\n%d\n%d\n", avg, middle, mostAppear, ran);
}

int main(void)
{
	int n; 
	scanf("%d", &n);

	int input;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &input);
		num[i] =input;
		
		// 빈도수 배열(입력받은 숫자를 인덱스로 하는 배열에 있는 값을 ++)에 저장
		// ex) input=3이면, same_arr[3]++
		same_arr[input + 4000]++;
	}
	answer(n);
	return 0;
}
