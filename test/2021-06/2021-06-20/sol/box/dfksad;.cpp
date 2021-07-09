#include<bits/stdc++.h>
using namespace std;

#define cout cerr
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)

typedef long long ll;
typedef pair<int,int> pii;
#define FR first
#define SE second

inline void rd(int &x){
	x=0;char ch=getchar();int f=1;
	while(ch<'0'||ch>'9'){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	x*=f;
}

int n,q;
#define Maxn 100010
int a[Maxn];

struct Dat{
	int a,b,c,ad;
	Dat(){a=b=c=ad=0;}
	Dat(int _a,int _b,int _c,int _ad){a=_a;b=_b;c=_c;ad=_ad;}
}h1[Maxn<<3],h2[Maxn<<3],h3[Maxn<<3],h4[Maxn<<3];
int cnt1,cnt2,cnt3,cnt4;
bool cmp(Dat x,Dat y){return x.a<y.a;}

int L[Maxn],R[Maxn],T=0;
set<int> S[Maxn];
int ans[Maxn<<1];

void Modify1(int u,int t){
	if(L[u]==t)return;
	h2[++cnt2]=Dat(u-1,n-L[u],T,-1);
	h2[++cnt2]=Dat(u-1,n-t,T,1);
	
	if(L[u]!=n+1)h3[++cnt3]=Dat(n+1-u,L[u],T,-1);
	L[u]=t;
	if(t!=n+1)h3[++cnt3]=Dat(n+1-u,t,T,1);
}

void Modify2(int u,int t){
	if(R[u]==t)return;
	h4[++cnt4]=Dat(n-u,R[u]-1,T,-1);
	h4[++cnt4]=Dat(n-u,t-1,T,1);
	
	if(R[u])h1[++cnt1]=Dat(u,n+1-R[u],T,-1);
	R[u]=t;
	if(t)h1[++cnt1]=Dat(u,n+1-t,T,1);
}

int lowbit(int x){return x&(-x);}
int sum[Maxn];
void Add(int x,int ad){
	for(int i=x;i<=q+1;i+=lowbit(i))sum[i]+=ad;
}
int query(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i))res+=sum[i];
	return res;
}

Dat hh[Maxn<<3];
void merge(Dat *B,int L,int pos,int R){
	int hd1=L,hd2=pos;int h=0;
	while(hd1<pos&&hd2<R){
		if(B[hd1].b<B[hd2].b)hh[++h]=B[hd1++];
		else hh[++h]=B[hd2++];
	}
	rep(i,hd1,pos-1)hh[++h]=B[i];
	rep(i,hd2,R-1)hh[++h]=B[i];
	rep(i,1,h)B[L+i-1]=hh[i];
}

bool caonima(Dat x,Dat y){
	return x.b<y.b;
}
void solve(Dat *A,Dat *B,int l,int r,int L,int R){
	if(l==r){
		rep(i,L,R-1)
			if(A[l].a<=B[i].a&&A[l].b<=B[i].b&&A[l].c<=B[i].c)
				ans[B[i].c]+=B[i].ad*A[l].ad;
		sort(B+L,B+R,caonima);
		return;
	}
	int mid=(l+r)>>1;int pos=R,t=A[mid].a;
	rep(i,L,R-1)
		if(B[i].a>=t){
			pos=i;
			break;
		}
	solve(A,B,l,mid,L,pos);solve(A,B,mid+1,r,pos,R);
	int at=l-1;
	rep(i,pos,R-1){
		while(at+1<=mid&&A[at+1].b<=B[i].b){
			at++;
			Add(A[at].c,A[at].ad);
		}
		ans[B[i].c]+=query(B[i].c)*B[i].ad;
	}
	rep(i,l,at)Add(A[i].c,-A[i].ad);

	merge(A,l,mid+1,r+1);merge(B,L,pos,R);
}

pii calc(int k){
    if(S[k].empty())return pii(n+1,0);
    set<int>::iterator it=S[k].begin();pii res;res.FR=(*it);
    it=S[k].end();it--;res.SE=(*it);
    return res;
}

void gao(int u){
    pii cur=calc(u);
    Modify1(u,cur.FR);Modify2(u,cur.SE);
}

int main(){
	rd(n);
	rep(i,1,n)rd(a[i]),S[a[i]].insert(i);
	T=1;
	rep(i,1,n){
		int u=i;
		pii cur=calc(i);
		L[i]=cur.FR;R[i]=cur.SE;
		if(cur.FR<=n){
			h3[++cnt3]=Dat(n+1-u,cur.FR,1,1);
			h1[++cnt1]=Dat(u,n+1-cur.SE,1,1);
	
			h2[++cnt2]=Dat(u-1,n-cur.FR,1,1);
		}
	}
	rd(q);
	int x,y;
	rep(i,2,q+1){
		rd(x);rd(y);
		int pre=a[x];S[pre].erase(x);
		a[x]=y;S[y].insert(x);
		T++;gao(pre);T++;gao(y);
	}
	sort(h1+1,h1+cnt1+1,cmp);sort(h2+1,h2+cnt2+1,cmp);
	sort(h3+1,h3+cnt3+1,cmp);sort(h4+1,h4+cnt4+1,cmp);
	if(cnt1&&cnt2)solve(h1,h2,1,cnt1,1,cnt2+1);
	if(cnt3&&cnt4)solve(h3,h4,1,cnt3,1,cnt4+1);
	ll Ans=0;
	rep(i,1,q+1){
		Ans+=ans[i*2-1]+ans[i*2-2];
		printf("%lld\n",Ans);
	}
	return 0;
}
