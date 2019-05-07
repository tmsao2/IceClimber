#include "Stage.h"
#include <DxLib.h>


Stage::Stage()
{
	int fmf_h = DxLib::FileRead_open("Stage/Stage2.fmf", false);

	DxLib::FileRead_read(&_fmfdata, sizeof(_fmfdata), fmf_h);

	std::vector<char> _tmp;
	_tmp.resize(_fmfdata.mapWidth * _fmfdata.mapHeight);
	DxLib::FileRead_read(&_tmp[0], _tmp.size(), fmf_h);

	DxLib::FileRead_close(fmf_h);

	_stageRange.size.width = _fmfdata.mapWidth*_fmfdata.chipW * 2;
	_stageRange.size.height = _fmfdata.mapHeight*_fmfdata.chipH * 2;

	_stageRange.center.x = _stageRange.size.width / 2;
	_stageRange.center.y = _stageRange.size.height / 2;


	data.range.size.width = _fmfdata.mapWidth;
	data.range.size.height = _fmfdata.mapHeight;
	data.chipSize = _fmfdata.chipH;


	_stagedata.resize(_fmfdata.mapWidth * _fmfdata.mapHeight);

	for (int i = 0; i < _fmfdata.mapHeight; i++) {
		for (int j = 0; j < _fmfdata.mapWidth; j++) {
			_stagedata[i * _fmfdata.mapWidth + j] = _tmp[i * _fmfdata.mapWidth + j];
		}
	}

	int e_fmf_h = DxLib::FileRead_open("Stage/Enemy.fmf", false);
	DxLib::FileRead_read(&e_fmfdata, sizeof(e_fmfdata), e_fmf_h);

	std::vector<char> e_tmp;

	e_tmp.resize(e_fmfdata.mapWidth * e_fmfdata.mapHeight);
	DxLib::FileRead_read(&e_tmp[0], e_tmp.size(), e_fmf_h);

	DxLib::FileRead_close(e_fmf_h);

	
	_enemydata.resize(e_fmfdata.mapWidth * e_fmfdata.mapHeight);

	for (int i = 0; i < e_fmfdata.mapHeight; i++) {
		for (int j = 0; j < e_fmfdata.mapWidth; j++) {
			_enemydata[i*e_fmfdata.mapWidth + j] = e_tmp[i*e_fmfdata.mapWidth + j];
		}
	}
	_readX = 0;
}


Stage::~Stage()
{
}

const Rect & Stage::GetStageRange() const
{
	return _stageRange;
}

const std::vector<char> Stage::GetEnemyData(int minX, int maxX)
{
	int L = max(minX / (e_fmfdata.chipW * 2), _readX);
	int R = maxX / (e_fmfdata.chipW * 2) + 1;
	if (R <= _readX)return std::vector<char>();

	auto idxL = L * e_fmfdata.mapHeight;
	auto idxR = min(R * e_fmfdata.mapHeight, _enemydata.size());
	auto begin = _enemydata.begin() + idxL;
	auto end = min(_enemydata.begin() + idxR, _enemydata.end());
	_readX = R;
	return std::vector<char>(begin, end);
}

const std::vector<char> Stage::GetStageData()
{
	return std::vector<char>(_stagedata.begin(), _stagedata.end());
}

void Stage::SetStageData(int num,int id)
{
	_stagedata[num] = id;
}

const STAGE & Stage::GetData()
{
	return data;
}

