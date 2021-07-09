/***************************************************************
	File name: mid.cpp
	Author: ljfcnyali
	Create time: 2019年10月22日 星期二 08时31分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 4000010;
const int N = 4000000;

int n, x, sum;
bitset<maxn> b;

signed main()
{
    freopen("mid.in", "r", stdin);
    freopen("mid.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) 
    {
        scanf("%lld", &x);
        b |= (b << x); b.set(x);
    }
    REP(i, 1, N) if ( b[i] ) ++ sum;
    sum = (sum + 1) / 2;
    REP(i, 1, N) 
    {
        if ( b[i] ) -- sum;
        if ( !sum ) { printf("%lld\n", i); return 0; }
    }
    return 0;
}
