/***************************************************************
	File name: T185755.cpp
	Author: ljfcnyali
	Create time: 2021年07月14日 星期三 15时05分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 810;

namespace IO {
const int MAXSIZE = 1 << 20;
char buf[MAXSIZE], *p1, *p2;
#define gc()                                                               \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) \
       ? EOF                                                               \
       : *p1++)
inline int read() {
  int x = 0, f = 1;
  char c = gc();
  while (!isdigit(c)) {
    if (c == '-') f = -1;
    c = gc();
  }
  while (isdigit(c)) x = x * 10 + (c ^ 48), c = gc();
  return x * f;
}
char pbuf[1 << 20], *pp = pbuf;
inline void push(const char &c) {
  if (pp - pbuf == 1 << 20) fwrite(pbuf, 1, 1 << 20, stdout), pp = pbuf;
  *pp++ = c;
}
inline void write(int x) {
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) push(sta[--top] + '0');
}
}  // namespace IO

using namespace IO;

int n, a[maxn][maxn], ans[maxn];
set<pii> Set;

inline void Solve(int x)
{
	int len = 0, pos = 1;
	for ( int i = n; i >= 1; -- i ) 
	{
		int cnt = 0;
		REP(j, 1, n - i + 1) 
		{
			if ( a[i][j] == x && !len ) len = i;
			if ( a[i][j] == x ) ++ cnt;
		}
		if ( len && cnt != len - i + 1 ) { pos = len - i; break ; } 
	}
	auto it = Set.lower_bound(pii(len, 0));
	int y = it -> second; Set.erase(it);
	ans[y + pos - 1] = x;
	if ( pos != 1 ) Set.insert(pii(pos - 1, y));
	if ( pos < len ) Set.insert(pii(len - pos, y + pos));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	n = read();
	REP(i, 1, n) REP(j, 1, n - i + 1) a[i][j] = read();
	Set.insert(pii(n, 1));
	REP(i, 1, n) Solve(i);
	REP(i, 1, n) printf("%d ", ans[i]); puts("");
    return 0;
}
