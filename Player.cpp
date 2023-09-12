#include "Player.h"

void Player::initialize(Vector2 pos) {
	// ワールドトランスフォーム初期化
	player_.wldTForm_.Initialize();
	player_.wldTForm_.translation_ = {pos.x, pos.y};
	// インプット初期化
	input_ = Input::GetInstance();
	// プレイヤーテクスチャ読み込み（gameScene.cpp > Initialize にも記載）
	uint32_t texturePlayer = TextureManager::Load("player.png");
	// スプライトデータ初期化
	spritePlayer_ = Sprite::Create(texturePlayer, {pos.x, pos.y}, {1, 1, 1, 1}, {0.5f, 0.5f});
	// プレイヤー移動速度
	player_.moveSpeed_ = 5;
}

void Player::Update() {
	// プレイヤー移動処理
	if (input_->PushKey(DIK_A)) {
		player_.wldTForm_.translation_.x -= player_.moveSpeed_;
	}
	if (input_->PushKey(DIK_D)) {
		player_.wldTForm_.translation_.x += player_.moveSpeed_;
	}
	if (player_.wldTForm_.translation_.x - 16 < 0) {
		player_.wldTForm_.translation_.x += player_.moveSpeed_;
	}
	if (player_.wldTForm_.translation_.x + 16 > 440) {
		player_.wldTForm_.translation_.x -= player_.moveSpeed_;
	}

	// プレイヤー描画位置更新
	spritePlayer_->SetPosition(
	    {player_.wldTForm_.translation_.x, player_.wldTForm_.translation_.y});

}

void Player::Attack() {}

void Player::Draw() {
	// プレイヤー描画(※3Dを追加する場合は別の関数を作成:ここは2D専用)
	spritePlayer_->Draw();
}

Player::~Player() {
	// デリート
	delete spritePlayer_;
}