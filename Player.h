#pragma once
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// プレイヤークラス
/// </summary>
class Player {
public:
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

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHundle_ = 0u;

	Input* input_ = nullptr;
};