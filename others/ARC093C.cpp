/***************************************************************
	File name: ARC093C.cpp
	Author: ljfcnyali
	Create time: 2021年05月29日 星期六 16时35分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e9;
const int Mod = 1e9 + 7;

int n, m, k, f[maxn], Begin[maxn], Next[maxn], To[maxn], e, W[maxn], ans;
struct node { int u, v, w; } Edge[maxn]; vector<int> p;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
inline void add(int u, int v, int w) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; W[e] = w; }
inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); } 

inline int DFS(int u, int fa, int t)
{
	if ( u == t ) return -INF; int ret = INF;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		if ( ret == INF ) ret = max(DFS(v, u, t), W[i]);
	}
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &m, &k);
	REP(i, 1, n) f[i] = i;
	REP(i, 1, m) scanf("%lld%lld%lld", &Edge[i].u, &Edge[i].v, &Edge[i].w);
	sort(Edge + 1, Edge + m + 1, [](const node &a, const node &b) { return a.w < b.w; });
	int sum = 0, num1 = 0, num2 = 0;
	REP(i, 1, m)
	{
		int fx = find(Edge[i].u), fy = find(Edge[i].v);
		if ( fx != fy ) 
		{ 
			f[fx] = fy; sum += Edge[i].w;
			add(Edge[i].u, Edge[i].v, Edge[i].w); add(Edge[i].v, Edge[i].u, Edge[i].w);
		}
		else p.push_back(Edge[i].w - DFS(Edge[i].u, 0, Edge[i].v));
	}
	for ( auto it : p ) if ( it + sum == k ) ++ num1; else if ( it + sum > k ) ++ num2;
	if ( sum == k ) ans = (power(2, n - 1) - 2) * power(2, m - n + 1) % Mod;
	ans = (ans + (power(2, num1) - 1) * power(2, num2 + 1)) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
