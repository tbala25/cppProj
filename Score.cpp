#include "Score.h"
using namespace std;

Score::Score()
{
    //ctor
}

Score::~Score()
{
    //dtor
}

void Score::increaseScore(const int& x) noexcept
{
    curScore += x;
    regenScore();
}

int Score::getScore() noexcept
{
    return curScore;
}

void Score::Draw(SDL_Renderer* r)
{
    SDL_Texture* message  = SDL_CreateTextureFromSurface(r, Score::sMessage); //sets message
    SDL_Rect messageRect; //create rect to draw
    messageRect.x = 10;
    messageRect.y = 10;
    messageRect.w = 100;
    messageRect.h = 100;
    SDL_RenderCopy(r, message, NULL, &messageRect);
    SDL_DestroyTexture(message);
}

void Score::regenScore()
{
    if(curScore != prevScore) { //if scores differ
	std::string scoreStr =  "Score: " + std::to_string(curScore); //print score
    	Score::sMessage = TTF_RenderText_Solid(Score::Sans, scoreStr.c_str(), Score::White); //render
    }
}
