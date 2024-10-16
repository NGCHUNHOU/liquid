#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
using namespace std;

struct windowSize { int width; int height; };
struct image_frame {
  sf::Texture baseTexture;
	sf::Sprite baseImage;
	sf::View baseView;
};

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
	static void handleDisplayEvents2(sf::RenderWindow& window, std::vector<std::unique_ptr<image_frame>>& imgf);
};

#endif
