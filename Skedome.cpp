#include "Skedome.h"

void Skedome::Initialize() {
	//worldTransform_.Initialize();
	//viewProjection_.Initialize();
}

void Skedome::Update() {}

void Skedome::Draw() {
	model_->Draw(worldTransform_, viewProjection_);
}
