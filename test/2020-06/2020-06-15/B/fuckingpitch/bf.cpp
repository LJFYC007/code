/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年06月15日 星期一 09时31分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, q;
char t[51][51], s[maxn], f[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B1.out", "w", stdout);
#endif
    scanf("%d%d", &n, &q);
    REP(i, 1, n) scanf("%s", t[i] + 1);
    scanf("%s", s + 1); m = str(s + 1);
    while ( q -- ) 
    {
        int op, l, r; scanf("%d%d%d", &op, &l, &r);
        if ( op == 1 ) 
        {
            scanf("%s", f + 1); int len = str(f + 1);
            REP(i, l, r) s[i] = f[(i - l) % len + 1];
        }
        else
        {
            int ans = 0;
            REP(i, l, r) REP(j, 1, n)
            {
                int len = str(t[j] + 1);
                if ( i + len - 1 > r ) continue ;
                REP(o, 1, len) if ( s[i + o - 1] != t[j][o] ) goto Next ;
                // if ( l == 66 && r == 141 ) cout << i << " " << j << endl;
                ++ ans;
Next : ;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
