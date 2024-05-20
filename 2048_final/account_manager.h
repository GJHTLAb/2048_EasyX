#pragma once
#include<graphics.h>
#include<fstream>
#include<vector>
#include"util.h"
#include"textbox.h"
#include"scene_manager.h"
#include"account.h"
#include"tipsbox.h"
using namespace std;

extern bool is_login;

extern Account current_acc;

extern SceneManager scene_manager;

extern TextBox login_scene_account_box;
extern TextBox login_scene_password_box;

extern TextBox register_scene_account_box;
extern TextBox register_scene_password_box;
extern TextBox register_scene_apassword_box;

extern TipsBox tips_box;

class AccountManager {
public:
	AccountManager() = default;
	~AccountManager() = default;
	void logout_account() {
		update_score();

		is_login = false;

		tips_box.set_tips(_T("退出成功！"));
	}
	void update_score() {
		Account acc;
		
		input.open("file/account_data.txt");
		output.open("file/account_data.tmp");

		while (read(input, acc)) {
			if (acc == current_acc) {
				acc.update_score(current_acc.get_score());
			}
			print(output, acc) << endl;
		}

		input.close();
		output.close();

		remove("file/account_data.txt");
		rename("file/account_data.tmp", "file/account_data.txt");
	}
	void login_account() {
		string account = TCHARToString(login_scene_account_box.get_text());
		string password = TCHARToString(login_scene_password_box.get_text());

		if (account.size() == 0 || password.size() == 0) {
			scene_manager.switch_to(SceneManager::Status::Login);
			return;
		}

		Account acc;
		Account _acc;
		
		bool check = false;

		_acc.account_set(account, password);

		input.open("file/account_data.txt");

		while (read(input, acc)) {
			if (_acc == acc) {
				current_acc = _acc;
				is_login = true;
				scene_manager.switch_to(SceneManager::Menu);
				tips_box.set_tips(_T("登入成功！"));
			}
			else if (acc == account)
				check = true;
		}

		if (check) {
			scene_manager.switch_to(SceneManager::Login);
			login_scene_account_box.set_text(StringToTCHAR(account));
			tips_box.set_tips(_T("密码错误！"));
		}
		else if (!is_login) {
			scene_manager.switch_to(SceneManager::Login);
			tips_box.set_tips(_T("用户不存在！"));
		}

		input.close();
	}
	void register_account() {
		string account=TCHARToString(register_scene_account_box.get_text());
		string password = TCHARToString(register_scene_password_box.get_text());
		string apassword = TCHARToString(register_scene_apassword_box.get_text());
		if (account.size() == 0 || password.size() == 0) {
			scene_manager.switch_to(SceneManager::Status::Register);
			return;
		}
		Account acc;

		input.open("file/account_data.txt");

		if (password != apassword) {
			scene_manager.switch_to(SceneManager::Status::Register);
			register_scene_account_box.set_text(StringToTCHAR(account));
			tips_box.set_tips(_T("密码不同！"));
			return;
		}
		while (read(input, acc)) {
			if (acc == account) {
				scene_manager.switch_to(SceneManager::Status::Register);
				tips_box.set_tips(_T("账号已存在！"));
				return;
			}
		}

		input.close();

		acc.account_set(account, password);

		output.open("file/account_data.txt",ofstream::app);
		print(output, acc) << endl;
		output.close();

		scene_manager.switch_to(SceneManager::Status::Login);
		login_scene_account_box.set_text(StringToTCHAR(account));
		tips_box.set_tips(_T("注册成功！"));
	}
	void get_all_account(vector<Account> &list) {
		Account acc;

		input.open("file/account_data.txt");

		while (read(input, acc))
			list.push_back(acc);

		input.close();
	}
private:
	ifstream input;
	ofstream output;
};