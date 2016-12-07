#include <stdio.h>
#include <SDL2/SDL.h>
#include <ctime>
#include "Piece.h"

using namespace std;


Piece::Piece(const int& ex, const int& why) {
    Piece::x_ = ex;
    Piece::y_ = why;
    setColor();
}

void Piece::setColor() noexcept{
    int randNum = rand() % 8 + 1; //generate random number
    //set cases for "random" colors
    if(randNum == 1) {
        Piece::color_ = make_tuple(255,0,0);
    }
    else if(randNum == 2) {
        Piece::color_ = make_tuple(0,255,0);
    }
    else if(randNum == 3) {
        Piece::color_ = make_tuple(0,0,255);
    }
    else if(randNum == 4) {
        Piece::color_ = make_tuple(255,255,0);
    }
    else if(randNum == 5) {
        Piece::color_ = make_tuple(0,255,255);
    }
    else if(randNum == 6) {
        Piece::color_ = make_tuple(150,100,0);
    }
    else if(randNum == 7) {
        Piece::color_ = make_tuple(0,100,255);
    }
    else if(randNum == 8) {
        Piece::color_ = make_tuple(100,0,150);
    }
}

int Piece::getX() const noexcept {
    return Piece::x_;
}

int Piece::getY() const noexcept{
    return Piece::y_;
}

int Piece::getR() const noexcept{
    return get<0>(this->color_);
}

int Piece::getG() const noexcept{
    return get<1>(this->color_);
}

int Piece::getB() const noexcept{
    return get<2>(this->color_);
}

void Piece::setY(const int& a) noexcept {
    Piece::y_ = a;
}

void Piece::setX(const int& a) noexcept {
    Piece::x_ = a;
}
