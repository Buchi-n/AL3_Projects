//#include "Enemy.h"
//
//void Enemy::Initialize(Vector2 pos) {
//	// プレイヤーテクスチャ読み込み
//	textureHandle_ = TextureManager::Load("Enemy.png");
//	
//	// スプライト生成
//	sprite_ = Sprite::Create(textureReticle, {640, 0}, {1, 1, 1, 1}, {(0.5f), (0.5f)});
//	enemy_ Initialize();
//	// 引数で受け取った初期座標をセット
//	worldTransform_.translation_ = pos;
//
//}
//
//void Enemy::Update() {
//	worldTransform_.UpdateMatrix();
//}
//void Enemy::Draw() {
//	// 描画(※3Dを追加する場合は別の関数を作成:ここは2D専用)
//	sprite_->Draw();
//}

//void EnemyBullet::OnCollision() { HP -= 1; }