#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9'){ t=c=='-'?-1:1; c=getchar(); }
	while(c>='0'&&c<='9'){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return r*t;
}
#define pii std::pair<int,int>
#define F first
#define S second
const int N=500010;
int n,m;
int vis[N];
std::vector<pii> t[N];
std::vector<int> R[N];
std::vector<int> Ans;
std::vector<int> a1,a2;
int u[N],v[N];
pii Back(std::vector<pii> &e)
{
	while(!e.empty()&&vis[std::abs(e.back().S)]) e.pop_back();
	if(e.empty()) return {0,0};
	vis[std::abs(e.back().S)]=1; return e.back();
}
void dfs(int u)
{
	pii b;
	while((b=Back(t[u]))!=pii{0,0}){ dfs(b.F); Ans.push_back(b.S); }
	while(!R[u].empty()){ Ans.push_back(R[u].back()); R[u].pop_back(); }
}
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	n=read(); m=read();
	fr(i,1,n)
	{
		int l=read(),u,v;
		if(l==1){ u=read(); v=m+1; }
		else{ u=read(); v=read(); }
		::u[i]=u; ::v[i]=v;
		if(u!=v){ t[u].push_back({v,i}); t[v].push_back({u,-i}); }
		else{ R[u].push_back(i); }
	}
//	fr(i,1,m+1){ printf("%d: ",i); for(auto j:t[i]) printf("{%d,%d} ",j.F,j.S);; putchar(10); }
	fr(i,1,m) if(t[i].size()&1) dfs(i);
	if(Ans.empty()) dfs(m+1);
//	for(auto i:Ans) printf("%d ",i);; putchar(10);
//	std::reverse(Ans.begin(),Ans.end());
	fr(i,1,m) while(R[i].size()>=2){ a1.push_back(R[i].back()); R[i].pop_back(); a2.push_back(R[i].back()); R[i].pop_back(); }
	fr(i,1,m)
	{
		static int lst[N]; pii b;
		while((b=Back(t[i]))!=pii{0,0})
		{
			if(lst[b.F]){ a1.push_back(lst[b.F]); a2.push_back(b.S); lst[b.F]=0; }
			else lst[b.F]=b.S;
		}
	}
	fr(i,0,Ans.size()-1) (i&1?a1:a2).push_back(Ans[i]);
	fr(i,1,m) if(!R[i].empty()) a1.push_back(R[i].back());
	assert(a1.size()+a2.size()==n); static int ans[N]; n=0; std::reverse(a2.begin(),a2.end());
	for(auto i:a1) ans[++n]=i;
	for(auto i:a2) ans[++n]=-i;
	fr(i,1,n) printf("%d%c",std::abs(ans[i]),i==n?'\n':' ');
	fr(i,1,n) printf("%d%c",ans[i]>=0,i==n?'\n':' ');
	static int A[N]; int p=0;
	fr(i,1,n)
	{
		int x=std::abs(ans[i]),y=ans[i]>=0;
		if(v[x]==m+1) A[++p]=u[x];
		else if(!y){ A[++p]=u[x]; A[++p]=v[x]; }
		else{ A[++p]=v[x]; A[++p]=u[x]; }
	}
	fr(i,1,p) assert(A[i]==A[p-i+1]);
//	fr(i,1,p) printf("%d%c",A[i],i==p?'\n':' ');
	return 0;
}
