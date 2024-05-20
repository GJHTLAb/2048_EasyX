#pragma once

#include<graphics.h>
#include<functional>
#include<iostream>
#include"gamebox.h"

using namespace std;

class Timer {
public:
	Timer(int wait_time)
		:wait_time(wait_time){ }
	~Timer() = default;
	void on_update(const int& delta) {
		static int pass_time=0;
		pass_time += delta;
		if (pass_time >= wait_time) {
			done = true;
			callback();
		}
	}
	bool check_done() {
		return done;
	}
	void set_callback(function<void()> callback) {
		this->callback = callback;
	}
private:
	bool done = false;
	int wait_time;
	function<void()> callback;
};