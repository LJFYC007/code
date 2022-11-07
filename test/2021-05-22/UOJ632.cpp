/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 8010;
const int Mod = 998244353;

int n, a[maxn][maxn]; vector<int> ans; vector<pii> p;
char s[maxn]; bool vis[2][maxn];

vector<int> operator + (vector<int> a, vector<int> b)
{
	int n = a.size() + b.size(); a.resize(n); b.resize(n);
	REP(i, 1, n - 1) a[i] = (a[i] + b[i]) % Mod; return a;
}

vector<int> operator * (vector<int> a, vector<int> b)
{
	int n = a.size(), m = b.size(); vector<int> c(n + m - 1);
	REP(i, 0, n - 1) REP(j, 0, m - 1) c[i + j] = (c[i + j] + 1ll * a[i] * b[j] % Mod) % Mod;
	return c;
}

inline void DFS(int u, int op)
{
	for ( auto v : p ) if ( a[u][v.first] != op ) 
		vis[op][v.first] = true;
}

inline vector<int> Solve(vector<pii> P)
{
	p = P; int n = p.size(); 
	if ( n == 1 ) { vector<int> ans(2); ans[0] = ans[1] = 1; return ans; }

	int x = 0, y = 0; 
	for ( int i = 1; i < n; ++ i )
	{
		if ( p[x].second > p[i].second ) x = i;
		if ( p[y].second < p[i].second ) y = i;
	}
	x = p[x].first; y = p[y].first;
	for ( auto it : p ) vis[0][it.first] = vis[1][it.first] = false;
	DFS(x, 0); DFS(y, 1); vis[0][x] = vis[1][y] = true;

	queue<int> Q[2]; REP(o, 0, 1) for ( auto it : p ) if ( vis[o][it.first] ) Q[o].push(it.first);
	while ( !Q[0].empty() && !Q[1].empty() ) REP(o, 0, 1)
	{
		int u = Q[o].front(); Q[o].pop();
		for ( auto it : p ) if ( !vis[o][it.first] && a[u][it.first] != o ) 
			vis[o][it.first] = true;
	}

	if ( Q[1].empty() ) 
	{
		vector<pii> A, B;
		for ( auto it : p ) if ( vis[1][it.first] ) A.push_back(it); else B.push_back(it);
		for ( int i = 0; i < A.size(); ++ i ) 
			A[i].second = A.size() - n + A[i].second;
		for ( int i = 0; i < B.size(); ++ i ) 
			B[i].second = B.size() - n + B[i].second;
		return Solve(A) * Solve(B);
	}

	vector<pii> A, B;
	for ( auto it : p ) if ( vis[0][it.first] ) A.push_back(it); else B.push_back(it);
	return Solve(A) + Solve(B);
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n - 1)
	{
		scanf("%s", s);
		REP(j, i + 1, n)
		{
			char c = s[(j - i - 1) / 4];
			int x = (c >= '0' && c <= '9') ? (c - '0') : (c - 'A' + 10);
			if ( (x >> (j - i - 1) % 4) & 1 ) a[i][j] = a[j][i] = true;
		}
	}
	vector<pii> p;
	REP(i, 1, n) { int num = 0; REP(j, 1, n) if ( a[i][j] ) ++ num; p.push_back(pii(i, num)); }
	ans = Solve(p); 
	REP(i, 1, n) printf("%d ", ans[i]); puts("");
    return 0;
}
