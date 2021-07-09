#include <cstdio>
#include <cstring>
#include <algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
using namespace std;

typedef long long ll;

int read() {
	char ch;int sig=1;
	for(ch=getchar();ch<'0'||ch>'9';ch=getchar()) if (ch=='-') sig=-1;
	int x=ch-'0';
	for(ch=getchar();ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
	return x*sig;
}

const int N=5e5+5,Mo=1e9+7;

int n,q,a[N],fa[N],pre[N];
ll sum[N],suf[N],pw[N],S[N],an[N];

struct Que{int l,r,id;}ask[N];
bool cmp(Que a,Que b) {return a.r<b.r;}

int get(int x) {return fa[x]?fa[x]=get(fa[x]):x;}

void merge(int x,int y) {
	fa[x]=y;pre[y]=pre[x];
	int len=x-pre[x];
	if (len>30&&sum[y]>0||(sum[x]+(sum[y]<<len))>Mo) sum[y]=Mo;
	else sum[y]=sum[x]+(sum[y]<<len);
}

ll query(int l,int r) {return (suf[l]-suf[r+1]*pw[r-l+1]%Mo+Mo)%Mo;}

int main() {
	freopen("border.in","r",stdin);
	freopen("border.out","w",stdout);
	n=read();q=read();
	fo(i,1,n) a[i]=read();
	fo(i,1,q) ask[i].l=read(),ask[i].r=read(),ask[i].id=i;
	sort(ask+1,ask+q+1,cmp);
	fo(i,1,n) pre[i]=i-1,fa[i]=0,sum[i]=a[i];
	fd(i,n,1) suf[i]=((suf[i+1]<<1)+a[i]+Mo)%Mo;
	pw[0]=1;fo(i,1,n) pw[i]=(pw[i-1]<<1)%Mo;
	int j=0;
	fo(i,1,n) {
		while (pre[i]&&sum[i]>=0) merge(pre[i],i);
		S[i]=(S[pre[i]]+(query(pre[i]+1,i)<<1))%Mo;
		while (ask[j+1].r==i) {
			int x=get(ask[++j].l);
			an[ask[j].id]=(S[i]-S[x]+query(ask[j].l,x)+Mo)%Mo;
		} 
	}
	fo(i,1,q) printf("%lld\n",an[i]);
	return 0;
}