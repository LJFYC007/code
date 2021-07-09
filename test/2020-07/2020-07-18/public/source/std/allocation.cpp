#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
typedef long long ll;
template <typename T> void chkmax(T &x, T y) {x = max(x, y); }
template <typename T> void chkmin(T &x, T y) {x = min(x, y); } 
template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
namespace KuhnMunkresForEachCapacity {
	const int MAXN = 505;
	const int INF  = 2e9;
	int nl, nr, a[MAXN][MAXN];
	bool visx[MAXN], visy[MAXN]; ll ans[MAXN];
	int x[MAXN], matchx[MAXN], home[MAXN];
	int y[MAXN], matchy[MAXN], slack[MAXN];
	void work() {
		chkmax(nr, nl);
		for (int i = 1; i <= nl; i++)
			x[i] = INF, matchx[i] = 0;
		for (int i = 1; i <= nr; i++)
			y[i] = matchy[i] = 0;
		for (int s = 1; s <= nl; s++) {
			for (int i = 1; i <= nr; i++) {
				visy[i] = false, home[i] = 0;
				slack[i] = INF;
			}
			for (int i = 1; i <= nl; i++)
				if (!matchx[i]) {
					visx[i] = true;
					for (int j = 1; j <= nr; j++) {
						int value = x[i] + y[j] - a[i][j];
						if (value < slack[j]) {
							slack[j] = value;
							home[j] = i;
						}
					}
				} else visx[i] = false;
			bool found = false;
			while (!found) {
				int delta = INF;
				for (int i = 1; i <= nr; i++)
					if (!visy[i]) chkmin(delta, slack[i]);
				for (int i = 1; i <= nl; i++)
					if (visx[i]) x[i] -= delta;
				for (int i = 1; i <= nr; i++)
					if (visy[i]) y[i] += delta;
					else slack[i] -= delta;
				for (int i = 1; i <= nr; i++)
					if (!visy[i] && slack[i] == 0) {
						visy[i] = true;
						if (!matchy[i]) {
							found = true;
							int pos = i, fa = home[pos];
							while (pos != 0) {
								int nxt = matchx[fa];
								matchx[fa] = pos, matchy[pos] = fa;
								pos = nxt, fa = home[pos];
							}
							break;
						} else {
							int pos = matchy[i];
							visx[pos] = true;
							for (int i = 1; i <= nr; i++) {
								if (visy[i]) continue;
								int value = x[pos] + y[i] - a[pos][i];
								if (value < slack[i]) {
									slack[i] = value;
									home[i] = pos;
								}
							}
						}
					}
			}
			for (int i = 1; i <= nl; i++)
				if (matchx[i]) ans[s] += a[i][matchx[i]];
		}
	}
}
int main() {
	freopen("allocation.in", "r", stdin);
	freopen("allocation.out", "w", stdout);
	int num; read(num);
	using namespace KuhnMunkresForEachCapacity;
	read(nl), nr = nl; int q; read(q);
	for (int i = 1; i <= nl; i++)
	for (int j = 1; j <= nr; j++)
		read(a[i][j]);
	work();
	for (int i = 1; i <= q; i++) {
		int x; read(x);
		chkmin(x, nl);
		printf("%lld.0\n", ans[x]);
	}
	return 0;
}