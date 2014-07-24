#include "stdafx.h"
#include<iostream>
#include"UNO.h"
#include"time.h"
#include<string>
using namespace std;

bool Card::CheckCurrent(Card& curr)
{
	if(curr.number == number || curr.type == type|| type==5)
		return true;
	return false;
}

Card::Card()
{
	int type = 0;
	int number = 0;
}
Card::Card(Card& c2)
{
	Card::type = c2.type;
	Card::number = c2.number;
}

void Card::show()
{
		if(type == 5)
		{
			cout <<"Wildcard"<<"  ";
		}
		if(type == 4)
		{
			cout <<"黃色"<<number<<"  ";
		}
		if(type == 3)
		{
			cout <<"紅色"<<number<<"  ";
		}
		if(type == 2)
		{
			cout <<"綠色"<<number<<"  ";
		}
		if(type == 1)
		{
			cout <<"藍色"<<number<<"  ";
		}
}


CardStack::CardStack(CardStack& c1)
{
	
	CardStack::num_card = c1.num_card;
	CardStack::stack = new Card[num_card];
	for(int i = 0;i<num_card;i++)
	{
		CardStack::stack[i] = c1.stack[i];
	}


}
CardStack::CardStack()
{
	stack = 0;
	num_card = 0;

}

//
Card CardStack::Pop()
{
	return stack[--num_card];
}

void CardStack::Shuffle(Card& temp)
{
	num_card++;
	Card* tempstack = new Card[num_card];
	for(int i = 0;i<num_card;i++)
	{

	}
	int numb1 = 0;
	srand(static_cast<unsigned int>(time(NULL)));
	numb1 = rand()%num_card;
	Card tempc(stack[numb1]);
	stack[numb1] = temp;
	stack[num_card-1] = tempc;
}

void Player::Display()
{
	for(int i = 0;i<myCard.num_card;i++)
	{
		if(myCard.stack[i].type == 5)
		{
			cout <<"<"<<i+1<<">"<<"Wildcard"<<"  ";
		}
		if(myCard.stack[i].type == 4)
		{
			cout <<"<"<<i+1<<">"<<"黃色"<<myCard.stack[i].number<<"  ";
		}
		if(myCard.stack[i].type == 3)
		{
			cout <<"<"<<i+1<<">"<<"紅色"<<myCard.stack[i].number<<"  ";
		}
		if(myCard.stack[i].type == 2)
		{
			cout <<"<"<<i+1<<">"<<"綠色"<<myCard.stack[i].number<<"  ";
		}
		if(myCard.stack[i].type == 1)
		{
			cout <<"<"<<i+1<<">"<<"藍色"<<myCard.stack[i].number<<"  ";
		}
		//cout <<myCard.stack[i].type<<"號碼："<< myCard.stack[i].number<<"  ";
	}
	cout <<endl;
}

void Player::Play(Card& curr, CardStack& stack1)
{
	int checkcard1 = 0;
	int pull = 0;

	for(int i = 0;i<stack1.num_card;i++)
	{
		if(stack1.stack[i].CheckCurrent(curr))
		{
			checkcard1++;
		}
	}
	if(checkcard1==0)
	{
		cout <<"沒牌可出,抽一張牌"<<endl;
	}
	else
	{
		cout << "可出的牌有:";
		for(int i = 0;i<stack1.num_card;i++)
		{
			if(stack1.stack[i].CheckCurrent(curr))
			{
				cout<<"<"<<i+1<<">";
				stack1.stack[i].show();
				checkcard1++;
			}
		}
		cout <<"選一張牌出";
		cin >> pull;
	}

}

void Player::ChangeColor(Card& curr)
{
	int color = 0;
	if(curr.type==5)
	{
		cout << "選一個顏色:"<<"  <1>藍色  "<<"  <2>綠色  "<<"  <3>紅色  "<<"  <4>黃色  ";
		cin >>color;
	}
	//UNO::currentCard.type = color;
}

UNO::UNO()
{
	UNO(2);
}

UNO::UNO(int num_player)
{
	num = num_player;
	list = new Player[num];
	
	tableCard.num_card = 80;
	tableCard.stack = new Card[tableCard.num_card];
	
	for (int type = 1; type <= 5; ++type) {
		int num = (type - 1) * 19;

		if (type == 5) {
			for (int i = 0; i <= 4; ++i)
				tableCard.stack[num + i].number = 10,
				tableCard.stack[num + i].type   = type;
			break;
		}

		tableCard.stack[num].number = 0;
		tableCard.stack[num].type = type;

		for (int i = 1; i <= 9; ++i) {
			tableCard.stack[num + i].number = tableCard.stack[num + i + 9].number = i;
			tableCard.stack[num + i].type   = tableCard.stack[num + i + 9].type   = type;
		}
	}
}

void UNO::shuffle()
{
	CardStack temp(tableCard);
	
	int numb = 0;
	srand(static_cast<unsigned int>(time(NULL)));
	
	for(int j = 0;j<tableCard.num_card;j++)
	{
		numb = rand()%tableCard.num_card;
		while(temp.stack[numb].number == 100)
		{
			numb = rand()%tableCard.num_card;
		}
		tableCard.stack[j] = temp.stack[numb];
		temp.stack[numb].number = 100;
	}
}

void UNO::deal()
{
	for(int i = 0;i<num;i++)
	{
		list[i].myCard.stack = new Card[80];
	}
	for(int k = 0;k<num;k++)
	{
		for(int j = 0;j<3;j++)
		{
			Card temp1(tableCard.Pop());
			list[k].myCard.num_card = 3;
			list[k].myCard.stack[j].number = temp1.number;
			list[k].myCard.stack[j].type = temp1.type;
		}
	}
	Card nowcard(tableCard.Pop());
	currentCard.number = nowcard.number;
	currentCard.type = nowcard.type;
}

void UNO::checkUNO()
{
	for(int i = 0;i<num;i++)
	{
		if(list[i].myCard.num_card ==1)
		{
			cout << "UNO!!!!";
		}
		if(list[i].myCard.num_card ==0)
		{
			cout << "玩家：" << list[i].name<<"獲勝!!!";
		}
	}

}

void UNO::Game()
{
	cout << "現在的牌為:";
	currentCard.show();
	cout <<endl;
	pFunc func = &Player::Play;
	
	for(int i = 0;i<num;i++)
	{
		cout <<"現在輪到玩家:"<<list[i].name<<endl;
		cout <<"他的牌有：";
		list[i].Display();
		(list[i].*func)(currentCard,list[i].myCard);
	}
}
