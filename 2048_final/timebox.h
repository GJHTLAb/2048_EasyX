#pragma once

#include<graphics.h>

class TimeBox {
public:
	TimeBox(RECT rect, LPCTSTR path_img):region(rect){
		loadimage(&background_img, path_img);
	}
	~TimeBox() = default;
	void on_enter() {
		pass_time = 0;
	}
	void on_update(const int& delta) {
		pass_time += delta;

		second = pass_time / 1000;
		minute = second / 60;
		second %= 60;
		hour = minute / 60;
		minute %= 60;

		_stprintf_s(time, _T("%02d:%02d:%02d"), hour, minute, second);
	}
	void on_draw() {
		putimage(region.left, region.top, &background_img);

		drawtext(time, &region, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	}
	void on_exit() {
		pass_time = 0;
	}

private:
	RECT region;
	IMAGE background_img;
	TCHAR time[10];
	int pass_time = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
};