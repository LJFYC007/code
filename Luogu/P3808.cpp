/***************************************************************
	File name: P3808.cpp
	Author: ljfcnyali
	Create time: 2020年06月19日 星期五 16时23分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, Next[maxn], tot;
char s[maxn];
struct node { int Next[26], val; } Trie[maxn];

inline void Insert(int x)
{
    int n = str(s + 1), p = 0;
    REP(i, 1, n)
    {
        int c = s[i] - 'a';
        if ( !Trie[p].Next[c] ) Trie[p].Next[c] = ++ tot;
        p = Trie[p].Next[c];
    }
    ++ Trie[p].val;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%s", s + 1); Insert(i); }
    queue<int> Q; REP(i, 0, 25) if ( Trie[0].Next[i] ) Q.push(Trie[0].Next[i]);
    while ( !Q.empty() ) 
    {
        int u = Q.front(); Q.pop();
        REP(i, 0, 25)
        {
            if ( !Trie[u].Next[i] ) { Trie[u].Next[i] = Trie[Next[u]].Next[i]; continue ; }
            Next[Trie[u].Next[i]] = Trie[Next[u]].Next[i];
            Q.push(Trie[u].Next[i]);
        }
    }
    scanf("%s", s + 1); n = str(s + 1);
    int ans = 0, p = 0;
    REP(i, 1, n)
    {
        int c = s[i] - 'a';
        p = Trie[p].Next[c];
        ans += Trie[p].val; Trie[p].val = 0;
    }
    printf("%d\n", ans);
    return 0;
}
