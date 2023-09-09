#pragma once
#include "Sprite.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include <Enums.h>
#include<time.h>


class Object {
public:
	void Initialize();

	void Update();

	void Draw();

	~Object();

private:
	Sprite* w_ = nullptr;
	Sprite* x_ = nullptr;
	Sprite* y_ = nullptr;
	Sprite* z_ = nullptr;

	Status objectPos1;
	Status objectPos2;
	Status objectPos3;
	Status objectPos4;

	uint32_t a_ = TextureManager::Load("num/0.png");//x2

	uint32_t b_ = TextureManager::Load("num/1.png");//x3

	uint32_t c_ = TextureManager::Load("num/2.png");//-2

	uint32_t d_ = TextureManager::Load("num/3.png");//-3

	uint32_t e_ = TextureManager::Load("num/4.png");//+2

	uint32_t f_ = TextureManager::Load("num/5.png");//+3

	uint32_t g_ = TextureManager::Load("num/6.png");//-10

	uint32_t h_ = TextureManager::Load("num/7.png");//+10

	int roopFlag = 0;
	int objectSpeed = 10;
	int ramdomObject1 = 0;
	int ramdomObject2 = 0;
	int ramdomObject3 = 0;
	int ramdomObject4 = 0;
};
