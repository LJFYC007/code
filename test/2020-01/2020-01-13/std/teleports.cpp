#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>

using namespace std;

#define clr(x) memset(x, 0, sizeof(x))
#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define For(i, st, en) for (int i = (st); i <= (int)(en); i++)
#define Ford(i, st, en) for (int i = (st); i >= (int)(en); i--)

typedef long long i64;

#define BASE 10000

int a[102400];
int p[102400];
bool c[202400];
bool u[102400];

int zz[102400];
int ans[102400];

void precalc() {
  clr(c);
  For(i, 2, 1000) {
    if (c[i])
      continue;
    int j = i * i;
    while (j <= 200000) {
      c[j] = true;
      j += i;
    }
  }
  p[0] = 0;
  For(i, 2, 200000) {
    if (!c[i])
      p[++p[0]] = i;
  }
}

void multak(int *a, int k) {
  int j = 0;
  For(i, 1, a[0]) {
    j += a[i] * k;
    a[i] = j % BASE;
    j /= BASE;
  }
  while (j)
    a[++a[0]] = j % BASE, j /= BASE;
}

int modak(int *a, int k) {
  int j = 0;
  Ford(i, a[0], 1) { j = (j * BASE + a[i]) % k; }
  return j;
}

void addmul(int *a, int *b, int k) {
  int j = 0;
  if (a[0] < b[0])
    a[0] = b[0];
  For(i, 1, a[0]) {
    j = j + a[i] + b[i] * k;
    a[i] = j % BASE;
    j /= BASE;
  }
  while (j)
    a[++a[0]] = j % BASE, j /= BASE;
}

void writelong(int *a) {
  printf("%d", a[a[0]]);
  Ford(i, a[0] - 1, 1) { printf("%04d", a[i]); }
  puts("");
}

int mypow(int a, int k, int p) {
  int ans = 1;
  int j = 1;
  while (j <= k)
    j <<= 1;
  j >>= 1;
  while (j) {
    ans = (i64)ans * ans % p;
    if (j & k)
      ans = (i64)ans * a % p;
    j >>= 1;
  }
  return ans;
}

void chineseRestore(int *a, int *p, int n) {
  clr(zz);
  clr(ans);
  ans[0] = 1;
  zz[0] = 1;
  zz[1] = 1;

  forn(i, n) {
    int m = modak(ans, p[i]);
    int zm = modak(zz, p[i]);
    int t = (i64)mypow(zm, p[i] - 2, p[i]) * ((a[i] - m + p[i]) % p[i]) % p[i];
    addmul(ans, zz, t);
    multak(zz, p[i]);
  }

  writelong(ans);
}

void solve(int n) {
  int s = 0;
  For(i, 1, p[0]) {
    if (p[i] + p[i + 1] - 1 > n) {
      s = i - 1;
      break;
    }
  }

  For(i, 1, s - 1) { a[i] = (p[i] - (p[s] - 1) % p[i]) % p[i]; }
  a[s] = 0;
  a[s + 1] = (p[s + 1] - (p[s] - 1 - 1) % p[s + 1]) % p[s + 1];
  a[s + 2] = (p[s + 2] - (p[s] * 2 - 1) % p[s + 2]) % p[s + 2];
  memset(u, 0, n * sizeof(*u));
  For(i, 1, s + 2) {
    int z = (p[i] - a[i]) % p[i];
    while (z < n) {
      u[z] = true;
      z += p[i];
    }
  }
  int t = s + 3;
  forn(i, n) {
    if (!u[i]) {
      u[i] = true;
      a[t] = (p[t] - (i + 1 - 1) % p[t]) % p[t];
      int z = (p[t] - a[t]) % p[t];
      while (z < n) {
        u[z] = true;
        z += p[t];
      }
      t++;
    }
  }

  chineseRestore(a + 1, p + 1, t - 1);
}

int main() {
  freopen("teleports.in", "rt", stdin);
  freopen("teleports.out", "wt", stdout);

  precalc();
  int n;
  scanf("%d", &n);
  assert((n >= 1) && (n <= 100000));
  if (n == 1)
    puts("1");
  else if (n <= 16)
    puts("No solution");
  else
    solve(n);

  return 0;
}
