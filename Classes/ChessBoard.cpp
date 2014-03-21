#include "ChessBoard.h"
#include "Defines.h"
#include "NumberTile.h"
#include <string.h>

bool ChessBoard::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	

	auto bgLayer = LayerColor::create(Color4B(160, 160, 160, 255), CHESS_LEN, CHESS_LEN);
	this->addChild(bgLayer);
	
	TTFConfig ttfConfig("fonts/Marker Felt.ttf", 50,GlyphCollection::ASCII);
	_scoreLabel = Label::createWithTTF(ttfConfig, "Score:0");
	_scoreLabel->setPosition(Point(100, 400));
	_scoreLabel->setColor(Color3B(255,255,0));
	this->addChild(_scoreLabel);

	for (auto i = 0; i < 4; ++i)
		for(auto j = 0; j < 4; ++j)
		{
			auto p_tile = LayerColor::create(Color4B(200, 200, 200, 255), TILE_LEN, TILE_LEN); 
			p_tile->setPosition(getTilePostion(i, j));
			this->addChild(p_tile);
		}

	_score = 0;
	memset(_chess, 0, sizeof(_chess));

	generateNewTile();
	generateNewTile();

	auto listerner = EventListenerTouchOneByOne::create();
	listerner->onTouchBegan = [this] (Touch* touch, Event* event){
		_startPoint = touch->getLocation();
		return true;
	};
	listerner->onTouchEnded = [this] (Touch* touch, Event* event){
		_endPoint = touch->getLocation();

 		auto dirX = _endPoint.x - _startPoint.x;
 		auto dirY = _endPoint.y - _startPoint.y;

		if (_endPoint.getDistance(_startPoint) < 20) return;

		auto angle = Point(dirX, dirY).getAngle();
		auto degrees = angle * 180 / PI;

		if (degrees<=45 && degrees>=-45)
			moveRight();
		else if (degrees > 45 && degrees < 135)
			moveUp();
		else if (degrees >= 135 || degrees <= -135)
			moveLeft();
		else 
			moveDown();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listerner, this);
	
    return true;
}

/*
	 0  1  2  3
	 4  5  6  7
	 8  9 10 11
	12 13 14 15
*/
Point ChessBoard::getTilePostion( int x, int y )
{
	auto posX = (y+1)*SPACE+y*TILE_LEN;
	auto posY = CHESS_LEN - ((x+1)*SPACE+(x+1)*TILE_LEN);

	return Point(posX, posY);
}

bool ChessBoard::isChessBoardFull()
{
	_emptyTiles.clear();
	for (int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			if (!_chess[i][j]) _emptyTiles.push_back(i*4+j);
	return _emptyTiles.size() == 0;
}

void ChessBoard::checkGameOver()
{
	if (!isChessBoardFull()) 
		return;

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			if (i > 0 && _chess[i-1][j] == _chess[i][j]) return;
			if (i < 3 && _chess[i][j] == _chess[i+1][j]) return;
			if (j > 0 && _chess[i][j-1] == _chess[i][j]) return;
			if (j < 3 && _chess[i][j] == _chess[i][j+1]) return;
		}
	
	TTFConfig ttfconfig("fonts/Marker Felt.ttf", 50);
	auto labGameOver = Label::createWithTTF(ttfconfig, "Game Over!");
	labGameOver->setPosition(Point(CHESS_LEN/2, CHESS_LEN/2));
	labGameOver->setAnchorPoint(Point::ANCHOR_MIDDLE);
	labGameOver->setScale(0.1f);
	labGameOver->runAction(ScaleTo::create(0.2f, 1.0f));
	addChild(labGameOver);
	_eventDispatcher->removeEventListenersForTarget(this);
}

void ChessBoard::generateNewTile()
{
	if(isChessBoardFull()) 
		return;

	int t = rand() % _emptyTiles.size();
	int number = _emptyTiles[t];
	int x = number / 4;
	int y = number % 4;
	auto newTile = NumberTile::create();
	auto pos = getTilePostion(x, y);
	newTile->setPosition(pos.x, pos.y);
	newTile->setScale(0.1f);
	newTile->setVisible(false);
	auto actSeq = Sequence::create(DelayTime::create(0.1f), 
								   Show::create(),
								   ScaleTo::create(0.2f, 1.0f), NULL);
	newTile->runAction(actSeq);
	addChild(newTile);

	_chess[x][y] = newTile->getNumber();
	_tileMap.insert(std::make_pair(number, newTile));

	checkGameOver();
}

void ChessBoard::moveLeft()
{
	int isMerge[4][4] = {0};
	bool hasEmpty = false;
	for (int i = 0; i < 4; ++i)
	{
		for(int j = 1; j < 4; ++j)
			if (_chess[i][j])
			{
				int k = j-1;

				if (_chess[i][k] && _chess[i][k] != _chess[i][j]) continue;

				hasEmpty = true;

				while(k>=0 && !_chess[i][k]) k--;

				if (k >= 0 && _chess[i][k] == _chess[i][j] && !isMerge[i][k])
				{
					mergeTwoTile(i, k, i, j);
					isMerge[i][k] = 1;
				}
				else 
					moveTileTo(i, k+1, i, j);
			}
	}

	if (hasEmpty) 
		generateNewTile();
}

void ChessBoard::moveRight()
{
	int isMerge[4][4] = {0};
	bool hasEmpty = false;
	for (int i = 0; i < 4; ++i)
	{
		for(int j = 2; j >= 0; --j)
			if (_chess[i][j])
			{
				int k = j+1;
				if (_chess[i][k] && _chess[i][k] != _chess[i][j]) continue;
				hasEmpty = true;
				while(k<=3 && !_chess[i][k]) k++;
				if (k <=3 && _chess[i][k] == _chess[i][j] && !isMerge[i][k])
				{
					mergeTwoTile(i, k, i, j);
					isMerge[i][k] = 1;
				}
				else 
					moveTileTo(i, k-1, i, j);
			}
	}
	if (hasEmpty) 
		generateNewTile();
}

void ChessBoard::moveUp()
{
	int isMerge[4][4] = {0};
	bool hasEmpty = false;
	for (int j = 0; j < 4; ++j)
	{
		for(int i = 1; i < 4; ++i)
			if (_chess[i][j])
			{
				int k = i-1;
				if (_chess[k][j] && _chess[k][j] != _chess[i][j]) continue;
				hasEmpty = true;
				while(k>=0 && !_chess[k][j]) k--;
				if (k >=0 && _chess[k][j] == _chess[i][j] && !isMerge[k][j])
				{
					mergeTwoTile(k, j, i, j);
					isMerge[k][j] = 1;
				}
				else 
					moveTileTo(k+1, j, i, j);
			}
	}
	if (hasEmpty) 
		generateNewTile();
}

void ChessBoard::moveDown()
{
	int isMerge[4][4] = {0};
	bool hasEmpty = false;
	for (int j = 0; j < 4; ++j)
	{
		for(int i = 2; i >= 0; --i)
			if (_chess[i][j])
			{
				int k = i+1;
				if (_chess[k][j] && _chess[k][j] != _chess[i][j]) continue;
				hasEmpty = true;
				while(k<=3 && !_chess[k][j]) k++;
				if (k<=3 && _chess[k][j] == _chess[i][j] && !isMerge[k][j])
				{
					mergeTwoTile(k, j, i, j);
					isMerge[k][j] = 1;
				}
				else 
					moveTileTo(k-1, j, i, j);
			}
	}
	if (hasEmpty)
		generateNewTile();
}

void ChessBoard::mergeTwoTile( int x1, int y1, int x2, int y2 )
{
	auto key1 = x1*4+y1;
	auto key2 = x2*4+y2;
	CCASSERT(_tileMap.find(key1) != _tileMap.end(), "k1 not find in map");
	CCASSERT(_tileMap.find(key2) != _tileMap.end(), "k2 not find in map");

	_chess[x1][y1]++;
	_chess[x2][y2] = 0;
	
	NumberTile* tile1 = _tileMap[key1];
	NumberTile* tile2 = _tileMap[key2];
	_tileMap.erase(key2);

	Point finalPos = getTilePostion(x1, y1);
	auto act1 = MoveTo::create(finalPos.getDistance(tile2->getPosition())/MOVE_SPPED, finalPos);
	auto act2 = ScaleTo::create(0.1f, 1.2f);
	auto act3 = ScaleTo::create(0.05f, 1.0f);
	auto act4 = CallFunc::create(
		[=](){
			_score += MI(_chess[x1][y1]);
			char str[30];
			sprintf(str, "Score:%d", _score);
			_scoreLabel->setString(str);
			tile1->setNumber(_chess[x1][y1]);
			tile2->removeFromParent();
	});

	tile2->runAction(Sequence::create(act1, act2, act3, act4, NULL));
}

void ChessBoard::moveTileTo( int x1, int y1, int x2, int y2 )
{
	auto key1 = x1*4+y1;
	auto key2 = x2*4+y2;
	CCASSERT(_tileMap.find(key2) != _tileMap.end(), "k2 not find in map");

	_chess[x1][y1] = _chess[x2][y2];
	_chess[x2][y2] = 0;

	NumberTile* tile2 = _tileMap[key2];
	Point finalPos = getTilePostion(x1, y1);
	auto actMove = MoveTo::create(finalPos.getDistance(tile2->getPosition())/MOVE_SPPED, finalPos);
	tile2->runAction(actMove);

	_tileMap.erase(key2);
	_tileMap.insert(std::make_pair(key1, tile2));
}










