#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <cstring>
#include "date.cpp"

using namespace std;


struct Card{
	
	char familyName[30];
	Date birthDate;
	char Sign[15];

	Card& operator=(const Card& other)
	{	
	
	   	size_t len = strlen(other.familyName) +1;
		strcpy_s(familyName,len, other.familyName);

		birthDate = other.birthDate;
		
		assignSign();
		
		return *this;
	};

	void assignSign() 
	{
		unsigned day = birthDate.getDay();
		unsigned month = birthDate.getMonth();


		switch(month)
		{
			case 1: if(day >= 21) strcpy(Sign, "Aquarius");
					else strcpy(Sign, "Capricorn");break;
		 
			case 2: if(day >= 20) strcpy(Sign, "Pisces");
					else strcpy(Sign,  "Aquarius");break;

			case 3: if(day >= 20) strcpy(Sign, "Aries");
					else strcpy(Sign, "Pisces");break;

			case 4: if(day >= 21) strcpy(Sign,"Taurus");
					else strcpy(Sign, "Aries");break;

			case 5: if(day >= 22) strcpy(Sign, "Gemini");
					else strcpy(Sign,"Taurus");break;
			
			case 6: if(day >= 22) strcpy(Sign, "Cancer");
					else strcpy(Sign, "Gemini");break;

			case 7: if(day >= 23) strcpy(Sign, "Leo");
					else strcpy(Sign, "Cancer");break;
 
			case 8: if(day >= 23) strcpy(Sign,"Virgo");
					else strcpy(Sign,"Leo");break;

			case 9: if(day >= 24) strcpy(Sign, "Libra");
					else strcpy(Sign,"Virgo");break;

			case 10: if(day >= 24) strcpy(Sign, "Scorpio");
					else strcpy(Sign, "Libra");break;

			case 11: if(day >= 23) strcpy(Sign, "Sagittarius");
					else strcpy(Sign, "Scorpio");break;

			case 12: if(day >= 22) strcpy(Sign, "Capricorn");
					else strcpy(Sign, "Sagittarius");break;


		};
	};
	
	void printCard()
    	{
        	cout << "Name : " <<familyName <<  endl;
       		birthDate.print();
	        cout << "Sign :" <<Sign << endl;
        
   	 };	 

	
};



#endif
