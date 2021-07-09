/***************************************************************
	File name: P3515.cpp
	Author: ljfcnyali
	Create time: 2019年09月19日 星期四 11时11分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 500010;

int n, a[maxn], p[maxn];

inline void Solve1(int l, int r, int L, int R)
{
    if ( l > r ) return ;
    int Mid = l + r >> 1, pos = Mid;
    long double k = 0;
    REP(i, L, min(R, Mid))
    {
        long double x = a[i] - a[Mid] + sqrt(double(Mid - i));
        if ( k < x ) { k = x; pos = i; }
    }
    p[Mid] = max(p[Mid], (int)ceil(k));
    Solve1(l, Mid - 1, L, pos);
    Solve1(Mid + 1, r, pos, R);
}

inline void Solve2(int l, int r, int L, int R)
{
    if ( l > r ) return ;
    int Mid = l + r >> 1, pos = Mid;
    long double k = 0;
    REP(i, max(L, Mid), R)
    {
        long double x = a[i] - a[Mid] + sqrt(double(i - Mid));
        if ( k < x ) { k = x; pos = i; }
    }
    p[Mid] = max(p[Mid], (int)ceil(k));
    Solve2(l, Mid - 1, L, pos);
    Solve2(Mid + 1, r, pos, R);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d", &a[i]);
    Solve1(1, n, 1, n);
    Solve2(1, n, 1, n);
    REP(i, 1, n) printf("%d\n", p[i]);
    return 0;
}
