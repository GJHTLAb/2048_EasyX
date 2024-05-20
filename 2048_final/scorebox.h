#pragma once

#include<graphics.h>

extern int current_score;

class ScoreBox {
public:
	ScoreBox(RECT rect, LPCTSTR path_img) :region(rect) {
		loadimage(&background_img, path_img);

		region_text.left = region.left;
		region_text.right = region.right;
		region_text.top = region.top + 40;
		region_text.bottom = region.bottom;
	}
	~ScoreBox() = default;
	void on_enter() {
		set_score(0);

		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 50;
		_tcscpy_s(f.lfFaceName, _T("»ªÎÄçúçê"));
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
	}
	void on_draw() {
		putimage(region.left, region.top, &background_img);

		drawtext(score, &region_text, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	}
	void on_exit() {
		set_score(0);

		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 28;
		_tcscpy_s(f.lfFaceName, _T("ºÚÌå"));
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
	}
	void set_score(int s) {
		_stprintf_s(score, _T("%d"), s);
	}
private:
	RECT region;
	RECT region_text;
	IMAGE background_img;
	TCHAR score[10];
};