/***************************************************************
	File name: clear.cpp
	Author: ljfcnyali
	Create time: 2020年07月14日 星期二 09时27分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, t, x[maxn], y[maxn];
pii a[maxn];
priority_queue<int> Q;

inline bool Check(int val)
{
    while ( !Q.empty() ) Q.pop();
    int now = 1;
    REP(i, 1, n)
    {
        while ( a[now].first < x[i] && now <= t ) { Q.push(a[now].second); ++ now; }
        int x = val;
        while ( !Q.empty() && x ) 
        { 
            -- x; 
            Q.pop(); 
        }
    }
    REP(i, now, t) Q.push(a[i].second);
    for ( int i = m; i >= 1; -- i ) 
    {
        int x = val;
        while ( !Q.empty() && x && Q.top() < y[i] ) { -- x; Q.pop(); }
    }
    return Q.empty();
}

int main()
{
    freopen("clear.in", "r", stdin);
    freopen("clear.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &t);
    REP(i, 1, n) scanf("%d", &x[i]);
    REP(i, 1, m) scanf("%d", &y[i]);
    sort(x + 1, x + n + 1); sort(y + 1, y + m + 1);
    REP(i, 1, t) scanf("%d%d", &a[i].first, &a[i].second);
    sort(a + 1, a + t + 1);
    // REP(i, 1, t) printf("%d %d\n", a[i].first, a[i].second); puts("");

    int L = 1, R = t, ans = -1;
    while ( L <= R ) 
    {
        int Mid = L + R >> 1;
        if ( Check(Mid) ) { ans = Mid; R = Mid - 1; }
        else L = Mid + 1;
    }
    printf("%d\n", ans);
    return 0;
}
