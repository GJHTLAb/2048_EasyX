#pragma once

#include"scene.h"
#include"button.h"
#include"textbox.h"
#include"scene_manager.h"
#include"account_manager.h"

extern SceneManager scene_manager;
extern AccountManager account_manager;

extern TextBox register_scene_account_box;
extern TextBox register_scene_password_box;
extern TextBox register_scene_apassword_box;

class RegisterScene :public Scene {
public:
	RegisterScene() {
		loadimage(&background_img, _T("image/accountscene_background.png"));
		loadimage(&operatorboard_img, _T("image/accountscene_operatorboard.png"));
		loadimage(&operatorboard_shader_img, _T("image/registerscene_operatorboard_shader.png"));

		back_button = new Button({ 375,150,425,200 }, _T("image/registerscene_backbutton_idle.png"), _T("image/registerscene_backbutton_hovered.png"), _T("image/registerscene_backbutton_idle.png"));
		back_button->set_on_click([]() {
			scene_manager.switch_to(SceneManager::Status::Login);
			});
		register_button = new Button({ 165,365,285,435 }, _T("image/registerscene_registerbutton_idle.png"), _T("image/registerscene_registerbutton_hovered.png"), _T("image/registerscene_registerbutton_idle.png"), _T("image/startscene_button_shader.png"));
		register_button->set_on_click([]() {
			account_manager.register_account();
			});

		account_box = &register_scene_account_box;
		password_box = &register_scene_password_box;
		apassword_box = &register_scene_apassword_box;

		account_box->on_set({ 125,205,325,245 }, 13);
		password_box->on_set({ 125,255,325,295 }, 13);
		apassword_box->on_set({ 125,305,325,345 }, 13);

		password_box->set_private();
		apassword_box->set_private();
	}
	~RegisterScene() {
		delete back_button;
		delete register_button;
	}
	void on_enter() {
		board_pos.first = 25;
		board_pos.second = -400;
		paused = false;

		back_button->on_enter();
		register_button->on_enter();

		account_box->on_enter();
		password_box->on_enter();
		apassword_box->on_enter();
	}
	void on_update(const int& delta) {
		account_box->on_update(delta);
		password_box->on_update(delta);
		apassword_box->on_update(delta);

		const int speed_y = 3;
		if (paused)
			return;
		board_pos.second += speed_y * delta;
		if (board_pos.second >= 150) {
			paused = true;
			board_pos.second = 150;
		}
	}
	void on_draw() {
		putimage(0, 0, &background_img);
		putimage(board_pos.first + 8, board_pos.second + 6, &operatorboard_shader_img);
		putimage(board_pos.first, board_pos.second, &operatorboard_img);

		back_button->on_draw(25 - board_pos.first, 150 - board_pos.second);
		register_button->on_draw(25 - board_pos.first, 150 - board_pos.second);

		account_box->on_draw(25 - board_pos.first, 150 - board_pos.second);
		password_box->on_draw(25 - board_pos.first, 150 - board_pos.second);
		apassword_box->on_draw(25 - board_pos.first, 150 - board_pos.second);
	}
	void on_input(const ExMessage& msg) {
		if (!paused)
			return;
		back_button->on_input(msg);
		register_button->on_input(msg);

		account_box->on_input(msg);
		password_box->on_input(msg);
		apassword_box->on_input(msg);
	}
	void on_exit() {
		account_box->on_exit();
		password_box->on_exit();
		apassword_box->on_exit();
	}
private:
	IMAGE background_img;
	IMAGE operatorboard_img;
	IMAGE operatorboard_shader_img;

	Button* back_button = nullptr;
	Button* register_button = nullptr;

	TextBox* account_box = nullptr;
	TextBox* password_box = nullptr;
	TextBox* apassword_box = nullptr;

	pair<int, int> board_pos;
	bool paused = false;
};