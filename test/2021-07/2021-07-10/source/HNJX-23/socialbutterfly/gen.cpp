#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int main()
{
    freopen("socialbutterfly.in", "w", stdout);
    srand(time(0)); 
    int T = 10000; printf("%d\n", T);
    while ( T -- )
    {
    vector<pii> Edge;
    int n = rand() % 15 + 1, m = 0, lim = rand() % 70 + 1;
    int val = rand() % 100 + 1;
    int y = rand() % 20 + 1;
    REP(i, 1, n) REP(j, i + 1, n)
    {
        int x = rand() % val == 0 ? rand() % y + 20 : rand() % y;
        m += x; REP(k, 1, x) Edge.push_back(pii(i, j));
    }
    printf("%d %d %d\n", n, m, lim);
    for ( auto it : Edge ) printf("%d %d\n", it.first, it.second);
    }
    return 0;
}