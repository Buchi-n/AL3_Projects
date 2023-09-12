#pragma once
#include <Enums.h>
#include <Input.h>
#include <Model.h>
#include <Sprite.h>
#include <WorldTransform.h>

class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos">初期座標(vector2型) 入力例{19,19}</param>
	void initialize(Vector2 pos);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// プレイヤーポジションゲッター
	/// </summary>
	/// <returns></returns>
	Vector2 GetPos() {
		return {player_.wldTForm_.translation_.x, player_.wldTForm_.translation_.y};
	}

	/// <summary>
	/// プレイヤー数ゲッター
	/// </summary>
	/// <returns></returns>
	int GetVal() { return player_.val_; }

	/// <summary>
	/// プレイヤー数セッター
	/// </summary>
	/// <param name="val">0=add 1=pull</param>
	void ChangeVal(int val, int add_pull) {
		if (add_pull == 0) {
			player_.val_ += val;
		} else if (add_pull == 1) {
			player_.val_ -= val;
		}
	}

private:
	// キー入力用インプット
	Input* input_ = nullptr;
	// スプライトデータ
	Sprite* spritePlayer_ = nullptr;
	// プレイヤーデータ(詳細:Enums.h)
	Status player_;
};