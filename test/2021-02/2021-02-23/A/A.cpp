/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年02月23日 星期二 15时17分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int Mod = 998244353;
const int N = 100000000;

int n, m, q;
vector<pii> Edge[maxn];
bool vis[maxn], unuse[maxn];
struct node
{
	vector<int> a; int val;
	inline void INIT() { a.clear(); val = -1; } 
	inline void Set() { a.push_back(1); val = 1; } 
} f[maxn];

node operator +(node f, node g)
{
	node h; h.a.clear(); h.val = (f.val + g.val) % Mod;
	int n = max(f.a.size(), g.a.size()); h.a.resize(n); f.a.resize(n); g.a.resize(n);
	REP(i, 0, n - 1) h.a[i] = (f.a[i] + g.a[i]) % Mod;
	for ( int i = 0; i < h.a.size(); ++ i ) if ( h.a[i] >= N ) 
	{
		if ( i + 1 == h.a.size() ) h.a.push_back(h.a[i] / N);
		else h.a[i + 1] += h.a[i] / N;	
		h.a[i] %= N;
	}
	return h;	
}

bool operator <(node f, node g)
{
	if ( f.a.size() != g.a.size() ) return f.a.size() < g.a.size();
	for ( int i = f.a.size() - 1; i >= 0; -- i ) 
		if ( f.a[i] != g.a[i] ) return f.a[i] < g.a[i];
	return 0;
}

node max(node a, node b) { return a < b ? a : b; } 

inline void DFS(int x)
{
	vis[x] = true; if ( unuse[x] ) return ; 
	if ( x <= m ) { f[x].Set(); return ; } 
	for ( auto it : Edge[x] ) 
	{
		if ( !vis[it.first] ) DFS(it.first);
		if ( !vis[it.second] ) DFS(it.second);
		if ( f[it.first].val == -1 || f[it.second].val == -1 ) continue ; 
		if ( f[x].val == -1 ) f[x] = f[it.first] + f[it.second];
		else f[x] = min(f[x], f[it.first] + f[it.second]);
	}
}

inline void Solve(int x) { REP(i, 1, n) { vis[i] = false; f[i].INIT(); } DFS(x); }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &m, &q);
	while ( q -- ) 
	{
		int op, x, y, z; scanf("%lld", &op);
		if ( op == 1 ) 
		{
			scanf("%lld%lld", &x, &y); unuse[y] = true; Solve(x); unuse[y] = false;
			if ( f[x].val == -1 ) { Solve(x); printf("%d\n", f[x].val == -1 ? -1 : 1); }
			else puts("0");
		}
		if ( op == 2 ) { scanf("%lld", &x); Solve(x); printf("%lld\n", f[x].val); }
		if ( op == 3 ) 
		{
			scanf("%lld%lld%lld", &x, &y, &z);
			Edge[z].push_back(pii(x, y));
		}
	}
    return 0;
}
