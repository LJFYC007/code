/***************************************************************
	File name: antieasy.cpp
	Author: ljfcnyali
	Create time: 2021年01月11日 星期一 08时53分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int __int128
typedef long long LL;

const int maxn = 1e6 + 10;

int Mod, n, m, b, p, q, Hash[maxn], fac[maxn], inv[maxn];
unsigned long long seed;
struct node { int l, p1, p2; bool flag; } Q[maxn];
char s[maxn], t[10];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

inline void read(int &x)
{
    char c = getchar(); x = 0;
    while ( c < '0' || c > '9' ) c = getchar();
    while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); } 
}

inline unsigned long long NEXT_SEED()
{
    seed = seed ^ seed >> 12;
    seed = seed ^ seed << 25;
    seed = seed ^ seed >> 27;
    return seed;
}

inline int Rand_Int(int l, int r) { return NEXT_SEED() % (r - l + 1) + l; }

inline int Val(int x) { return s[x] == '(' ? p : q; }

inline int Get(int l, int r)
{
    int val = (Hash[r] - Hash[l - 1]) % Mod;
    val = val * inv[l - 1] % Mod;
    return (val + Mod) % Mod;
}

signed main()
{
    read(Mod); read(n); read(m);
    scanf("%s", s + 1);
    REP(i, 1, (m + 1) / 2)
    {
        read(Q[i].l); read(Q[i].p1); read(Q[i].p2); 
        scanf("%s", t + 1); if ( t[1] == 'Y' ) Q[i].flag = true;        
    }
    REP(i, (m + 1) / 2 + 1, m) { read(Q[i].l); read(Q[i].p1); read(Q[i].p2); }
    
    srand(time(0));
    REP(o, 1, 100000000ll / n)
    {
        seed = rand(); 
        int ans = seed; REP(i, 1, 10) NEXT_SEED();
        b = Rand_Int(1, Mod - 1); 
        p = Rand_Int(1, Mod - 1);
        q = Rand_Int(1, Mod - 1);
        fac[0] = inv[0] = 1; int invb = power(b, Mod - 2);
        REP(i, 1, n) { fac[i] = fac[i - 1] * (LL)b % Mod; inv[i] = inv[i - 1] * (LL)invb % Mod; }
        REP(i, 1, n) Hash[i] = (Hash[i - 1] + Val(i) * fac[i - 1]) % Mod;
        
        REP(i, 1, (m + 1) / 2)
        {
            bool t = Get(Q[i].p1, Q[i].p1 + Q[i].l - 1) == Get(Q[i].p2, Q[i].p2 + Q[i].l - 1);
            if ( t != Q[i].flag ) goto Next ;
        }
        printf("%lld\n", (long long)ans);
        REP(i, 1, m)
        {
            // cout << (LL)Get(Q[i].p1, Q[i].p1 + Q[i].l - 1) << endl;
            // cout << (LL)Get(Q[i].p2, Q[i].p2 + Q[i].l - 1) << endl;
            bool t = Get(Q[i].p1, Q[i].p1 + Q[i].l - 1) == Get(Q[i].p2, Q[i].p2 + Q[i].l - 1);
            if ( t ) puts("Yes"); else puts("No");
        }
        return 0;
Next : ;
    }
    cerr << "Fuck" << endl;
    return 0;
}
