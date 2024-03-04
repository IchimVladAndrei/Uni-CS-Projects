#pragma once
/// <summary>
/// This function validates the given parameter on its standard format for date DD/MM/YYYY
/// </summary>
/// <param name="date"></param>
/// <returns>1 for valid , 0 otherwise</returns>
int validate_date(char date[]);

/// <summary>
/// This function validates the given parameter on having at least 3 characters
/// </summary>
/// <param name="destination"></param>
/// <returns>1 for valid, 0 otherwise</returns>
int validate_destination(char destination[]);

/// <summary>
/// This function validates the given parameter on it being: city break,mountain or seaside
/// </summary>
/// <param name="type"></param>
/// <returns>1 for valid,0 otherwise</returns>
int validate_type(char type[]);

/// <summary>\
///	This function validates the given parameter on it being at least 1
/// </summary>/// <param name="price"></param>/// <returns>1 for valid,0 otherwise</returns>
int validate_price(int price);