/***************************************************************
	File name: AGC029D.cpp
	Author: ljfcnyali
	Create time: 2021年07月11日 星期日 15时28分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int h, w, n, ans = INF; 
set<int> Set[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d%d", &h, &w, &n);
	REP(i, 1, n) { int x, y; scanf("%d%d", &x, &y); Set[y].insert(x); }
	REP(i, 1, w) Set[i].insert(h + 1);
	int pos = 1;
	REP(i, 1, w) if ( pos <= h ) 
	{
		ans = min(ans, (*Set[i].lower_bound(pos)) - 1);
		++ pos;
		while ( Set[i + 1].find(pos) != Set[i + 1].end() ) ++ pos;
	}
	printf("%d\n", ans);
    return 0;
}
