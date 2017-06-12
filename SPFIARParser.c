#include "SPFIARParser.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 1024

bool spParserIsInt(const char* str)
{
	if (*str == '\0')
		return false;
	if (*str == '-')
		str++;
	if (*str == '\0')
		return false;

	bool isInt = true;

	while (*str != '\0')
	{

		if ((*str >'9') || (*str <'0'))
		{
			isInt = false;
			break;
		}
		str++;
	}
	return isInt;
}

/**
 * Parses a specified line. If the line is a command which has an integer
 * argument then the argument is parsed and is saved in the field arg and the
 * field validArg is set to true. In any other case then 'validArg' is set to
 * false and the value 'arg' is undefined
 *
 * @return
 * A parsed line such that:
 *   cmd - contains the command type, if the line is invalid then this field is
 *         set to INVALID_LINE
 *   validArg - is set to true if the command is add_disc and the integer argument
 *              is valid
 *   arg      - the integer argument in case validArg is set to true
 */

SPCommand spParserPraseLine(const char* str)
{
	struct command_t result;
	char *token;
	char line[MAX_LINE_LENGTH];

	strcpy(line, str);
	const char *delimeter = " \t\r\n";
	result.validArg = false;
	result.cmd = SP_INVALID_LINE;

	token = strtok(line, delimeter);

	//if command is 'quit'
	if (strcmp(token,"quit") == 0)
	{
		token = strtok(NULL, delimeter);
		if (token == NULL)
		{
			result.cmd = SP_QUIT;
			return result;
		}
	}

	//if command is 'restart'
	if (strcmp(token,"restart") == 0)
	{
		token = strtok(NULL, delimeter);
		if (token == NULL)
		{
			result.cmd = SP_RESTART;
			return result;
		}
	}

	//if command is 'suggest_move'
	if (strcmp(token,"suggest_move") == 0)
	{
		token = strtok(NULL, delimeter);
		if (token == NULL)
		{
			result.cmd = SP_SUGGEST_MOVE;
			return result;
		}

	}

	//if command is 'undo_move'
	if (strcmp(token,"undo_move") == 0)
	{
		token = strtok(NULL, delimeter);
		if (token == NULL){
			result.cmd = SP_UNDO_MOVE;
			return result;
		}


	}

	//if command is 'add_disc'
	printf("%s\n",token);
	if (strcmp(token,"add_disc\0") == 0)
	{
		token = strtok(NULL, delimeter);
		if (spParserIsInt(token))
		{
			result.cmd = SP_ADD_DISC;
			result.arg = atoi(token);
			result.validArg = true;
			return result;
		}
	}
	return result;

}
