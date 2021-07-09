#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 100010;

signed main(int argc, char* argv[])
{
    REP(i, 1, 1000000000) ;
    srand(time(0));
    int n = atoi(argv[1]), m = rand() % n;
    printf("%d %d\n", n, m);
    REP(i, 1, n) printf("%d ", rand() % n); puts(""); 
    REP(i, 1, n) printf("%d ", rand() % n); puts(""); 
    return 0;
}

