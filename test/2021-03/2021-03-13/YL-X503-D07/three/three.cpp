#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>

const int maxn = 4e6 + 10;
const int INF = 2e18;

namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	// getchar
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
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
using io :: flush;

int n, Begin[maxn], Next[maxn], To[maxn], e, Q, dis[maxn], f[maxn];
int sum, num, size[maxn], Max[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS(int u, int fa, int MAX)
{
	int fucku = max(MAX, Max[u]), x = (fucku * num - sum) / 2; f[fucku] = max(f[fucku], x);
	// cout << u << " " << fucku << " " << sum << " " << MAX << endl;
	int Max1 = -1, Max2 = -1;
	for ( int i = Begin[u]; i; i = Next[i] ) 
	{
		int v = To[i]; if ( v == fa ) continue ; 
		if ( Max[v] > Max1 ) { Max2 = Max1; Max1 = Max[v]; } 
		else Max2 = max(Max2, Max[v]);
	}
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ; 
		sum += num - 2 * size[v];
		// int t = -1;
		// for ( int j = Begin[u]; j; j = Next[j] ) if ( To[j] != v && To[j] != fa ) t = max(t, Max[To[j]]);
		int t = Max1 == Max[v] ? Max2 : Max1;
		DFS(v, u, max(t + 1, MAX) + 1);
		sum -= num - 2 * size[v];
	}
}

inline void DFS1(int u, int fa)
{
	int son = 0;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ; 
		dis[v] = dis[u] + 1; DFS1(v, u); ++ son; size[u] += size[v];
		Max[u] = max(Max[u], Max[v] + 1); 
	}
	if ( !son || (u == 1 && son == 1) ) { ++ num; sum += dis[u]; size[u] = 1; } 
}

signed main()
{
	freopen("three.in", "r", stdin);
	freopen("three.out", "w", stdout);
	read(n);
	REP(i, 1, n - 1) 
	{ 
		int u, v; read(u); read(v); 
		add(u, n + i); add(n + i, u);
		add(v, n + i); add(n + i, v);
	}

	REP(i, 1, n) f[i] = -INF;
	DFS1(1, 0); DFS(1, 0, 0);
	REP(i, 3, n) f[i] = max(f[i], f[i - 2] + num);
	// REP(i, 1, n) cout << f[i] << " "; cout << endl;
	vector<int> p; REP(i, 1, n) p.push_back(f[i]); p.push_back(INF);
	read(Q);
	while ( Q -- ) 
	{
		int x; read(x); 
		int pos = lower_bound(p.begin(), p.end(), x) - p.begin() + 1;
		if ( pos > n ) 
		{
			pos = n + 2 * ((x - f[n] - 1) / num + 1);
			pos = min(pos, n - 1 + 2 * ((x - f[n - 1] - 1) / num + 1));
		}
		print(pos);
		putc('\n');
	}
	return 0;
}
