/***************************************************************
	File name: P3203.cpp
	Author: ljfcnyali
	Create time: 2019年06月17日 星期一 09时34分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 200010;

int block, p[maxn], a[maxn], to[maxn], s[maxn], n, m;

inline void Solve(int l, int r)
{
    for ( int i = r; i >= l; -- i )
    {
        int L = (p[i] - 1) * block + 1, R = p[i] * block;
        if ( i + a[i] > R ) { to[i] = i + a[i]; s[i] = 1; }
        else { s[i] = s[i + a[i]] + 1; to[i] = to[i + a[i]]; }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); block = sqrt(n) * 2;
    REP(i, 1, n) { scanf("%d", &a[i]); p[i] = (i - 1) / block + 1; }
    Solve(1, n);
    scanf("%d", &m);
    REP(i, 1, m)
    {
        int opt; scanf("%d", &opt);
        if ( opt == 1 ) 
        {
            int x, ans = 0; scanf("%d", &x); ++ x;
            while ( x <= n ) { ans += s[x]; if ( to[x] == x ) break ; x = to[x]; }
            printf("%d\n", ans);
        }
        else
        {
            int x, val; scanf("%d%d", &x, &val); ++ x;
            a[x] = val; Solve((p[x] - 1) * block + 1, p[x] * block);
        }
    }
    return 0;
}
