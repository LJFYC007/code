/***************************************************************
	File name: a.cpp
	Author: ljfcnyali
	Create time: 2019年11月13日 星期三 08时46分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int n, q, a[maxn], d;

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%d", &n);
    a[0] = 1;
    REP(i, 1, n) 
    { 
        int x; scanf("%d", &x); d = __gcd(d, x);
        REP(j, 0, maxn - x - 1) a[j + x] |= a[j]; 
    }
    // REP(i, 0, 1000) if ( a[i] ) printf("%d ", i); puts("");
    // REP(i, 0, 1000) if ( !a[i] && i % d == 0 ) printf("%d ", i); puts("");
    scanf("%d", &q);
    REP(i, 1, q)
    {
        int x; scanf("%d", &x);
        if ( a[x] == 1 ) puts("Acesrc!");
        else puts("Acesrc?");
    }
    return 0;
}
