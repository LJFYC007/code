/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年05月28日 星期二 09时16分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int prime[maxn], cnt, v[maxn], n, ans, p[maxn];
map<int, bool> Map;

inline bool pd(int x)
{
	if ( x <= 1 ) return false;
	for ( int i = 2; i * i <= x; ++ i ) 
		if ( x % i == 0 ) return false;
	return true;
}

inline void DFS(int x, int sum, int num)
{
	if ( sum > n ) return ;
	if ( prime[x] > n || x > cnt ) return ;
	if ( n % sum != 0 ) return ;
	if ( n % sum == 0 && pd((n / sum) - 1) ) 
	{ 
		int s = num * ((n / sum) - 1);
		if ( !Map.count(s) ) 
		{
			p[++ ans] = s; 
			Map[s] = true;
		}
	}
	if ( sum == n ) 
	{
		if ( !Map.count(num) )
		{
			p[++ ans] = num; 
			Map[num] = true;
		}
		return ; 
	}
	int cnt = 1, s = 1;
	while ( sum * s <= n ) 
	{
		DFS(x + 1, sum * s, num * cnt);
		cnt *= prime[x]; s += cnt;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	int Max = maxn - 10;
	REP(i, 2, Max)
	{
		if ( !v[i] ) { prime[++ cnt] = i; v[i] = i; }
		REP(j, 1, cnt) 
		{
			if ( prime[j] > i || prime[j] * i > Max ) break ; 
			v[prime[j] * i] = prime[j];
		}
	}
	while ( ~scanf("%d", &n) )
	{
		ans = 0; 
		DFS(1, 1, 1);
		printf("%d\n", ans); if ( ans == 0 ) continue;
		sort ( p + 1, p + ans + 1 );
		REP(i, 1, ans) printf("%d ", p[i]); puts("");
	}
    return 0;
}
