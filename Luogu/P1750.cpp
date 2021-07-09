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

const int maxn = 10010;

int a[maxn], n, k;

priority_queue<int, vector<int>, greater<int> > Q;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, n)
    {
        if ( Q.size() == k ) 
        {
            printf("%d ", Q.top());
            Q.pop();
        }
        Q.push(a[i]);
    }
    while ( !Q.empty() ) { printf("%d ", Q.top()); Q.pop(); }
    return 0;
}
