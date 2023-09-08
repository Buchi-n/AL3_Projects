#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	// 各種 delete を記載
	delete player_;
	delete score_;
	delete object_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// プレイヤーテクスチャ読み込み（gameScene.cpp > Initialize にも記載）
	uint32_t textureBG[3] = {
	    TextureManager::Load("bg/title.png"),
	    TextureManager::Load("bg/gamePlay.png"),
	    TextureManager::Load("bg/result.png"),
	};

	// テクスチャロード（用途ごとのcpp > Initialize にも記載）
	TextureManager::Load("bg/title.png");    // タイトル
	TextureManager::Load("bg/gamePlay.png"); // ゲームプレイ
	TextureManager::Load("bg/result.png");   // リザルト
	TextureManager::Load("player.png");      // プレイヤー
	TextureManager::Load("num/0.png"), TextureManager::Load("num/1.png");
	TextureManager::Load("num/2.png"), TextureManager::Load("num/3.png");
	TextureManager::Load("num/4.png"), TextureManager::Load("num/5.png");
	TextureManager::Load("num/6.png"), TextureManager::Load("num/7.png");
	TextureManager::Load("num/8.png"), TextureManager::Load("num/9.png"); // 数字

	for (int i = 0; i < 3; i++) {
		// スプライトデータ null 代入
		spriteBG_[i] = nullptr;
		// スプライトデータ初期化
		spriteBG_[i] = Sprite::Create(textureBG[i], {0, 0}, {1, 1, 1, 1}, {0.0f, 0.0f});
	}

	// プレイヤー初期化
	player_ = new Player();
	// 初期座標を入力
	player_->initialize({220, 700});
	// スコア初期化
	score_ = new Score();
	score_->Initialize();
	// 初期座標を入力（アンカー右端）
	score_->SetPos({360, 100});
	//オブジェクト初期化
	object_ = new Object();
	object_->Initialize();
}

void GameScene::Update() {

	// シーン処理
	switch (scene_) {
	// タイトル
	case Scene::Title:
		// エンターキー押下
		if (input_->TriggerKey(DIK_RETURN)) {
			// シーン遷移 ゲームプレイ
			scene_ = Scene::GamePlay;
			// スコア描画位置変更
			score_->SetPos({360, 100});
		}
		break;
	// ゲームプレイ
	case Scene::GamePlay:
		// プレイヤー更新
		player_->Update();
		// スコア更新
		score_->AddScore(addScore_);
		//オブジェクト更新
		object_->Update();

		// 　エンターキー押下（デバッグ用）
		if (input_->TriggerKey(DIK_RETURN)) {
			// シーン遷移 リザルト
			scene_ = Scene::Result;
			// スコア描画位置変更 < 本実装時は[シーン遷移 リザルト と同じ if 文内に入れる]
			score_->SetPos({360, 400});
		}

		break;
		// リザルト
	case Scene::Result:
		// エンターキー押下
		if (input_->TriggerKey(DIK_RETURN)) {
			// シーン遷移 タイトル
			scene_ = Scene::Title;
			GameScene::Initialize();
		}

		break;
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

	// シーン処理
	switch (scene_) {
	// タイトル
	case Scene::Title:
		spriteBG_[0]->Draw();
		break;
	// ゲームプレイ
	case Scene::GamePlay:
		spriteBG_[1]->Draw();
		break;
		// リザルト
	case Scene::Result:
		spriteBG_[2]->Draw();
		break;
	}

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

	// シーン処理
	switch (scene_) {
	// タイトル
	case Scene::Title:

		break;
	// ゲームプレイ
	case Scene::GamePlay:
		// プレイヤー描画
		player_->Draw();
		//オブジェクト描画
		object_->Draw();
		// スコア描画
		score_->Draw(score_->GetScore());

		break;
		// リザルト
	case Scene::Result:
		// スコア描画
		score_->Draw(score_->GetScore());

		break;
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
