#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;

const int maxn = 100005;
const int maxd = 19;
int root = 0, n, m, top = 0;
int tot = 0, V[maxn << 1], N[maxn << 1], C[maxn << 1], F[maxn];
int dp[maxn][2], fa[maxn][maxd], son[maxn], down[maxn], up[maxn], tofa[maxn], sum[maxn], num[maxn];
pair<int, int> len[maxn];

void add(int a, int b, int c)  {
    ++ tot, V[tot] = b, C[tot] = c, N[tot] = F[a], F[a] = tot;
}

void update(int x, int v)  {
    if (v > dp[x][0])  dp[x][1] = dp[x][0], dp[x][0] = v;
    else if (v > dp[x][1])  dp[x][1] = v;
}

void dp1(int x, int f)  {
    dp[x][0] = dp[x][1] = 0;
    for (int p = F[x]; p > 0; p = N[p])
        if (V[p] != f)  {
            dp1(V[p], x);
            update(x, dp[V[p]][0] + C[p]);
        }
}

void dp2(int x, int f, int tf)  {
    if (f != 0)  {
        if (dp[x][0] + tf == dp[f][0])  update(x, tf + dp[f][1]);
        else update(x, tf + dp[f][0]);
    }
    for (int p = F[x]; p > 0; p = N[p])
        if (V[p] != f)  dp2(V[p], x, C[p]);
}

void dfs(int x, int f)  {
    fa[x][0] = f;
    for (int d = 1; d < maxd; d ++)
        fa[x][d] = fa[ fa[x][d - 1] ][d - 1];
    down[x] = son[x] = 0;
    for (int p = F[x]; p > 0; p = N[p])
        if (V[p] != f) {
            up[V[p]] = up[x] + C[p];
            tofa[V[p]] = C[p];
            dfs(V[p], x);
            if (C[p] + down[V[p]] > down[x])  {
                down[x] = down[V[p]] + C[p];
                son[x] = V[p];
            }
        }
}

void precalc(int x, int f, int ext)  {
    if (son[x] == 0)  {
        len[++ top] = make_pair(-ext, x);
        return;
    }
    precalc(son[x], x, ext + tofa[son[x]]);
    for (int p = F[x]; p > 0; p = N[p])  
        if (V[p] != f && V[p] != son[x])  {
            precalc(V[p], x, C[p]);
        }
}

int main()  {

    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; i ++)  {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }

    //find root
    dp1(1, 0);
    dp2(1, 0, 0); //furthest[x] = dp[x][0]
    root = 0;
    for (int i = 1; i <= n; i ++)
        if (root == 0 || dp[i][0] < dp[root][0])  root = i;

    //precalc
    up[0] = 0;
    tofa[root] = up[root] = 0;
    dfs(root, 0);
    top = 0;
    precalc(root, 0, 0);
    sort(len + 1, len + 1 + top); //(-len, leaf #)
    memset(num, 0, sizeof num);
    sum[0] = 0, num[root] = 1;
    for (int i = 1; i <= top; i ++)  {
        sum[i] = sum[i - 1] - len[i].first;
        int x = len[i].second;
        while (num[x] == 0)  {
            num[x] = i;
            x = fa[x][0];
        }
    }

    //solve
    int ans = 0;
    dp1(root, 0);
    for (int i = 1; i <= m; i ++)  {
        int x, y;
        scanf("%d%d", &x, &y);
        x = (x + ans - 1) % n + 1;
        y = (y + ans - 1) % n + 1;
        if (num[x] <= 2 * y)  {
            ans = sum[min(2 * y, top)];
        }else  { //substitution
            int anc = x;
            for (int d = maxd - 1; d >= 0; d --)
                if (fa[anc][d] != 0 && num[fa[anc][d]] > 2 * y)  anc = fa[anc][d];
            anc = fa[anc][0];
            ans = sum[min(2 * y, top)] + dp[x][0] + up[x] - up[anc];
            ans -= min(-len[2 * y].first, dp[anc][0]); 
        }
        printf("%d\n", ans);
    }
    return 0;
}
