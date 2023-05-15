#include "PlayerBullet.h"
#include <cassert>
#include "WorldTransform.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position) {
//NULLポインタチェック
	assert(model);

	model_ = model;
	//テクスチャ読み込み
	textureHundle_ = TextureManager::Load("cube.jpg");
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update() {
	//ワールドトランスフォーム更新
	worldTransform_.UpdateMatrix();

}

void PlayerBullet::Draw(const ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection, textureHundle_);
}
