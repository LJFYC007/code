/***************************************************************
	File name: c.cpp
	Author: ljfcnyali
	Create time: 2019年08月08日 星期四 10时06分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( LL i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;

LL a[maxn], n, ans = 0x3f3f3f3f, Max, p[110];

inline LL js(LL i, LL num)
{
    LL x = a[i], sum = 0;
    for ( LL i = 60; i >= 0; -- i )
        if ( x + p[i] <= num ) 
        {
            x += p[i];
            ++ sum;
        }
    return sum;
}

inline void Check(LL x)
{
    LL sum = 0; 
    REP(i, 1, n) 
    {
        sum += js(i, x);
        if ( sum >= ans ) return ;
    }
    ans = sum;
}

int main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    p[0] = 1; REP(i, 1, 60) p[i] = p[i - 1] * 2;
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld", &a[i]); Max = max(Max, a[i]); }
    sort(a + 1, a + n + 1);
    REP(i, Max, Max + 500) Check(i);
    printf("%lld\n", ans);
    return 0;
}
