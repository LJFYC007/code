/***************************************************************
	File name: P2730.cpp
	Author: ljfcnyali
	Create time: 2019年05月08日 星期三 08时40分34秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 20;

int a[maxn];
bool p[500010];

struct node
{
	int f[10], v[500], ans;
};

inline int fc(int x)
{
	if ( x == 0 ) return 0;
	if ( x == 1 ) return 1;
	return x * fc(x - 1);
}

inline int js(node p1)
{
	int sum = 0;
	REP(i, 1, 8)
	{
		int s = 0;
		REP(j, i + 1, 8)
			if ( p1.f[i] > p1.f[j] ) ++ s;
		sum += s * fc(8 - i);
	}
	return sum;
}

inline bool pd(node p1)
{
	REP(i, 1, 8) if ( a[i] != p1.f[i] ) return false;
	return true;
}

inline void BFS()
{
	queue<node> Q;
	node p1;
	REP(i, 1, 4) p1.f[i] = i; 
	p1.f[5] = 8; p1.f[6] = 7; p1.f[7] = 6; p1.f[8] = 5;
	p1.ans = 0;
	Q.push(p1);
	int cnt = 0;
	while ( !Q.empty() )
	{
		//++ cnt; if ( cnt == 10000 ) return ;
		p1 = Q.front(); Q.pop();
		if ( pd(p1) == true ) 
		{
			printf("%d\n", p1.ans);
			REP(i, 1, p1.ans)
			{
				printf("%c", 'A' + p1.v[i] - 1);
				if ( i % 60 == 0 ) puts("");
			}
			return ;
		}
		int num = js(p1);
		if ( p[num] == true ) continue ;
		p[num] = true;

		//REP(i, 1, p1.ans) printf("%c", 'A' + p1.v[i] - 1); puts("");
		//REP(i, 1, 4) printf("%d ", p1.f[i]); puts("");
		//REP(i, 5, 8) printf("%d ", p1.f[i]); puts(""); puts("");

		node p2 = p1;
		REP(i, 1, 4) swap(p2.f[i], p2.f[i + 4]);
		p2.ans ++; p2.v[p2.ans] = 1;
		Q.push(p2);

		p2 = p1;
		REP(i, 2, 4) { swap(p2.f[i], p2.f[1]); swap(p2.f[i + 4], p2.f[5]); }
		p2.ans ++; p2.v[p2.ans] = 2;
		Q.push(p2);

		p2 = p1;
		swap(p2.f[2], p2.f[3]); swap(p2.f[2], p2.f[7]); swap(p2.f[2], p2.f[6]);
		p2.ans ++; p2.v[p2.ans] = 3;
		Q.push(p2);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	REP(i, 1, 8)
		scanf("%d", &a[i]);
	swap(a[5], a[8]); swap(a[6], a[7]);
	BFS();
    return 0;
}
