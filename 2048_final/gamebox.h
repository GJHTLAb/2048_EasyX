#pragma once
#include"block.h"
#include"timer.h"
#include"scorebox.h"
#include<ctime>

extern int current_score;

class GameBox {
public:
	GameBox() = default;
	~GameBox() = default;
	void new_block(int num) {
		srand(time(0));
		for (int i = 0; i < num; i++) {
			while (true) {
				int x = rand() % 4, y = rand() % 4;
				if (block[x][y] == NULL) {
					int z = rand() % 4;
					if (z < 3)
						block[x][y] = new Block(1, POSX[x], POSY[y]);
					else
						block[x][y] = new Block(2, POSX[x], POSY[y]);
					break;
				}
			}
		}
	}
	bool check_running() {
		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 4; j++)
				if (block[i][j] == NULL) return true;
		for (size_t i = 0; i < 4; i++)
			for (size_t j = 0; j < 4; j++) {
				if (i < 2 && block[i][j]->get_num() == block[i + 1][j]->get_num()) return true;
				if (j < 2 && block[i][j]->get_num() == block[i][j + 1]->get_num()) return true;
				if (i > 1 && block[i][j]->get_num() == block[i - 1][j]->get_num()) return true;
				if (j > 1 && block[i][j]->get_num() == block[i][j - 1]->get_num()) return true;
			}
		if (fail_played == false) {
			fail_played = true;
			mciSendString(_T("play fail from 0"), NULL, 0, NULL);
		}
		return false;
	}
	bool check_block_idle() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (block[i][j] != NULL && !block[i][j]->check_idle()) return false;
		return true;
	}
	void play_sound() {
		switch (sound) {
		case 1:
			mciSendString(_T("play 1 from 0"), NULL, 0, NULL);
			break;
		case 2:
			mciSendString(_T("play 2 from 0"), NULL, 0, NULL);
			break;
		case 3:
			mciSendString(_T("play 3 from 0"), NULL, 0, NULL);
			break;
		case 4:
			mciSendString(_T("play 4 from 0"), NULL, 0, NULL);
			break;
		case 5:
			mciSendString(_T("play 5 from 0"), NULL, 0, NULL);
			break;
		case 6:
			mciSendString(_T("play 6 from 0"), NULL, 0, NULL);
			break;
		case 7:
			mciSendString(_T("play 7 from 0"), NULL, 0, NULL);
			break;
		case 8:
			mciSendString(_T("play 8 from 0"), NULL, 0, NULL);
			break;
		}
		sound++;
		if (sound == 9) sound = 1;
	}
	void move_up() {
		bool ismove = false;
		memset(iscombine, 0, sizeof(iscombine));
		for (int j = 1; j < 4; j++) {
			for (int i = 0; i < 4; i++) {
				if (block[i][j] == NULL) continue;
				int k = j, pre = block[i][j]->get_num();
				while (k > 0 && block[i][k - 1] == NULL) {
					k--;
				}
				if (k > 0 && block[i][k - 1]->get_num() == block[i][j]->get_num() && !iscombine[i][k - 1] && !iscombine[i][j]) {
					Block* p = new Block(*block[i][j]);
					p->move_to(POSX[i], POSY[k - 1]);
					block_temp.push_back(p);
					block[i][j] = NULL;
					k--;
					iscombine[i][k] = true;
					block[i][k]->add_idx();
					block[i][k]->set_summon();
					current_score += block[i][k]->get_num();
					ismove = true;
				}
				else if (k != j) {
					block[i][j]->move_to(POSX[i], POSY[k]);
					block[i][k] = block[i][j];
					block[i][j] = NULL;
					ismove = true;
				}
			}
		}
		if (ismove) {
			play_sound();
			Timer* p = new Timer(300);
			p->set_callback([&]() {
				new_block(1);
				});
			timer.push_back(p);
		}
	}
	void move_down() {
		bool ismove = false;
		memset(iscombine, 0, sizeof(iscombine));
		for (int j = 2; ~j; j--) {
			for (int i = 0; i < 4; i++) {
				if (block[i][j] == NULL) continue;
				int k = j, pre = block[i][j]->get_num();
				while (k < 3 && block[i][k+1] == NULL) {
					k++;
				}
				if (k < 3 && block[i][k+1]->get_num() == block[i][j]->get_num() && !iscombine[i][k+1] && !iscombine[i][j]) {
					Block* p = new Block(*block[i][j]);
					p->move_to(POSX[i], POSY[k+1]);
					block_temp.push_back(p);
					block[i][j] = NULL;
					k++;
					iscombine[i][k] = true;
					block[i][k]->add_idx();
					block[i][k]->set_summon();
					current_score += block[i][k]->get_num();
					ismove = true;
				}
				else if (k != j) {
					block[i][j]->move_to(POSX[i], POSY[k]);
					block[i][k] = block[i][j];
					block[i][j] = NULL;
					ismove = true;
				}
			}
		}
		if (ismove) {
			play_sound();
			Timer* p = new Timer(300);
			p->set_callback([&]() {
				new_block(1);
				});
			timer.push_back(p);
		}
	}
	void move_left() {
		bool ismove = false;
		memset(iscombine, 0, sizeof(iscombine));
		for (int i = 1; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (block[i][j] == NULL) continue;
				int k = i, pre = block[i][j]->get_num();
				while (k > 0 && block[k - 1][j] == NULL) {
					k--;
				}
				if (k > 0 && block[k - 1][j]->get_num() == block[i][j]->get_num() && !iscombine[k - 1][j] && !iscombine[i][j]) {
					Block* p = new Block(*block[i][j]);
					p->move_to(POSX[k - 1], POSY[j]);
					block_temp.push_back(p);
					block[i][j] = NULL;
					k--;
					iscombine[k][j] = true;
					block[k][j]->add_idx();
					block[k][j]->set_summon();
					current_score += block[k][j]->get_num();
					ismove = true;
				}
				else if (k != i) {
					block[i][j]->move_to(POSX[k], POSY[j]);
					block[k][j] = block[i][j];
					block[i][j] = NULL;
					ismove=true;
				}
			}
		}
		if (ismove) {
			play_sound();
			Timer* p = new Timer(300);
			p->set_callback([&]() {
				new_block(1);
				});
			timer.push_back(p);
		}
	}
	
	void move_right() {
		bool ismove = false;
		memset(iscombine, 0, sizeof(iscombine));
		for (int i = 2; ~i; i--) {
			for (int j = 0; j < 4; j++) {
				if (block[i][j] == NULL) continue;
				int k = i, pre = block[i][j]->get_num();
				while (k < 3 && block[k + 1][j] == NULL) {
					k++;
				}
				if (k < 3 && block[k + 1][j]->get_num() == block[i][j]->get_num() && !iscombine[k + 1][j] && !iscombine[i][j]) {
					Block* p = new Block(*block[i][j]);
					p->move_to(POSX[k + 1], POSY[j]);
					block_temp.push_back(p);
					block[i][j] = NULL;
					k++;
					iscombine[k][j] = true;
					block[k][j]->add_idx();
					block[k][j]->set_summon();
					current_score += block[k][j]->get_num();
					ismove = true;
				}
				else if (k != i) {
					block[i][j]->move_to(POSX[k], POSY[j]);
					block[k][j] = block[i][j];
					block[i][j] = NULL;
					ismove = true;
				}
			}
		}
		if (ismove) {
			play_sound();
			Timer* p = new Timer(300);
			p->set_callback([&]() {
				new_block(1);
				});
			timer.push_back(p);
		}
	}
	
	void on_enter() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				block[i][j] = NULL;
				last_block[i][j] = NULL;
			}
				
		while (timer.size()) {
			delete timer[timer.size() - 1];
			timer.pop_back();
		}
		while (block_temp.size()) {
			delete block_temp[block_temp.size() - 1];
			block_temp.pop_back();
		}
		current_score = 0;
		sound = 1;
		fail_played = false;
		new_block(2);
	}
	void on_update(const int& delta) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (block[i][j] != NULL) block[i][j]->on_update(delta);
		for (size_t i = 0; i < timer.size(); i++) {
			timer[i]->on_update(delta);
			if (timer[i]->check_done()) {
				delete timer[i];
				swap(timer[i], timer[timer.size()-1]);
				timer.pop_back();
				i--;
			}
		}
		for (size_t i = 0; i < block_temp.size(); i++) {
			block_temp[i]->on_update(delta);
			if (block_temp[i]->check_idle()) {
				delete block_temp[i];
				swap(block_temp[i], block_temp[block_temp.size() - 1]);
				block_temp.pop_back();
				i--;
			}
		}
	}
	void on_draw() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (block[i][j] != NULL) block[i][j]->on_draw();
		for (size_t i = 0; i < block_temp.size(); i++)
			block_temp[i]->on_draw();
	}
	void on_input(const ExMessage& msg) {
		if (check_block_idle() && !timer.size() && msg.message == WM_KEYUP) {
			switch (msg.vkcode) {
			case VK_UP:
				move_up();
				break;
			case VK_DOWN:
				move_down();
				break;
			case VK_LEFT:
				move_left();
				break;
			case VK_RIGHT:
				move_right();
				break;
			default:
				break;
			}
		}
	}
	void on_exit() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				if (block[i][j] != NULL) delete block[i][j];
				if (last_block[i][j] != NULL) delete last_block[i][j];
			}
				
		while (timer.size()) {
			delete timer[timer.size() - 1];
			timer.pop_back();
		}
		while (block_temp.size()) {
			delete block_temp[block_temp.size() - 1];
			block_temp.pop_back();
		}
	}

private:
	Block* block[4][4];
	Block* last_block[4][4];
	bool iscombine[4][4];
	int POSX[4] = { 10,120,230,340 };
	int POSY[4] = { 160,270,380,490 };
	int sound;
	bool fail_played = false;
	vector<Timer*> timer;
	vector<Block*> block_temp;
};