#include "CardGame.h"

#include <ctime>
#include "constart.h"
using namespace std;
CardGame::CardGame() {
	selfCards_node = Node::create();//初始化节点
}

void CardGame::shuffle(int a[], int len)
{
	int idx, tmp, i;
	for (int i = 0; i < len; i++)
	{
		a[i] = i;
	}
	srand((unsigned)time(NULL));
	for (i = len - 1; i > 0; i--) {
		idx = rand() % i; // 随机一个i范围内的数，然后和i交换位置
		tmp = a[i];
		a[i] = a[idx];
		a[idx] = tmp;
	}


}

///单例模式
static CardGame *s_SharedGame = nullptr;
CardGame *CardGame::getInstance() {
	if (!s_SharedGame) {
		s_SharedGame = new (std::nothrow) CardGame;
		CCASSERT(s_SharedGame, "FATAL:Not enough memory");

	}
	return s_SharedGame;
}
void CardGame::cleanInstance() {
	CC_SAFE_DELETE(s_SharedGame);
}
//判断是否为单牌
bool  isdan(vector<int>arr) {
	bool allSame = false;
	for (int i = 1; i < arr.size(); i++)
	{
		if (arr[0] % 13 != arr[i] % 1)
		{

			allSame = true;
			break;
		}
	}
	if (allSame==false)
	{
		return false;
	}
	else
	{
		return true;
	}

}
//判断是否为对子
bool isDouble(vector<int>arr) {
	int s = 0;
	for (int  i = 0; i < arr.size(); i++)
	{
		if (arr[1]%13==arr[i]%13)
		{
			s++;
		}
	}
	if (s == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//顺子
bool isStraight(vector<int>arr) {

	vector<int >vec(14, 0);
	for (int i = 0; i < arr.size(); i++)
	{
		vec[arr[i] % 13] = vec[arr[i] % 13] + 1;
	}
	if (vec[12] > 0 && vec[0] > 0)
	{
		vec[0]--;
		vec[13]++;
	}
	int count = 0;
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == 1)
		{
			count++;
		}
		else  if (count != 0)
		{
			break;
		}
	}
	if (count == arr.size())
	{
		return true;
	}
	else
	{
		return  false;
	}
	return false;


}

bool  isbaozi(vector<int>arr) {

	int s = 0;
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[1] % 13 == arr[i] % 13)
		{
			s++;
		}
	}
	if (s ==3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool  isflower(const int *arr) {
	int s = 0;
	for (int  i = 0; i < 3; i++)
	{
		if (arr[1]==arr[i])
		{
			s++;
		}
	}
	if (s == 3)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

bool  isstraight(vector<int>arr, const int *hua) {

	int s = 0;
	for (int i = 0; i <3; i++)
	{
		if (hua[1] == hua[i])
		{
			s++;
		}
	}
	if (s == 3)
	{
		vector<int >vec(14, 0);
		for (int i = 0; i < arr.size(); i++)
		{
			vec[arr[i] % 13] = vec[arr[i] % 13] + 1;
		}
		if (vec[12] > 0 && vec[0] > 0)
		{
			vec[0]--;
			vec[13]++;
		}
		int count = 0;
		for (int i = 0; i < vec.size(); i++)
		{
			if (vec[i] == 1)
			{
				count++;
			}
			else  if (count != 0)
			{
				break;
			}
		}
		if (count == arr.size())
		{
			return true;
		}
		else
		{
			return  false;
		}
		return false;
	}
	else
	{
		return false;
	}

}
//获取牌面值
int getValue(int tag) {
	int res = tag % 13 + 1;
	if (res == 1)res = 14;
	return res;
}
int getcolor(int color) {
	int s = color;
	int  a = 0;
	if (s == 1)
	{
	
		a = 4;
	}
	else  if(s==2)
	{
		
		a = 1;
	}
	else if (s==3)
	{
		a = 2;
	}
	else  if(s==4)
	{

		a = 3;
	}
	return a;


}
PokerType CardGame::getPokerTypeWithCards(vector<int> arr, const int *hua)
{

 if (isbaozi(arr))
	{
		return PokerType::POKER_TYPE_LEOPARD;

	}
	else if (isstraight(arr, hua))
	{
		return PokerType::POKER_TYPE_STRAIGHT_FLUSH;
	}
	else if (isflower(hua))
	{
		return PokerType::POKER_TYPE_GOLDEN_FLOWER;
	}
	else  if (isStraight(arr))
	{
		return PokerType::POKER_TYPE_STRAIGHT;
	}
	else if (isDouble(arr))
	{
		return PokerType::POKER_TYPE_DOUBLE;
	}
	else
	{
		return PokerType::POKER_TYPE_SINGLE;
	}
	return PokerType();
}
bool Pair(vector<int> selfCards, vector<int> lastCards, const int *mhua, const int *dhua) {

	
			if (getValue(selfCards[0]) == getValue(selfCards[1]))
			{
				if (getValue(selfCards[2]) > getValue(lastCards[2]))
				{
					return true;
				}
				else  if (getValue(selfCards[ 2]) < getValue(lastCards[ 2]))
				{
					return false;
				}
				else {
					/////////////花色比较//////////////
					if (getcolor(mhua[2]) > getcolor(dhua[2]))
					{
						return true;
					}
					else {
						return false;
					}
				}
			
			}
			else if (getValue(selfCards[2]) == getValue(selfCards[2]))
			{
				if (getValue(selfCards[0]) > getValue(lastCards[0]))
				{
					return true;
				}
				else  if (getValue(selfCards[0]) < getValue(lastCards[0]))
				{
					return false;
				}
				else {
					
					/////////////花色比较//////////////
					if (getcolor(mhua[0]) > getcolor(dhua[0]))
					{
						return true;
					}
					else {
						return false;
					}

				}
			}
			else
			{
				return false;
			}


}


bool CardGame::biggerThanLast(vector<int> selfCards, vector<int> lastCards, const int *color1, const int *color2)
{
	//获取牌型
	PokerType selfType = getPokerTypeWithCards(selfCards,color1);
	PokerType lastType = getPokerTypeWithCards(lastCards,color2);

	// 上家单牌
	if (lastType == POKER_TYPE_SINGLE)
	{
		// 自己单牌
		if (selfType == POKER_TYPE_SINGLE)
		{

			if (getValue(selfCards[0]) > getValue(lastCards[0]))
			{
				return true;
			}
			else 	 if (getValue(selfCards[0]) < getValue(lastCards[0]))
			{
				return false;
			}
			else {


				if (getValue(selfCards[1]) > getValue(lastCards[1]))
				{
					return true;
				}
				else 	 if (getValue(selfCards[1]) < getValue(lastCards[1]))
				{
					return false;
				}
				else {

					if (getValue(selfCards[2]) > getValue(lastCards[2]))
					{
						return true;
					}
					else 	 if (getValue(selfCards[2]) < getValue(lastCards[2]))
					{
						return false;
					}
					else {

						/////////////花色比较//////////////
						if (getcolor(color1[0]) > getcolor(color2[0]))
						{
							return true;
						}
						else {
							return false;
						}

					}

				}
			}

		}
	}

	//对子
	else  if (lastType == POKER_TYPE_DOUBLE)
	{
		if (selfType == POKER_TYPE_DOUBLE)
		{
		
			if (getValue(selfCards[1]) > getValue(lastCards[1]))
			{

				return true;
			}
			else  if(getValue(selfCards[1]) < getValue(lastCards[1]))
			{
				return false;
			}
			else
			{
				Pair(selfCards, lastCards, color1, color2);
			}
		}
	}
	//顺子
	else  if (lastType == POKER_TYPE_STRAIGHT)
	{
		if (selfType == POKER_TYPE_STRAIGHT)
		{
				vector<int> table(14, 0);
				for (int i = 0; i < selfCards.size(); i++) {
					table[selfCards[i] % 13]++;
				}
				if (table[12] == 1 && table[0] > 0)
				{
					table[13]++;
					table[0]--;
				}
				int idx = -1;
				for (int i = 0; i < 14; i++)
				{
					if (table[i] == 1)
					{
						idx = i;
						break;
					}
				}
				if (idx > lastCards[lastCards.size() - 1])
				{
					return true;
				}
				else if (idx < lastCards[lastCards.size() - 1])
				{
					return false;
				}
				else
				{
                  	/////////////花色比较//////////////
					if (getcolor(color1[2]) > getcolor(color2[2]))
					{
						return true;
					}
					else {
						return false;
					}
				}
			}
	}
	//金花
 else  if (lastType == POKER_TYPE_GOLDEN_FLOWER)
	{
		if (selfType == POKER_TYPE_GOLDEN_FLOWER)
		{
			 if (getcolor(color1[1])>getcolor(color2[1]))
			 {
				 return true;
			 }
			 else   if (getcolor(color1[1])< getcolor(color2[1]))
			 {
				 return false;
			 }
			 else
			 {

				 if (getValue(selfCards[0]) > getValue(lastCards[0]))
				 {
					 return true;
				 }
				 else
				 {
					 return false;
				 }
			 }
		}
	}
	
	//顺金
 else  if (lastType == POKER_TYPE_STRAIGHT_FLUSH)
	{
		if (selfType == POKER_TYPE_STRAIGHT_FLUSH)
		{
			vector<int> table(14, 0);
			for (int i = 0; i < selfCards.size(); i++) {
				table[selfCards[i] % 13]++;
			}
			if (table[12] == 1 && table[0] > 0)
			{
				table[13]++;
				table[0]--;
			}
			int idx = -1;
			for (int i = 0; i < 14; i++)
			{
				if (table[i] == 1)
				{
					idx = i;
					break;
				}
			}
			if (idx > lastCards[lastCards.size() - 1])
			{
				if (getcolor(color1[1]) > getcolor(color2[1]))
				{
					return true;
				}
				else  if (getcolor(color1[1]) < getcolor(color2[1]))
				{
					return false;
				}
				else
				{
					if (getValue(selfCards[0]) > getValue(lastCards[0]))
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				return false;
			}
		}
	}
//豹子
else  if (lastType == POKER_TYPE_LEOPARD)
	{
	if (selfType == POKER_TYPE_LEOPARD)
	{
		if (getValue(selfCards[0]) > getValue(lastCards[0]))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
	return false;
}

int CardGame::shop()
{

	auto player = new Player();
	golds = player->money;
	jewel = player->zuanshi;
	//account = player->account;
	return 1;
}

