#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

struct node
{
    int x, time;
}a;

deque<node> Q;

int n, m;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n)
    {
        if ( Q.empty() ) printf("0\n");
        else
        {
            if ( Q.front().time + m < i ) Q.pop_front();
            printf("%d\n", Q.front().x);
        }
        scanf("%d", &a.x);
        a.time = i;        
        while ( !Q.empty() && Q.back().x >= a.x ) Q.pop_back();
        Q.push_back(a);
    }
    return 0;
}
