/***************************************************************
	File name: P5283.cpp
	Author: ljfcnyali
	Create time: 2019年08月18日 星期日 15时04分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 20000010;

struct node
{
    int next[2], size;
} Trie[maxn];

struct Node
{
    int val, pos, k;
    bool operator < (const Node &a) const { return val < a.val; }
} p1, p2;

int n, k, a[maxn], cnt = 1, ans;
priority_queue<Node> Q;

inline void Insert(int x)
{
    int p = 1; ++ Trie[p].size;
    for ( int i = 32; i >= 0; -- i )
    {
        int c = (x >> i) & 1;
        if ( !Trie[p].next[c] ) Trie[p].next[c] = ++ cnt;
        p = Trie[p].next[c];
        ++ Trie[p].size;
    }
}

inline int Query(int x, int k)
{
    int p = 1, sum = 0;
    for ( int i = 32; i >= 0; -- i )
    {
        int c = (x >> i) & 1;
        if ( Trie[p].next[!c] ) 
        {
            if ( k <= Trie[Trie[p].next[!c]].size ) c = !c;
            else k -= Trie[Trie[p].next[!c]].size;
        }
        p = Trie[p].next[c];
        if ( c == 1 ) sum += 1LL << i;
    }
    return sum ^ x;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    REP(i, 1, n) { scanf("%lld", &a[i]); a[i] ^= a[i - 1]; Insert(a[i]); }
    Insert(0); 
    REP(i, 0, n) Q.push((Node){Query(a[i], 1), i, 1});
    REP(i, 1, k * 2)
    {
        p1 = Q.top(); Q.pop(); ans += p1.val;
        if ( p1.k < n ) Q.push((Node){Query(a[p1.pos], p1.k + 1), p1.pos, p1.k + 1});
    }
    printf("%lld\n", ans / 2);
    return 0;
}
