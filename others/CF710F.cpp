/***************************************************************
	File name: CF710F.cpp
	Author: ljfcnyali
	Create time: 2019年09月26日 星期四 14时42分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 300010;

int n;
char s[maxn];
struct AC
{
    struct node
    {
        int next[26], Next[26];
        LL val, num;
    } *Trie[20];
    int Next[20][maxn * 2], top, size[20], tot[20], Max;

    inline void INIT(int x, int y)
    {
        REP(i, 0, 25) Trie[x][y].Next[i] = 0;
        Trie[x][y].val = 0;
    }

    inline void Merge(int a, int b, int p, int q)
    {
        Trie[a][p].val += Trie[b][q].val;
        REP(i, 0, 25)
        {
            if ( !Trie[b][q].Next[i] ) continue ;
            if ( !Trie[a][p].Next[i] ) { Trie[a][p].Next[i] = ++ tot[a]; INIT(a, tot[a]); }
            Merge(a, b, Trie[a][p].Next[i], Trie[b][q].Next[i]);
        }
    }

    inline void Get(int a, int p)
    {
        REP(i, 0, 25) Trie[a][p].next[i] = Trie[a][p].Next[i];
        REP(i, 0, 25) if ( Trie[a][p].next[i] ) Get(a, Trie[a][p].next[i]);
    }

    inline void BFS(int x)
    {
        queue<int> Q; Q.push(1);
        while ( !Q.empty() ) 
        {
            int u = Q.front(); Q.pop();
            REP(i, 0, 25)
            {
                if ( !Trie[x][u].next[i] ) { Trie[x][u].next[i] = Trie[x][Next[x][u]].next[i]; continue ; }
                Q.push(Trie[x][u].next[i]);
                Next[x][Trie[x][u].next[i]] = Trie[x][Next[x][u]].next[i];
            }
            Trie[x][u].num = Trie[x][u].val + Trie[x][Next[x][u]].num;
        }
    }

    inline void Insert()
    {
        ++ top; Max = top;
        int x = 10000;
        if ( top <= 1 ) x = 300000;
        else if ( top <= 3 ) x = 100000;
        else if ( top <= 5 ) x = 50000;
        else if ( top <= 10 ) x = 20000;
        Trie[top] = (new node[x + 100]);
        size[top] = tot[top] = 1;
        REP(i, 0, 25) Trie[top][0].Next[i] = 1;
        int len = str(s + 1), p = 1; 
        REP(i, 1, len)
        {
            INIT(top, p);
            int c = s[i] - 'a';
            Trie[top][p].Next[c] = ++ tot[top];
            p = Trie[top][p].Next[c];
        }
        INIT(top, p);
        Trie[top][p].val = 1;
        while ( size[top] == size[top - 1] ) 
        {
            -- top;
            size[top] += size[top + 1];
            Merge(top, top + 1, 1, 1); 
        }
        REP(i, top + 1, Max) delete [] Trie[i];
        REP(i, 0, 25) Trie[top][0].next[i] = 1;
        Get(top, 1);
        BFS(top);
    }

    inline LL Solve(int x)
    {
        int len = str(s + 1), u = 1; LL ans = 0;
        REP(i, 1, len)
        {
            int c = s[i] - 'a';
            u = Trie[x][u].next[c];
            ans += Trie[x][u].num; 
        }
        return ans;
    }

    inline LL Query()
    {
        LL ans = 0;
        REP(i, 1, top) ans += Solve(i);
        return ans;
    }
} A, B;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n)
    {
        int opt; scanf("%d %s", &opt, s + 1);
        if ( opt == 1 ) A.Insert();
        else if ( opt == 2 ) B.Insert();
        else { printf("%lld\n", A.Query() - B.Query()); fflush(stdout); }
    }
    return 0;
}
