#pragma once
#include "Hash_Table.h"
#include <vector>
// ����� ������������ �����������
class Lexical_Analyzator
{
private:
public:
	// ����������� ����. �����������
	Lexical_Analyzator();

	// ���� ��� �������
	Hash_Table hash_tab;

	// ������ �������
	vector<TOKEN_ELEM> Our_Tokens;

	// �-� ���������� ������� �� �����
	void Add_new_tokens(string &str_name);
};