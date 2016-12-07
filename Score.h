#ifndef SCORE_H
#define SCORE_H
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>
using namespace std;

class Score
{
    public:
        Score();
        virtual ~Score();
        void increaseScore(int x) noexcept;
        int getScore() noexcept;
        void Draw(SDL_Renderer* r);
        void regenScore();

    protected:

    private:
        int curScore = 0;
        int prevScore = -1;

        TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
	SDL_Color White = {255, 255, 255};
	SDL_Surface* sMessage = TTF_RenderText_Solid(Sans, "Score :", White);
};

#endif // SCORE_H
