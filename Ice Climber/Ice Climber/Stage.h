#pragma once
#include "Geometry.h"
#include <vector>

struct FMF
{
	int identifier;
	int size;
	int mapWidth;
	int mapHeight;
	char chipH;
	char chipW;
	char layerCount;
	char bitCount;
};

struct STAGE
{
	Rect range;
	int chipSize;
};

class Stage
{
private:
	Rect _stageRange;
	int _readX;

	//ステージ情報
	FMF _fmfdata;
	FMF e_fmfdata;
	STAGE data;
	//ステージのエネミー情報
	std::vector<char> _enemydata;
	std::vector<char> _stagedata;
public:
	Stage();
	~Stage();

	//ステージの範囲を渡す
	const Rect& GetStageRange()const;
	//現在の画面内の敵情報を渡す
	const std::vector<char> GetEnemyData(int minX, int maxX);
	//現在の画面内の足場情報を渡す
	const std::vector<char> GetStageData();

	void SetStageData(int num,int id);

	const STAGE& GetData();
};
