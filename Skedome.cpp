#include "Skedome.h"

void Skedome::Initialize(Model* model) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {};
}

void Skedome::Update() {}

void Skedome::Draw(ViewProjection& view) {
	model_->Draw(worldTransform_, view);
}
