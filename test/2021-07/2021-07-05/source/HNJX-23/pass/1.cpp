#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define pii pair<int, int>

const int maxn = 5010;

int n, m, q, p[maxn]; bool vis[maxn];
char s[maxn], t[maxn];

inline void Solve()
{
    int len = m + m + 1;
    REP(i, 1, len) p[i] = 0; 
    for ( int i = m; i >= 1; -- i ) s[i + i] = s[i];
    REP(i, 1, len) if ( i & 1 ) s[i] = '$';
    int Max = 0, pos = 0;
    REP(i, 1, len)
    {
        if ( Max >= i ) p[i] = min(Max - i, p[pos + pos - i]);
        while ( i - p[i] >= 1 && i + p[i] <= len && s[i - p[i]] == s[i + p[i]] ) ++ p[i];
        if ( i + p[i] > Max ) { Max = i + p[i]; pos = i; }
    }
}

int main()
{
    freopen("pass.in", "r", stdin);
    freopen("pass.out", "w", stdout);
    scanf("%d", &n); scanf("%s", t + 1); 
    scanf("%d", &q);
    while ( q -- ) 
    {
        int l, r; scanf("%d%d", &l, &r); m = r - l + 1;
        REP(i, l, r) s[i - l + 1] = t[i];
        memset(vis, 0, sizeof(vis));

        bool ccc = false;
        REP(i, 1, m - 2) if ( s[i] == s[i + 2] ) ccc = true;
        
        Solve();
        REP(i, 1, m + m + 1) if ( i & 1 ) 
        {
            REP(j, i - p[i] + 1, i + p[i] - 1) if ( j % 2 == 0 ) 
                vis[j / 2] = true;
        }

        bool flag = true;
        REP(i, 1, m) if ( !vis[i] ) flag = false;
        flag |= ccc;
        if ( flag ) printf("1"); else printf("0");
    }
    return 0;
}