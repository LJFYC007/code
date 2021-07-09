#include <cassert>
#include <iostream>

using namespace std;

const int MAX = 50;
const int MANY = 1 << 25;

int M[MAX][MAX];
int Adj1[MAX], Adj2[MAX], Adj12[MAX];
char dp1[MANY];
int dp2[MANY];

int main() {
  freopen("cows.in", "r", stdin);
  freopen("cows.out", "w", stdout);
  int n;
  cin >> n;
  int n1 = n / 2;
  int n2 = (n + 1) / 2;
  assert(1 <= n && n <= MAX);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      char c;
      cin >> c;
      M[i][j] = c - '0';
      if (i > j)
        assert(M[i][j] == M[j][i]);
      if (M[i][j] == 0)
        continue;
      if (i < n1 && j < n1)
        Adj1[i] |= 1 << j;
      if (i < n1 && j >= n1)
        Adj12[i] |= 1 << (j - n1);
      if (i >= n1 && j >= n1)
        Adj2[i] |= 1 << (j - n1);
    }
  }
  dp1[0] = 1;
  for (int i = 1; i < (1 << n1); i++) {
    for (int j = 0; j < n1; j++) {
      if (i & (1 << j)) {
        if ((dp1[i ^ (1 << j)] == 1) && (((Adj1[j] | (1 << j)) & i) == i)) {
          dp1[i] = 1;
        }
        break;
      }
    }
    // printf("%d", dp1[i]);
  }
  // printf("\n");
  dp2[0] = 1;
  for (int i = 1; i < (1 << n2); i++) {
    for (int j = n1; j < n; j++) {
      if (i & (1 << (j - n1))) {
        dp2[i] = dp2[i ^ (1 << (j - n1))];
        dp2[i] += dp2[i & Adj2[j]];
        break;
      }
    }
    // printf("%d %d\n", i, dp2[i]);
  }
  long long ans = 0;
  for (int i = 0; i < (1 << n1); i++) {
    if (!dp1[i])
      continue;
    int x = (1 << n2) - 1;
    for (int j = 0; j < n1; j++) {
      if (i & (1 << j))
        x &= Adj12[j];
    }
    ans += dp2[x];
  }
  cout << ans;
  return 0;
}
