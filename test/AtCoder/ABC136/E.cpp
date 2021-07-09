/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年08月04日 星期日 19时58分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 510;

int n, k, sum, a[maxn], ans, b[maxn], c[maxn];

inline bool pd(int x)
{
    if ( x < ans ) return false;
    REP(i, 1, n) b[i] = a[i] % x;
    sort(b + 1, b + n + 1);
    REP(i, 1, n) c[i] = x - b[i];
    // REP(i, 1, n) printf("%d ", b[i]); puts("");
    REP(i, 2, n) { b[i] += b[i - 1]; c[i] += c[i - 1]; }
    REP(i, 1, n) if ( b[i] == (c[n] - c[i]) && b[i] <= k ) return true; 
    return false;
}

int main()
{
    scanf("%d%d", &n, &k);
    REP(i, 1, n) scanf("%d", &a[i]), sum += a[i];
    for ( int i = 1; i * i <= sum; ++ i ) 
    {
        if ( sum % i != 0 ) continue ;
        if ( pd(sum / i) ) ans = max(ans, sum / i);
        if ( pd(i) ) ans = max(ans, i);
    }
    printf("%d\n", ans);
    return 0;
}
