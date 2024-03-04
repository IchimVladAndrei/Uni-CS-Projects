#include <stdio.h>
int permutare(int a);
int main()
{
	int nr=0;
	printf("Number is: ");
	scanf("%x", &nr);
	for (int i = 1; i <= 8; i++)
	{
		
		printf("Permutarea este %x\n", nr);
		nr = permutare(nr);
		

	}
	return 0;
}