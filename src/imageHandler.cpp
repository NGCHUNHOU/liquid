#include <imageHandler.h>
#include <fstream>
#include <iostream>
#include <vector>

windowSize imageHandler::global_winSize = { 800, 600 };

void imageHandler::initArgCounter(argCounter& argCt_ptr) {
  argCt = &argCt_ptr;
};

void imageHandler::initWindowFrame(sf::RenderWindow& win, sf::View& v, windowSize& w) {
  window = &win;
  view = &v;
  winSize = &w;
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

void imageHandler::displayImage(sf::Sprite* imgSource) {
  float scaleFactor = min((float)winSize->width / imgSource->getTexture()->getSize().x, (float)winSize->height / imgSource->getTexture()->getSize().y);
  imgSource->setScale(scaleFactor, scaleFactor);
	imgSource->setOrigin(imgSource->getTexture()->getSize().x / 2.0f, imgSource->getTexture()->getSize().y / 2.0f);
	imgSource->setPosition(winSize->width / 2.0f, winSize->height / 2.0f);
	sf::View view;
	view.setSize(winSize->width, winSize->height);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);

  std::unique_ptr<image_frame> base_image_frame(new image_frame());
  base_image_frame.get()->baseImage = *imgSource;
  base_image_frame.get()->baseTexture = *(imgSource->getTexture());
  image_frames.emplace_back(std::move(base_image_frame));
  handleDisplayEvents2(nullptr);
};

void imageHandler::openSingleImage(string imgPath) {
	ifstream file(imgPath);
	if (!file.good()) {
		cout << "failed to open the image" << endl;
		exit(1);
	}

	sf::Texture texture;
	texture.loadFromFile(imgPath);
	sf::Sprite imgSource(texture);

	displayImage(&imgSource);
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
};

void imageHandler::xmove_images(int &img_index, sf::Event &ev) {
  if (ev.type == sf::Event::KeyPressed) {
    if (ev.key.code == sf::Keyboard::L) {
      img_index = (img_index + 1) % image_frames.size();

      float scaleFactor = min((float)winSize->width / image_frames[img_index]->baseTexture.getSize().x, (float)winSize->height / image_frames[img_index]->baseTexture.getSize().y);
      image_frames[img_index]->baseImage.setScale(scaleFactor, scaleFactor);
      image_frames[img_index]->baseImage.setOrigin(image_frames[img_index]->baseImage.getTexture()->getSize().x / 2.0f, image_frames[img_index]->baseImage.getTexture()->getSize().y / 2.0f);
      image_frames[img_index]->baseImage.setPosition(winSize->width / 2.0f, winSize->height / 2.0f);
    };
    if (ev.key.code == sf::Keyboard::H) {
      img_index = (img_index - 1) % image_frames.size();

      float scaleFactor = min((float)winSize->width / image_frames[img_index]->baseTexture.getSize().x, (float)winSize->height / image_frames[img_index]->baseTexture.getSize().y);
      image_frames[img_index]->baseImage.setScale(scaleFactor, scaleFactor);
      image_frames[img_index]->baseImage.setOrigin(image_frames[img_index]->baseImage.getTexture()->getSize().x / 2.0f, image_frames[img_index]->baseImage.getTexture()->getSize().y / 2.0f);
      image_frames[img_index]->baseImage.setPosition(winSize->width / 2.0f, winSize->height / 2.0f);

    };
  };
}

void imageHandler::handleDisplayEvents2(void (imageHandler::*event_functions)(int &img_index, sf::Event &ev)) {
	int imageIndex = 0;
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
				break;
			};
			if (event.type == sf::Event::Resized) {
				setLetterboxView(view, event.size.width, event.size.height);
			};
      if (event_functions != nullptr) {
        (this->*event_functions)(imageIndex, event);
      };
		};
		window->clear();
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
    float scaleFactor = min((float)winSize->width / base_image_frame.get()->baseTexture.getSize().x, (float)winSize->height / base_image_frame.get()->baseTexture.getSize().y);
    base_image_frame.get()->baseImage.setScale(scaleFactor, scaleFactor);
    base_image_frame.get()->baseImage.setOrigin(base_image_frame.get()->baseImage.getTexture()->getSize().x / 2.0f, base_image_frame.get()->baseImage.getTexture()->getSize().y / 2.0f);
    base_image_frame.get()->baseImage.setPosition(winSize->width / 2.0f, winSize->height / 2.0f);

    image_frames.emplace_back(std::move(base_image_frame));
  };
	handleDisplayEvents2(&imageHandler::xmove_images);
};
