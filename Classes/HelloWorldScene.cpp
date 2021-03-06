#include "HelloWorldScene.h"


#include "MapBuilder.h"
#include "Utils.h"

#include <noise/noise.h>
#include <json/document.h>

#include <algorithm>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Point center{visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y};

    map_ = GameMap::loadTmx("terrain.tmx", "Terrain", "Walkable");

    fieldWidth_ = visibleSize.width * 3;
    fieldHeight_ = visibleSize.height * 3;

    MapBuilder builder;
    builder.buildMap(map_, fieldWidth_, fieldHeight_);

    // add the sprite as a child to this layer
    this->addChild(map_->getTmxMap(), 0);

    rapidjson::Document heroJson;
    readJsonFile("hero.json", heroJson);

    EntityInfo *playerInfo = new EntityInfo();
    playerInfo->read(heroJson);

    player_ = new Player(playerInfo);
    player_->init(this);

    // creating a keyboard event listener
    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        if(keyCode == DOWN_ARROW)
        {
            player_->walk(Direction::down);
        }
        else if (keyCode == UP_ARROW)
        {
            player_->walk(Direction::up);
        }
        else if (keyCode == LEFT_ARROW)
        {
            player_->walk(Direction::left);
        }
        else if (keyCode == RIGHT_ARROW)
        {
            player_->walk(Direction::right);
        }

        if(std::find(downKeys_.begin(), downKeys_.end(), keyCode) == downKeys_.end())
        {
            downKeys_.push_back(keyCode);
        }
    };

    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        downKeys_.erase(std::remove(downKeys_.begin(), downKeys_.end(), keyCode), downKeys_.end());
        player_->stop();
    };

    rapidjson::Document enemiesJson;
    readJsonFile("enemies.json", enemiesJson);
    for (auto iter = enemiesJson.Begin(); iter != enemiesJson.End(); ++iter)
    {
        EntityInfo *enemyInfo = new EntityInfo{};
        enemyInfo->read(*iter);
        enemyInfo_.push_back(enemyInfo);
    }

    std::random_device rd;
    std::default_random_engine randomEnemy{rd()};
    int numEnemies = 1;
    size_t enemyCount = enemyInfo_.size();
    for (int e = 0; e < numEnemies; ++e)
    {
        int enemyIndex = randomEnemy() % enemyCount;
        EntityInfo *enemyInfo = enemyInfo_[enemyIndex];
        Enemy *enemy = new Enemy{enemyInfo};
        enemy->init(this);
        enemy->sprite()->setPosition({64.0, 64.0});
        enemies_.push_back(enemy);
    }

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->runAction(Follow::create(player_->sprite(), Rect(0, 0, fieldWidth_, fieldHeight_)));

    this->schedule(schedule_selector(HelloWorld::updateScene));

    return true;
}

void HelloWorld::updateScene(float delta)
{
    for (Enemy *enemy : enemies_)
    {
        enemy->update(delta, fieldWidth_, fieldHeight_, map_);
    }

    bool isRunning = isKeyPressed(SHIFT_KEY);
    int speed = isRunning ? 6 : 3;

    Sprite *playerSprite = player_->sprite();
    Size playerSize = playerSprite->getTextureRect().size;
    float width = playerSize.width;
    float height = playerSize.height;

    Vec2 playerPosition = playerSprite->getPosition();
    float playerX = playerSprite->getPositionX();
    float playerY = playerSprite->getPositionY();

    bool stop = true;
    if (isKeyPressed(RIGHT_ARROW))
    {
        if (playerX + width + speed < fieldWidth_)
        {
            playerPosition.x += speed;
            stop = false;
        }
        else
        {
            playerPosition.x = fieldWidth_ - width;
        }
    }
    else if (isKeyPressed(LEFT_ARROW))
    {
        if (playerX > speed)
        {
            playerPosition.x -= speed;
            stop = false;
        }
        else
        {
            playerPosition.x = 0;
        }
    }
    else if (isKeyPressed(UP_ARROW))
    {
        if (playerY + height + speed < fieldHeight_)
        {
            playerPosition.y += speed;
            stop = false;
        }
        else
        {
            playerPosition.y = fieldHeight_ - height;
        }
    }
    else if (isKeyPressed(DOWN_ARROW))
    {
        if (playerY >= speed)
        {
            playerPosition.y -= speed;
            stop = false;
        }
        else
        {
            playerPosition.y = 0;
        }
    }

    if (stop)
    {
        player_->stop();
        return;
    }


    {
    }

    player_->setPosition(playerPosition, map_);
}
