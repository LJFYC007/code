/***************************************************************
	File name: K.cpp
	Author: ljfcnyali
	Create time: 2020年10月16日 星期五 21时48分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 30;

int n, a[maxn], f[30][20];
priority_queue<int> Q; 

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    // int T = 10;
    while ( ~scanf("%d", &n) )
    {
        // if ( T == 0 ) return 0; -- T;
        while ( !Q.empty() ) Q.pop();
        REP(i, 1, n) { scanf("%d", &a[i]); if ( a[i] ) Q.push(a[i]); }

        memset(f, 0x3f, sizeof(f)); f[0][0] = 0;
        REP(i, 0, n - 1) REP(j, 0, 19)
        {
            if ( f[i][j] == 0x3f3f3f3f ) continue ;
            REP(k, 0, j) REP(o, 0, 19)
            {
                if ( k + o > 19 ) continue ;
                int num = j - k + o;
                if ( num <= a[i + 1] && (a[i + 1] - num) % 3 == 0 ) 
                    f[i + 1][k + o] = min(f[i + 1][k + o], f[i][j] + (a[i + 1] - num) / 3 + o);
            }
        }
        // REP(i, 1, n) REP(j, 0, 10) printf("%d %d %d\n", i, j, f[i][j]);
        printf("%d ", f[n][0]);

        int ans = 0;
        while ( Q.size() > 1 ) 
        {
            int u = Q.top(); Q.pop();
            int v = Q.top(); Q.pop();
            -- u; -- v; if ( u > 0 ) Q.push(u); if ( v > 0 ) Q.push(v);
            ++ ans;
        }
        if ( Q.size() ) 
        {
            int x = Q.top(); Q.pop();
            ans += x / 3; x %= 3;
        }
        printf("%d\n", ans);
    }
    return 0;
}
