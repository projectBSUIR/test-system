#include <iostream>
#include <unistd.h>
using namespace std;

int main()
{
	int i=0;
	while(i<20)
	{
		cout<<"|Test Thread Message|";
		sleep(1);
		i++;
	}
}
