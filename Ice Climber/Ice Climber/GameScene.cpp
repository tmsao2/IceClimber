#include "GameScene.h"
#include "ResultScene.h"
#include <DxLib.h>
#include <string>
#include "Game.h"
#include "Peripheral.h"
#include "Player.h"
#include "BackGround.h"
#include "EnemyFactory.h"
#include "Enemy.h"
#include "CharacterObject.h"
#include "CollisionDetector.h"
#include "Stage.h"
#include "Ground.h"
#include "Camera.h"

const int screen_x_size = 512;
const int screen_y_size = 480;

const int offset = 16;
const char* grImg = "image/Ground.png";
const char* crImg = "image/Condor.png";
const char* itImg = "image/nasu.png";
const char* goImg = "image/GameOver.png";

void GameScene::StartUpdate(const Peripheral & p)
{

}

void GameScene::NormalUpdate(const Peripheral & p)
{
	auto scroll = camera->ScrollValue();

	player->Update(p);		//プレイヤーの更新
	for (auto& enemy : efactory->GetLegion()) {			//敵の更新
		enemy->Update();
	}

	//ブロックとプレイヤーの当たり判定
	for (int i = 0; i < stageheight; i++) {
		for (int j = 0; j < stagewidth; j++) {
			int idx = (stage->GetStageData()[j + i * stagewidth]);
			if (idx != 4) {
				Position2 pos = Position2(j * blockSize * 2 + blockSize, i*blockSize * 2 - (stageheight*blockSize * 2 - screen_y_size) + blockSize - offset * 2);
				for (auto& prect : player->GetActionRects()) {
					if (prect.rt == RectType::damage) {
						Rect rc;
						rc.center = pos;
						rc.size.width = blockSize * 2;
						rc.size.height = blockSize * 2;
						if (CollisionDetector::IsCollided(player->GetActuralRectForAction(prect.rc), rc)) {
							if (player->GetFall()) {
								player->OnGround(rc.Top());
								camera->CheckPos(pos);
							}
							else {
								player->HitBlock(rc);
								if (idx != 0) {
									br_blocks.push_back(BREAK_BLOCK(Position2f(pos.x, pos.y), idx, Vector2f(player->GetTurn() ? 1.0f : -1.0f, -5.0f), player->GetTurn()));
									stage->SetStageData(j + i * stagewidth, 4);
									++blockCnt;
								}
							}
						}
					}
				}
				DxLib::DrawRectRotaGraph(pos.x, pos.y - scroll, idx*blockSize, 0, blockSize, blockSize, 2, DX_PI / 180 * 45, blockgh, true, false);
				//DebugDraw(pos);
			}
		}
	}
	if (!br_blocks.empty()) {
		for (auto& block : br_blocks) {
			block.pos += block.vel;
			DxLib::DrawRectRotaGraph(block.pos.x, block.pos.y - scroll, block.id*blockSize, 0, blockSize, blockSize, 2, block.vel.y >= 0 ? DX_PI / 180 * 90 : 0, blockgh, true, !block.turnflag);
			block.vel.y += Game::Instance().GetGravity();
		}
	}
	player->Draw();
	if (player->GetPos().y > camera->GetViewport().Bottom()) {
		DxLib::DrawRotaGraph(256, 240,2,0, gameovergh, true);
		if (p.IsPressing(PAD_INPUT_10)) {
			Game::Instance().ChangeScene(new ResultScene());
		}
	}
}

void GameScene::BonusUpdate(const Peripheral & p)
{

}

void GameScene::DebugDraw(Position2 pos)
{
	Rect rc;
	rc.center = pos;
	rc.size.width = blockSize * 2;
	rc.size.height = blockSize * 2;
	auto scroll = camera->ScrollValue();

	DxLib::DrawBox(rc.Left(), rc.Top()-scroll, rc.Right(), rc.Bottom() - scroll, 0xff0000, false);
}

GameScene::GameScene()
{
	stage.reset(new Stage());
	camera.reset(new Camera(*stage));
	player.reset(new Player(*camera));
	ground.reset(new Ground());
	background.reset(new BackGround(*camera));
	efactory.reset(new EnemyFactory(*camera, *player, *ground));
	camera->SetFocus(player);
	_updater = &GameScene::NormalUpdate;
	blockgh = DxLib::LoadGraph(grImg);
	condorgh = DxLib::LoadGraph(crImg);
	nasugh = DxLib::LoadGraph(itImg);
	gameovergh=DxLib::LoadGraph(goImg);
	blockSize = stage->GetData().chipSize;
	stageheight = stage->GetData().range.Height();
	stagewidth = stage->GetData().range.Width();
}


GameScene::~GameScene()
{
}

void GameScene::Update(const Peripheral & p)
{
	camera->Update();

	const std::string enemyname[] = { "","Topi","Nitpicker"};
	auto enemies = stage->GetEnemyData(camera->GetViewport().Left(), camera->GetViewport().Right());
	auto& mapsize = stage->GetStageRange();
	for (auto& enemy : enemies) {
		if (enemyname[enemy] != "") {
			if (enemyname[enemy] == "Nitpicker") {
				efactory->Create(enemyname[enemy].c_str(), Position2f((float)((cnt / (mapsize.size.height / blockSize*2)) * blockSize*2), (float)(cnt % (mapsize.size.height / blockSize*2) * 32.0f)));
			}
			else {
				efactory->Create(enemyname[enemy].c_str(), Position2f((cnt / (mapsize.size.height / blockSize*2)) * blockSize*2, cnt % (mapsize.size.height / blockSize*2) * blockSize*2 - 96.0f));
			}
		}
		++cnt;
	}
	
	
	background->Draw();

	///敵の表示
	for (auto& enemy : efactory->GetLegion()) {
		enemy->Draw();
	}
	
	(this->*_updater)(p);


}
