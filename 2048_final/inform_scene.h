#pragma once

#include"scene.h"
#include"button.h"
#include"scene_manager.h"

extern SceneManager scene_manager;

class InformScene :public Scene {
public:
	InformScene() {
		loadimage(&background_img, _T("image/informscene_background.png"));

		back_button = new Button(RECT{ 165,500,285,570 }, _T("image/informscene_backbutton_idle.png"), _T("image/informscene_backbutton_hovered.png"), _T("image/informscene_backbutton_idle.png"), _T("image/startscene_button_shader.png"));
		back_button->set_on_click([]() {
			scene_manager.switch_to(SceneManager::Status::Menu);
			});
	}
	~InformScene() {
		delete back_button;
	}
	void on_enter() {
		
		back_button->on_enter();
	}
	void on_draw() {
		putimage(0, 0, &background_img);

		back_button->on_draw();
	}
	void on_input(const ExMessage& msg) {
		back_button->on_input(msg);
	}
private:
	IMAGE background_img;

	Button* back_button = nullptr;
};