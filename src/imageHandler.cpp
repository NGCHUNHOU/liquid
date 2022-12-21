#include <imageHandler.h>
#include <fstream>
#include <iostream>
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
	// find the min ratio value between width and height, set scale with min ratio if the ratio value < 1
	float scaleFactor = min((float)window.getSize().x / imgSource->getTexture()->getSize().x, (float)window.getSize().y / imgSource->getTexture()->getSize().y);
	if (scaleFactor < 1)
		imgSource->setScale(scaleFactor, scaleFactor);
	imgSource->setOrigin(imgSource->getTexture()->getSize().x / 2.0f, imgSource->getTexture()->getSize().y / 2.0f);
	imgSource->setPosition(width / 2.0f, height / 2.0f);
	sf::View view;
	//view.setSize(imgSource->getTexture()->getSize().x, imgSource->getTexture()->getSize().y);
	view.setSize(width, height);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);

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
void imageHandler::openImg(string imgPath) {
	ifstream file(imgPath);
	if (!file.good()) {
		cout << "failed to open the images" << endl;
		exit(1);
	}

	imageResolution imgSize = { 800, 600 };
	sf::Texture texture;
	texture.loadFromFile(imgPath);
	sf::Sprite imgSource(texture);
	displayImg(imgSize.width, imgSize.height, &imgSource);
	return;
};
void imageHandler::openMultipleImgs(char** imgPaths, short arg_c) {
	cout << "first image path " << imgPaths[1] << "\n" << "second image path " << imgPaths[2] << endl;
	vector<sf::Texture> images;
	vector<sf::Sprite> sprites;
	imageResolution imgSize = { 800, 600 };
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(imgSize.width, imgSize.height, desktop.bitsPerPixel), "Liquid");

	for (int i = 1;i < arg_c;i++) {
		ifstream file(imgPaths[i]);
		if (!file.good()) {
			cout << "failed to open the images" << endl;
			exit(1);
		}

		sf::Texture texture;
		sf::Sprite baseImage_copy;
		texture.loadFromFile(imgPaths[i]);
		baseImage_copy.setTexture(texture);
		float scaleFactor = min((float)window.getSize().x / texture.getSize().x, (float)window.getSize().y / texture.getSize().y);
		baseImage_copy.setScale(scaleFactor, scaleFactor);
		baseImage_copy.setOrigin(baseImage_copy.getTexture()->getSize().x / 2.0f, baseImage_copy.getTexture()->getSize().y / 2.0f);
		baseImage_copy.setPosition(imgSize.width / 2.0f, imgSize.height / 2.0f);
		images.push_back(texture);
		sprites.push_back(baseImage_copy);
	}

	sf::Sprite baseImage;
	baseImage.setTexture(images[0]);
	float scaleFactor = min((float)window.getSize().x / images[0].getSize().x, (float)window.getSize().y / images[0].getSize().y);
	if (scaleFactor < 1)
		baseImage.setScale(scaleFactor, scaleFactor);
	baseImage.setOrigin(baseImage.getTexture()->getSize().x / 2.0f, baseImage.getTexture()->getSize().y / 2.0f);
	baseImage.setPosition(imgSize.width / 2.0f, imgSize.height / 2.0f);
	int imageIndex = 0;

	sf::View view;
	view.setSize(imgSize.width, imgSize.height);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);

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
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::L) {
					imageIndex += 1;
					if (imageIndex >= images.size())
						imageIndex = 0;
					baseImage.setTexture(images[imageIndex]);
					baseImage.setTextureRect(sf::IntRect(0, 0, images[imageIndex].getSize().x, images[imageIndex].getSize().y));
					baseImage.setScale(sprites[imageIndex].getScale());
					baseImage.setOrigin(sprites[imageIndex].getOrigin());
					baseImage.setPosition(sprites[imageIndex].getPosition());
				};
				if (event.key.code == sf::Keyboard::H) {
					imageIndex -= 1;
					if (imageIndex < 0)
						imageIndex = images.size() - 1;
					baseImage.setTexture(images[imageIndex]);
					baseImage.setTextureRect(sf::IntRect(0, 0, images[imageIndex].getSize().x, images[imageIndex].getSize().y));
					baseImage.setScale(sprites[imageIndex].getScale());
					baseImage.setOrigin(sprites[imageIndex].getOrigin());
					baseImage.setPosition(sprites[imageIndex].getPosition());
				};
			};
		};
		window.clear();
		window.setView(view);
		window.draw(baseImage);
		window.display();
	};

};
