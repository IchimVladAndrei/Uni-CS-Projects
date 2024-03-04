#pragma once
#include <string>
using namespace std;
class Tutorial {
private:
	string title;
	string presenter;
	string duration;
	
	int likes;
	string link;
	
public:
	Tutorial();
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="title"></param>
	/// <param name="presenter"></param>
	/// <param name="duration"></param>
	/// <param name="likes"></param>
	/// <param name="link"></param>
	Tutorial(string title,string presenter,string duration,int likes,string link);
	/// <summary>
	/// getter for likes
	/// </summary>
	/// <param name="likes"></param>
	void set_likes(int likes);
	/// <summary>
	/// getter for title
	/// </summary>
	/// <returns></returns>
	string get_title();
	/// <summary>
	/// getter for title
	/// </summary>
	/// <returns></returns>
	string get_presenter();
	/// <summary>
	/// getter for duration
	/// </summary>
	/// <returns></returns>
	string get_duration();
	/// <summary>
	/// getter for link
	/// </summary>
	/// <returns></returns>
	string get_link();
	/// <summary>
	/// gets likes
	/// </summary>
	/// <returns></returns>
	int get_likes();
};