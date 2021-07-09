/***************************************************************
	File name: P1919.cpp
	Author: ljfcnyali
	Create time: 2019年09月27日 星期五 09时02分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

struct BigInt
{
#define int long long
    const static int MAXN = 200010;
    const static int Mod = 998244353;
    const static int g = 3;

    string s;

    int power(int a, int b)
    {
        long long r = 1;
        while ( b ) { if ( b & 1 ) r = (r * a) % Mod; a = (a * a) % Mod; b >>= 1; }
        return r;
    }

    void NTT(int *f, int n, int inv) 
    {
        int r[MAXN];
        REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? n >> 1 : 0);
        REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
        for ( int Mid = 1; Mid < n; Mid <<= 1 )
        {
            int tmp = power(g, (Mod - 1) / (Mid << 1));
            if ( inv == -1 ) tmp = power(tmp, Mod - 2);
            for ( int i = 0; i < n; i += (Mid << 1) )
            {
                int sum = 1;
                for ( int j = 0; j < Mid; ++ j, sum = (sum * tmp) % Mod )
                {
                    int x = f[i + j], y = (sum * f[i + j + Mid]) % Mod;
                    f[i + j] = (x + y) % Mod; f[i + j + Mid] = (x - y + Mod) % Mod;
                }
            }
        }
    }

    BigInt Solve(string s1, string s2, bool x)
    {
        int a[MAXN], b[MAXN], n = s1.size() - 1, m = s2.size() - 1;
        for ( int i = n; i >= 0; -- i ) a[n - i] = s1[i] - '0';
        for ( int i = m; i >= 0; -- i ) b[m - i] = s2[i] - '0';
        m += n; n = 1;
        while ( n <= m ) n <<= 1;
        NTT(a, n, 1); NTT(b, n, 1);
        REP(i, 0, n - 1) if ( x == false ) a[i] = (a[i] + b[i]) % Mod; else a[i] = (a[i] * b[i]) % Mod;
        NTT(a, n, -1);
        int inv = power(n, Mod - 2);
        REP(i, 0, n - 1) a[i] = (a[i] * inv) % Mod;
        REP(i, 0, n - 1) a[i] = (a[i] + Mod) % Mod;
        REP(i, 0, n - 1)
            if ( a[i] >= 10 ) 
            {
                a[i + 1] += a[i] / 10;
                a[i] %= 10;
                if ( i == _end_ ) { ++ _end_; ++ n; }
            }
        while ( !a[n - 1] && n > 1 ) -- n;
        BigInt ans;
        for ( int i = n - 1; i >= 0; -- i ) ans.s += a[i] + '0';
        return ans;
    }

    BigInt operator + (BigInt &x) 
    {
        return Solve(s, x.s, 0);
    }

    BigInt operator * (BigInt &x) 
    {
        return Solve(s, x.s, 1);
    }

#undef int 
} A, B, C;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    return 0;
}
