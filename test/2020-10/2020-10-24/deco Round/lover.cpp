#include <bits/stdc++.h>
#define LL long long
#define pI pair <LL, LL>
#define MOD 998244353
using namespace std;
LL n, m;
LL f[56][38][20][20], g[2][56][38][20][20], tmp;
int ci[10][4] =
{
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{2, 0, 0, 0},
	{0, 0, 1, 0},
	{1, 1, 0, 0},
	{0, 0, 0, 1},
	{3, 0, 0, 0},
	{0, 2, 0, 0}};
int pi[4] = {2, 3, 5, 7};


LL s[5][56][38][20][20], h[5][56][38][20][20], ans[56][38][20][20];
LL ansfin;


void md(LL &a) {if (a >= MOD) a -= MOD;}
int mi[4], s0;
pI ccmap[10000]; int tot;
LL powi(LL a, LL b)
{
	LL c = 1;
	for (LL p = 1; p <= b; ++ p)
		c = c * a;
	return c;
}
int main()
{
	cin >> n >> m;
	{
		LL nn = n;
		while (nn)
		{
			LL s = nn % 10;
			for (int i = 0; i < 4; ++ i)
				mi[i] += ci[s][i];
			if (s == 0) s0 ++;
			nn /= 10;
		}
	}
	{
	g[0][0][0][0][0] = 1;
	LL nn = n;
	for (int i = 1; nn; ++ i, nn /= 10)
	{
		int s = nn % 10;
		for (int j = 0; j < 4; ++ j)
			mi[j] -= ci[s][j];
		if (s == 0) s0 --;
		for (LL a = 0; a <= 54; ++ a)
			for (LL b = 0; b <= 36; ++ b)
				for (LL c = 0; c <= 18; ++ c)
					for (LL d = 0; d <= 18; ++ d)
						if (g[tmp][a][b][c][d])
						{
							if (nn >= 10)
							{
								for (LL p = 1; p < 10; ++ p)
									f[a + ci[p][0]][b + ci[p][1]][c + ci[p][2]][d + ci[p][3]] +=
										g[tmp][a][b][c][d],
									md(f[a + ci[p][0]][b + ci[p][1]][c + ci[p][2]][d + ci[p][3]]);
								if (!s0)
									for (LL p = 1; p <= (i == 1? s: s - 1); ++ p)
										f[a + mi[0] + ci[p][0]][b + mi[1] + ci[p][1]]
											[c + mi[2] + ci[p][2]][d + mi[3] + ci[p][3]] +=
											g[tmp][a][b][c][d],
										md(f[a + mi[0] + ci[p][0]][b + mi[1] + ci[p][1]]
											[c + mi[2] + ci[p][2]][d + mi[3] + ci[p][3]]);
							}
							else
							{
								for (LL p = 1; p <= (i == 1? s: s - 1); ++ p)
									f[a + mi[0] + ci[p][0]][b + mi[1] + ci[p][1]]
										[c + mi[2] + ci[p][2]][d + mi[3] + ci[p][3]] +=
										g[tmp][a][b][c][d],
									md(f[a + mi[0] + ci[p][0]][b + mi[1] + ci[p][1]]
										[c + mi[2] + ci[p][2]][d + mi[3] + ci[p][3]]);
							}
						}

		tmp ^= 1;
		for (LL a = 0; a <= 54; ++ a)
			for (LL b = 0; b <= 36; ++ b)
				for (LL c = 0; c <= 18; ++ c)
					for (LL d = 0; d <= 18; ++ d)
						g[tmp][a][b][c][d] = 0;

		for (LL a = 0; a <= 54; ++ a)
			for (LL b = 0; b <= 36; ++ b)
				for (LL c = 0; c <= 18; ++ c)
					for (LL d = 0; d <= 18; ++ d)
						if (g[!tmp][a][b][c][d])
						{
							for (LL p = 1; p < 10; ++ p)
							{
								g[tmp][a + ci[p][0]][b + ci[p][1]][c + ci[p][2]][d + ci[p][3]] +=
									g[!tmp][a][b][c][d];
								md(g[tmp][a + ci[p][0]][b + ci[p][1]][c + ci[p][2]][d + ci[p][3]]);
							}
						}
	}
	}
	for (LL a = 54; ~a; -- a)
		for (LL b = 36; ~b; -- b)
			for (LL c = 18; ~c; -- c)
				for (LL d = 18; ~d; -- d)
				{
					s[1][a][b][c][d] = s[1][a][b][c][d + 1] + f[a][b][c][d], md(s[1][a][b][c][d]);
					s[2][a][b][c][d] = s[2][a][b][c + 1][d] + s[1][a][b][c][d], md(s[2][a][b][c][d]);
					s[3][a][b][c][d] = s[3][a][b + 1][c][d] + s[2][a][b][c][d], md(s[3][a][b][c][d]);
					s[4][a][b][c][d] = s[4][a + 1][b][c][d] + s[3][a][b][c][d], md(s[4][a][b][c][d]);
				}
	for (LL a = 54, aa = powi(2, a); ~a; -- a, aa /= 2)
		for (LL b = 36, bb = powi(3, b); ~b; -- b, bb /= 3)
			for (LL c = 18, cc = powi(5, c); ~c; -- c, cc /= 5)
				for (LL d = 18, dd = powi(7, d); ~d; -- d, dd /= 7)
				{
					h[1][a][b][c][d] = h[1][a][b][c][d + 1], md(h[1][a][b][c][d]);
					h[2][a][b][c][d] = h[2][a][b][c + 1][d] + h[1][a][b][c][d], md(h[2][a][b][c][d]);
					h[3][a][b][c][d] = h[3][a][b + 1][c][d] + h[2][a][b][c][d], md(h[3][a][b][c][d]);
					h[4][a][b][c][d] = h[4][a + 1][b][c][d] + h[3][a][b][c][d], md(h[4][a][b][c][d]);
					ans[a][b][c][d] = s[4][a][b][c][d] * s[4][a][b][c][d] - h[4][a][b][c][d] + MOD;
					ans[a][b][c][d] %= MOD;
					if (1.0 * aa * bb * cc * dd / 2 <= m)
						if (aa * bb * cc * dd <= m)
							ansfin += ans[a][b][c][d], md(ansfin);
					for (int k = 1; k <= 4; ++ k) h[k][a][b][c][d] += ans[a][b][c][d], md(h[k][a][b][c][d]);

				}

	cout << ansfin;
}
