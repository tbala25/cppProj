#ifndef GameState_h
#define GameState_h

#include <stdio.h>
#include <vector>
#include <set>
#include "Piece.h"

class GameState{
public:
    /**
     * Constructor for the Game State object
     *
     */
    GameState();

    /**
     * Collects the mouse cursor location
     * @param x the mouse's x position
     * @param y the mouse's y position
     */
    void catchXYfromClick(int x, int y) noexcept;
    /**
     * Adds a piece to the game state
     * @param piece the piece
     */
    void addPiece(Piece piece) noexcept;
    /**
     * Gets the vector index of the clicked piece
     * If not a piece, return -1
     * @param x the mouse's x position
     * @param y the mouse's y position
     * @return the index of the piece that was clicked
     */
    int whichPieceWasClicked(int x, int y) const noexcept;
    /**
     * Checks if the mouse coords were on a piece
     * @param x the mouse's x position
     * @param y the mouse's y position
     * @param x_piece the piece's x position
     * @param y_piece the piece's y position
     * @return true if on piece, false else
     */
    bool wasThisPieceClicked(int x, int y, int x_piece, int y_piece) const noexcept;
    /**
     * Swap the two pieces
     *
     */
    void swapPieces() noexcept;
    /**
     * Calls the Swap function
     *
     */
    void swapCaller() noexcept;
    /**
     *  Scans the board for sets of 3
     *
     */
    void scanForMatches() noexcept;

    /**
     *  deletes matched pieces from the game board
     *  [Does not actually delete them, rather resets
     *   the color to a new color]
     */
    void deleteMatchedPieces() noexcept;
    /**
     * Checks if two pieces color matches
     * @return true if match, false else
     */
    bool doPiecesMatch(int p1, int p2) const noexcept;
    
    /*
     * scanFor matches helper
     * scans vertically and horizontally
     */
    void scanForMatches2() noexcept;
    
    /*
     * fills gameBoard_ with pieces
     */
    void init() noexcept;
    
    /*
     * @params the x and y coord to init the piece with
     *@returns a new piece
     */
    Piece newPiece(const int& x, const int& y) const noexcept;
    
    /*
     * @returns the vector of pieces
     */
    std::vector<Piece> getPieces() const noexcept;
    
private:
    /* The 8x8 game board */
    std::vector< Piece > gameBoard_;
    /* The active tile */
    int firstTile_;
    /* The active tile */
    int secondTile_;
    /* Indexes of matched pieces */
    std::set<int> matchedPieces_;
    
};

#endif /* GameState_h */
