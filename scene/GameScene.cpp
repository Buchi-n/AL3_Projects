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
	delete skydome_;
	delete modelSkydome_;
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
	viewProjection_.Initialize();

	player_ = new Player();
	player_->Initialize(playerModel_, playerTextureHandle_);

	//敵初期化処理
	enemyTextureHandle_ = TextureManager::Load("uvChecker.png");
	enemyModel_ = Model::Create();
	enemyWorldTransform_.Initialize();

	enemy_ = new Enemy();
	Vector3 enemyVelocity(0, kEnemySpeedY,kEnemySpeedZ);
	enemyWorldTransform_.translation_.x = 15.0f;
	enemyWorldTransform_.translation_.z = 40.0f;
	enemy_->Initialize(enemyModel_, enemyWorldTransform_.translation_, enemyVelocity);

	//レールカメラ
	railCamera_ = new RailCamera();
	railCamera_->Initialize(railcameraWorldTransform_);

	//敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

	debugCamera_ = new DebugCamera(WinApp::kWindowWidth, WinApp::kWindowHeight);

	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	skydome_ = new Skedome();
	skydome_->Initialize(modelSkydome_);
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() {
	player_->Updete();
	enemy_->Update();
	skydome_->Update();
	railCamera_->Update();
	debugCamera_->Update();
	CheckAllCollisions();

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_B)) {
		isDebugCameraActive_ = true;
	}

#endif //  _DEBUG

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
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
	skydome_->Draw(viewProjection_);
	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);
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
	Vector3 distAB;
	//距離加算
	float distAdd;
	//半径格納
	float radA, radB;
	//半径加算
	float radAdd;

	//自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	//敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

	#pragma region 自キャラと敵弾の当たり判定

	//自キャラの半径
	radA = player_->GetRad();
	//自キャラの座標
	posA = player_->GetWorldPosition();

	//自キャラと敵弾全ての当たり判定
	for (EnemyBullet* bullet : enemyBullets) {
		//敵弾の半径
		radB = bullet->GetRad();
		//敵弾の座標
		posB = bullet->GetWorldPosition();
		//AとBの距離を求める
		distAB.x = (posB.x - posA.x) * (posB.x - posA.x);
		distAB.y = (posB.y - posA.y) * (posB.y - posA.y);
		distAB.z = (posB.z - posA.z) * (posB.z - posA.z);
		distAdd = distAB.x + distAB.y + distAB.z;
		radAdd = radA+radB;
		//弾と弾の交差判定
		if (distAdd <= radAdd * radAdd) {
			//自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			//敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
	#pragma endregion

	#pragma region 自弾と敵キャラの当たり判定

	//敵キャラの半径
	radA = enemy_->GetRad();
	// 敵キャラの座標
	posA = enemy_->GetWorldPosition();

	// 敵キャラと自弾の当たり判定
	for (PlayerBullet* bullet : playerBullets) {
		//自弾の半径
		radB = bullet->GetRad();
		// 自弾の座標
		posB = bullet->GetWorldPosition();
		// AとBの距離を求める
		distAB.x = (posB.x - posA.x) * (posB.x - posA.x);
		distAB.y = (posB.y - posA.y) * (posB.y - posA.y);
		distAB.z = (posB.z - posA.z) * (posB.z - posA.z);
		distAdd = distAB.x + distAB.y + distAB.z;
		radAdd = radA + radB;
		// 弾と弾の交差判定
		if (distAdd <= radAdd * radAdd) {
			// 敵キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();
			// 自弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
	#pragma endregion

	#pragma region 自弾と敵弾の当たり判定
	for (PlayerBullet* pBullet : playerBullets) {
		//自弾の半径
		radA = pBullet->GetRad();
		//自弾の座標
		posA = pBullet->GetWorldPosition();

		// 自弾と敵弾全ての当たり判定
		for (EnemyBullet* eBullet : enemyBullets) {
			//敵弾の半径
			radB = eBullet->GetRad();
			// 敵弾の座標
			posB = eBullet->GetWorldPosition();
			// AとBの距離を求める
			distAB.x = (posB.x - posA.x) * (posB.x - posA.x);
			distAB.y = (posB.y - posA.y) * (posB.y - posA.y);
			distAB.z = (posB.z - posA.z) * (posB.z - posA.z);
			distAdd = distAB.x + distAB.y + distAB.z;
			radAdd = radA + radB;
			// 弾と弾の交差判定
			if (distAdd <= radAdd * radAdd) {
				// 敵弾の衝突時コールバックを呼び出す
				eBullet->OnCollision();
				// 自弾の衝突時コールバックを呼び出す
				pBullet->OnCollision();
			}
		}
	}
	#pragma endregion
}
