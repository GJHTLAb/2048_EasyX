#pragma once

#include"account.h"
#include"account_manager.h"
#include"block.h"
#include"button.h"
#include"gamebox.h"
#include"scene.h"
#include"scene_manager.h"
#include"scorebox.h"
#include"timebox.h"
#include<iostream>

extern int current_score;

extern Account current_acc;

extern AccountManager account_manager;

class GamingScene :public Scene {
public:
	GamingScene() {
		loadimage(&background_img, _T("image/gamescene_background.png"));

		back_button = new Button({ 340,85,440,140 }, _T("image/gamescene_backbutton_idle.png"), _T("image/gamescene_backbutton_hovered.png"), _T("image / gamescene_backbutton_idle.png"), _T("image/gamescene_backbutton_shader.png"));
		back_button->set_on_click([]() {
			scene_manager.switch_to(SceneManager::Menu);
			});
		restart_button = new Button({ 230,15,440,70 }, _T("image/restart_button_idle.png"), _T("image/restart_button_hovered.png"), _T("image/restart_button_idle.png"), _T("image/restart_button_shader.png"));
		restart_button->set_on_click([&]() {
			on_exit();
			on_enter();
			});

		score_box = new ScoreBox({ 10,15,220,140 }, _T("image/scorebox_background.png"));
		time_box = new TimeBox({ 230,15,440,70 }, _T("image/timebox_background.png"));
	}
	~GamingScene() {
		delete back_button;
		delete restart_button;
		delete score_box;
		delete time_box;
	}
	void on_enter() {
		back_button->on_enter();

		game_box.on_enter();
		score_box->on_enter();
		time_box->on_enter();
	}
	void on_update(const int& delta) {
		game_box.on_update(delta);
		time_box->on_update(delta);
	}
	void on_draw() {
		putimage(0, 0, &background_img);

		back_button->on_draw();
		if (!game_box.check_running()) {
			restart_button->on_draw();
		}
		else {
			time_box->on_draw();
		}
		game_box.on_draw();

		static int pre_score = current_score;
		if (pre_score != current_score) {
			pre_score = current_score;
			score_box->set_score(current_score);
		}
		score_box->on_draw();
	}
	void on_input(const ExMessage& msg) {
		back_button->on_input(msg);

		if (game_box.check_running()) {
			game_box.on_input(msg);
		}
		else {
			restart_button->on_input(msg);
		}
	}
	void on_exit() {
		current_acc.update_score(current_score);
		account_manager.update_score();
		game_box.on_exit();
		score_box->on_exit();
		time_box->on_exit();
	}
private:
	IMAGE background_img;

	Button* back_button = nullptr;
	Button* restart_button = nullptr;

	GameBox game_box;

	ScoreBox* score_box = nullptr;
	TimeBox* time_box = nullptr;
};