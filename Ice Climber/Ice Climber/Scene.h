#pragma once
class Peripheral;
// シーン管理のための基底クラス
// 純粋仮想クラス
class Scene
{
public:
	Scene();
	virtual ~Scene();

	// シーンの更新
	virtual void Update(const Peripheral& p) = 0;
};

