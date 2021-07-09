/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年01月31日 星期日 09时15分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, k, Mod, a[maxn], ans, num[maxn];
map<vector<int>, bool> Map;

inline void DFS(int x)
{
	if ( x == n + 1 ) 
	{
		vector<int> p;
		REP(i, 1, n) p.push_back(a[i]);
		if ( !Map.count(p) ) 
		{ 
			Map[p] = true; ++ ans; 
			REP(i, 1, k) num[i] = 0;
			REP(i, 1, n) if ( i & 1 ) ++ num[a[i]]; else -- num[a[i]];
			REP(i, 1, k) assert(num[i] == 0);
		}
		return ; 
	}
	if ( a[x] ) { DFS(x + 1); return ; } 
	REP(col, 1, k)
	{
		REP(j, x + 1, n) 
		{
			if ( a[j] ) break ;
			a[x] = a[j] = col; DFS(x + 1);
			a[x] = a[j] = 0;
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &n, &k, &Mod);
	DFS(1);
	printf("%d\n", ans);
    return 0;
}
