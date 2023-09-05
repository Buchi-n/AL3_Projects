#pragma once
#include"Sprite.h"

class Object {
public:
    void Initialize();
    
    void Update(); 

    void Draw();
private:
    Sprite* a_= nullptr;//x2
    Sprite* b_= nullptr;//x3
    Sprite* c_= nullptr;//-2
    Sprite* d_= nullptr;//-3

    Vector2 objectPos;  
};
