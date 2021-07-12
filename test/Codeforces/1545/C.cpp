/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年07月12日 星期一 19时10分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int T, n, a[maxn][maxn], ans, num[maxn];
vector<int> p, q;

inline void Erase(int x)
{
	q.push_back(x); vector<int> b;
	for ( auto it : p ) if ( it != x ) 
	{
		bool flag = true;
		REP(j, 1, n) if ( a[it][j] == a[x][j] ) { flag = false; break ; }
		if ( flag ) b.push_back(it);
	}
	p = b;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d", &n); ans = 1; p.clear(); q.clear();
		REP(i, 1, n + n) REP(j, 1, n) scanf("%d", &a[i][j]);
		REP(i, 1, n + n) p.push_back(i);
		
		while ( !p.empty() ) 
		{
			REP(j, 1, n) 
			{
				mem(num); for ( auto it : p ) ++ num[a[it][j]];
				for ( auto it : p ) if ( num[a[it][j]] == 1 ) { Erase(it); goto Next; }		
			}
			ans = (ans + ans) % 998244353; Erase(p[0]);
Next : ; 
		}
		printf("%d\n", ans);
		for ( auto it : q ) printf("%d ", it); puts("");
	}
    return 0;
}
