#pragma once

#include"graphics.h"
#include"account.h"
#include"account_manager.h"
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

extern AccountManager account_manager;

class RankBox {
public:
	RankBox() {
		loadimage(&user_background_img, _T("image/ranklistscene_userbackground.png"));
		loadimage(&scroll_img, _T("image/ranklistscene_scroll.png"));
	}
	~RankBox() = default;
	void on_enter() {
		while (user.size())
			user.pop_back();
		account_manager.get_all_account(user);

		sort(user.begin(), user.end(), [](const Account& a, const Account& b) {
			return a.get_score() > b.get_score();
			});

		int n = user.size();
		if (n == 0) scrl = 0;
		else scrl = 160000 / (n * 80);

		posx = 0;
		posy = 0;
		scrx = 292;
		scry = 0;

		settextcolor(BLACK);
	}
	void on_draw(const int& X, const int& Y) {
		int sumy = 0;
		for (int i = 0; i < user.size(); i++) {
			TCHAR text[256]{};
			_stprintf_s(text, _T("  %d.%s %d"), i + 1, StringToTCHAR(user[i].get_account()), user[i].get_score());
			if (sumy<posy && sumy + 80>posy) {
				putimage(X, Y, 300, sumy + 80 - posy, &user_background_img, 0, posy - sumy);
			}
			else if (sumy >= posy && sumy + 80 <= posy + 400) {
				putimage(X, Y + sumy - posy, 300, 80, &user_background_img, 0, 0);
				RECT rect = { X, Y + sumy - posy, X + 300, Y + sumy - posy + 80 };
				drawtext(text, &rect, DT_SINGLELINE | DT_VCENTER);
			}
			else if (sumy >= posy && sumy + 80 >= posy + 400) {
				putimage(X, Y + sumy - posy, 300, posy + 400 - sumy, &user_background_img, 0, 0);
			}
			sumy += 80;
		}
		if (user.size() * 80 > 400)
			scry = (400 - scrl) * posy / (user.size() * 80 - 400);
		putimage(X+scrx, Y+scry, 8, scrl, &scroll_img, 0, 0);
	}
	void on_input(const ExMessage& msg) {
		if (msg.message == WM_MOUSEWHEEL && CheckCursorHit(msg.x, msg.y) && user.size() * 80 > 400) {
			posy -= msg.wheel / 20;

			if (posy < 0) posy = 0;
			else if (posy > user.size() * 80 - 400) posy = user.size() * 80 - 400;
		}
	}
	void on_exit() {
		settextcolor(WHITE);
	}

private:
	IMAGE user_background_img;
	IMAGE scroll_img;

	vector<Account> user;

	int scrl;
	int posx, posy;
	int scrx, scry;

	bool CheckCursorHit(int x, int y) const {
		return x >= 75 && x <= 375 && y <= 500 && y >= 100;
	}
};
