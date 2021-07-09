/***************************************************************
	File name: CF1037G.cpp
	Author: ljfcnyali
	Create time: 2020年10月21日 星期三 21时04分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define x first
#define y second
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, lpos[26][maxn], rpos[26][maxn], c[26][maxn], MaxL[maxn], g[maxn][26], h[maxn][26];
char s[maxn];
pii Q[maxn];
vector<pii> q;
map<int, int> f[maxn];
bool vis[26];

inline int lowbit(int x) { return x & -x; }

inline void add(int op, int pos, int val) { for ( int i = pos; i <= n; i += lowbit(i) ) c[op][i] ^= val; }

inline int get(int op, int l, int r)
{
    int sum = 0;
    for ( int i = r; i > 0; i -= lowbit(i) ) sum ^= c[op][i];
    for ( int i = l - 1; i > 0; i -= lowbit(i) ) sum ^= c[op][i];
    return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", s + 1); n = str(s + 1);
    scanf("%d", &m);
    REP(i, 1, n) { f[i][i] = 0; q.push_back(pii(i, i)); MaxL[i] = i; }
    REP(i, 1, m) 
    { 
        scanf("%d%d", &Q[i].x, &Q[i].y); 
        MaxL[Q[i].y] = min(MaxL[Q[i].y], Q[i].x);
        if ( !f[Q[i].x].count(Q[i].y) )
        {
            q.push_back(Q[i]); 
            f[Q[i].x][Q[i].y] = 0; 
        }
    }
    REP(i, 0, 25) rpos[i][n + 1] = n + 1;
    for ( int i = n; i >= 1; -- i )       
    {
        f[i][i - 1] = 0;
        REP(j, 0, 25) rpos[j][i] = rpos[j][i + 1];
        rpos[s[i] - 'a'][i] = i;
        REP(j, 0, 25) if ( rpos[j][i] <= n && !f[i].count(rpos[j][i] - 1) ) 
        {
            f[i][rpos[j][i] - 1] = 0;
            q.push_back(pii(i, rpos[j][i] - 1));
        }
    }

    REP(i, 1, n)
    {
        REP(j, 0, 25) lpos[j][i] = lpos[j][i - 1];
        lpos[s[i] - 'a'][i] = i;
        REP(j, 0, 25) if ( lpos[j][i] >= MaxL[i] && lpos[j][i] && !f[lpos[j][i] + 1].count(i) ) 
        {
            f[lpos[j][i] + 1][i] = 0;
            q.push_back(pii(lpos[j][i] + 1, i));
        }
    }
    sort(q.begin(), q.end(), [](pii a, pii b) { return a.x > b.x || (a.x == b.x && a.y - a.x < b.y - b.x); });

    for ( auto it : q ) 
    {
        if ( it.x > it.y ) continue ;
        REP(i, 0, 25) vis[i] = false;
        REP(i, 0, 25) 
        {
            int r = rpos[i][it.x], l = lpos[i][it.y];
            if ( r > it.y ) continue ;
            int x = g[it.x][i];
            if ( r < l ) 
                x ^= get(i, r, l - 1);
            x ^= h[it.y][i];
            vis[x] = true;
        }
        REP(i, 0, 25) if ( !vis[i] ) { f[it.x][it.y] = i; break ; }
        if ( it.y < n && rpos[s[it.y + 1] - 'a'][it.x] == it.y + 1 ) g[it.x][s[it.y + 1] - 'a'] = f[it.x][it.y];
        if ( it.x > 1 && lpos[s[it.x - 1] - 'a'][it.y] == it.x - 1 ) h[it.y][s[it.x - 1] - 'a'] = f[it.x][it.y];
        int c = s[it.x - 1] - 'a', pos = rpos[c][it.x];
        if ( it.x > 1 && s[it.x - 1] == s[it.y + 1] && rpos[c][it.x] == it.y + 1 )
            add(s[it.x - 1] - 'a', it.x - 1, f[it.x][it.y]);
    }

    REP(i, 1, m)
        if ( f[Q[i].x][Q[i].y] > 0 ) puts("Alice");
        else puts("Bob"); 
    return 0;
}
