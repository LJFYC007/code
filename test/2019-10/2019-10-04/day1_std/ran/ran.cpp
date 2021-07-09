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

void write(ll x) {
	char ch[20];int tot=0;
	for(;x;x/=10) ch[++tot]=x%10+'0';
	fd(i,tot,1) putchar(ch[i]);
	puts("");
}

const int N=1.2e6+5;

int n,q,sz[N],opt;
ll C[N],L[N],R[N],LR[N],sum;

void build(int v,int l,int r) {
	sz[v]=1;
	L[v]=(2*l+1);C[v]-=(ll)l*(l+1);
	R[v]=(2*r-1);C[v]-=(ll)r*(r-1);
	if (l==r) return;
	C[v]+=(ll)4*(l+1)*(r-1);LR[v]=4;
	L[v]-=4*(r-1);R[v]-=4*(l+1);
	int mid=l+r>>1;
	build(v<<1,l,mid);build(v<<1|1,mid+1,r);
	sz[v]+=sz[v<<1]+sz[v<<1|1];
	C[v]+=C[v<<1]+C[v<<1|1];LR[v]+=LR[v<<1]+LR[v<<1|1];
	L[v]+=L[v<<1]+L[v<<1|1];R[v]+=R[v<<1]+R[v<<1|1];
}

ll query(int v,int l,int r,int x,int y) {
	if (x<=l&&r<=y) {
		ll tmp=C[v];
		tmp+=(sum-(ll)x*x-(ll)y*y)*sz[v];
		tmp+=L[v]*x;tmp+=R[v]*y;tmp+=LR[v]*x*y;
		return tmp;
	}
	ll tmp=sum;
	if (x<=l) tmp-=(ll)(l-x)*(l-x+1);
	if (r<=y) tmp-=(ll)(y-r)*(y-r+1);
	int mid=l+r>>1;
	if (x<=mid) tmp+=query(v<<1,l,mid,x,y);
	if (y>mid) tmp+=query(v<<1|1,mid+1,r,x,y);
	return tmp;
}

int main() {
	freopen("ran.in","r",stdin);
	freopen("ran.out","w",stdout);
	n=read();q=read();opt=read();
	build(1,1,n);
	ll ans=0;
	for(;q;q--) {
		ll l=((ans*opt)^read())%n+1,r=((ans*opt)^read())%n+1;
		if (l>r) swap(l,r);
		sum=(ll)(r-l+1)*(r-l+2);
		write(ans=query(1,1,n,l,r)/2);
	}
	return 0;
}