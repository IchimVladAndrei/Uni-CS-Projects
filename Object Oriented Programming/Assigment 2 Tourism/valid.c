#include "valid.h"
#include <ctype.h>
#include <string.h>
#pragma once

int validate_date(char date[])
{
	// 05/10/2021
	// 0123456789
	if (date[2] != '/' && date[5] != '/')
		return 0;
	for (int i = 0; i < strlen(date); i++)
		if (i != 2 && i != 5 && isdigit(date[i]) == 0)
			return 0;
	return 1;

}

int validate_destination(char destination[])
{
	if (strlen(destination) >= 3)
		return 1;
	return 0;
}

int validate_type(char type[])
{
	
	if (strcmp(type, "Seaside") == 0 || strcmp(type, "Mountain") == 0 || strcmp(type, "City break") == 0)
		return 1;
	return 0;

}

int validate_price(int price)
{
	if (price > 0)
		return 1;
	return 0;
}
