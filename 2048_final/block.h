#pragma once

#include<graphics.h>
#include<vector>

using namespace std;

extern vector<vector<IMAGE>> block_img;

class Block {
public:
	
	Block(size_t img_idx, int posx, int posy)
		:img_idx(img_idx), sta_idx(0), posx(posx), posy(posy), to_posx(posx), to_posy(posy), status(Summon) { }
	~Block() = default;
	void on_update(const int& delta) {
		static int pass_time = 0;
		const int speed_x = 70;
		const int speed_y = 70;
		switch (status) {
		case Idle:
			sta_idx = 4;
			if (posx != to_posx || posy != to_posy) {
				posx = to_posx;
				posy = to_posy;
			}
			break;
		case Summon:
			pass_time += delta;
			if (posx != to_posx || posy != to_posy) {
				posx = to_posx;
				posy = to_posy;
			}
			if (pass_time >= 10) {
				pass_time = 0;
				sta_idx++;
				if (sta_idx == 9) {
					sta_idx = 4;
					status = Idle;
				}
			}
			break;
		case Move:
			pass_time += delta;
			if (pass_time > 100) {
				pass_time = 0;
				posx = to_posx;
				posy = to_posy;
				status = Idle;
			}
			else {
				int deltax = to_posx - posx, deltay = to_posy - posy;
				double length = sqrt(deltax * deltax + deltay * deltay);
				sta_idx = 4;
				if (length <= 100) {
					posx = to_posx;
					posy = to_posy;
					pass_time = 0;
					status = Idle;
				}
				else {
					deltax /= length, deltay /= length;
					posx += deltax * speed_x;
					posy += deltay * speed_y;
				}
			}
			break;
		}
	}
	void on_draw() {
		int width = block_img[img_idx][sta_idx].getwidth();
		int	height = block_img[img_idx][sta_idx].getheight();
		putimage(posx + 53 - width / 2, posy + 53 - height / 2, &block_img[0][sta_idx]);
		putimage(posx + 50 - width / 2, posy + 50 - height / 2, &block_img[img_idx][sta_idx]);
	}
	void move_to(int to_posx, int to_posy) {
		this->to_posx = to_posx;
		this->to_posy = to_posy;
		this->status = Move;
	}
	void add_idx() {
		img_idx++;
	}
	void set_summon() {
		status = Summon;
	}
	bool check_idle() {
		return status == Idle;
	}
	int get_num() {
		return 1 << img_idx;
	}

private:
	size_t img_idx, sta_idx;
	int posx, posy;
	int to_posx, to_posy;
	enum Status {
		Idle,
		Summon,
		Move
	}status;
};