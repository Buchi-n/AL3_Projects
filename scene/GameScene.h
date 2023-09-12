#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Enums.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "SafeDelete.h"
#include "Score.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Object.h"

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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	// プレイヤー用
	Player* player_ = nullptr;
	// スコア用
	Score* score_ = nullptr;
	// スコア増加量
	int addScore_ = 9;
	//オブジェクト
	Object* object_ = nullptr;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	// ゲームシーン
	Scene scene_ = Scene::Title;
	// スプライトデータ
	Sprite* spriteBG_[3];
};