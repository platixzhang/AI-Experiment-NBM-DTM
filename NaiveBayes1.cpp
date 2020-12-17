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
	{
		//calculate p_unacc
		double temp1=1.0,temp2=1.0;
		int cntTemp1=0,cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/unacc;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/unacc;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/unacc;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/unacc;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/unacc;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/unacc;
		temp2*=(cntTemp2)/1728.0;
		//cout<<temp1<<" "<<temp2;
		p_unacc=unacc*temp1/temp2;
	}
	
	{
		//calculate p_acc
		double temp1=1.0,temp2=1.0;
		int cntTemp1=0,cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/acc;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/acc;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/acc;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/acc;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/acc;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/acc;
		temp2*=(cntTemp2)/1728.0;
		//cout<<temp1<<" "<<temp2;
		p_acc=acc*temp1/temp2;
	}
	
	{
		//calculate p_good
		double temp1=1.0,temp2=1.0;
		int cntTemp1=0,cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/good;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/good;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/good;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/good;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/good;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/good;
		temp2*=(cntTemp2)/1728.0;
		//cout<<temp1<<" "<<temp2;
		p_good=good*temp1/temp2;
	}
	
	{
		//calculate p_vgood
		double temp1=1.0,temp2=1.0;
		int cntTemp1=0,cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/vgood;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/vgood;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/vgood;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/vgood;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/vgood;
		temp2*=(cntTemp2)/1728.0;
		cntTemp1=0;cntTemp2=0;
		for(int i=0;i<1728;i++)
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
		temp1*=(cntTemp1/1728.0)/vgood;
		temp2*=(cntTemp2)/1728.0;
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
	infile.open("test1.txt");
	int gradeT=0,gradeF=0;
	for(int i=0;i<1350;i++)
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
	printf("=========================================\nGRADES\nSuccessful:%d\nUnsuccessful:%d\nPrecision:%lf",gradeT,gradeF,(double)(gradeT*1.0/1350));
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
	//(3) Test. 
	testData();
	return 0;
}
