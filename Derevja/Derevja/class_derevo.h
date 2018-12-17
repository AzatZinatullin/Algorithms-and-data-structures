
//  class_derevo.h


#ifndef Derevja_class_derevo_h
#define Derevja_class_derevo_h

#include <iostream>
#include <cstdlib>

using namespace std;

//Класс «узел дерева»
class Node
{
       
    
public:
    
    char d;     // тег узла
    Node * lft; // левый сын
    Node * rgt; // правый сын
    
    
    Node() : lft(nullptr), rgt(nullptr) { } // конструктор узла
    ~Node(){ if(lft) delete lft;            // деструктор (уничтожает поддерево)
        if (rgt) delete rgt; }
    
    friend class Tree;          // дружественный класс «дерево»
};


// Класс «дерево в целом»
class Tree
{
    Node * root; // указатель на корень дерева
    int count;
    char num, maxnum;       //счётчик тегов и максимальный тег
    int maxrow, offset;     //максимальная глубина, смещение корня
    char ** SCREEN;         // память для выдачи на экран
    void clrscr();          // очистка рабочей памяти
    Node* MakeNode(int depth);      // создание поддерева
    void OutNodes(Node * v, int r, int c);         // выдача поддерева
    
    Tree (const Tree &);        // фиктивный конструктор копии
    Tree (Tree &&);             //копия с переносом (С++11)
    Tree operator = (const Tree &) const;   // фиктивное присваивание
    Tree operator = (Tree &&) const;        //присваивание с переносом (С++11)
    int SFS1(Node *v);   // Внутренний обход дерева
    
public:
    
    Tree(char num, char maxnum, int maxrow);
    ~Tree();
    void MakeTree() { root = MakeNode(0); } // ввод — генерация дерева
    bool exist() { return root != nullptr; } // проверка «дерево не пусто»
    void OutTree();     // выдача на экран
    
    int SFS(){ return SFS1(root); }  // Интерфейсная функция внутреннего обхода
    
    int getMaxDepth(Node* v, int depth); // Рекурсивная функция расчета высоты дерева
    
    void outDepth();            // Функция выдает высоту правого поддерева для корня
    
};


// Конструктор дерева инициализирует параметры разметки и создаёт рабочую память матрицу символов, необходимую для выдачи изображения дерева на экран.
Tree::Tree(char nm, char mnm, int mxr): count(0),
num(nm), maxnum(mnm), maxrow(mxr), offset(40), root(nullptr), SCREEN(new char * [maxrow])
{for(int i = 0; i < maxrow; i++)
    SCREEN[i] = new char[80];}


// Деструктор дерева уничтожает матрицу символов и запускает деструктор узла для корня.
Tree::~Tree()
{ for(int i = 0; i < maxrow; i++) delete []SCREEN[i];
    delete []SCREEN; delete root; }

Node * Tree::MakeNode(int depth)
{
    Node * v = nullptr;
    int Y = (depth < rand()%6+1) && (num <= 'z');
    
    // Вариант: cout ≪ "Node (" ≪ num ≪ ',' ≪ depth ≪ ")1/0: "; cin ≫ Y;
    
    if (Y)               // создание узла, если Y = 1
    {
        v = new Node;
        v->d = num++;        // разметка в прямом порядке (= «в глубину»)
        v->lft = MakeNode(depth+1);
        // v->d = num++;           //вариант — во внутреннем
        v->rgt = MakeNode(depth+1);
        // v->d = num++;        // вариант — в обратном
    }
    return v;
}

void Tree::OutTree()
{
    clrscr();
    OutNodes(root, 1, offset);
    for (int i = 0; i < maxrow; i++)
    {
        SCREEN[i][79] = 0;
        cout << "\n" << SCREEN[i];
    }
    cout << "\n";
}

void Tree::clrscr()
{
    for(int i = 0; i < maxrow; i++)
        memset(SCREEN[i], '.', 80);
}


void Tree::OutNodes(Node * v, int r, int c)
{
    if (r&&c&&(c<80)) SCREEN[r-1][c-1]=v->d; // вывод метки
    if (r<maxrow)
    {
        if (v->lft) OutNodes(v->lft, r+1, c-(offset>>r)); //левый сын
        // if (v->mdl) OutNode(v->mdl, r + 1, c); — средний сын (если нужно)
        if (v->rgt) OutNodes(v->rgt, r+1, c+(offset>>r)); //правый сын
    }
}


int Tree::SFS1(Node *v)
{
    if(v == NULL)
    { return 0;}
    SFS1(v->lft);
    cout << v->d << '_';count++;
    SFS1(v->rgt);
    
    return count;
}

void Tree::outDepth()
{
	int depth = 0;
	depth = getMaxDepth(root->rgt, depth);
    cout << "\nВысота правого поддерева для корня = " << depth;
}

int Tree::getMaxDepth(Node* v, int depth)
{
	if (!v)
		return depth;
	else
        return max(getMaxDepth(v->lft, depth + 1), getMaxDepth(v->rgt, depth + 1));
}

#endif
