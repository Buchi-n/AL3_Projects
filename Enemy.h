#pragma once
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"
#include <list>
#include "MathUtilitie.h"
//自機クラスの前方宣言
class Player;

    /// <summary>
/// 敵
/// </summary>
class Enemy {
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期座標</param>
	/// <param name="velocity">速度</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// 弾発射
	/// </summary>
	void Fire();

	/// <summary>
	/// プレイヤーｹﾞｯﾀｰ
	/// </summary>
	/// <param name="player"></param>
	void SetPlayer(Player* player) { player_ = player; }
	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetWorldPosition();

	/// <summary>
	/// 衝突を検出したら呼び出されるコールバック関数
	/// </summary>
	void OnCollision();

	// 弾リストを取得
	const std::list<EnemyBullet*>& GetBullets() { return bullets_; } 

	/// <summary>
	/// ｹﾞｯﾀｰ(半径)
	/// </summary>
	/// <returns>半径</returns>
	float GetRad() { return rad_; }

	private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	//速度
	Vector3 velocity_;

	//フェーズ
	enum class Phase {
		Approch, //接近
		Leave, //離脱
	};
	Phase phase_ = Phase::Approch;

	// 弾
	std::list<EnemyBullet*> bullets_;
	uint32_t frame;

	//自キャラ
	Player* player_ = nullptr;

	// 半径
	float rad_ = 1.0f;
};
