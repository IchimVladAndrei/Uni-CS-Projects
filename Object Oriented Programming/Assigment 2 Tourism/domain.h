#pragma once
typedef struct {
	char type[30];
	char destination[50];
	char date[20];
	int price;
}Offer;
/// <summary>
/// This function creates a variable of type offer
/// </summary>
/// <param name="type"></param>
/// <param name="destination"></param>
/// <param name="date"></param>
/// <param name="price"></param>
/// <returns>The created offer</returns>
Offer create_offer(char type[], char destination[], char date[], int price);
/// <summary>
/// This function is a getter
/// </summary>
/// <param name="o"></param>
/// <returns>type of offer</returns>
char* get_type(Offer* o);
/// <summary>
/// This function is a getter
/// </summary>
/// <param name="o"></param>
/// <returns>destination of offer</returns>
char* get_destination(Offer* o);
/// <summary>
/// This function is a getter
/// </summary>
/// <param name="o"></param>
/// <returns>date of offer</returns>
char* get_date(Offer* o);
/// <summary>
/// This function is a getter
/// </summary>
/// <param name="o"></param>
/// <returns>price of offer</returns>
int get_price(Offer* o);
/// <summary>
/// This function assigns new values to another offer.
/// </summary>
/// <param name="new_offer">The new  offer</param>
/// <param name="offer">The older offer</param>
void new_values(Offer* new_offer, Offer offer);
