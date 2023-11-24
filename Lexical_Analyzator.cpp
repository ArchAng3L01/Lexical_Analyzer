
#include "Lexical_Analyzator.h"
#include "fa.h"

// ����������� ����. �����������
Lexical_Analyzator::Lexical_Analyzator(){

};

// �-� ���������� ������� �� ��� � ����. ����������
void Lexical_Analyzator::Add_new_tokens(string &str_name)
{
	// �������������� ���
	FA fa;

	// ����. ������ �������
	vector<TOKEN_ELEM> Tokens_are_we_have = fa.Get_Vector_Tokens(str_name);

	for (auto s : Tokens_are_we_have)
	{
		Our_Tokens.push_back(s);
	}
}