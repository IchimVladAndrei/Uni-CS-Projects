#pragma once
#include <cstdlib>
#include <string>
#include "domain.h"

class Validator {
public:

	/// <summary>
	/// validates the title based on it being only letters
	/// </summary>
	/// <param name="title"></param>
	/// <returns></returns>
	bool validate_title(string title);
	/// <summary>
	/// validates the presenter based on it being only letters
	/// </summary>
	/// <param name="presenter"></param>
	/// <returns></returns>
	bool validate_presenter(string presenter);
	/// <summary>
	/// validates the duration based on it being of form "mm:ss"
	/// </summary>
	/// <param name="duration"></param>
	/// <returns></returns>
	bool validate_duration(string duration);
	/// <summary>
	/// validates the likes it being a positive number
	/// </summary>
	/// <param name="likes"></param>
	/// <returns></returns>
	bool validate_likes(int likes);
	/// <summary>
	/// validates the link on it having at least a www. form
	/// </summary>
	/// <param name="link"></param>
	/// <returns></returns>
	bool validate_link(string link);

};