#include <bits/stdc++.h>
using namespace std;
namespace Base {
#define mr make_pair
typedef long long ll;
typedef double db;
const int inf = 0x3f3f3f3f, INF = 0x7fffffff;
const ll infll = 0x3f3f3f3f3f3f3f3fll, INFll = 0x7fffffffffffffffll;
template <typename T> void read(T &x) {
  x = 0;
  int fh = 1;
  double num = 1.0;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-')
      fh = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  if (ch == '.') {
    ch = getchar();
    while (isdigit(ch)) {
      num /= 10;
      x = x + num * (ch - '0');
      ch = getchar();
    }
  }
  x = x * fh;
}
template <typename T> void chmax(T &x, T y) { x = x < y ? y : x; }
template <typename T> void chmin(T &x, T y) { x = x > y ? y : x; }
} // namespace Base
using namespace Base;

const int N = 100100, M = 100100;
vector<pair<int, int>> e[N];
bool use[N];
int frm[N], n, m, k, p[11];
ll mask[M];
ll randll() {
  return ((ll)rand() << 48ll) + ((ll)rand() << 32ll) + ((ll)rand() << 16ll) +
         (ll)rand();
}

void ModifyMask(int x) {
  use[x] = true;
  for (unsigned i = 0; i < e[x].size(); i++)
    if (!use[e[x][i].first]) {
      frm[e[x][i].first] = e[x][i].second;
      ModifyMask(e[x][i].first);
    }

  ll sum = 0;
  for (unsigned i = 0; i < e[x].size(); i++)
    if (e[x][i].second != frm[x])
      sum ^= mask[e[x][i].second];
  if (frm[x] != 0)
    mask[frm[x]] = sum;
}
int main() {
  freopen("disconnected.in", "r", stdin);
  freopen("disconnected.out", "w", stdout);

  read(n);
  read(m);
  for (int i = 1; i <= m; i++) {
    int u, v;
    read(u);
    read(v);
    e[u].push_back(mr(v, i));
    e[v].push_back(mr(u, i));
  }

  for (int i = 1; i <= m; i++)
    mask[i] = randll();
  ModifyMask(1);

  read(k);
  for (int i = 1; i <= k; i++) {
    int num;
    read(num);
    bool flag = false;
    for (int j = 0; j < num; j++)
      read(p[j]);
    for (int j = 1; j < (1 << num); j++) {
      ll sum = 0;
      for (int t = 0; t < num; t++)
        if (((1 << t) & j) != 0)
          sum ^= mask[p[t]];
      if (sum == 0)
        flag = true;
    }
    if (!flag)
      puts("Connected");
    else
      puts("Disconnected");
  }
  return 0;
}
