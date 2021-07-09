/***************************************************************
	File name: LibreOJ_3343.cpp
	Author: ljfcnyali
	Create time: 2021年01月09日 星期六 16时25分29秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson(i, j) Tree[i].son[0][j]
#define rson(i, j) Tree[i].son[1][j]
#define size(i, j) Tree[i].size[j]
typedef long long LL;

const int maxn = 1e5 + 10;

int m;
struct TREE { int n; vector<int> son[2], size; } Tree[maxn];
bool flag;
vector<pii> p;

inline bool Solve(vector<pii> a)
{
    if ( a.empty() ) return false;
    // for ( auto it : a ) cout << "(" << it.first << " " << it.second << ")" << endl; puts("");
    vector<pii> A, B, C, D;
    for ( auto it : a ) 
    {
        int x = it.first, u = it.second;
        if ( size(x, u) == 1 ) return true;
        if ( lson(x, u) && !rson(x, u) ) A.push_back(pii(x, lson(x, u)));
        if ( !lson(x, u) && rson(x, u) ) B.push_back(pii(x, rson(x, u)));
        if ( rson(x, u) && size(x, lson(x, u)) == 1 ) C.push_back(pii(x, rson(x, u)));
        if ( lson(x, u) && size(x, rson(x, u)) == 1 ) D.push_back(pii(x, lson(x, u)));
    }
    return Solve(A) & Solve(B) & Solve(C) & Solve(D);
}

inline void DFS(int x, int u)
{
    size(x, u) = 1;    
    if ( lson(x, u) ) { DFS(x, lson(x, u)); size(x, u) += size(x, lson(x, u)); }
    if ( rson(x, u) ) { DFS(x, rson(x, u)); size(x, u) += size(x, rson(x, u)); }
    if ( min(size(x, lson(x, u)), size(x, rson(x, u))) > 1 ) flag = true;
}

int main()
{
    freopen("surreal.in", "r", stdin);
    freopen("surreal.out", "w", stdout);
    int T; scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d", &m); p.clear(); 
        REP(i, 1, m)
        {
            scanf("%d", &Tree[i].n); int n = Tree[i].n;
            Tree[i].son[0].resize(n + 1); Tree[i].son[1].resize(n + 1); Tree[i].size.resize(n + 1);
            REP(j, 1, n) scanf("%d%d", &lson(i, j), &rson(i, j));
            flag = false; DFS(i, 1);
            if ( !flag ) p.push_back(pii(i, 1));
        }
        if ( Solve(p) ) puts("Almost Complete");
        else puts("No");
    }
    return 0;
}
