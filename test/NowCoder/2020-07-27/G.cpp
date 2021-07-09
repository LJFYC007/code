/***************************************************************
	File name: G.cpp
	Author: ljfcnyali
	Create time: 2020年07月27日 星期一 14时52分46秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, k;
vector<int> p1[410], q1[410], p2[410], q2[410];
vector<pii> ans1[410], ans2[410];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &n, &k);
        if ( k == 1 || n == 1 ) { puts("-1"); continue ; } 
        mem(p1); mem(p2); mem(q1); mem(q2); mem(ans1); mem(ans2);
        int m = 2 * n * (n + 1);
        if ( m % k != 0 ) { puts("-1"); continue ; }
    
        REP(i, 1, n) if ( i % 2 == 1 ) p1[1].push_back(i); else q1[1].push_back(i);
        REP(i, 2, n + 1)
        {
            if ( i % 2 == 0 ) 
            {
                REP(j, 1, n + 1) if ( j % 2 == 1 ) p2[j].push_back(i - 1); else q2[j].push_back(i - 1);
                REP(j, 1, n) if ( j % 2 == 1 ) q1[i].push_back(j); else p1[i].push_back(j);
            }
            else
            {
                REP(j, 1, n + 1) if ( j % 2 == 1 ) q2[j].push_back(i - 1); else p2[j].push_back(i - 1);
                REP(j, 1, n) if ( j % 2 == 1 ) p1[i].push_back(j); else q1[i].push_back(j);
            }
        }
       
        int sum = m / k, tot = 1;
        REP(i, 1, n + 1) for ( auto j : p1[i] ) 
        {
            if ( !sum ) { sum = m / k; ++ tot; }
            -- sum; ans1[i].push_back(pii(j, tot));
        }
        REP(i, 1, n + 1) for ( auto j : p2[i] ) 
        {
            if ( !sum ) { sum = m / k; ++ tot; }
            -- sum; ans2[i].push_back(pii(j, tot));
        }

        REP(i, 1, n + 1) for ( auto j : q1[i] ) 
        {
            if ( !sum ) { sum = m / k; ++ tot; }
            -- sum; ans1[i].push_back(pii(j, tot));
        }
        REP(i, 1, n + 1) for ( auto j : q2[i] ) 
        {
            if ( !sum ) { sum = m / k; ++ tot; }
            -- sum; ans2[i].push_back(pii(j, tot));
        }

        REP(i, 1, n + 1)
        {
            sort(ans1[i].begin(), ans1[i].end());
            for ( auto j : ans1[i] ) printf("%d ", j.second); puts("");
        }
        REP(i, 1, n + 1)
        {
            sort(ans2[i].begin(), ans2[i].end());
            for ( auto j : ans2[i] ) printf("%d ", j.second); puts("");
        }
    }
    return 0;
}
