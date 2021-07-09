/***************************************************************
	File name: P2421.cpp
	Author: ljfcnyali
	Create time: 2019年06月07日 星期五 14时47分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int C[maxn], p[maxn], l[maxn], n;

inline void exgcd(int a, int b, int &d, int &x, int &y)
{
    if ( !b ) { d = a; x = 1; y = 0; }
    else { exgcd(b, a % b, d, x, y); int t = x; x = y; y = t - (a / b) * y; }
}

inline bool check(int m)
{
    int d, x, y;
    REP(i, 1, n - 1)
        REP(j, i + 1, n)
        {
            int a = p[i] - p[j], b = m, c = C[j] - C[i];
            exgcd(a, b, d, x, y);
            if ( c % d != 0 ) continue ; 
            a /= d; b /= d; c /= d;
            if ( b < 0 ) b = -b;
            x = ((x * c) % b + b) % b;
            if ( x <= l[i] && x <= l[j] ) return false;
        }
    return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    int Max = 0;
    REP(i, 1, n) { scanf("%d%d%d", &C[i], &p[i], &l[i]); Max = max(Max, C[i]); }
    for ( int i = Max; ; ++ i ) if ( check(i) ) { printf("%d\n", i); return 0; }
    return 0;
}
