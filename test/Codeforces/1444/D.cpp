/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2020年11月09日 星期一 09时01分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, m, a[maxn], b[maxn], p[4][maxn], len[4];
pii ans[maxn];
bitset<1000010> f[1010];

inline pii operator + (pii a, pii b) { return pii(a.first + b.first, a.second + b.second); }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        a[0] = b[0] = 0; mem(len);
        scanf("%d", &n); REP(i, 1, n) { scanf("%d", &a[i]); a[0] += a[i]; }
        scanf("%d", &m); REP(i, 1, m) { scanf("%d", &b[i]); b[0] += b[i]; }
        if ( n != m || a[0] % 2 != 0 || b[0] % 2 != 0 ) { puts("No"); continue ; }

        mem(f); f[0][0] = 1;
        REP(i, 1, n) f[i] = f[i - 1] | (f[i - 1] << a[i]);
        int sum = a[0] / 2;
        if ( !f[n][sum] ) { puts("No"); continue ; }
        for ( int i = n; i >= 1; -- i ) 
            if ( sum >= a[i] && f[i - 1][sum - a[i]] ) { sum -= a[i]; p[0][++ len[0]] = a[i]; }
            else p[1][++ len[1]] = a[i];

        mem(f); f[0][0] = 1;
        REP(i, 1, n) f[i] = f[i - 1] | (f[i - 1] << b[i]);
        sum = b[0] / 2;
        if ( !f[n][sum] ) { puts("No"); continue ; }
        for ( int i = n; i >= 1; -- i ) 
            if ( sum >= b[i] && f[i - 1][sum - b[i]] ) { sum -= b[i]; p[2][++ len[2]] = b[i]; }
            else p[3][++ len[3]] = b[i];
        REP(i, 0, 3) sort(p[i] + 1, p[i] + len[i] + 1);
        // REP(i, 0, 3) { REP(j, 1, len[i]) cout << p[i][j] << " "; cout << endl; } 

        bool rev = false;
        if  ( len[0] > len[2] ) 
        { 
            rev = true; 
            swap(len[0], len[2]); swap(len[1], len[3]);
            swap(p[0], p[2]); swap(p[1], p[3]);
        }

        REP(i, 1, len[1]) p[1][i] = -p[1][i];
        REP(i, 1, len[3]) p[3][i] = -p[3][i];

        pii now = pii(0, 0); m = 0;
        int k = 1, t = 1;
        for ( int i = len[0]; i >= 1; -- i )
        {
            now = now + (rev ? pii(0, p[0][i]) : pii(p[0][i], 0)); ans[++ m] = now;
            now = now + (rev ? pii(p[2][k], 0) : pii(0, p[2][k])); ans[++ m] = now; ++ k;
        }
        while ( k <= len[2] ) 
        {
            now = now + (rev ? pii(0, p[1][t]) : pii(p[1][t], 0)); ans[++ m] = now; ++ t;
            now = now + (rev ? pii(p[2][k], 0) : pii(0, p[2][k])); ans[++ m] = now; ++ k;
        }
        t = len[1];
        REP(i, 1, len[3])
        {
            now = now + (rev ? pii(0, p[1][t]) : pii(p[1][t], 0)); ans[++ m] = now; -- t;
            now = now + (rev ? pii(p[3][i], 0) : pii(0, p[3][i])); ans[++ m] = now; 
        }
        puts("Yes");
        REP(i, 1, m) printf("%d %d\n", ans[i].first, ans[i].second);
    }
    return 0;
}
