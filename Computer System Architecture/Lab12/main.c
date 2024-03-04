#include <stdio.h>
int findmaximum(int list_size, int list[]);
int main() {
	int list[20], list_size=0;
	printf("List size is:\n");
	scanf(" %d ", &list_size);
	for (int i = 0; i < list_size; i++) 
		{printf("Enter number:\n");
		scanf("%d", &list[i]);}
	FILE *f = fopen("data.txt", "w");
	fprintf(f, "The maximum is %x.", findmaximum(list_size, list));
	return 0;
	
}