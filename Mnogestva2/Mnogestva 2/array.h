
//  array.h (способ представления массивом символов)

#pragma once
#ifndef Mnogestva_2_array_h
#define Mnogestva_2_array_h

#include <cstring>
#include <iostream>  

using namespace std;


class Set
{
    private:            // Закрытая часть класса — данные
    
        static int N;   // Мощность универсума
        int n;          // Мощность множества
        char S, *A;     // Символ тег и память для множества
    
    public:             // Открытая часть — функции для работы с множеством
    
        Set operator | (const Set&) const;  // Объединение
        Set operator & (const Set&) const;  // Пересечние
        void Show();                        // Вывод множества на экран
        int power() {return n;}             // Получение мощности множества
        Set(char);                          // Конструктор множества
        Set();                              // Конструктор по умолчанию
        Set(const Set&);                    // Конструктор копии
        Set operator = (const Set&);        // Оператор присваивания
        ~Set(){cout << "Деструктор\n"; delete []A;}                 // деструктор
};

    int Set:: N = 10;

    Set::Set(): n(0), S('0'), A(new char[N+1])
    {
        cout << "Конструктор по умолчанию\n";
        A[0]= 0;
    }

    Set::Set(char s): n(0), S(s), A(new char[N+1])
    {
        cout << "Конструктор множества";
        for(int i = 0; i < N; i++)
            if(rand()%2)
                A[n++] = i+'0';
                A[n] = 0;
        cout << '\n' << S << " = [" << A << "]" << endl;
    }

    Set Set::operator & (const Set& B) const
    {
        cout << "Оператор пересечения" << endl;
        Set C;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < B.n; j++)
                if (A[i] == B.A[j]) C.A[C.n++] = A[i];
        }
        C.A[C.n] = 0;
        return C;
    }  

    Set Set:: operator | (const Set &B) const
    {
        cout << "Оператор объединения" << endl;
        Set C;
        memcpy(C.A, A, n);
        C.n = n;
        for(int i = 0; i <B.n; i++)
        {
            bool f = true;
            for(int j = 0; j < n; j++)
                if (B.A[i] == A[j])
                    f = false;
                if (f) C.A[C.n++] = B.A[i];
        }
        C.A[C.n] = 0;
        return C;
    }       
 
    Set::Set(const Set & B) : S(B.S), n(B.n), A(new char[N+1])
    {
        cout << "Конструктор копии" << endl;
        memcpy(A, B.A, N+1);
    }

    Set  Set::operator = (const Set& B)
    {
        cout << "Оператор присваивания" << endl;
        if (this != &B)
        {
            n = B.n;
            memcpy(A,B.A,N+1);
            S = 'E';
        }
    return *this;
    }
   
    void Set::Show()
    {
        cout << "Функция вывода множества на экран";
        cout << '\n' << S << " = [" << A << "]";
    }

#endif
