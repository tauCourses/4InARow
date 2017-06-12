#include "SPFIARParser.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 1024

bool spParserIsInt(const char* str)
{
	if (*str == '-')
		str++;
	do
	{
		if ((*str < '0') || (*str > '9'))
			return false;
		str++;	
	}while (*str != '\0');
		
	return true;
}

SPCommand spParserPraseLine(const char* str)
{
	SPCommand result;
	char *token;
	char line[MAX_LINE_LENGTH];

	strcpy(line, str);

	const char *delimeter = " \t\r\n";
	char line[MAX_LINE_LENGTH], *token;

	struct command_t result;
	result.validArg = false;

	strcpy(line, str);	
	token = strtok(line, delimeter);
	result.cmd = commandFromStr(token);
	
	if(result.cmd == SP_ADD_DISC)
	{
		token = strtok(NULL, delimeter);
		if (spParserIsInt(token))
		{
			result.cmd = SP_ADD_DISC;
			result.arg = atoi(token);
			result.validArg = true;
		}			
	}

	token = strtok(NULL, delimeter);
	if (token != NULL)
		result.cmd = SP_INVALID_LINE;
	
	return result;
}

SP_COMMAND commandFromStr(char* token)
{
	if(strcmp(token,"quit") == 0)
		return SP_QUIT;
	if(strcmp(token,"restart") == 0)
		return SP_RESTART;
	if(strcmp(token,"suggest_move") == 0)
		return SP_SUGGEST_MOVE;
	if(strcmp(token,"undo_move") == 0)
		return SP_UNDO_MOVE;
	if(strcmp(token,"add_disc") == 0)
		return SP_ADD_DISC;

	return SP_INVALID_LINE;
	
}
