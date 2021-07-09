/***************************************************************
	File name: card.cpp
	Author: ljfcnyali
	Create time: 2020年07月24日 星期五 14时50分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int Mod = 1e9 + 7;

int n, m, k, ans;
struct Matrix { int f[3][3]; } f;

Matrix operator * (Matrix a, Matrix b) 
{
    Matrix c;
    REP(i, 1, 2) REP(j, 1, 2) c.f[i][j] = 0;
    REP(i, 1, 2) REP(j, 1, 2) REP(k, 1, 2) c.f[i][j] = (c.f[i][j] + a.f[i][k] * b.f[k][j]) % Mod;
    return c;
}

inline Matrix power(Matrix f, int n)
{
    Matrix g = f; -- n;
    while ( n ) { if ( n & 1 ) g = g * f; f = f * f; n >>= 1; }
    return g;
}

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

namespace Subtask1
{
    struct Matrix { int f[4][4]; } f;

    Matrix operator * (Matrix a, Matrix b) 
    {   
        Matrix c;
        REP(i, 1, 3) REP(j, 1, 3) c.f[i][j] = 0;
        REP(i, 1, 3) REP(j, 1, 3) REP(k, 1, 3) c.f[i][j] = (c.f[i][j] + a.f[i][k] * b.f[k][j]) % Mod;
        return c;
    }

    inline Matrix power(Matrix f, int n)
    {
        Matrix g = f; -- n;
        while ( n ) { if ( n & 1 ) g = g * f; f = f * f; n >>= 1; }
        return g;
    }

    inline int main(int l, int r)
    {
        f.f[1][1] = l - 1; f.f[1][2] = r - l; f.f[1][3] = m - r + 1;
        f.f[2][1] = l - 1; f.f[2][2] = r - l; f.f[2][3] = m - r;
        f.f[3][1] = l - 1; f.f[3][2] = r - l - 1; f.f[3][3] = m - r + 1;

        f = power(f, n - 1);
        int x = l - 1, y = r - l, z = m - r + 1;
        int ret1 = (f.f[1][1] + f.f[1][2] + f.f[1][3]) * x % Mod;
        int ret2 = (f.f[2][1] + f.f[2][2] + f.f[2][3]) * y % Mod;
        int ret3 = (f.f[3][1] + f.f[3][2] + f.f[3][3]) * z % Mod;
        /*
        int ret1 = (f.f[1][1] + f.f[2][1] + f.f[3][1]) * x % Mod;
        int ret2 = (f.f[1][2] + f.f[2][2] + f.f[3][2]) * y % Mod;
        int ret3 = (f.f[1][3] + f.f[2][3] + f.f[3][3]) * z % Mod;
        */
        int ans = (ret1 + ret2 + ret3) % Mod;
        printf("%lld\n", (ans + Mod) % Mod);
        return 0;
    }
}

signed main()
{
    freopen("card.in", "r", stdin);
    freopen("card.out", "w", stdout);
    scanf("%lld%lld%lld", &m, &n, &k);
    if ( m < k ) 
    {
        int r = (k + 1) / 2, l = k - m;
        return Subtask1 :: main(l, r);
    }
    f.f[1][1] = k - 2; f.f[1][2] = k - 1;
    f.f[2][1] = m - k + 1; f.f[2][2] = m - k + 1;
    f = power(f, n - 1);
    int x = k - 1, y = m - k + 1;
    ans = ((f.f[1][1] + f.f[2][1]) * x + (f.f[1][2] + f.f[2][2]) * y) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
