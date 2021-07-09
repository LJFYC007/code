/***************************************************************
	File name: P2444.cpp
	Author: ljfcnyali
	Create time: 2019年08月02日 星期五 21时14分55秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 8010;

char s[30010];
int n, Next[maxn], cnt;
struct node
{
    int next[2], val;
} Trie[maxn * maxn];
bool vis[maxn], use[maxn];

inline void Insert()
{
    int u = 1;
    REP(i, 0, str(s) - 1)
    {
        int c = s[i] - '0';
        if ( !Trie[u].next[c] ) Trie[u].next[c] = ++ cnt;
        u = Trie[u].next[c];
    }
    Trie[u].val = 1; 
}

inline void BFS()
{
    queue<int> Q; Q.push(1);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        REP(i, 0, 1) 
        {
            if ( !Trie[u].next[i] ) { Trie[u].next[i] = Trie[Next[u]].next[i]; continue ; }
            Next[Trie[u].next[i]] = Trie[Next[u]].next[i];
            Trie[u].val |= Trie[Next[u]].val;
            Q.push(Trie[u].next[i]);
        }
    }
}

inline void DFS(int u)
{
    if ( use[u] ) { puts("TAK\n"); exit(0); } 
    if ( vis[u] || Trie[u].val ) return ;
    vis[u] = use[u] = true;
    REP(i, 0, 1) DFS(Trie[u].next[i]);
    use[u] = false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cnt = 1; REP(i, 0, 1) Trie[0].next[i] = 1;
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%s", s); Insert(); }
    BFS();
    vis[0] = use[0] = true;
    DFS(1);
    printf("NIE\n");
    return 0;
}
