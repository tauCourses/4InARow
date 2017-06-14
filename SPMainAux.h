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
#define ERR_COLUMN_FULL "Error: column %d is full\n" 
#define ERR_CANNOT_UNDO "Error: cannot undo previous move!\n"
#define ERR_GAME_OVER "Error: the game is over\n"
#define ERR_FUNC_FAIL "Error: %s has failed"
#define ERR_INVALID_LEVEL "Error: invalid level (should be between 1 to 7)\n"

#define MSG_ENTER_DIFF_LEVEL "Please enter the difficulty level between [1-7]:\n"
#define MSG_NEXT_MOVE "Please make the next move:\n"
#define MSG_YOU_WIN "Game over: you win\n"
#define MSG_COM_WIN "Game over: computer wins\n"
#define MSG_TIE "Game over: it's a tie\n"
#define MSG_AFTER_GAME_OVER "Please enter 'quit' to exit or 'restart_game' to start a new game!\n"
#define MSG_SUGGEST_MOVE "Suggested move: drop a disc to column %d\n"
#define MSG_REMOVE_COM_DISC "Remove disc: remove computer's disc at column %d\n"
#define MSG_REMOVE_USER_DISC "Remove disc: remove user's disc at column %d\n"
#define MSG_COM_MOVE "Computer move: add disc to column %d\n"
#define MSG_RESTARTED "Game restarted!\n"
#define MSG_EXIT "Exiting...\n"

/**
 * gets the difficulty level from the user.
 * while the input is not an integer between 1 to 7 prints an error and wait for another input.
 * @return
 * 0 if quit command found.
 * Otherwise, a legal difficulty number is returned.
 */
unsigned int getDifficulty();



/**
 * gets the input from user and return it after parsing.
 * @return
 * a SPCommand from user input
 */
SPCommand getCommandFromUser();

/**
 * gets the current command from the user and handles bad commands,
 * and makes sure only valid command returns.
 * @return
 * an executable SPcommand according to the user input.
 */
SPCommand getCommand(SPFiarGame *game);

/**
 * check if the command type is legal after game is over
 * @param command - the command to process
 * @return
 * true if command.cmd is restart or quit
 * false otherwise
 */
bool isGameOverCommand(SPCommand command);

/**
 * execute the command given to the given game.
 * @param command - the command to process.
 * 		  game - the current game that get the command.
 */
void executeCommand(SPCommand *pointerToCommand,SPFiarGame **pointerToGame);

/**
 * execute the command undo_move.
 * @param game - the current game that need to undo move in.
 */
void executeUndo(SPFiarGame *game);

/**
 * execute one undo_move - either the user's or the computer's.
 * complementary of the executeUndo fucntion.
 * @param game - the current game that need to undo one move in.
 */
int doOneUndo(SPFiarGame *game);

/**
 * execute the command add_disc given to the given game.
 * @param command - the command add_disc with it's argument to process.
 * 		  game - the current game that get the command.
 */
void executeAddDisc(SPCommand command,SPFiarGame *game);


/**
 * Initalize a new game - get's the diffculty input from user, and creates a new game and print the new game board.
 * @return
 * the new game
 * NULL if there was a memory failure or 'quit' was entered by user in difficulty input.
 */
SPFiarGame* initalize();

/**
 * makes the computer next turn after the user (if user has not won) according to minmax with given difficulty.
 * @param game - the current game that the play is done upon.
 */
void computerTurn(SPFiarGame *game);

/**
 * prints the correct winner message according to the game situation.
 * assumes the game has a winner.
 * @game - the game for which the winner message is printed
 */
void printWinner(char winner);


#endif
