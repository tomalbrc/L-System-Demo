// MainScene.cpp
// Tom Albrecht 18.11.16
// Copyright 2016

#include "MainScene.hpp"


using namespace FE;

/*


start  : F
rules  : (F → F+F−F−F+F)


-------------
[F]+[F]+[F]+[F]+[F]+[F]
  Правило: F->F[++F][--F][-FF][+FF]FF[+F][-F]FF


------------------
Аксиома: ---F
  Правило: F->F[+F]F[-F]F
  Угол: (360/14)

---------
	a: "F",
	b: "FF+[+F]-[-F++]"




------------

a: "F",
b: "FF"

a: "X",
b: "F-[[X]+X]+F[+FX]-X


*/

Vec2 CalculatePoint(double angle, double distance) {
	return Vec2Make((distance * sin(angle)), (distance * cos(angle)));
}

void drawLine(Vec2 p1, Vec2 p2, const DrawTexturePtr &dest, const WindowPtr &w, Vec2 off = Vec2Make(0)) {
//	auto off = Vec2Null();
	dest->drawLine(p2+off, p1+off, ColorWhiteColor());
}

/**
 * MainScene impl.
 */
void MainScene::processString(std::string finalString) {
        auto tex = DrawTexture::create(getWindow()->getSize(), ColorClearColor());

	for (char &c: finalString) {
		if (c == 'F' || c == 'G') {
			// draw line w/ rotation from state point
			auto val = CalculatePoint(normalState.rot, len) + normalState.pos;
		    drawLine(normalState.pos, val, tex, getWindow(), offset);
			normalState.pos = val;
		}
		if (c == 'f') { // no draw for lowercase f
			auto val = CalculatePoint(normalState.rot, len) + normalState.pos;
			normalState.pos = val;
		}
		if (c == '+') {
            //change rot
			normalState.rot += angle;
        }
		if (c == '-') {
            //change rot
          	normalState.rot -= angle;
                }
		if (c == '[') {
			 //save state
			savedStates.push_back(normalState);
		}
		if (c == ']') {
            // restore state
			normalState = savedStates.back();
			savedStates.pop_back();
		}
	}

 	tex->apply();
	sprite->setTexture(tex);
}


std::string MainScene::generateString(std::string input) {
	std::string res = "";

	for (char &chara : input) {
		for (auto &&rule : rules) {
			FELog("Rule: "<<rule.a<<" -> "<<rule.b);
			
			std::string stri(&chara, 1);
			if (stri == rule.a) {
				res = res + rule.b;
				FELog("Out: "<<res);
			} else res += chara;
		}
	}

	return res;
}


void MainScene::setWindow(WindowPtr window) {
	Scene::setWindow(window);

	sprite = Sprite::create();
	addChild(sprite);

	labelNode = LabelNode::create("noob", "SSFDT.ttf", 20, ColorYellowColor());
	addChild(labelNode);
		
	keyDown(FEKeyCodeReturn);
}

void MainScene::mouseClickBegan(SDL_MouseButtonEvent event, Vec2 coords) {
	normalState.rot = DegreesToRadians(180);
	normalState.pos = Vec2Make(0);

	auto finalString = axiom;
	for (int i = 0; i<iterations; ++i) {
		finalString = generateString(finalString);
	}

	offset = coords;

	processString(finalString);
	FELog(finalString);
}

void MainScene::keyDown(FEKeyCode key) {
	Scene::keyDown(key);
	
	switch (key) {
		case FEKeyCodeF: inputBuffer += "F";break;
		case FEKeyCodeG: inputBuffer += "G";break;
//		case FEKeyCodeF: inputBuffer += "f";break;
		case FEKeyCodeX: inputBuffer += "X";break;
		case FEKeyCode1: inputBuffer += "1";break;
		case FEKeyCode2: inputBuffer += "2";break;
		case FEKeyCode3: inputBuffer += "3";break;
		case FEKeyCode4: inputBuffer += "4";break;
		case FEKeyCode5: inputBuffer += "5";break;
		case FEKeyCode6: inputBuffer += "6";break;
		case FEKeyCode7: inputBuffer += "7";break;
		case FEKeyCode8: inputBuffer += "8";break;
		case FEKeyCode9: inputBuffer += "9";break;
		case FEKeyCode0: inputBuffer += "0";break;
		case FEKeyCodePlus: inputBuffer += "+"; break;
		case FEKeyCodeMinus: inputBuffer += "-";break;
		case FEKeyCodeComma: inputBuffer += "[";break;
		case FEKeyCodePeriod: inputBuffer += "]";break;
		case FEKeyCodeHash: inputBuffer += "#"; break;
		case FEKeyCodeSpace: inputBuffer += " "; break;
		case FEKeyCodeBackspace: inputBuffer.pop_back();break;
		case FEKeyCodeReturn: {
			rules.clear();
			
			
			std::stringstream ss;
			ss.str(inputBuffer);
			std::string item;
			
			bool has = false;
			while (std::getline(ss, item, '#')) {
				std::stringstream sss;
				sss.str(item);
				std::string item2;
				int v2 = 0;
				Rule r = Rule("","");
				while (std::getline(sss, item2, ' ')) {
					if (v2 == 0) r.a = item2;
					else if (v2 == 1) r.b = item2;
					else if (v2 == 2) axiom = item2;
					else if (v2 == 3) angle = DegreesToRadians(double(atoi(item2.c_str())));
					else if (v2 == 4) this->len = atoi(item2.c_str());
					else iterations = atoi(item2.c_str());
					v2++;
				}
				FELog("Axiom"<< axiom <<"new rule - A: "<<r.a<<", b: "<<r.b);
				rules.push_back(r);
			}
			
			break;
		}
		default: break;
	}
}

void MainScene::update() {
	Scene::update();

	labelNode->setText(inputBuffer);
}
