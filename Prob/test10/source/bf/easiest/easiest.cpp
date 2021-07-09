/***************************************************************
	File name: easiest.cpp
	Author: ljfcnyali
	Create time: 2020年10月06日 星期二 19时08分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e7 + 10;

int n, q, a[maxn], f[maxn];
LL ret;
const int N = 1e9 ;
unsigned x = 123456789 , y = 362436069, z;
unsigned gen ( )
{
    unsigned t ;
    x ^= x << 16; x ^= x >> 5 ; x ^= x << 1 ;
    t = x ; x = y ; y = z ; z = t ^ x ^ y ;
    return z % N + 1 ;
}

int main()
{
    freopen("easiest.in", "r", stdin);
    freopen("easiest.out", "w", stdout);
    scanf("%d%d%u", &n, &q, &z);
    REP(i, 1, n) { a[i] = gen(); f[i] = i; }
    while ( q -- ) 
    {
        int l = gen() % n + 1, r = gen() % n + 1;
        if ( l > r ) swap(l, r);
        LL ans = 0; 
        for ( int i = l; i <= r; i = f[i] + 1 )
        {
            ans += a[i];
            a[i] = 0;
        }
        f[l] = r;
        ret ^= ans;
    }
    cout << ret << endl;
    return 0;
}
