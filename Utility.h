#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // sort
#include <ctime> // time
#include <random> // mt19937
#include <functional> // bind
#include <cmath> // rqrt, pow, ceil
#include <time.h> //tm
#include <stdarg.h> // format_string() - va_start, va_end

using namespace std;

void swap(int& a, int& b)
{
	int address = a;
	a = b;
	b = address;
}

int Char2Int(char c)
{
	return c - '0';
}

char Int2Char(int i)
{
	return i + '0';
}

auto randomGenerator(int min, int max)
{
	mt19937 engine((unsigned int)time(NULL));
	uniform_int_distribution<int> distribution(min, max);
	return bind(distribution, engine);
}

string reverseStr(string str)
{
	string result = "";

	for (int i = str.length() - 1; i >= 0; i--)
	{
		result += str[i];
	}

	return result;
}

string stringSum(string a, string b)
{
	if (a == "" && b == "")
		return "Error";

	if (a == "")
		return b;

	if (b == "")
		return a;

	string result = "";

	string tempUp = "";
	string tempDown = ""; 
	if (a.length() >= b.length())
	{
		tempUp = reverseStr(a);
		tempDown = reverseStr(b);
	}
	else
	{
		tempUp = reverseStr(b);
		tempDown = reverseStr(a);
	}
	
	int i = 0;
	int tempIntUp = 0;
	int tempIntDown = 0;
	int tempSum = 0;
	int tempCarry = 0;
	for (; i < tempDown.length(); i++)
	{
		tempIntUp = Char2Int(tempDown[i]);
		tempIntDown = Char2Int(tempUp[i]);

		tempSum = tempIntUp + tempIntDown + tempCarry;

		tempCarry = tempSum / 10;
		result += Int2Char(tempSum % 10);
	}
	int gap = tempUp.length() - tempDown.length();
	if (gap > 0)
	{
		int tempLoop = gap + i;
		for ( ; i<tempLoop; i++)
		{
			tempIntUp = Char2Int(tempUp[i]);
			result += Int2Char(tempIntUp + tempCarry);
			tempCarry = 0;
		}
	}
	else if (tempCarry > 0)
	{
		result += Int2Char(tempCarry);
	}	

	return reverseStr(result);
}

bool sortFunc(int& a, int& b)
{
	return a < b;
}

bool sortFunction(int& a, int& b)
{
	return a > b;
}

int getDistance(pair<int, int>& sPos, pair<int, int>& dPos)
{
	// 이동 거리 계산
	int x = abs(sPos.first - dPos.first);
	int y = abs(sPos.second - dPos.second);
	return x + y - 1; // 만나기만 하면되니까 1 빼기
}

vector<string> split(string str, char deli)
{
	int startPos = 0;
	int findPos = 0;
	vector<string> result;

	while (startPos < str.size())
	{
		findPos = str.find(deli, startPos);
		string tmp_str;

		if (findPos == string::npos)
		{
			// for last token
			findPos = str.size();
			tmp_str = str.substr(startPos, findPos - startPos);
			result.push_back(tmp_str);
			break;
		}
		tmp_str = str.substr(startPos, findPos - startPos);
		result.push_back(tmp_str);
		startPos = findPos + 1;
	}

	return result;
}

int getMilliSecond(int hour, int min, int sec, int milli)
{
	int rMin = (hour * 60) + min;
	int rSec = (min * 60) + sec;
	int rMilli = (sec * 1000) + milli;
	
	return rMilli;
}

void convertMS2Time(int value, int& hour, int& min, int& sec, int& ms)
{
	ms = value % 1000;
	sec = value / 1000;
	
	min = sec / 60;
	sec = sec % 60;

	hour = min / 60;
	min = min & 60;
}

std::string format_string(const std::string fmt, ...) {
	int size = ((int)fmt.size()) * 2;
	std::string buffer;
	va_list ap;
	while (1) {
		buffer.resize(size);
		va_start(ap, fmt);
		int n = vsnprintf((char*)buffer.data(), size, fmt.c_str(), ap);
		va_end(ap);
		if (n > -1 && n < size) {
			buffer.resize(n);
			return buffer;
		}
		if (n > -1)
			size = n + 1;
		else
			size *= 2;
	}
	return buffer;
}

string getTimeStr(int hour, int min, int sec, int ms)
{
	string result = "";

	result += to_string(hour);
	result += ":";
	result += to_string(min);
	result += ":";
	result += to_string(sec);
	result += ".";
	result += to_string(ms);

	//result += format_string("%d:%d:%d.%d", hour, min, sec, ms);
	
	return result;
}

// 재귀함수 - 우박수
void ookParkSu(int inputNum)
{
	if (inputNum == 1)
	{
		cout << inputNum << endl;
		return;
	}

	// 정방향 출력
	cout << inputNum << endl;

	if (inputNum % 2 == 1)
	{
		// 홀수 (3n + 1)
		ookParkSu(inputNum * 3 + 1);
	}
	else
	{
		// 짝수 (n / 2)
		ookParkSu(inputNum / 2);
	}
	
	// 역방향 출력
	//cout << inputNum << endl;
}

int permutation(vector<int>& vecInt, int pick)
{
	reverse(vecInt.begin() + pick, vecInt.end());
	return next_permutation(vecInt.begin(), vecInt.end());
}

void eraseVecValue(vector<int>& vecInt, int value)
{
	for (int i = 0; i < vecInt.size(); i++)
	{
		if (value == vecInt[i])
		{
			vecInt.erase(vecInt.begin()+i);
			i--;
		}
	}
}

/*
int solution(int inputNum)
{
	if (inputNum % 5 == 0)
	{
		return inputNum / 5;
	}
	else
	{
		solution(inputNum - 5);
	}
}
*/

