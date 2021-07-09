/***************************************************************
	File name: P4735.cpp
	Author: ljfcnyali
	Create time: 2019年07月31日 星期三 09时50分45秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 50000010;

struct node
{
    int next[2], sum;
} Tree[maxn];

int n, a[maxn], m, Root[maxn], p[110], cnt;

inline void Insert(int root, int last, int val)
{
    for ( int i = 30; i >= 0; -- i ) 
    {
        Tree[root].sum = Tree[last].sum + 1;
        if ( val >= p[i] )
        {
            val -= p[i];
            if ( !Tree[root].next[1] ) Tree[root].next[1] = ++ cnt;
            Tree[root].next[0] = Tree[last].next[0];
            root = Tree[root].next[1];
            last = Tree[last].next[1];
        }
        else
        {
            if ( !Tree[root].next[0] ) Tree[root].next[0] = ++ cnt;
            Tree[root].next[1] = Tree[last].next[1];
            root = Tree[root].next[0];
            last = Tree[last].next[0];
        }
    }
    Tree[root].sum = Tree[last].sum + 1;
}

inline int Query(int p, int q, int val)
{
    int sum = 0;
    for ( int i = 30; i >= 0; -- i ) 
    {
        int c = (val & (1 << i)) ? 1 : 0; 
        if ( Tree[q].next[!c] > Tree[p].next[!c] ) { sum += 1 << i; p = Tree[p].next[!c]; q = Tree[q].next[!c]; }
        else { p = Tree[p].next[c]; q = Tree[q].next[c]; }
    }
    return sum;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) { scanf("%d", &a[i]); if ( i > 1 ) a[i] ^= a[i - 1]; }
    p[0] = 1; REP(i, 1, 30) p[i] = p[i - 1] * 2;
    REP(i, 1, n) Insert(Root[i] = ++ cnt, Root[i - 1], a[i]);
    REP(i, 1, m)
    {
        char s[10]; scanf("%s", s);
        if ( s[0] == 'A' ) { scanf("%d", &a[++ n]); a[n] ^= a[n - 1]; Insert(Root[n] = ++ cnt, Root[n - 1], a[n]); }
        else
        {
            int l, r, p; scanf("%d%d%d", &l, &r, &p);
            -- l; -- r;
            if ( l == r && !l ) { printf("%d\n", a[n] ^ p); continue ; } 
            printf("%d\n", Query(Root[max(l - 1, 0)], Root[r], a[n] ^ p));
        }
    }
    return 0;
}
