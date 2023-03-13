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
	struct windowSize { int width; int height; };
	static void displayImage(int width, int height, sf::Sprite* imgSource);
	static void openImage(string imgPath);
	static void updateTextureSize(sf::Sprite* baseImg, sf::Texture* textre, sf::Sprite* updateImg);
	static void openMultipleImages(char** imgsPath, short arg_c);
};

#endif
