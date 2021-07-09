/***************************************************************
	File name: matrix.cpp
	Author: ljfcnyali
	Create time: 2020年09月30日 星期三 16时06分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2010;
const int Mod = 998244353;

int n, cnt, ans;
vector<int> Edge[maxn];
bool vis[maxn];

inline void DFS(int u)
{
    vis[u] = true; ++ cnt; 
    for ( auto v : Edge[u] ) if ( !vis[v] ) 
        DFS(v);
}

// #define DEBUG 1  // 调试开关
struct IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
	char buf[MAXSIZE], *p1, *p2;
	char pbuf[MAXSIZE], *pp;
#if DEBUG
#else
	IO() : p1(buf), p2(buf), pp(pbuf) {}
	~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
	inline char gc() {
#if DEBUG  // 调试，可显示字符
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
#if DEBUG  // 调试，可显示字符
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

signed main()
{
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) REP(j, 1, n) { double x; io.read(x); if ( x > 0 ) Edge[i].push_back(j); }
    REP(i, 1, n) 
    { 
        cnt = 0; 
        mem(vis);
        DFS(i); 
        ans += cnt; 
    }
    cout << ans << endl;
    return 0;
}
