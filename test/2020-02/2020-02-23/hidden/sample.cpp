#include "hidden.hpp"
#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )

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
	inline void gi (I &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
	}
	// print a signed integer
	template <class I>
	inline void print (I &x) {
		if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) putc (qu[qr --]);
	}
	//no need to call flush at the end manually!
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: gi;
using io :: putc;
using io :: print;

const int maxn = 1e6 + 10;

vector<int>  s, ans;
bool flag, use[maxn];
int len, p[maxn], M;

inline void Check()
{
	REP(i, 0, (1 << len) - 1)
	{
		s.clear();
		for ( int j = len - 1; j >= 0; -- j ) s.push_back((i >> j) & 1);
		int ret = 0;
		REP(i, 0, M - 1) if ( p[i] == s[ret] ) ++ ret;
		if ( use[i] && ret < len ) return ;
		if ( !use[i] && ret >= len ) return ;
	}
	flag = true;
	REP(i, 0, M - 1) ans.push_back(p[i]);
}

inline void DFS(int x)
{
	if ( flag == true ) return ;
	if ( x == M ) { Check(); return ; }
	REP(i, 0, 1) { p[x] = i; DFS(x + 1); }
}

vector<int> guess(int n)
{
	M = n;
	len = n / 2 + 1;
	REP(i, 0, (1 << len) - 1)
	{
		s.clear();
		for ( int j = len - 1; j >= 0; -- j ) s.push_back((i >> j) & 1);
		if ( is_subsequence(s) )
		{
			use[i] = true;
			//for ( auto j : s ) cerr << j << " "; cerr << endl;
		}
	}
	DFS(0);
	return ans;
}
