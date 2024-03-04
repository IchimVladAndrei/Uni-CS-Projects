#include "domain.h"
#pragma once
#include <stdio.h>
#include <string.h>

Offer create_offer(char type[], char destination[], char date[], int price)
{
	Offer o;
	strcpy(o.type, type);
	strcpy(o.destination, destination);
	strcpy(o.date, date);
	o.price = price;
	return o;
}

char* get_type(Offer* o)
{
	return o->type;
}

char* get_destination(Offer* o)
{
	return o->destination;
}

char* get_date(Offer* o)
{
	return o->date;
}

int get_price(Offer* o)
{
	return o->price;

}

void new_values(Offer* new_offer, Offer offer)
{
	strcpy(new_offer->type, offer.type);
	strcpy(new_offer->destination, offer.destination);
	strcpy(new_offer->date, offer.date);
	new_offer->price = offer.price;
}
