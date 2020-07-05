#include <stdio.h>
#include <stdlib.h>

#define MAX 11

//arrays must be sorted first for this to work, returns length of output array
int Merge(int a1[], int a2[], int n1, int n2){
	int output[n1+n2];
	//a2 is smaller than a1 so it can go before
	if ((a1[0] >= a2[0]) && (a1[0] >= a2[n2-1])){
		for (int i=0; i<n2;i++ ){
			output[i] = a2[i];
		}
		for (int i=0; i<n1;i++ ){
			output[i+n2] = a1[i];
		}
	}
	//a2 is bigger than a1 so it can go after
	else if ((a2[0] >= a1[0]) && (a2[0] >= a1[n1-1])){
		for (int i=0; i<n1;i++ ){
			output[i] = a1[i];
		}
		for (int i=0; i<n2;i++ ){
			output[i+n1] = a2[i];
		}
		
	}	//the two overlap so merge individually
	else{
	
		int outputcnt = 0;
		int a1cnt = 0;
		int a2cnt = 0;

		while (outputcnt<n1+n2){

			if ((a1[a1cnt] < a2[a2cnt]) && (a1cnt <n1)){
				output[outputcnt] = a1[a1cnt];
				outputcnt++;
				a1cnt++;
			}else if ((a2[a2cnt] < a1[a1cnt]) && (a2cnt <n2)){
				output[outputcnt] = a2[a2cnt];
				outputcnt++;
				a2cnt++;
			}else if (a1cnt <n1){
				output[outputcnt] = a1[a1cnt];
				outputcnt++;
				a1cnt++;
			}else if (a2cnt <n2){
				output[outputcnt] = a2[a2cnt];
				outputcnt++;
				a2cnt++;
			}	
		}
		
	}
	
	for (int i=0; i<(n1+n2);i++ ){
		a1[i] = output[i];
    }
	return n1+n2;	
	
}

//first split until only arrays with one element are there then merge 
void MergeSort(int a[], int n) { /* code to sort a[0].. a[n - 1] using merge sort */ 

	int sizel=0; 
	int sizer=0;
	
	sizel = n/2;
	sizer = (n%2!=0) ? sizel+1 : sizel;
	
	if (sizel > 0)
	{
		MergeSort(a,sizel);
		MergeSort(a+sizel,sizer);
		Merge(a,a+sizel,sizel,sizer);
	}	
}


//get ith largest by dividing the array and recur
int iLargest2(int arr[],int n, int i)
{
	MergeSort(arr,n);
	if (n>1){
		
		int pivot = n/2;
		if (pivot == i){
			return arr[n-i];
		}else if(pivot < i){
			iLargest2(arr,pivot,i);
		}else{
			if (n%2==0){	
				iLargest2(arr+pivot-1,pivot,i);
			}else{
				iLargest2(arr+pivot,pivot+1,i);
			}
			
		}	
	}
	return arr[n-i];
}

//get ith largest by sorting array first 
int iLargest1(int arr[],int n, int i)
{
	MergeSort(arr,n);
	return arr[n-i];
}

//get the second largest of unsorted array
int SecondLargest(int arr[], int n)
{
	int twolargest[2] = {arr[0],arr[1]};	
	for (int i=0; i<n+1;i++ ){
		
		if (arr[i] > twolargest[0]){
				twolargest[1] = twolargest[0];
			twolargest[0] = arr[i];
		
		}
		if ((arr[i] > twolargest[1]) && (arr[i] < twolargest[0]))
		{
			
			twolargest[1] = arr[i];		
		}
	}
	

	
	return twolargest[1];
	
}

//main function
int main(int argc, char *argv[]) {

	if (argc != 2)
	{
		printf("bad number of arguments");
		return -1;
	}

	
	int arr[MAX] = {-1,4,37,6,11,7,9,1,3,15,3};
	int i = atoi(argv[1]);
	if (i<1)
	{		
		printf("bad argument");
		return -1;	
	}
	printf("The array given is: %d",arr[0]);
	
	for (int k=1; k<MAX;k++ ){
		printf(", %d",arr[k]);
    }
	printf("\n\n");
	printf("Second largest number of array is: %d\n",SecondLargest(arr,MAX));
	if (i==1){
		printf("L");
	}else if (i==2){
		printf("%dnd l",i);
	}else if (i <= 0){
		return -1;
	}else{
		printf("%dth l",i);
	}
	
	printf("argest number of array: \n");
	printf("using iLargest1 is: %d\n",iLargest1(arr,MAX,i));
	printf("using iLargest2 is: %d\n",iLargest2(arr,MAX,i));
		
	return 0; 

}

