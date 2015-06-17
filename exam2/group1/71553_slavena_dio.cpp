// abstrakciq, enkapsulaciq, polimorfizym, nasledqvane
#include <iostream>
#include <cassert>
#include <cstring>
#include <cmath>
using namespace std;
class Musical_Skill
{
    char* name;
    int skill;
public:
    Musical_Skill(char* name = "piano", int skill = 1)
    {
        this->name = new char[strlen(name)+1];
        assert(this->name != NULL);
        strcpy(this->name, name);

        this->skill = skill;
    }
    Musical_Skill(const Musical_Skill& other)
    {
        this->name = new char[strlen(other.name)+1];
        assert(this->name != NULL);
        strcpy(this->name, other.name);

        this->skill = other.skill;
    }
    virtual ~Musical_Skill()
    {
        delete [] name;
    }
    Musical_Skill& operator=(const Musical_Skill& other)
    {
        if(this != &other)
        {
            delete [] name;
            this->name = new char[strlen(other.name)+1];
            assert(this->name != NULL);
            strcpy(this->name, other.name);

            this->skill = other.skill;
        }
        return *this;
    }
    char* getName() const
    {
        return name;
    }
    int getSkill() const
    {
        return skill;
    }
    void print()
    {
        cout<< "Name: " << name << endl;
        cout<< "Skill: " << skill << endl;
    }

};
class Musician
{
   protected: char* name;
    int beauty;
    int porok;
    Musical_Skill m[5];
    int size;
public:
    Musician(char* name = "musician", int beauty = 1, int porok = 1, int size = 0)
    {
        this->name = new char[strlen(name)+1];
        assert(this->name != NULL);
        strcpy(this->name, name);
        this->beauty = beauty;
        this->porok = porok;
        this->size = size;
    }
    Musician(const Musician& other)
    {
        this->name = new char[strlen(other.name)+1];
        assert(this->name != NULL);
        strcpy(this->name, other.name);
        this->beauty = other.beauty;
        this->porok = other.porok;
        size = other.size;
        for(int i = 0; i < size; i++)
            m[i] = other.m[i];
    }
    ~Musician()
    {
        delete [] name;
    }
    Musician& operator=(const Musician& other)
    {
        if(this != &other)
        {
            delete [] name;
            this->name = new char[strlen(other.name)+1];
            assert(this->name != NULL);
            strcpy(this->name, other.name);
            this->beauty = other.beauty;
            this->porok = other.porok;
            size = other.size;
            for(int i = 0; i < size; i++)
                m[i] = other.m[i];
        }
        return *this;
    }
    bool moreThanHundred ()
    {
        for(int i = 0; i < size; i ++)
            if(m[i].getMusicalSkill > 100)
            return true;
        return false;
    }
    bool lessThanTen()
    {
        for(int i = 0; i < size; i++)
            if(m[i].getMusicalSkill < 10)
            return true;
        return false;
    }
    bool addMusicalSkill(Musical_Skill m)
    {
        if(size < 5)
        {
            m[size] = m;
            size++;
            return true;
        }
        else return false;
    }
    bool removeMusicalSkill(char* name)
    {
        for(int i = 0; i < size; i++)
        {
            if(!strcmp(m[i].getName(), name))
            {
                for(int j = i+1; j < size; j++)
                    m[j-1] = m[j];
                size--;
            }
            return true;
        }
        return false;
    }
    void sortMS()
    {
        //int index = i;
        for(int i = size - 1; i > 1; i--)
        {
            if(m[i].getSkill() > m[i-1].getSkill())
                swap(m[i], m[i-1]);
        }
    }
    int sumMS()
    {
        int sum = 0;
        for(int i = 0; i < size; i++)
            sum += m[i].getSkill();
    }
    virtual char* getName() const
    {
        return name;
    }
    virtual void setName(char* n)
    {
        delete [] name;
        name = new char[strlen(n)+1];
        assert(name != NULL);
        strcpy(name, n);
    }
    virtual int getBeauty() const = 0;
    virtual int getPorok() const = 0;
    virtual char* getType() const = 0;
    virtual void getBestMS(int n)
    {
        sortMS();
        for(int i = 0; i < n; i++)
            m[i].print();
    }
    //virtual char** getBest() const = 0;
};
class RockMusician : virtual public Musician
{
public:
    virtual int getBeauty() const
    {
        return beauty*beauty + sumMS() - porok*3*3.14;
    }
    virtual int getPorok() const
    {
        return porok;
    }
    virtual char* getType() const
    {
        return "rock";
    }
    RockMusician(char* name = "musician", int beauty = 1, int porok = 1) : Musician(name, beauty, porok)
    {

    }
    RockMusician(const RockMusician& other) : Musician(other)
    {

    }
    ~RockMusician()
    {

    }
    RockMusician& operator=(const RockMusician& other)
    {
        if(this != &other)
        {
            Musician :: operator=(other);
        }
        return *this;
    }
};
class FolkMusician : virtual public Musician
{
    bool rasa;
public:
    FolkMusician(char* name = "musician", int beauty = 1, int porok = 1, bool rasa = true) : Musician(name, beauty, porok)
    {
        this->rasa = rasa;
    }
    FolkMusician(const FolkMusician& other) : Musician(other)
    {
        rasa = other.rasa;
    }
    ~FolkMusician()
    {

    }
    FolkMusician& operator=(const FolkMusician& other)
    {
        if(this != & other)
        {
            Musician :: operator=(other);
            rasa = other.rasa;
        }
        return *this;
    }
    virtual int getBeauty() const
    {
        return pow(beauty, 5) + porok + rasa*cos; //cos??
    }
    virtual int getPorok() const
    {
        return porok;
    }
    virtual char* getType() const
    {
        return "rock_tack";
    }
};
class Band
{
    char* bandName;
    Musician* musicians[10];
    int size;
public:
    virtual void addMusician(Musician* m) = 0;
    virtual void removeMusician(char* name) = 0;
    Band(char* bandName = "band1", int size = 0)
    {
        this->bandName = new char[strlen(bandName)+1];
        assert(this->bandName != NULL);
        strcpy(this->bandName, bandName);
        this->size = size;
    }
    Band(const Band& other)
    {
        this->bandName = new char[strlen(other.bandName)+1];
        assert(this->bandName != NULL);
        strcpy(this->bandName, other.bandName);
        this->size = other.size;
        for(int i = 0; i < this->size; i++)
            musicians[i] = other.musicians[i];
    }
    virtual ~Band()
    {
        delete [] bandName;
    }
    Band& operator=(const Band& other)
    {
        if(this != &other)
        {
            delete [] bandName;
            this->bandName = new char[strlen(other.bandName)+1];
            assert(this->bandName != NULL);
            strcpy(this->bandName, other.bandName);
            this->size = other.size;
            for(int i = 0; i < this->size; i++)
                musicians[i] = other.musicians[i];
        }
        return *this;
    }
    int sumPoroci()
    {
        int sum = 0;
        for(int i = 0; i < size; i++)
            sum += musicians.getPorok();
        return sum;
    }
};
class RockBand() : virtual public Band
{
    public:
        RockBand(char* bandName = "band", int size = 0) : Band(name, size)
        {

        }
        RockBand(const RockBand& other) : RockBand(other)
        {

        }
        ~RockBand()
        {

        }
        RockBand& operator=(const RockBand& other)
        {
            if(this != &other)
            {
                Band :: operator=(other);
            }
            return *this;
        }
    virtual bool addMusician(Musician* m)
    {
        if(size < 10)
        {
            if((!(strcmp(m->getType(), "rock"))) || (m->moreThanHundred()))
            {
                musicians[size] = m;
                size++;
                return true;
            }
        else return false;
        }
        return false;
    }
    virtual bool removeMusician(char* name)
    {
        if(size > 0)
        {
            for(int i = 0; i < size; i++)
            {
                if(!strcmp(musicians[i]->getName(), name))
                {
                    for(int j = i+1; j < size; j++)
                    {
                        musicians[j-1] = musicians[j];
                    }
                    size--;
                    return true;
                }
            }
            return false;
        }
        else return false;
    }
    double averageBeautyBand()
    {
        int sum = 0;
        for(int i = 0; i < size; i++)
        {
            sum += musicians[i]->getBeauty();
        }
        return sum/size;
    }
    double scoreOfBand()
    {
        //int sum = 0;
        return musicians->sumMS() - musicians->sumPoroci();
    }
};
class FolkBand : virtual public Band
{
public:
    virtual void addMusician(Musician* m)
    {
        if(size < 10)
        {
            if((!strcmp(m->getType(), "folk")) || (musicians->lessThanTen()))
                { musicians[size] = m;
                size++;
                return true;
                }
                else return false;

        }
        return false;
    }
};
