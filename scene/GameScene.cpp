#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	// 各種 delete を記載
	delete player_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// テクスチャロード（用途ごとのcpp > Initialize にも記載）
	TextureManager::Load("uvChecker.png"); // プレイヤー
	TextureManager::Load("num/0.png"), TextureManager::Load("num/1.png");
	TextureManager::Load("num/2.png"), TextureManager::Load("num/3.png");
	TextureManager::Load("num/4.png"), TextureManager::Load("num/5.png");
	TextureManager::Load("num/6.png"), TextureManager::Load("num/7.png");
	TextureManager::Load("num/8.png"), TextureManager::Load("num/9.png"); // 数字

	// プレイヤー初期化
	player_ = new Player();
	// 初期座標を入力
	player_->initialize({10, 10});
	// スコア初期化
	score_ = new Score();
	score_->Initialize();
	// 初期座標を入力（アンカー右端）
	score_->SetPos({360, 100});
}

void GameScene::Update() {
	// プレイヤー更新
	player_->Update();
	// スコア更新
	score_->AddScore(addScore_);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	player_->Draw();
	score_->Draw(score_->GetScore());
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
