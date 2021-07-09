#include <bits/stdc++.h>
#define N 125
#define clr(x) memset(a[x], 0, sizeof *a)

typedef std::vector <int> vec;

// O (p * prime * T) = 30240 * 26 * 120

const int P = 30240; // 32 * 27 * 5 * 7
const int p[26] = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113};

int n;
int a[N][N], buf[N];
bool fy[N];
int cnt = 0, z[N];
int mod[N][N];

inline void up(int &x, const int y) {x < y ? x = y : 0;}

int main() {

	freopen("silence.in", "r", stdin);
	freopen("silence1.out", "w", stdout);
	int i, j, k, u, v, w, T, cur, ans = 0;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i)
		for (scanf("%d", &T), j = 0; j < T; ++j) scanf("%d", &v), a[T][j] += v;
	// clear large identities
	for (i = 0; i < 32; ++i) a[32][i] += std::max(a[64][i], a[64][i + 32]);
	for (i = 0; i < 27; ++i) a[27][i] += std::max(std::max(a[81][i], a[81][i + 27]), a[81][i + 54]);
	for (i = 0; i < 14; a[14][i] += v, ++i)
		for (v = 0, j = i; j < 112; j += 14) up(v, a[49][j % 49] + a[98][j]);
	for (i = 0; i < 60; a[60][i] += v, ++i)
		for (v = 0, j = i; j < 360; j += 60) up(v, a[25][j % 25] + a[50][j % 50] + a[75][j % 75] + a[100][j % 100]);
	clr(25); clr(49); clr(50); clr(64); clr(75); clr(81); clr(98); clr(100);
	// enumerating
	for (i = 0; i < 26; ++i) for (j = p[i]; j <= 120; j += p[i]) fy[j] = true;
	for (i = 1; i <= 120; ++i) {
		if (!fy[i]) z[++cnt] = i;
		for (j = 0; j <= 120; ++j) mod[i][j] = j % i;
	}
	for (v = 0; v < P; ++v) {
		cur = 0;
		for (i = 1; i <= cnt; ++i) cur += a[z[i]][v % z[i]];
		for (i = 0; i < 26; ++i) {
			memset(buf, 0, (j = p[i]) << 2);
			for (k = 1; (w = j * k) <= 120; ++k)
				for (u = v % k; u < w; u += k) buf[mod[j][u]] += a[w][u];
			for (w = k = 0; k < j; ++k) up(w, buf[k]); cur += w;
		}
		up(ans, cur);
	}
	printf("%d\n", ans);
	return 0;
}
