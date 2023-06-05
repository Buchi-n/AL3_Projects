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
	enemyWorldTransform_.translation_.x = 15.0f;
	enemyWorldTransform_.translation_.z = 40.0f;
	enemy_->Initialize(enemyModel_, enemyWorldTransform_.translation_, enemyVelocity);

	//敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

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

void GameScene::CheckAllCollisions() {
	//衝突対象AとBの座標
	Vector3 posA, posB;
	// 距離格納
	Vector3 abDist;
	//半径格納
	int aRadian = 10;
	int bRadian = 10;

	//自弾リストの取得
	const std::list<PlayerBullet*>& playeBullets = player_->GetBullets();
	//敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

	#pragma region 自キャラと敵弾の当たり判定

	//自キャラの座標
	posA = player_->GetWorldPosition();

	//自キャラと敵弾全ての当たり判定
	for (EnemyBullet* bullet : enemyBullets) {
		//敵弾の座標
		posB = bullet->GetWorldPosition();
		//AとBの距離を求める
		abDist.x = (posA.x - posB.x) * (posA.x - posB.x);
		abDist.y = (posA.y - posB.y) * (posA.y - posB.y);
		abDist.z = (posA.z - posB.z) * (posA.z - posB..z);
	}
	#pragma endregion

	#pragma region 自弾と敵キャラの当たり判定
	#pragma endregion

	#pragma region 自弾と敵弾の当たり判定
	#pragma endregion
}
