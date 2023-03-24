#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
	int* arr=new int[2000000];
	int i=0;
	while(i<1999999)
	{
		arr[i]=i;
		if(i%300000) cout<<i;
	}
	return 0;
}
