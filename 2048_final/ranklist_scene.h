#pragma once

#include"scene.h"
#include<graphics.h>
#include"scene_manager.h"
#include"button.h"
#include"rankbox.h"

extern SceneManager scene_manager;

class RankListScene :public Scene {
public:
	RankListScene() {
		loadimage(&background_img, _T("image/ranklistscene_background.png"));

		back_button = new Button({ 165,515,285,575 }, _T("image/informscene_backbutton_idle.png"), _T("image/informscene_backbutton_hovered.png"), _T("image/informscene_backbutton_idle.png"), _T("image/startscene_button_shader.png"));
		back_button->set_on_click([]() {
			scene_manager.switch_to(SceneManager::Menu);
			});
	}
	~RankListScene() {
		delete back_button;
	}
	void on_enter() {
		rank_box.on_enter();

		back_button->on_enter();
	}
	void on_update(const int& delta) {
		
	}
	void on_draw() {
		putimage(0, 0, &background_img);

		rank_box.on_draw(75, 100);

		back_button->on_draw();
	}
	void on_input(const ExMessage& msg) {
		rank_box.on_input(msg);

		back_button->on_input(msg);
	}
	void on_exit() {
		rank_box.on_exit();
	}
	
private:
	IMAGE background_img;

	RankBox rank_box;

	Button* back_button;
};