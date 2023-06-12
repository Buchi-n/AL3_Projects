#pragma once
#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "Enemy.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Skedome.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	Sprite* sprite_ = nullptr;
	uint32_t playerTextureHandle_ = 0u;
	uint32_t enemyTextureHandle_ = 0u;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	//プレイヤー処理
	Model* playerModel_ = nullptr;
	WorldTransform playerWorldTransform_;
	ViewProjection viewProjection_;

	Player* player_ = nullptr;

	//3Dモデル:天球
	Model* modelSkydome_ = nullptr;
	Skedome* skydome_ = nullptr;

	//敵処理
	Model* enemyModel_ = nullptr;
	WorldTransform enemyWorldTransform_;
	const float kEnemySpeedY = 0.003f;
	const float kEnemySpeedZ = -0.1f;

	Enemy* enemy_ = nullptr;

	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
	// float imputFloat3[3] = { 0,0,0 };
};