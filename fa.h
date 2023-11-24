#pragma once
#include <string>
#include <vector>
#include "TOKEN_ELEM.h"

using namespace std;

// ����� ��������� ��������, ������� ����� ��������� �����
class FA
{
private:
public:
	// ������ ������������ ������
	vector<char> Operations_Symbols = {'=', '+', '-'};

	// ������ ��������, ������� �� �������� �������������
	//(�������� ",")
	vector<char> Not_Operations_Symbols = {',', '(', ')'};

	// ������ �������� ����
	vector<string> KeyWords = {"INTEGER", "REAL", "PROGRAM", "END",
							   "RTOI", "ITOR"};

	// �-� ��������, � ������� ����� �������� ���������, �� ������� �����
	// ����� ����������
	vector<vector<int>> TransitFunction;

	// ����������� ��������� ��������
	FA();

	// ������� ������������ ������ �������, ������� ���� �������
	vector<TOKEN_ELEM> Get_Vector_Tokens(string &str);
	// TOKEN_ELEM Get_Vector_Tokens(string &str);
};