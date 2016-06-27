#pragma once

#include <Windows.h>
#include <iostream>
#include <memory>

#include <GameEngine.h>

#include "../Script/PlayerController.h"

class Test : public SimpleGameApp
{
public:
	Test(HINSTANCE hInstance, int cmdShow) : SimpleGameApp{ hInstance, cmdShow } {}
	~Test() {}

private:
	void InitGame() override;
	void GameShutdown()override;

private:
	int camera;
};