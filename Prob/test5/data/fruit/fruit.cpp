/***************************************************************
	File name: fruit.cpp
	Author: ljfcnyali
	Create time: 2019年10月25日 星期五 11时19分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 10010;

int n, m, a[maxn], ans = -1;

inline bool Check(int x)
{
    int sum = 0, num = 0;
    for ( int i = 1; i <= n; ++ i ) 
    {
        sum += a[i];
        if ( sum >= x ) { sum = 0; ++ num; }
    }
    return num >= m;
}

signed main()
{
    // freopen("fruit.in", "r", stdin);
    // freopen("fruit.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) scanf("%lld", &a[i]);
    int L = 1, R = 100000000000;
    while ( L <= R ) 
    {
        int Mid = L + R >> 1;
        if ( Check(Mid) ) { ans = Mid; L = Mid + 1; }
        else R = Mid - 1;
    }
    printf("%lld\n", ans);
    return 0;
}
