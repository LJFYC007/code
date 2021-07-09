/***************************************************************
	File name: password.cpp
	Author: ljfcnyali
	Create time: 2020年10月23日 星期五 09时58分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 210;
const int Mod = 1e9 + 7;

int m, T, l, n, p[maxn];
char s[10][maxn], S[maxn];
struct Matrix
{
    int n, m, a[maxn][maxn];
} f, g;
inline Matrix operator * (Matrix a, Matrix b)
{
    Matrix c; c.n = a.n; c.m = b.m;
    REP(i, 1, c.n) REP(j, 1, c.m) 
    {
        c.a[i][j] = 0;
        REP(k, 1, a.m) c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j]) % Mod;
    }
    return c;
}

inline int calc(int x)
{
    int ret = 0;
    REP(i, 1, str(S + 1) - l + 1)
    {
        bool flag = true;
        REP(j, 1, l) if ( S[i + j - 1] != s[x][j] ) { flag = false; break ; } 
        ret += flag;
    }
    return ret;
}

signed main()
{
    freopen("password.in", "r", stdin);
    freopen("password.out", "w", stdout);
    scanf("%lld", &m);
    REP(i, 1, m) scanf("%s", s[i] + 1); l = str(s[1] + 1);
    REP(i, 1, m) scanf("%lld", &p[i]);
    scanf("%lld", &T);
    while ( T -- ) 
    {
        scanf("%s", S + 1); scanf("%lld", &n);
        if ( n <= m ) 
        {
            continue ;
        }
        n -= m;
        f.n = 0; f.m = 1;
        REP(i, 1, m) f.a[++ f.n][1] = (i == p[1]);
        REP(i, 1, m) f.a[++ f.n][1] = (i == p[m]);
        REP(i, 1, m) REP(j, 1, m) f.a[++ f.n][1] = 0;
        REP(i, 1, m) f.a[++ f.n][1] = calc(i);

        REP(
    } 
    return 0;
}
