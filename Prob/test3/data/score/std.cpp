#include"score.h"
#include<math.h>
#include<string.h>
#include<stdio.h>
const int N=1010;
int b[N],k;
void run(int n)
{
	k=sqrt(n);
	memset(b,0,sizeof(b));
	if(!query(b,1))
	{
		for(int i=1;i<=n;i++)
			b[i]=1;
		query(b,n);
		return;
	}
	int l=1;
	while(l<=n)
	{
		l++;
		if(!query(b,l))
			b[l]=1;
		if(l%k==0&&b[l]!=0)
		{
			if(!query(b,l))
				break;
		}
	}
	for(int i=((l-1)/k)*k+1;i<=l;i++)
	{
		if(query(b,i))
			continue;
		b[i]^=1;
		if(query(b,i))
			continue;
		l=i-1;
		break;
	}
	for(int i=l+1;i<=n;i++)
	{
		for(int j=i;j>=2;j--)
			b[j]=b[j-1];
		b[1]=0;
		if(!query(b,i))
			b[1]=1;
	}
	query(b,n);
}
