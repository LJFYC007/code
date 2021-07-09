/***************************************************************
	File name: travel.cpp
	Author: ljfcnyali
	Create time: 2020年04月15日 星期三 20时45分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 1e18;

int n, m, k, x, a[maxn], ans, sum, p[maxn], Ans;
bool vis[maxn];
priority_queue<pii, vector<pii>, greater<pii> > Q;

signed main()
{
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &x);
    REP(i, 1, n) scanf("%lld", &a[i]); 
    if ( x != 1 && m == 0 ) { puts("-1"); return 0; }
    if ( x != n && m == n - 1 ) { puts("-1"); return 0; }
    Ans = INF;
    if ( m < x ) 
    {
        ans = a[x] - a[1] + a[n] - a[1];
        if ( ans < Ans ) 
        {
            Ans = ans; int pos = x, N = 0;
            vis[pos] = true;
            REP(i, 1, m - 1) { p[++ N] = -- pos; vis[pos] = true; }
            p[++ N] = 1; vis[1] = true;
            REP(i, 1, n) if ( !vis[i] ) p[++ N] = i;
            mem(vis);
        }
        int y = x - m + 1;
        ans = 2 * (a[n] - a[1]) - a[x] + a[y - 1];
        if ( ans < Ans ) 
        {
            Ans = ans; int N = 0;
            REP(i, x + 1, n) p[++ N] = i;
            for ( int i = x - 1; i >= y; -- i ) p[++ N] = i;
            REP(i, 1, y - 1) p[++ N] = i;
        }

        ans = a[n] - a[1] + a[n] - a[x];
        m = n - 1 - m;
        int sum = INF, pos = 0, ret = 0;
        for ( int i = x - 1; i >= m + 2; -- i ) Q.push(pii(a[i] - a[i - 1], i));
        for ( int i = m + 1; i >= 1; -- i )
        {
            if ( ret + a[i] - a[1] < sum ) { sum = ret + a[i] - a[1]; pos = i; }
            Q.push(pii(a[i] - a[i - 1], i));
            ret = (ret + Q.top().first * 2);
            Q.pop();
        }
        ans += sum;
        while ( !Q.empty() ) Q.pop();
        REP(i, pos + 1, x - 1) Q.push(pii(a[i] - a[i - 1], i));
        REP(i, 1, m - pos + 1) { vis[Q.top().second] = true; Q.pop(); }
        REP(i, 2, pos) vis[i] = true;
        p[0] = x;
        int Sum = 0;
        if ( ans < Ans ) 
        {
            Ans = ans; int N = 0;
            for ( int i = n; i >= x + 1; -- i ) p[++ N] = i;
            for ( int i = x - 1, j; i >= 1; i = j - 1 ) 
            {
                j = i;
                if ( !vis[i] ) { p[++ N] = i; continue ; }
                while ( vis[j] && j >= 2 ) -- j;
                REP(k, j, i) p[++ N] = k;
            }
            REP(i, 1, n - 1) Sum += abs(a[p[i - 1]] - a[p[i]]);
        }

        printf("%lld\n", Ans);
        REP(i, 1, n - 1) printf("%lld ", p[i]); puts("");
        return 0;
    }
    ans = a[n] - a[1] + a[x] - a[1];
    m -= x - 1;
    int sum = INF, pos = 0, ret = 0;
    REP(i, x + 2, n - m) Q.push(pii(a[i] - a[i - 1], i));
    REP(i, n - m + 1, n + 1) 
    {
        if ( ret + a[n] - a[i - 1] < sum ) { sum = ret + a[n] - a[i - 1]; pos = i; }
        Q.push(pii(a[i] - a[i - 1], i));
        ret = (ret + Q.top().first * 2);
        Q.pop();
    }
    ans += sum;
    while ( !Q.empty() ) Q.pop();
    REP(i, x + 2, pos - 1) Q.push(pii(a[i] - a[i - 1], i));
    REP(i, 1, m - n + pos - 1) { vis[Q.top().second] = true; Q.pop(); }
    REP(i, pos, n) vis[i] = true;
    if ( ans < Ans ) 
    {
        Ans = ans; int N = 0;
        for ( int i = x - 1; i >= 1; -- i ) p[++ N] = i; 
        for ( int i = x + 1, j; i <= n; i = j + 1 ) 
        {
            j = i;
            if ( !vis[i + 1] ) { p[++ N] = i; continue ; }
            while ( vis[j + 1] && j <= n ) ++ j;
            for ( int k = j; k >= i; -- k ) p[++ N] = k;
        }
    }
    ans = a[n] - a[x] + a[n] - a[1];
    if ( ans < Ans ) 
    {
        printf("%lld\n", ans); 
        int pos = n - m - 1;
        REP(i, x + 1, pos) printf("%lld ", i);
        for ( int i = n; i > pos; -- i ) printf("%lld ", i);
        for ( int i = x - 1; i >= 1; -- i ) printf("%lld ", i);
        puts("");
        return 0;
    }

    printf("%lld\n", Ans);
    REP(i, 1, n - 1) printf("%lld ", p[i]); puts("");
    return 0;
}
