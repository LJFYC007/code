/***************************************************************
	File name: robot.cpp
	Author: ljfcnyali
	Create time: 2019年07月16日 星期二 10时59分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 10;

int a[maxn], b[maxn], n, h[maxn], ans;

inline bool check()
{
    REP(s, 1, n)
    {
        int i = s - 1, sum1 = 0, sum2 = 0;
        while ( i >= 1 && h[i] <= h[s] ) { -- i; ++ sum1; }
        i = s + 1;
        while ( i <= n && h[i] < h[s] ) { ++ i; ++ sum2; }
        if ( abs(sum1 - sum2) > 2 ) return false;
    }
    return true;
}

inline void DFS(int x)
{
    if ( x == n + 1 ) { if ( check() ) ++ ans; return ; }
    REP(i, a[x], b[x]) { h[x] = i; DFS(x + 1); }
}

int main()
{
    freopen("robot.in", "r", stdin);
    freopen("robot.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d%d", &a[i], &b[i]);
    DFS(1);
    printf("%d\n", ans);
    return 0;
}
