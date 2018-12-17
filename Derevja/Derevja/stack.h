
//  stack.h

#ifndef Derevja_stack_h
#define Derevja_stack_h

template <class Item> class STACK
{
    Item * S;
    int t;
public:
    
    STACK(int maxt) : S(new Item[maxt]), t(0) { }
    int empty() const { return t==0; }
    void push(Item item) { S[t++] = item; }
    Item pop() {return (t ? S[--t] : 0); }
    
};


#endif
