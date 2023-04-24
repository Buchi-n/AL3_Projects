
#include "Player.h"
#include "cassert"

void Player::Initialize(Model* model, uint32_t texturehandle)
{ 
	assert(model);
	model_ = model;
	textureHandle_ = texturehandle;
	worldTransform_;
}

void Player::Update()
{
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
