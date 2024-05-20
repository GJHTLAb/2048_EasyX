#pragma once

#include<graphics.h>

class TextBox {
public:
	TextBox() = default;
	~TextBox() = default;
	void on_set(RECT rect, size_t len) {
		region = rect;
		maxlen = len;
		text = new TCHAR[maxlen];
		text[0] = NULL;
		text_star = new TCHAR[maxlen];
		text_star[0] = NULL;
	}
	void set_private() {
		put_star = true;
	}
	void on_enter() {
		
	}
	void on_update(const int& delta) {
		static int pass_time=0;
		pass_time += delta;
		if (pass_time > 500) {
			pass_time = 0;
			draw_line ^= 1;
		}
	}
	void on_draw() {
		if(put_star) drawtext(text_star, &region, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
		else drawtext(text,&region,DT_SINGLELINE|DT_VCENTER|DT_LEFT);
		if (draw_line && status == Input) line(region.left + textwidth(text) + 3, region.top + 3, region.left + textwidth(text) + 3, region.bottom - 3);
	}
	void on_draw(const int& board_x,const int& board_y) {
		RECT r = region;
		r.left -= board_x;
		r.right -= board_x;
		r.top -= board_y;
		r.bottom -= board_y;
		if(put_star) drawtext(text_star, &r, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
		else drawtext(text, &r, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
		if (draw_line && status == Input) line(r.left + textwidth(text) + 3, r.top + 3, r.left + textwidth(text) + 3, r.bottom - 3);
	}
	void on_input(const ExMessage& msg) {
		switch (msg.message) {
		case WM_LBUTTONDOWN:
			if (status == Idle && CheckCursorHit(msg.x, msg.y))
				status = Input;
			else if (status == Input && !CheckCursorHit(msg.x, msg.y))
				status = Idle;
			break;
		case WM_CHAR:
			if (status == Input) {
				size_t len = _tcslen(text);
				switch (msg.ch) {
				case '\b':
					if (len) {
						text[len - 1] = NULL;
						text_star[len - 1] = NULL;
					}
					break;
				case '\n':
				case '\r':
					status = Idle;
					break;
				default:
					if (len < maxlen - 1) {
						text_star[len] = '*';
						text[len++] = msg.ch;
						text_star[len] = NULL;
						text[len] = NULL;
					}
				}
			}
		}
	}
	void on_exit() {
		text[0] = NULL;
		text_star[0] = NULL;
	}
	void set_text(TCHAR* text) {
		this->text = text;
	}
	TCHAR* get_text(){
		return text;
	}
private:
	enum Status {
		Idle,
		Input
	};

	RECT region{};
	TCHAR* text = nullptr;
	TCHAR* text_star = nullptr;
	size_t maxlen = 0;
	Status status = Idle;
	bool draw_line = false;
	bool put_star = false;

	bool CheckCursorHit(int x, int y) const {
		return x >= region.left && x <= region.right && y >= region.top && y <= region.bottom;
	}
};