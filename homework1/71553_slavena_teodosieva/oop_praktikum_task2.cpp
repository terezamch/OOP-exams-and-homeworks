#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;
class Date
{
    int month,
        day,
        year;
public:
    Date(int day = 1, int month = 1, int year = 2000)
    {
        this->day = day;
        this->month = month;
        this->year = year;
    }
    /*
    Date(const Date& other)
    {
        month = other.month;
        day = other.day;
        year = other.year;
    }
    Date& operator=(const Date& other)
    {
        if(this != &other)
        {
            month = other.month;
            day = other.day;
            year = other.year;
        }
        return *this;
    }
    */
    void printDate() const
    {
        cout<<day<<"."<<month<<"."<<year<<endl;
    }
    void setMonth(int m)
    {
        if (m >= 1 && m <= 12)
        {
            month = m;
        }
        else
            cout<<"Nevaliden mesec"<<endl;
    }
    void setDay(int d)
    {
        if (d >= 1 && d <= 31)
        {
            day = d;
        }
        else
            cout<<"Nevaliden den"<<endl;
    }
    void setYear(int y)
    {
        if(y >= 0)
            year = y;
        else
            cout<<"Nevalidna godina"<<endl;
    }
    int getMonth() const
    {
        return month;
    }
    int getDay() const
    {
        return day;
    }
    int getYear() const
    {
        return year;
    }
    bool operator<(Date d)
    {
        if(this->getMonth() == d.getMonth())
        {
            if(this->getDay() < d.getDay())
                return true;
            else
                return false;
        }
        else if(this->getMonth() < d.getMonth())
            return true;
        return false;
    }
    bool operator>(Date d)
    {
        if(this->getMonth() == d.getMonth())
        {
            if(this->getDay() > d.getDay())
                return true;
            else
                return false;
        }
        else if(this->getMonth() > d.getMonth())
            return true;
        return false;
    }
};
struct Card
{
    char* lastName;
    Date dateOfBirth;

    Card(char* lastName = "Ivanov", int d = 1, int m = 1, int y = 2000) : dateOfBirth(d,m,y)
    {
        this->lastName = new char[strlen(lastName)+1];
        assert(this->lastName != NULL);
        strcpy(this->lastName, lastName);
        //dateOfBirth.setDay(d);
        //dateOfBirth.setMonth(m);
        //dateOfBirth.setYear(y);
    }
    Card(const Card& other)
    {
        lastName = new char[strlen(other.lastName)+1];
        assert(lastName != NULL);
        strcpy(lastName, other.lastName);
        dateOfBirth = Date(other.dateOfBirth.getDay(), other.dateOfBirth.getMonth(), other.dateOfBirth.getYear());
    }
    Card& operator=(const Card& other)
    {
        if(this != &other)
        {
            delete [] lastName;
            lastName = new char[strlen(other.lastName)+1];
            assert(lastName != NULL);
            strcpy(lastName, other.lastName);
            dateOfBirth.setDay(other.dateOfBirth.getDay());
            dateOfBirth.setMonth(other.dateOfBirth.getMonth());
            dateOfBirth.setYear(other.dateOfBirth.getYear());
        }
        return *this;
    }
    ~Card()
    {
        delete [] lastName;
    }
    char* getLastName() const
    {
       return lastName;
    }
    Date getDateOfBirth() const
    {
        return dateOfBirth;
    }
    void printCard() const
    {
        cout<<"Last Name: "<<lastName<<endl;
        dateOfBirth.printDate();
        //cout<<endl;
    }
};

struct Zodiac
{
    char name[9];
    Date beginning;
    Date ending;
public:
    Zodiac(char* name = "oven", int d1 = 21, int m1 = 3, int y1 = 0, int d2 = 20, int m2 = 4, int y2 = 0) : beginning(d1,m1,y1), ending(d2,m2,y2)
    {
        strcpy(this->name, name);
        //beginning.setDay(d1);
        //beginning.setMonth(m1);
        //beginning.setYear(y1);
        //ending.setDay(d2);
        //ending.setMonth(m2);
        //ending.setYear(y2);
    }
    Date getBeginning() const
    {
        return beginning;
    }
    Date getEnding() const
    {
        return ending;
    }
    void print()
    {
        cout<<"Zodiac Sign: "<<name<<"("<<beginning.getDay()<<"."<<beginning.getMonth()<<" - "
            <<ending.getDay()<<"."<<ending.getMonth()<<")"<<endl;
        //beginning.printDate();
        //cout<<" ";
        //ending.printDate();
        //cout<<endl;
    }
};
class ListPerson
{
   Card* cards;
   int size;
   int capacity;
public:
   ListPerson(int size = 0, int capacity = 2)
   {
       this->size = size;
       this->capacity = capacity;
       cards = new Card [capacity];
       assert(cards!=NULL);
   }
   ListPerson(const ListPerson& other)
   {
       size = other.size;
       capacity = other.capacity;
       cards = new Card [other.capacity];
       assert(cards != NULL);
       for(int i=0; i<size; i++)
       {
           cards[i] = other.cards[i];
       }
   }
   ~ListPerson()
   {
       delete [] cards;
   }
   ListPerson& operator=(const ListPerson& other)
   {
       if(this != &other)
       {
           delete [] cards;
           size = other.size;
           capacity = other.capacity;
           cards = new Card[capacity];
           assert(cards != NULL);
           for(int i=0; i<size; i++)
           {
              cards[i] = other.cards[i];
           }
       }
       return *this;
   }
   void setSize(int _size)
   {
       if(_size > 0)
        size = _size;
       else
        cout<<"Nevaliden razmer"<<endl;
   }
   int getSize() const
   {
       return size;
   }
   void setCapacity(int _capacity)
   {
       if(_capacity > 0)
        capacity = _capacity;
       else
        cout<<"Nevaliden kapacitet"<<endl;
   }
   int getCapacity() const
   {
       return capacity;
   }
   void deleteCard(char* _lastName)
   {
       if(capacity > size*2)
       {
           capacity /= 2;
           Card* temp = new Card[capacity];
           for(int i = 0; i<size; i++)
                temp[i] = cards[i];
           delete [] cards;
           cards = new Card[capacity];
           for(int i = 0; i<size; i++)
                cards[i] = temp[i];
           delete [] temp;
       }
       for(int i=0; i<size; i++)
       {
           if(!strcmp(cards[i].getLastName(), _lastName))
            {
                for(int j=i+1; j<size; j++)
                    cards[j-1] = cards[j];
                size--;
                break;
            }
       }
   }
   void addCard(Card c)
   {
       if(size == capacity)
       {
           Card* tmp = new Card[size];
           assert(tmp != NULL);
           for(int i=0; i<size; i++)
           {
               tmp[i] = cards[i];
           }
           delete [] cards;
           capacity *= 2;
           cards = new Card[capacity];
           for(int i=0; i<size; i++)
           {
               cards[i] = tmp[i];
           }
           delete [] tmp;
       }
       cards[size] = c;
       size++;
   }
   Card getCard(const char* _lastName) const
   {
       for(int i=0; i<size; i++)
       {
           if(!strcmp(cards[i].getLastName(),_lastName))
            return cards[i];
       }
   }
   //obedinenie
   ListPerson operator+(const ListPerson& other)
   {
       ListPerson temp;
       temp.setSize(size + other.size);
       temp.setCapacity(capacity + other.capacity);
       temp.cards = new Card[temp.capacity]; // Card[temp.getCapacity()]
       assert(temp.cards != NULL);
       for(int i = 0; i < size; i++)
       {
           temp.cards[i] = cards[i];
       }
       for(int i=size;i<(size + other.size);i++)
       {
           int j = 0;
           temp.cards[i] = other.cards[j];
           j++;
       }
       return temp;
   }
   //sechenie
   ListPerson operator*(const ListPerson& other)
   {
       int _size = 0, _capacity = 0;
       if(size < other.size)
       {
           _size = size;
           _capacity = capacity;
       }
       else
       {
           _size = other.size;
           _capacity = other.capacity;
       }
       ListPerson temp;
       temp.setSize(_size);
       temp.setCapacity(_capacity);
       temp.cards = new Card[temp.capacity];
       assert(temp.cards != NULL);
       for(int i=0; i<size; i++)
       {
           for(int j=0; j<other.size; j++)
           {
               if(!(strcmp(cards[i].getLastName(), other.cards[j].getLastName())))
               {
                   int k=0;
                   temp.cards[k] = cards[i];
                   k++;
                   break;
               }
           }
       }
       return temp;
   }
   //razlika
   ListPerson operator-(const ListPerson& other)
   {
       ListPerson temp;
       temp.setSize(size + other.size);
       temp.setCapacity(capacity + other.capacity);
       temp.cards = new Card[temp.capacity];
       assert(temp.cards != NULL);
       for(int i=0; i<size; i++)
       {
           temp.cards[i] = cards[i];
       }
       delete [] cards;
       for(int i=0; i<size; i++)
       {
           for(int j=0; j<other.size; j++)
           {
               if(!strcmp(temp.cards[i].getLastName(), other.cards[j].getLastName()))
                deleteCard(other.cards[i].getLastName());
           }
       }
       for(int i=size; i<size + other.size; i++)
       {
           int j=0;
           temp.cards[i] = other.cards[j];
           j++;
       }
       return temp;
   }
   Zodiac getZodiacalSign(char* name)
   {
       Zodiac zodiacSigns[12];
       zodiacSigns[0] = Zodiac ("Oven", 21, 3, 0, 20, 4, 0);
       zodiacSigns[1] = Zodiac ("Telec", 21, 4, 0, 21, 5, 0);
       zodiacSigns[2] = Zodiac ("Bliznaci", 22, 5, 0, 21, 6, 0);
       zodiacSigns[3] = Zodiac ("Rak", 22, 6, 0, 22, 7, 0);
       zodiacSigns[4] = Zodiac ("Lyv", 23, 7, 0, 23, 8, 0);
       zodiacSigns[5] = Zodiac ("Deva", 24, 8, 0, 23, 9 ,0);
       zodiacSigns[6] = Zodiac ("Vezni", 24, 9, 0, 23, 10, 0);
       zodiacSigns[7] = Zodiac ("Skorpion", 24, 10, 0, 22, 11, 0);
       zodiacSigns[8] = Zodiac ("Strelec", 23, 11, 0, 21, 12, 0);
       zodiacSigns[9] = Zodiac ("Kozirog", 22, 12, 0, 20, 1, 0);
       zodiacSigns[10] = Zodiac ("Vodolei", 21, 1, 0, 19, 2, 0);
       zodiacSigns[11] = Zodiac ("Ribi", 20, 2, 0, 20, 3, 0);
       for(int i=0; i<size; i++)
       {
           if(!strcmp(cards[i].getLastName(), name))
           {
               for(int j = 0; j<12; j++)
               {
                   //if((cards[i].dateOfBirth.getMonth() == zodiacSigns[j].beginning.getMonth() || cards[i].dateOfBirth.getMonth() == zodiacSigns[j].ending.getMonth())
                       //&& (zodiacSigns[j].beginning.getDay() <= cards[i].dateOfBirth.getDay() && cards[i].dateOfBirth.getDay() <= zodiacSigns[j].ending.getDay()))
                    if(cards[i].getDateOfBirth() > zodiacSigns[j].getBeginning() && cards[i].getDateOfBirth() < zodiacSigns[j].getEnding())
                       return zodiacSigns[j];
               }
           }
       }
   }
   void printListPerson() const
   {
       cout<<"Size: "<<size<<" "<<"Capacity: "<<capacity<<endl;
       for(int i=0; i<size; i++)
       {
           getCard(cards[i].getLastName()).printCard();
           cout<<endl;
       }
   }
};
int main()
{
    Date data1;
    Date data2(24,2,1996);
    Date data3(3,4,1968);
    data1.printDate();
    data2.printDate();
    cout<<data1.getDay()<<" ";
    cout<<data2.getMonth()<<" ";
    cout<<data3.getYear()<<endl;
    data1.setDay(23);
    data1.setMonth(5);
    data1.setYear(1997);
    data1.printDate();
    if(data2<data3)
     cout<<"Da"<<endl;
     else cout<<"Ne"<<endl;
    cout<<"***************"<<endl;
    Card c1;
    c1.printCard();
    Card c2("Slavena", 24, 2, 1996);
    c2.printCard();
    //cout<<c2.getLastName()<<endl;
    //Card c3 = c2;
    //c3.printCard();
    Card c4("Teodosieva", 27, 8, 1992);
    //c4 = c2;
    c4.printCard();
    Card c5("Nakova", 13, 7, 1995);
    c5.printCard();
    Card c6("Champoeva", 15, 12, 1995);
    c6.printCard();
    cout<<"*****************"<<endl;
    ListPerson lp1;
    lp1.printListPerson();
    ListPerson lp2(0,5);
    lp2.printListPerson();
    //ListPerson lp3 = lp2;
    //lp3.printListPerson();
    //ListPerson lp4;
    //lp4 = lp2;
    //lp4.printListPerson();
    lp1.addCard(c2);
    lp1.printListPerson();
    lp1.getZodiacalSign(c2.getLastName()).print();
    //lp1.addCard(c4);
    //lp1.printListPerson();
    //lp1.addCard(c5);
    //lp1.printListPerson();
}
