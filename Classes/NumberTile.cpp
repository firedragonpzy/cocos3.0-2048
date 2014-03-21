#include "NumberTile.h"
#include "Defines.h"
#include <stdio.h>

bool NumberTile::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255)))
	{
		return false;
	}

	_number = rand() % 2 + 1;
	this->setColor(Color3B(Tile_Color[_number].r, Tile_Color[_number].g, Tile_Color[_number].b));
	this->setContentSize(Size(TILE_LEN, TILE_LEN));

	TTFConfig ttfconfig = TTFConfig("fonts/Marker Felt.ttf", 50);
	char str[10];
	sprintf(str, "%d", MI(_number));
	_scoreLabel = Label::createWithTTF(ttfconfig, str);
	_scoreLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	_scoreLabel->setPosition(Point(TILE_LEN/2, TILE_LEN/2));
	this->addChild(_scoreLabel);

	return true;
}

void NumberTile::setNumber( int number )
{
	_number = number;
	char str[10];
	sprintf(str, "%d", MI(_number));
	_scoreLabel->setString(str);
	this->setColor(Color3B(Tile_Color[_number].r, Tile_Color[_number].g, Tile_Color[_number].b));
}

