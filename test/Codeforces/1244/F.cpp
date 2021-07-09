/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年10月27日 星期日 18时59分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 400010;

int n, k, a[maxn], ans[maxn];
char s[maxn];

inline int Check()
{
    int i = 1;
    while ( a[i] != a[i + 1] && i < n ) ++ i;
    return i;
}

inline void Solve(int L, int R)
{
    int x = a[L - 1], y = a[R + 1];
    REP(i, L, R)
    {
        int t = min(i - L, R - i) + 1;
        if ( t > k ) { ans[i] = (k & 1) ? 3 - a[i] : a[i]; continue ; }
        if ( i - L == R - i ) 
        { 
            if ( x == y ) ans[i] = x;
            else ans[i] = a[i]; 
            continue ; 
        }
        if ( i - L < R - i ) ans[i] = x;
        else ans[i] = y;
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    scanf("%s", s + 1);
    REP(i, 1, n) if ( s[i] == 'B' ) a[i] = 1; else a[i] = 2;
    REP(i, 1, n) a[n + i] = a[i];
    int l = Check(), r = l + n - 1;
    if ( l == n && a[n] != a[n + 1] )
    {
        l = r = 0;
        if ( k & 1 ) REP(i, 1, n) ans[i] = 3 - a[i];
        else REP(i, 1, n) ans[i] = a[i];
    }
    // REP(i, l, r) printf("%d ", a[i]); puts("");
    REP(i, l, r)
    {
        if ( a[i] == a[i + 1] || a[i] == a[i - 1] ) continue ;
        int L = i, R = i;
        while ( a[R] != a[R + 1] && R < r ) ++ R;
        if ( a[R] == a[R + 1] ) -- R;
        Solve(L, R);
        i = R;
    }
    REP(i, l, r) if ( !ans[i] ) ans[i] = a[i];
    REP(i, 1, l - 1) ans[i] = ans[i + n];
    REP(i, 1, n) printf("%c", ans[i] == 1 ? 'B' : 'W');
    puts("");
    return 0;
}
