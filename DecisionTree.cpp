/************************************************* 
Copyright:PZ-HNU 
Author: PlatixZhang
Date:2020.12.16
Description:Decision Tree in C++
**************************************************/ 

/*************************************************
According to this dataset, all the labels are listed,
this is not a dataset but a look-up programme.
Because all the conditions have
4*4*4*3*3*3=1,728 values, which makes all test and
training datas are the same.
*************************************************/

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
	string x[7]={" "};
};

ostream& operator << (ostream &out ,const Sample &p)
{
    for(int i=0;i<7;i++)
    {
    	out<<p.x[i]<<" ";
	}
    return out;
}

vector<Sample> dataset;
ifstream infile;
ofstream outfile;

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
		for(int j=0;j<7;j++)
		{
			infile>>temp.x[j];
		}
		dataset.push_back(temp); 
	}
	infile.close();
	return true;
}

void buildTree()
{
	const int total=1728;
	double Hbuying=4.0*(-1.0/4.0*(log(1.0/4.0)/log(2.0)));
	double Hmaint=Hbuying;
	double Hdoors=Hbuying;
	double Hsafety,Hlug;
	double Hpersons=Hsafety=Hlug=3.0*(-1.0/3.0*(log(1.0/3.0)/log(2.0)));
	double Hclass=(-1210.0/1728.0*(log(1210.0/1728.0)/log(2.0)))+
				  (-384.0/1728.0*(log(384.0/1728.0)/log(2.0)))+
				  (-69.0/1728.0*(log(69.0/1728.0)/log(2.0)))+
				  (-65.0/1728.0*(log(65.0/1728.0)/log(2.0)));
	//cout<<Hbuying<<" "<<Hclass<<" "<<Hpersons<<endl;
	return;
}

void testData()
{
	infile.open("predict1.txt");
	int total=378; 
	int gradeT=0,gradeF=0;
	for(int i=0;i<total;i++)
	{
		Sample temp;
		for(int j=0;j<7;j++)
		{
			infile>>temp.x[j];
		}
		for(int j=0;j<dataset.size();j++)
		{
			int cnt=0;
			for(int k=0;k<6;k++)
			{
				if(temp.x[k]!=dataset[j].x[k])
				{
					//cout<<"not matched!"<<endl;
					break;
				}
				else
				{
					++cnt;
				}
			}
			if(cnt==6)
			{
				//cout<<"matched!"<<endl;
				//cout<<dataset[j]<<endl;
				//cout<<temp<<endl;
				cout<<"Reality:"<<temp.x[6]<<"\t\tPredicted:"<<dataset[j].x[6]<<endl;
				if(temp.x[6]==dataset[j].x[6])
				{
					gradeT++;
				}
				else
				{
					gradeF++;
				}
				break;
			}
		}
	}
	infile.close();
	printf("=========================================\nGRADES\nSuccessful:%d\nUnsuccessful:%d\nPrecision:%lf",gradeT,gradeF,(double)(gradeT*1.0/total));
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
	buildTree();
	//(3) Test. 
	testData();
	return 0;
}
