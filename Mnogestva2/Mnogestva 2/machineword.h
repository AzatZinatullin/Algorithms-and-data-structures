
//  machineword.h (способ представления машинным словом)

#ifndef Mnogestva_2_machineword_h
#define Mnogestva_2_machineword_h

#include <cstring>
#include <iostream>

using namespace std;


class Set
{
private:            // Закрытая часть класса — данные
    
    static int N;   // Мощность универсума
    int n;          // Мощность множества
    int mw;         // Память для машинных слов
    char S;         // Символ тег
    
public:             // Открытая часть — функции для работы с множеством
    
    Set operator | (const Set&) const;  // Объединение
    Set operator & (const Set&) const;  // Пересечние
    void Show();                        // Вывод множества на экран
    int power() {return n;}             // Получение мощности множества
    Set(char);                          // Конструктор множества
    Set();                              // Конструктор по умолчанию
    Set(const Set&);                    // Конструктор копии
    Set operator = (const Set&);        // Оператор присваивания
    
};

int Set:: N = 10;

    Set::Set(): n(0), S('0')
        {mw= 0;}

    Set::Set(char s): n(0), S(s)
    {
        mw = rand();
        
        cout << S << " = [";
        for(int i = 0; i < N; i++)
        {
            if((mw >> i) & 1){
                cout << char(i + '0');
                n++;}
        }
        cout << "]" << endl;
        
    }
    
    Set Set:: operator | (const Set& B) const
    {
        Set C;
        C.mw = B.mw | mw;
        return C;
    }

    Set Set:: operator & (const Set& B) const
    {
        Set C;
        C.mw = B.mw & mw;
        return C;
    }

    Set::Set(const Set&B)
    {
        S=B.S;
        n=B.n;
        mw=B.mw;
    }

    Set Set :: operator = (const Set&B)
    {
        if(this != &B)
        {
            n=B.n;
            mw = B.mw;
            S = 'E';
        }
        return *this;
    }
    void Set :: Show()
    {
        cout << S << " = [";
        for(int i = 0; i < N; i++)
              if((mw >> i) & 1)
                  cout << char(i + '0');
        cout << "]";
    }

#endif
