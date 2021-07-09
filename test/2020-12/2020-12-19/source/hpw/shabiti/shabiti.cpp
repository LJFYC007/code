/*************************************************************************
	> File Name: shabiti.cpp
	> Author: The-Out-Land
	> Mail: 2264454706@qq.com 
	> Created Time: 2020年12月19日 星期六 12时45分49秒
 ************************************************************************/

#include <bits/stdc++.h>

#define enter putchar('\n')
#define space putchar(' ')
#define re register
#define N 1010
#define M 3010
#define bit bitset<N>

using namespace std;

inline int max(int x,int y){return (x>y?x:y);}

inline int min(int x,int y){return (x<y?x:y);}

inline int read(){
	int x=0;char c=getchar();bool y=1;
	for(;c<'0' || c>'9';c=getchar()) if(c=='-') y=0;
	for(;c>='0' && c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	if(y) return x;
	return -x;
}

int n,m,id,len,tot,L;

int from[M],to[M],p[M];

bit a[N],E[M],c[M],now;

char s[N];

inline void Read(){
	int x=read(),y=read();
	scanf("%s",s);
	len=strlen(s);
	now.reset();
	for(re int i=0;i<len;++i) now[len-i-1]=s[i]-'0';
	L=max(L,len);
	++tot;
	from[tot]=x,to[tot]=y,E[tot]=now;
	return;
}

inline void insert(int x){
	for(re int i=L;~i;--i)
	if(a[x][i]){
		if(!p[i])		{p[i]=x;break;}
		else			a[x]^=a[p[i]],c[x]^=c[p[i]];
	}
	return;
}

inline void query(){
	bit ans;
	int wh=0;
	for(re int i=L;~i;--i){
		if(!ans[i] && a[p[i]].any()) wh=max(wh,i),ans^=a[p[i]];
	}
	for(re int i=wh;~i;--i) putchar(ans[i]+'0');
	return;
}

inline void modify(int id,int wh){
	bit O,Q;
	int x=0;
	for(re int i=1;i<=n;++i)if(c[i][id] && a[i].none()){x=i;break;}
	if(!x){
		for(re int i=0;i<=L;++i)
		if(p[i] && c[p[i]][id])
		{x=p[i];p[i]=0;break;}
	}
	for(re int i=1;i<=n;++i){
		if(c[i][id] && i!=x){
			a[i]^=a[x];
			c[i]^=c[x];
		} 
	}
	a[x]^=E[wh];
	insert(x);
	return;
}

inline void Input(){
	id=read();
	n=read();m=read();
	for(re int i=1;i<=m;++i) Read();
	for(re int i=1;i<=n;++i) c[i][i]=1;
	return;
}

inline void solve(){
	L=max(L,n+2);
	for(re int i=1;i<=m;++i){
		modify(from[i],i);
		modify(to[i],i);
		query();
		enter;
	}
	return;
}

int main(){
	freopen("shabiti.in","r",stdin);
	freopen("shabiti.out","w",stdout);
	Input();
	solve();
	return 0;
}
