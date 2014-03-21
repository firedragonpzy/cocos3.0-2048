#include "HelloWorldScene.h"
#include "ChessBoard.h"
#include "Defines.h"

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
	
	auto director = Director::getInstance();
	auto FrameSize = director->getOpenGLView()->getFrameSize();
	auto DesignSize = Size(DESIGN_WIDTH, DESIGN_HEIGHT);

	float scaleX = FrameSize.width / DesignSize.width;
	float scaleY = FrameSize.height / DesignSize.height;
	float p_scale = scaleX > scaleY ? scaleY : scaleX;
	Point center = Point(FrameSize.width/2, FrameSize.height/2);

	auto layer = HelloWorld::create();
	layer->setContentSize(DesignSize);
	layer->setAnchorPoint(Point(0.5, 0.5));
	layer->ignoreAnchorPointForPosition(false);
	layer->setScale(p_scale);
	layer->setPosition(center);
    
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(DESIGN_WIDTH - closeItem->getContentSize().width/2, closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

	auto bglayer = LayerColor::create(Color4B(230, 230, 230, 255));
	bglayer->setContentSize(Size(DESIGN_WIDTH, DESIGN_HEIGHT));
	this->addChild(bglayer);

    auto chessBoard = ChessBoard::create();
	chessBoard->setContentSize(Size(CHESS_LEN, CHESS_LEN));
	auto posX = (DESIGN_WIDTH - CHESS_LEN) / 2;
	auto posY = (DESIGN_HEIGHT - CHESS_LEN) / 2; 
	chessBoard->setPosition(Point(posX, posY));
	this->addChild(chessBoard);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(scene);
}
