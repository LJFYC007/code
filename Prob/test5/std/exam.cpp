#include<bits/stdc++.h>
using namespace std;
int n,ans1,ans2;
int main()
{
	freopen("exam.in","r",stdin);
	freopen("exam.out","w",stdout);
	scanf("%d",&n);
	for(register int i=1;i<=n;i++)
	{
		int max1=0,max2=0,max3=0;
		for(register int x;;)
		{
			scanf("%d",&x);
			if(!x)
				break;
			if(x>max1)
			{
				max3=max2;
				max2=max1;
				max1=x;
			}
			else
				if(x>max2)
				{
					max3=max2;
					max2=x;
				}
				else
					if(x>max3)
						max3=x;
		}
		int sum=max1+max2+max3;
		if(sum>ans1)
		{
			ans1=sum;
			ans2=i;
		}
	}
	printf("%d %d",ans1,ans2);
	return 0;
}
