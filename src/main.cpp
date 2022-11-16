#include <iostream>
#include <array>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <getopt.h>
using namespace std;

void setLetterboxView(sf::View *view, int windowWidth, int windowHeight) {
    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view->getSize().x / (float) view->getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view->setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );
    return;
}

struct imageResolution { int width; int height; };

void displayImg(int width, int height, sf::Sprite *imgSource) {
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(width, height, desktop.bitsPerPixel), "Liquid");
	sf::View view;
	view.setSize(imgSource->getTexture()->getSize().x, imgSource->getTexture()->getSize().y);
	view.setCenter( view.getSize().x / 2, view.getSize().y / 2 );

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}
			if (event.type == sf::Event::Resized) {
				setLetterboxView(&view, event.size.width, event.size.height);
			};
		};
		window.clear();
		window.setView(view);
		window.draw(*imgSource);
		window.display();
	};
};

void openImg(string imgPath) {
	imageResolution imgSize = { 800, 600 };
	sf::Texture texture;
	texture.loadFromFile(imgPath);
	sf::Sprite imgSource;
	imgSource.setTexture(texture);
	displayImg(imgSize.width, imgSize.height, &imgSource);
	return;
};

int main(int argc, char** argv) {
	if (argc < 2) {
		cout << "no argument found" << endl;
		return 1;
	};

	char *flags = "h:a:";
	option opts[] = { 
		{"help", optional_argument,  (int*)&flags[0], 1},
		{"all", optional_argument,  (int*)&flags[0], 2} 
	};

	char opt = argParser::getopt_long(argc, argv, flags, opts);
	while (true) {
		if (argParser::getArgType(opt) == 2) {
			cout << "unknown option" << endl;
			break;
		};

		if (argParser::getArgType(opt) == 1) {
			openImg(argv[1]);
			break;
		}

		switch (opt) {
			case 'h':
				cout << "help page" << endl;
				break;

			case 'a':
				cout << "show all page" << endl;
				break;
		};

		if (argParser::getArgType(opt) == 3) 
			break;
	};

	return 0;
};
