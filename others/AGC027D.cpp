/***************************************************************
	File name: AGC027D.cpp
	Author: ljfcnyali
	Create time: 2021年04月21日 星期三 15时57分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 510;
const int maxm = 3e6 + 10;
const int N = 1e15;

int n, m, a[maxn][maxn], prime[maxm], tot, p[maxn], q[maxn];
int dt[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
bool vis[maxm];

inline int lcm(int x, int y) { if ( !x || !y ) return x + y; return x / __gcd(x, y) * y; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	REP(i, 2, maxm - 10)
	{
		if ( !vis[i] ) prime[++ tot] = i;
		for ( int j = 1; j <= tot && i * prime[j] < maxm; ++ j ) 
		{
			vis[i * prime[j]] = true;
			if ( i % prime[j] == 0 ) break ; 
		}
	}

	bool flag = false; scanf("%lld", &n); if ( n % 2 == 0 ) { ++ n; flag = true; } 

	REP(i, 1, n) if ( i & 1 ) p[i] = prime[++ m];
	REP(i, 1, n) if ( i & 1 ) q[i] = prime[++ m];
	REP(i, 1, n) if ( !(i & 1) ) p[i] = prime[++ m];
	REP(i, 1, n) if ( !(i & 1) ) q[i] = prime[++ m];

	REP(i, 1, n) REP(j, 1, n) if ( !((i + j) & 1) ) 
	{
		int x = (i - j) / 2 + (n + 1) / 2, y = (i + j) / 2;
		a[i][j] = p[x] * q[y];
	}
	REP(i, 1, n) REP(j, 1, n) if ( (i + j) & 1 ) a[i][j] = lcm(lcm(a[i - 1][j], a[i][j - 1]), lcm(a[i + 1][j], a[i][j + 1])) + 1;

	if ( flag ) -- n;
	REP(i, 1, n) { REP(j, 1, n) printf("%lld ", a[i][j]); puts(""); } 
	
	REP(i, 1, n) REP(j, 1, n) REP(o, 0, 3)
	{
		int x = i + dt[o][0], y = j + dt[o][1];
		if ( x < 1 || y < 1 || x > n || y > n ) continue ; 
		assert(max(a[x][y], a[i][j]) % min(a[x][y], a[i][j]) == 1);
		if ( a[i][j] > N ) cerr << a[i][j] << endl;
		assert(a[i][j] <= N);
	}
    return 0;
}
