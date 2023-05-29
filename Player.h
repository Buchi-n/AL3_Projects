#pragma once
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "PlayerBullet.h"
#include <list>
#include "MathUtilitie.h"

/// <summary>
/// プレイヤークラス
/// </summary>
class Player {
public:
	/// <summary>
	///デストラクタ
	/// </summary>
	~Player();
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHundle">テクスチャ</param>
	void Initialize(Model* model, uint32_t textureHundle);
	/// <summary>
	/// 更新処理
	/// </summary>
	void Updete();
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection& viewProjection);
	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();
	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHundle_ = 0u;
	Input* input_ = nullptr;
	//弾
	std::list<PlayerBullet*> bullets_;
};