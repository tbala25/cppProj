#ifndef Piece_h
#define Piece_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include <tuple>

class Piece {
    
/*
 * Piece object represents rect in board. It is a rect and they differ by color
 * has x,y coord
 * has a tuple to represent rgb values for color
 */
public:
    
    /**
     * Public constructor
     * @params the x and y coordinate of the rect
     */
    Piece(const int& x, const int&y);
    
    /*
     *@returns the x coord of piece
     */
    int getX() const noexcept;
    /*
     *@returns the y coord of piece
     */
    int getY() const noexcept;
    /*
     *@returns the red value of color
     */
    int getR() const noexcept;
    /*
     *@returns the green value of color
     */
    int getG() const noexcept;
    /*
     *@returns the blue value of color
     */
    int getB() const noexcept;
    /* Sets y coordinate
     *@param the y coord
     */
    void setY(/*given y coord*/const int& a) noexcept;
    /* Sets x coordinate
     *@param the x coord
     */
    void setX(/*given y coord*/const int& a) noexcept;
    /*
     * Sets the tuple<int,int,int> for color via a random number generator
     */
    void setColor() noexcept;

    
    
private:
    //pos in grid, 0-8
    int x_;
    int y_;
    
    std::tuple<int, int, int> color_;
};


#endif /* Piece_h */
