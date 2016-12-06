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
    init();
    this->firstTile_ = -1;
    this->secondTile_ = -1;
}


/**
 * Collects the mouse cursor location
 * @param x the mouse's x position
 * @param y the mouse's y position
 */
void GameState::catchXYfromClick(int x, int y){
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
void GameState::addPiece(Piece piece){
    this->gameBoard_.push_back(piece);
}

/**
 * Gets the vector index of the clicked piece
 * If not a piece, return -1
 * @param x the mouse's x position
 * @param y the mouse's y position
 * @return the index of the piece that was clicked
 */
int GameState::whichPieceWasClicked(int x, int y){
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
bool GameState::wasThisPieceClicked(int x, int y, int x_piece, int y_piece){
    return (x >= x_piece && x < x_piece + 50 && y_piece <= y && y_piece > y - 50);
}


/**
 * Swap the two pieces
 *
 */
void GameState::swapPieces(){
    Piece temp = this->gameBoard_[this->secondTile_];
    this->gameBoard_[this->secondTile_] = this->gameBoard_[this->firstTile_];
    this->gameBoard_[this->firstTile_] = temp;
}


/**
 * Calls the Swap function
 *
 */
void GameState::swapCaller(){
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
void GameState::scanForMatches(){
    //scanForVertMatches();
    //scanForHoriMatches();
    scanForMatches2();
    deleteMatchedPieces();
}

void GameState::scanForMatches2() {
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
void  GameState::deleteMatchedPieces(){
    
    // Iterate the set of pieces to "delete"
    for(auto f : this->matchedPieces_) {
        GameState::fall(f);
    }
    
    // Clear the matched pieces set as they have been 'deleted'
    this->matchedPieces_.clear();
}

void GameState::fall(int f) {
    int col = f/8; //top piece of col index
    int beneathY;
    
    //starts at top of col and iterates down until(not including) piece that is to be deleted
    for(int x = col; x < f; x++) {
        //X is to be deleted, x+1 takes x's Yloc and index in board
    
        //the Y coord of the piece below the current piece
        beneathY  = GameState::gameBoard_.at(x+1).getY();
        
        //set new Y coord
        GameState::gameBoard_.at(x).setY(beneathY);
        //set new index in board
        GameState::gameBoard_.at(x+1) = GameState::gameBoard_.at(x);
        
    }
    //add piece to top
    GameState::gameBoard_.at(col) = GameState::newPiece(60*col, 50);
}

Piece GameState::newPiece(int x, int y) {
    return Piece(x,y);
}


/**
 * Checks if two pieces color matches
 * @return true if match, false else
 */
bool GameState::doPiecesMatch(int p1, int p2){
    bool rMatch = this->gameBoard_.at(p1).getR() == this->gameBoard_.at(p2).getR();
    bool gMatch = this->gameBoard_.at(p1).getG() == this->gameBoard_.at(p2).getG();
    bool bMatch = this->gameBoard_.at(p1).getB() == this->gameBoard_.at(p2).getB();
    return rMatch && gMatch && bMatch;
    //return this->gameBoard_.at(p1).getColor() == this->gameBoard_.at(p2).getColor();
}

void GameState::init() {
    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 8; y ++) {
            GameState::gameBoard_.push_back(Piece(x,y));
        }
    }
}

std::vector<Piece> GameState::getPieces() {
    return GameState::gameBoard_;
}
