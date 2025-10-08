#include "GameScene.h"
#include "SceneId.h"

void GameScene::Initialize() {}

std::optional<SceneId> GameScene::Update(float dt) {
	(void)dt;

	return std::nullopt;
}

void GameScene::Draw() {}

void GameScene::Finalize() {}
