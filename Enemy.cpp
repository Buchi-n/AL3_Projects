#include "Enemy.h"
#include <assert.h>

Enemy::~Enemy() {
	//bullet_の開放
	for (EnemyBullet* bullet : bullets_)
	{
		delete bullet;
	}
}

void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	//NULLポインタチェック
	assert(model);	

	frame = 0;

	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("uvChecker.png");
	//ワールドトランスフォーム初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;

}

void Enemy::Update() {
	//デスフラグの立った弾を削除
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead())
		{
			delete bullet;
			return true;
		}
		return false;
	});

	//フェーズ
	switch (phase_) { 
	case Phase::Approch:
	default:
		//移動(ベクトルを加算)
		worldTransform_.translation_.x += velocity_.x;
		worldTransform_.translation_.y += velocity_.y;
		worldTransform_.translation_.z += velocity_.z;	
		//既定の位置に到達したら離脱
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		//移動(ベクトルを加算)
		worldTransform_.translation_.x += -velocity_.x;
		worldTransform_.translation_.y += velocity_.y;
		worldTransform_.translation_.z += -velocity_.z;	
		break;
	}
	//ワールドトランスフォーム更新
	worldTransform_.UpdateMatrix();

	//弾更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	// 弾描画
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}

	frame++;
	if (frame % 60 == 0) {
		Fire();
	}
	if (frame >= 120)
	{
		frame = 0;
	}
}

void Enemy::Fire() {
	// 弾速
	const float kBulletSpeed = 0.5f;
	Vector3 velocity(0, 0, -kBulletSpeed);
	// 速度ベクトルを敵の向きに合わせて回転させる
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);
	// 弾を生成し初期化
	EnemyBullet* newBullet = new EnemyBullet;
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	// 弾を登録する
	bullets_.push_back(newBullet);
}
