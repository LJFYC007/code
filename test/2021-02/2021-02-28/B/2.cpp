#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int Mod = 1e9 + 7;

int n, m, K, p[10];
struct node
{
	int a[30], w;

	inline void INIT()
	{
		int x = w, t = 0;
		while ( x ) { a[t ++] = x % 2; x /= 2; } 
		m = max(m, t);
	}
} L, Y, X; 

inline int Get(int s, int pos) { return (s / p[pos - 1]) % 3; }

inline int DFS(int i, int j, int x, int s, int w, int a, int b, int c, int d)
{
	if ( i == m ) 
	{
		
	}
	
	int ret = DFS(i, j + 1, 0, s, w, a, b, c, d) + DFS(i, j + 1, 1, :;
	return ret;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	cin >> n >> L.w >> Y.w >> X.w >> K; -- Y.w;
	L.INIT(); Y.INIT(); X.INIT(); p[0] = 1; REP(i, 1, 9) p[i] = p[i - 1] * 3;
	int ans = (DFS(0, 1, 0, 0, 0, 0, 0, 0, 0) + DFS(0, 1, 1, 0, 0, 0, 0, 0, 0)) % Mod;
	cout << ans << endl;
	return 0;
}
