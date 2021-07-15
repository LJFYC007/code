#include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
	int a=0;char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while('0'<=c&&c<='9'){
		a=a*10+c-48;
		c=getchar();
	}
	return a;
}
#define pii pair<int,int>
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define MN 5005
int T,n,m,q;
pii a[MN],b[MN];
int up[MN],dw[MN];
int qry(pii *a,pii w){
	int p=lower_bound(a+1,a+1+n,w)-a;
	if(a[p]==w)return 0;
	p=lower_bound(a+1,a+1+n,mp(w.x,0ll))-a;
	up[p]=m;dw[p]=0;
	int l=p;
	for(int i=p-1;i;--i){
		up[i]=up[i+1];
		dw[i]=dw[i+1];
		if(i!=p-1){
			if(a[i+1].y>=w.y)up[i]=min(up[i],a[i+1].y);
			else dw[i]=max(dw[i],a[i+1].y);
		}
		if(a[p].x-a[i].x<=up[i]-dw[i]&&up[i]>w.y&&dw[i]<w.y)l=i;
		else break;
	}
	int res=0;
	if(a[p].x>w.x)res=a[p].x-a[l].x;
	for(int i=p+1;i<=n;++i){
		up[i]=up[i-1];
		dw[i]=dw[i-1];
		if(a[i-1].y>=w.y)up[i]=min(up[i],a[i-1].y);
		else dw[i]=max(dw[i],a[i-1].y);
		if(up[i]==w.y||dw[i]==w.y)break;
		while(l<p&&!(a[i].x-a[l].x<=min(up[i],up[l])-max(dw[i],dw[l])&&up[l]>w.y&&dw[l]<w.y)){l++;}
		if(l>=p)break;
		if(a[i].x>w.x){
//			cerr<<"OK: "<<a[l].x<<" "<<a[i].x<<endl;
			res=max(res,a[i].x-a[l].x);
		}
	}
//	cerr<<"done"<<endl;
	return res;
}
signed main(){
    freopen("input.txt", "r", stdin);
    freopen("ansput.txt", "w", stdout);
	T=read();
	while(T--){
		m=read();n=read();
		for(int i=1;i<=n;++i){
			a[i].x=read(),a[i].y=read();
			b[i].y=a[i].x,b[i].x=a[i].y;
		}
		a[++n]=mp(0,0);b[n]=mp(0,0);
		a[++n]=mp(m,0);b[n]=mp(m,0);
		sort(a+1,a+1+n);
		sort(b+1,b+1+n);
		q=read();
		while(q--){
			pii w;w.x=read(),w.y=read();
			int A=qry(a,w);
			swap(w.x,w.y);
			int B=qry(b,w);
			printf("%lld\n",max(A,B)*max(A,B));
		}
	}
	return 0;
}
