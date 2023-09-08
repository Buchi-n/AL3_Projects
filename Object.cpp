#include "Object.h"
#include<time.h>

void Object::Initialize() {
	objectPos1.wldTForm_.Initialize();
	objectPos2.wldTForm_.Initialize();
	objectPos3.wldTForm_.Initialize();
	objectPos4.wldTForm_.Initialize();
	
	w_ = Sprite::Create(a_, {64, -64}, {1, 1, 1, 1}, {(0.0f), (0.5f)});
	x_ = Sprite::Create(b_, {192, -64}, {1, 1, 1, 1}, {(0.0f), (0.5f)});
	y_ = Sprite::Create(c_, {320, -64}, {1, 1, 1, 1}, {(0.0f), (0.5f)});
	z_ = Sprite::Create(d_, {448, -64}, {1, 1, 1, 1}, {(0.0f), (0.5f)});
}

void Object::Update() {
	//乱数
	time_t CurrentTime = time(nullptr);
	srand((unsigned int) CurrentTime);
	
	if (roopFlag == 0) {//ループ初期化
		ramdomObject1 = rand() % 7;
		ramdomObject2 = rand() % 7;
		ramdomObject3 = rand() % 7;
		ramdomObject4 = rand() % 7;
		objectPos1.wldTForm_.translation_ = {0, -64};
		objectPos2.wldTForm_.translation_ = {110, -64};
		objectPos3.wldTForm_.translation_ = {220, -64};
		objectPos4.wldTForm_.translation_ = {330, -64};
		for (int i = 0; i < 7; i++) {
			if (ramdomObject1 == i) {
				if (i == 0) {
					w_->SetTextureHandle(a_);
				}
				if (i == 1) {
					w_->SetTextureHandle(b_);
				}
				if (i == 2) {
					w_->SetTextureHandle(c_);
				}
				if (i == 3) {
					w_->SetTextureHandle(d_);
				}
				if (i == 4) {
					w_->SetTextureHandle(e_);
				}
				if (i == 5) {
					w_->SetTextureHandle(f_);
				}
				if (i == 6) {
					w_->SetTextureHandle(g_);
				}
				if (i == 7) {
					w_->SetTextureHandle(h_);
				}
			}
			if (ramdomObject2 == i) {
				if (i == 0) {
					x_->SetTextureHandle(a_);
				}
				if (i == 1) {
					x_->SetTextureHandle(b_);
				}
				if (i == 2) {
					x_->SetTextureHandle(c_);
				}
				if (i == 3) {
					x_->SetTextureHandle(d_);
				}
				if (i == 4) {
					x_->SetTextureHandle(e_);
				}
				if (i == 5) {
					x_->SetTextureHandle(f_);
				}
				if (i == 6) {
					x_->SetTextureHandle(g_);
				}
				if (i == 7) {
					x_->SetTextureHandle(h_);
				}
			}
			if (ramdomObject3 == i) {
				if (i == 0) {
					y_->SetTextureHandle(a_);
				}
				if (i == 1) {
					y_->SetTextureHandle(b_);
				}
				if (i == 2) {
					y_->SetTextureHandle(c_);
				}
				if (i == 3) {
					y_->SetTextureHandle(d_);
				}
				if (i == 4) {
					y_->SetTextureHandle(e_);
				}
				if (i == 5) {
					y_->SetTextureHandle(f_);
				}
				if (i == 6) {
					y_->SetTextureHandle(g_);
				}
				if (i == 7) {
					y_->SetTextureHandle(h_);
				}
			}
			if (ramdomObject2 == i) {
				if (i == 0) {
					z_->SetTextureHandle(a_);
				}
				if (i == 1) {
					z_->SetTextureHandle(b_);
				}
				if (i == 2) {
					z_->SetTextureHandle(c_);
				}
				if (i == 3) {
					z_->SetTextureHandle(d_);
				}
				if (i == 4) {
					z_->SetTextureHandle(e_);
				}
				if (i == 5) {
					z_->SetTextureHandle(f_);
				}
				if (i == 6) {
					z_->SetTextureHandle(g_);
				}
				if (i == 7) {
					z_->SetTextureHandle(h_);
				}
			}
		}
		roopFlag = 1;
	}
	if (roopFlag == 1) {//オブジェクト移動
		objectPos1.wldTForm_.translation_.y += objectSpeed;
		objectPos2.wldTForm_.translation_.y += objectSpeed;
		objectPos3.wldTForm_.translation_.y += objectSpeed;
		objectPos4.wldTForm_.translation_.y += objectSpeed;
		if (objectPos1.wldTForm_.translation_.y > 800) {
			roopFlag = 0;
		}
	}
	w_->SetPosition(
	    {objectPos1.wldTForm_.translation_.x, objectPos1.wldTForm_.translation_.y});
	x_->SetPosition(
		{objectPos2.wldTForm_.translation_.x, objectPos2.wldTForm_.translation_.y});
	y_->SetPosition(
		{objectPos3.wldTForm_.translation_.x, objectPos3.wldTForm_.translation_.y});
	z_->SetPosition(
		{objectPos4.wldTForm_.translation_.x, objectPos4.wldTForm_.translation_.y});
}

void Object::Draw() { 
	w_->Draw();
	x_->Draw();
	y_->Draw();
	z_->Draw();
}

Object::~Object() { 
	delete w_;
	delete x_;
	delete y_;
	delete z_;
}

