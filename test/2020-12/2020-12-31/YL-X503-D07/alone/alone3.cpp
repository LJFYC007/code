/***************************************************************
	File name: alone3.cpp
	Author: ljfcnyali
	Create time: 2020年12月31日 星期四 11时15分57秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const double eps = 1e-14;
const double delta = 0.9998;

int op, n, m, Ans;
map<int, bool> Map[maxn];
vector<int> p, gg;
set<int> q; 

inline void Insert(int x)
{
    for ( auto it : q ) if ( Map[it].count(x) ) return ;
    q.insert(x);
}

inline void SA()
{
    int T = n * 300; q.clear();
    while ( T > eps ) 
    {
        int x = rand() % n + 1; set<int> qq = q;
        auto it = q.lower_bound(x);
        if ( it != q.end() && *it == x ) 
        {
            if ( rand() % q.size() == 0 ) q.erase(it); 
            else { T *= delta; continue ; }
        }
        else Insert(x);
        if ( q.size() == qq.size() ) continue ;
        gg.clear(); for ( auto it : q ) gg.push_back(it);
        if ( gg.size() > Ans ) { Ans = gg.size(); p = gg; }
        if ( exp(1 / T) * RAND_MAX < rand() ) q = qq;
        T *= delta;
    }
}

int main()
{
    scanf("%d%d%d", &op, &n, &m);
    REP(i, 1, m) { int u, v; scanf("%d%d", &u, &v); Map[u][v] = Map[v][u] = true; }
    srand(time(0));
    REP(i, 1, 3) SA();
    printf("%d\n", Ans);
    for ( auto it : p ) printf("%d\n", it);
    return 0;
}
