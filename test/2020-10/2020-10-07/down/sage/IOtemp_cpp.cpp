//C++
#include<cstdio>

namespace IO{
	int c;
	unsigned int seed;
	unsigned int randnum(){
		seed^=seed<<13;
		seed^=seed>>17;
		seed^=seed<<5;
		return seed;
	}

	inline int read(int &x){scanf("%d",&x);return x;}
	inline void init_case(int &m,int &a,int &b,int &d,int p[]){
		scanf("%d%u%d%d%d%d",&m,&seed,&a,&b,&c,&d);
		for(int i=1;i<=m;i++){
			if(randnum()%c==0)p[i]=-1;
			else p[i]=randnum()%b;
		}
	}

	inline void update_ans(unsigned int &ans_sum,unsigned int cur_ans,int no){
		const static unsigned int mod=998244353;
		ans_sum^=(long long)no*(no+7)%mod*cur_ans%mod;
	}
}
using IO::read;
using IO::init_case;
using IO::update_ans;
/*
һ��ʼ�����read(T)������������T
������ÿ�����ݿ�ʼʱ�����init_case(m,a,b,d,p)����m,a,b,d,p[]
ÿ�����ݿ�ʼʱ����һ����ʼ��Ϊ0��32λ�޷������α���ans_sum�洢�𰸣�Ȼ�����ÿ��i��
��32λ�޷������α���cur_ans�洢��i�δ𰸣�������update_ans(ans_sum,cur_ans,i)���¡�������ans_sum���ɡ�
*/

//ʾ�����룺
/*
int main(){
	static int p[2000005];
	int T;read(T);
	int m,a,b,d;
	while(T--){
		unsigned int ans_sum=0,cur_ans=0;
		init_case(m,a,b,d,p);
		for(int i=1;i<=m;i++){
			......//�������
			update_ans(ans_sum,cur_ans,i);
		}
		printf("%u\n",ans_sum);
	}
	return 0;
}
*/
