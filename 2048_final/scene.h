#pragma once

#include<graphics.h>

class Scene {
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void on_enter() { }
	virtual void on_update(const int& delta) { }
	virtual void on_draw() { }
	virtual void on_input(const ExMessage& msg) { }
	virtual void on_exit() { }
};