#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

struct windowSize { int width; int height; };

class imageHandler
{
public:
  static void printImagesList(char** imgPaths, short arg_c);
	static void setLetterboxView(sf::View* view, int windowWidth, int windowHeight);
	static windowSize winSize;
	static void displayImage(int width, int height, sf::Sprite* imgSource);
	static void openImage(string imgPath);
	static void updateTextureSize(sf::Sprite* baseImg, sf::Texture* textre, sf::Sprite* updateImg);
	static void openMultipleImages(char** imgsPath, short arg_c);
	static void handleDisplayEvents(sf::RenderWindow& window, sf::View *view, sf::Sprite* imageSource, char** imgPaths, short arg_c, bool isMultipleImages = false);
};

#endif
