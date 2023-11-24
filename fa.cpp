
#include <iostream>
#include "fa.h"
// #include "Lexical_Analyzator.h"

using namespace std;

// ����������� ��������� ��������
FA::FA()
{
	// �������������� ������� ���� �������: ������� 4 ���������(������� �������)
	// ������������, ��� ������������ �� �����
	// ������� ������ � ������������ ���������
	//(��������� ������), � ��������� �� ���������, �� ������� �� ����� ����������
	TransitFunction = vector<vector<int>>(4, vector<int>(1024, 3));

	// ������� � ����� ��������� ����� ������� �� �����:
	// 1) ���� �� �������� ��������� ��� �� ����� => �������� � ������
	// ���������
	// 2) ���� �� ������� ���������(���������) ��� �� ����� =>
	// �������� � ������ ���������
	// 3) ���� �� ������� ��������� (���������) ��� �� ����� =>
	// �� ����� - �������� � ������������� ������ ���������
	for (int i = '0'; i <= '9'; ++i)
	{
		TransitFunction[0][i] = 1;
		TransitFunction[1][i] = 1;
		TransitFunction[2][i] = 3;
	}

	// ���������� � ����������� ��� ����
	for (int i = 'a'; i <= 'z'; ++i)
	{
		TransitFunction[0][i] = 2;
		TransitFunction[1][i] = 3;
		TransitFunction[2][i] = 2;
	}

	for (int i = 'A'; i <= 'Z'; ++i)
	{
		TransitFunction[0][i] = 2;
		TransitFunction[1][i] = 3;
		TransitFunction[2][i] = 2;
	}

	// ������������, ��� �� ����� �� �� �������� ��������, ��
	// ���� � ����� ����� �������� ����, �� ��� ����� ������������ ��� ������������
	TransitFunction[0][(int)('.')] = 1;
	TransitFunction[1][(int)('.')] = 1;
	TransitFunction[2][(int)('.')] = 3;
};

// �������� �������� �������� ���������� ������� �� ������ ��������
//(���� ������ �������� => ������ ������)
bool Do_we_get_Operation_Symbol(
	char c, string &str,
	vector<TOKEN_ELEM> &Possible_Tokens, vector<char> &Operat_Symb,
	vector<string> &KeyWords, int &current_state)
{

	// ������ ����, ������� �������, �������� ��
	// ��� ������ - �������� ��������
	bool flag = false;

	for (auto Op_S : Operat_Symb)
	{
		if (c == Op_S && Op_S == '=')
		{
			// ������ ����� �����
			TOKEN_ELEM new_token;

			// ������, ���� ������� ��� ������ ��������
			//(�.�. ������������, ��� ������� ������ �������� � ������� �� ������
			//) => ������ ��������
			// ���� ���� �� ������� ����������
			current_state = 0;
			str = "";
			new_token.Type_of_Token = "Assign_Operation";
			new_token.Name_of_Token = c;
			Possible_Tokens.push_back(new_token);
			flag = true;
		}
		else if (c == Op_S && Op_S == '+')
		{
			TOKEN_ELEM new_token;

			current_state = 0;
			str = "";
			new_token.Type_of_Token = "Plus_Operation";
			new_token.Name_of_Token = c;
			Possible_Tokens.push_back(new_token);
			flag = true;
		}
		else if (c == Op_S && Op_S == '-')
		{
			TOKEN_ELEM new_token;

			current_state = 0;
			str = "";
			new_token.Type_of_Token = "Minus_Operation";
			new_token.Name_of_Token = c;
			Possible_Tokens.push_back(new_token);
			flag = true;
		}
	}
	if (flag)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// �-� ��������, �������� �� ��� ������ �� ������������
bool Do_we_get_not_oper_symb(
	char c, string &str,
	vector<TOKEN_ELEM> &Possible_Tokens, vector<char> &N_Operat_Symb,
	vector<string> &KeyWords, int &current_state)
{

	// ������ ����, ������� �������, �������� ��
	// ��� ������ - �������� ����������
	bool flag = false;

	for (auto N_Op_S : N_Operat_Symb)
	{
		if (c == N_Op_S && N_Op_S == ',')
		{
			// ������ ����� �����
			TOKEN_ELEM new_token;

			// ������, ���� ������� ��� ������ ��������
			//(�.�. ������������, ��� ������� ������ �������� � ������� �� ������
			//) => ������ ��������
			// ���� ���� �� ������� ����������
			current_state = 0;
			str = "";
			new_token.Type_of_Token = "Comma";
			new_token.Name_of_Token = c;
			Possible_Tokens.push_back(new_token);
			flag = true;
		}
		else if (c == N_Op_S && N_Op_S == '(')
		{

			TOKEN_ELEM new_token;

			current_state = 0;
			str = "";
			new_token.Type_of_Token = "Left_Bracket";
			new_token.Name_of_Token = c;
			Possible_Tokens.push_back(new_token);
			flag = true;
		}
		else if (c == N_Op_S && N_Op_S == ')')
		{
			TOKEN_ELEM new_token;

			current_state = 0;
			str = "";
			new_token.Type_of_Token = "Right_Bracket";
			new_token.Name_of_Token = c;
			Possible_Tokens.push_back(new_token);
			flag = true;
		}
	}
	if (flag)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
// for determine which TOKEN_ELEM we are get on current step
TOKEN_ELEM FA::Get_Vector_Tokens(string &str)
{

	// current state, from where we're start
	int current_state = 0;

	// line with reading words
	string s = "";

	for (auto d : str)
	{
		// ������� ������������: ��� ������ ������ �������� �� ������������
		if (Do_we_get_not_oper_symb(d, s, Our_Tokens,
									Not_Operations_Symbols, KeyWords, current_state))
		{
			continue;
		}
		if (Do_we_get_Operation_Symbol(d, s, Our_Tokens,
									   Operations_Symbols, KeyWords, current_state))
		{
			continue;
		}
		if (d == ' ' || d == '\t')
		{
			TOKEN_ELEM new_token;
			if (current_state == 2)
			{
				new_token.Type_of_Token = "Id";

				for (auto k : KeyWords)
				{
					if (s == k)
					{
						new_token.Type_of_Token = "KeyWord";
					}
				}
				new_token.Name_of_Token = s;
				Our_Tokens.push_back(new_token);

				return new_token;
			}
			if (current_state == 1)
			{
				bool flag = false;
				for (int i = 0; i < s.size(); ++i)
				{
					if (s[i] == '.')
					{
						flag = true;
					}
				}
				if (flag)
				{
					new_token.Type_of_Token = "RealConst";
					new_token.Name_of_Token = s;
				}
				else
				{
					new_token.Type_of_Token = "Const";
					new_token.Name_of_Token = s;
				}
				Our_Tokens.push_back(new_token);
			}
			if (current_state == 3)
			{
				new_token.Type_of_Token = "ERROR";
				new_token.Name_of_Token = s;
				Our_Tokens.push_back(new_token);
			}
			current_state = 0;
			s = "";
		}
		else
		{
			current_state = TransitFunction[current_state][d];
			s += d;
		}
	}

	// ���� ����� ���� ����������� �� ��������� �� � �������,
	// �.�. �� ��� �� �� ������� => ������������ ���
	if (current_state != 0)
	{
		TOKEN_ELEM new_token;
		if (current_state == 2)
		{
			new_token.Type_of_Token = "Id";

			for (auto k : KeyWords)
			{
				if (s == k)
				{
					new_token.Type_of_Token = "KeyWord";
				}
			}
			new_token.Name_of_Token = s;
			Our_Tokens.push_back(new_token);
		}
		if (current_state == 1)
		{
			bool flag = false;
			for (int i = 0; i < s.size(); ++i)
			{
				if (s[i] == '.')
				{
					flag = true;
				}
			}
			if (flag)
			{
				new_token.Type_of_Token = "RealConst";
				new_token.Name_of_Token = s;
			}
			else
			{
				new_token.Type_of_Token = "Const";
				new_token.Name_of_Token = s;
			}
			Our_Tokens.push_back(new_token);
		}
		if (current_state == 3)
		{
			new_token.Type_of_Token = "ERROR";
			new_token.Name_of_Token = s;
			Our_Tokens.push_back(new_token);
		}
	}
}*/



// �-� ������������ ������ �������
vector<TOKEN_ELEM> FA::Get_Vector_Tokens(string &str)
{
	// ������ ������ �������, �������� � ������� �������� ������ ������
	vector<TOKEN_ELEM> Our_Tokens;

	// ����� ������� ��������� ����� ����, � ���� ��� ������ �� �������
	int current_state = 0;

	// ������, � ������� ����� ����������� �����, �������������� ���������
	//(������� �� �������� ����������)
	string s = "";

	for (auto d : str)
	{
		// ������� ������������: ��� ������ ������ �������� �� ������������
		if (Do_we_get_not_oper_symb(d, s, Our_Tokens,
									Not_Operations_Symbols, KeyWords, current_state))
		{
			continue;
		}
		if (Do_we_get_Operation_Symbol(d, s, Our_Tokens,
									   Operations_Symbols, KeyWords, current_state))
		{
			continue;
		}
		if (d == ' ' || d == '\t')
		{
			TOKEN_ELEM new_token;
			if (current_state == 2)
			{
				new_token.Type_of_Token = "Id";

				for (auto k : KeyWords)
				{
					if (s == k)
					{
						new_token.Type_of_Token = "KeyWord";
					}
				}
				new_token.Name_of_Token = s;
				Our_Tokens.push_back(new_token);

				// return new_token;
			}
			if (current_state == 1)
			{
				bool flag = false;
				for (int i = 0; i < s.size(); ++i)
				{
					if (s[i] == '.')
					{
						flag = true;
					}
				}
				if (flag)
				{
					new_token.Type_of_Token = "RealConst";
					new_token.Name_of_Token = s;
				}
				else
				{
					new_token.Type_of_Token = "Const";
					new_token.Name_of_Token = s;
				}
				Our_Tokens.push_back(new_token);
			}
			if (current_state == 3)
			{
				new_token.Type_of_Token = "ERROR";
				new_token.Name_of_Token = s;
				Our_Tokens.push_back(new_token);
			}
			current_state = 0;
			s = "";
		}
		else
		{
			current_state = TransitFunction[current_state][d];
			s += d;
		}
	}

	// ���� ����� ���� ����������� �� ��������� �� � �������,
	// �.�. �� ��� �� �� ������� => ������������ ���
	if (current_state != 0)
	{
		TOKEN_ELEM new_token;
		if (current_state == 2)
		{
			new_token.Type_of_Token = "Id";

			for (auto k : KeyWords)
			{
				if (s == k)
				{
					new_token.Type_of_Token = "KeyWord";
				}
			}
			new_token.Name_of_Token = s;
			Our_Tokens.push_back(new_token);
		}
		if (current_state == 1)
		{
			bool flag = false;
			for (int i = 0; i < s.size(); ++i)
			{
				if (s[i] == '.')
				{
					flag = true;
				}
			}
			if (flag)
			{
				new_token.Type_of_Token = "RealConst";
				new_token.Name_of_Token = s;
			}
			else
			{
				new_token.Type_of_Token = "Const";
				new_token.Name_of_Token = s;
			}
			Our_Tokens.push_back(new_token);
		}
		if (current_state == 3)
		{
			new_token.Type_of_Token = "ERROR";
			new_token.Name_of_Token = s;
			Our_Tokens.push_back(new_token);
		}
	}

	return Our_Tokens;
}