//naslediavane, abstrakcia, kapsulacia, polimorfisam

#include <iostream>
#include <cstring>
#include <cassert>
#include <cmath>

using namespace std;

struct Musical_skill
{
    char* name;
    int skill;
    void del()
    {
        delete [] name;
    }
    void cpy(const Musical_skill& other)
    {
        name = new char[strlen(other.name)+1];
        assert(name != NULL);
        strcpy(name, other.name);
        skill = other.skill;

    }
    Musical_skill()
    {
        name = "";
        skill = 0;
    }
    Musical_skill(char* name, int skill)
    {
        this->name = new char[strlen(name)+1];
        assert(this->name != NULL);
        strcpy(this->name, name);
        this->skill = skill;
    }
    Musical_skill(const Musical_skill& other)
    {
        cpy(other);
    }
    virtual ~Musical_skill()
    {
        del();
    }
    Musical_skill& operator=(const Musical_skill& other)
    {
        if(this != &other)
        {
            del();
            cpy(other);
        }
        return *this;
    }
//    Musical_skill& operator+(Musical_skill& other)
//    {
//        int sum = skill+other.skill;
//        Musical_skill* temp = new Musical_skill(name, sum);
//        return *temp;
//    }
};


class Musician
{
protected:
    char*name;
    int beauty;
    int vices;
    Musical_skill skill[5];
public:
    void del()
    {
        delete [] name;
    }
    void cpy(const Musician& other)
    {
        name = new char[strlen(other.name)+1];
        assert(name != NULL);
        strcpy(name, other.name);
        beauty = other.beauty;
        vices = other.vices;
        for(int i = 0; i < 5; i++)
        {
            skill[i] = other.skill[i];
        }
    }
    Musician()
    {
        name = "";
        beauty = 0;
        vices = 0;
        skill[5]; //?
    }
    Musician(char* name, int beauty, int vices, Musical_skill skill[5]) 
    {
        this->name = new char[strlen(name)+1];
        assert(this->name != NULL);
        strcpy(this->name, name);
        this->beauty = beauty;
        this->vices = vices;
        for(int i = 0; i < 5; i++)
        {
            this->skill[i] = skill[i];
        }

    }
    Musician(const Musician& other)
    {
        cpy(other);
    }
    ~Musician()
    {
        del();
    }
    Musician& operator=(const Musician& other)
    {
        cpy(other);
        del();
    }
    void set_name(char* name)
    {
        this->name = new char[strlen(name)+1];
        assert(this->name != NULL);
        strcpy(this->name, name);
    }
    int get_sum()
    {
        int *sum;
        *sum = 0;
        for(int i = 0; i < 5; i++)
        {
            *sum += skill[i].skill;
        }
        return *sum;
    }
    char* get_name()const
    {
        return name;
    }
    virtual double get_beauty() = 0;

    virtual int get_vices() = 0;
    virtual char* get_type() = 0;
    Musical_skill& get_best_skills( Musical_skill* skill)
    {
        Musical_skill best = skill[0];
        for(int i = 0; i < 5; i ++)
        {
            if(skill[i].skill > best.skill) best = skill[i]; //best.skill?
        }
        return best;

    }
};



class Rock:public Musician
{
    Rock():Musician()
    {

    }
    Rock(char* name, int beauty, int vices, Musical_skill skill[5]):Musician(name, beauty, vices, skill)
    {

    }
    Rock(const Rock& other):Musician(other)
    {

    }
    Rock& operator=(const Rock& other)
    {
        if(this != &other)
        {
            Musician::operator=(other);
        }
        return *this;
    }
    virtual double get_beauty()
    {
        return beauty*2 + this->get_sum() - vices*3*3.14;
    }
    virtual int get_vices()
    {
        return vices;
    }
    virtual char* get_type()
    {
        return "rock";
    }
};


class Folk:public Musician
{
protected:
    bool race;
public:
    Folk():Musician()
    {
        race = 1;
    }
    Folk(char* name, int beauty, int vices, Musical_skill skill[5]):Musician(name, beauty, vices, skill)
    {
        this->race = race;
    }
    Folk(const Folk& other):Musician(other)
    {
        race = other.race;
    }
    Folk& operator=(const Folk& other)
    {
        if(this != &other)
        {
            Musician::operator=(other);
            race = other.race;
        }
        return *this;
    }
    virtual double get_beauty()
    {
        return beauty*5 + vices + race*this->get_best_skills(skill).skill;
    }
    virtual char*get_type()
    {
        return "rock_tack";
    }
};

class Group
{
    protected:
    char* name;
    Musician* m[10];
    int size;
    public:
        Group()
        {
            name = "";
            m[20];
            size = 0;
        }
        Group(char* name, Musician* m[20], int size)
        {
            this->name = new char[strlen(name)+1];
            assert(this->name != NULL);
            strcpy(this->name, name);
            for(int i = 0; i < size; i++)
            {
                this->m[i] = m[i];
            }
            this->size = size;
        }
        Group(const Group& other)
        {
            name = new char[strlen(other.name)+1];
            assert(name != NULL);
            strcpy(name, other.name);
            for(int i = 0; i < other.size; i++)
            {
                m[i] = other.m[i];
            }
            size = other.size;
        }
        virtual ~Group()
        {
            delete[]name;
        }
        Group& operator=(const Group& other)
        {
            if(this != &other)
            {
                delete[]name;
                name = new char[strlen(other.name)+1];
                assert(name != NULL);
                strcpy(name, other.name);
                for(int i = 0; i < other.size; i++)
                {
                    m[i] = other.m[i];
                }
                size = other.size;
            }
        }
        virtual bool add_m(Musician& other);
        virtual void remove_m(char* name);
};

class RockG:virtual public Group
{
    RockG():Group()
    {

    }
    RockG(char* name, Musician* m[20], int size):Group(name, m, size)
    {

    }
    RockG(const RockG&other):Group(other)
    {

    }
    RockG& operator=(const RockG& other)
    {
        if(this!= & other)
        {
            Group::operator=(other);
        }
        return *this;

    }
    bool add_m(Musician& other)
    {
        if(strcmp(other.get_type(), "rock_track") == 0) // или имат умение на даден инструмент повече от 100. 
        {
            m[size] = &other;
            size++;
            return true;
        }
    }
    void remove_m(char* name)
    {
        for(int i = 0; i < size; i++)
        {
            if(strcmp(m[i]->get_name(), name) == 0)
            {
               for (int j = i + 1; j < size; ++j)
                {
                    m[j - 1] = m[j];
                }
            }
        }
        size --;
    }
};

class FolkG:virtual public Group
{
    FolkG():Group()
    {

    }
    FolkG(char* name, Musician* m[20], int size):Group(name, m, size)
    {

    }
    FolkG(const FolkG&other):Group(other)
    {

    }
    FolkG& operator=(const FolkG& other)
    {
        if(this!= & other)
        {
            Group::operator=(other);
        }
        return *this;

    }
    virtual bool add_m(Musician& other)
    {
        if(strcmp(other.get_type(), "rock") == 0) // ..
        {
            m[size] = &other;
            size++;
            return true;
        }
    }
    void remove_m(char* name)
    {
        for(int i = 0; i < size; i++)
        {
            if(strcmp(m[i]->get_name(), name) == 0)
            {
               for (int j = i + 1; j < size; ++j)
                {
                    m[j - 1] = m[j];
                }
            }
        }
        size --;
    }
};

class FolkRock:public RockG, public FolkG
{
public:
    FolkRock():Group(), RockG(), FolkG()
    {

    }
    //FolkRock(Musician* m[20],Musician* b[20]):Group()
};

int main()
{

}
