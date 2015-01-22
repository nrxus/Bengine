#pragma once
#include "GLTexture.h"
#include <string>

namespace Bengine {
  class ImageLoader {
  public:
    static GLTexture loadPNG(std::string filePath);
  };
}
