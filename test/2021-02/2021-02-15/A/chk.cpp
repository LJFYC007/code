/***************************************************************
	File name: chk.cpp
	Author: ljfcnyali
	Create time: 2021年02月15日 星期一 09时51分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

bool f[3010][3010];

int main()
{
    freopen("input.txt", "r", stdin);
	int n; scanf("%d", &n);
    freopen("output.txt", "r", stdin);
	int m; scanf("%d", &m);
	REP(i, 1, m)
	{
		int p, q; scanf("%d%d", &p, &q);
		vector<int> a, b;
		REP(j, 1, p) { int x; scanf("%d", &x); a.push_back(x); }
		REP(j, 1, q) { int x; scanf("%d", &x); b.push_back(x); }
		for ( auto x : a ) for ( auto y : b ) f[x][y] = true;
	}
	REP(i, 1, n) REP(j, 1, n) 
	{
		if ( j <= i && i <= j + 1 ) 
		{
			if ( f[i][j] ) { cerr << "NO1" << " " << i << " " << j << endl; return 0; } 
		}
		else
		{
			if ( !f[i][j] ) { cerr << "NO2" << " " << i << " " << j << endl; return 0; } 
		}
	}
	cerr << "YES" << endl;
    return 0;
}
