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
#define int long long
typedef long long LL;

const int maxn = 52;

int n, m, k, q, a[maxn][maxn], b[maxn][maxn], ans, III, cnt, Max, f[110], sum;
int dt[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool vis[maxn][maxn], use[maxn][maxn];
vector<pii> A;
vector<pii> pos; queue<pii> Q;

inline void Delete(int i, int j) 
{ 
	if ( i < 1 || j < 1 || i > n || j > m || vis[i][j] || !a[i][j] ) return ; 
	ans += a[i][j] * III; vis[i][j] = true; Q.push(pii(i, j)); 
}

inline void DFS(int x, int y)
{
	if ( vis[x][y] || !use[x][y] ) return ; Delete(x, y); ++ cnt;
	REP(i, 0, 3)
	{
		int u = x + dt[i][0], v = y + dt[i][1];
		if ( a[u][v] == a[x][y] ) DFS(u, v);
	}
}

inline bool Check()
{
	mem(use); bool flag = false; pos.clear();
	REP(i, 1, n) REP(j, 1, m) 
	{
		if ( j <= m - 2 && a[i][j] && a[i][j] == a[i][j + 1] && a[i][j] == a[i][j + 2] ) 
		{
			flag = true;
			pos.push_back(pii(i, j)); use[i][j] = use[i][j + 1] = use[i][j + 2] = true;
		} 
		if ( i <= n - 2 && a[i][j] && a[i][j] == a[i + 1][j] && a[i + 2][j] == a[i][j] ) 
		{
			flag = true;
			pos.push_back(pii(i, j)); use[i][j] = use[i + 1][j] = use[i + 2][j] = true;
		}
	}
	return flag;
}

inline void Erase()
{
	mem(vis); while ( !Q.empty() ) Q.pop();
	for ( int i = 0; i < pos.size(); ++ i ) 
	{
		int x = pos[i].first, y = pos[i].second;
		if ( vis[x][y] ) continue ; 
		cnt = 0; DFS(x, y); ans += 50 * (cnt - 3) * (cnt - 3);
	}
	while ( !Q.empty() ) 
	{
		int x = Q.front().first, y = Q.front().second; Q.pop();
		if ( b[x][y] == 1 || b[x][y] == 3 ) REP(i, 1, m) Delete(x, i); 
		if ( b[x][y] == 2 || b[x][y] == 3 ) REP(i, 1, n) Delete(i, y); 
		if ( b[x][y] == 4 ) REP(i, x - 1, x + 1) REP(j, y - 1, y + 1) Delete(i, j);
		if ( b[x][y] == 5 ) REP(i, x - 2, x + 2) REP(j, y - 2, y + 2) Delete(i, j);
		if ( b[x][y] == 6 ) 
		{
			REP(i, 1, n) REP(j, 1, m) if ( a[i][j] == a[x][y] ) Delete(i, j);
		}
	}
}

inline void Fall()
{
	REP(i, 1, n) REP(j, 1, m) if ( vis[i][j] ) a[i][j] = b[i][j] = 0;
	REP(j, 1, m)
	{
		int pos = n;
		for ( int i = n; i >= 1; -- i )		
		{
			if ( !a[i][j] ) continue ; 
			if ( i == pos ) { -- pos; continue ; }   
			swap(a[i][j], a[pos][j]); swap(b[i][j], b[pos][j]); 
			-- pos;
		}
	}
}

inline void DFS(int x)
{
	if ( x == 5 ) 
	{
		vector<pii> a;
		REP(i, 1, k) if ( f[i] ) a.push_back(pii(-f[i], i));
		sort(a.begin(), a.end());

		if ( a.size() == 1 ) Max = max(Max, 1000 + 10 * a[0].second);
		if ( a.size() == 2 ) 
		{
			if ( a[0].first == -4 ) Max = max(Max, 750 + 5 * a[0].second);
			if ( a[0].first == -3 ) Max = max(Max, 500 + 3 * a[0].second + a[1].second);
		}
		if ( a.size() == 3 ) 
		{
			if ( a[0].first == -3 ) Max = max(Max, 300 + 3 * a[0].second);
			if ( a[0].first == -2 && a[1].first == -2 ) 
				Max = max(Max, 200 + a[0].second + 2 * a[1].second);
		}
		if ( a.size() == 4 ) 
			Max = max(Max, 100 + a[0].second * 2);
		if ( a.size() == 5 ) 
			Max = max(Max, 50 + a[4].second);
		return ;
	}
	if ( A[x].first ) { ++ f[A[x].first]; DFS(x + 1); -- f[A[x].first]; }
	if ( A[x].second ) { ++ f[A[x].second]; DFS(x + 1); -- f[A[x].second]; }
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld%lld", &n, &m, &k, &q);
	REP(i, 1, n) REP(j, 1, m) scanf("%lld", &a[i][j]);
	REP(i, 1, n) REP(j, 1, m) scanf("%lld", &b[i][j]);
	int ttt = 0;
	vector<pii> t;
	REP(ooo, 1, q)
	{
		int u1, u2, v1, v2; scanf("%lld%lld%lld%lld", &u1, &v1, &u2, &v2);
		if ( !a[u1][v1] || !a[u2][v2] ) continue ; 
		if ( abs(u1 - u2) + abs(v1 - v2) != 1 ) continue ; 
		swap(a[u1][v1], a[u2][v2]); swap(b[u1][v1], b[u2][v2]);
		if ( !Check() ) { swap(a[u1][v1], a[u2][v2]); swap(b[u1][v1], b[u2][v2]); continue ; } 
		++ ttt;
		t.push_back(pii(use[u1][v1] ? a[u1][v1] : 0, use[u2][v2] ? a[u2][v2] : 0));
		III = 1; Erase(); Fall();

		while ( Check() ) { ++ III; Erase(); Fall(); }
		ans += 80 * (III - 1) * (III - 1);
	}		

	for ( int i = 4; i < t.size(); ++ i ) 
	{
		A.clear(); REP(j, i - 4, i) A.push_back(t[j]);
		Max = 0; DFS(0); ans += Max;
	}

	if ( ttt == q ) ans += 1000;
	int num = 0; REP(i, 1, n) REP(j, 1, m) if ( a[i][j] ) ++ num;
	if ( !num ) ans += 10000;
	printf("%lld\n", ans);
    return 0;
}
