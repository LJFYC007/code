/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年06月13日 星期六 09时44分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int INF = 1e18;

int n, ans = -INF, d[maxn], c[maxn], Begin[maxn], Next[maxn], To[maxn], e, p[maxn], a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

namespace Subtask1
{
    inline int main()
    {
        REP(i, 1, n)
        {
            int sum = 0; 
            REP(j, 1, n) a[j] = d[j];
            sum += a[i]; a[i - 1] += a[i]; a[i + 1] += a[i];
            for ( int j = i - 1; j >= 1; -- j ) 
            {
                sum += a[j];
                a[j - 1] += a[j];
            }
            REP(j, i + 1, n)
            {
                sum += a[j];
                a[j + 1] += a[j];
            }
            ans = max(ans, sum);
        }
        printf("%lld\n", ans);
        return 0;
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B1.out", "w", stdout);
#endif
    scanf("%lld", &n);
    REP(i, 1, n) scanf("%lld", &d[i]);
    bool flag = true;
    REP(i, 2, n) { scanf("%lld", &c[i]); add(i, c[i]); add(c[i], i); if ( c[i] != i - 1 ) flag = false; }
    REP(i, 1, n) p[i] = i;     
    do
    {
        int sum = 0;    
        REP(i, 1, n) a[i] = d[i];
        REP(i, 1, n)
        {
            int u = p[i]; sum += a[u]; 
            for ( int j = Begin[u]; j; j = Next[j] ) 
            {
                int v = To[j]; if ( a[v] == -1 ) continue ;
                a[v] += a[u];
            }
            a[u] = -1;
        }
        ans = max(ans, sum);
    } while ( next_permutation(p + 1, p + n + 1) );
    printf("%lld\n", ans);
    return 0;
}
