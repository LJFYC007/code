#include<bits/stdc++.h>
using namespace std;
const int maxn=1e2+10;
int n,a[maxn];
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	{
		int cnt=0,sum=0;
		for(;;)
		{
			scanf("%d",&a[++cnt]);
			if(!a[cnt])
			{
				cnt--;
				break;
			}
		}
		for(register int i=2;i<cnt;i++)
			if(a[i]>a[i-1] && a[i]>a[i+1])
				sum++;
		if(sum^1)
			puts("no");
		else
			puts("yes");
	}
}
