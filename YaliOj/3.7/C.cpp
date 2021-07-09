/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2019年05月23日 星期四 10时36分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 500010;

int n, m, sum[maxn], num[maxn], degree[maxn], f[maxn];

inline int cha(int x)
{
	return f[x] == x ? x : f[x] = cha(f[x]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	while ( ~scanf("%d%d", &n, &m) )
	{
		int ans = 0;
		mem(sum); mem(num); mem(degree);
		REP(i, 1, n) f[i] = i;
		REP(i, 1, m) 
		{ 
			int u, v; scanf("%d%d", &u, &v);
			++ degree[u]; ++ degree[v]; 
			int fx = cha(u), fy = cha(v);
			if ( fx != fy ) f[fx] = fy;
		}
		REP(i, 1, n)
		{
			num[cha(i)] ++ ;
			if ( degree[i] % 2 == 1 ) ++ sum[cha(i)];
		}
		REP(i, 1, n)
		{
			if ( num[i] <= 1 ) continue ;
			if ( sum[i] == 0 ) ++ ans;
			else ans += sum[i] / 2;
		}
		printf("%d\n", ans);
	}
    return 0;
}
