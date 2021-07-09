/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月23日 星期四 09时39分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 100010;

int in[maxn], out[maxn], t, n, k;
int a[30][30];
bool flag1, flag2, flag, p[maxn], vis[maxn];
char s[maxn];

/*inline void add(int u, int v)
{
	To[++ e] = v;
	Next[e] = Begin[u];
	Begin[u] = e;
}*/

inline void dfs(int u)
{
	vis[u] = true;
	REP(i, 0, 25)
	{
		if ( a[u][i] == 0 ) continue;
		if ( vis[i] ) continue;
		dfs(i);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("words.in", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &t);
	while ( t -- ) 
	{
		mem(in); mem(out); flag1 = flag2 = false; flag = true;
		mem(a); mem(p); mem(vis);
		scanf("%d", &n); getchar();
		REP(i, 1, n)
		{
			scanf("%s", s); int len = str(s);
			in[s[0] - 'a'] ++; out[s[len - 1] - 'a'] ++;
			int u = s[0] - 'a', v = s[len - 1] - 'a';
			a[u][v] = a[v][u] = true;
			p[u] = p[v] = true; k = u;
		}
		dfs(k);
		REP(i, 0, 25) 
		{
			if ( p[i] != vis[i] ) { flag = false; break ; }
			if ( in[i] == out[i] ) continue ;
			if ( in[i] == out[i] + 1 ) 
			{
				if ( flag1 == false ) { flag1 = true; continue; }
				flag = false; break ; 
			}
			if ( in[i] + 1 == out[i] ) 
			{
				if ( flag2 == false ) { flag2 = true; continue; }
				flag = false; break ;
			}
			flag = false; break ;
		}
		if ( (flag1 == true && flag2 == false) || (flag1 == false && flag2 == true) ) flag = false;
		if ( flag == true ) printf("Ordering is possible.\n");
		else printf("The door cannot be opened.\n");
	}
    return 0;
}
