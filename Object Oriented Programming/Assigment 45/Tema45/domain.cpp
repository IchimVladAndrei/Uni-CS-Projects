#include "domain.h"
#include <cstring>
#pragma once

Tutorial::Tutorial()
{
}

Tutorial::Tutorial(string title, string presenter, string duration, int likes, string link):
	title{ title }, presenter{ presenter }, duration{ duration }, likes{ likes }, link{ link }
{
}

void Tutorial::set_likes(int likes)
{
	this->likes = likes;
}

string Tutorial::get_title()
{

	return this->title;
}

string Tutorial::get_presenter()
{
	return this->presenter;
}

string Tutorial::get_duration()
{
	return this->duration;
}

string Tutorial::get_link()
{
	return this->link;
}

int Tutorial::get_likes()
{
	return this->likes;
}
