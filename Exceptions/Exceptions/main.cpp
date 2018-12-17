
//  main.cpp

#include <iostream>
#include "screen.h"
#include "shape.h"
#include <exception>


using namespace std;
// Дополнительная "сборная" фигура

class myshape : public rectangle
{ // Моя фигура ЯВЛЯЕТСЯ прямоугольником
    line* l_eye; // левый глаз – моя фигура СОДЕРЖИТ линию
    line* r_eye; // правый глаз
    line* mouth; // рот
public:
    myshape(point, point);
    void draw();
    void move(int, int);
};


myshape::myshape(point a, point b) : rectangle(a, b)
// myshape запускает конструктор базового класса rectangle !
{
    int ll = neast().x - swest().x + 1;
    int hh = neast().y - swest().y + 1;
    l_eye = new line(point(swest().x + 2, swest().y + hh * 3/4), 2);
    r_eye = new line(point(swest().x + ll - 4, swest().y + hh * 3/4), 2);
    mouth = new line(point(swest().x + 2, swest().y + hh / 4), ll - 4);
}

void myshape::draw()
{
    rectangle::draw();
    int a = (swest().x + neast().x)/2;
    int b = (swest().y + neast().y)/2;
    put_point(point(a, b));
}


void myshape::move(int a, int b)
{
    rectangle::move(a, b);
    l_eye->move(a, b);
    r_eye->move(a, b);
    mouth->move(a, b);
}

class myshape_2 : public oblique_cross
{ // Моя фигура ЯВЛЯЕТСЯ треугольником с косым крестом
public:
    myshape_2(point a, point b);
    void draw();
};

// myshape запускает конструктор класса oblique_cross,
// а тот в свою очередь констуркторы классов треугольник и прямоугольник!
myshape_2::myshape_2(point a, point b) : oblique_cross(a, b){};


void myshape_2::draw()
{
    triangle::draw();
    oblique_cross::draw();
}


int main(int argc, const char * argv[])
{
    screen_init();
    
    //== 1.Объявление набора фигур ==
    
    rotatable* p1 = new rectangle(point(0,0), point(14,5));
    shape* p2 = new line(point(0,15),17);
    shape* p3 = new myshape(point(15,10), point(27,18));
    
    triangle* p4 = new triangle(point(40,3), point(60,13));
    triangle* p5 = new oblique_cross(point(42,26), point(58,16));
    
    
    shape_refresh();
    
   // cin.get(); //Смотреть исходный набор
    
    //== 2.Ориентация ==
    
    p4->state=2;    // Поворот треугольника влево
    p4->move(5,0);  // Сдвинуть треугольник на 5 точек вправо по оси X
    p5->move(5,0);  // Сдвинуть косой крест на 5 точек вправо по оси X
    
    p1->rotate_right();
    shape_refresh();
    
   // cin.get(); //Смотреть ориентацию
    
    //== 3.Сборка изображения ==
    
    p4->state=0;
    imposition(p4, p5); // Наложить треугольник на крест
    
    triangle* p6 = new myshape_2(point(38,0), point(48,5));
    p6->state=3;
    
    triangle* p7 = new myshape_2(point(38,0), point(48,5));
    p7->state=0;
    
    triangle* p8 = new myshape_2(point(38,0), point(48,5));
    p8->state=3;
    
    
    up(p2,p3);
    up(p1,p2);
    imposition(p7,p2);
    imposition_2(p8,p3);
    imposition_1(p6,p3);
    shape_refresh();
    
   // cin.get(); //Смотреть результат
   // screen_destroy();
    return 0;
}




