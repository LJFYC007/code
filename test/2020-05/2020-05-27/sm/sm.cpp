/***************************************************************
	File name: sm.cpp
	Author: ljfcnyali
	Create time: 2020年05月27日 星期三 18时57分20秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, sum, ans[maxn], Map3[maxn];
vector<pii> Map1[maxn];
vector<int> Map2[maxn];
set<int> Set;
struct node 
{ 
    int u, v, id; 
    node(int a, int b, int c) { u = a; v = b; id = c; }
} ;
vector<node> f[maxn];

signed main()
{
    freopen("sm.in", "r", stdin);
    freopen("sm.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n) 
    {
        int u, v, t; scanf("%lld%lld%lld", &t, &u, &v);
        f[t].push_back(node(u, v, i));
    }
    int x = 1, num = 0;
    // int N = 8;
    int N = 50000000;
    REP(o, 0, N)
    {
        if ( o <= 100000 ) 
        for ( auto i : f[o] ) 
        {
            ++ Map3[i.u]; ++ num;
            if ( i.u >= x ) ++ sum;
            else -- sum;
            Map1[i.u].push_back(pii(i.v, i.id));
        }
        for ( auto i : Map1[x] ) 
        {
            -- Map3[x]; ++ Map3[i.first];
            Map2[i.first].push_back(i.second);
            if ( i.first >= x ) ++ sum;
            else -- sum;
        }
        for ( auto i : Map2[x] ) { -- Map3[x]; -- num; ans[i] = o; }
        sum -= Map1[x].size() + Map2[x].size();
        Map1[x].clear();
        Map2[x].clear();;
        if ( num == 0 ) continue ;
        if ( sum >= 0 ) { sum -= 2 * Map3[x]; ++ x; }
        else { -- x; sum += 2 * Map3[x]; }
    }
    
    int T = N + 1, sum = 0;
    REP(i, 0, m) 
    {
        if ( Map1[i].size() || Map2[i].size() ) Set.insert(i);
        if ( i < x ) sum -= Map1[i].size() + Map2[i].size(); 
        else sum += Map1[i].size() + Map2[i].size();
    }
    while ( num ) 
    {
        if ( sum < 0 )
        {
            int pos = *(-- Set.upper_bound(x));
            T += x - pos; x = pos;
            sum += Map1[x].size() + Map2[x].size();
            for ( auto i : Map1[x] ) 
            {
                Map2[i.first].push_back(i.second);
                Set.insert(i.first);
                if ( i.first >= x ) ++ sum;
                else -- sum;
            }
            Set.erase(x);
            num -= Map2[x].size();
            for ( auto i : Map2[x] ) ans[i] = T;
            Map1[x].clear(); Map2[x].clear();
        }
        else
        {
            int pos = *Set.lower_bound(x);
            T += pos - x; x = pos;
            sum -= Map1[x].size() + Map2[x].size();
            for ( auto i : Map1[x] ) 
            {
                Map2[i.first].push_back(i.second);
                Set.insert(i.first);
                if ( i.first >= x ) ++ sum;
                else -- sum;
            }
            Set.erase(x);
            num -= Map2[x].size();
            for ( auto i : Map2[x] ) ans[i] = T;
            Map1[x].clear(); Map2[x].clear();
        }
    }

    REP(i, 1, n) printf("%lld\n", ans[i]);
    return 0;
}
