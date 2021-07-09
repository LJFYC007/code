//�����·���ѡ�ֵĽ�����
//��ע�⣺ʵ������ʱʹ�õĽ�����������ͬ
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
char hidden_str_[233333]; int n_,ml_,cnt_;
std::vector<int> guess(int);
bool is_subsequence(std::vector<int> v)
{
	if((int)v.size()>n_)
	{
		puts("query length too long");
		exit(-1);
	}
	for(auto s:v)
		if(s!=0&&s!=1)
		{
			puts("query sequence is not binary");
			exit(-1);
		}
	++cnt_;
	if(int(v.size())>ml_) ml_=int(v.size());
	if(!v.size()) return 1;
	unsigned p=0;
	for(int i=0;i<n_;++i)
	{
		if(v[p]==int(hidden_str_[i])-48)
		{++p; if(p==v.size()) return 1;}
	}
	return 0;
}
int main()
{
	scanf("%s",hidden_str_);
	n_=strlen(hidden_str_);
	std::vector<int> g=guess(n_);
	for ( auto i :g ) printf("%d ", i); puts("");
	if(int(g.size())!=n_)
	{
		puts("length of your result is wrong");
		exit(-1);
	}
	for(int i=0;i<n_;++i)
		if(g[i]!=int(hidden_str_[i])-48)
		{
			printf("position %d of your result is wrong\n",i);
			exit(-1);
		}
	int a=ml_,b=n_/2+1;
	double score=(a<=b)?1:(pow(0.32,a/(double)b-1)*0.9);
	printf("Well done! You made %d queries with max length %d. You can get %.10lf of the full score.\n",cnt_,a,score);
}

