#pragma once

#include<utility>
#include"scene.h"
#include"textbox.h"
#include"button.h"
#include"scene_manager.h"
#include"account_manager.h"

using namespace std;

extern bool is_login;

extern Account current_acc;

extern SceneManager scene_manager;

extern AccountManager account_manager;

extern TextBox login_scene_account_box;
extern TextBox login_scene_password_box;

class LoginScene :public Scene {
public:
	LoginScene() {
		loadimage(&background_img, _T("image/registerscene_background.png"));
		loadimage(&operatorboard_img, _T("image/registerscene_operatorboard.png"));
		loadimage(&operatorboard_shader_img, _T("image/registerscene_operatorboard_shader.png"));
		loadimage(&operatorboard_login_img, _T("image/accountscene_operatorboard_login.png"));

		back_button = new Button({ 375,150,425,200 }, _T("image/registerscene_backbutton_idle.png"), _T("image/registerscene_backbutton_hovered.png"), _T("image/registerscene_backbutton_idle.png"));
		back_button->set_on_click([]() {
			scene_manager.switch_to(SceneManager::Status::Menu);
			});
		login_button = new Button({ 65,365,185,435 }, _T("image/startscene_registerbutton_idle.png"), _T("image/startscene_registerbutton_hovered.png"), _T("image/startscene_registerbutton_idle.png"), _T("image/startscene_button_shader.png"));
		login_button->set_on_click([]() {
			account_manager.login_account();
			});
		register_button = new Button({ 265,365,385,435 }, _T("image/registerscene_registerbutton_idle.png"), _T("image/registerscene_registerbutton_hovered.png"), _T("image/registerscene_registerbutton_idle.png"), _T("image/startscene_button_shader.png"));
		register_button->set_on_click([]() {
			scene_manager.switch_to(SceneManager::Status::Register);
			});
		logout_button = new Button({ 105,365,345,435 }, _T("image/accountscene_logoutbutton_idle.png"), _T("image/accountscene_logoutbutton_hovered.png"), _T("image/accountscene_logoutbutton_idle.png"), _T("image/accountscene_logoutbutton_shader.png"));
		logout_button->set_on_click([]() {
			account_manager.logout_account();
			});
		account_box = &login_scene_account_box;
		password_box = &login_scene_password_box;
		account_box->on_set({ 125,235,325,275 }, 13);
		password_box->on_set({ 125,285,325,325 }, 13);

		password_box->set_private();

		current_acc_box.on_set({ 125,275,325,315 }, 13);
	}
	~LoginScene() {
		delete back_button;
		delete login_button;
		delete register_button;
		delete logout_button;
	}
	void on_enter() {
		board_pos.first = 25;
		board_pos.second = 600;
		paused = false;
		back_button->on_enter();
		login_button->on_enter();
		register_button->on_enter();
		logout_button->on_enter();

		account_box->on_enter();
		password_box->on_enter();

		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 28;
		_tcscpy_s(f.lfFaceName, _T("ºÚÌå"));
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);

		current_acc_box.set_text(StringToTCHAR(current_acc.get_account()));
	}
	void on_update(const int& delta) {
		if (is_login) {

		}
		else {
			account_box->on_update(delta);
			password_box->on_update(delta);
		}
		
		const int speed_y = -3;
		if (paused)
			return;
		board_pos.second += speed_y * delta;
		if (board_pos.second <= 150) {
			paused = true;
			board_pos.second = 150;
		}
	}
	void on_draw() {
		putimage(0, 0, &background_img);
		
		if (is_login) {
			putimage(board_pos.first + 8, board_pos.second + 6, &operatorboard_shader_img);
			putimage(board_pos.first, board_pos.second, &operatorboard_login_img);
			back_button->on_draw(25 - board_pos.first, 150 - board_pos.second);
			logout_button->on_draw(25 - board_pos.first, 150 - board_pos.second);

			current_acc_box.on_draw(25 - board_pos.first, 150 - board_pos.second);
		}
		else {
			putimage(board_pos.first + 8, board_pos.second + 6, &operatorboard_shader_img);
			putimage(board_pos.first, board_pos.second, &operatorboard_img);
			back_button->on_draw(25 - board_pos.first, 150 - board_pos.second);
			login_button->on_draw(25 - board_pos.first, 150 - board_pos.second);
			register_button->on_draw(25 - board_pos.first, 150 - board_pos.second);

			account_box->on_draw(25 - board_pos.first, 150 - board_pos.second);
			password_box->on_draw(25 - board_pos.first, 150 - board_pos.second);
		}
	}
	void on_input(const ExMessage& msg) {
		if (!paused)
			return;
		if (is_login) {
			back_button->on_input(msg);
			logout_button->on_input(msg);
		}
		else {
			back_button->on_input(msg);
			login_button->on_input(msg);
			register_button->on_input(msg);

			account_box->on_input(msg);
			password_box->on_input(msg);
		}
		
	}
	void on_exit() {
		account_box->on_exit();
		password_box->on_exit();
	}
private:
	IMAGE background_img;
	IMAGE operatorboard_img;
	IMAGE operatorboard_shader_img;
	IMAGE operatorboard_login_img;

	Button* back_button = nullptr;
	Button* login_button = nullptr;
	Button* register_button = nullptr;
	Button* logout_button = nullptr;
	
	TextBox* account_box = nullptr;
	TextBox* password_box = nullptr;

	TextBox current_acc_box;

	pair<int, int> board_pos;
	bool paused = false;
};