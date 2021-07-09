/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年03月14日 星期日 09时33分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;

int n, k, a[maxn][maxn];
bool vis[maxn];

inline void DFS(int x, int sum)
{
	if ( x == n + 1 ) 
	{
		if ( sum % k == 0 ) { puts("Yes"); exit(0); }
		return ; 
	}
	REP(i, 1, n) if ( !vis[i] && a[x][i] != -1 ) 
	{
		vis[i] = true; DFS(x + 1, sum + a[x][i]);
		vis[i] = false;
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	REP(i, 1, n) REP(j, 1, n) scanf("%d", &a[i][j]);
	DFS(1, 0);
	puts("No");
	cerr << " Fuck ";
    return 0;
}
