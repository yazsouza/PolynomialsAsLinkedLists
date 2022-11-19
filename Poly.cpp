

#include "Poly.h"
#include <iostream>

Poly::Poly()
{

	//Creates a dummy header for the zero polynomial

	PolyNode* new_poly = new PolyNode(-1, 0, NULL);
	head = new_poly;

}

Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff)
{
	head = new PolyNode(-1, 0, NULL); //Sets head to a dummy variable
	PolyNode* Dummy = head;
	int length = coeff.size(); //Finds size of linked list

	for (int i = 0; i < length; i++) {//Increments through each elemnt

		PolyNode* new_poly = new PolyNode(deg[i], coeff[i], NULL); //Sets a new node to the values given at the same index

		Dummy->next = new_poly; //Places new node at end of list
		Dummy = Dummy->next; //Increments dummy to the new element to be modified

	}
}

Poly::~Poly()
{

	PolyNode* next_address = NULL;


	//Makes sure the list isn't initially empty
	if (head != NULL) {

		PolyNode* next_address = head->next;

	}
	else {
		return;
	}

	//Goes through each element of the linked list and deletes that whole object while saving 
	//the address of the next element to be deleted next
	while (next_address != NULL) {
		PolyNode* temp = next_address->next;
		delete next_address;
		next_address = temp;
	}

	head->next = NULL;



}

void Poly::addMono(int i, double c)
{
	if (c == 0)
		return; //if coeff is zero stay the same

	PolyNode* temp = head->next;
	PolyNode* prev = head;

	while (temp != NULL) {

		if (i == temp->deg) { // if degrees are equal, add terms
			temp->coeff += c;
			if (temp->coeff == 0) {//delete temp if coeff becomes 0
				prev->next = temp->next; //prev points to next term after temp
				delete temp;
			}
			return;
		}
		else if (i > temp->deg) { // if input degree is larger, make new node
			prev->next = new PolyNode(i, c, temp);
			return;
		}
		//incriment prev and temp
		prev = temp;
		temp = temp->next;
	}

	//make new end node
	prev->next = new PolyNode(i, c, NULL);
}

void Poly::addPoly(const Poly& p)
{
	PolyNode* temp = p.head->next;

	while (temp != NULL) { //iterate through p
		addMono(temp->deg, temp->coeff); //call addMono for each term in p
		temp = temp->next; //incriment temp
	}
}

void Poly::multiplyMono(int i, double c)
{
	PolyNode* temp = head->next;

	if (c == 0) {

		Poly::~Poly();

	}
	else {

		while (temp != NULL) {

			temp->deg = temp->deg + i;
			temp->coeff = temp->coeff * c;
			temp = temp->next;

		}

	}



}

void Poly::multiplyPoly(const Poly& p)
{

	PolyNode* temp = head->next;
	PolyNode* temp_p = p.head->next;

	Poly new_poly = Poly();

	while (temp != NULL) {

		temp_p = p.head->next;

		while (temp_p != NULL) {

			int degree = temp_p->deg + temp->deg;
			int coefficient = temp_p->coeff * temp->coeff;

			new_poly.addMono(degree, coefficient);

			temp_p = temp_p->next;

		}

		temp = temp->next;
	}


	head->next = new_poly.head->next;

}

void Poly::duplicate(Poly& outputPoly)
{
	PolyNode* temp = outputPoly.head;
	PolyNode* term = head;

	while (term->next != NULL) { //iterate through linked list
		temp->next = new PolyNode(term->next->deg, term->next->coeff, NULL); //add each item to new linked list
		temp = temp->next;
		term = term->next;
	}

}

int Poly::getDegree()
{

	if (head->next == NULL || head == NULL) {

		return -1;

	}
	else {

		return head->next->deg;

	}
}

int Poly::getTermsNo()
{
	PolyNode* next_address = head->next;

	int size = 0;

	while (next_address != NULL) {
		PolyNode* temp = next_address->next;

		size++;

		next_address = temp;
	}

	return size;
}

double Poly::evaluate(double x)
{
	double sum = 0;
	PolyNode* temp = head->next; //start after dummy head


	while (temp != NULL) {
		sum += pow(x, temp->deg) * (temp->coeff); //evaluate polynomial
		temp = temp->next; //iterate item on list
	}

	return sum;
}

std::string Poly::toString()
{

	std::string new_string = "";

	PolyNode* temp = head->next;

	while (temp != NULL) {

		char coefficient = temp->coeff + 48;

		new_string += (std::to_string(temp->coeff) + "X^");

		new_string += std::to_string(temp->deg);

		if (temp->next != NULL) {
			new_string += "+";
		}

		temp = temp->next;

	}

	return new_string;
}