// Tom Albrecht, 17.11.16

#include "FayEngine/FayEngine.h"
#include "MainScene.hpp"

int main() {
	FE::EngineHelper::getInstance()->Init();
	
	auto win = FE::Window::create("L-System Demo", FE::Vec2Make(640), false, false);
	win->presentScene(MainScene::create());
	win->startLoop();
	
	return 0;
}
