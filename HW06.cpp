#include"stdafx.h"
#include<iostream>
#include"UNO.h"
#include<string>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int num_player = 0;
	cout << "輸入遊戲人數:";
	cin  >> num_player;
	cout << endl;
	UNO uno1(num_player);
	for(int i = 0;i<num_player;i++)
	{
		cout <<"輸入第"<<i+1<<"位玩家名稱:"<<endl;
		cin  >> uno1.list[i].name;
	}
	cout <<"所有玩家名稱:"<<endl;
	for(int i = 0;i<num_player;i++)
	{
		cout << uno1.list[i].name<<endl;
	}
	uno1.shuffle();
	uno1.deal();
	uno1.Game();
	cout <<endl;
	return 0;
}
