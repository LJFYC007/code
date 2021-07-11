#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define pii pair<int, int>

const int maxn = 1e5 + 10;

int main()
{
    freopen("tree.in", "w", stdout);
    srand(time(0));
    int n = 50, m = 5000; printf("%d %d\n", n, m);
    REP(i, 2, n) printf("%d %d\n", i, rand() % (i - 1) + 1);
    REP(i, 1, m)
    {
        int op = rand() % 2 + 1, x = rand() % n + 1;
        if ( op == 1 ) printf("%d %d %d %d\n", op, rand() % n + 1, rand() % n + 1, x);
        else printf("%d %d %d\n", op, rand() % n + 1, x);
    }

    return 0;
}