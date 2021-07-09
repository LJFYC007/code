#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 100005
#define ll long long
#define mod 1000000007
using namespace std;
int n,m,k,top;
char s[N];int hf[N],hg[N];
int nx[N],la[N],st[N],si[N],fc[N],ny[N];
int f[5005][5005],g[5005][5005];
int po(int a,int b){
	int an=1;
	while(b!=0){
		if(b&1) an=(ll)an*a%mod;
		a=(ll)a*a%mod;b=(b>>1);
	}
	return an;
}
int adt(int a,int b){
	if(a+b>=mod) return a+b-mod;
	return a+b;
}
int C(int a,int b){
	if(a<0||b<a) return 0;
	return (ll)fc[b]*ny[a]%mod*ny[b-a]%mod;
}
void clear_h(int a,int b){for(int i=0;i<=si[a]+si[b]+1;i++) hf[i]=hg[i]=0;}
void work_add(int a,int b){
	for(int i=0;i<=si[a];i++)
		for(int j=0;j<=si[b];j++){
			hf[i+j+1]=adt(hf[i+j+1],(ll)f[a][i]*C(j,si[b])%mod);
			hf[i+j+1]=adt(hf[i+j+1],(ll)g[a][i]*C(j,si[b])%mod);
			hg[i+j+1]=adt(hg[i+j+1],(ll)f[b][j]*C(i,si[a])%mod);
		}
}
void work_mul(int a,int b){
	for(int i=0;i<=si[a];i++)
		for(int j=0;j<=si[b];j++){
			hf[i+j]=adt(hf[i+j],(ll)f[a][i]*C(j,si[b])%mod);
			hg[i+j]=adt(hg[i+j],(ll)g[a][i]*f[b][j]%mod);
		}
}
void tog(int a,int b){si[a]+=si[b];si[a]++;for(int i=0;i<=si[a];i++) f[a][i]=hf[i],g[a][i]=hg[i];}
int solve(int li,int ri){
	int a=(++n);
	while(nx[li]==ri) li++,ri--;
	if(li==ri){si[a]=0;f[a][0]=s[li]-'0';return a;}
	vector<int>h;int la=li;h.clear();
	for(int i=li;i<=ri;i++){
		if(s[i]=='('){i=nx[i];continue;}
		if(s[i]=='-'){
			int tmp=solve(la,i-1);la=i+1;
			h.push_back(tmp);
		}
	}
	int tmp=solve(la,ri);h.push_back(tmp);
	si[a]=si[h[0]];
	for(int i=0;i<=si[a];i++) g[a][i]=f[h[0]][i];
	for(int i=1;i<h.size();i++) clear_h(a,h[i]),work_add(a,h[i]),work_mul(a,h[i]),tog(a,h[i]);
	for(int i=0;i<=si[a];i++) f[a][i]=adt(f[a][i],g[a][i]);
	return a;
}
int main()
{
	freopen("operator.in","r",stdin);
	freopen("operator.out","w",stdout);
	scanf("%d%d",&m,&k);fc[0]=ny[0]=1;
	for(int i=1;i<=m;i++) fc[i]=(ll)fc[i-1]*i%mod,ny[i]=po(fc[i],mod-2);
	for(int i=1;i<=m;i++) scanf(" %c",&s[i]);
	for(int i=1;i<=m;i++){
		if(s[i]=='(') st[++top]=i;
		if(s[i]==')') nx[st[top]]=i,la[i]=st[top],top--;
	}
	int root=solve(1,m);
	printf("%d\n",f[root][k]);
	return 0;
}
