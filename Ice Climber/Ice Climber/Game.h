#pragma once
#include <memory>
#include "Geometry.h"

class Scene;

//ゲーム全体を制御するクラス

class Game
{
private:
	Game();					//生成禁止
	Game(const Game&);		//コピー禁止
	void operator=(const Game&)const;	//代入禁止

	///シーン管理
	std::shared_ptr<Scene> _scene;
public:
	Size screen_size;

	static Game& Instance() {
		static Game instance;
		return instance;
	}
	~Game();

	///キャラクターの拡大率を返す
	float GetObjectScale()const;
	///重力を返す
	float GetGravity() const;
	///ウィンドウのサイズ
	const Size GetWindowSize() const;

	///初期化系
	void Initialize();

	///中にループ
	void Run();

	///後処理
	void Terminate();

	///シーンの変更
	void ChangeScene(Scene* scene);
};

