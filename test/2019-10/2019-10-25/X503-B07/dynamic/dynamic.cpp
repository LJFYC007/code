/***************************************************************
	File name: dynamic.cpp
	Author: ljfcnyali
	Create time: 2019年10月25日 星期五 08时33分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int unsigned long long
typedef long long LL;

const int maxn = 100010;
const int N = 100000;

int l, r, ans;

signed main()
{
    freopen("dynamic.in", "r", stdin);
    freopen("dynamic.out", "w", stdout);
    scanf("%llu%llu", &l, &r);
    int now = 2;
    REP(i, 1, 64)
    {
        if ( l < now - 1 && now - 1 < r ) ++ ans;
        now *= 2;
    }
    printf("%llu\n", ans);
    return 0;
}
