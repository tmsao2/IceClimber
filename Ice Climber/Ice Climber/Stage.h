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

	//�X�e�[�W���
	FMF _fmfdata;
	FMF e_fmfdata;
	STAGE data;
	//�X�e�[�W�̃G�l�~�[���
	std::vector<char> _enemydata;
	std::vector<char> _stagedata;
public:
	Stage();
	~Stage();

	//�X�e�[�W�͈̔͂�n��
	const Rect& GetStageRange()const;
	//���݂̉�ʓ��̓G����n��
	const std::vector<char> GetEnemyData(int minX, int maxX);
	//���݂̉�ʓ��̑������n��
	const std::vector<char> GetStageData();

	void SetStageData(int num,int id);

	const STAGE& GetData();
};
