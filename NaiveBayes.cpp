/************************************************* 
Copyright:PZ-HNU 
Author: PlatixZhang
Date:2020.12.16
Description:Naive Bayes Database in C++
**************************************************/ 
#include <windows.h>
#include <memory.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>

using namespace std;
struct Sample
{
	string buying;
	string maint;
	string doors;
	string persons;
	string lug_boot;
	string safety;
	string Class_Values;
	Sample(string buying,string maint,string doors,string persons,string lug_boot,string safety,string Class_Values):
		buying(buying),maint(maint),doors(doors),persons(persons),lug_boot(lug_boot),safety(safety),Class_Values(Class_Values)
		{}
	Sample(string buying,string maint,string doors,string persons,string lug_boot,string safety):
		buying(buying),maint(maint),doors(doors),persons(persons),lug_boot(lug_boot),safety(safety)
		{Class_Values="unitialized";}
	Sample(){}
};

ostream& operator << (ostream &out ,const Sample &p)
{
    out<<p.buying<<"\t"<<p.maint<<"\t"<<p.doors<<"\t"<<p.persons<<"\t"<<p.lug_boot<<"\t"<<p.safety<<"\t"<<p.Class_Values<<endl;
    return out;
}

//Dataset Variables
vector<Sample> dataset;
vector<Sample> testset;
ifstream infile;
ofstream outfile; 

//Bayes Probibilities Variables
double acc,unacc,good,vgood;
double buyVHi,buyHi,buyMi,buyLo;
double mtVHi,mtHi,mtMi,mtLo;
double d2,d3,d4,d5;
double p2,p4,p5;
double lgS,lgM,lgB;
double sfLo,sfMi,sfHi;

bool getData()
{
	infile.open("dataset1.txt");
	if(!infile)
	{
		return false;
	}
	//10,368 ',' replaced with ' ',(1728 samples)
	for(int i=0;i<1728;i++)
	{
		Sample temp;
		infile>>temp.buying>>temp.maint>>temp.doors>>temp.persons>>temp.lug_boot>>temp.safety>>temp.Class_Values;
		dataset.push_back(temp); 
	}
	infile.close();
	return true;
}

void calProb()
{
	const int total=1728;
	//calculate buying;
	{
		int cnt1=0,cnt2=0,cnt3=0,cnt4=0;
		for(int i=0;i<total;i++)
		{
			if(dataset[i].buying=="vhigh")
			{
				cnt1++;
			}
			else if(dataset[i].buying=="high")
			{
				cnt2++;
			}
			else if(dataset[i].buying=="med")
			{
				cnt3++;
			}
			else if(dataset[i].buying=="low")
			{
				cnt4++;
			}
		}
		buyVHi=(cnt1+0.0)/total;
		buyHi=(cnt2+0.0)/total;
		buyMi=(cnt3+0.0)/total;
		buyLo=(cnt4+0.0)/total;
		cout<<"calculate buying in dataset..."<<endl;
		//printf("buying:%lf,%lf,%lf,%lf\n",buyVHi,buyHi,buyMi,buyLo);
	}
	//calculate maintain
	{
		int cnt1=0,cnt2=0,cnt3=0,cnt4=0;
		for(int i=0;i<total;i++)
		{
			if(dataset[i].maint=="vhigh")
			{
				cnt1++;
			}
			else if(dataset[i].maint=="high")
			{
				cnt2++;
			}
			else if(dataset[i].maint=="med")
			{
				cnt3++;
			}
			else if(dataset[i].maint=="low")
			{
				cnt4++;
			}
		}
		mtVHi=(cnt1+0.0)/total;
		mtHi=(cnt2+0.0)/total;
		mtMi=(cnt3+0.0)/total;
		mtLo=(cnt4+0.0)/total;
		cout<<"calculate maintain in dataset..."<<endl;
		//printf("maintian:%lf,%lf,%lf,%lf\n",mtVHi,mtHi,mtMi,mtLo);
	}
	//calculate doors
	{
		int cnt1=0,cnt2=0,cnt3=0,cnt4=0;
		for(int i=0;i<total;i++)
		{
			if(dataset[i].doors=="2")
			{
				cnt1++;
			}
			else if(dataset[i].doors=="3")
			{
				cnt2++;
			}
			else if(dataset[i].doors=="4")
			{
				cnt3++;
			}
			else if(dataset[i].doors=="5more")
			{
				cnt4++;
			}
		}
		d2=(cnt1+0.0)/total;
		d3=(cnt2+0.0)/total;
		d4=(cnt3+0.0)/total;
		d5=(cnt4+0.0)/total;
		cout<<"calculate doors in dataset..."<<endl;
		//printf("doors:%lf,%lf,%lf,%lf\n",d2,d3,d4,d5);
	}
	//calculate persons
	{
		int cnt1=0,cnt2=0,cnt3=0;
		for(int i=0;i<total;i++)
		{
			if(dataset[i].persons=="2")
			{
				cnt1++;
			}
			else if(dataset[i].persons=="4")
			{
				cnt2++;
			}
			else if(dataset[i].persons=="more")
			{
				cnt3++;
			}
		}
		p2=(cnt1+0.0)/total;
		p4=(cnt2+0.0)/total;
		p5=(cnt3+0.0)/total;
		cout<<"calculate persons in dataset..."<<endl;
		//printf("persons:%lf,%lf,%lf\n",p2,p4,p5);
	}
	//calculate lugguage boots
	{
		int cnt1=0,cnt2=0,cnt3=0;
		for(int i=0;i<total;i++)
		{
			if(dataset[i].lug_boot=="small")
			{
				cnt1++;
			}
			else if(dataset[i].lug_boot=="med")
			{
				cnt2++;
			}
			else if(dataset[i].lug_boot=="big")
			{
				cnt3++;
			}
		}
		lgS=(cnt1+0.0)/total;
		lgM=(cnt2+0.0)/total;
		lgB=(cnt3+0.0)/total;
		cout<<"calculate lugguage in dataset..."<<endl;
		//printf("lugs:%lf,%lf,%lf\n",lgS,lgM,lgB);
	}
	//calculate safety
	{
		int cnt1=0,cnt2=0,cnt3=0;
		for(int i=0;i<total;i++)
		{
			if(dataset[i].safety=="low")
			{
				cnt1++;
			}
			else if(dataset[i].safety=="med")
			{
				cnt2++;
			}
			else if(dataset[i].safety=="high")
			{
				cnt3++;
			}
		}
		sfLo=(cnt1+0.0)/total;
		sfMi=(cnt2+0.0)/total;
		sfHi=(cnt3+0.0)/total;
		cout<<"calculate safety in dataset..."<<endl;
		//printf("safety:%lf,%lf,%lf\n",sfLo,sfMi,sfHi);
	}
	//calculate classvalue
	{
		int cnt1=0,cnt2=0,cnt3=0,cnt4=0;
		for(int i=0;i<total;i++)
		{
			if(dataset[i].Class_Values=="unacc")
			{
				cnt1++;
			}
			else if(dataset[i].Class_Values=="acc")
			{
				cnt2++;
			}
			else if(dataset[i].Class_Values=="good")
			{
				cnt3++;
			}
			else if(dataset[i].Class_Values=="vgood")
			{
				cnt4++;
			}
		}
		unacc=(cnt1+0.0)/total;
		acc=(cnt2+0.0)/total;
		good=(cnt3+0.0)/total;
		vgood=(cnt4+0.0)/total;
		cout<<"calculate result in dataset..."<<endl;
		//printf("Class:%lf,%lf,%lf,%lf\n",unacc,acc,good,vgood);
	}
}

string calPredict(Sample s)
{
	string flag="not predicted!";
	double p_unacc,p_acc,p_good,p_vgood;
	double x[6]={0.0};
	if(s.buying=="vhigh")
	{
		x[0]=buyVHi;
	}
	else if(s.buying=="high")
	{
		x[0]=buyHi;
	}
	else if(s.buying=="med")
	{
		x[0]=buyMi;
	}
	else if(s.buying=="low")
	{
		x[0]=buyLo;
	}
	
	if(s.maint=="vhigh")
	{
		x[1]=mtVHi;
	}
	else if(s.maint=="high")
	{
		x[1]=mtHi;
	}
	else if(s.maint=="med")
	{
		x[1]=mtMi;
	}
	else if(s.maint=="low")
	{
		x[1]=mtLo;
	}
	
	if(s.doors=="2")
	{
		x[2]=d2;
	}
	else if(s.doors=="3")
	{
		x[2]=d3;
	}
	else if(s.doors=="4")
	{
		x[2]=d4;
	}
	else if(s.doors=="5more")
	{
		x[2]=d5;
	}
	
	if(s.persons=="2")
	{
		x[3]=p2;
	}
	else if(s.persons=="4")
	{
		x[3]=p4;
	}
	else if(s.persons=="more")
	{
		x[3]=p5;
	}
	
	if(s.lug_boot=="small")
	{
		x[4]=lgS;
	}
	else if(s.lug_boot=="med")
	{
		x[4]=lgM;
	}
	else if(s.lug_boot=="big")
	{
		x[4]=lgB;
	}
	
	if(s.safety=="low")
	{
		x[5]=sfLo;
	}
	else if(s.safety=="med")
	{
		x[5]=sfMi;
	}
	else if(s.safety=="high")
	{
		x[5]=sfHi;
	}
	
	printf("%lf,%lf,%lf,%lf,%lf,%lf\n",x[0],x[1],x[2],x[3],x[4],x[5]);
	
	//calculate unacc
	{
		double pi1=1,pi2=1;
		for(int i=0;i<6;i++)
		{
			pi1*=(x[i]/unacc);
			pi2*=x[i];
		}
		printf("pi1=%lf,pi2=%lf,unacc=%lf\n",pi1,pi2,unacc);
		p_unacc=(unacc*pi1)/(pi2);
	}
	//calculate acc
	{
		double pi1=1,pi2=1;
		for(int i=0;i<6;i++)
		{
			pi1*=(x[i]/acc);
			pi2*=x[i];
		}
		printf("pi1=%lf,pi2=%lf,acc=%lf\n",pi1,pi2,acc);
		p_acc=(acc*pi1)/(pi2);
	}
	//calculate good
	{
		double pi1=1,pi2=1;
		for(int i=0;i<6;i++)
		{
			pi1*=(x[i]/good);
			pi2*=x[i];
		}
		printf("pi1=%lf,pi2=%lf,gd=%lf\n",pi1,pi2,good);
		p_good=(good*pi1)/(pi2);
	}
	//calculate very good
	{
		double pi1=1,pi2=1;
		for(int i=0;i<6;i++)
		{
			pi1*=(x[i]/vgood);
			pi2*=x[i];
		}
		printf("pi1=%lf,pi2=%lf,vgood=%lf\n",pi1,pi2,vgood);
		p_vgood=(vgood*pi1)/(pi2);
	}
	//who is bigger?
	cout<<"p_unacc\tp_acc\tp_good\tp_vgood\n"<<p_unacc<<"\t"<<p_acc<<"\t"<<p_good<<"\t"<<p_vgood<<endl;
	double currMax=p_unacc;
	flag="unacc";
	if(p_acc>currMax)
	{
		currMax=p_acc;
		flag="acc";
	}
	if(p_good>currMax)
	{
		currMax=p_good;
		flag="good";
	}
	if(p_vgood>currMax)
	{
		currMax=p_vgood;
		flag="vgood";
	}
	return flag;
}

void testData()
{
	infile.open("test1.txt");
	for(int i=0;i<1350;i++)
	{
		Sample temp;
		infile>>temp.buying>>temp.maint>>temp.doors>>temp.persons>>temp.lug_boot>>temp.safety>>temp.Class_Values;
		if(i%129==0)
		{
			cout<<temp;
			string test_predict=calPredict(temp);
		}
		//cout<<"Reality:"<<temp.Class_Values<<"\t\tPredicted:"<<test_predict<<endl;
		//testset.push_back(temp); 
	}
	infile.close();
}

int main()
{
	//(1) Get data set!
	if(getData())
	{
		cout<<"Get data set!"<<endl;
	}
	else
	{
		cout<<"Can not access data set!"<<endl;
	}
	//(2) Get the probibility of each section
	calProb();
	//(3) Test the Test
	testData();
	return 0;
}
