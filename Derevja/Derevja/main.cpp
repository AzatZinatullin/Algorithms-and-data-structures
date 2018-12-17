
// Задание выполнил студент группы 5005 Зинатуллин Азат.
// Вариант №21. 
// Вид дерева: двоичное. Разметка: прямая. Способ обхода: внутренний.
// Нужно вычислить: высоту правого поддерева для корня.

#include <iostream>
#include <ctime>
#include "class_derevo.h"


using namespace std;


int main(int argc, const char * argv[])
{
        int n = 0;
        Tree Tr('a','z',8);
        srand(time(nullptr));
        setlocale(LC_ALL, "Russian");
        
        Tr.MakeTree();
        
        if(Tr.exist())
        {
            Tr.OutTree();
            cout << "\n" << "Обход в глубину: ";
            n= Tr.SFS();
            cout << " Пройдено узлов = " << n;
            Tr.outDepth();
        }
        else cout << "Дерево пусто!";
        cout << "\n" << "=== Конец ===";
    
    return 0;
}

