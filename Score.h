#ifndef SCORE_H
#define SCORE_H
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>
using namespace std;

class Score
{
public:
    /*
    * Public constructor
    */
    Score();
    /*
    * Destructor
    */
    virtual ~Score();
    /*
     * adds given int to score
     * @params score addition
     */
    void increaseScore(const int& x) noexcept;
    /*
     * @returns the score
     */
    int getScore() noexcept;
    /*
     * draws the score
     */
    void Draw(SDL_Renderer* r);
    /*
     * regens the score
     */
    void regenScore();
    
private:
    //cur score
    int curScore = 0;
    //previous score
    int prevScore = -1;

    //font for rendering
    TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
	SDL_Color White = {255, 255, 255};
	SDL_Surface* sMessage = TTF_RenderText_Solid(Sans, "Score :", White);
};

#endif // SCORE_H
