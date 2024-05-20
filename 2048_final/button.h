#pragma once

#include<graphics.h>
#include<functional>

class Button {
public:
	Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed, LPCTSTR path_img_shader) {
		region = rect;
		loadimage(&img_idle, path_img_idle);
		loadimage(&img_hovered, path_img_hovered);
		loadimage(&img_pushed, path_img_pushed);
		loadimage(&img_shader, path_img_shader);

		have_shader = true;
	}
	Button(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed) {
		region = rect;
		loadimage(&img_idle, path_img_idle);
		loadimage(&img_hovered, path_img_hovered);
		loadimage(&img_pushed, path_img_pushed);
	}
	~Button() = default;
	void on_enter() {
		status = Idle;
	}
	void on_draw() {
		switch (status) {
		case Idle:
			if (have_shader) putimage(region.left + 3, region.top + 3, &img_shader);
			putimage(region.left, region.top, &img_idle);
			break;
		case Hovered:
			putimage(region.left, region.top, &img_hovered);
			break;
		case Pushed:
			putimage(region.left, region.top, &img_pushed);
			break;
		}
	}
	void on_draw(const int& board_x, const int& board_y) {
		switch (status) {
		case Idle:
			if (have_shader) putimage(region.left - board_x + 3, region.top - board_y + 3, &img_shader);
			putimage(region.left-board_x, region.top-board_y, &img_idle);
			break;
		case Hovered:
			putimage(region.left - board_x, region.top - board_y, &img_hovered);
			break;
		case Pushed:
			putimage(region.left - board_x, region.top - board_y, &img_pushed);
			break;
		}
	}
	void on_input(const ExMessage& msg) {
		switch (msg.message) {
		case WM_MOUSEMOVE:
			if (status == Idle && CheckCursorHit(msg.x, msg.y))
				status = Hovered;
			else if (status == Hovered && !CheckCursorHit(msg.x, msg.y))
				status = Idle;
			break;
		case WM_LBUTTONDOWN:
			if (CheckCursorHit(msg.x, msg.y))
				status = Pushed;
			break;
		case WM_LBUTTONUP:
			if (status == Pushed) {
				mciSendString(_T("play b1 from 150"), NULL, 0, NULL);
				on_click();
			}
			break;
		}
	}
	void set_on_click(std::function<void()> on_click) {
		this->on_click = on_click;
	}
private:
	enum Status{
		Idle,
		Hovered,
		Pushed
	};

	RECT region;
	IMAGE img_idle;
	IMAGE img_hovered;
	IMAGE img_pushed;
	IMAGE img_shader;
	Status status = Idle;

	std::function<void()> on_click;

	bool have_shader = false;

	bool CheckCursorHit(int x, int y) const {
		return x >= region.left && x <= region.right && y >= region.top && y <= region.bottom;
	}
};