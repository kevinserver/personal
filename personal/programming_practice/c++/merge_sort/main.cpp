//merge sort practice
#include <stdio>
#include <stdlib>

int * mergeSort(int* arr);
int * divide(int* arr);
int * combine(int* arr);


int main(int argc, char const *argv[])
{
	int array[] = {4,6,2,7,4,8,0,1,5,3,7,5};

	return 0;
}

int * mergeSort(int* arr)
{
	int *newArray = arr;
	int size = newArry.length();
	if (size != 1)
	{
		
		// int subArray1[size/2];
		// int subArray2[size/2];
		// for (int i = 0; i < size/2-1; i++)
		// {
		// 	subArray1[i] = sorted[i];
		// 	subarray2[i] = sorted[i+size/2];
		// }
		// mergeSort
	}

}
int * divide(int* arr)
{
	int *newArray = arr;
	int size = newArry.length();
	if (size != 1)
	{
		int subArray1[size/2];
		int subArray2[size/2];
		for (int i = 0; i < size/2; i++)
		{
			subArray1[i] = sorted[i];
			subarray2[i] = sorted[i+size/2];
		}
		divide(subArray1);
		divide(subArray2);
	}
}
int * combine(int* arr)
{

}