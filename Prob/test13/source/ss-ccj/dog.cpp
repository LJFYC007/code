#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;
const int INF=1000001;
int q,wzz,cs,k;
vector<int>t1,t2;
long long ans;
typedef struct{
	long long sum,num;
}P;
P p[4000002];
void gengxin(int root,int begin,int end,int wz,int z){
	if (begin>wz || end<wz)return;
	if (begin==end)
	{
		p[root].sum+=(long long)begin*z;p[root].num+=z;
		return;
	}
	int mid=(begin+end)/2;
	gengxin(root*2,begin,mid,wz,z);gengxin(root*2+1,mid+1,end,wz,z);
	p[root].sum=(p[root*2].sum+p[root*2+1].sum);
	p[root].num=(p[root*2].num+p[root*2+1].num);
}
void gx(int x,int y){
	gengxin(1,1,INF,x,y);
	t1.push_back(x);t2.push_back(y);
}
void fuyuan(){
	for (int i=t1.size()-1;i>=0;i--)gengxin(1,1,INF,t1[i],-t2[i]);
}
long long chaxund(int root,int begin,int end,int wz){
	if (begin==end)return p[root].num; 
	int mid=(begin+end)/2;
	if (wz<=mid)return chaxund(root*2,begin,mid,wz);else return chaxund(root*2+1,mid+1,end,wz);
}
int cxx(int root,int begin,int end){
	if (begin==end)return begin;
	int mid=(begin+end)/2;
	if (p[root*2].num)return cxx(root*2,begin,mid);else return cxx(root*2+1,mid+1,end);
}
void fin(int root,int begin,int end,int begin2,int end2){
	if (begin>end2 || end<begin2 || wzz)return;
	if (begin>=begin2 && end<=end2)
	{
		if (p[root].num)wzz=cxx(root,begin,end);
		return;
	}
	int mid=(begin+end)/2;
	fin(root*2,begin,mid,begin2,end2);fin(root*2+1,mid+1,end,begin2,end2);
}
void cx2(int root,int begin,int end,int k){
	if (begin==end){ans+=(long long)k*begin;return;}
	int mid=(begin+end)/2;
	if (p[root*2].num<k)
	{
		ans+=p[root*2].sum;cx2(root*2+1,mid+1,end,k-p[root*2].num);
	}
	else cx2(root*2,begin,mid,k);
}
void chaxun(int root,int begin,int end,int begin2,int end2){
	if (begin>end2 || end<begin2 || cs==k)return;
	if (begin>=begin2 && end<=end2)
	{
		if (cs+p[root].num<=k)
		{
			cs+=p[root].num;ans+=p[root].sum;
		}
		else
		{
			cx2(root,begin,end,k-cs);cs=k;
		}
		return;
	}
	int mid=(begin+end)/2;
	chaxun(root*2,begin,mid,begin2,end2);chaxun(root*2+1,mid+1,end,begin2,end2);
}
int main()
{
	freopen("dog.in","r",stdin);
	freopen("dog.out","w",stdout);
	scanf("%d",&q);
	for (int i=1;i<=q;i++)
	{
		int op;
		scanf("%d",&op);
		if (op==1)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			gengxin(1,1,INF,x,y-chaxund(1,1,INF,x));
		}
		else
		{
			t1.clear();t2.clear();
			scanf("%d",&k);ans=k;
			int d1=chaxund(1,1,INF,1),d2=chaxund(1,1,INF,2);
			if (d2/2+d1>=k){printf("%d\n",k);continue;}
			else
			{
				k-=d2/2+d1;
				if (d2%2==0)
				{
					gx(2,-d2);gx(3,d2/2);
					wzz=0;fin(1,1,INF,2,INF);
					gx(wzz,-1);gx(wzz+1,1);
				}
				else
				{
					gx(2,-d2);gx(3,d2/2+1);
				}
				cs=0;chaxun(1,1,INF,3,INF);ans-=2*k;
			}
			fuyuan();printf("%lld\n",ans);
		}
	}
	return 0;
}
