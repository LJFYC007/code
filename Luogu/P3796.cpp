/***************************************************************
	File name: P3796.cpp
	Author: ljfcnyali
	Create time: 2019年08月02日 星期五 20时34分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 100010;

char S[210][210], T[maxn * 10];
int n, Next[maxn * 3], ans, cnt, sum[maxn];
vector<int> a;

struct node
{
    int next[26];
    vector<int> a;
} Tree[maxn * 3];

inline void INIT(int cnt)
{
    REP(i, 0, 25) Tree[cnt].next[i] = 0;
    Tree[cnt].a.clear();
}

inline void Insert(int x)
{
    int p = 1;
    REP(i, 0, str(S[x]) - 1)
    {
        int c = S[x][i] - 'a';
        if ( !Tree[p].next[c] ) { INIT(++ cnt); Tree[p].next[c] = cnt; }
        p = Tree[p].next[c];
    }
    Tree[p].a.push_back(x);
}

inline void BFS()
{
    queue<int> Q; Q.push(1);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        // cerr << u << endl;
        REP(i, 0, 25)
        {
            if ( !Tree[u].next[i] ) { Tree[u].next[i] = Tree[Next[u]].next[i]; continue ; }
            Next[Tree[u].next[i]] = Tree[Next[u]].next[i];
            Q.push(Tree[u].next[i]);
        }
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    while ( ~scanf("%d", &n) )
    {
        if ( !n ) break ; 
        REP(i, 0, 25) Tree[0].next[i] = 1;
        INIT(1); mem(Next); mem(sum); ans = 0; cnt = 1;
        REP(i, 1, n) { scanf("%s", S[i]); Insert(i); }
        BFS();
        scanf("%s", T);
        int u = 1;
        REP(i, 0, str(T) - 1)
        {
            int c = T[i] - 'a';
            int v = Tree[u].next[c];
            while ( v > 1 )
            {
                REP(j, 0, Tree[v].a.size() - 1) ++ sum[Tree[v].a[j]];
                v = Next[v];
            }
            u = Tree[u].next[c];
        }
        REP(i, 1, n) if ( sum[i] > ans ) ans = sum[i];
        printf("%d\n", ans);
        REP(i, 1, n) if ( sum[i] == ans ) printf("%s\n", S[i]);
    }
    return 0;
}
