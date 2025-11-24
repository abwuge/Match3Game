#include "utils/GameConfig.h"

GameConfig &GameConfig::getInstance()
{
    static GameConfig instance;
    return instance;
}
