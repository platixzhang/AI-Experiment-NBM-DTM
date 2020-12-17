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
	double total=3078.0;
	infile.open("dataset2.txt");
	if(!infile)
	{
		return false;
	}
	//10,368 ',' replaced with ' ',(total samples)
	for(int i=0;i<total;i++)
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
	const int total=3078;
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
	double total=3078.0;
	double p_unacc,p_acc,p_good,p_vgood;
	{
		//calculate p_unacc
		double temp1=1.0,temp2=1.0;
		int cntTemp1=0,cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.buying==dataset[i].buying)
			{
				if(dataset[i].Class_Values=="unacc")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		//cout<<cntTemp1<<" "<<cntTemp2<<endl;
		temp1*=(cntTemp1/total)/unacc;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.maint==dataset[i].maint)
			{
				if(dataset[i].Class_Values=="unacc")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/unacc;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.doors==dataset[i].doors)
			{
				if(dataset[i].Class_Values=="unacc")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/unacc;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.persons==dataset[i].persons)
			{
				if(dataset[i].Class_Values=="unacc")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/unacc;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.lug_boot==dataset[i].lug_boot)
			{
				if(dataset[i].Class_Values=="unacc")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/unacc;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.safety==dataset[i].safety)
			{
				if(dataset[i].Class_Values=="unacc")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/unacc;
		temp2*=(cntTemp2)/total;
		//cout<<temp1<<" "<<temp2;
		p_unacc=unacc*temp1/temp2;
	}
	
	{
		//calculate p_acc
		double temp1=1.0,temp2=1.0;
		int cntTemp1=0,cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.buying==dataset[i].buying)
			{
				if(dataset[i].Class_Values=="acc")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		//cout<<cntTemp1<<" "<<cntTemp2<<endl;
		temp1*=(cntTemp1/total)/acc;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.maint==dataset[i].maint)
			{
				if(dataset[i].Class_Values=="acc")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/acc;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.doors==dataset[i].doors)
			{
				if(dataset[i].Class_Values=="acc")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/acc;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.persons==dataset[i].persons)
			{
				if(dataset[i].Class_Values=="acc")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/acc;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.lug_boot==dataset[i].lug_boot)
			{
				if(dataset[i].Class_Values=="acc")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/acc;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.safety==dataset[i].safety)
			{
				if(dataset[i].Class_Values=="acc")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/acc;
		temp2*=(cntTemp2)/total;
		//cout<<temp1<<" "<<temp2;
		p_acc=acc*temp1/temp2;
	}
	
	{
		//calculate p_good
		double temp1=1.0,temp2=1.0;
		int cntTemp1=0,cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.buying==dataset[i].buying)
			{
				if(dataset[i].Class_Values=="good")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		//cout<<cntTemp1<<" "<<cntTemp2<<endl;
		temp1*=(cntTemp1/total)/good;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.maint==dataset[i].maint)
			{
				if(dataset[i].Class_Values=="good")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/good;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.doors==dataset[i].doors)
			{
				if(dataset[i].Class_Values=="good")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/good;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.persons==dataset[i].persons)
			{
				if(dataset[i].Class_Values=="good")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/good;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.lug_boot==dataset[i].lug_boot)
			{
				if(dataset[i].Class_Values=="good")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/good;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.safety==dataset[i].safety)
			{
				if(dataset[i].Class_Values=="good")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/good;
		temp2*=(cntTemp2)/total;
		//cout<<temp1<<" "<<temp2;
		p_good=good*temp1/temp2;
	}
	
	{
		//calculate p_vgood
		double temp1=1.0,temp2=1.0;
		int cntTemp1=0,cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.buying==dataset[i].buying)
			{
				if(dataset[i].Class_Values=="vgood")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		//cout<<cntTemp1<<" "<<cntTemp2<<endl;
		temp1*=(cntTemp1/total)/vgood;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.maint==dataset[i].maint)
			{
				if(dataset[i].Class_Values=="vgood")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/vgood;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.doors==dataset[i].doors)
			{
				if(dataset[i].Class_Values=="vgood")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/vgood;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.persons==dataset[i].persons)
			{
				if(dataset[i].Class_Values=="vgood")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/vgood;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.lug_boot==dataset[i].lug_boot)
			{
				if(dataset[i].Class_Values=="vgood")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/vgood;
		temp2*=(cntTemp2)/total;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<total;i++)
		{
			if(s.safety==dataset[i].safety)
			{
				if(dataset[i].Class_Values=="vgood")
				{
					++cntTemp1;
				}
				++cntTemp2;
			}
		}
		temp1*=(cntTemp1/total)/vgood;
		temp2*=(cntTemp2)/total;
		//cout<<temp1<<" "<<temp2;
		p_vgood=vgood*temp1/temp2;
	}
	
	
	//Compare
	//printf("%lf,%lf,%lf,%lf\n",p_unacc,p_acc,p_good,p_vgood);
	double result=p_unacc;
	flag="unacc";
	if(p_acc>result)
	{
		result=p_acc;
		flag="acc";
	}
	if(p_good>result)
	{
		result=p_good;
		flag="good";
	}
	if(p_vgood>result)
	{
		result=p_vgood;
		flag="vgood";
	}
	return flag;
}

void testData()
{
	infile.open("predict1.txt");
	int gradeT=0,gradeF=0;
	for(int i=0;i<378;i++)
	{
		Sample temp;
		infile>>temp.buying>>temp.maint>>temp.doors>>temp.persons>>temp.lug_boot>>temp.safety>>temp.Class_Values;
		if(i%1==0)
		{
			//cout<<temp;
			string test_predict=calPredict(temp);
			cout<<"Reality:"<<temp.Class_Values<<"\t\tPredicted:"<<test_predict<<endl;
			if(temp.Class_Values==test_predict)
			{
				++gradeT;
			}
			else
			{
				++gradeF;
			}
		}
		//testset.push_back(temp); 
	}
	infile.close();
	printf("=========================================\nGRADES\nSuccessful:%d\nUnsuccessful:%d\nPrecision:%lf",gradeT,gradeF,(double)(gradeT*1.0/378));
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
