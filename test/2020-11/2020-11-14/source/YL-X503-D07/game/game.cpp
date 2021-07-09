/***************************************************************
	File name: game.cpp
	Author: ljfcnyali
	Create time: 2020年11月14日 星期六 09时52分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define y1 hhakioi
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, x1, y1, x2, y2;

int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    cin >> n >> m >> x1 >> y1 >> x2 >> y2;    
    if ( abs(x1 - x2) + abs(y1 - y2) <= 1 ) { puts("-1"); return 0; }
    int ans = 3;
    if ( x2 <= 2 && y2 <= 2 && n - x2 <= 1 && m - y2 <= 1 ) { puts("1"); return 0; }
    if ( (n == 2 || m == 2) && (abs(x1 - x2) > 1 || abs(y1 - y2) > 1) ) { puts("2"); return 0; }
    if ( n == 1 || m == 1 ) { puts("2"); return 0; }
    if ( n - x1 <= 1 && m - y1 <= 1 ) { puts("2") ;return 0; }
    printf("%d\n", ans);
    return 0;
}
