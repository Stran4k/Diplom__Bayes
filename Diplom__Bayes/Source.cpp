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
{                                           // изменение заглавных букв на строчные и удаление знаков препинаний
    vector <char> Punctuation_Marks = { '?', '!', '.', ',', '-', '"', ';', ':', '{', '}', '[', ']', '~', '<', '>', '№', '(', ')', '%', '«', '»', '–', '+', '$', '/', '—', '°' };

    vector <string> Сapital_Letters = { "а", "б", "в", "г", "д", "е", "ё", "е", "ж", "з", "и", "й", "к", "л", "м", "м", "н", "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "э", "ю", "я" };
    vector <char> Lowercase_Letters = { 'А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ё', 'ё', 'Ж', 'З', 'И', 'Й', 'К', 'Л', 'М','M', 'Н', 'О', 'П', 'Р', 'С', 'Т', 'У', 'Ф', 'Х', 'Ц', 'Ч', 'Ш', 'Щ', 'Э', 'Ю', 'Я' };
    vector <char> numbers = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };


    for (int q = 0; q < 9; q++) {
        for (int i = 0; i <= doc.length(); i++) {

            for (int u = 0; u <= Lowercase_Letters.size() - 1; u++) {

                if (doc[i] == Lowercase_Letters[u]) {

                    doc.replace(i, 1, Сapital_Letters[u]);

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


string Anti_stop_word(string doc, string docAnti)  // удаление стоп-слов
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
    // буквы
    vector <string> Сapital_Letters = { "а", "б", "в", "г", "д", "е", "ё", "е", "ж", "з", "и", "й", "к", "л", "м", "н", "о", "п", "р",
                                                                                     "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "э", "ю", "я" };

    //гласные
    vector <string> vowels = { "у", "е", "а", "о", "э", "я", "и", "ю", "ы" };

    // деепричастия     ERFECTIVE_GERUND
    vector <string>  Adverbial_Participle1 = { "ав", "авши","авшись" };
    vector <string>  Adverbial_Participle12 = { "яв", "явши","явшись" };
    vector <string>  Adverbial_Participle2 = { "ив", "ивши","ившись", "ыв", "ывши","ывшись" };
    //окончания группы 1 должны следовать за а или я 

// прилагательные
    vector <string> Adjective = { "ее","ие","ое","ими","ыми",  "ей","ий","ые", "ый", "ой",  "ем","им","ым", "ом", "его",   "ого", "ему", "ому", "их", "ых",
                                                                                                                            "ую", "юю", "ая", "яя", "ою", "ею" };

    // причастия
    vector <string> Participle1 = { "аен", "анн", "авш", "ающ", "ащ" };
    vector <string> Participle12 = { "яен", "янн", "явш", "яющ", "ящ" };

    vector <string> Participle2 = { "ивш", "ывш", "ующ" };
    //окончания группы 1 должны следовать за а или я 

// рефлексивный
    vector <string> Reflexive = { "ся", "сь" };

    // глаголы
    vector <string> Verb1 = { "ала", "ана", "аете", "айет", "али", "ай", "ал", "аем", "ан", "ало", "ано", "ает", "ают", "аны", "ать", "аешь", "анно" };
    vector <string> Verb12 = { "яла", "яна", "яете", "яйет", "яли", "яй", "ял", "яем", "ян", "яло", "яно", "яет", "яют", "яны", "ять", "яешь", "янно" };

    vector <string> Verb2 = { "ила", "ыла", "ена", "ейте", "уйте", "ите", "или", "ыли", "ей", "ой", "ий", "ыл", "им", "ым", "ен", "ыло", "ило", "ено",
                                                                                           "ят", "ует", "уют", "ит", "ыт", "ены", "ить", "ыть", "ишь", "ую", "ю" };
    //окончания группы 1 должны следовать за а или я 

    // Существительные
    vector <string> Noun = { "а", "ев", "ов", "ие", "ье", "е", "иями", "ями", "ами", "еи", "ии", "и", "ией", "ей", "ой", "ий", "й", "иям", "ям", "ием",  "ем",
                                                                                     "ам", "ом", "о", "у", "ах", "иях", "ях", "ы", "ь", "ию", "ью", "ю", "ия", "ья", "я" };

    // превосходная степень 
    vector <string> super_Lative = { "ейш", "ейше" };

    // отвлеченное состояние прилагательного в существительных
    vector <string> Derivatijnal = { "ост", "ость", "ота", "ета", "ина", "изна" };

    //в слове есть как минимум 1 гласная и минимум 3 буквы 
    // если нн удалить 1 н
    // слова >2 букв
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


    // +     ШАГ  -1-
                // 
                // 
                // Выполняется гентрудий-деепричастие
                // если нашли то другие гентрудии 1                    +
                // гентрудий 12                                        +
                // если нашли гентрудий 2 не выполняется               +
                // гентрудий 2                                         +
                //
                // если гентрудии закончились провалом идем дальше     +
                // 
                // проверяем Рефлективность                            +
                //   прилагательные                                    +
                //   глагол                                            +
                //   существительное                                   +
                // 
                // 
                // +      ШАГ  -2-
                // 
                // 
                // если есть "и" удалить ее                            +
                // 
                // 
                // +     ШАГ  -3-
                //
                //  
                // если есть деривационный удалить ее                  +
                // 
                // 
                //      ШАГ  -4-
                // 
                // 
                //  1 если есть "НН" то удаляем "1" "Н"                                   +
                //  2 превосходная степень если да то удалить и убрать "Н"                +
                //  3  "Ь" удалить его
                // 
                // доп проверка на длину слова (на основание)-
                // 
                // +     нужна доп проверка на случай если слово остается без глассных    +



    // имеем векторс слов документа                                                                 /// стоит определить основу слова и не трогать её
                                                                                                    /// онснова особо не нужна мы и так делаем проверку на наличие глассной


    for (unsigned long long int i = 0; i < Doc.size() - 1; i++)
    {
        bool ToF = false;
        string word = Doc[i];
        if (word.size() >= 3)
        {


            for (unsigned k = vowels.size(); k != 0; ) // проверка на наличие гласных
            {
                k--;
                if (word.find(vowels[k]) != string::npos)
                {
                    ToF = true;
                    break; // гласная найдена, стопаем проверку

                }


                if (ToF == true) break;
            }



            if (ToF == true)
            {
                int Steper = 0;
                int StepP = 0;
                int Step = 0;                                     //  ШАГ
                int number_Ap1[3]{ 0,0,0 };

                for (unsigned k = 0; k < 3; k++)                                       // 1 деепричастие  
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
                            for (unsigned k = vowels.size(); k != 0; ) // проверка на наличие гласных
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // гласная найдена, стопаем проверку

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



                if (Step == 0)                                                              // деепричастие 12
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
                            for (unsigned k = vowels.size(); k != 0; ) // проверка на наличие гласных
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // гласная найдена, стопаем проверку

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


                if (Step == 0)                                                              // деепричастие 2
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
                            for (unsigned k = vowels.size(); k != 0; ) // проверка на наличие гласных
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // гласная найдена, стопаем проверку

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


                // cout << " Рефлективный" << endl;
                if (Step == 0)                                                              // Рефлективность
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
                            for (unsigned k = vowels.size(); k != 0; ) // проверка на наличие гласных
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // гласная найдена, стопаем проверку

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

                // cout << "Прилагательные " << endl;

                if (Step == 0)                                                              // Прилагательные
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
                            for (unsigned k = vowels.size(); k != 0; ) // проверка на наличие гласных
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // гласная найдена, стопаем проверку

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


                //cout << "причастие 1" << endl;




                if (StepP == 1)                                                              // Причастие 1
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
                            for (unsigned k = vowels.size(); k != 0; ) // проверка на наличие гласных
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // гласная найдена, стопаем проверку

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

                //cout << "причастие 12" << endl;

                if (StepP == 1 and Steper == 0)                                                              // Причастие 12
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
                            for (unsigned k = vowels.size(); k != 0; ) // проверка на наличие гласных
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // гласная найдена, стопаем проверку

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

                //cout << "причастие 2" << endl;

                if (StepP == 1 and Steper == 0)                                                              // Причастие 2
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
                            for (unsigned k = vowels.size(); k != 0; ) // проверка на наличие гласных
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // гласная найдена, стопаем проверку

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

                //cout << " Глаголы 2" << endl;

                if (Step == 0)                                                              // глагол 2
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
                            for (unsigned k = vowels.size(); k != 0; ) // проверка на наличие гласных
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // гласная найдена, стопаем проверку

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

                //cout << "глаголы 1" << endl;

                if (Step == 0)                                                              // глаголы 1
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
                            for (unsigned k = vowels.size(); k != 0; ) // проверка на наличие гласных
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // гласная найдена, стопаем проверку

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

                //cout << "глаголы 12" << endl;

                if (Step == 0)                                                              // глаголы 12
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
                            for (unsigned k = vowels.size(); k != 0; ) // проверка на наличие гласных
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // гласная найдена, стопаем проверку

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

                //cout << "существительные " << endl;

                if (Step == 0 or Step == 1)                                                              // Существительные
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
                            for (unsigned k = vowels.size(); k != 0; ) // проверка на наличие гласных
                            {
                                k--;
                                if (word1.find(vowels[k]) != string::npos)
                                {
                                    ToFu = true;
                                    break; // гласная найдена, стопаем проверку

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

                // ШАГ  -2- \\

                //cout << " И " << endl;

                if (word.rfind("и") == word.size() - 1)                                   //  "И"
                {
                    Doc[i] = word.substr(0, word.rfind("и"));
                }

                // ШАГ   -3- \\

                //cout << "Дериватион " << endl;


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
                        for (unsigned k = vowels.size(); k != 0; ) // проверка на наличие гласных
                        {
                            k--;
                            if (word1.find(vowels[k]) != string::npos)
                            {
                                ToFu = true;
                                break; // гласная найдена, стопаем проверку

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

                // ШАГ   -4- \\


                //cout << "НН " << endl;

                string nn = "нн";
                bool found = strstr(word.c_str(), nn.c_str());
                if (found) {
                    if (word.rfind("н") == word.size() - 1)                                   //  "НН"
                    {

                        Doc[i] = word.substr(0, word.rfind("н"));
                        word = Doc[i];


                    }
                }



                //cout << "Превосх " << endl;

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
                        for (unsigned k = vowels.size(); k != 0; ) // проверка на наличие гласных
                        {
                            k--;
                            if (word1.find(vowels[k]) != string::npos)
                            {
                                ToFu = true;
                                break; // гласная найдена, стопаем проверку

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

                //cout << " Н " << endl;


                if (Step == 4)
                {
                    if (word.rfind("н") == word.size() - 1)                                   //  "Н"
                    {
                        Doc[i] = word.substr(0, word.rfind("н"));
                    }
                }

                // cout << " Ь " << endl;


                if (word.rfind("ь") == word.size() - 1)                                   //  "Ь"
                {
                    Doc[i] = word.substr(0, word.rfind("ь"));
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

    ifstream Doc_1("Doс_1.txt");
    while (!Doc_1.eof()) {
        Doc_1.get(D_1);
        Doc1.push_back(D_1);
    }
    Doc_1.close();
    cout << " Чтение 1 документа завершено" << endl;
    d1 = atoi(Doc1.c_str());

    ifstream Doc_2("Doc_2.txt");
    while (!Doc_2.eof()) {
        Doc_2.get(D_2);
        Doc2.push_back(D_2);
    }
    Doc_2.close();
    cout << " Чтение 2 документа завершено" << endl;
    d2 = atoi(Doc2.c_str());

    ifstream Doc_3("Doc_3.txt");
    while (!Doc_3.eof()) {
        Doc_3.get(D_3);
        Doc3.push_back(D_3);
    }
    Doc_3.close();
    cout << " Чтение 3 документа завершено" << endl;
    d3 = atoi(Doc3.c_str());

    ifstream Doc_Vertifikation("Doc_Vertifikation.txt");
    while (!Doc_Vertifikation.eof()) {
        Doc_Vertifikation.get(D_V);
        Doc_Verti.push_back(D_V);

    }
    Doc_Vertifikation.close();
    cout << " Чтение документа для классификации завершено" << endl;
    dv = atoi(Doc_Verti.c_str());

    ifstream stop_word("stop_word.txt");
    while (!stop_word.eof()) {
        stop_word.get(s_w);
        Stop_word.push_back(s_w);
    }
    stop_word.close();
    cout << " Чтение стоп-слов завершено" << endl << endl << endl;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                             /////////// Удаление знаков препинай и изменение заглавных букв на строчные, а также цифр\\\\\\\\\\\
   

    Doc1 = Corrector(Doc1), Doc2 = Corrector(Doc2), Doc3 = Corrector(Doc3), Doc_Verti = Corrector(Doc_Verti), Stop_word = Corrector(Stop_word);

    ofstream outD2("outputD2.txt");
    outD2 << Doc2;
    outD2.close();

    cout << " Запись документов после предобработки завершена" << endl;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                      /////////// удаление стоп-слов \\\\\\\\\\\


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
    cout << " Запись документов после удаления стоп-слов завершена" << endl;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                      /////////// Стемминг \\\\\\\\\\\

    Doc1 = Stemming(Doc1), Doc2 = Stemming(Doc2), Doc3 = Stemming(Doc3), Doc_Verti = Stemming(Doc_Verti);

    cout << " Запись документов после Стемминга завершена" << endl << endl << endl;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                            /////////////  Векторы всех слов  \\\\\\\\\\\
    

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
                                            /////////////  Подсчет результатов  \\\\\\\\\\\




    std::string wordsUW = Doc1 + Doc2 + Doc3;
    std::unordered_set<std::string> words_UW;
    std::regex sepre(R"([\s,\.\!\-]+)");
    std::sregex_token_iterator iter(wordsUW.begin(), wordsUW.end(), sepre, -1), end;
    for (; iter != end; ++iter)
        words_UW.insert(*iter);

    int uw = words_UW.size();
    double uniquуwords = Doc__1.size() + Doc__2.size() + Doc__3.size() - uw;

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

        sum1 += log((itoe1 + 1.0) / (double)(uniquуwords + (double)Doc__1.size()));
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

        sum2 += log((itoe2 + 1.0) / (double)(uniquуwords + (double)Doc__2.size()));
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

        sum3 += log((itoe3 + 1.0) / (double)(uniquуwords + (double)Doc__3.size()));
    }


    naive1 = log((double)d1 / ((double)d1 + (double)d2 + (double)d3)) + sum1;
    naive2 = log((double)d2 / ((double)d1 + (double)d2 + (double)d3)) + sum2;
    naive3 = log((double)d3 / ((double)d1 + (double)d2 + (double)d3)) + sum3;

    cout << " Результаты работы алгоритма Байеса (чем ближе к 0 оценка, тем больше вероятно, " << endl << " что документ проверки относится к данному типу классификации) " << endl << endl;
    cout << " Оценка принадлежности к типу документов 1  = " << naive1 << endl;
    cout << " Оценка принадлежности к типу документов 2  = " << naive2 << endl;
    cout << " Оценка принадлежности к типу документов 3  = " << naive3 << endl << endl;

    if (naive1 > naive2 and naive1 > naive3) {
        cout << "  Поступивший документ на проверку, относится к типу документов 1 " << endl;
    }
    else {
        if (naive2 > naive3) {
            cout << "  Поступивший документ на проверку, относится к типу документов 2 " << endl;
        }
        else {
            cout << "  Поступивший документ на проверку, относится к типу документов 3 " << endl << endl;
        }
    }



    return 0;
}