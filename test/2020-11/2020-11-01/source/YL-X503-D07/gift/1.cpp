/***************************************************************
  File name: gift.cpp
Author: ljfcnyali
Create time: 2020年11月01日 星期日 10时27分23秒
 ***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int INF = 1e18;
const int Mod = 1e9 + 7;

int n, a[maxn], val[maxn], ans, b[maxn], pre[maxn];
bool vis[maxn];
vector<int> p[maxn];

signed main()
{
    freopen("gift.in", "r", stdin);
    freopen("gift.out", "w", stdout);
    scanf("%lld", &n); 
    REP(i, 1, n) 
    { 
        scanf("%lld", &a[i]); 
        if ( p[a[i]].size() ) pre[i] = p[a[i]].back();
        p[a[i]].push_back(i); 
    }
    REP(o, 1, n)
    {
        int Min = INF, pos;
        REP(i, 1, n) if ( !vis[i] && a[i] < Min ) { Min = a[i]; pos = i; }
        val[pos] = 1; vis[pos] = true;
        REP(i, 1, n) b[i] = b[i - 1] + val[i];
        int lst = 0;
        REP(i, 1, pos - 1) if ( a[i] == a[pos] ) lst = i;
        /*
           int ret1 = 0, ret2 = 0;
           REP(i, lst + 1, pos) ret1 += b[pos - 1] - b[i - 1];
           REP(i, pos, n) ret2 += b[i] - b[pos - 1];
           ret1 *= (n - pos + 1); ret2 *= (pos - lst);
           ans = (ans + a[pos] * (ret1 + ret2)) % Mod;
        */
        // REP(i, 1, pos) REP(j, pos, n) ans = (ans + a[pos] * (b[j] - b[i - 1])) % Mod;
        REP(i, lst + 1, pos) REP(j, pos, n) ans = (ans + a[pos] * (b[j] - b[i - 1])) % Mod;
        /*
        if ( !lst ) continue ;
        REP(i, 1, n)
        {
            if ( a[i] <= a[pos] ) continue ;
            REP(l, 1, min(lst, i)) REP(r, max(pos, i), n)
                ans = (ans - a[i]); // * (b[r] - b[l - 1])) % Mod;
        }
        */
        if ( pos == p[a[pos]].back() ) 
        {
            REP(i, 1, n) REP(l, pre[a[i]] + 1, i) REP(r, i, n)
            {
                if ( a[i] <= a[pos] ) continue ;
                int num = 0, sum = 0;
                REP(k, l, r) 
                {
                    if ( a[k] == a[pos] ) ++ num;
                    if ( a[k] == a[i] ) ++ sum;
                }
                // if ( sum > 1 ) continue ;
                if ( num > 1 ) ans -= a[i] * (num - 1);
            }
        }
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
