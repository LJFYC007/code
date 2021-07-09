#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
using namespace std;

typedef long long ll;

int read() {
	char ch;
	for(ch=getchar();ch<'0'||ch>'9';ch=getchar());
	int x=ch-'0';
	for(ch=getchar();ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
	return x;
}

void write(int x) {
	if (!x) {puts("0");return;}
	char ch[20];int tot=0;
	for(;x;x/=10) ch[++tot]=x%10+'0';
	fd(i,tot,1) putchar(ch[i]);
	puts("");
}

const int N=1e6+5,Mo=998244353;

int pwr(int x,int y) {
	int z=1;
	for(;y;y>>=1,x=(ll)x*x%Mo)
		if (y&1) z=(ll)z*x%Mo;
	return z;
}

int n,m,fac[N],inv[N];

void pre(int N) {
	fac[0]=1;fo(i,1,N) fac[i]=(ll)fac[i-1]*i%Mo;
	inv[N]=pwr(fac[N],Mo-2);fd(i,N-1,0) inv[i]=(ll)inv[i+1]*(i+1)%Mo;
}

int C(int m,int n) {return (ll)fac[m]*inv[n]%Mo*inv[m-n]%Mo;}

int main() {
	freopen("temple.in","r",stdin);
	freopen("temple.out","w",stdout);
	pre(1e6);
	for(int ty=read();ty;ty--) {
		int n=read(),m=read();
		write(C((n+m)/2,m));
	}
	return 0;
}
