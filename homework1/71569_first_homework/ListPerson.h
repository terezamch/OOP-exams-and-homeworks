#ifndef LISTPERSON_H
#define LISTPERSON_H
#include "Card.h"


class ListPerson
{

public:
	ListPerson();
	ListPerson(size_t, size_t);
	ListPerson(const ListPerson&);
	~ListPerson();

	ListPerson& operator=(const ListPerson&);
	void addCard(Card); 
	void removeCard(const char*);	
	int findCard(const char*) const;
	Card& getCard(const char*) const;
	void copyCards(const ListPerson&);
	ListPerson& operator+=(const ListPerson&);
	ListPerson similarity(const ListPerson&) const;
	ListPerson difference(const ListPerson&) const;
	
	const char* getSign(const char*) const;
	
	void print() const;

private:
	Card* library;

	size_t size;
	size_t MAX_CAPACITY;
	


};




#endif
