#include <bits/stdc++.h>
using namespace std;
const int N=250100;
const int P=1e9+9;
int n,K;
int ny[N],jc[N],f[27][N];
int ksm(int x,int k)
{
	int res=1;
	while(k)
	{
		if(k&1)	res=1ll*res*x%P;
		k>>=1;x=1ll*x*x%P;
	}
	return res;
}
inline int lowbit(int x)
{
	return x&(-x);
}
int dfs(int now,int S)
{
	if(f[now][S]!=-1) return f[now][S];
	if(!S)
	{
		f[now][S]=jc[n];
		for(int i=0;i<now;i++) f[now][S]=1ll*f[now][S]*(K-i)%P;
		return f[now][S];
	}
	int res=0,s=S^lowbit(S);
	for(int i=s;i;i=(i-1)&s) 
		 (res+=1ll*ny[S^i]*dfs(now+1,i)%P)%=P;
	(res+=1ll*ny[S]*dfs(now+1,0)%P)%=P;
	return f[now][S]=res;
}
int main()
{
	memset(f,-1,sizeof(f));
	scanf("%d%d",&n,&K);
	jc[0]=1;
	for(int i=1;i<=n;i++) jc[i]=1ll*jc[i-1]*i%P;
	ny[n]=ksm(jc[n],P-2);
	for(int i=n-1;i>=0;i--) ny[i]=1ll*ny[i+1]*(i+1)%P;
	int ans=ksm(K,n);
	if(n&1) printf("%d\n",ans);
	else printf("%d\n",(ans-dfs(0,n)+P)%P);
	return 0;
}
