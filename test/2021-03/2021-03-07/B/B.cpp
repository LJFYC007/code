/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年03月07日 星期日 09时20分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e6 + 10;
const int Mod = 998244353;
const int inv2 = (Mod + 1) / 2;

int T, n, fac[maxn], inv[maxn], r[maxn], buf[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int sgn(int x) { return x & 1 ? -1 : 1; } 
inline int add(int x, int y) { return x + y >= Mod ? x + y - Mod : x + y; }

inline void NTT(vector<int> &a, int inv)
{
	int n = a.size();
	vector<unsigned long long> f(n); 
	REP(i, 0, n - 1) f[i] = a[i] < 0 ? a[i] + Mod : a[i];
    REP(i, 0, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    REP(i, 0, n - 1) if ( i < r[i] ) swap(f[i], f[r[i]]);
	buf[0]=1;
    for ( int Mid = 1; Mid < n; Mid <<= 1 ) 
    {
        int tmp = power(3, (Mod - 1) / (Mid << 1));
        if ( inv == -1 ) tmp = power(tmp, Mod - 2); 
		for(int i=Mid;i>0;i-=2)buf[i]=buf[i>>1];
		for(int i=1;i<Mid;i+=2)buf[i]=buf[i-1]*tmp%Mod;
        for ( int i = 0; i < n; i += (Mid << 1) ) 
        {
            int sum = 1;
            for ( int j = 0; j < Mid; ++ j) 
            {
                int x = f[i + j], y = f[i + Mid + j] * buf[j] % Mod;
				f[i + j] = x+y; f[i + Mid + j] = x + Mod - y;
            }
        }
		if(Mid==(1<<17)){
			for(int i=0;i<n;++i)f[i]%=Mod;
		}
    }
	for(int i=0;i<n;++i)if(f[i]>=Mod)f[i]%=Mod;
    if ( inv == -1 ) 
    {
        inv = power(n, Mod - 2); 
        REP(i, 0, n - 1) f[i] = f[i] * inv % Mod;
    }
	REP(i, 0, n - 1) a[i] = f[i] % Mod;
}

inline vector<int> operator *(vector<int> a, vector<int> b)
{
	int n = a.size(), m = b.size(), len = 1;
	while ( len < n + m - 1 ) len <<= 1; a.resize(len); b.resize(len);
	NTT(a, 1); NTT(b, 1); REP(i, 0, len - 1) a[i] = a[i] * b[i] % Mod; NTT(a, -1);
	a.resize(n + m - 1); return a;
}


vector<int> Inv(vector<int> f){
	int n = f.size(); vector<int> g(n);
	if(n==1){g[0]=power(f[0],Mod-2);return g;}
	g = f; g.resize((n + 1) / 2); g = Inv(g);
	int len=1;
	while(len<=n*3/2+1)len<<=1;
	vector<int> a(len), b(len);
	int m=(n+1)>>1;
	for(int i=0;i<m;++i)b[i]=g[i];
	for(int i=0;i<n;++i)a[i]=f[i];
	NTT(b,1);
	NTT(a,1);
	for(int i=0;i<len;++i)a[i]=a[i]*b[i]%Mod*b[i]%Mod;
	NTT(a,-1);
	g.resize(n);
	for(int i=m;i<n;++i)g[i]=Mod-a[i];
	return g;
}
inline vector<int> Sqrt(vector<int> f)
{
    vector<int> g, h;
    if ( f.size() == 1 ) { g.resize(1); g[0] = 1; return g; }
    int n = f.size(); g = f; g.resize((n + 1) / 2);
    g = Sqrt(g); g.resize(n); h = Inv(g); g = g * g; g.resize(n);
    REP(i, 0, n - 1) { f[i] = (g[i] + f[i]) % Mod; h[i] = h[i] * inv2 % Mod; }
    f = f * h; 
	f.resize(n); 
	return f;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &T); n = 1000000; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;

	vector<int> f(n + 1);
	REP(i, 0, n) f[i] = -2 * inv[i] % Mod;	
	f[0] += 3; f = Sqrt(f);
	while ( T -- ) 
	{
		scanf("%lld", &n); 
		printf("%lld\n", (-f[n] * fac[n] % Mod + Mod - 1) % Mod);
	}
    return 0;
}
