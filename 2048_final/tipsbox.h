#pragma once

#include<graphics.h>
#include<utility>
#include"util.h"
#include"textbox.h"

using namespace std;

class TipsBox {
public:
	TipsBox() {
		loadimage(&tipsbox_background_img, _T("image/tipsbox_background.png"));
		loadimage(&tipsbox_background_shader_img, _T("image/tipsbox_background_shader.png"));

		status = Idle;
	}
	~TipsBox() {

	}
	void on_update(const int& delta) {
		int speed_y = 0;
		static int pass_time = 0;
		switch (status)
		{
		case TipsBox::Idle:
			pos.first = 25;
			pos.second = -100;
			break;
		case TipsBox::Down:
			speed_y = 1;
			pos.second += speed_y * delta;
			if (pos.second >= 0) {
				pos.second = 0;
				status = Wait;
			}
			break;
		case TipsBox::Wait:
			pass_time += delta;
			if (pass_time > 1500) {
				pass_time = 0;
				status = Up;
			}
			break;
		case TipsBox::Up:
			speed_y = -1;
			pos.second += speed_y * delta;
			if (pos.second <= -100) {
				pos.second = -100;
				status = Idle;
			}
			break;
		default:
			break;
		}
	}
	void on_draw() {
		putimage(pos.first + 8, pos.second + 2, &tipsbox_background_shader_img);
		putimage(pos.first, pos.second, &tipsbox_background_img);

		RECT r{ pos.first,pos.second,pos.first + 400,pos.second + 100 };
		drawtext(text, &r, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	}
	void set_tips(const TCHAR* text) {
		status = Down;

		pos.first = 25;
		pos.second = -100;

		this->text = text;
	}
private:
	IMAGE tipsbox_background_img;
	IMAGE tipsbox_background_shader_img;
	
	const TCHAR* text;

	pair<int, int> pos;
	enum Status {
		Idle,
		Down,
		Wait,
		Up
	}status;
};