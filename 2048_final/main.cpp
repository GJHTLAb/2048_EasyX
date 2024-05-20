#include"account_manager.h"
#include"gaming_scene.h"
#include"inform_scene.h"
#include"login_scene.h"
#include"menu_scene.h"
#include"ranklist_scene.h"
#include"register_scene.h"
#include"scene_manager.h"
#include"tipsbox.h"
#include<graphics.h>
#include<vector>

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "MSIMG32.LIB")

using namespace std;

bool running = true;

bool is_login = false;

int current_score = 0;

Account current_acc;

AccountManager account_manager;

SceneManager scene_manager;

Scene* menu_scene = nullptr;
Scene* inform_scene = nullptr;
Scene* gaming_scene = nullptr;
Scene* login_scene = nullptr;
Scene* register_scene = nullptr;
Scene* ranklist_scene = nullptr;

TextBox login_scene_account_box;
TextBox login_scene_password_box;

TextBox register_scene_account_box;
TextBox register_scene_password_box;
TextBox register_scene_apassword_box;

TipsBox tips_box;

vector<vector<IMAGE>> block_img; 

static void load_game_resourse() {
	block_img.resize(18);
	TCHAR pathfile[256]{};
	for (int i = 0; i < 16; i++) {
		block_img[i].resize(9);
		_stprintf_s(pathfile, _T("image/block_%d.png"), i);
		for (int j = 0; j < 9; j++)
			loadimage(&block_img[i][j], pathfile, 88 + j * 3, 88 + j * 3);
	}

	mciSendString(_T("open music/pianoC.mp3 alias 1"), NULL, 0, NULL);
	mciSendString(_T("open music/pianoD.mp3 alias 2"), NULL, 0, NULL);
	mciSendString(_T("open music/pianoE.mp3 alias 3"), NULL, 0, NULL);
	mciSendString(_T("open music/pianoF.mp3 alias 4"), NULL, 0, NULL);
	mciSendString(_T("open music/pianoG.mp3 alias 5"), NULL, 0, NULL);
	mciSendString(_T("open music/pianoA.mp3 alias 6"), NULL, 0, NULL);
	mciSendString(_T("open music/pianoB.mp3 alias 7"), NULL, 0, NULL);
	mciSendString(_T("open music/pianoC2.mp3 alias 8"), NULL, 0, NULL);
	mciSendString(_T("open music/button04a.mp3 alias b1"), NULL, 0, NULL);
	mciSendString(_T("open music/s_c_piano2.mp3 alias fail"), NULL, 0, NULL);

	menu_scene = new MenuScene();
	inform_scene = new InformScene();
	gaming_scene = new GamingScene();
	login_scene = new LoginScene();
	register_scene = new RegisterScene();
	ranklist_scene = new RankListScene();

	scene_manager.set_current_scene(menu_scene);
}

int main() {
	ExMessage msg{};
	const int FPS = 120;
	
	load_game_resourse();

	HWND hwnd = initgraph(450, 600);
	SetWindowText(hwnd, _T("2048"));

	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 28;
	_tcscpy_s(f.lfFaceName, _T("ºÚÌå"));
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	setbkmode(TRANSPARENT);

	BeginBatchDraw();

	while (running) {
		DWORD frame_start_time = GetTickCount();
		
		while (peekmessage(&msg))
			scene_manager.on_input(msg);

		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;
		scene_manager.on_update(delta_tick);
		last_tick_time = current_tick_time;

		cleardevice();
		scene_manager.on_draw();
		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_start_time;
		if (frame_delta_time < 1000 / FPS)
			Sleep(1000 / FPS - frame_delta_time);
	}
	
	EndBatchDraw();
	return 0;
}