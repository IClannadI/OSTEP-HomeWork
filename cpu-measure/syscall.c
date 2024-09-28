#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int compare(const void* a, const void *b) {
	return (*(int*)a - *(int*)b);
}

int main()
{
	char buf[100];
	int result[100];  	
	struct timeval tp;
	for (int i = 0, j = 0; i < 100; ++i, ++j) {  // 进行100次测试
		gettimeofday(&tp, NULL);
		int bef_time = tp.tv_usec;

		for (int i = 0; i < 10000; ++i) {  // 进行10000次系统调用
			read(STDIN_FILENO, buf, 0);
		}
			
		gettimeofday(&tp, NULL);
		int aft_time = tp.tv_usec;

		result[j] = aft_time - bef_time;  // 计算一次10000系统调用所用时间
	}
	
	qsort(result, 100, sizeof(int), compare);  // 对结果数组进行快速排序

	long int sum = 0;
	for (int i = 1; i < 99; ++i) {  // 去掉最高值和最低值，计算平均时间
		sum += result[i];
	}
	long int aver_time = sum / 100;  // 每一万次系统调用所需时间
	printf("The syscall time spended is %ld\n", aver_time);
}

