//#pragma GCC target("avx,avx2")	
#include<bits/stdc++.h>
//#include<immintrin.h>
using namespace std;

template <typename T> void chmin(T&x,const T &y)
{
	if(x>y)x=y;
}
template <typename T> void chmax(T &x,const T &y)
{
	if(x<y)x=y;
}
typedef int64_t s64;
typedef uint64_t u64;
typedef uint32_t u32;
typedef pair<int,int> pii;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
#define rep0(i,l,r) for(int i=l;i<r;++i)
#define gc (c=getchar())
char readc()
{
	char c;
	while(isspace(gc));
	return c;
}
int read()
{
	char c;
	while(gc<'-');
	if(c=='-')
	{
		int x=gc-'0';
		while(gc>='0')x=x*10+c-'0';
		return -x;
	}
	int x=c-'0';
	while(gc>='0')x=x*10+c-'0';
	return x;
}
#undef gc

const int N=2e5+5;
namespace BIT{
	int c[N];
	int query_suf(int i){
		int ans=0;
		for(;i<N;i+=i&-i)chmax(ans,c[i]);
		return ans;
	}
	void add_pre(int i,int w){
		for(;i;i-=i&-i)chmax(c[i],w);
	}
};
int p[N],dp[N];
namespace ZKW{
	int a[N*3],d=(1<<18)-1;
	void add(int i){
		i+=d;
		while(i){++a[i];i>>=1;}
	}
	int query_max(int k){
		int i=1;
		while(i<=d)
		if(a[i*2+1]>=k){
			i=i*2+1;
		}
		else {
			k-=a[i*2+1];
			i=i*2;
		}
		return i-d;
	}
};

void print(int p[],int n,int k){
	vector<int>q(n);
	rep(i,0,n-1)q[i]=i+1;
	sort(q.begin(),q.end(),[&](int x,int y){return p[x]<p[y];});
	per(i,k-1,0){
		int j=q[i];
		printf("%d ",p[j]);
		while(++j,j<=n && p[j]>p[q[k-1]])printf("%d ",p[j]);
	} 
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
	int n,k;
	cin>>n>>k;
	rep(i,1,n)p[i]=read();
	if(p[1]<=k){print(p,n,k); puts(""); exit(0);}
	rep(i,1,n)if(p[i]<=p[1]){
		dp[i]=BIT::query_suf(p[i])+1;
		BIT::add_pre(p[i],dp[i]);
	}
	static int np[N];
	rep(i,1,n)np[p[i]]=i;
	int max_pos=0,min_cnt=N;
	rep(v,1,p[1]){
		int x=np[v];
		ZKW::add(x);
		int leave=k-dp[x];
		if(leave<=0){
			rep(i,1,n)printf("%d ",p[i]); puts("");
			exit(0);
		}
		if(leave<=v){
			int j=ZKW::query_max(leave);
			if(j>x)
			if(j>max_pos || (j==max_pos && leave<min_cnt)){
				max_pos=j;
				min_cnt=leave;
			}
		}
	}
	cout << max_pos << " " << min_cnt << endl;
	rep(i,1,max_pos-1)printf("%d ",p[i]); 
	print(p+max_pos-1,n-max_pos+1,min_cnt); puts("");
}
 
/* stuff you should look for
	* int overflow, array bounds, uppercase/lowercase, fa[++tot]=tot(UB)  
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/
