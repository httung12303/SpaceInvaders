#include "BasicFunction.h"

void waitUntilKeyPressed()
{
    SDL_Event e;

    while (true) {
        if (SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }

}

void errorLog(std::ostream& os, std::string msg, bool fatal) {

    os << msg << " Error: " << SDL_GetError() << '\n';

    if (fatal) {
        SDL_Quit();
        exit(1);
    }

}

bool overlap(const SDL_Rect& a, const SDL_Rect& b) {
    return !(a.x > b.x + b.w || a.x + a.w < b.x || a.y > b.y + b.h || a.y + a.h < b.y);
}
