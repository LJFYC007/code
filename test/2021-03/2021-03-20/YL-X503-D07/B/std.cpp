
/**************************************************************
    Problem: 3976
    User: 2019gz52
    Language: C++
    Result: Accepted
    Time:991 ms
    Memory:9908 kb
****************************************************************/
 
 
#include<bits/stdc++.h>
#define cs const
#define pb push_back
using namespace std;
typedef vector<int> vi; 
cs int Mod = 998244353;
int add(int a, int b) {
    return a + b >= Mod ? a + b - Mod : a + b;
}
void Add(int &a, int b) {
    a = add(a, b);
}
cs int N = 205;
cs int M = 1 << 20 | 5;
 
int n, m, A, B;
bool a[N], b[N];
vi c[N];
void Set(int &s, int p, int c) {
    if((s >> p & 1) ^ c) 
        s ^= 1 << p; 
}
int work(int n) {
    int sz = 0;
    for(int i = 0; i < n; i++) 
        sz = max(sz, (int)c[i].size());
    int u = 1 << (sz + 1); 
    c[n] = c[0];
    int ans = 0; 
    for(int S0 = 0; S0 < u / 2; S0++) {
        static int dp[2][1 << 11 | 5];
        memset(dp, 0, sizeof dp);
        int now = 0, nxt = 1; 
        dp[now][S0 << 1] = 1; 
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < c[i].size(); j++) {
                memset(dp[nxt], 0, u << 2);
                for(int s = 0, w, t; s < u; s++) 
                if(w = dp[now][s]) {
                    int x = c[i][j];
//                  cout <<i << ' ' << j << ' ' << x << ' ' << a[x] << ' ' << b[x] << endl;
                    t = s, Set(t, j, 0);
                    Add(dp[nxt][t], w);
                    if(b[x] && j && !(s >> (j - 1) & 1)){
                        t = s, Set(t, j, 1), Set(t, j - 1, 1);
                        Add(dp[nxt][t], w);
                    }
                    if(a[x]) {
                        if(j && !(s >> j & 1) && c[i - 1][j - 1] == x - A){
                            t = s, Set(t, j, 1);
                            Add(dp[nxt][t], w);
                        } if(j < c[i - 1].size() && 
                        !(s >> (j + 1) & 1) && c[i - 1][j] == x - A){
                            t = s, Set(t, j, 1), Set(t, j + 1, 1);
                            Add(dp[nxt][t], w);
                        } if(j + 1 < c[i - 1].size() && 
                        !(s >> (j + 2) & 1) && c[i - 1][j + 1] == x - A){
                            t = s, Set(t, j + 2, 1), Set(t, j, 1);
                            Add(dp[nxt][t], w);
                        }
                    }
                } swap(now, nxt);
//              cout << i << ' ' << j << endl;
//              for(int s = 0; s < u; s++)
//                  cout << dp[now][s] << ' '; cout << endl;
            }
            memset(dp[nxt], 0, u << 2);
            for(int s = 0; s < u; s++)
                Add(dp[nxt][(s << 1) & (u - 1)], dp[now][s]);
            swap(now, nxt);
        }
        Add(ans, dp[now][S0 << 1]);
//      cout << "______________________________ " << S0 << ' ' << dp[now][S0 << 1] << endl;
    } return ans;
}
 
int main() {
    freopen("B.in", "r", stdin);
    freopen("B1.out", "w", stdout);
    cin >> n >> m >> A >> B; 
    for(int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        --u, --v;
        if(v - u == A) a[v] = 1; 
        if(v - u == B) b[v] = 1; 
    } 
    if(B <= 20) {
        static int dp[2][M];
        int now = 0, nxt = 1; 
        int u = 1 << B; 
        dp[now][0] = 1; 
        for(int i = 0; i < n; i++) {
            memset(dp[nxt], 0, u << 2);
            for(int s = 0, c; s < u; s++)
            if(c = dp[now][s]) {
                int t = s << 1;
                Add(dp[nxt][t & (u - 1)], c); t |= 1; 
                if(a[i] && !(t >> A & 1)) 
                    Add(dp[nxt][(t ^ (1 << A)) & (u - 1)], c);
                if(b[i] && !(t >> B & 1))
                    Add(dp[nxt][(t ^ (1 << B)) & (u - 1)], c);
            } swap(now, nxt);
        } 
        int ans = 0; 
        for(int i = 0; i < u; i++)
            Add(ans, dp[now][i]);
        cout << ans << '\n';
        return 0; 
    }
    static bool ex[N];
    int ans = 1; 
    for(int i = 0; i < B; i++) if(!ex[i]){
        int x = i, m = 0;
        while(1) {
            ex[x] = 1; 
            for(int i = x; i < n; i += B)
            c[m].pb(i); 
            ++ m, x = (x + A) % B;
            if(x == i) break;
        }
        ans = 1ll * ans * work(m) % Mod;
        for(int j = 0; j < m; j++) c[j].clear();
    } cout << ans << '\n';
    return 0; 
}
