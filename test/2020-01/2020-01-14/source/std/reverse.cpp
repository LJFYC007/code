#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e5 + 5;
const int MAXM = 6e5 + 9;
const int Mod = 998244353;
const int P = 1e9 + 7;
const int Q = 1e9 + 9;
const int GP = 10001;
const int GQ = 10005;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
template <typename T> void chkmax(T &x, T y) { x = max(x, y); }
template <typename T> void chkmin(T &x, T y) { x = min(x, y); }
template <typename T> void read(T &x) {
  x = 0;
  int f = 1;
  char c = getchar();
  for (; !isdigit(c); c = getchar())
    if (c == '-')
      f = -f;
  for (; isdigit(c); c = getchar())
    x = x * 10 + c - '0';
  x *= f;
}
template <typename T> void write(T x) {
  if (x < 0)
    x = -x, putchar('-');
  if (x > 9)
    write(x / 10);
  putchar(x % 10 + '0');
}
template <typename T> void writeln(T x) {
  write(x);
  puts("");
}
struct info {
  int x, y;
};
int power(int x, int y, int P) {
  if (y == 0)
    return 1;
  int tmp = power(x, y / 2, P);
  if (y % 2 == 0)
    return 1ll * tmp * tmp % P;
  else
    return 1ll * tmp * tmp % P * x % P;
}
info operator+(info a, info b) {
  info ans;
  ans.x = (a.x + b.x >= P) ? (a.x + b.x - P) : (a.x + b.x);
  ans.y = (a.y + b.y >= Q) ? (a.y + b.y - Q) : (a.y + b.y);
  return ans;
}
info operator-(info a, info b) {
  info ans;
  ans.x = (a.x - b.x >= 0) ? (a.x - b.x) : (a.x - b.x + P);
  ans.y = (a.y - b.y >= 0) ? (a.y - b.y) : (a.y - b.y + Q);
  return ans;
}
info operator*(info a, int b) {
  info ans;
  ans.x = 1ll * a.x * b % P;
  ans.y = 1ll * a.y * b % Q;
  return ans;
}
info operator*(info a, info b) {
  info ans;
  ans.x = 1ll * a.x * b.x % P;
  ans.y = 1ll * a.y * b.y % Q;
  return ans;
}
bool operator==(info a, info b) { return a.x == b.x && a.y == b.y; }
info base, powb[MAXM];
info invb, powi[MAXM], sum[MAXM];
void update(int &x, int y) {
  x += y;
  if (x >= Mod)
    x -= Mod;
}
bool mark[MAXN];
int n, m, l, r, ans[MAXM];
int a[MAXN], powk[MAXN];
void popback() { r--; }
void popfront() { l++; }
void pushback(int x) {
  ans[++r] = x;
  sum[r] = sum[r - 1] + powb[r] * x;
}
void pushfront(int x) {
  ans[--l] = x;
  sum[l - 1] = sum[l] - powb[l] * x;
}
bool cmp(int s, int t, int len) {
  int l = 0, r = len;
  //	cerr << len << endl;
  while (l < r) {
    int mid = (l + r + 1) / 2;
    if ((sum[s + mid - 1] - sum[s - 1]) ==
        (sum[t + mid - 1] - sum[t - 1]) * powb[s - t])
      l = mid;
    else
      r = mid - 1;
  }
  if (l == len || ans[s + l] < ans[t + l])
    return true;
  else
    return false;
}
int main() {
  freopen("reverse.in", "r", stdin);
  freopen("reverse.out", "w", stdout);
  powb[0] = powi[0] = (info){1, 1};
  base = (info){GP, GQ};
  invb = (info){power(GP, P - 2, P), power(GQ, Q - 2, Q)};
  for (int i = 1; i < MAXM; i++) {
    powb[i] = powb[i - 1] * base;
    powi[i] = powi[i - 1] * invb;
  }
  powk[0] = 1;
  for (int i = 1; i < MAXN; i++)
    powk[i] = 37ll * powk[i - 1] % Mod;
  int T;
  read(T);
  for (int t = 1; t <= T; t++) {
    //	printf("Case %d: ", t);
    read(n), read(m);
    for (int i = 1; i <= n; i++)
      read(a[i]), mark[i] = false;
    for (int i = 1; i <= m; i++) {
      int x;
      read(x);
      mark[x] = true;
    }
    ans[l = r = MAXN] = a[1];
    sum[l - 1] = (info){0, 0};
    sum[l] = powb[l] * a[1];
    int last = 1;
    for (int i = 2; i <= n; i++)
      if (!mark[i]) {
        int len = i - last;
        int x = l, length = r - l + 1;
        for (int j = last + 1; j <= i; j++) {
          pushback(a[j]);
          pushfront(a[j]);
        }
        int y = l;
        //	cerr << length << endl;
        if (cmp(x, y, length + len)) {
          while (len--)
            popfront();
        } else {
          while (len--)
            popback();
        }
        last = i;
      }
    while (last != n)
      pushback(a[++last]);
    int final = 0;
    for (int i = l; i <= r; i++)
      update(final, 1ll * powk[i - l] * ans[i] % Mod);
    writeln(final);
  }
  return 0;
}
