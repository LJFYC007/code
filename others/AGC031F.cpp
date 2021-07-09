/***************************************************************
	File name: AGC031F.cpp
	Author: ljfcnyali
	Create time: 2021年03月12日 星期五 19时35分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, q, Mod, g, f[maxn]; 
struct node { int u, v, w; } Edge[maxn];
bool vis[2][maxn];

inline int GetId(int x, int p, int q) { return (x - 1) * 6 + p * 3 + q + 1; } 

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); } 

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d%d", &n, &m, &q, &Mod); g = Mod;
	REP(i, 1, m) scanf("%d%d%d", &Edge[i].u, &Edge[i].v, &Edge[i].w);
	REP(i, 2, m) g = __gcd(g, abs(Edge[i].w - Edge[1].w)); 
	int z = Edge[1].w % g; REP(i, 1, m) Edge[i].w /= g; Mod = __gcd(Mod, g + g + g);
	REP(i, 1, n * 6) f[i] = i;
	REP(i, 1, m) REP(p, 0, 1) REP(q, 0, 2)
	{
		int x = GetId(Edge[i].u, p, q), y = GetId(Edge[i].v, (p + 1) % 2, (q + q + Edge[i].w) % 3);
		int fx = find(x), fy = find(y);
		if ( fx != fy ) f[fx] = fy;

		x = GetId(Edge[i].v, p, q); y = GetId(Edge[i].u, (p + 1) % 2, (q + q + Edge[i].w) % 3);
		fx = find(x); fy = find(y);
		if ( fx != fy ) f[fx] = fy;
	}
	int val = z % Mod;
	REP(k, 0, Mod - 1) { vis[k & 1][val] = true; val = val * 2 % Mod; } 

	while ( q -- ) 
	{
		int s, t, r; scanf("%d%d%d", &s, &t, &r);
		bool ans = false;
		REP(p, 0, 1) REP(q, 0, 2)
		{
			int fx = find(GetId(t, 0, 0)), fy = find(GetId(s, p, q));
			if ( fx != fy ) continue ; 
			int x = ((r + z - q * g) % Mod + Mod) % Mod;			
			if ( vis[p][x] ) ans = true;
		}
		if ( ans ) puts("YES"); else puts("NO");
	}
    return 0;
}
