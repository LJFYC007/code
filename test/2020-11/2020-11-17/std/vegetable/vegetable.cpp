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

const int K = 40;
const int N = 200;
const int Q = 100000;

int n, m, q;

struct BIT {
#define lowbit(x) (x & -x)
    int c[N + 5][N + 5][N + 5]; 

    void add(int x, int y, int z) {
        for(int i = x; i <= m; i += lowbit(i))
            for(int j = y; j <= n; j += lowbit(j))
                for(int k = z; k <= m; k += lowbit(k)) ++ c[i][j][k];
    }

    int query(int x, int y, int z) {
        int res = 0;
        for(int i = x; i > 0; i -= lowbit(i))
            for(int j = y; j > 0; j -= lowbit(j))
                for(int k = z; k > 0; k -= lowbit(k)) res += c[i][j][k];
        return res;
    }
} bit;

struct query {
    int x1, y1, x2, y2, id;

    void input(int _id) {
        id = _id;
        read(x1), read(y1);
        read(x2), read(y2);
    }

    bool operator < (const query& rhs) const {
        return x1 > rhs.x1;
    }
};

vector <int> d;
vector <query> mod;
vector <pii> p[Q + 5];

query que[Q + 5];
int ans[Q + 5], cnt[N*N + 5];
int a[N + 5][N + 5], b[N + 5][N + 5];

inline int pw2(int x) { return x * x; }

void calc(int col) {
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) b[i][j] = b[i][j-1] + (a[i][j] == col);
        for(int j = 1; j <= m; ++j) b[i][j] = b[i][j] + b[i-1][j];
    }
    for(int i = 1; i <= q; ++i) {
        int x1 = que[i].x1, y1 = que[i].y1;
        int x2 = que[i].x2, y2 = que[i].y2;

        ans[que[i].id] += pw2(b[x2][y2] - b[x1-1][y2] - b[x2][y1-1] + b[x1-1][y1-1]);
    }
}

void input() {
    read(n), read(m); read(q);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j) d.pb(read(a[i][j]));
    for(int i = 1; i <= q; ++i) que[i].input(i);
}

void solve() {
    std::sort(d.begin(), d.end());
    d.erase(std::unique(d.begin(), d.end()), d.end());

    for(int i = 1; i <= n; ++i) 
        for(int j = 1; j <= m; ++j) {
            a[i][j] = std::lower_bound(d.begin(), d.end(), a[i][j]) - d.begin();
            ++ cnt[a[i][j]];
            p[a[i][j]].pb(mp(i, j)); 
        }

    for(int i = 0; i < (int) d.size(); ++i) {
        if(cnt[i] >= K) {
            calc(i);
        } else {
            for(auto x : p[i])
                for(auto y : p[i]) {
                    query temp;
                    temp.x1 = x.fst, temp.y1 = x.snd;
                    temp.x2 = y.fst, temp.y2 = y.snd;
                    if(temp.x1 > temp.x2) std::swap(temp.x1, temp.x2);
                    if(temp.y1 > temp.y2) std::swap(temp.y1, temp.y2);

                    mod.pb(temp);
                }
        }
    }

    std::sort(que + 1, que + q + 1);
    std::sort(mod.begin(), mod.end());

    for(int i = 1, j = 0; i <= q; ++i) {
        while(j < (int) mod.size() && mod[j].x1 >= que[i].x1) {
            bit.add(m - mod[j].y1 + 1, mod[j].x2, mod[j].y2);
            ++ j;
        }
        ans[que[i].id] += bit.query(m - que[i].y1 + 1, que[i].x2, que[i].y2);
    }
    for(int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
}

int main() {
    freopen("vegetable.in", "r", stdin);
    freopen("vegetable.out", "w", stdout);

    input();
    solve();

    return 0;
}
