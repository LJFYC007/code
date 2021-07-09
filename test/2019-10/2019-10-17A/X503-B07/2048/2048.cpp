/***************************************************************
	File name: 2048.cpp
	Author: ljfcnyali
	Create time: 2019年10月17日 星期四 14时44分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 510;

int n, ans, a[maxn], Stack[maxn];

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; }
    return r;
}

inline void SA()
{
    int sum, tot = 0;
    sum = a[1]; Stack[++ tot] = a[1];
    REP(i, 2, n)
    {
        if ( Stack[tot] == a[i] && tot ) 
        {
            Stack[++ tot] = a[i];
            sum += a[i];
            while ( tot > 1 && Stack[tot] == Stack[tot - 1] ) 
            {
                -- tot;
                sum += Stack[tot] + Stack[tot + 1];
                Stack[tot] *= 2;
            }
            continue ;
        }
        if ( rand() % min(10ll, i) == 0 ) continue ;
        sum += a[i]; Stack[++ tot] = a[i];
    }
    ans = max(ans, sum);
}

signed main()
{
    freopen("2048.in", "r", stdin);
    freopen("2048.out", "w", stdout);
    srand(time(0));
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    REP(i, 1, 30000000 / n) SA();
    printf("%lld\n", ans);
    return 0;
}
