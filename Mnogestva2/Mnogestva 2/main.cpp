
// Задание выполнил студент группы 5005 Зинатуллин Азат.
// Вариант №21. Универсум десятичные числа.
// Множество, содержащее цифры, имеющиеся в A или B или являющиеся общими для C и D.
// Формализация задания: E=A|B|(C&D)

#include <iostream>
#include <time.h>
#include "array.h"

using namespace std;

 // определение статического члена класса
const long q0 = 100000; // количество повторений цикла времени

int main()
{   //    srand(static_cast<unsigned long>(5));
    //    srand(time(nullptr));
        Set A('A'), B('B'), C('C'), D('D'), E;
    
        clock_t begin = clock();

        for(long q =0; q < q0; q++)
        {
            E = (A|B|(C&D));
        }
        
        clock_t end = clock();
        E.Show();
        
        cout << " Middle power=" <<
        (A.power() + B.power() + C.power() + D.power() + E.power())/5 <<
        " Time=" << (end-begin) << " / " << q0 << endl;
        
    return 0;
}

