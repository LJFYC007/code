/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年07月15日 星期四 09时01分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 10010;

int T, n, m, q;
pii a[maxn]; deque<int> Q[2];

inline bool Check(int len, int x, int y)
{
	Q[0].clear(); Q[1].clear();
	for ( int i = 1, j; i <= n; i = j ) 
	{
		while ( !Q[0].empty() && a[Q[0].front()].x <= a[i].x - len ) Q[0].pop_front();
		while ( !Q[1].empty() && a[Q[1].front()].x <= a[i].x - len ) Q[1].pop_front();
		int Max = Q[0].empty() ? 0 : a[Q[0].front()].y;
		int Min = Q[1].empty() ? m : a[Q[1].front()].y;
		if ( a[i].x > x && a[i - 1].x < x && a[i].x - a[i - 1].x >= len ) return true;
		if ( a[i].x > x && a[i].x - len < x && a[i].x - len >= 0 && Min - Max >= len ) return true;
		j = i;	
		while ( j <= n && a[j].x == a[i].x ) 
		{
			while ( !Q[0].empty() && a[j].y <= y && a[j].y > a[Q[0].back()].y ) Q[0].pop_back();
			while ( !Q[1].empty() && a[j].y >= y && a[j].y < a[Q[1].back()].y ) Q[1].pop_back();
			if ( a[j].y <= y ) Q[0].push_back(j);
			if ( a[j].y >= y ) Q[1].push_back(j);
			++ j;
		}
	}
	return false;
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
		scanf("%d%d", &m, &n); 
		REP(i, 1, n) scanf("%d%d", &a[i].x, &a[i].y);
		a[++ n] = pii(m, m);
		sort(a + 1, a + n + 1);
		scanf("%d", &q);
		REP(i, 1, q) 
		{
			int x, y; scanf("%d%d", &x, &y); 
			int L = 2, R = 1e9, ans = 0;
			while ( L <= R ) 
			{
				int Mid = L + R >> 1;
				if ( Check(Mid, x, y) ) { ans = Mid; L = Mid + 1; }
				else R = Mid - 1;
			}
			printf("%lld\n", 1ll * ans * ans);
		}
	}
    return 0;
}
