#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

//put auxiliary functions and constants used by the main function here.

#include "SPFIARParser.h"
#include "SPFIARGame.h"
#include "SPArrayList.h"
#include "main.h"
#include "SPMiniMax.h"

#define HISTORY_SIZE 20

//All messages to print are predefined here
#define ERR_INVALID_COMMAND "Error: invalid command\n"
#define ERR_COLUMN_OUT_OF_RANGE "Error: column number must be in range 1-7\n"
#define ERR_COLUMN_FULL "Error: column X is full\n"
#define ERR_CANNOT_UNDO "Error: cannot undo previous move!\n"
#define ERR_GAME_OVER "Error: the game is over\n"
#define ERR_FUNC_FAIL "Error: %s has failed"
#define ERR_INVALID_LEVEL "Error: invalid level (should be between 1 to 7\n"

#define MSG_ENTER_DIFF_LEVEL "Please enter the difficulty level between [1-7]:\n"
#define MSG_NEXT_MOVE "Please make the next move:\n"
#define MSG_YOU_WIN "Game over: you win\n"
#define MSG_COM_WIN "Game over: computer wins\n"
#define MSG_TIE "Game over: it's a tie\n"
#define MSG_AFTER_GAME_OVER "Please enter 'quit' to exit or 'restart' to start a new game!\n"
#define MSG_SUGGEST_MOVE "Suggested move: drop a disc to column %d\n"
#define MSG_REMOVE_COM_DISC "Remove disc: remove computer's disc at column %d\n"
#define MSG_REMOVE_USER_DISC "Remove disc: remove user's disc at column %d\n"
#define MSG_COM_MOVE "Computer move: add disc to column %d\n"
#define MSG_EXIT "Exiting...\n"




//need to fix!
/**
 * gets the difficulty level from the user.
 * while the input is not an integer between 1 to 7 prints an error and wait for another input.
 * @return
 * -1 if there is fail in scanf().
 * Otherwise, a legal difficulty number is returned.
 */
unsigned int getDifficulty();



/**
 * return a command from user input
 */
SPCommand getCommandFromUser();

/**
 * gets the current command from the user.
 * @return
 * an SPcommand according to the user input.
 */
SPCommand getCommand(SPFiarGame *game);

/**
 */
bool isGameOverCommand(SPCommand command);

/*

fill in here!

*/
void executeCommand(SPCommand command,SPFiarGame *game);

void executeUndo(SPFiarGame *game);

int doOneUndo(SPFiarGame *game);

void executeAddDisc(SPCommand command,SPFiarGame *game);

SPFiarGame* initalize();

void computerTurn(SPFiarGame *game);

/**
 * prints the correct winner message according to the game situation.
 * assumes the game has a winner.
 * @game - the game for which the winner message is printed
 */
void printWinner(char winner);

#endif
