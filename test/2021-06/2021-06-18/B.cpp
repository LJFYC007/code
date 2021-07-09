/***************************************************************
    File name: B.cpp
    Author: ljfcnyali
    Create time: 2021年06月18日 星期五 20时09分09秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 4e5 + 10;
const int Mod = 1004535809;
 
int n, m, a[maxn], b[maxn], belong[maxn], B, R[maxn], ccc[maxn];
vector<int> p[maxn], f, g;
 
inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = 1ll * r * a % Mod; a = 1ll * a * a % Mod; b >>= 1; } return r; }
 
inline int add(int x, int y) { return x + y >= Mod ? x + y - Mod : x + y; }
 
#define u64 unsigned long long
#define i64 long long
void NTT(vector<int> &a, int flag)
{
	static u64 T[maxn]; int n = a.size();
	REP(i, 0, n - 1) T[i] = a[i];
	if (flag < 0) reverse(T + 1, T + n);
	static int *w[30], pool[maxn << 1 | 10];
	static bool vis[30];
	w[0] = pool;
	REP(i, 0, n - 1)
	{
		R[i] = (R[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
		if (i < R[i]) swap(T[i], T[R[i]]);
	}
	for (int i = 1, c = 0; i < n; i <<= 1, c++)
	{
		if (!vis[c])
		{
			vis[c] = 1;
			const i64 wn = power(3, (Mod - 1) >> c + 1);
			if (i < maxn) w[c + 1] = w[c] + i;
			w[c][0] = 1;
			REP(j, 1, i - 1) w[c][j] = w[c][j - 1] * wn % Mod;
		}
		for (int k = 0; k < n; k += i + i)
			for (int l = 0; l < i; l++)
			{
				u64 x(T[k + l]), y(T[k + l + i] * w[c][l] % Mod);
				T[k + l] = x + y;
				T[k + l + i] = Mod + x - y;
			}
	}
	REP(i, 0, n - 1) a[i] = T[i] % Mod;
	if (flag < 0)
	{
		const int invn = power(n, Mod - 2);
		REP(i, 0, n - 1) a[i] = 1ll * a[i] * invn % Mod;
	}
}
 
vector<int> operator *(vector<int> a, vector<int> b)
{
    int n = a.size(), m = b.size(), len = 1;
    while ( len < n + m - 1 ) len <<= 1; a.resize(len); b.resize(len);
    NTT(a, 1); NTT(b, 1); REP(i, 0, len - 1) a[i] = 1ll * a[i] * b[i] % Mod; NTT(a, -1);
    REP(i, 0, n + m - 2) a[i] = (a[i] + Mod) % Mod;
    a.resize(n + m - 1); return a;
}

inline void read(int &x)
{
	char c = getchar(); x = 0;
	while ( c < '0' || c > '9' ) c = getchar();
	while ( c >= '0' && c <= '9' ) { x = x * 10 + c - '0'; c = getchar(); } 
}
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); REP(i, 1, n) read(a[i]);
    scanf("%d", &m); B = 1600;
    REP(i, 1, n) belong[i] = (i - 1) / B + 1;
    REP(o, 1, m)
    {
        int l, r, x; read(l); read(r); read(x);
        if ( belong[l] + 1 >= belong[r] ) REP(i, l, r) b[x + i - l] += a[i];
        else
        {
            REP(i, l, belong[l] * B) b[x + i - l] += a[i];
            REP(i, belong[r] * B - B + 1, r) b[x + i - l] += a[i];
            REP(i, belong[l] + 1, belong[r] - 1) p[i].push_back(x + i * B - B + 1 - l);
        }
    }
 
    REP(o, 1, belong[n])
    {
        f.clear(); REP(i, o * B - B + 1, min(o * B, n)) f.push_back(a[i]);
        g.clear(); g.resize(n); REP(i, 0, n - 1) g[i] = 0;  
        for ( auto it : p[o] ) ++ g[it - 1];
        f = f * g;
        REP(i, 0, n - 1) b[i + 1] = (b[i + 1] + f[i]) % Mod;
    }
 
    REP(i, 1, n) printf("%d\n", (b[i] + Mod) % Mod);
    return 0;
}
