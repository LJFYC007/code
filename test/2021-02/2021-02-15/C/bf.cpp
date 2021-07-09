/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年02月15日 星期一 10时34分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, k, a[maxn], m, ans;

inline void DFS(int lst, int x, int sum)
{
	if ( x == n + 1 ) 
	{
		if ( !sum ) ++ ans;
		return ; 	
	}
	// REP(i, 0, m - 1) DFS(i, x + 1, sum ^ i);
	REP(i, lst, m - 1) DFS(i + 1, x + 1, sum ^ i);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	REP(i, 1, k) { scanf("%d", &a[i]); m |= 1 << a[i]; }
	DFS(0, 1, 0); printf("%d\n", ans);
	return 0;
	ans = 0; -- n; DFS(0, 1, 0); printf("%d\n", ans);
	ans = 0; -- n; DFS(0, 1, 0); printf("%d\n", ans);
	ans = 0; -- n; DFS(0, 1, 0); printf("%d\n", ans);
	ans = 0; -- n; DFS(0, 1, 0); printf("%d\n", ans);
	ans = 0; -- n; DFS(0, 1, 0); printf("%d\n", ans);
    return 0;
}
