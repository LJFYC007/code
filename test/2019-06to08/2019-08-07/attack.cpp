/***************************************************************
	File name: attack.cpp
	Author: huhao
	Create time: Wed 07 Aug 2019 09:51:07 AM CST
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
#define ui long long
const ui N=1000010,_x=(-1u)/2;
ui A,B,C,q,al[N],ar[N],bl[N],br[N],cl[N],cr[N],w[N];
ui ***b,***a;
/*void add(ui x,ui y,ui z,ui w)
{
	if(!x||!y||!z)
		return;
	for(ui i=x;i;i-=i&(-i))
		for(ui j=y;j;j-=j&(-j))
			for(ui k=z;k;k-=k&(-k))
			{
//				printf("%d %d %d\n",i,j,k);
				b[i][j][k]+=w;
//				b[i][j][k]=b[i][j][k]>_x?_x:b[i][j][k];
			}
}
ui query(ui x,ui y,ui z)
{
	ui r=0;
	for(ui i=x;i<=A;i+=i&(-i))
		for(ui j=y;j<=B;j+=j&(-j))
			for(ui k=z;k<=C;k+=k&(-k))
			{
				r+=b[i][j][k];
//				r=r>_x?_x:r;
			}
	return r;
}*/
void add(int x,int y,int z,int _w)
{
	if(x<1||x>A||y<1||y>B||z<1||z>C)
		return;
	b[x][y][z]+=_w;
}
int query(int x,int y,int z)
{
	return b[x][y][z]+=b[x-1][y][z]+b[x][y-1][z]+b[x][y][z-1]-b[x-1][y-1][z]-b[x-1][y][z-1]-b[x][y-1][z-1]+b[x-1][y-1][z-1];
}
ui check(ui m)
{
	fr(i,1,A)
		fr(j,1,B)
			fr(k,1,C)
				b[i][j][k]=0;
	fr(i,1,m)
	{
		add(ar[i],br[i],cr[i],-w[i]);
		add(al[i],br[i],cr[i],w[i]);
		add(ar[i],bl[i],cr[i],w[i]);
		add(ar[i],br[i],cl[i],w[i]);
		add(al[i],bl[i],cr[i],-w[i]);
		add(al[i],br[i],cl[i],-w[i]);
		add(ar[i],bl[i],cl[i],-w[i]);
		add(al[i],bl[i],cl[i],w[i]);
	}
	ui ans=0;
/*	printf("%lld\n",m);
	fr(i,1,A)
		fr(j,1,B)
			fr(k,1,C)
				printf("%lld %lld\n",a[i][j][k],query(i,j,k));*/
	fr(i,1,A)
	{
		fr(j,1,B)
		{
			fr(k,1,C)
				if(query(i,j,k)>a[i][j][k])
				{
					ans=1;
					break;
				}
			if(ans)
				break;
		}
		if(ans)
			break;
	}
/*	fr(i,l,m)
	{
		w[i]=-w[i];
		add(ar[i],br[i],cr[i],w[i]);
		add(al[i],br[i],cr[i],-w[i]);
		add(ar[i],bl[i],cr[i],-w[i]);
		add(ar[i],br[i],cl[i],-w[i]);
		add(al[i],bl[i],cr[i],w[i]);
		add(al[i],br[i],cl[i],w[i]);
		add(ar[i],bl[i],cl[i],w[i]);
		add(al[i],bl[i],cl[i],-w[i]);
		w[i]=-w[i];
	}*/
	return ans;
}
int main()
{
	freopen("attack.in","r",stdin);
//	freopen("../../down/attack2.in","r",stdin);
	freopen("attack.out","w",stdout);
	A=read();
	B=read();
	C=read();
	q=read();
	a=(new ui**[A+1]);
	b=(new ui**[A+1]);
	fr(i,0,A)
	{
		a[i]=(new ui*[B+1]);
		b[i]=(new ui*[B+1]);
		fr(j,0,B)
		{
			a[i][j]=(new ui[C+1]);
			b[i][j]=(new ui[C+1]);
		}
	}
	fr(i,1,A)
		fr(j,1,B)
			fr(k,1,C)
				a[i][j][k]=read();
	fr(i,1,q)
	{
		al[i]=read();
		ar[i]=read()+1;
		bl[i]=read();
		br[i]=read()+1;
		cl[i]=read();
		cr[i]=read()+1;
		w[i]=read();
	}
	ui l=1,r=q;
	while(l<r)
	{
		ui mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	printf("%lld\n",l);
	return 0;
}
