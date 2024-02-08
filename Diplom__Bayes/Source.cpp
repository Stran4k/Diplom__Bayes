#include <iostream>
#include "windows.h"
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <functional>
#include <regex>
#include <unordered_set>



using namespace std;

string Corrector(string doc)
{                                           // ��������� ��������� ���� �� �������� � �������� ������ ����������
    vector <char> Punctuation_Marks = { '?', '!', '.', ',', '-', '"', ';', ':', '{', '}', '[', ']', '~', '<', '>', '�', '(', ')', '%', '�', '�', '�', '+', '$', '/', '�', '�' };

    vector <string> �apital_Letters = { "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�" };
    vector <char> Lowercase_Letters = { '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�','M', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�' };
    vector <char> numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };


    for (int q = 0; q < 9; q++) {
        for (int i = 0; i <= doc.length(); i++) {

            for (int u = 0; u <= Lowercase_Letters.size() - 1; u++) {

                if (doc[i] == Lowercase_Letters[u]) {

                    doc.replace(i, 1, �apital_Letters[u]);

                }

            }
            for (int u = 0; u <= Punctuation_Marks.size() - 1; u++) {

                if (doc[i] == Punctuation_Marks[u]) {

                    doc.replace(i, 1, "");

                }

            }
            for (int u = 0; u <= numbers.size() - 1; u++) {

                if (doc[i] == numbers[u]) {

                    doc.replace(i, 1, "");

                }

            }
        }
    }
    return doc;
}


string Anti_stop_word(string doc, string docAnti)  // �������� ����-����
{
    string word_A;
    vector<string> DocA;
    for (unsigned long long int i = 0; i < docAnti.length(); i++) {
        if (docAnti[i] != ' ' and docAnti[i] != '\n')
        {

            word_A += docAnti[i];

        }
        else {
            DocA.push_back(word_A);
            if (i < docAnti.length() + 1)
                word_A.clear();
        }
    }
    DocA.push_back(word_A);

    string word_D;
    vector<string> Doc;
    for (unsigned long long int i = 0; i < doc.length(); i++) {
        if (doc[i] != ' ' and doc[i] != '\n') {
            word_D += doc[i];
        }
        else {
            Doc.push_back(word_D);
            if (i < doc.length() + 1)
                word_D.clear();
        }
    }
    Doc.push_back(word_D);

    for (int q = 0; q < 9; q++)
    {
        for (unsigned long long int i = 0; i < DocA.size() - 1; i++)
        {
            for (unsigned long long int j = 0; j < Doc.size() - 1; j++)
            {
                if (Doc[j] == "-") {
                    Doc[j] = "";
                }

                if (Doc[j] == DocA[i])
                {
                    Doc[j] = "";
                    break;
                }
            }
        }
    }



    string s;
    for (const auto& piece : Doc) s += piece + ' ';
    return s;
}

string Stemming(string doc)
{
    // �����
    vector <string> �apital_Letters = { "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�",
                                                                                     "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�" };

    //�������
    vector <string> vowels = { "�", "�", "�", "�", "�", "�", "�", "�", "�" };

    // ������������     ERFECTIVE_GERUND
    vector <string>  Adverbial_Participle1 = { "��", "����","������" };
    vector <string>  Adverbial_Participle12 = { "��", "����","������" };
    vector <string>  Adverbial_Participle2 = { "��", "����","������", "��", "����","������" };
    //��������� ������ 1 ������ ��������� �� � ��� � 

// ��������������
    vector <string> Adjective = { "��","��","��","���","���",  "��","��","��", "��", "��",  "��","��","��", "��", "���",   "���", "���", "���", "��", "��",
                                                                                                                            "��", "��", "��", "��", "��", "��" };

    // ���������
    vector <string> Participle1 = { "���", "���", "���", "���", "��" };
    vector <string> Participle12 = { "���", "���", "���", "���", "��" };

    vector <string> Participle2 = { "���", "���", "���" };
    //��������� ������ 1 ������ ��������� �� � ��� � 

// ������������
    vector <string> Reflexive = { "��", "��" };

    // �������
    vector <string> Verb1 = { "���", "���", "����", "����", "���", "��", "��", "���", "��", "���", "���", "���", "���", "���", "���", "����", "����" };
    vector <string> Verb12 = { "���", "���", "����", "����", "���", "��", "��", "���", "��", "���", "���", "���", "���", "���", "���", "����", "����" };

    vector <string> Verb2 = { "���", "���", "���", "����", "����", "���", "���", "���", "��", "��", "��", "��", "��", "��", "��", "���", "���", "���",
                                                                                           "��", "���", "���", "��", "��", "���", "���", "���", "���", "��", "�" };
    //��������� ������ 1 ������ ��������� �� � ��� � 

    // ���������������
    vector <string> Noun = { "�", "��", "��", "��", "��", "�", "����", "���", "���", "��", "��", "�", "���", "��", "��", "��", "�", "���", "��", "���",  "��",
                                                                                     "��", "��", "�", "�", "��", "���", "��", "�", "�", "��", "��", "�", "��", "��", "�" };

    // ������������ ������� 
    vector <string> super_Lative = { "���", "����" };

    // ����������� ��������� ��������������� � ���������������
    vector <string> Derivatijnal = { "���", "����", "���", "���", "���", "����" };

    //� ����� ���� ��� ������� 1 ������� � ������� 3 ����� 
    // ���� �� ������� 1 �
    // ����� >2 ����
    string word_D;
    vector<string> Doc;
    for (unsigned long long int i = 0; i < doc.length(); i++) {
        if (doc[i] != ' ' and doc[i] != '\n') {
            word_D += doc[i];
        }
        else {
            Doc.push_back(word_D);
            if (i < doc.length() + 1)
                word_D.clear();
        }
    }
    Doc.push_back(word_D);


    // +     ���  -1-
                // 
                // 
                // ����������� ���������-������������
                // ���� ����� �� ������ ��������� 1                    +
                // ��������� 12                                        +
                // ���� ����� ��������� 2 �� �����������               +
                // ��������� 2                                         +
                //
                // ���� ��������� ����������� �������� ���� ������     +
                // 
                // ��������� ��������������                            +
                //   ��������������                                    +
                //   ������                                            +
                //   ���������������                                   +
                // 
                // 
                // +      ���  -2-
                // 
                // 
                // ���� ���� "�" ������� ��                            +
                // 
                // 
                // +     ���  -3-
                //
                //  
                // ���� ���� ������������� ������� ��                  +
                // 
                // 
                //      ���  -4-
                // 
                // 
                //  1 ���� ���� "��" �� ������� "1" "�"                                   +
                //  2 ������������ ������� ���� �� �� ������� � ������ "�"                +
                //  3  "�" ������� ���
                // 
                // ��� �������� �� ����� ����� (�� ���������)-
                // 
                // +     ����� ��� �������� �� ������ ���� ����� �������� ��� ��������    +



    // ����� ������� ���� ���������                                                                 /// ����� ���������� ������ ����� � �� ������� �
                                                                                                    /// ������� ����� �� ����� �� � ��� ������ �������� �� ������� ��������


    for (unsigned long long int i = 0; i < Doc.size() - 1; i++)
    {
        bool ToF = false;
        string word = Doc[i];
        if (word.size() >= 3)
        {


            for (unsigned k = vowels.size(); k != 0; ) // �������� �� ������� �������
            {
                k--;
                if (word.find(vowels[k]) != string::npos)
                {
                    ToF = true;
                    break; // ������� �������, ������� ��������

                }


                if (ToF == true) break;
            }



            if (ToF == true)
            {
                int Steper = 0;
                int StepP = 0;
                int Step = 0;                                     //  ���
                int number_Ap1[3]{ 0,0,0 };

                for (unsigned k = 0; k < 3; k++)                                       // 1 ������������  
                {
                    if (word.rfind(Adverbial_Participle1[k]) != string::npos)
                    {
                        number_Ap1[k] = Adverbial_Participle1[k].size();

                        Step = 1;
                    }

                }
                if (Step == 1)
                {
                    int l = 0;
                    int lengf[4]{ 0, 0, 0,0 };
                    int index[4]{ 0, 0, 0,0 };
                    for (int n = 0; n < 3; n++)
                    {
                        if (number_Ap1[n] != 0)
                        {
                            if (number_Ap1[n] > lengf[3]) {
                                lengf[l] = number_Ap1[n];
                                index[l] = n;
                                l += 1;
                            }
                        }

                    }
                    for (int m = 0; m <= l; m++)
                    {
                        int l = 0;
                        int lengf[3]{ 0, 0, 0 };
                        int index[3]{ 0, 0, 0 };
                        for (int n = 0; n < 2; n++)
                        {
                            if (number_Ap1[n] != 0)
                            {
                                if (number_Ap1[n] > lengf[2]) {
                                    lengf[l] = number_Ap1[n];
                                    index[l] = n;
                                    l += 1;
                                }
                            }

                        }
                        for (int m = 0; m != l; m++)
                        {
                            string word1;
                            word1 = word.substr(0, word.rfind(Adverbial_Participle1[index[m]]));

                            bool ToFu = false;
                            for (unsigned k = vowels.size(); k != 0; ) // �������� �� ������� �������
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // ������� �������, ������� ��������

                                }
                            }
                            if (ToFu == true)
                            {
                                if (word.size() - lengf[m] + 1 == word1.size()) {
                                    Doc[i] = word1;
                                    word = word1;
                                }
                                else {
                                    Step = 0;
                                }

                            }
                        }
                    }
                }



                if (Step == 0)                                                              // ������������ 12
                {
                    int number_Ap12[3]{ 0,0,0 };

                    for (unsigned k = 0; k < 3; k++)
                    {
                        if (word.rfind(Adverbial_Participle12[k]) != string::npos)
                        {
                            number_Ap12[k] = Adverbial_Participle12[k].size();

                            Step = 1;
                        }

                    }
                    if (Step == 1)
                    {
                        int l = 0;
                        int lengf[4]{ 0, 0, 0,0 };
                        int index[4]{ 0, 0, 0,0 };
                        for (int n = 0; n < 3; n++)
                        {
                            if (number_Ap12[n] != 0)
                            {
                                if (number_Ap12[n] > lengf[3]) {
                                    lengf[l] = number_Ap12[n];
                                    index[l] = n;
                                    l += 1;
                                }
                            }

                        }
                        for (int m = 0; m <= l; m++)
                        {
                            string word1;
                            word1 = word.substr(0, word.rfind(Adverbial_Participle12[index[m]]));

                            bool ToFu = false;
                            for (unsigned k = vowels.size(); k != 0; ) // �������� �� ������� �������
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // ������� �������, ������� ��������

                                }
                            }
                            if (ToFu == true)
                            {
                                if (word.size() - lengf[m] + 1 == word1.size()) {
                                    Doc[i] = word1;
                                    word = word1;
                                }
                                else {
                                    Step = 0;
                                }

                            }
                        }
                    }
                }


                if (Step == 0)                                                              // ������������ 2
                {
                    int number_Ap2[6]{ 0,0,0,0,0,0 };

                    for (unsigned k = 0; k < 6; k++)
                    {
                        if (word.rfind(Adverbial_Participle2[k]) != string::npos)
                        {
                            number_Ap2[k] = Adverbial_Participle2[k].size();

                            Step = 1;
                        }

                    }
                    if (Step == 1)
                    {
                        int l = 0;
                        int lengf[7]{ 0,0,0,0,0,0,0 };
                        int index[7]{ 0,0,0,0,0,0,0 };
                        for (int n = 0; n < 6; n++)
                        {
                            if (number_Ap2[n] != 0)
                            {
                                if (number_Ap2[n] > lengf[6]) {
                                    lengf[l] = number_Ap2[n];
                                    index[l] = n;
                                    l += 1;
                                }
                            }

                        }
                        for (int m = 0; m <= l; m++)
                        {
                            string word1;
                            word1 = word.substr(0, word.rfind(Adverbial_Participle2[index[m]]));

                            bool ToFu = false;
                            for (unsigned k = vowels.size(); k != 0; ) // �������� �� ������� �������
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // ������� �������, ������� ��������

                                }
                            }
                            if (ToFu == true)
                            {
                                if (word.size() - lengf[m] == word1.size()) {
                                    Doc[i] = word1;
                                    word = word1;
                                }
                                else {
                                    Step = 0;
                                }

                            }
                        }
                    }
                }


                // cout << " ������������" << endl;
                if (Step == 0)                                                              // ��������������
                {
                    int number_Ref[2]{ 0,0 };

                    for (unsigned k = 0; k < 2; k++)
                    {
                        if (word.rfind(Reflexive[k]) != string::npos)
                        {
                            number_Ref[k] = Reflexive[k].size();

                            Step = 1;
                        }

                    }
                    if (Step == 1)
                    {
                        int l = 0;
                        int lengf[3]{ 0, 0, 0 };
                        int index[3]{ 0, 0, 0 };
                        for (int n = 0; n < 2; n++)
                        {
                            if (number_Ref[n] != 0)
                            {
                                if (number_Ref[n] > lengf[2]) {
                                    lengf[l] = number_Ref[n];
                                    index[l] = n;
                                    l += 1;
                                }
                            }

                        }
                        for (int m = 0; m <= l; m++)
                        {
                            string word1;
                            word1 = word.substr(0, word.rfind(Reflexive[index[m]]));

                            bool ToFu = false;
                            for (unsigned k = vowels.size(); k != 0; ) // �������� �� ������� �������
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // ������� �������, ������� ��������

                                }
                            }
                            if (ToFu == true)
                            {
                                if (word.size() - lengf[m] == word1.size()) {
                                    Doc[i] = word1;
                                    word = word1;
                                }
                                else {
                                    Step = 0;
                                }

                            }
                        }
                    }
                }

                // cout << "�������������� " << endl;

                if (Step == 0)                                                              // ��������������
                {
                    int number_Adj[26]{ 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0 };

                    for (unsigned k = 0; k < 26; k++)
                    {
                        if (word.rfind(Adjective[k]) != string::npos)
                        {
                            number_Adj[k] = Adjective[k].size();

                            Step = 1;
                            StepP = 1;
                        }

                    }
                    if (Step == 1)
                    {
                        int l = 0;
                        int lengf[27]{ 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0 };
                        int index[27]{ 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0 };
                        for (int n = 0; n < 26; n++)
                        {
                            if (number_Adj[n] != 0)
                            {
                                if (number_Adj[n] > lengf[26]) {
                                    lengf[l] = number_Adj[n];
                                    index[l] = n;
                                    l += 1;
                                }
                            }

                        }
                        for (int m = 0; m <= l; m++)
                        {
                            string word1;
                            word1 = word.substr(0, word.rfind(Adjective[index[m]]));

                            bool ToFu = false;
                            for (unsigned k = vowels.size(); k != 0; ) // �������� �� ������� �������
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // ������� �������, ������� ��������

                                }
                            }
                            if (ToFu == true)
                            {
                                if (word.size() - lengf[m] == word1.size()) {
                                    Doc[i] = word1;
                                    word = word1;
                                    Step = 1;
                                    StepP = 1;
                                }
                                else {
                                    Step = 0;
                                    StepP = 0;
                                }

                            }
                        }
                    }
                }


                //cout << "��������� 1" << endl;




                if (StepP == 1)                                                              // ��������� 1
                {
                    int number_PR[5]{ 0,0,0,0,0 };

                    for (unsigned k = 0; k != 5; k++)
                    {
                        if (word.rfind(Participle1[k]) != string::npos)
                        {
                            number_PR[k] = Participle1[k].size();

                            Step = 1;
                            Steper = 1;
                        }

                    }
                    if (Steper == 1)
                    {
                        int l = 0;
                        int lengf[6]{ 0, 0, 0, 0, 0, 0 };
                        int index[6]{ 0, 0, 0, 0, 0, 0 };
                        for (int n = 0; n < 5; n++)
                        {
                            if (number_PR[n] != 0)
                            {
                                if (number_PR[n] > lengf[5]) {
                                    lengf[l] = number_PR[n];
                                    index[l] = n;
                                    l += 1;
                                }
                            }

                        }
                        for (int m = 0; m <= l; m++)
                        {
                            string word1;
                            word1 = word.substr(0, word.rfind(Participle1[index[m]]));

                            bool ToFu = false;
                            for (unsigned k = vowels.size(); k != 0; ) // �������� �� ������� �������
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // ������� �������, ������� ��������

                                }
                            }
                            if (ToFu == true)
                            {
                                if (word.size() - lengf[m] == word1.size()) {
                                    Doc[i] = word1;
                                    word = word1;
                                }
                                else {
                                    Step = 0;
                                }

                            }
                        }
                    }
                }

                //cout << "��������� 12" << endl;

                if (StepP == 1 and Steper == 0)                                                              // ��������� 12
                {
                    int number_PR12[5]{ 0,0,0,0,0 };

                    for (unsigned k = 0; k < 5; k++)
                    {
                        if (word.rfind(Participle12[k]) != string::npos)
                        {
                            number_PR12[k] = Participle12[k].size();

                            Step = 1;
                            Steper = 1;
                        }

                    }
                    if (Steper == 1)
                    {
                        int l = 0;
                        int lengf[6]{ 0, 0, 0, 0, 0, 0 };
                        int index[6]{ 0, 0, 0, 0, 0, 0 };
                        for (int n = 0; n < 5; n++)
                        {
                            if (number_PR12[n] != 0)
                            {
                                if (number_PR12[n] > lengf[5]) {
                                    lengf[l] = number_PR12[n];
                                    index[l] = n;
                                    l += 1;
                                }
                            }

                        }
                        for (int m = 0; m <= l; m++)
                        {
                            string word1;
                            word1 = word.substr(0, word.rfind(Participle12[index[m]]));

                            bool ToFu = false;
                            for (unsigned k = vowels.size(); k != 0; ) // �������� �� ������� �������
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // ������� �������, ������� ��������

                                }
                            }
                            if (ToFu == true)
                            {
                                if (word.size() - lengf[m] == word1.size()) {
                                    Doc[i] = word1;
                                    word = word1;

                                }
                                else {
                                    Step = 0;
                                }

                            }
                        }
                    }
                }

                //cout << "��������� 2" << endl;

                if (StepP == 1 and Steper == 0)                                                              // ��������� 2
                {
                    int number_PR2[3]{ 0,0,0 };

                    for (unsigned k = 0; k < 3; k++)
                    {
                        if (word.rfind(Participle2[k]) != string::npos)
                        {
                            number_PR2[k] = Participle2[k].size();

                            Step = 1;
                            Steper = 1;
                        }
                        else {
                            Step = 0;
                        }

                    }
                    if (Steper == 1)
                    {
                        int l = 0;
                        int lengf[4]{ 0, 0, 0, 0 };
                        int index[4]{ 0, 0, 0, 0 };
                        for (int n = 0; n < 3; n++)
                        {
                            if (number_PR2[n] != 0)
                            {
                                if (number_PR2[n] > lengf[3]) {
                                    lengf[l] = number_PR2[n];
                                    index[l] = n;
                                    l += 1;
                                }
                            }

                        }
                        for (int m = 0; m <= l; m++)
                        {
                            string word1;
                            word1 = word.substr(0, word.rfind(Participle2[index[m]]));

                            bool ToFu = false;
                            for (unsigned k = vowels.size(); k != 0; ) // �������� �� ������� �������
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // ������� �������, ������� ��������

                                }
                            }
                            if (ToFu == true)
                            {
                                if (word.size() - lengf[m] == word1.size()) {
                                    Doc[i] = word1;
                                    word = word1;
                                }
                                else {
                                    Step = 0;
                                }

                            }
                        }
                    }
                }

                //cout << " ������� 2" << endl;

                if (Step == 0)                                                              // ������ 2
                {
                    int number_ver2[29]{ 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0 };

                    for (unsigned k = 0; k < 29; k++)
                    {
                        if (word.rfind(Verb2[k]) != string::npos)
                        {
                            number_ver2[k] = Verb2[k].size();

                            Step = 1;
                        }

                    }
                    if (Step == 1)
                    {
                        int l = 0;
                        int lengf[30]{ 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 };
                        int index[30]{ 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0 };
                        for (int n = 0; n < 29; n++)
                        {
                            if (number_ver2[n] != 0)
                            {
                                if (number_ver2[n] > lengf[29]) {
                                    lengf[l] = number_ver2[n];
                                    index[l] = n;
                                    l += 1;
                                }
                            }

                        }
                        for (int m = 0; m <= l; m++)
                        {
                            string word1;
                            word1 = word.substr(0, word.rfind(Verb2[index[m]]));

                            bool ToFu = false;
                            for (unsigned k = vowels.size(); k != 0; ) // �������� �� ������� �������
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // ������� �������, ������� ��������

                                }
                            }
                            if (ToFu == true)
                            {
                                if (word.size() - lengf[m] == word1.size()) {
                                    Doc[i] = word1;
                                    word = word1;
                                }
                                else {
                                    Step = 0;
                                }

                            }
                        }

                    }
                }

                //cout << "������� 1" << endl;

                if (Step == 0)                                                              // ������� 1
                {
                    int number_ver1[17]{ 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0 };

                    for (unsigned k = 0; k < 17; k++)
                    {
                        if (word.rfind(Verb1[k]) != string::npos)
                        {
                            number_ver1[k] = Verb1[k].size();

                            Step = 1;
                        }

                    }
                    if (Step == 1)
                    {
                        int l = 0;
                        int lengf[18]{ 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0 };
                        int index[18]{ 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0 };
                        for (int n = 0; n < 17; n++)
                        {
                            if (number_ver1[n] != 0)
                            {
                                if (number_ver1[n] > lengf[17]) {
                                    lengf[l] = number_ver1[n];
                                    index[l] = n;
                                    l += 1;
                                }
                            }

                        }
                        for (int m = 0; m <= l; m++)
                        {
                            string word1;
                            word1 = word.substr(0, word.rfind(Verb1[index[m]]));

                            bool ToFu = false;
                            for (unsigned k = vowels.size(); k != 0; ) // �������� �� ������� �������
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // ������� �������, ������� ��������

                                }
                            }
                            if (ToFu == true)
                            {
                                if (word.size() - lengf[m] + 1 == word1.size()) {
                                    Doc[i] = word1;
                                    word = word1;
                                    Step = 4;
                                }
                                else {
                                    Step = 0;
                                }

                            }
                        }
                    }
                }

                //cout << "������� 12" << endl;

                if (Step == 0)                                                              // ������� 12
                {
                    int number_Verb12[17]{ 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0 };

                    for (unsigned k = 0; k != 17; k++)
                    {
                        if (word.rfind(Verb12[k]) != string::npos)
                        {
                            number_Verb12[k] = Verb12[k].size();

                            Step = 1;
                        }

                    }
                    if (Step == 1)
                    {
                        int l = 0;
                        int lengf[18]{ 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0 };
                        int index[18]{ 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0 };
                        for (int n = 0; n < 17; n++)
                        {
                            if (number_Verb12[n] != 0)
                            {
                                if (number_Verb12[n] > lengf[17]) {
                                    lengf[l] = number_Verb12[n];
                                    index[l] = n;
                                    l += 1;
                                }
                            }

                        }
                        for (int m = 0; m <= l; m++)
                        {
                            string word1;
                            word1 = word.substr(0, word.rfind(Verb12[index[m]]));

                            bool ToFu = false;
                            for (unsigned k = vowels.size(); k != 0; ) // �������� �� ������� �������
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // ������� �������, ������� ��������

                                }
                            }
                            if (ToFu == true)
                            {
                                if (word.size() - lengf[m] + 1 == word1.size()) {
                                    Doc[i] = word1;
                                    word = word1;
                                }
                                else {
                                    Step = 0;
                                }

                            }
                        }
                    }
                }

                //cout << "��������������� " << endl;

                if (Step == 0 or Step == 1)                                                              // ���������������
                {
                    int number_Noun[36]{ 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0 };

                    for (unsigned k = 0; k != 36; k++)
                    {
                        if (word.rfind(Noun[k]) != string::npos)
                        {
                            number_Noun[k] = Noun[k].size();

                            Step = 1;
                        }

                    }
                    if (Step == 1)
                    {
                        int l = 0;
                        int lengf[37]{ 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0 };
                        int index[37]{ 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,  0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0 };
                        for (int n = 0; n < 36; n++)
                        {
                            if (number_Noun[n] != 0)
                            {
                                if (number_Noun[n] > lengf[36]) {
                                    lengf[l] = number_Noun[n];
                                    index[l] = n;
                                    l += 1;
                                }
                            }

                        }
                        for (int m = 0; m <= l; m++)
                        {
                            string word1;
                            word1 = word.substr(0, word.rfind(Noun[index[m]]));

                            bool ToFu = false;
                            for (unsigned k = vowels.size(); k != 0; ) // �������� �� ������� �������
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // ������� �������, ������� ��������

                                }
                            }
                            if (ToFu == true)
                            {
                                if (word.size() - lengf[m] == word1.size()) {
                                    Doc[i] = word1;
                                    word = word1;
                                }
                                else {
                                    Step = 0;
                                }

                            }
                        }

                    }
                }

                // ���  -2- \\

                //cout << " � " << endl;

                if (word.rfind("�") == word.size() - 1)                                   //  "�"
                {
                    Doc[i] = word.substr(0, word.rfind("�"));
                }

                // ���   -3- \\

                //cout << "���������� " << endl;


                int number_Der[6]{ 0,0,0,0,0,0 };

                for (unsigned k = 0; k != 6; k++)
                {
                    if (word.rfind(Derivatijnal[k]) != string::npos)
                    {
                        number_Der[k] = Derivatijnal[k].size();

                        Step = 3;
                    }

                }

                if (Step == 3)
                {
                    int l = 0;
                    int lengf[6]{ 0, 0, 0, 0, 0, 0 };
                    int index[6]{ 0, 0, 0, 0, 0, 0 };
                    for (int n = 0; n < 5; n++)
                    {
                        if (number_Der[n] != 0)
                        {
                            if (number_Der[n] > lengf[5]) {
                                lengf[l] = number_Der[n];
                                index[l] = n;
                                l += 1;
                            }
                        }

                    }
                    for (int m = 0; m <= l; m++)
                    {
                        string word1;
                        word1 = word.substr(0, word.rfind(Derivatijnal[index[m]]));

                        bool ToFu = false;
                        for (unsigned k = vowels.size(); k != 0; ) // �������� �� ������� �������
                        {
                            k--;
                            if (word1.find(vowels[k]) != string::npos)
                            {
                                ToFu = true;
                                break; // ������� �������, ������� ��������

                            }
                        }
                        if (ToFu == true)
                        {
                            if (word.size() - lengf[m] == word1.size()) {
                                Doc[i] = word1;
                                word = word1;

                            }
                            else {
                                Step = 0;
                            }

                        }
                    }

                }

                // ���   -4- \\


                //cout << "�� " << endl;

                string nn = "��";
                bool found = strstr(word.c_str(), nn.c_str());
                if (found) {
                    if (word.rfind("�") == word.size() - 1)                                   //  "��"
                    {

                        Doc[i] = word.substr(0, word.rfind("�"));
                        word = Doc[i];


                    }
                }



                //cout << "������� " << endl;

                int number_Lat[2]{ 0,0 };

                for (unsigned k = 0; k < 2; k++)
                {
                    if (word.rfind(super_Lative[k]) != string::npos)
                    {
                        number_Lat[k] = super_Lative[k].size();

                        Step = 4;
                    }

                }

                if (Step == 4)
                {

                    int l = 0;
                    int lengf[3]{ 0, 0, 0 };
                    int index[3]{ 0, 0, 0 };
                    for (int n = 0; n < 2; n++)
                    {
                        if (number_Lat[n] != 0)
                        {
                            if (number_Lat[n] > lengf[2]) {
                                lengf[l] = number_Lat[n];
                                index[l] = n;
                                l += 1;
                            }
                        }

                    }
                    for (int m = 0; m <= l; m++)
                    {
                        string word1;
                        word1 = word.substr(0, word.rfind(super_Lative[index[m]]));

                        bool ToFu = false;
                        for (unsigned k = vowels.size(); k != 0; ) // �������� �� ������� �������
                        {
                            k--;
                            if (word1.find(vowels[k]) != string::npos)
                            {
                                ToFu = true;
                                break; // ������� �������, ������� ��������

                            }
                        }
                        if (ToFu == true)
                        {
                            if (word.size() - lengf[m] == word1.size()) {
                                Doc[i] = word1;
                                word = word1;
                                Step = 4;
                            }
                            else {
                                Step = 0;
                            }

                        }
                    }


                }

                //cout << " � " << endl;


                if (Step == 4)
                {
                    if (word.rfind("�") == word.size() - 1)                                   //  "�"
                    {
                        Doc[i] = word.substr(0, word.rfind("�"));
                    }
                }

                // cout << " � " << endl;


                if (word.rfind("�") == word.size() - 1)                                   //  "�"
                {
                    Doc[i] = word.substr(0, word.rfind("�"));
                }



            }
            else
            {
                Doc[i] = ' ';
            }


        }
        else {
            Doc[i] = ' ';
        }
    }
    string s;
    for (const auto& piece : Doc) s += piece + ' ';
    return s;
    //return doc;
}



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    string Doc1, Doc2, Doc3, Doc_Verti, Stop_word;
    char D_1, D_2, D_3, D_V, s_w;
    int d1 = 0, d2 = 0, d3 = 0, dv = 0;

    ifstream Doc_1("Do�_1.txt");
    while (!Doc_1.eof()) {
        Doc_1.get(D_1);
        Doc1.push_back(D_1);
    }
    Doc_1.close();
    cout << " ������ 1 ��������� ���������" << endl;
    d1 = atoi(Doc1.c_str());

    ifstream Doc_2("Doc_2.txt");
    while (!Doc_2.eof()) {
        Doc_2.get(D_2);
        Doc2.push_back(D_2);
    }
    Doc_2.close();
    cout << " ������ 2 ��������� ���������" << endl;
    d2 = atoi(Doc2.c_str());

    ifstream Doc_3("Doc_3.txt");
    while (!Doc_3.eof()) {
        Doc_3.get(D_3);
        Doc3.push_back(D_3);
    }
    Doc_3.close();
    cout << " ������ 3 ��������� ���������" << endl;
    d3 = atoi(Doc3.c_str());

    ifstream Doc_Vertifikation("Doc_Vertifikation.txt");
    while (!Doc_Vertifikation.eof()) {
        Doc_Vertifikation.get(D_V);
        Doc_Verti.push_back(D_V);

    }
    Doc_Vertifikation.close();
    cout << " ������ ��������� ��� ������������� ���������" << endl;
    dv = atoi(Doc_Verti.c_str());

    ifstream stop_word("stop_word.txt");
    while (!stop_word.eof()) {
        stop_word.get(s_w);
        Stop_word.push_back(s_w);
    }
    stop_word.close();
    cout << " ������ ����-���� ���������" << endl << endl << endl;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                             /////////// �������� ������ �������� � ��������� ��������� ���� �� ��������, � ����� ����\\\\\\\\\\\
   

    Doc1 = Corrector(Doc1), Doc2 = Corrector(Doc2), Doc3 = Corrector(Doc3), Doc_Verti = Corrector(Doc_Verti), Stop_word = Corrector(Stop_word);

    ofstream outD2("outputD2.txt");
    outD2 << Doc2;
    outD2.close();

    cout << " ������ ���������� ����� ������������� ���������" << endl;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                      /////////// �������� ����-���� \\\\\\\\\\\


    Doc1 = Anti_stop_word(Doc1, Stop_word), Doc2 = Anti_stop_word(Doc2, Stop_word), Doc3 = Anti_stop_word(Doc3, Stop_word), Doc_Verti = Anti_stop_word(Doc_Verti, Stop_word), Stop_word = Anti_stop_word(Stop_word, Stop_word);

    ofstream out11("output2.txt");
    out11 << Doc1;
    out11.close();

    ofstream outDA2("outputDA2.txt");
    outDA2 << Doc2;
    outDA2.close();

    ofstream outAA("outputANTI.txt");
    outAA << Stop_word;
    outAA.close();
    cout << " ������ ���������� ����� �������� ����-���� ���������" << endl;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                      /////////// �������� \\\\\\\\\\\

    Doc1 = Stemming(Doc1), Doc2 = Stemming(Doc2), Doc3 = Stemming(Doc3), Doc_Verti = Stemming(Doc_Verti);

    cout << " ������ ���������� ����� ��������� ���������" << endl << endl << endl;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                            /////////////  ������� ���� ����  \\\\\\\\\\\
    

    ofstream out("output.txt");
    out << Doc_Verti;
    out.close();

    ofstream out1("output1.txt");
    out1 << Doc1;
    out1.close();

    ofstream outDS2("outputDS2.txt");
    outDS2 << Doc2;
    outDS2.close();

    ofstream out3("output3.txt");
    out3 << Doc3;
    out3.close();




    string word_D1;
    vector<string> Doc__1;
    for (unsigned long long int i = 0; i < Doc1.length(); i++) {
        if (Doc1[i] != ' ' && Doc1[i] != '\0') {
            word_D1 += Doc1[i];
        }
        else {
            Doc__1.push_back(word_D1);
            if (i < Doc1.length() + 1)
                word_D1.clear();
        }
    }
    Doc__1.push_back(word_D1);


    string word_D2;
    vector<string> Doc__2;
    for (unsigned long long int i = 0; i < Doc2.length(); i++) {
        if (Doc2[i] != ' ' && Doc2[i] != '\0') {
            word_D2 += Doc2[i];
        }
        else {
            Doc__2.push_back(word_D2);
            if (i < Doc2.length() + 1)
                word_D2.clear();
        }
    }
    Doc__2.push_back(word_D2);


    string word_D3;
    vector<string> Doc__3;
    for (unsigned long long int i = 0; i < Doc3.length(); i++) {
        if (Doc3[i] != ' ' && Doc3[i] != '\0') {
            word_D3 += Doc3[i];
        }
        else {
            Doc__3.push_back(word_D3);
            if (i < Doc3.length() + 1)
                word_D3.clear();
        }
    }
    Doc__3.push_back(word_D3);


    string word_V;
    vector<string> Doc__V;
    for (unsigned long long int i = 0; i < Doc_Verti.length(); i++) {
        if (Doc_Verti[i] != ' ' && Doc_Verti[i] != '\0') {
            word_V += Doc_Verti[i];
        }
        else {
            Doc__V.push_back(word_V);
            if (i < Doc_Verti.length() + 1)
                word_V.clear();
        }
    }
    Doc__V.push_back(word_V);


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                            /////////////  ������� �����������  \\\\\\\\\\\




    std::string wordsUW = Doc1 + Doc2 + Doc3;
    std::unordered_set<std::string> words_UW;
    std::regex sepre(R"([\s,\.\!\-]+)");
    std::sregex_token_iterator iter(wordsUW.begin(), wordsUW.end(), sepre, -1), end;
    for (; iter != end; ++iter)
        words_UW.insert(*iter);

    int uw = words_UW.size();
    double uniqu�words = Doc__1.size() + Doc__2.size() + Doc__3.size() - uw;

    long double naive1 = 0, naive2 = 0, naive3 = 0, sum1 = 0.0, sum2 = 0.0, sum3 = 0.0;

    long double itoe1 = 0.0, itoe2 = 0.0, itoe3 = 0.0;

    for (unsigned long long int i = 0; i < Doc__V.size() - 1; i++) {

        for (unsigned long long int j = 0; j < Doc__1.size() - 1; j++) {

            if (Doc__V[i] == Doc__1[j]) {
                itoe1 = 1.0;
                break;
            }
            else {
                itoe1 = 0;
            }
        }

        sum1 += log((itoe1 + 1.0) / (double)(uniqu�words + (double)Doc__1.size()));
    }


    for (unsigned long long int i = 0; i < Doc__V.size(); i++) {

        for (unsigned long long int j = 0; j < Doc__2.size(); j++) {
            if (Doc__V[i] == Doc__2[j]) {
                itoe2 = 1.0;
                break;
            }
            else {
                itoe2 = 0;
            }
        }

        sum2 += log((itoe2 + 1.0) / (double)(uniqu�words + (double)Doc__2.size()));
    }


    for (unsigned long long int i = 0; i < Doc__V.size(); i++) {

        for (unsigned long long int j = 0; j < Doc__3.size(); j++) {
            if (Doc__V[i] == Doc__3[j]) {
                itoe3 = 1.0;
                break;
            }
            else {
                itoe3 = 0;
            }
        }

        sum3 += log((itoe3 + 1.0) / (double)(uniqu�words + (double)Doc__3.size()));
    }


    naive1 = log((double)d1 / ((double)d1 + (double)d2 + (double)d3)) + sum1;
    naive2 = log((double)d2 / ((double)d1 + (double)d2 + (double)d3)) + sum2;
    naive3 = log((double)d3 / ((double)d1 + (double)d2 + (double)d3)) + sum3;

    cout << " ���������� ������ ��������� ������ (��� ����� � 0 ������, ��� ������ ��������, " << endl << " ��� �������� �������� ��������� � ������� ���� �������������) " << endl << endl;
    cout << " ������ �������������� � ���� ���������� 1  = " << naive1 << endl;
    cout << " ������ �������������� � ���� ���������� 2  = " << naive2 << endl;
    cout << " ������ �������������� � ���� ���������� 3  = " << naive3 << endl << endl;

    if (naive1 > naive2 and naive1 > naive3) {
        cout << "  ����������� �������� �� ��������, ��������� � ���� ���������� 1 " << endl;
    }
    else {
        if (naive2 > naive3) {
            cout << "  ����������� �������� �� ��������, ��������� � ���� ���������� 2 " << endl;
        }
        else {
            cout << "  ����������� �������� �� ��������, ��������� � ���� ���������� 3 " << endl << endl;
        }
    }



    return 0;
}