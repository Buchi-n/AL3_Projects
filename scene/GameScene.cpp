#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete playerModel_;
	delete player_;
	delete enemyModel_;
	delete enemy_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	
	//プレイヤー初期化処理
	playerTextureHandle_ = TextureManager::Load("sample.png");
	playerModel_ = Model::Create();
	playerWorldTransform_.Initialize();
	playerViewProjection_.Initialize();

	player_ = new Player();
	player_->Initialize(playerModel_, playerTextureHandle_);

	//敵初期化処理
	enemyTextureHandle_ = TextureManager::Load("uvChecker.png");
	enemyModel_ = Model::Create();
	enemyWorldTransform_.Initialize();
	enemyViewProjection_.Initialize();

	enemy_ = new Enemy();
	Vector3 enemyVelocity(0, kEnemySpeedY,kEnemySpeedZ);
	enemy_->Initialize(enemyModel_, enemyWorldTransform_.translation_, enemyVelocity);

	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&playerViewProjection_);
}

void GameScene::Update() {
	player_->Updete();
	enemy_->Update();

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		isDebugCameraActive_ = true;
	}

#endif //  _DEBUG

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		playerViewProjection_.matView = debugCamera_->GetViewProjection().matView;
		playerViewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		playerViewProjection_.TransferMatrix();
	} else {
		playerViewProjection_.UpdateMatrix();
	}
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
	// model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	player_->Draw(playerViewProjection_);
	enemy_->Draw(enemyViewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}