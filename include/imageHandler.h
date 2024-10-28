#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <getopt.h>
#include <string>
#include <memory>
using namespace std;

struct windowSize { int width; int height; };

struct image_frame {
  sf::Texture baseTexture;
	sf::Sprite baseImage;
};

class imageHandler
{
private:
  argCounter *argCt;
  sf::RenderWindow *window;
  std::vector<std::unique_ptr<image_frame>> image_frames;
  sf::View *view;
public:
  static void printImagesList(char** imgPaths, short arg_c);
	static void setLetterboxView(sf::View* view, int windowWidth, int windowHeight);
	static windowSize winSize;
	static void displayImage(int width, int height, sf::Sprite* imgSource);
	static void openImage(string imgPath);
	static void updateTextureSize(sf::Sprite* baseImg, sf::Texture* textre, sf::Sprite* updateImg);
	void openMultipleImages();
  void initArgCounter(argCounter& argCt_ptr);
  void initWindowFrame(sf::RenderWindow& win, sf::View& v);
	static void handleDisplayEvents(sf::RenderWindow& window, sf::View *view, sf::Sprite* imageSource, char** imgPaths, short arg_c, bool isMultipleImages = false);
	void handleDisplayEvents2();
};

#endif
