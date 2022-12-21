#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
class imageHandler
{
public:
	static void setLetterboxView(sf::View* view, int windowWidth, int windowHeight);
	struct imageResolution { int width; int height; };
	static void displayImg(int width, int height, sf::Sprite* imgSource);
	static void openImg(string imgPath);
	static void updateTextureSize(sf::Sprite* baseImg, sf::Texture* textre, sf::Sprite* updateImg);
	static void openMultipleImgs(char** imgsPath, short arg_c);
};

#endif
