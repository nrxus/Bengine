#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace Bengine {
  TextureCache::TextureCache() {}
  TextureCache::~TextureCache() {}

  GLTexture TextureCache::getTexture(std::string texturePath) {
    auto nit = m_textureMap.find(texturePath);
    if (nit == m_textureMap.end()) {
      GLTexture newTexture = ImageLoader::loadPNG(texturePath);
      m_textureMap.insert(make_pair(texturePath,newTexture));
      return newTexture;
    }
    return nit->second;
  }
}
