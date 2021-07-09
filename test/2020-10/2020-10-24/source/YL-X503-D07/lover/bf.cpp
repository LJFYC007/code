/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年10月24日 星期六 09时25分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, k, ans;

inline int get(int x)
{
    int ret = 1;
    while ( x ) { ret *= x % 10; x /= 10; }
    return ret;
}

int main()
{
    freopen("lover.in", "r", stdin);
    freopen("lover1.out", "w", stdout);
    scanf("%d%d", &n, &k);
    REP(i, 1, n) REP(j, 1, n)
    {
        int x = get(i), y = get(j);
        if ( !x || !y ) continue ;
        if ( __gcd(x, y) <= k ) ++ ans;
    }
    printf("%d\n", ans);
    return 0;
}
