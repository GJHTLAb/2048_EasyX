#pragma once

#include"scene.h"
#include"tipsbox.h"

extern Scene* menu_scene;
extern Scene* inform_scene;
extern Scene* gaming_scene;
extern Scene* login_scene;
extern Scene* register_scene;
extern Scene* ranklist_scene;

extern TipsBox tips_box;

class SceneManager {
public:
	enum Status {
		Menu,
		Inform,
		Gaming,
		Login,
		Register,
		RankList
	};
	SceneManager() = default;
	~SceneManager() = default;
	void set_current_scene(Scene* scene) {
		current_scene = scene;
		current_scene->on_enter();
	}
	void switch_to(Status scene) {
		current_scene->on_exit();
		switch (scene) {
		case Menu:
			current_scene = menu_scene;
			break;
		case Inform:
			current_scene = inform_scene;
			break;
		case Gaming:
			current_scene = gaming_scene;
			break;
		case Login:
			current_scene = login_scene;
			break;
		case Register:
			current_scene = register_scene;
			break;
		case RankList:
			current_scene = ranklist_scene;
			break;
		}
		current_scene->on_enter();
	}
	void on_update(const int& delta) {
		current_scene->on_update(delta);
		tips_box.on_update(delta);
	}
	void on_draw() {
		current_scene->on_draw();
		tips_box.on_draw();
	}
	void on_input(const ExMessage& msg) {
		current_scene->on_input(msg);
	}

private:
	Scene* current_scene = nullptr;
};