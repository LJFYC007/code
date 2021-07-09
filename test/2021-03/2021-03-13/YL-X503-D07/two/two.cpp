#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	// getchar
	inline char gc() 
	{
		return (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++) ;
	}
	// #define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	// print the remaining part
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	// putchar
	inline void putc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	// input a signed integer
	template <class I>
	inline void read (I &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
	}
	// print a signed integer
	template <class I>
	inline void print (I x) {
		if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) putc (qu[qr --]);
	}
	//no need to call flush at the end manually!
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: read;
using io :: putc;
using io :: print;
using io :: gc;

const int maxn = 3510;
int n, m, L[maxn], R[maxn], f[maxn][maxn], g[maxn][maxn], up[maxn][maxn], down[maxn][maxn], a[maxn][maxn];
long long ans;

inline void Solve(int n, int l, int r, int op, vector<int> tt)
{
	if ( n <= 1 || l >= r ) return ; 

	if ( op == 0 ) { int now = 0; REP(i, 1, n) REP(j, 1, r) a[i][j] = tt[now ++]; }
	else { int now = 0; REP(i, 1, n) REP(j, 1, r) a[j][i] = tt[now ++]; swap(n, r); }

	int Mid = l + r >> 1; 
	vector<int> b; 
	REP(i, 1, n) REP(j, l, Mid) b.push_back(a[i][j]);
	Solve(n, 1, Mid - l + 1, op ^ 1, b);
	b.clear();
	REP(i, 1, n) REP(j, Mid + 1, r) b.push_back(a[i][j]);
	Solve(n, 1, r - Mid, op ^ 1, b);

	REP(i, 1, n)
	{
		L[i] = 0; while ( L[i] < Mid - l + 1 && a[i][Mid - L[i]] == 1 ) ++ L[i];
		R[i] = 0; while ( R[i] < r - Mid && a[i][Mid + R[i] + 1] == 1 ) ++ R[i];
	}
	REP(i, 1, n) REP(j, 1, n) f[i][j] = g[i][j] = up[i][j] = down[i][j] = 0;
	
	REP(j, Mid + 1, r) 
	{
		int len = 0;
		REP(i, 1, n)
		{
			if ( a[i][j] == 1 ) { ++ len; continue ; } 
			REP(k, i - len, i - 1) if ( j <= Mid + R[k] ) { ++ down[k][k]; -- down[k][i]; } 
			len = 0;
		}
		REP(k, n - len + 1, n) if ( j <= Mid + R[k] ) ++ down[k][k]; 
		len = 0;
		for ( int i = n; i >= 1; -- i ) 
		{
			if ( a[i][j] == 1 ) { ++ len; continue ; } 
			REP(k, i + 1, i + len) if ( j <= Mid + R[k] ) { ++ up[k][k]; -- up[k][i]; } 
			len = 0;
		}
		REP(k, 1, len) if ( j <= Mid + R[k] ) ++ up[k][k];
	}
	REP(i, 1, n) REP(j, i, n) down[i][j] += down[i][j - 1];
	REP(i, 1, n) for ( int j = i; j >= 1; -- j ) up[i][j] += up[i][j + 1];
	REP(i, 1, n) 
	{
		REP(j, i + 1, n) if ( R[i] <= R[j] ) g[i][j] += down[i][j];
		for ( int j = i - 1; j >= 1; -- j ) if ( R[i] < R[j] ) g[j][i] += up[i][j];
	}

	REP(i, 1, n) REP(j, 1, n) up[i][j] = down[i][j] = 0;
	REP(j, l, Mid) 
	{
		int len = 0;
		REP(i, 1, n)
		{
			if ( a[i][j] == 1 ) { ++ len; continue ; } 
			REP(k, i - len, i - 1) if ( Mid - L[k] < j ) { ++ down[k][k]; -- down[k][i]; } 
			len = 0;
		}
		REP(k, n - len + 1, n) if ( Mid - L[k] < j ) ++ down[k][k]; 
		len = 0;
		for ( int i = n; i >= 1; -- i ) 
		{
			if ( a[i][j] == 1 ) { ++ len; continue ; } 
			REP(k, i + 1, i + len) if ( Mid - L[k] < j ) { ++ up[k][k]; -- up[k][i]; } 
			len = 0;
		}
		REP(k, 1, len) if ( Mid - L[k] < j ) ++ up[k][k]; 
	}
	REP(i, 1, n) REP(j, i, n) down[i][j] += down[i][j - 1];
	REP(i, 1, n) for ( int j = i; j >= 1; -- j ) up[i][j] += up[i][j + 1];
	REP(i, 1, n) 
	{
		REP(j, i + 1, n) if ( L[i] <= L[j] ) f[i][j] += down[i][j];
		for ( int j = i - 1; j >= 1; -- j ) if ( L[i] < L[j] ) f[j][i] += up[i][j];
	}

	REP(i, 1, n) REP(j, i, n) ans += 1ll * f[i][j] * g[i][j];
}

signed main()
{
	freopen("two.in", "r", stdin);
	freopen("two.out", "w", stdout);
	read(n); read(m); vector<int> a;
	REP(i, 1, n) REP(j, 1, m) { char c = gc(); while ( c != '.' && c != '#' ) c = gc(); a.push_back(c == '.'); }
	Solve(n, 1, m, 0, a);
	print(ans); putc('\n');
	return 0;
}
