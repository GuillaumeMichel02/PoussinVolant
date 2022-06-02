#include "text_manager.h"

TextManager::TextManager(TTF_Font* fontBig_temp, TTF_Font* fontSmall_temp) : fontBig(fontBig_temp), fontSmall(fontSmall_temp), frontColor({255,220,0}), backColor({0,0,0}), frontMessage(NULL), backMessage(NULL) {}