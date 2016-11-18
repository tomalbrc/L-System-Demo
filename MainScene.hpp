// Created by Tom Albrecht
// 17.11.16 - 18:54
// Copyright 2016

#include "FayEngine/FayEngine.h"
#include <string>

class MainScene;
FE_create_Ptr(MainScene);

class MainScene: public FE::Scene {
public:
	FE_create_FUNC(MainScene);

	virtual void setWindow(FE::WindowPtr win);
	
	std::string myStr;
};
