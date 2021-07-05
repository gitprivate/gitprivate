#include "Utility.h"

vector<pair<int, int>> vecMyTer;

vector<int> checkBricks;

bool isHaveSamePoint(vector<pair<int, int>> vec, int x, int y)
{
	for (int i = 0; i < vec.size(); i++)
	{
		// 이미 지나간 길은 패스
		if (vec[i].first == x
			&& vec[i].second == y)
		{
			return true;
		}
	}
	
	return false;
}

void floodFill(vector<vector<int>>& maps, int x, int y)
{
	if (x < 0 || x > 4)
		return;

	if (y < 0 || y >= maps.size())
		return;

	if (maps[y][x] == 1)
	{
		if (isHaveSamePoint(vecMyTer, x, y))
			return;

		vecMyTer.push_back(make_pair(x, y));

		// 우리땅 처리
		floodFill(maps, x - 1, y);
		floodFill(maps, x + 1, y);
		floodFill(maps, x, y - 1);
		floodFill(maps, x, y + 1);
	}
	else
	{
		// 아님 처리
		return;
	}
}

bool isDropable(vector<int> bricks, int curHeight, int x, int& count, vector<int>& checkBricks)
{
	// 왼쪽
	bool isLeftOkey = false;
	for (int i = x - 1; i >= 0; i--)
	{
		if (bricks[i] >= curHeight)
		{
			isLeftOkey = true;
			break;
		}
		count++;
	}

	if (isLeftOkey == false)
		return false;
	
	// 오른쪽
	bool isRightOkey = true;
	for (int i = x + 1; i < bricks.size(); i++)
	{
		if (bricks[i] >= curHeight)
		{
			isRightOkey = true;
			break;
		}
		count++;
	}

	return isRightOkey;
}

int main(void)
{
	cout << "---------------" << endl;
	cout << "<Test>" << endl;

	vector<int> bricks = { 0,2,0,1,3,1,2,0,1,0,2,0 };

	int maxHeight = 0;
	for (auto it : bricks)
	{
		maxHeight = it > maxHeight ? it : maxHeight;
	}

	int curHeight = 1;
	int answer = 0;
	while (curHeight <= maxHeight)
	{
		vector<int> checkBricks;
		for (int x = 0; x < bricks.size(); x++)
		{
			if (bricks[x] < curHeight)
			{
				// 낮은 위치를 찾았으면 좌우로 벽을 찾는다
				int tempCount = 0;
				if (isDropable(bricks, curHeight, x, tempCount, checkBricks))
				{
					answer += tempCount;

					answer++;
				}
			}
		}

		curHeight++;
		checkBricks.clear();
	}

	cout << answer << endl;


	/*
	cout << "Hello, World!!" << endl;

	cout << "---------------" << endl;
	cout << "<Swap>" << endl;

	int a = 3;
	int b = 5;
	cout << a << ", " << b << endl;
	
	swap(a, b);

	cout << a << ", " << b << endl;

	cout << "---------------" << endl;
	cout << "<Char <-> Integer>" << endl;

	char c = 'a';
	cout << Char2Int(c) << endl;

	int i = 49;
	cout << Int2Char(i) << endl;

	string str = to_string(i);
	cout << str << endl;

	cout << "---------------" << endl;
	cout << "<Random>" << endl;

	int randomMin = 0;
	int randomMax = 20;
	int randomLen = 5;
	auto randomGen = randomGenerator(randomMin, randomMax);
	vector<int> vecRInt;
	for (int i=0; i<randomLen; i++)
	{
		vecRInt.push_back(randomGen());
	}
	for (auto it = vecRInt.begin(); it != vecRInt.end(); it++)
	{
		cout << *it;
		if (it != vecRInt.end() - 1)
			cout << ", ";
	}
	cout << endl;

	cout << "---------------" << endl;
	cout << "<Lamda Sort>" << endl;

	sort(vecRInt.begin(), vecRInt.end()
		, [](auto a, auto b)
		{
			return a > b;
		}
		);
	for (auto it = vecRInt.begin(); it != vecRInt.end(); it++)
	{
		cout << *it;
		if (it != vecRInt.end()-1)
			cout << ", ";
	}
	cout << endl;

	cout << "---------------" << endl;
	cout << "<Common Func Sort>" << endl;

	sort(vecRInt.begin(), vecRInt.end(), sortFunc);

	for (auto it = vecRInt.begin(); it != vecRInt.end(); it++)
	{
		cout << *it;
		if (it != vecRInt.end() - 1)
			cout << ", ";
	}
	cout << endl;

	cout << "---------------" << endl;
	cout << "<Vector Find, Erase>" << endl;

	int findTarget = randomGen();
	auto f = find(vecRInt.begin(), vecRInt.end(), findTarget);
	if (f != vecRInt.end())
	{
		vecRInt.erase(f);
		cout << "erase : " << findTarget << endl;
	}
	else
	{
		cout << "not found : " << findTarget << endl;
	}
	for (auto it = vecRInt.begin(); it != vecRInt.end(); it++)
	{
		cout << *it;
		if (it != vecRInt.end() - 1)
			cout << ", ";
	}
	cout << endl;

	cout << "---------------" << endl;
	cout << "<String Find, Erase>" << endl;

	string strFind = "i'm a boy, you're a girl.";
	string delStr = "a";
	auto strPos = strFind.find(delStr, 5);
	if (strPos != string::npos)
	{
		strFind = strFind.erase(strPos, delStr.length());
		cout << "erase : " << (int)strPos << endl;
	}
	else
	{
		cout << "not found" << (int)strPos << endl;
	}
	cout << strFind << endl;
	
	cout << "---------------" << endl;
	cout << "<Reverse String>" << endl;

	string reverse = "abcde";
	cout << reverse << endl;
	cout << reverseStr(reverse) << endl;

	cout << "---------------" << endl;
	cout << "<String Sum>" << endl;
	
	auto strSumLenGen = randomGenerator(1, 3);
	auto strSumValGen = randomGenerator(0, 3);

	int strA_len = strSumLenGen();
	int strB_len = strSumLenGen();
	string strA = "";
	string strB = "";
	for (int i = 0; i < strA_len; i++)
	{
		strA += Int2Char(strSumValGen());
	}
	cout << "before StrA : " << strA << endl;
	while (strA[0] == '0')
	{
		strA = strA.erase(0, 1);
	}
	for (int i = 0; i < strB_len; i++)
	{
		strB += Int2Char(strSumValGen());
	}
	cout << "before StrB : " << strB << endl;
	while (strB[0] == '0')
	{
		strB = strB.erase(0, 1);
	}
	cout << "strA(" << strA_len << ") : " << strA << endl;
	cout << "strB(" << strB_len << ") : " << strB << endl;
	cout << "result : " << stringSum(strA, strB) << endl;

	cout << "---------------" << endl;
	cout << "<Recursive Function>" << endl;

	ookParkSu(5);

	cout << "---------------" << endl;
	cout << "<Permutation>" << endl;
	*/

	/*
	vector<int> vecInt;
	vector<int>::iterator vecIntIt;

	int pN = 15;
	int pPick = 5;

	for (int i = 1; i <= pN; i++)
	{
		vecInt.push_back(i);
	}

	while (true)
	{
		for (int i = 0; i < pPick; i++)
		{
			cout << vecInt[i] << " ";
		}
		cout << endl;

		if (permutation(vecInt, pPick) == false)
			break;
	}
	*/

	
	
	
	return 0;
}
