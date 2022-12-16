#include "imageHandler.h"
void imageHandler::setLetterboxView(sf::View *view, int windowWidth, int windowHeight) {
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
void imageHandler::displayImg(int width, int height, sf::Sprite* imgSource) {
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
}
void imageHandler::openImg(string imgPath) {
		imageResolution imgSize = { 800, 600 };
		sf::Texture texture;
		texture.loadFromFile(imgPath);
		sf::Sprite imgSource;
		imgSource.setTexture(texture);
		displayImg(imgSize.width, imgSize.height, &imgSource);
		return;
}
