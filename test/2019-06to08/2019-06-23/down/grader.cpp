#include "tree.h"
#include <bits/stdc++.h>
using namespace std;

namespace __inter_lib {

    const int N = 100000;

    int fa[N + 5];
    vector<int> G[N + 5];
    int n, type, limit, rt;

    bool can[N + 5];
    int sub_time, qry_time;
    int dfn[N + 5], efn[N + 5], dfc;

    int query(int x, int y) {
        if (++ qry_time > limit) {
            puts("Query limit exceeded");
            fprintf(stderr, "Error, Query Times Out of Limit!\n");
            exit(0);
        }
        if (dfn[x] <= dfn[y] && dfn[y] <= efn[x]) return 1;
        if (dfn[y] <= dfn[x] && dfn[x] <= efn[y]) return -1;
        return 0;
    }

    void submit(int x) {
        if (!can[x]) {
            puts("Invalid Answer");
            fprintf(stderr, "Wrong Answer.\n");
            exit(0);
        }

        for (auto y : G[x]) {
            can[y] = true;
        }
        
        ++ sub_time;
    }

    void dfs(int x) {
        dfn[x] = ++ dfc;
        for(auto y : G[x]) {
            dfs(y);
        }
        efn[x] = dfc;
    }

    void main() {
        scanf("%d%d%d", &n, &type, &limit);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", fa + i);
            G[fa[i]].push_back(i);

            if (!fa[i]) {
                rt = i;
            }
        }

        dfs(rt);
        can[rt] = true;

        solve(n, type);

        if (sub_time != n) {
            puts("Invalid Answer");
            fprintf(stderr, "Wrong Answer.\n");
        } else {
            puts("Correct");
            fprintf(stderr, "Correct Answer, Query Times = %d\n", qry_time);
        }
    }
}

int query(int x, int y) {
    return __inter_lib::query(x, y);
}

void submit(int x) {
    return __inter_lib::submit(x);
}

int main() {

    __inter_lib::main();

    return 0;
}
