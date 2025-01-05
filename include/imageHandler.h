#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <getopt.h>
#include <string>
#include <memory>

#define VERTICAL_WHEEL 0
#define HORIZONTAL_WHEEL 1
#define UNKNOWN_WHEEL 2

#define WHEEL_FORWARD 1
#define WHEEL_BACKWARD -1

#define ZOOM_RATE 0.1f

struct windowSize { int width; int height; };

struct image_frame {
  sf::Texture baseTexture;
	sf::Sprite baseImage;
};

int getWheelType(sf::Event &ev);

class imageHandler
{
private:
  argCounter *argCt;
  sf::RenderWindow *window;
  windowSize *winSize;
  std::vector<std::unique_ptr<image_frame>> image_frames;
  sf::View *view;
public:
  static windowSize global_winSize;
  static void printImagesList(char** imgPaths, short arg_c);
	static void setLetterboxView(sf::View* view, int windowWidth, int windowHeight);
	void displayImage(sf::Sprite* imgSource);
  void xmove_images(int &img_index, sf::Event &ev);
	void openSingleImage(std::string imgPath);
	static void updateTextureSize(sf::Sprite* baseImg, sf::Texture* textre, sf::Sprite* updateImg);
	void openMultipleImages();
  void initArgCounter(argCounter& argCt_ptr);
  void initWindowFrame(sf::RenderWindow& win, sf::View& v, windowSize& w);
	void handleDisplayEvents2(void (imageHandler::*event_functions)(int &img_index, sf::Event &ev));
  void zoom_in_out(sf::Event &ev);
};

#endif
