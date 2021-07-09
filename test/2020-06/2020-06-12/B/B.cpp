/***************************************************************
    File name: B.cpp
    Author: ljfcnyali
    Create time: 2020年06月12日 星期五 08时01分10秒
***************************************************************/
#include<bits/stdc++.h>
  
using namespace std;
  
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;
  
const int maxn = 20000;
  
int n, m, p[2][maxn], z[maxn], Z[maxn];
bitset<maxn> g[3010];
string ans, s[3010], f[2];
  
inline void Get(string a, string b)
{
    int L = 0, R = 0, n = b.length(), m = a.length();
    REP(i, 1, n - 1)
    {
        if ( i <= R ) Z[i] = min(R - i + 1, Z[i - L]);
        else Z[i] = 0;
        while ( i + Z[i] < n && b[Z[i]] == b[i + Z[i]] ) ++ Z[i];
        if ( i + Z[i] - 1 > R ) { L = i; R = i + Z[i] - 1; }
    }
    L = R = 0;
    REP(i, 0, m - 1)
    {
        if ( i <= R ) z[i] = min(R - i + 1, Z[i - L]);
        else z[i] = 0;
        while ( z[i] < n && i + z[i] < m && b[z[i]] == a[i + z[i]] ) ++ z[i];
        if ( i + z[i] - 1 > R ) { L = i; R = i + z[i] - 1; }
    }
}
  
inline bool cmp(string a, string b)
{
    REP(i, 0, b.length() - 1) if ( a[i] != b[i] ) return false;
    return true;
}
  
int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) cin >> s[i];
    g[n].set(0, true);
    for ( int i = n - 1; i >= 1; -- i )
        g[i] = g[i + 1] | (g[i + 1] << s[i + 1].length());
    int o = 0;
    REP(i, 1, n)
    {
        int len = f[o].length(), l = s[i].length(), num = 0;
        // cout << f[o] << endl;
        // REP(j, 0, len - 1) cout << p[o][j]; cout << endl;
        assert(len <= m);
        int pos = -1; bool flag = false;
        if ( !g[i][m - l] ) flag = true;
        Get(f[o], s[i]);
        REP(j, 0, len - 1)
        {
            if ( m - j - 1 - l < 0 ) continue ;
            if ( !p[o][j] || !g[i][m - j - 1 - l] ) continue ;
            if ( flag == true ) { pos = j; flag = false; }
            else
            {
                int x = z[pos + 1], Len = j - pos;
                if ( x == l ) { pos = j; continue ; }
                if ( x < Len )
                {
                    if ( f[o][pos + x + 1] < s[i][x] ) pos = j;
                    continue ;
                }
                x = Z[Len];
                if ( x < l - Len )
                {
                    if ( s[i][x] < s[i][Len + x] ) pos = j;
                    continue ;
                }
                else pos = j;
            }
        }
        string t = f[o].substr(0, pos + 1) + s[i], x = f[o];
        if ( m >= x.length() && g[i][m - x.length()] && (flag == true || (!(x.length() < t.length() && cmp(t, x)) && x < t) || (x.length() > t.length() && cmp(x, t))) )
        {
            f[o ^ 1] = x; pos = f[o ^ 1].length() - 1;
        }
        else if ( flag == true ) { f[o ^ 1].clear(); continue ; }
        else f[o ^ 1] = t;
        REP(j, 0, f[o ^ 1].length() - 1) p[o ^ 1][j] = 0;
        while ( pos < (int)min(f[o].length(), f[o ^ 1].length()) - 1 && f[o][pos + 1] == f[o ^ 1][pos + 1] ) 
            ++ pos;
        REP(j, 0, pos) p[o ^ 1][j] = p[o][j];
        Get(f[o ^ 1], s[i]);
        REP(j, 0, f[o ^ 1].length() - 1)
        {
            if ( j + l > m || j + l > f[o ^ 1].length() ) continue ;
            if ( j > 0 && j - 1 >= f[o].length() ) continue ;
            if ( !g[i][m - j - l] || (j > 0 && !p[o][j - 1]) ) continue ;
            if ( z[j] == l ) p[o ^ 1][j + l - 1] = 1;
        }
        o ^= 1;
    }
    REP(j, 0, m - 1) printf("%c", f[o][j]);
    puts("");
    return 0;
}
