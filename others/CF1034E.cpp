/***************************************************************
	File name: CF1034E.cpp
	Author: ljfcnyali
	Create time: 2020年10月16日 星期五 11时33分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int unsigned long long
typedef long long LL;

const int maxn = 1 << 21;

int n, m, a[maxn], b[maxn], cnt[maxn];

inline void FWT(int *f, int op)
{
    for ( int Mid = 1; Mid < m; Mid <<= 1 ) 
        for ( int i = 0; i < m; i += (Mid << 1) )
            for ( int j = 0; j < Mid; ++ j )
                f[i + j + Mid] += op * f[i + j];
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%llu", &n);
    REP(i, 0, (1 << n) - 1) 
    {
        cnt[i] = 1;
        for ( int j = 0; j < n; ++ j ) if ( (i >> j) & 1 ) cnt[i] *= 4;
    }
    getchar(); REP(i, 0, (1 << n) - 1) { char c = getchar(); a[i] = (c - '0') * cnt[i]; }
    getchar(); REP(i, 0, (1 << n) - 1) { char c = getchar(); b[i] = (c - '0') * cnt[i]; }
    m = 1 << n;
    FWT(a, 1); FWT(b, 1);
    REP(i, 0, (1 << n) - 1) a[i] = a[i] * b[i];
    FWT(a, -1);
    REP(i, 0, (1 << n) - 1) printf("%llu", (a[i] / cnt[i]) % 4);
    puts("");
    return 0;
}
