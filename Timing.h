#pragma once

namespace Bengine {
  class FpsLimiter {
  public:
    FpsLimiter();
    ~FpsLimiter();

    void init(float maxFPS);
    void begin();
    float end(); //return current FPS
    void setMaxFPS(float maxFPS);

  private:
    void calculateFPS();

    float m_fps;
    float m_frameTime;
    float m_maxFPS;
    unsigned int m_startTicks;
  };
}
