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
#define ld double
int n,m,k;
namespace sub1
{
	const int N=500010;
	int y[N];
	ld c[N];
	int lst;
	ld ans;
	int main()
	{
		fr(i,1,m)
			y[i]=read();
		fr(i,1,k-1)
			c[i]=1-read()/100.;
		fr(i,1,k)
		{
			int a=read(),s=read(),z=read();
			ld p=(ld)y[s]/z;
			if(lst)
				p*=c[i-lst];
			p=max((ld)0,1-p);
			p=1-p*p;
			ans+=a*p;
			if(p<(ld)0.64)
				lst=i;
		}
		printf("%.2lf\n",(double)ans);
		return 0;
	}
}
namespace sub2
{
	const int N=10,K=110;
	const ld inf=1e12,eps=1e-10;
	double x[N+5];
	int y[K];
	double c[K];
	ld f[K][(1<<N)+10][K],ans;
	inline ld calc(ld p)
	{
		p=max((ld)0,1-p);
		return 1-p*p;
	}
	int main()
	{
		fr(i,1,n)
			x[i]=1+read()/100.;
		fr(i,1,m)
			y[i]=read();
		fr(i,1,k-1)
			c[i]=1-read()/100.;
		fr(i,0,(1<<n)-1)
			f[0][i][0]=-inf;
		f[0][0][0]=0;
		fr(i,1,k)
		{
			int a=read(),s=read();
			ld p=(ld)y[s]/read();
//			printf("%d %.10lf\n",i,(double)calc(p));
			fr(lst,0,i-1)
			{
				ld P=lst==0?p:p*c[i-lst];
				fr(j,0,(1<<n)-1)
				{
					ld _P=calc(P);
					int K=_P>=(ld)0.64?lst:i;
					f[i][j][K]=max(f[i][j][K],f[i-1][j][lst]+_P*a);
					for(int o=j;o;o=(o-1)&j)
						if(f[i-1][j^o][lst]>-eps)
						{
							ld P_=P;
							fr(l,1,n)
								if(o&(1<<(l-1)))
									P_*=x[l];
							_P=calc(P_);
							K=_P>=(ld)0.64?lst:i;
							f[i][j][K]=max(f[i][j][K],f[i-1][j^o][lst]+_P*a);
						}
				}
			}
		}
		fr(i,0,(1<<n)-1)
			fr(j,0,k)
			{
				ans=max(ans,f[k][i][j]);
//				printf("%d %d %.2lf\n",i,j,(double)f[k][i][j]);
			}
		printf("%.2lf\n",(double)ans);
		return 0;
	}
}
int main()
{
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	n=read();
	m=read();
	k=read();
	if(!n)
		return sub1::main();
	else
		return sub2::main();
	return 0;
}
