#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "console.h"
#include "repo.h"
#include "dynamic.h"
#include "service.h"
#include "reundo.h"
#include "valid.h"

void test_add() {
	Offer a = create_offer("Seaside", "Argentina", "10/10/1999", 123);
	DynamicArray* b = createDA(10);
	add_TElem(b, a);
	assert(strcmp(b->data[0].type, "Seaside")==0);
	assert(strcmp(b->data[0].destination, "Argentina") == 0);
	assert(strcmp(b->data[0].date, "10/10/1999") == 0);
	assert(b->data[0].price == 123);
	destroy(b);
}

void test_delete() {
	Offer a = create_offer("Seaside", "Argentina", "10/10/1999", 123);
	Offer c = create_offer("Mountain", "Chile", "25/12/2000", 234);
	DynamicArray* b = createDA(10);
	add_TElem(b, a);
	add_TElem(b, c);

	assert(strcmp(b->data[0].type, "Seaside") == 0);
	assert(strcmp(b->data[0].destination, "Argentina") == 0);
	assert(strcmp(b->data[0].date, "10/10/1999") == 0);
	assert(b->data[0].price == 123);
	delete_TElem(b, 0);
	assert(strcmp(b->data[0].type, "Mountain") == 0);
	assert(strcmp(b->data[0].destination, "Chile") == 0);
	assert(strcmp(b->data[0].date, "25/12/2000") == 0);
	assert(b->data[0].price == 234);
	destroy(b);
}

void test_update() {

	Offer a = create_offer("Seaside", "Argentina", "10/10/1999", 123);
	Offer c = create_offer("Mountain", "Chile", "25/12/2000", 234);
	DynamicArray* b = createDA(10);
	add_TElem(b, a);
	add_TElem(b, c);

	assert(strcmp(b->data[0].type, "Seaside") == 0);
	assert(strcmp(b->data[0].destination, "Argentina") == 0);
	assert(strcmp(b->data[0].date, "10/10/1999") == 0);
	assert(b->data[0].price == 123);
	update_TElem(b, c, 0);
	assert(strcmp(b->data[0].type, "Mountain") == 0);
	assert(strcmp(b->data[0].destination, "Chile") == 0);
	assert(strcmp(b->data[0].date, "25/12/2000") == 0);
	assert(b->data[0].price == 234);
	destroy(b);
}

void test_add_repo() {
	DynamicArray* a = createDA(12);
	Repos* r = createRepos(*a);
	init_repo(r);
	add_offer_r(r, "City break", "Uganda", "04/04/1990", 45);
	assert(strcmp(r->array.data[10].type, "City break") == 0);
	assert(strcmp(r->array.data[10].destination, "Uganda") == 0);
	assert(strcmp(r->array.data[10].date, "04/04/1990") == 0);
	assert(r->array.data[10].price == 45);
	destroy(a);
}

void test_add_service() {

	DynamicArray* a = createDA(12);
	Repos* r = createRepos(*a);
	init_repo(r);
	UndoRedo* undoredo = createUndoRepo(20, r);
	Service* service = create_service(*r, *undoredo);

	add_offer_r(r, "City break", "Uganda", "04/04/1990", 45);
	assert(strcmp(r->array.data[10].type, "City break") == 0);
	assert(strcmp(r->array.data[10].destination, "Uganda") == 0);
	assert(strcmp(r->array.data[10].date, "04/04/1990") == 0);
	assert(r->array.data[10].price == 45);
	destroy_s(service);
	destroy_reundo(undoredo);
	destroy(a);
}

void test_valid_type() {
	char t1[100] = "";
	assert(validate_type(t1) == 0);
	char t2[100] = "gibberish";
	assert(validate_type(t2) == 0);
	char t3[100] = "Mountain";
	assert(validate_type(t3) == 1);

}

void test_valid_destination() {
	char d1[100] = "a";
	char d2[100] = "USA";
	assert(validate_destination(d1) == 0);
	assert(validate_destination(d2) == 1);
}

void test_valid_date() {
	char d1[100] = "21 mar 1990", d2[100] = "21.03.2005", d3[100] = "21/03/2005";
	assert(validate_date(d1) ==0 );
	assert(validate_date(d2) == 0);
	assert(validate_date(d3) == 1);
}

void test_valid_price() {
	int p1=0, p2=-1, p3=300;
	assert(validate_price(p1) == 0);
	assert(validate_price(p2) == 0);
	assert(validate_price(p3) == 1);
}
void test_ALL() {
	test_add();
	test_delete();
	test_update();
	test_add_repo();
	test_add_service();
	test_valid_date();
	test_valid_destination();
	test_valid_price();
	test_valid_type();
}