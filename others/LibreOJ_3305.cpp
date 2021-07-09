/***************************************************************
	File name: LibreOJ_3305.cpp
	Author: ljfcnyali
	Create time: 2020年07月19日 星期日 15时55分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;

int n, a[maxn], ans;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &a[i]);
    int sum = a[1];
    REP(i, 2, n)
    {
        sum += a[i];
        if ( sum > 0 ) ans += sum;
    }
    printf("%lld\n", ans);
    return 0;
}
