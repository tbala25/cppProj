//
//  GameState.cpp
//  cppGame
//
//  Created by Nicholas Scheuring on 12/5/16.
//  Copyright © 2016 Nick Scheuring. All rights reserved.
//
#include <iostream>
#include "GameState.h"


GameState::GameState(){
    std::cout << "Game State Constructor" << std::endl;
    init(); //fills game board
    this->firstTile_ = -1;
    this->secondTile_ = -1;
}

/**
 * Collects the mouse cursor location
 * @param x the mouse's x position
 * @param y the mouse's y position
 */
void GameState::catchXYfromClick(int x, int y) noexcept{
    GameState::scanForMatches();
    int pieceIndex = whichPieceWasClicked(x, y);
   
    // If there is an active tile
    if(this->firstTile_ >= 0){
       // std::cout << "fol 1 " << this->firstTile_ << " " << this->secondTile_ << std::endl;
        //If the second tile exists already
        if(this->secondTile_ >= 0){
            // Then this piece is a new piece to swap
            this->firstTile_ = pieceIndex;
            this->secondTile_ = -1;
           // std::cout << "fol 2 " << this->firstTile_ << " " << this->secondTile_ << std::endl;
        }
        else{
            //This choice is the second in a swap
            this->secondTile_ = pieceIndex;
          //  std::cout << "fol 3 " << this->firstTile_ << " " << this->secondTile_ << std::endl;
            // DO the swap here
            swapCaller();
        }
    }
    else{
        // This is the active tile
        this->firstTile_ = pieceIndex;
    }
    std::cout << "Piece Index:: " << pieceIndex << std::endl;
    
}

/**
 * Adds a piece to the game state
 * @param piece the piece
 */
void GameState::addPiece(Piece piece) noexcept{
    this->gameBoard_.push_back(piece);
}

/**
 * Gets the vector index of the clicked piece
 * If not a piece, return -1
 * @param x the mouse's x position
 * @param y the mouse's y position
 * @return the index of the piece that was clicked
 */
int GameState::whichPieceWasClicked(int x, int y) const noexcept{
    int returnVal = -1;
    //std::cout << "WPWC BP? : VS: " << (this->gameBoard_).size() << std::endl;
    for(int i = 0; i < (this->gameBoard_).size(); i++){
        if(wasThisPieceClicked(x,y,
                               this->gameBoard_[i].getX(),
                               this->gameBoard_[i].getY())){
            //std::cout << "Clicke:: x= " << x << " y=" << y << "p-x" << this->gameBoard_[i].getX() << "p-y" <<this->gameBoard_[i].getY() << std::endl;
            returnVal = i;
            std::cout << "A Piece Was Clicked at index : " << i << std::endl;
            break;
        }
    }
    return returnVal;
}

/**
 * Checks if the mouse coords were on a piece
 * @param x the mouse's x position
 * @param y the mouse's y position
 * @return true if on piece, false else
 */
bool GameState::wasThisPieceClicked(int x, int y, int x_piece, int y_piece) const noexcept{
    return (x >= x_piece && x < x_piece + 50 && y_piece <= y && y_piece > y - 50);
}


/**
 * Swap the two pieces
 *
 */
void GameState::swapPieces() noexcept{
    Piece temp = this->gameBoard_[this->secondTile_];
    this->gameBoard_[this->secondTile_] = this->gameBoard_[this->firstTile_];
    this->gameBoard_[this->firstTile_] = temp;
}


/**
 * Calls the Swap function
 *
 */
void GameState::swapCaller() noexcept{
    swapPieces();
    //scanForVertMatches();
    //scanForHoriMatches();
    scanForMatches2();
    if(this->matchedPieces_.size() > 0){
        deleteMatchedPieces();
    }
    else{
        swapPieces();
    }
}

/**
 *  Scans the board for sets of 2
 *
 */
void GameState::scanForMatches() noexcept{

    scanForMatches2();
    deleteMatchedPieces();
}

void GameState::scanForMatches2() noexcept{
    //vert
    int firstCol;
    int secCol;
    for(int x = 0; x < 63; x++) {
        int y = x + 1;
        firstCol = x/8;
        secCol = y/8;
        if(firstCol == secCol) {
            //std::cout << "same col" + std::to_string(firstCol) << std::endl;
            if(doPiecesMatch(x, y)) {
                std::cout << " match found vert" + std::to_string(x) + "," + std::to_string(y) << std::endl;
                matchedPieces_.insert(x);
                matchedPieces_.insert(y);
            }
        }
    }

    //horiz
    for(int x = 0; x < 56; x++) {
        int y = x+8;
        if(doPiecesMatch(x, y)) {
            std::cout << " match found horiz" + std::to_string(x) + "," + std::to_string(y) << std::endl;
            matchedPieces_.insert(x);
            matchedPieces_.insert(y);
        }
        
    }
}

/**
 *  deletes matched pieces from the game board via the fall method
 *
 */
void GameState::deleteMatchedPieces() noexcept{
    
    // Iterate the set of pieces to "delete"
    for(auto f : this->matchedPieces_) {
        //GameState::fall(f);
        GameState::gameBoard_.at(f).setColor();
    }
    
    // Clear the matched pieces set as they have been 'deleted'
    this->matchedPieces_.clear();
}


/**
 * Checks if two pieces color matches
 * @return true if match, false else
 */
bool GameState::doPiecesMatch(int p1, int p2) const noexcept{
    bool rMatch = this->gameBoard_.at(p1).getR() == this->gameBoard_.at(p2).getR();
    bool gMatch = this->gameBoard_.at(p1).getG() == this->gameBoard_.at(p2).getG();
    bool bMatch = this->gameBoard_.at(p1).getB() == this->gameBoard_.at(p2).getB();
    return rMatch && gMatch && bMatch;
    //return this->gameBoard_.at(p1).getColor() == this->gameBoard_.at(p2).getColor();
}

void GameState::init() noexcept {
    int x = 350;
    int y = 50;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j ++) {
            GameState::gameBoard_.push_back(Piece(x,y));
            y +=60;
        }
        x+= 60;
        y = 50;
    }
}

std::vector<Piece> GameState::getPieces() const noexcept {
    return GameState::gameBoard_;
}
