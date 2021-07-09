/***************************************************************
	File name: travel.cpp
	Author: huhao
	Create time: Sat 26 Dec 2020 09:39:00 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#include<vector>
#include"travel.h"
#ifdef compile_with_grader
#include"grader.cpp"
#endif
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)

namespace run
{
	const int N=1<<11|10;
	std::vector<int> e[N];
	int v[N],w[N];
	void Report(int u,int v)
	{
//		printf("R %d %d\n",u,v);
		if(!u||!v) return ;
		report(u,v); e[u].push_back(v); e[v].push_back(u);
	}
	void split(int u,int f,std::vector<int> a,std::vector<int> &b,std::vector<int> &c)
	{
		int p=check(u,f,a);
		if(p==1||p==2)
		{
			for(auto i:a) (p==1?b:c).push_back(i);
			return ;
		}
		int n=a.size(),m=n/2; std::vector<int> a1,a2;
		fr(i,0,m-1) a1.push_back(a[i]);
		fr(i,m,n-1) a2.push_back(a[i]);
		split(u,f,a1,b,c); split(u,f,a2,b,c);
	}
	void dfs(int u,int f)
	{
		w[u]=1;
		for(auto i:e[u]) if(v[i]&&i!=f){ dfs(i,u); w[u]+=w[i]; }
	}
	void Dfs(int u,int f,int op,std::vector<int> &a,std::vector<int> &b)
	{
		if(!v[u]) return ;
		if(v[u]==2) op=1;
		(op?b:a).push_back(u);
		for(auto i:e[u]) if(i!=f) Dfs(i,u,op,a,b);
	}
	int findr(std::vector<int> a,int f)
	{
		if(a.size()==1) return a[0];
		int u=a[0],m;
		for(auto i:a) v[i]=1;
		dfs(u,0); m=w[u];
		for(auto i:a) if(w[i]+w[i]>=m&&w[i]<w[u]) u=i;
		dfs(u,0); std::vector<int> b,c,d,C,D; int t=m/2;
		for(auto i:e[u]) if(v[i]) b.push_back(i);
		std::sort(b.begin(),b.end(),[&](int a,int b){ return w[a]>w[b]; });
		int c1=0,c2=0;
		for(auto i:b) if(w[i]<=t){ t-=w[i]; v[i]=2; c1++; /*printf(">%d\n",i);*/ }
		else c2++;
		Dfs(u,f,0,c,d);
		for(auto i:a) v[i]=0;
		if(check(f,u,d)==1) return findr(c,f);
		else
		{
			if(c1>1) d.push_back(u);
			return findr(d,f);
		}
	}
	void solve(std::vector<int> a)
	{
		if(a.size()<=1) return ;
		std::vector<int> b,c;
		split(a[1],a[0],a,b,c);
		solve(b); solve(c);
		Report(a[0],findr(c,a[0]));
	}
	void solve(int n,int lA,int lB)
	{
		std::vector<int> a;
		fr(i,1,n) a.push_back(i);
		solve(a);
	}
}
void solve(int n,int la,int lb){ run::solve(n,la,lb); }
