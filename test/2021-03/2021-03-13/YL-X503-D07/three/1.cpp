#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>

const int maxn = 2e6 + 10;
const int INF = 1e8;

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

int n, Begin[maxn], Next[maxn], To[maxn], e, Q, dis[maxn], s, t, Max;
int Stack[maxn], tot, ans[2], num[2], len[2];
pii Edge[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; } 

inline void DFS1(int u, int fa, int op)
{
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ; 
		dis[v] = dis[u] + 1; DFS1(v, u, op);
	}
	if ( dis[u] > len[op] ) len[op] = dis[u];
}

inline void DFS2(int u, int fa)
{
	Stack[++ tot] = u;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ; 
		dis[v] = dis[u] + 1; DFS2(v, u);
	}
	if ( dis[u] > Max ) 
	{ 
		Max = dis[u]; s = Stack[tot / 2]; t = Stack[tot / 2 + 1]; 
		len[0] = (tot / 2) - 1; len[1] = tot - len[0] - 2;
	}
	-- tot;	
}

inline void DFS3(int u, int fa, int op)
{
	bool son = false;
	for ( int i = Begin[u]; i; i = Next[i] )
	{
		int v = To[i]; if ( v == fa ) continue ; 
		dis[v] = dis[u] + 1; DFS3(v, u, op); son = true;
	}
	if ( !son ) 
	{
		++ num[op];
		ans[op] += len[op] - dis[u];
	}
}

inline bool Check(int x)
{
	REP(i, 1, n - 1)
	{
		ans[0] = ans[1] = len[0] = len[1] = 0;
		s = Edge[i].first; t = Edge[i].second;
		dis[s] = 1; dis[t] = 1; DFS1(s, t, 0); DFS1(t, s, 1);	
		DFS3(s, t, 0); DFS3(t, s, 1);

		int ret = len[0] + len[1] - 1, x = y - (ans[0] + ans[1]);
		int op = len[0] < len[1] ? 0 : (num[0] > num[1] ? 0 : 1);
		while ( x > 0 ) { ++ ret; x -= num[op]; op ^= 1; } 
	}
	return false;
}

int main()
{
	freopen("three.in", "r", stdin);
	freopen("three.out", "w", stdout);
	read(n);
	REP(i, 1, n - 1) { int u, v; read(u); read(v); add(u, v); add(v, u); Edge[i] = pii(u, v); } 
//	dis[1] = 1; DFS1(1, 0);
//	dis[t] = 1; DFS2(t, 0);
// 	printf("%d %d\n", s, t);
//	dis[s] = dis[t] = 1; DFS3(s, t, 0); DFS3(t, s, 1);
	read(Q);
	while ( Q -- ) 
	{
		int y, val = INF, l = 1, r = 10; read(y); 

		while ( l <= r ) 
		{
			int Mid = (l + r) >> 1;
			if ( Check(Mid) ) { val = Mid; r = Mid - 1; } 
			else l = Mid + 1;
		}
		print(val); putc('\n');
	}
	return 0;
}
