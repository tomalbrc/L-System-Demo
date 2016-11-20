// Created by Tom Albrecht
// 17.11.16 - 18:54
// Copyright 2016

#include "FayEngine/FayEngine.h"

class MainScene;
FE_create_Ptr(MainScene);

struct State {
        double rot;
        FE::Vec2 pos;
};
struct Rule {
	std::string a,b;
	Rule(std::string ai, std::string bi) {
                a = ai;
                b = bi;
        }
};

class MainScene: public FE::Scene {
        FE::SpritePtr sprite;

	std::vector<Rule> rules = {};
	std::string generateString(std::string input);
	void processString(std::string);
	
	// overall turn angle used by + and -
	double angle = DegreesToRadians(25);
	double len = 6;
	
	std::string axiom = "F";
	
	// Turtle drawing stuff
	State normalState;
	std::vector<State> savedStates;

	// input label
	FE::LabelNodePtr labelNode;
	std::string inputBuffer = "F F[++F[-F][F]-FF[F]] F 14 26 4";
	
	// drawing offset (mouse)
	FE::Vec2 offset = FE::Vec2Null();
	// how many string replacement operations
	int iterations = 3;
public:
	FE_create_FUNC(MainScene);

	virtual void setWindow(FE::WindowPtr win);
	virtual void mouseClickBegan(SDL_MouseButtonEvent event, FE::Vec2 coords);
	virtual void keyDown(FE::FEKeyCode key);
	virtual void update();
};
