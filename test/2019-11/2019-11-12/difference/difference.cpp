/***************************************************************
	File name: difference.cpp
	Author: ljfcnyali
	Create time: 2019年11月12日 星期二 09时38分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, a[maxn], tot;
pii Stack[maxn];

signed main()
{
    freopen("difference.in", "r", stdin);
    freopen("difference.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) 
    {
        scanf("%lld", &a[i]); 
        Stack[++ tot] = pii(a[i], 1);
        while ( tot > 1 && Stack[tot].first * Stack[tot - 1].second < Stack[tot - 1].first * Stack[tot].second ) 
        {
            -- tot; 
            Stack[tot].first += Stack[tot + 1].first;
            Stack[tot].second += Stack[tot + 1].second;
        }
    }
    REP(i, 1, tot) REP(j, 1, Stack[i].second) 
    {
        int x = __gcd(Stack[i].first, Stack[i].second);
        printf("%lld/%lld ", Stack[i].first / x, Stack[i].second / x);
    }
    puts("");
    return 0;
}
