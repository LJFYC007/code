/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年05月24日 星期日 10时25分40秒
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

int f[maxn];

signed main()
{
    freopen("A.in", "w", stdout);
    srand(time(0));
    int n = 100000;
    printf("%lld\n", n);
    REP(i, 1, n)
    {
        int l = (LL)rand() * rand() % 1000000000000000000;
        int r = (LL)rand() * rand() % 1000000000000000000;
        printf("%lld %lld\n", min(l, r), max(l, r));
    }
    return 0;
}
