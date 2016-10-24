#include<iostream>
#include<string>
#include<cstring>
#include<stdio.h>
using namespace std;
main()
{
int qa;
	char buffer[250]="vocal aaa";
					qa = strncmp(buffer, "vocal", 4);
					if(qa>0)
					{
						cout<<"1\n";
					}
					if(qa<0)
					{
			cout<<"2\n";
					}
					if(qa==0)
					{
cout<<"3\n";
					}
}
