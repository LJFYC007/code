#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 50010;
const int Mod = 998244353;

int T, n, m, tot, Next[maxn];
LL dp[510][maxn];
char s[510];

struct node
{
    int next[2], val;
} Tree[maxn];

inline void INIT()
{
    REP(i, 0, tot + 1) Tree[i].next[0] = Tree[i].next[1] = Tree[i].val = 0;
    //mem(dp); mem(Tree);
    REP(i, 0, tot + 1) REP(j, 0, 200) dp[j][i] = 0;
    tot = 0; mem(Next);
}

inline void Insert()
{
    int p = 0;
    REP(i, 0, n - 1)
    {
        int c = s[i] - '0';
        if ( !Tree[p].next[c] ) Tree[p].next[c] = ++ tot;
        p = Tree[p].next[c];
    }
    ++ Tree[p].val;
}

inline void BFS()
{
    queue<int> Q;
    REP(i, 0, 1) if ( Tree[0].next[i] ) Q.push(Tree[0].next[i]);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        REP(i, 0, 1)
            if ( !Tree[u].next[i] ) Tree[u].next[i] = Tree[Next[u]].next[i];
            else
            {
                Q.push(Tree[u].next[i]);
                Next[Tree[u].next[i]] = Tree[Next[u]].next[i];
            }
    }
}

inline LL power(LL a, LL b)
{
    LL r = 1;
    while ( b )
    {
        if ( b & 1 ) r = (r * a) % Mod;
        a = (a * a) % Mod;
        b >>= 1;
    }
    //cerr << r << endl;
    return r;
}

int main()
{
    scanf("%d", &T);
    while ( T -- ) 
    {
        INIT();
        scanf("%d%d", &n, &m);
        scanf("%s", s); Insert();
        REP(i, 0, n - 1)
        {
            if ( s[i] == '0' ) { s[i] = '1'; Insert(); s[i] = '0'; }
            else { s[i] = '0'; Insert(); s[i] = '1'; }
        }
        BFS();
        dp[0][0] = 1;
        REP(i, 0, m - 1)
            REP(j, 0, tot - 1)
            {
                if ( !dp[i][j] ) continue ;
                REP(k, 0, 1)
                {
                    int u = Tree[j].next[k];
                    if ( Tree[u].val ) continue ;
                    dp[i + 1][u] = (dp[i][j] + dp[i + 1][u]) % Mod;
                }
            }
        LL sum = 0;
        REP(i, 0, tot - 1) sum = (sum + dp[m][i]) % Mod;
        LL ans = power(2, m) - sum;
        ans = ((ans % Mod) + Mod) % Mod;
        printf("%lld\n", ans);
//        cerr << tot << endl;
//        printf("%d\n", tot);
    }
    return 0;
}
