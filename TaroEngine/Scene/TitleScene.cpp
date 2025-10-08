#include "TitleScene.h"
#include "SceneId.h"

void TitleScene::Initialize() {}

std::optional<SceneId> TitleScene::Update(float dt) {
	(void)dt;

	return std::nullopt;
}

void TitleScene::Draw() {}

void TitleScene::Finalize() {}
