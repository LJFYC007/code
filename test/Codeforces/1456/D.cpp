/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2020年11月29日 星期日 16时00分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 5010;
const int INF = 1e18;

int n, m, f[maxn][maxn], pos[maxn], MinTime[maxn];
pii a[maxn];
map<int, int> Map;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n); Map[0] = true;
    REP(i, 1, n) { scanf("%lld%lld", &a[i].x, &a[i].y); Map[a[i].y] = true; }
    for ( auto it : Map ) { Map[it.first] = ++ m; pos[m] = it.first; }
    
    a[0] = pii(0, 0); 
    if ( abs(a[1].y) > a[1].x ) { puts("NO"); return 0; }
    REP(i, 1, n) MinTime[i] = INF;
    f[0][Map[0]] = true;
    REP(i, 1, n) 
    {
        bool flag = false; REP(j, 1, m) flag |= f[i - 1][j]; 
        if ( !flag && MinTime[i - 1] > a[i - 1].x && (i == 1 || !f[i - 2][Map[a[i - 1].y]]) ) { puts("NO"); return 0; }

        if ( i >= 2 && f[i - 2][Map[a[i - 1].y]] )
        {
            MinTime[i] = min(MinTime[i], max(a[i - 1].x, a[i - 2].x + abs(a[i].y - a[i - 2].y)));
            REP(j, 1, m) if ( abs(pos[j] - a[i].y) + max(a[i - 1].x, abs(pos[j] - a[i - 2].y) + a[i - 2].x) <= a[i].x )
                f[i][j] = true;
        }

        MinTime[i] = min(MinTime[i], max(a[i - 1].x, MinTime[i - 1] + abs(a[i].y - a[i - 1].y)));
        if ( MinTime[i] <= a[i].x ) f[i][Map[a[i].y]] = true;

        if ( MinTime[i - 1] <= a[i - 1].x ) 
            REP(j, 1, m) if ( abs(pos[j] - a[i].y) + max(a[i - 1].x, abs(pos[j] - a[i - 1].y) + MinTime[i - 1]) <= a[i].x )
                f[i][j] = true;
        REP(j, 1, m) if ( abs(a[i].y - pos[j]) + abs(pos[j] - a[i - 1].y) <= a[i].x - a[i - 1].x ) 
            f[i][j] = true;
        REP(j, 1, m) if ( abs(a[i].y - a[i - 1].y) <= a[i].x - a[i - 1].x )
            f[i][j] |= f[i - 1][j]; 

        // cout << MinTime[i] << endl; REP(j, 1, m) cout << f[i][j] << " "; cout << endl;
    }
    bool flag = false;
    REP(j, 1, m) flag |= f[n][j]; 
    if ( flag || f[n - 1][Map[a[n].y]] ) puts("YES");
    else puts("NO");
    return 0;
}
