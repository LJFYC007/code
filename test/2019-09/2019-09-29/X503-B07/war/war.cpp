/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2019年09月29日 星期日 08时32分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 110;
const int g = 3;
const int Mod = 998244353;
const int MAXN = 10010;

int n;

struct BigInt
{
    string s;
} a[maxn], b[maxn], ans, c, s, t;

int power(int a, int b)
{
    int r = 1; 
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
    REP(i, 0, ((m + n) << 1) + 100) a[i] = b[i] = 0;
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
    BigInt ans; ans.s.clear();
    for ( int i = n - 1; i >= 0; -- i ) ans.s += a[i] + '0';
    return ans;
}

inline BigInt operator + (BigInt a, BigInt b)
{
    return Solve(a.s, b.s, 0);
}

inline BigInt operator * (BigInt a, BigInt b)
{
    return Solve(a.s, b.s, 1);
}

inline bool cmp(BigInt a, BigInt b)
{
    if ( a.s.size() > b.s.size() ) return false;         
    if ( a.s.size() < b.s.size() ) return true;
    int n = a.s.size() - 1;
    REP(i, 0, n)
        if ( a.s[i] > b.s[i] ) return false;
        else if ( a.s[i] < b.s[i] ) return true;
    return false;
}

signed main()
{
    freopen("war.in", "r", stdin);
    freopen("war.out", "w", stdout);
    scanf("%lld", &n);    
    REP(i, 1, n) cin >> a[i].s;
    REP(i, 1, n) cin >> b[i].s;
    sort(a + 1, a + n + 1, cmp);
    // REP(i, 1, n) cout << a[i].s << " "; cout << endl;
    sort(b + 1, b + n + 1, cmp);
    // REP(i, 1, n) cout << b[i].s << " "; cout << endl;
    ans.s = "0";
    REP(i, 1, n)
    {
        s = a[i]; t = b[i];
        // cerr << cmp(s, t) << " " << (s * s).s << " " << (t * t).s << endl;
        if ( cmp(s, t) == true ) c = s * s;
        else c = t * t;
        // cerr << "lastans = " << ans.s << endl;
        // cerr << "c = " << c.s << endl;
        // cerr << "ans + c = " << (ans + c).s << endl;
        ans = ans + c;
        // cerr << "ans = " << ans.s << endl;
    }
    cout << ans.s << endl;
    return 0;
}