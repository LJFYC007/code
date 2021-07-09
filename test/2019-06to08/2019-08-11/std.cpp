#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
long long read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 1e6 + 5;
int n, m, x, y;
int top, w[Max_n], stk[Max_n];
long long s[Max_n], h[Max_n], f[Max_n], g[Max_n];
long long must[Max_n], G[Max_n];
long long F(int x) { return 1ll * (x + 1) * (x) / 2; }
double slp1(int i, int j) {
  return (double)(f[i] + s[i] + F(i - 1) - f[j] - s[j] - F(j - 1)) /
         (i - j);
}
double slp2(int i, int j) {
  return (double)(g[i] + h[i] + F(i) - g[j] - h[j] - F(j)) /
         (i - j);
}
void Max(long long &a, long long b) { a = a < b ? b : a; }
void Solve(int l, int r) {
  int mid = (l + r) >> 1;
  if (l == r) {
    Max(must[l], f[l - 1] + g[l + 1] - w[l] + 1);
    return;
  }
  top = 0;
  G[r + 1] = G[l - 1] = -2e18;
  for (int i = l - 1; i < mid; i++) {
    while (top > 1 && slp1(stk[top - 1], stk[top]) < slp1(stk[top], i)) top--;
    stk[++top] = i;
  }
  for (int i = mid; i <= r; i++) {
    while (top > 1 && slp1(stk[top - 1], stk[top]) < i) top--;
    G[i] = f[stk[top]] + F(i - stk[top]) - s[i] + s[stk[top]] + g[i + 1];
  }
  for (int i = r; i >= mid; i--) Max(G[i], G[i + 1]), Max(must[i], G[i]);
  top = 0;
  for (int i = r + 1; i > mid; i--) {
    while (top > 1 && slp2(stk[top - 1], stk[top]) > slp2(stk[top], i)) top--;
    stk[++top] = i;
  }
  for (int i = mid; i >= l; i--) {
    while (top > 1 && slp2(stk[top - 1], stk[top]) > i) top--;
    G[i] = g[stk[top]] + F(stk[top] - i) - h[i] + h[stk[top]] + f[i - 1];
  }
  for (int i = l; i <= mid; i++) Max(G[i], G[i - 1]), Max(must[i], G[i]);
  Solve(l, mid), Solve(mid + 1, r);
}
int main() {
  n = read();
  for (int i = 1; i <= n; i++) w[i] = read();
  for (int i = 1; i <= n; i++) s[i] = s[i - 1] + w[i];
  for (int i = n; i >= 1; i--) h[i] = h[i + 1] + w[i];
  stk[top = 1] = 0;
  for (int i = 1; i <= n; i++) {
    while (top > 1 && slp1(stk[top - 1], stk[top]) < i) top--;
    f[i] = f[stk[top]] + F(i - stk[top]) - s[i] + s[stk[top]];
    Max(f[i], f[i - 1]);
    while (top > 1 && slp1(stk[top - 1], stk[top]) < slp1(stk[top], i)) top--;
    stk[++top] = i;
  }
  stk[top = 1] = n + 1;
  for (int i = n; i >= 1; i--) {
    while (top > 1 && slp2(stk[top - 1], stk[top]) > i) top--;
    g[i] = g[stk[top]] + F(stk[top] - i) - h[i] + h[stk[top]];
    Max(g[i], g[i + 1]);
    while (top > 1 && slp2(stk[top - 1], stk[top]) > slp2(stk[top], i)) top--;
    stk[++top] = i;
  }
  for (int i = 1; i <= n; i++) must[i] = -2e18; 
  Solve(1, n);
  m = read();
  while (m--) {
    x = read(), y = read();
    printf("%lld\n", max(f[x - 1] + g[x + 1], must[x] + w[x] - y));
  }
}
