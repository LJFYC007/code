/***************************************************************
	File name: cactus.cpp
	Author: huhao
	Create time: Fri 13 Sep 2019 09:40:28 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=r*10+c-48;
		c=getchar();
	}
	return r*t;
}
const int N=10010,M=5010;
int n,m,k,f[N][M],a[N],b[N],r,l,ans,lst,p[N];
inline int Min(int a,int b)
{
	return a<b?a:b;
}
int main()
{
	freopen("cactus.in","r",stdin);
	freopen("cactus.out","w",stdout);
	n=read();
	m=read();
	k=read();
	fr(i,1,n)
	{
		a[i]=read();
		b[i]=read();
	}
	r=n;
	ans=n+1;
	while(r)
	{
		l=r;
		fr(i,0,m)
			f[r][i]=k+1;
		f[r][0]=0;
		f[r][a[r]]=b[r];
		while(l>1&&f[l][m]>k)
		{
			l--;
			fr(i,0,m)
				f[l][i]=f[l+1][i];
			fr(i,0,m-a[l])
				f[l][i+a[l]]=Min(f[l][i+a[l]],f[l+1][i]+b[l]);
		}
		if(f[l][m]<=k)
			ans=Min(ans,r-l+1);
		if(lst>r)
		{
			fr(i,0,m)
				f[r+1][i]=k+1;
			f[r+1][0]=0;
			f[r+1][a[r+1]]=b[r+1];
			fr(i,r+2,lst)
			{
				fr(j,0,m)
					f[i][j]=f[i-1][j];
				fr(j,0,m-a[i])
					f[i][j+a[i]]=Min(f[i][j+a[i]],f[i-1][j]+b[i]);
			}
			fr(i,0,m)
				p[i]=r+1;
			fr(i,l+1,r)
			{
				fr(j,1,m-1)
				{
					while(f[i][j]+f[p[m-j]][m-j]>k&&p[m-j]<=lst)
						p[m-j]++;
					if(p[m-j]<=lst)
					{
/*						printf("%d %d  %d %d %d\n",i,p[m-j],l,r,lst);
						fr(o,0,m)
							if(f[i][o]!=k+1)
								printf("(%d %d)",o,f[i][o]);
						putchar(10);
						fr(o,0,m)
							if(f[p[m-j]][o]!=k+1)
								printf("(%d %d)",o,f[p[m-j]][o]);
						putchar(10);*/
						ans=Min(ans,p[m-j]-i+1);
					}
				}
			}
		}
		fr(i,0,m)
			f[l][i]=k+1;
		f[l][0]=0;
		f[l][a[l]]=b[l];
		if(f[l][m]<=k)
		{
			ans=1;
			break;
		}
		fr(i,l+1,r)
		{
			fr(j,0,m)
				f[i][j]=f[i-1][j];
			fr(j,0,m-a[i])
				f[i][j+a[i]]=Min(f[i][j+a[i]],f[i-1][j]+b[i]);
			if(f[i][m]<=k)
			{
				ans=Min(ans,i-l+1);
				break;
			}
		}
		lst=r;
		r=l-1;
	}
	printf("%d\n",ans>n?-1:ans);
	return 0;
}
