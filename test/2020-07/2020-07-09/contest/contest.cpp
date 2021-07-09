/***************************************************************
	File name: contest.cpp
	Author: ljfcnyali
	Create time: 2020年07月09日 星期四 15时51分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;
const int maxm = 1e6 + 1e5;

int n, m, A[maxn], B[maxn], a[maxn], k, b[maxn], ans[maxn], ret;
bool vis[32];
struct node { int op, x, y, k, b[6]; } Q[maxn];
struct Node
{
    int pos, val, x; 
    Node(int a = 0, int b = 0, int c = 0) { pos = a; val = b; x = c; }
    bool operator < (const Node &a) const { return pos > a.pos; }
} ;
vector<int> p[maxm];
set<int> Set;

inline int Find(int x, int pos) 
{ 
    auto it = Set.upper_bound(pos);
    while ( it != Set.end() ) 
    {
        auto i = upper_bound(p[x].begin(), p[x].end(), pos);
        int position = i == p[x].end() ? n + 1 : *i;
        if ( position < *it ) return position;
        pos = *it; if ( x == a[pos] ) return pos;
        x ^= B[pos] ^ A[pos]; ++ it;
    }
    auto i = upper_bound(p[x].begin(), p[x].end(), pos);
    return i == p[x].end() ? n + 1 : *i;
}

inline bool Solve()
{
    priority_queue<Node> Q; mem(vis);
    REP(i, 1, k)
    { 
        int pos = Find(b[i], 0);
        if ( pos != n + 1 ) Q.push(Node(pos, b[i], 1 << i - 1));
    }
    while ( !Q.empty() ) 
    {
        Node u = Q.top(); Q.pop();
        if ( u.val == ret || ret == 0 ) return true;
        if ( vis[u.x] ) continue ; vis[u.x] = true;
        REP(i, 1, k)
        {
            if ( (u.x >> i - 1) & 1 ) continue ;
            int pos = Find(a[u.pos] ^ b[i], u.pos);
            if ( pos != n + 1 ) Q.push(Node(pos, u.val ^ b[i], u.x | (1 << i - 1)));
        }
    }
    return false;
}

inline void ReBuild()
{
    REP(i, 1, n) if ( p[a[i]].size() ) p[a[i]].clear(); 
    REP(i, 1, n) { a[i] = a[i - 1] ^ A[i]; B[i] = A[i]; p[a[i]].emplace_back(i); }
    ret = a[n]; Set.clear();        
}

int main()
{
    freopen("contest.in", "r", stdin);
    freopen("contest.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &A[i]);
    REP(i, 1, m) 
    {
        scanf("%d", &Q[i].op);
        if ( Q[i].op == 1 ) scanf("%d%d", &Q[i].x, &Q[i].y);
        else
        {
            scanf("%d", &Q[i].k);
            REP(j, 1, Q[i].k) scanf("%d", &Q[i].b[j]);
        }
    }

    int block = 800;
    for ( int l = 1, r = min(m, block); l <= m; l += block, r = min(m, r + block) )
    {
        ReBuild();

        REP(i, l, r) if ( Q[i].op == 1 ) 
        {
            ret ^= B[Q[i].x] ^ Q[i].y;
            B[Q[i].x] = Q[i].y;
            Set.insert(Q[i].x);
        }
        else 
        {
            k = Q[i].k; REP(j, 1, k) b[j] = Q[i].b[j];
            printf("%s\n", Solve() ? "yes" : "no");
        }
        REP(i, l, r) if ( Q[i].op == 1 ) A[Q[i].x] = Q[i].y;
    }
    return 0;
}
