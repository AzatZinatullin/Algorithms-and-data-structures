
//  arraybit.h (способ представления массивом битов)

#ifndef Mnogestva_2_arraybit_h
#define Mnogestva_2_arraybit_h

#include <cstring>
#include <iostream>


using namespace std;


class Set
{
private:            // Закрытая часть класса — данные
    
    static int N;   // Мощность универсума
    int n;          // Мощность множества
    char bA[10];    // Память под массив битов
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
    {
        bA[0]= 0;
    }

    Set::Set(char s): n(0), S(s)
    {
        
        cout << S << " = [";
        for(int i = 0; i < N; i++)
        {
            
            bA[i]=rand()%2;
            
            if(bA[i]) {cout << char(i + '0');
                n++;
            }
            else cout << "-";
            }
        cout << "]" << endl;
    }

    Set Set::operator & (const Set& B) const
    {
        Set C;
        for (int i = 0; i<N; ++i)
            C.bA[i] = B.bA[i]&bA[i];
        return C;
    }

    Set Set:: operator | (const Set& B) const
    {
        Set C;
        for (int i = 0; i<N; ++i)
            C.bA[i] = B.bA[i]|bA[i];
        return C;
    }

    Set::Set(const Set&B) :  S(B.S), n(B.n)
    {
        memcpy(bA, B.bA, N);
    } 

    Set Set :: operator = (const Set& B)
    {
        if(this != &B)
        {
            n=B.n;
            memcpy(bA,B.bA,N);
            S = 'E';
        }
        return *this;
    }

    void Set :: Show()
    {
        cout << S << " = [";
        for(int i = 0; i < N; ++i)
            if(bA[i]) cout << char(i + '0');
            else cout << "-";
        cout << "]";
    }

#endif
