#include<bits/stdc++.h>
using namespace std;
int main()
{
	srand(time(0));
	freopen("exam3.in","w",stdout);
	int n=4;
	printf("%d\n",n);
	for(register int i=1;i<=n;i++)
	{
		int num=rand()%497+3;
		for(register int j=1;j<=num;j++)
			printf("%d ",rand()%300+1);
		puts("0");
	}
	return 0;
}
