#include <iostream>
using namespace std;

//struct that we will be using to store domino tiles
struct Domino {
	int back = 0;
	int front = 0;
};


Domino flip(const Domino& domino) {
	//flipping the domino
	//i use Domino since i dont want to change argument's original state
	Domino dom;
	dom.back = domino.front;
	dom.front = domino.back;
	return dom;
}
void add(Domino* route, int& size_route, const Domino& domino) {
	//adding the domino tile to the given route
	route[size_route] = domino;
	size_route++;
}

bool possibleNextMove(Domino* route, const int& size_route, const Domino& domino) {
	//checking wheter this domino tile can be added to the given route
	if (route[size_route-1].front == domino.back) {
		return true;
	}
	return false;
}

void clear(Domino* dominos, int& size) {
	//claering the whole domino route
	for (int i = 0; i < size; i++) {
		dominos[i].back = 0;
		dominos[i].front = 0;
	}
	size = 0;
}

void set(Domino* from, Domino* to, int& size_from ,const int& size_to) {
	//works like operator= for domino routes
	clear(from,size_from);
	for (int i = 0; i < size_to; i++) {
		from[i] = to[i];
		size_from++;
	}
}

//returning the size of the given domino route
int getSize(Domino* dominos,const int& numDominos) {
	int size = 0;
	for (int i = 0; i < numDominos; i++) {
		//if the next move is impossible then you get the whole size
		if (!possibleNextMove(dominos, i + 1, dominos[i+1])) {
			size = i+1;
			break;
		}
	}
	return size;
}

Domino* dominoAlgorith(const int& numDominos, Domino* dominos) {
	//the size of the 3 domino routes we will be using
	int size_longestRoute = 0, size_currentRoute=0, size_currentFlippedRoute=0;

	//here we will store the longest route
	Domino* longestRoute = new Domino[numDominos];
	if (longestRoute == nullptr) {
		cout << "Unsuccsessful operation";
		delete[] longestRoute;
		return nullptr;
	}
	//here we will store the current route
	Domino* currentRoute = new Domino[numDominos];
	if (currentRoute == nullptr) {
		cout << "Unsuccsessful operation";
		delete[] longestRoute;
		delete[] currentRoute;
		return nullptr;
	}
	//here we will store the current flipped route
	Domino* currentFlippedRoute = new Domino[numDominos];
	if (currentFlippedRoute == nullptr) {
		cout << "Unsuccsessful operation";
		delete[] longestRoute;
		delete[] currentRoute;
		delete[] currentFlippedRoute;
		return nullptr;
	}
	
	//starting the cycle with the inputted domino tile
	for (int i = 0; i < numDominos; i++) {

		//the currentRoute starts with the normal version of the given domino tile
		add(currentRoute, size_currentRoute, dominos[i]);

		//the currentFlippedRoute stars with the flipped side of the given domino tile
		add(currentFlippedRoute, size_currentFlippedRoute, flip(dominos[i]));

		//cycle to checks combinations with other inputted domino tiles and the given routes
		for (int j = 0; j < numDominos; j++) {
			//skipping element so there is no dublicate 
			if (j == i) {
				j++;
			}
			//checking can the normal domino tile be added to the route that starts with the normal version of the domino
			if (possibleNextMove(currentRoute, size_currentRoute, dominos[j])) {
				add(currentRoute, size_currentRoute, dominos[j]);
			}
			//checking can the flipped domino tile be added to the route that starts with the normal version of the domino
			else if (possibleNextMove(currentRoute, size_currentRoute, flip(dominos[j]))) {
				add(currentRoute, size_currentRoute, flip(dominos[j]));
			}

			//checking can the normal domino tile be added to the route that starts with the flipped version of the domino
			if  (possibleNextMove(currentFlippedRoute, size_currentFlippedRoute, dominos[j])) {
				add(currentFlippedRoute, size_currentFlippedRoute, dominos[j]);
			}

			//checking can the flipped domino tile be added to the route that starts with the flipped version of the dominp
			else if (possibleNextMove(currentFlippedRoute, size_currentFlippedRoute, flip(dominos[j]))) {
				add(currentFlippedRoute, size_currentFlippedRoute, flip(dominos[j]));
			}

			//comparint both the size of the currentRoute and currentFlippedRoute
			if (size_currentFlippedRoute > size_currentRoute) {
				//if the size of the currentFlpRoute is bigger than the longestRoute, the currentFlipRoute becomes the longestRoute
				if (size_currentFlippedRoute > size_longestRoute) {
					set(longestRoute, currentFlippedRoute, size_longestRoute, size_currentFlippedRoute);
				}
			}

			else if (size_currentRoute > size_currentFlippedRoute) {
				//if the size of the currentRoute is bigger than the longestRoute, the currentRoute becomes the longestRoute
				if (size_currentRoute > size_longestRoute) {
					set(longestRoute, currentRoute, size_longestRoute ,size_currentRoute);
				}
			}
			
			//if both of them are equal one of them becomes the longestRoute
			else if (size_currentFlippedRoute == size_currentRoute) {
				if (size_currentFlippedRoute > size_longestRoute) {
					set(longestRoute, currentFlippedRoute, size_longestRoute ,size_currentFlippedRoute);
				}
			}
		}
		//when we have done all the combinations of the start domino tile with the others we refresh the sequence
		//so we can make new combinations with other domino tiles for start
		clear(currentFlippedRoute, size_currentFlippedRoute);
		clear(currentRoute, size_currentRoute);
	}
	delete[] currentFlippedRoute;
	delete[] currentRoute;
	return longestRoute;
}

int main() {

	//numbers of domino tiles
	int numDominos = 0;
	if (!(cin >> numDominos)) {
		cout << "You are not allowed to enter symbol or you have entered to long number.";
		return -1;
	}

	//here we will be storing inputed domino tiles
	Domino* dominos = new Domino[numDominos];
	if (dominos == nullptr) {
		cout << "Unsuccsesfull allocation";
		delete[] dominos;
	}
	for (int i = 0; i < numDominos; i++) {
		if (!(cin >> dominos[i].back >> dominos[i].front)) {
			cout << "You are not allowed to enter symbols or you have entered to long numbers ";
			delete[] dominos;
			return -1 ;
		}
	}

	//pointer who points to an array of the longes domino route
    Domino* pDomino = dominoAlgorith(numDominos, dominos);
	if (pDomino == nullptr) {
		cout << "Unsuccsessful operation";
		delete[] dominos;
		return -1;
		
	}

	//getting the size of the longest chain
	int size = getSize(pDomino,numDominos);
	for (int i = 0; i < size; i++) {
		cout << pDomino[i].back << " " << pDomino[i].front << " ";
	}

	//deleting dynamically alocated memory
	delete[] pDomino;
	delete[] dominos;
	return 0;

}