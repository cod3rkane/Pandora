#ifndef CORE_GAME_HPP
#define CORE_GAME_HPP

#include "util/registry.hpp"

namespace Core {
  class Game {
  public:
    void init();
    void input();
    bool logic();
    void render();

  private:
    enum class State {
                      playing,
                      won,
                      lost
    };

    Registry reg;
    State state = State::playing;
  };
}

#endif
