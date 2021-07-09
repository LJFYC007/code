/*
	Problem:	matrix.cpp
	Time:		2020-09-30 15:59
	Author:		CraZYali
	E-Mail:		yms-chenziyang@outlook.com 
*/

#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <bitset>
#include <iostream>
#include <cstdio>

using namespace std;
const double eps = 1e-8;
const int maxn = 2000 + 10;

template <typename T>
inline T read()
{
	T ans = 0, flag = 1;
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

#define file(FILE_NAME) freopen(FILE_NAME".in", "r", stdin), freopen(FILE_NAME".out", "w", stdout)

int n;
bitset <maxn> G[maxn];
struct IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
	char buf[MAXSIZE], *p1, *p2;
	char pbuf[MAXSIZE], *pp;
#if DEBUGG
#else
	IO() : p1(buf), p2(buf), pp(pbuf) {}
	~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
	inline char gc() {
#if DEBUGG  // 调试，可显示字符
		return getchar();
#endif
		if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
		return p1 == p2 ? ' ' : *p1++;
	}
	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	template <class T>
		inline void read(T &x) {
			register double tmp = 1;
			register bool sign = 0;
			x = 0;
			register char ch = gc();
			for (; !isdigit(ch); ch = gc())
				if (ch == '-') sign = 1;
			for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
			if (ch == '.')
				for (ch = gc(); isdigit(ch); ch = gc())
					tmp /= 10.0, x += tmp * (ch - '0');
			if (sign) x = -x;
		}
	inline void read(char *s) {
		register char ch = gc();
		for (; blank(ch); ch = gc())
			;
		for (; !blank(ch); ch = gc()) *s++ = ch;
		*s = 0;
	}
	inline void read(char &c) {
		for (c = gc(); blank(c); c = gc())
			;
	}
	inline void push(const char &c) {
#if DEBUGG  // 调试，可显示字符
		putchar(c);
#else
		if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
		*pp++ = c;
#endif
	}
	template <class T>
		inline void write(T x) {
			if (x < 0) x = -x, push('-');  // 负数输出
			static T sta[35];
			T top = 0;
			do {
				sta[top++] = x % 10, x /= 10;
			} while (x);
			while (top) push(sta[--top] + '0');
		}
	template <class T>
		inline void write(T x, char lastChar) {
			write(x), push(lastChar);
		}
} io;
int main()
{
	file("matrix");
	int n;
	io.read(n);
	DEBUG;
	REP(i, 1, n)
		REP(j, 1, n)
		{
			double x;
			io.read(x);
			if (x > eps)
				G[i][j] = 1;
		}
	DEBUG;
	REP(i, 1, n)
		REP(j, 1, n)
		if (G[j][i]) G[j] |= G[i];
	REP(i, 1, n) G[i][i] = 1;
	int ans = 0;
	REP(i, 1, n) ans += G[i].count();
	io.write(ans);
	return 0;
}
