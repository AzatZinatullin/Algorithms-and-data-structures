
//=== Файл shape.h -- библиотека фигур

#ifndef Nasledovanie_shape_h
#define Nasledovanie_shape_h

#include <iostream>


using namespace std;

//==1. Поддержка экрана в форме матрицы символов ==

char screen[XMAX][YMAX];
enum color { black='*', white='.'};

void screen_init()
{
    for (int y=0; y<YMAX; y++)
        for (int x=0; x<XMAX; x++)
            screen[x][y] = white;
}

int on_screen(int a, int b) // проверка попадания на экран
{ return 0 <= a && a < XMAX && 0 <= b && b < YMAX; }

void put_point(int a, int b)
{
    if (on_screen(a,b))
        screen[a][b] = black;
}


void put_line(int x0, int y0, int x1, int y1)
/*
 
 Рисование отрезка прямой (x0,y0) - (x1,y1).
 Уравнение прямой: b(x-x0) + a(y-y0) = 0.
 Минимизируется величина abs(eps),
 где eps = 2*(b(x-x0)) + a(y-y0).
 
 */
{
   
        int dx = 1;
        int a = x1 - x0;
        if (a < 0) dx = -1, a = -a;
    
        int dy = 1;
        int b = y1 - y0;
        if (b < 0) dy = -1, b = -b;
    
        int two_a = 2*a;
        int two_b = 2*b;
    
        int xcrit = -b + two_a;
        int eps = 0;
    
        for (;;)
        {
            put_point(x0, y0);
            if (x0 == x1 && y0 == y1) break;
            if (eps <= xcrit) x0 += dx, eps += two_b;
            if (eps >= a || a < b) y0 += dy, eps -= two_a;
        }
   
}

void screen_clear() { screen_init(); } //Очистка экрана

void screen_refresh() // Обновление экрана
{
    for (int y = YMAX-1; 0 <= y; --y)  // с верхней строки до нижней
    {
        for (int x = 0; x < XMAX; ++x) // от левого столбца до правого
            cout << screen[x][y];
        cout << '\n';
    }
}


//==2. Библиотека фигур ==
struct shape // Виртуальный базовый класс "фигура"
{
    static shape* list;
    shape* next;
    shape() { next = list; list = this; }
    virtual point north() const = 0;
    virtual point south() const = 0;
    virtual point  east() const = 0;
    virtual point  west() const = 0;
    virtual point neast() const = 0;
    virtual point seast() const = 0;
    virtual point nwest() const = 0;
    virtual point swest() const = 0;
    virtual void draw() = 0;
    virtual void move(int, int) = 0;
};


shape *shape::list = nullptr; //Инициализация списка фигур

class rotatable : public shape  //Фигуры, пригодные к повороту
{
public:
    virtual void rotate_left() = 0; //Повернуть влево
    virtual void rotate_right() = 0; //Повернуть вправо
  
};

class reflectable : public shape // Фигуры, пригодные к зеркальному отражению
{
public:
    virtual void flip_horisontally() = 0; // Отразить горизонтально
    virtual void flip_vertically() = 0; // Отразить вертикально
};

class line : public shape
/* 
 отрезок прямой ["w", "e" ].
 north() определяет точку "выше центра отрезка и так далеко
 на север, как самая его северная точка", и т. п. 
 */
{
    point w, e;
public:
    string name;
    line(point a, point b, string newname = "line") : w(a), e(b) {};
    line(point a, int L, string newname = "line") : w(point(a.x + L - 1, a.y)), e(a) { };
    point north() const { return point((w.x+e.x)/2, e.y<w.y? w.y : e.y); }
    point south() const { return point((w.x+e.x)/2, e.y<w.y? e.y : w.y); }
    point east()  const { return point((w.x+e.x)/2, e.y<w.y? e.y : w.y); }
    point west()  const { return point((w.x+e.x)/2, e.y<w.y? e.y : w.y); }
    point neast() const { return point((w.x+e.x)/2, e.y<w.y? e.y : w.y); }
    point seast() const { return point((w.x+e.x)/2, e.y<w.y? e.y : w.y); }
    point nwest() const { return point((w.x+e.x)/2, e.y<w.y? e.y : w.y); }
    point swest() const { return point((w.x+e.x)/2, e.y<w.y? e.y : w.y); }
    
    void move(int a, int b)
    {
        w.x += a; w.y += b; e.x += a; e.y += b;
    }
    void draw() { put_line(w, e); }
    
     
};

// Прямоугольник
class rectangle : public rotatable
  /* 
     nw ------ n ------ ne
     |                  |
     |                  |
     w         c        e
     |                  |
     |                  |
     sw ------ s ------ se 
  */
{
protected:
    point sw, ne;
public:
    string name;
    rectangle(point, point, string name = "rectangle");
    point north() const { return point((sw.x + ne.x)/2, ne.y); }
    point south() const { return point((sw.x + ne.x)/2, sw.y); }
    point east()  const { return point(ne.x, (sw.y + ne.y)/2); }
    point west()  const { return point(sw.x, (sw.y + ne.y)/2); }
    point neast() const { return ne; }
    point seast() const { return point(ne.x, sw.y); }
    point nwest() const { return point(sw.x, ne.y); }
    point swest() const { return sw; }
    
    void rotate_right() // Поворот вправо относительно se
    {
        int w = ne.x - sw.x, h = ne.y - sw.y;
        sw.x = ne.x - h*2;
        ne.y = sw.y + w/2;
    }
    
    void rotate_left() //Поворот влево относительно sw
    {
        int w = ne.x - sw.x, h = ne.y - sw.y;
        ne.x = sw.x + h * 2;
        ne.y = sw.y + w / 2;
    }
    
    void move(int a, int b)
    {
        sw.x += a;
        sw.y += b;
        ne.x += a;
        ne.y += b;
      
    }
    void draw();
};


rectangle::rectangle(point a, point b, string newname)
{
    name = newname;
    if (a.x <= b.x)
    {
        if (a.y <= b.y) sw = a, ne = b;
        else sw = point(a.x, b.y), ne = point(b.x, a.y);
    }
    else
    {
        if (a.y <= b.y) sw = point(b.x, a.y), ne = point(a.x, b.y);
        else sw = b, ne = a;
    }
 
}

void rectangle::draw()
{
    
        point nw(sw.x, ne.y);
        point se(ne.x, sw.y);
        put_line(nw, ne);
        put_line(ne, se);
        put_line(se, sw);
        put_line(sw, nw);
  
}


//Треугольник
class triangle : public rectangle
/*
 
 nw     n     ne
       / \
      /   \
 w   /  c  \  e
    /       \
   /         \
 sw --- s --- se
 
 */

{
public:
    int state=3;    //Переменная флаг, указывает положение треугольника в пространстве.
    triangle(point a, point b);
    void draw();
};

//Конструктор класса "треугольник" вызывает конструктор класса "прямоугольник"
triangle::triangle(point a, point b) : rectangle(a,b){};

void triangle::draw()
{
    switch (state)
    {
        case 0: //Стандартное положение
            put_line(north(), seast());
            put_line(seast(), sw);
            put_line(sw, north());
            break;
        case 1: //Поворот вправо
            put_line(nwest(), east());
            put_line(east(), sw);
            put_line(sw, nwest());
            break;
        case 2: //Поворот влево
            put_line(ne, west());
            put_line(west(), seast());
            put_line(seast(), ne);
            break;
        case 3: //Вертикальное отражение
            put_line(nwest(), ne);
            put_line(ne, south());
            put_line(south(), nwest());
            break;           
    }
}


//Косой крест
class oblique_cross : public triangle
/*
 
 nw nn  n  ee ne
      \   /
       \ /
 w      c     e
       / \
      /   \
 sw ww  s  ss se
 */          
 
{
public:
    oblique_cross(point a, point b);
    void draw();
};

oblique_cross::oblique_cross(point a, point b) : triangle(a, b){};

void oblique_cross::draw()
{
    point nn(sw.x+3,ne.y);
    point ee(ne.x-3,ne.y);
    point ss(ne.x-3,sw.y);
    point ww(sw.x+3,sw.y);
    put_line(nn, ss);
    put_line(ww, ee);
}


void shape_refresh() // Перерисовка всех фигур
// Здесь используется динамическое связывание‼!
{
    screen_clear();
    for (shape* p = shape::list; p; p = p->next)
    {
    
            p->draw();
        
    }
    screen_refresh();
}

void up(shape* p, const shape* q) // поместить p над q
// Здесь используется динамическое связывание‼!
{
    point n = q->north();
    point s = p->south();
    p->move(n.x - s.x, n.y - s.y + 1);
}


void imposition(shape* p, const shape* q) // поместить p поверх q
// Здесь используется динамическое связывание‼!
{
    point n = q->south();
    point s = p->south();
    p->move(n.x - s.x , n.y - s.y + 1);
}

void imposition_1(shape* p, const shape* q) // поместить p поверх q
// Здесь используется динамическое связывание‼!
{
    point n = q->swest();
    point s = p->neast();
    p->move(n.x - s.x - 1, n.y - s.y - 1);
}

void imposition_2(shape* p, const shape* q) // поместить p поверх q
// Здесь используется динамическое связывание‼!
{
    point n = q->seast();
    point s = p->nwest();
    p->move(n.x - s.x + 1, n.y - s.y - 1);
}

//========================================================
#endif
