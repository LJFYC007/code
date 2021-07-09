#include <bits/stdc++.h>

using std::pair;
using std::vector;
using std::string;

typedef long long ll;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb(a) push_back(a)
#define mp(a, b) std::make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)

template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;

string procStatus() {
    std::ifstream t("/proc/self/status");
    return string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}

template <typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = 1000000;

int n, C;
int h[N + 5];
ll s[2][N + 5], dp[N + 5];

ll solve(int x, int y, int mx) {
    ll a = y - x - 1;
    ll b = -2 * (s[0][y-1] - s[0][x]) - (x != 0) * C - (y != n+1) * C;
    ll c = s[1][y-1] - s[1][x] + 1ll * (x != 0) * h[x] * C + 1ll * (y != n+1) * h[y] * C;

    ll t;
    t = (ll) std::round(-1. * b / 2 / a);

    chkmax<ll>(t, mx);
    if(x != 0) chkmin(t, (ll) h[x]);
    if(y <= n) chkmin(t, (ll) h[y]);

    return a * t * t + b * t + c;
}

int main() {
    freopen("construct.in", "r", stdin);
    freopen("construct.out", "w", stdout);

    read(n), read(C);
    for(int i = 1; i <= n; ++i) {
        read(h[i]);
        s[0][i] = s[0][i-1] + h[i];
        s[1][i] = s[1][i-1] + 1ll * h[i] * h[i];
    }

    static int stk[N + 5], top;

    h[0] = h[n + 1] = oo;
    stk[top ++] = 0;

    for(int i = 1; i <= n+1; ++i) {
        dp[i] = dp[i-1] + ((i == 1 || i == n+1) ? 0 : 1ll * C * std::abs(h[i] - h[i-1]));
        while(top > 0 && h[stk[top-1]] <= h[i]) {
            if(top > 1) 
                chkmin(dp[i], dp[stk[top-2]] + solve(stk[top-2], i, h[stk[top-1]]));
            -- top;
        }
        stk[top ++] = i;
    }
    printf("%lld\n", dp[n+1]);

    return 0;
}
