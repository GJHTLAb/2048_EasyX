#pragma once

#include"scene.h"
#include"button.h"
#include"scene_manager.h"
#include"account.h"

extern Account current_acc;

extern bool running;

extern SceneManager scene_manager;

class MenuScene :public Scene {
public:
	MenuScene() {
		loadimage(&background_img, _T("image/startscene_background.png"));

		logo_button = new Button(RECT{ 75,50,375,150 }, _T("image/startscene_logobutton_idle.png"), _T("image/startscene_logobutton_hovered.png"), _T("image/startscene_logobutton_idle.png"), _T("image/startscene_logobutton_shader.png"));
		logo_button->set_on_click([]() {
			scene_manager.switch_to(SceneManager::Status::Inform);
			});
		startgame_button = new Button(RECT{ 165,265,285,325 }, _T("image/startscene_startbutton_idle.png"), _T("image/startscene_startbutton_hovered.png"), _T("image/startscene_startbutton_idle.png"), _T("image/startscene_button_shader.png"));
		startgame_button->set_on_click([]() {
			scene_manager.switch_to(SceneManager::Status::Gaming);
			});
		register_button = new Button(RECT{ 165,365,285,425 }, _T("image/startscene_registerbutton_idle.png"), _T("image/startscene_registerbutton_hovered.png"), _T("image/startscene_registerbutton_idle.png"), _T("image/startscene_button_shader.png"));
		register_button->set_on_click([]() {
			scene_manager.switch_to(SceneManager::Status::Login);
			});
		exit_button = new Button(RECT{ 165,465,285,525 }, _T("image/startscene_exitbutton_idle.png"), _T("image/startscene_exitbutton_hovered.png"), _T("image/startscene_exitbutton_idle.png"), _T("image/startscene_button_shader.png"));
		exit_button->set_on_click([]() {
			running = false;
			});
		ranklist_button = new Button(RECT{ 365,515,430,580 }, _T("image/startscene_rankbutton_idle.png"), _T("image/startscene_rankbutton_hovered.png"), _T("image/startscene_rankbutton_idle.png"), _T("image/startscene_rankbutton_shader.png"));
		ranklist_button->set_on_click([]() {
			scene_manager.switch_to(SceneManager::Status::RankList);
			});
	}
	~MenuScene() {
		delete logo_button;
		delete startgame_button;
		delete register_button;
		delete exit_button;
		delete ranklist_button;
	}
	void on_enter() {
		logo_button->on_enter();
		startgame_button->on_enter();
		register_button->on_enter();
		exit_button->on_enter();
		ranklist_button->on_enter();
	}
	void on_draw() {
		putimage(0, 0, &background_img);

		logo_button->on_draw();
		startgame_button->on_draw();
		register_button->on_draw();
		exit_button->on_draw();
		ranklist_button->on_draw();
	}
	void on_input(const ExMessage& msg) {
		logo_button->on_input(msg);
		startgame_button->on_input(msg);
		register_button->on_input(msg);
		exit_button->on_input(msg);
		ranklist_button->on_input(msg);
	}
private:
	IMAGE background_img;

	Button* logo_button = nullptr;
	Button* startgame_button = nullptr;
	Button* register_button = nullptr;
	Button* exit_button = nullptr;
	Button* ranklist_button = nullptr;
};