#include "party.h"
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

bool vis[maxn];

inline vector<int> Get(int l, int r)
{
    vector<int> p; p.clear();
    REP(i, l, r) p.push_back(i);
    return ask(p);
}

int findUnusualGuest(int n, int m, int q) 
{
    if ( n < m ) 
    {
        int L = 0, R = n - 1; vector<int> p = Get(L, R);
        if ( p.size() != m ) 
        {
            for ( auto i : p ) vis[i] = true;
            REP(i, n, n + m - 1) if ( !vis[i] ) return i;
        }
        while ( L < R ) 
        {
            int Mid = L + R >> 1;
            p = Get(L, Mid);
            if ( p.size() > (Mid - L + 1) ) R = Mid;
            else L = Mid + 1;
        }
        return L;
    }
    else
    {
        int L = n, R = n + m - 1; vector<int> p = Get(L, R);
        if ( p.size() != n ) 
        {
            for ( auto i : p ) vis[i] = true;
            REP(i, 0, n - 1) if ( !vis[i] ) return i;
        }
        while ( L < R ) 
        {
            int Mid = L + R >> 1;
            p = Get(L, Mid);
            if ( p.size() > (Mid - L + 1) ) R = Mid;
            else L = Mid + 1;
        }
        return L;
    }
    return 0;
}
