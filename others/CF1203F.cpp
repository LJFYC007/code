/***************************************************************
	File name: CF1203F.cpp
	Author: ljfcnyali
	Create time: 2019年10月29日 星期二 20时28分13秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;

int f[100010], n, ret, ans;
pii a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &ret);
    REP(i, 1, n) scanf("%d%d", &a[i].first, &a[i].second); 
    sort(a + 1, a + n + 1);
    REP(i, 1, n) 
    {
        if ( a[i].second < 0 ) continue ;
        if ( a[i].first <= ret ) { ret += a[i].second; ++ ans; }
    }
    f[ret] = ans;    
    sort(a + 1, a + n + 1, [](pii a, pii b) { return a.first + a.second > b.first + b.second || (a.first + a.second == b.first + b.second && a.first > b.first); });
    REP(i, 1, n)
    {
        if ( a[i].second >= 0 ) continue ;
        REP(j, a[i].first, ret)
            if ( j + a[i].second >= 0 )
                f[j + a[i].second] = max(f[j + a[i].second], f[j] + 1);
    }
    REP(i, 0, ret) ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}
