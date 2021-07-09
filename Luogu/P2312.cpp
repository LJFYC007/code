/***************************************************************
	File name: P2312.cpp
	Author: ljfcnyali
	Create time: 2019年08月18日 星期日 11时24分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;
#define int long long

const int Mod1 = 99844353;
const int Mod2 = 19260817;
const int maxn = 1000010;

int a[maxn][3], n, m, ans[maxn], sum;

inline int power(int a, int b, int Mod)
{
    int r = 1;
    while ( b ) 
    {
        if ( b & 1 ) r = (r * a) % Mod;
        a = (a * a) % Mod; b >>= 1;
    }
    return r;
}

inline bool Check(int x)
{
    int sum1 = 0, sum2 = 0, s1 = 1, s2 = 1;
    REP(i, 0, n)
    {
        sum1 = (sum1 + s1 * a[i][1]) % Mod1;
        sum2 = (sum2 + s2 * a[i][2]) % Mod2;
        s1 = (s1 * x) % Mod1;
        s2 = (s2 * x) % Mod2;
    }
    if ( sum1 == 0 && sum2 == 0 ) return true;
    return false;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &m);
    REP(i, 0, n) 
    {
        char c = getchar();
        bool flag = false;
        while ( !((c >= '0' && c <= '9') || c == '-') ) c = getchar();
        if ( c == '-' ) { flag = true; c = getchar(); }
        while ( c >= '0' && c <= '9' ) 
        {
            a[i][1] = (a[i][1] * 10 + c - '0') % Mod1;
            a[i][2] = (a[i][2] * 10 + c - '0') % Mod2;
            c = getchar();
        }
        if ( flag == true ) a[i][1] = -a[i][1], a[i][2] = -a[i][2];
    }
    REP(i, 1, m) if ( Check(i) ) ans[++ sum] = i;
    printf("%lld\n", sum);
    REP(i, 1, sum) printf("%lld\n", ans[i]);
    return 0;
}
