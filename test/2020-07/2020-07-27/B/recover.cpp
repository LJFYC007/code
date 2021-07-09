#include "recover.h"
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;

vector<pii> ans;
bool vis[maxn], Edge[maxn][maxn];;

vector<pii> recover(int n)
{
    while ( 1 ) 
    {
        vector<int> p; p.clear();
        pii x;
        REP(i, 1, n) 
        {
            if ( vis[i] ) continue ;
            for ( auto j : p ) if ( Edge[j][i] || Edge[i][j] ) goto Next ;
            p.push_back(i); 
            if ( p.size() == 1 ) { vis[i] = true; continue ; } 
            x = query(p);
            if ( x.first == -1 ) { vis[i] = true; continue ; }
            p.pop_back(); Edge[x.first][x.second] = 1;
Next : ;
        }

        if ( p.empty() ) break ;

        vector<int> g = p;
        REP(i, 1, n) 
        {
            if ( vis[i] ) continue ;
            p.push_back(i); 
            for ( int j = 0; j < p.size(); ++ j )
                if ( Edge[p[j]][i] || Edge[i][p[j]] ) { p.erase(p.begin() + j); -- j; }
            x = query(p);
            while ( x.first != -1 ) 
            {
                Edge[x.first][x.second] = 1;
                int y = x.first == i ? x.second : x.first; 
                for ( int j = 0; j < p.size(); ++ j ) 
                    if ( p[j] == y ) { p.erase(p.begin() + j); break ; }
                x = query(p);
            }
            p = g;
        }
    }
    REP(i, 1, n) REP(j, 1, n) if ( Edge[i][j] ) ans.push_back(pii(i, j));
    return ans;
}
