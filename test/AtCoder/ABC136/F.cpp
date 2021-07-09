/***************************************************************
	File name: F.cpp
	Author: ljfcnyali
	Create time: 2019年08月04日 星期日 19时58分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 200010;
const LL Mod = 998244353;

struct node
{
    int x, y;
} H[maxn];
int num, n;
LL ans, p[maxn];
int c[maxn][2];

inline int cmp1(node a, node b) { return a.x < b.x; }

inline int cmp2(node a, node b) { return a.y < b.y; }

inline int lowbit(int x) { return x & -x; }

inline void Add(int pos, int val, int opt) 
{ 
    for ( int i = pos; i <= n; i += lowbit(i) ) 
        c[i][opt] += val;
}

inline int getsum(int pos, int opt)
{
    int sum = 0;
    for ( int i = pos; i >= 1; i -= lowbit(i) )
        sum += c[i][opt];
    return sum;
}

int main()
{
    scanf("%d", &n);
    REP(i, 1, n) scanf("%d%d", &H[i].x, &H[i].y);
    sort(H + 1, H + n + 1, cmp1);
    REP(i, 1, n) H[i].x = i;
    sort(H + 1, H + n + 1, cmp2);
    REP(i, 1, n) H[i].y = i;
    sort(H + 1, H + n + 1, cmp1);
    p[0] = 1; REP(i, 1, n) p[i] = (p[i - 1] * 2) % Mod;
    ans = (p[n - 1] * 2) % Mod;
    REP(i, 3, n) Add(H[i].y, 1, 1);
    Add(H[1].y, 1, 0);
    REP(i, 2, n - 1)
    {
        LL a = getsum(H[i].y, 0), b = i - 1 - a;
        LL c = getsum(H[i].y, 1), d = n - i - c;
        // cerr << a << " " << b << " " << c << " " << d << endl;
        a = p[a] - 1; b = p[b] - 1; c = p[c] - 1; d = p[d] - 1;
        ans += (((a + 1) * (b + 1)) % Mod) * ((c + 1) * (d + 1)) % Mod; ans %= Mod;
        ans += (a * d) + (b * c); ans %= Mod;
        ans += (((a * d) % Mod) * b + ((a * d) % Mod) * c); ans %= Mod;
        ans += (((b * c) % Mod) * a + ((b * c) % Mod) * d); ans %= Mod;
        ans += (((b * c) % Mod) * ((a * d) % Mod) % Mod); ans %= Mod;
        Add(H[i].y, 1, 0);
        Add(H[i + 1].y, -1, 1);
    }
    printf("%lld\n", ans);
    return 0;
}
