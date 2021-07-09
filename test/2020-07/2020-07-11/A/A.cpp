/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2424年07月11日 星期六 08时21分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define int long long
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;
const int w = (1 << 24);

int n, N, block, a[maxn], ans, b[maxn], c[maxn];
char s[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r *= a; a *= a; b >>= 1; } return r; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1); block = 24;
    reverse(s + 1, s + n + 1);
    for ( int l = 1, r = min(n, block); l <= n; l += block, r = min(n, r + block) )
    {
        ++ N;
        REP(i, l, r) a[N] += (s[i] - '0') << (i - l);
    }
    for ( int i = 1; i <= N; ++ i ) 
    {
        int num = 24, sum = 0;
        if ( i == N ) REP(j, 1, 24) if ( (a[i] >> j - 1) & 1 ) num = j;
        while ( a[i] ) 
        {
            if ( a[i] == 1 && i == N ) break ; 
            // cerr << a[i] << " " << num << endl;
            if ( a[i] < 0 ) return 0;
            ++ ans;
            if ( a[i] & 1 ) 
            {
                a[i] = a[i] * 3 + 1; ++ sum;
                if ( a[i] >= (1ll << num) ) 
                {
                    if ( i == N ) ++ N;
                    b[i + 1] = b[i + 1] * power(3, sum - c[i + 1]) + a[i] / (1ll << num);
                    c[i + 1] = sum; a[i] %= (1ll << num);
                }
            }
            else { a[i] >>= 1; -- num; }
        }
        REP(j, i + 1, N) a[j] = a[j] * power(3, sum);
        a[i + 1] += b[i + 1] * power(3, sum - c[i + 1]);
        b[i + 1] = c[i + 1] = 0;
        for ( int j = i + 1; j <= N; ++ j ) if ( a[j] >= w ) 
        {
            if ( j == N ) ++ N;
            a[j + 1] += a[j] / w; a[j] %= w;
        }
        ans += num;
    }
    printf("%lld\n", ans - 1);
    return 0;
}
