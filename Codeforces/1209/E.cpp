/***************************************************************
	File name: E1.cpp
	Author: ljfcnyali
	Create time: 2020年10月14日 星期三 10时52分25秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, m, a[13][2010], f[14][1 << 14], g[14][1 << 14], id[2010], Max[2010];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    REP(o, 1, T)
    {
        scanf("%d%d", &n, &m);
        REP(i, 1, m) { Max[i] = 0; id[i] = i; }
        REP(i, 1, n) REP(j, 1, m) { scanf("%d", &a[i][j]); Max[j] = max(Max[j], a[i][j]); }
        sort(id + 1, id + m + 1, [](int x, int y) { return Max[x] > Max[y]; });
        m = min(m, n);
        mem(f);
        REP(s, 0, (1 << n) - 1) REP(i, 1, m)
        {
            g[i][s] = 0;
            REP(k, 1, n)
            {
                int val = 0;
                REP(j, 1, n) if ( (s >> j - 1) & 1 ) val += a[(j + k) % n + 1][id[i]];
                g[i][s] = max(g[i][s], val);
            }
        }
        REP(i, 1, m) REP(s, 0, (1 << n) - 1)
        {
            int S = (1 << n) - 1 - s;
            for ( int t = S; ; t = S & (t - 1) )
            {
                f[i][t | s] = max(f[i][t | s], f[i - 1][s] + g[i][t]);
                if ( !t ) break ; 
            }
        }
        cout << f[m][(1 << n) - 1] << endl;
    }
    return 0;
}
