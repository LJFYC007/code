#include <bits/stdc++.h>

using namespace std;

namespace Fast_IO {

const int __SIZE = 1 << 18;
char ibuf[__SIZE], *iS, *iT;

#define ll long long
#define ge (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)

template<typename T>
inline void read(T &x) {
	char ch, t = 0; x = 0;
	while(!isdigit(ch = ge)) t |= ch == '-';
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = ge;
	x = t ? -x : x;
}
inline int read_int() { int x; return read(x), x; }
inline ll read_ll() { ll x; return read(x), x; }

#undef ll
#undef ge
} using Fast_IO::read;

#define ri Fast_IO::read_int()
#define rl Fast_IO::read_ll()

int main() {
	return 0;
}
