#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main ()
{
	srand(time(NULL));

	int x, y;
	bool xsign, ysign; // true if negative

	int arrX[100000];
	int arrY[100000];

	for(int i=0; i<100000; i++)
	{
		x = rand()%1000;
		y = rand()%1000;
		xsign = rand()%2;
		ysign = rand()%2;

		if(xsign) x *= -1;
		if(ysign) y *= -1;

		arrX[i] = x;
		arrY[i] = y;
	}

	for (int i=0;i<100000; i++)
		cout << arrX[i] << " " << arrY[i] << " ";


return 0;
}
