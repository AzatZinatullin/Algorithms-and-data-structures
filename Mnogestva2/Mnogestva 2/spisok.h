
//  spisok.h (способ представления списком)

#ifndef Mnogestva_2_spisok_h
#define Mnogestva_2_spisok_h

#include <cstring>
#include <iostream>

using namespace std;

struct EL {
    char d;
    EL * next;
    EL(char d, EL * next = nullptr) : d(d), next(next) { }  
    ~EL() {if (next) delete next;}
};

class Set
{
private:            // Закрытая часть класса — данные
    
    static int N;   // Мощность универсума
    int n;          // Мощность множества
    char S;         // Символ тег и память для множества
    EL *La;         // Указатель на список
    
    
public:             // Открытая часть — функции для работы с множеством
   
    Set operator | (const Set&) const;  // Объединение
    Set operator & (const Set&) const;  // Пересечние
    void Show();                        // Вывод множества на экран
    int power() {return n;}             // Получение мощности множества
    Set(char);                          // Конструктор множества
    Set();                              // Конструктор по умолчанию
    Set(const Set&);                    // Конструктор копии
    Set operator = (const Set&);        // Оператор присваивания
    ~Set(){delete La;}                  // деструктор
};

int Set:: N = 10;


    Set::Set(): n(0), S('0')
    {   
        La = nullptr;
    }


    Set::Set(char s): n(0), S(s)
    {
        La = nullptr;
        for(int i=0; i<N; ++i)
        {
            char A;
            if(rand()%2)
            {
                A=i+'0';
                EL* e = new EL(A, La);
                La = e;
                A=0;
                n++;
            }
        }
        cout << S << " = ";
        for (EL *v = La; v; v = v->next)
            cout << v->d;
        cout << endl; 
    }

    Set Set::operator & (const Set& B) const
    {
        Set C;
        for (EL* u = La; u; u = u->next)
        {
            bool f=true;
            for (EL* v = B.La; v&&f; v = v->next)
                if (u->d == v->d)
                {
                    EL* e = new EL(u->d, C.La);
                    C.La = e;
                    f=false;
                }
        }
        return C;
    }   

    Set Set:: operator | (const Set &B) const
    {
        Set C;
        for (EL* u = La; u; u = u->next)
        {
            EL* e = new EL(u->d, C.La);
            C.La = e; ++C.n;
        }
        for (EL* u = B.La; u; u = u->next)
        {
            bool f = true;
            for (EL* v = C.La; v; v = v->next)
                if (u->d == v->d) f=false;
            if(f)
			{
				EL* e = new EL(u->d, C.La);
				C.La = e;
			}
        }
        
        return C;
    }

    Set::Set(const Set & B) : S(B.S), n(B.n)
    {
        La = nullptr;
        for (EL* u = B.La; u; u = u->next)
        {
            EL* e = new EL(u->d, La);
            La = e;
        }
    }

    Set Set::operator = (const Set& B)
    {
        if (this != &B)
        {
            n=B.n;
            La = nullptr;
            for (EL* u = B.La; u; u = u->next)
            {
                EL* e = new EL(u->d, La);
                La = e;
            }
            S = 'E';
            
        }
        return *this;
    }

    void Set::Show()
    {
        cout << '\n' << S << " = [";
        for (EL *v = La; v; v = v->next)
            cout << v->d ;
            cout << "]";
    }


#endif
