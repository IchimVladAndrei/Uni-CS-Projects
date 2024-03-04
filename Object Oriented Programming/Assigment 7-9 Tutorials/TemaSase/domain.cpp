#include "domain.h"
#include <cstring>
#include <iostream>
#pragma once
using namespace std;
Tutorial::Tutorial()
{}

Tutorial::Tutorial(string title, string presenter, string duration, int likes, string link) :
	title{ title }, presenter{ presenter }, duration{ duration }, likes{ likes }, link{ link }
{
}

void Tutorial::set_likes(int likes)
{
	this->likes = likes;
}

const string& Tutorial::get_title()
{

	return this->title;
}

const string& Tutorial::get_presenter()
{
	return this->presenter;
}

const string& Tutorial::get_duration()
{
	return this->duration;
}

const string& Tutorial::get_link()
{
	return this->link;
}

const int& Tutorial::get_likes()
{
	return this->likes;
}

ostream& operator<<(ostream& output, const Tutorial& t)
{
	output << t.title << " " << t.presenter << " " << t.duration << " " << t.likes << " " << t.link;
	return output;
}

istream& operator>>(istream& input, Tutorial& t)
{
	input >> t.title >> t.presenter >> t.duration >> t.likes >> t.link;
	return input;
}
