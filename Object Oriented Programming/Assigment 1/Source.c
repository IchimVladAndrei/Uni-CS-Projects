#include <stdio.h>

//9.Decompose a given natural number in its prime factors.
//Given a vector of numbers, find the longest contiguous subsequence such that any consecutive elements contain the same digits.

/// <summary>
/// This function decomposes a natural number in its prime factors and transfers them into an array.
/// </summary>
/// <param name="a"> An integer, greater than 0</param>
/// <param name="temp">The array where on position i, the prime factor is and position i+1 its power is.</param>
/// <param name="finish">A pointer</param>
void prime_fact(int a,int temp[],int *finish) {
	int d = 2, p,i=0;
	while (a > 1) {
		p = 0;
		while (a % d == 0) {
			++p;
			a /= d;

		}
		if (p) {
			temp[i++] = d;
			temp[i++] = p;
			*finish = i;
		}
			
		d++;
		if (a > 1 && d * d > a)
			d = a;
	}
	
}
/// <summary>
/// This function prints the result of the first problem.
/// </summary>
/// <param name="temp">An array</param>
/// <param name="stop">Last position to be read</param>
void print_powers(int temp[], int stop) {
	for (int i = 0; i < stop; i += 2)
		printf("%d to the power %d\n", temp[i], temp[i + 1]);
}
/// <summary>
/// This function reads an array.
/// </summary>
/// <param name="size"></param>
/// <param name="temp"></param>
void read_vector(int size, int temp[]) {
	for (int i = 0; i < size; i++)
		scanf("%d", &temp[i]);
}
/// <summary>
/// This verifies the condition given in the second problem. 
/// It uses two frequency arrays, for each neighbours numbers in the given array.
/// </summary>
/// <param name="a">Number found in position i</param>
/// <param name="b">Number found in posititon i+1</param>
/// <returns>1,if the condition is achieved,0 otherwise</returns>
int verified(int a, int b) {
	int digit_a[10] = { 0 }, digit_b[10] = { 0 };
	while (a) {
		digit_a[a % 10]++;
		a /= 10;
	}
	while (b) {
		digit_b[b % 10]++;
		b /= 10;
	}
	for (int i = 0; i <= 9; i++)
		if (digit_a[i] != digit_b[i])
			return 0;
	return 1;
}
/// <summary>
/// This function solves the second problem. 
/// It always compares the currenct subsequence to a max size and updates correspondigly.
/// </summary>
/// <param name="len_vector">The size of the array</param>
/// <param name="temp">Integer array</param>
/// <param name="fstart">A pointer for starting position</param>
/// <param name="fstop">A pointer for the end position</param>
void secventa(int len_vector, int temp[], int* fstart, int* fstop) {
	int start = 0, end = 0, size = 1, max_size = -1, mend = -1, mstart = 0;
	for (int i = 0; i < len_vector - 1; i++)
		if (verified(temp[i], temp[i + 1])) {///return 1 daca respecta cerinta
			size++;
			if (size > max_size) {
				max_size = size;
				end = i + 1;
				mstart = start;
				mend = end;
			}
		}
		else { start = i + 1, end = i + 1; size = 1; }
	*fstart = mstart, *fstop = mend;
	
	//de testat alte cazuri
};
/// <summary>
/// This function prints the result of the second problem, only by printing values in the maximum subsequence.
/// </summary>
/// <param name="temp">Integer array</param>
/// <param name="fstart">Integer, starting position</param>
/// <param name="fstop">Integer, end position</param>
void print_vector(int temp[], int fstart, int fstop) {
	for (int i = fstart; i <=fstop; i++)
		printf("%d ", temp[i]);
	printf("\n");
}
/// <summary>
/// This function enables the user to select an option to solve certain problems.
/// </summary>
void menu() {
	int choice = -1, numbers[100], ssize = 0;

	while (choice != 4) {
		printf("What you want to do:\n");

		printf("1.First problem\n2.Second problem\n3.Read an array\n4.Exit\n");
		scanf("%d", &choice);
		switch (choice) {
		case 1: {
			int number,powers[30],stop;
			printf("What number to read?\n");
			scanf("%d", &number);
			prime_fact(number,powers,&stop);
			print_powers(powers, stop);
			printf("\n");
			break; }
		case 2: {
			int start, stop;
			secventa(ssize, numbers, &start, &stop);
			print_vector(numbers,start, stop);
			break;
		}
		case 3: {
			printf("How many numbers you want to read? not greater than 100 though :))\n");
			scanf("%d", &ssize);
			read_vector(ssize, numbers);
			break;
		}
		case 4:
			printf("\nApplication closing\n");
			break;
		default:
			printf("Hey hey not an option!!");
			break;
		}

	}
}

int main() {
	menu();
	return 0;
}