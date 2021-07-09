#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 1e5 + 10;

int n, Mod, ans1, ans2, sum, size[maxn];
vector<int> Edge[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline void DFS1(int u)
{
	size[u] = 1;
	for ( auto v : Edge[u] ) { DFS1(v); size[u] += size[v]; } 
	if ( u == 2 ) sum = (sum + size[u] * size[u]) % Mod;
}

inline int Solve() { sum = 0; DFS1(1); return sum; }

inline void DFS(int x)
{
	if ( x == n + 1 ) { ++ ans2; ans1 = (ans1 + Solve()) % Mod; return ; } 
	for ( int j = 1; j < x; ++ j ) if ( x % j == 0 ) 
	{
		Edge[j].push_back(x);
		DFS(x + 1);
		Edge[j].pop_back();
	}
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &Mod);
	DFS(2);
	ans1 = ans1 * power(ans2, Mod - 2) % Mod;
//	ans1 = ans1 * 2 % Mod;
	printf("%lld\n", (ans1 + Mod) % Mod);
	return 0;
}
