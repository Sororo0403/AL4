#include "SceneManager.h"

void SceneManager::Register(SceneId id, SceneFactory factory) { factories_[id] = std::move(factory); }

void SceneManager::SetFirst(SceneId id) { Change(id); }

void SceneManager::Update() {
	if (!hasCurrent_ || !current_) {
		return;
	}

	if (auto next = current_->Update()) {
		Change(*next);
	}
}

void SceneManager::Draw() {
	if (!hasCurrent_ || !current_) {
		return;
	}

	current_->Draw();
}

void SceneManager::Change(SceneId next) {
	if (current_) {
		current_->Finalize();
		current_.reset();
	}

	auto it = factories_.find(next);
	if (it == factories_.end()) {
		return;
	}

	current_ = (it->second)();
	currentId_ = next;
	hasCurrent_ = true;

	if (current_) {
		current_->Initialize();
	}
}
