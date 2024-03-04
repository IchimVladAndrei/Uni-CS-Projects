#include "validator.h"
#include <string>

bool Validator::validate_title(string title)
{
	for (char x : title)
		if (isdigit(x))
			return false;
	return true;
}

bool Validator::validate_presenter(string presenter)
{
	for (char x : presenter)
		if (isdigit(x))
			return false;
	return true;

}

bool Validator::validate_duration(string duration)
{
	if (duration[2] != ':')
		return false;
	if (duration.length() > 5)
		return false;
	if (duration[0] > '5')
		return false;
	if (duration[3] > '5')
		return false;
	return true;
}

bool Validator::validate_likes(int likes)
{
	if (likes < 0)
		return false;
	return true;
}

bool Validator::validate_link(string link)
{
	if (link.find("www.") == std::string::npos)
		return false;
	return true;

}
