#include "Enemy.h"
#include <assert.h>
#include "Player.h"

Enemy::~Enemy() {
	//bullet_の開放
	//for (EnemyBullet* bullet : bullets_)
	//{
	//	delete bullet;
	//}
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
	//bullets_.remove_if([](EnemyBullet* bullet) {
	//	if (bullet->IsDead())
	//	{
	//		delete bullet;
	//		return true;
	//	}
	//	return false;
	//});

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
	//for (EnemyBullet* bullet : bullets_) {
	//	bullet->Update();
	//}
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	// 弾描画
	//for (EnemyBullet* bullet : bullets_) {
	//	bullet->Draw(viewProjection);
	//}

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
	const float kBulletSpeed = -0.05f;
	Vector3 move;
	//自キャラのワールド座標取得
	player_->GetWorldPosition();
	// 敵キャラのワールド座標取得
	GetWorldPosition();
	// 敵→自の差分ベクトル
	move.x = GetWorldPosition().x - player_->GetWorldPosition().x;
	move.y = GetWorldPosition().y - player_->GetWorldPosition().y;
	move.z = GetWorldPosition().z - player_->GetWorldPosition().z;
	
	//正規化
	Normalize(move);
	// ベクトルの長さを早さに合わせる
	Vector3 velocity(move.x*kBulletSpeed, move.y*kBulletSpeed, move.z*kBulletSpeed);
	// 速度ベクトルを敵の向きに合わせて回転させる
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);
	// 弾を生成し初期化
	EnemyBullet* newBullet = new EnemyBullet;
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);
	// 弾を登録する
	//bullets_.push_back(newBullet);
}

Vector3 Enemy::GetWorldPosition() {
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド座標の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void Enemy::OnCollision() {
	//何もしない
}
