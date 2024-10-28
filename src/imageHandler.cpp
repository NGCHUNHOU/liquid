#include <imageHandler.h>
#include <fstream>
#include <iostream>
#include <vector>

windowSize imageHandler::winSize = { 800, 600 };

void imageHandler::initArgCounter(argCounter& argCt_ptr) {
  argCt = &argCt_ptr;
};

void imageHandler::initWindowFrame(sf::RenderWindow& win, sf::View& v) {
  window = &win;
  view = &v;
}

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

void imageHandler::handleDisplayEvents(sf::RenderWindow& window, sf::View *view, sf::Sprite* imageSource, char** imgPaths, short arg_c, bool isMultipleImages) {
	int imageIndex = 1;
	sf::Sprite baseImage_copy;
	sf::Texture baseTexture_copy;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}
			if (event.type == sf::Event::Resized) {
				setLetterboxView(view, event.size.width, event.size.height);
			};

			if (isMultipleImages) {
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::L) {
						imageIndex += 1;
						if (imageIndex >= arg_c)
							imageIndex = 1;
						baseTexture_copy.loadFromFile(imgPaths[imageIndex]);
						baseImage_copy.setTexture(baseTexture_copy);

						float scaleFactor = min((float)800 / baseTexture_copy.getSize().x, (float)600 / baseTexture_copy.getSize().y);
						baseImage_copy.setScale(scaleFactor, scaleFactor);
						baseImage_copy.setOrigin(baseImage_copy.getTexture()->getSize().x / 2.0f, baseImage_copy.getTexture()->getSize().y / 2.0f);
						baseImage_copy.setPosition(800 / 2.0f, 600 / 2.0f);
						updateTextureSize(imageSource, &baseTexture_copy, &baseImage_copy);
					};
					if (event.key.code == sf::Keyboard::H) {
						imageIndex -= 1;
						if (imageIndex < 1)
							imageIndex = arg_c - 1;
						baseTexture_copy.loadFromFile(imgPaths[imageIndex]);
						baseImage_copy.setTexture(baseTexture_copy);

						float scaleFactor = min((float)800 / baseTexture_copy.getSize().x, (float)600 / baseTexture_copy.getSize().y);
						baseImage_copy.setScale(scaleFactor, scaleFactor);
						baseImage_copy.setOrigin(baseImage_copy.getTexture()->getSize().x / 2.0f, baseImage_copy.getTexture()->getSize().y / 2.0f);
						baseImage_copy.setPosition(800 / 2.0f, 600 / 2.0f);
						updateTextureSize(imageSource, &baseTexture_copy, &baseImage_copy);
					};
				};

			}
		};
		window.clear();
		window.setView(*view);
		window.draw(*imageSource);
		window.display();
	};
}

void imageHandler::displayImage(int width, int height, sf::Sprite* imgSource) {
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(width, height, desktop.bitsPerPixel), "Liquid");
	// find the min ratio value between width and height, set scale with min ratio if the ratio value < 1
	float scaleFactor = min((float)window.getSize().x / imgSource->getTexture()->getSize().x, (float)window.getSize().y / imgSource->getTexture()->getSize().y);
	if (scaleFactor < 1)
		imgSource->setScale(scaleFactor, scaleFactor);
	imgSource->setOrigin(imgSource->getTexture()->getSize().x / 2.0f, imgSource->getTexture()->getSize().y / 2.0f);
	imgSource->setPosition(width / 2.0f, height / 2.0f);
	sf::View view;
	view.setSize(width, height);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);

	handleDisplayEvents(window, &view, imgSource, nullptr, 0);
};
void imageHandler::openImage(string imgPath) {
	ifstream file(imgPath);
	if (!file.good()) {
		cout << "failed to open the images" << endl;
		exit(1);
	}

	sf::Texture texture;
	texture.loadFromFile(imgPath);
	sf::Sprite imgSource(texture);
	displayImage(imageHandler::winSize.width, imageHandler::winSize.height, &imgSource);
	return;
};
void imageHandler::updateTextureSize(sf::Sprite *baseImg, sf::Texture *textre, sf::Sprite *updateImg) {
	baseImg->setTexture(*textre);
	baseImg->setTextureRect(sf::IntRect(0, 0, textre->getSize().x, textre->getSize().y));
	baseImg->setScale(updateImg->getScale());
	baseImg->setOrigin(updateImg->getOrigin());
	baseImg->setPosition(updateImg->getPosition());
};
void imageHandler::printImagesList(char** imgPaths, short arg_c) {
  short image_index = arg_c - 1;
  while (image_index != 0) {
    printf("opening image from %s\n", imgPaths[image_index]);
    image_index -= 1;
  };
}

void imageHandler::handleDisplayEvents2() {
	int imageIndex = 0;
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
				break;
			}
			if (event.type == sf::Event::Resized) {
				setLetterboxView(view, event.size.width, event.size.height);
			};

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::L) {
          imageIndex = (imageIndex + 1) % image_frames.size();
          /*
          imageIndex += 1;
          if (imageIndex >= imgf.size())
            imageIndex = 0;
          baseTexture_copy.loadFromFile(imgPaths[imageIndex]);
          baseImage_copy.setTexture(baseTexture_copy);

          float scaleFactor = min((float)800 / imgf[imageIndex]->baseTexture.getSize().x, (float)600 / imgf[imageIndex]->baseTexture.getSize().y);
          imgf[imageIndex]->baseImage.setScale(scaleFactor, scaleFactor);
          imgf[imageIndex]->baseImage.setOrigin(imgf[imageIndex]->baseImage.getTexture()->getSize().x / 2.0f, imgf[imageIndex]->baseImage.getTexture()->getSize().y / 2.0f);
          imgf[imageIndex]->baseImage.setPosition(800 / 2.0f, 600 / 2.0f);
          updateTextureSize(imageSource, &baseTexture_copy, &baseImage_copy);
          */
        };
        if (event.key.code == sf::Keyboard::H) {
          imageIndex = (imageIndex - 1) % image_frames.size();
          /*
          imageIndex -= 1;
          if (imageIndex < 1)
            imageIndex = arg_c - 1;
          baseTexture_copy.loadFromFile(imgPaths[imageIndex]);
          baseImage_copy.setTexture(baseTexture_copy);

          float scaleFactor = min((float)800 / imgf[imageIndex]->baseTexture.getSize().x, (float)600 / imgf[imageIndex]->baseTexture.getSize().y);
          imgf[imageIndex]->baseImage.setScale(scaleFactor, scaleFactor);
          imgf[imageIndex]->baseImage.setOrigin(imgf[imageIndex]->baseImage.getTexture()->getSize().x / 2.0f, imgf[imageIndex]->baseImage.getTexture()->getSize().y / 2.0f);
          imgf[imageIndex]->baseImage.setPosition(800 / 2.0f, 600 / 2.0f);
          updateTextureSize(imageSource, &baseTexture_copy, &baseImage_copy);
          */
        };
      };

		};
		window->clear();
		// window.setView(*view);
		// window.draw(*imageSource);
		// window->setView(image_frames[imageIndex]->baseView);
    window->setView(*view);
		window->draw(image_frames[imageIndex]->baseImage);
		window->display();
	};
}

void imageHandler::openMultipleImages() {
  std::unique_ptr<image_frame> base_image_frame;
  for (int i = 1 ; i < argCt->arguments_count ; ++i) {
    printf("opening image from %s\n", argCt->arguments_vector[i]);
    base_image_frame = std::unique_ptr<image_frame>(new image_frame());
    base_image_frame.get()->baseTexture.loadFromFile(argCt->arguments_vector[i]);
    base_image_frame.get()->baseImage.setTexture(base_image_frame.get()->baseTexture);
    float scaleFactor = min((float)window->getSize().x / base_image_frame.get()->baseTexture.getSize().x, (float)window->getSize().y / base_image_frame.get()->baseTexture.getSize().y);
    if (scaleFactor < 1) {
      base_image_frame.get()->baseImage.setScale(scaleFactor, scaleFactor);
    }
    base_image_frame.get()->baseImage.setOrigin(base_image_frame.get()->baseImage.getTexture()->getSize().x / 2.0f, base_image_frame.get()->baseImage.getTexture()->getSize().y / 2.0f);
    base_image_frame.get()->baseImage.setPosition(imageHandler::winSize.width / 2.0f, imageHandler::winSize.height / 2.0f);

    image_frames.emplace_back(std::move(base_image_frame));
  };
	handleDisplayEvents2();
};
