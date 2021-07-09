/***************************************************************
	File name: E.cpp
	Author: ljfcnyali
	Create time: 2019年09月01日 星期日 20时16分00秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 1010;

queue<int> Q[maxn];
int n;
bool vis[maxn];

int main()
{
    scanf("%d", &n);
    REP(i, 1, n)
        REP(j, 1, n - 1)
        {
            int x; scanf("%d", &x);
            Q[i].push(x);
        }
    int i = 1;
    while ( i ) 
    {
        bool flag = true;
        REP(i, 1, n) if ( !Q[i].empty() ) { flag = false; break ; }
        if ( flag == true ) { printf("%d\n", i - 1); return 0; }
        mem(vis);
        REP(i, 1, n)
        {
            if ( Q[i].empty() || Q[Q[i].front()].empty() ) continue ;
            if ( vis[i] || vis[Q[i].front()] ) continue ;
            if ( Q[Q[i].front()].front() == i ) 
            {
                vis[Q[i].front()] = vis[i] = true; 
                Q[Q[i].front()].pop();
                Q[i].pop();
                flag = true;
            }
        }
        if ( !flag ) { printf("-1\n"); return 0; }
        ++ i;
    }
    return 0;
}
