/***************************************************************
  File name: travel.cpp
Author: ljfcnyali
Create time: 2020年12月26日 星期六 11时11分56秒
 ***************************************************************/
#include<bits/stdc++.h>
#include "travel.h"

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int sum, p[maxn], a[maxn], m;
pii size[maxn];
bool vis[maxn];

inline void Solve(int x, int l, int r)
{
    if ( l == r ) { vis[a[l]] = false; report(x, a[l]); return ; }
    int Mid = l + r >> 1;
    vector<int> t; REP(i, l, Mid) t.push_back(a[i]);
    if ( t.size() && check(1, x, t) != 2 ) Solve(x, l, Mid);
    else Solve(x, Mid + 1, r);
}

namespace Subtask1 
{
    inline void Solve(int root, vector<int> a, vector<int> leaf)
    {
        if ( a.size() == leaf.size() + 1 ) 
        {
            for ( auto it : leaf ) report(it, root);
            return ; 
        }
        mem(vis); for ( auto it : a ) vis[it] = true;
        for ( auto it : leaf ) vis[it] = false; vis[root] = false;
        vector<int> b; REP(i, 1, 1000) if ( vis[i] ) b.push_back(i);
        int pos = rand() % b.size(), x = b[pos];
        for ( auto it : leaf ) b.push_back(it);
        
        vector<int> a1, a2, leaf1, leaf2;
        while ( check(root, x, b) != 2 ) 
        {
            pos = Find(root, x, b);  
            a1.push_back(pos); if ( !vis[pos] ) leaf1.push_back(pos);
        }
    }

    inline void main(int n)
    {
        vector<int> a; REP(i, 1, n) a.push_back(i); 
        vector<int> leaf; REP(i, 2, n) if ( check(i, i, a) ) leaf.push_back(i);
        Solve(1, a, leaf); 
    }
}

void solve(int n, int limA, int limB)
{
    if ( limB == 0 ) return Subtask1 :: main(n);
    size[1] = pii(n, 1); p[1] = n;
    REP(i, 2, n) { size[i] = pii(find(1, i), i); p[i] = size[i].first; } 
    sort(size + 1, size + n + 1);
    REP(i, 1, n)
    {
        if ( size[i].first == 1 ) { vis[size[i].second] = true; continue ; }
        sum = p[size[i].second] - 1;
        while ( 1 ) 
        {
            m = 0;
            REP(j, 1, n) if ( vis[j] ) a[++ m] = j;
            random_shuffle(a + 1, a + m + 1);
            vector<int> t;
            REP(j, 1, m) t.push_back(a[j]);
            if ( !t.size() || check(1, size[i].second, t) == 2 ) break ; 
            Solve(size[i].second, 1, m); 
        }
        vis[size[i].second] = true;
    }
}
