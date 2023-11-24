#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <algorithm>
#include "Syntax_Analyzator.h"
#include "Lexical_Analyzator.h"

using namespace std;

// ф-я которая запустит работу лексического анализатора
void Work_of_Lexical_Analyzator()
{
    // открываем файл с текстом
    ifstream input("input.txt");

    // переменная, в которой будем весь наш текст
    string Input_text_from_file = "";

    // Создаём объект: лексический анализатор
    Lexical_Analyzator Lex_Analyzator;

    // считываем входной файл с прогой
    while (getline(input, Input_text_from_file))
    {

        Lex_Analyzator.Add_new_tokens(Input_text_from_file);
        // Lex_Analyzator.hash_tab.Adding_new_Word_in_Table(s);
    }

    // добавляем токены в хэш
    for (auto s : Lex_Analyzator.Our_Tokens)
    {
        Lex_Analyzator.hash_tab.Adding_new_Word_in_Table(s);
    }

    // открываем файл для записи тех лексем, которые были считаны в проге
    ofstream output("output.txt");

    // бежим по хэшу
    for (int i = 0; i < Lex_Analyzator.hash_tab.hash_table.size(); ++i)
    {
        // без & здесь не работает - т.е. мы к указательному объекту
        // сразу передаём оригинально
        // результат Lex_Analyzator.hash_tab.hash_table[i];
        Node* Current_Node = &Lex_Analyzator.hash_tab.hash_table[i];

        if (Current_Node->Information_about_current_node.Type_of_Token != "mb" && Current_Node->Information_about_current_node.Name_of_Token != "bn")
        {

            if (Current_Node->right_son == nullptr)
            {
                output << "(" << Current_Node->Information_about_current_node.Type_of_Token << ": " << Current_Node->Information_about_current_node.Name_of_Token << " )"
                    << " " << i << "\n";
            }
            else
            {
                vector<string> Already_Names;

                output << "(" << Current_Node->Information_about_current_node.Type_of_Token << ": ";
                output << Current_Node->Information_about_current_node.Name_of_Token;
                Already_Names.push_back(Current_Node->Information_about_current_node.Name_of_Token);

                if (Current_Node->right_son != nullptr)
                {
                    while (Current_Node->right_son != nullptr)
                    {
                        bool flag = false;
                        for (int j = 0; j < Already_Names.size(); ++j)
                        {
                            if (Current_Node->Information_about_current_node.Name_of_Token == Already_Names[j])
                            {
                                flag = true;
                            }
                        }
                        if (flag == false)
                        {
                            output << Current_Node->Information_about_current_node.Name_of_Token;
                            if (Current_Node->right_son != nullptr)
                            {
                                output << " | ";
                            }
                        }
                        Current_Node = Current_Node->right_son;
                    }
                }
                output << " ) " << i << "\n";
            }
        }
        else
        {
            continue;
        }
    }

    // закрываем файлы
    input.close();
    output.close();
}

/*
// ф-я для  работы синтаксического анализатора
void Work_of_Syntax_Analyzator()
{
    // входной файл
    ifstream input("input.txt");

    // стриговая переменная с нашим текстом в файле
    string our_text = "";

    Syntax_Analyzator anal;

    anal.Tree_of_parse.push_back(Node("Program"));

    // Node r("PROGRAM A");

    // auto p = anal.get_Praser().parse(r);

    while (getline(input, our_text))
    {
        anal.p.parse(anal.Tree_of_parse[0], our_text);
        anal.Tree_of_parse[0].print(0);
        cout << "\n\n";
    }

    anal.Tree_of_parse[0].print(0);

    // anal.Tree_of_parse.push_back(Node("Program"));

    /*
    Node root("Program");

    getline(input, our_text);

    Parser p(our_text);



    root.print(0);*/

    /*
    //пока не дошли до конца файла - считываем
    while (getline(input, our_text)) {

    }
    }*/

int main()
{
    // ф-я для запуска работы лексическоо анализатора
    // Work_of_Lexical_Analyzator();

    // ф-я для запуска работы синтаксического анализатора
    // Work_of_Syntax_Analyzator();

    Work_of_Lexical_Analyzator();

    return 0;
}