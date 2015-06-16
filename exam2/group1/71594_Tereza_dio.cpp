//nasledqwane 
//abstrakciq
//
//

#include <iostream>
#include <cassert>
#include <cstring>
#include <cmath>

using namespace std;

class MusicalSkill
{
private:
	char* name;
	int skill;
	void cpy(const MusicalSkill & other)
	{
		this->name = new char[strlen(other.name) + 1];
		assert(name);
		strcpy_s(this->name, strlen(name) + 1, other.name);
		this->skill = other.skill;
	}
	void del()
	{
		delete[]name;
	}
public:
	MusicalSkill(char* name = " ", int skill = 0)
	{
		this->name = new char[strlen(name) + 1];
		assert(name);
		strcpy_s(this->name, strlen(name) + 1, name);
		this->skill = skill;
	}
	~MusicalSkill()
	{
		del();
	}
	MusicalSkill(const MusicalSkill & other)
	{
		cpy(other);
	}
	MusicalSkill operator =(const MusicalSkill & other)
	{
		if (this != &other)
		{
			del();
			cpy(other);
		}
		return *this;
	}
	char* getName()const
	{
		return this->name;
	}
	int getSkill()const
	{
		return this->skill;
	}
};
class Musicant
{
protected:
	char* name;
	int beauty;
	int poroci;
	MusicalSkill musSkills[5];
	void cpy(const Musicant & other)
	{
		this->name = new char[strlen(other.name) + 1];
		assert(name);
		strcpy_s(this->name, strlen(name) + 1, other.name);
		this->beauty = other.beauty;
		this->poroci = other.poroci;
		for (int i = 0; i < 5; i++)
		{
			this->musSkills[i] = other.musSkills[i];
		}
	}
	void del()
	{
		delete[]name;
	}
public:
	Musicant(char* name = " ", int beauty = 0, int poroci = 0)
	{
		this->name = new char[strlen(name) + 1];
		assert(name);
		strcpy_s(this->name, strlen(name) + 1, name);
		this->beauty = beauty;
		this->poroci = poroci;
	}
	virtual ~Musicant()
	{
		del();
	}
	Musicant(const Musicant & other)
	{
		cpy(other);
	}
	Musicant & operator = (const Musicant & other)
	{
		if (this != &other)
		{
			del();
			cpy(other);
		}
		return *this;
	}
	char* getName()const
	{
		return this->name;
	}
	void setName(char* name)
	{
		this->name = new char[strlen(name) + 1];
		assert(name);
		strcpy_s(this->name, strlen(name) + 1, name);
	}
	virtual int getBeauty()const = 0;
	virtual int getPoroci()const = 0;
	virtual char* getType() = 0;
// вземане на най-силните( с най-голяма оценка за умение) N поискани Musical_skill-ове на музканта.??
};

class RockMusicant:public Musicant
{
//the big 4?
public:
	virtual char* getType()const
	{
		char* type = "rock";
		return type;
	}
	virtual int getBeauty()const
	{
//красотата се пресмята по формулата -> красота( член данна)^2 + сумата от всички музикални умения - пороци * 3 ПИ.
		return pow(beauty, 2);
	}
	virtual int getPoroci()const
	{
		return this->poroci;
	}
};

class OtherMusicant :public Musicant
{
//the big 4?
private:
	bool race;
	OtherMusicant(char* name = " ", int beauty = 0, int poroci = 0, bool race = true) : Musicant(name, beauty, poroci)
	{
		this->race = race;
	}
	virtual int getBeauty()const
	{
//красотата се пресмята по формулата -> красота( член данна)^5 + пороци + расова принадлежност * cos(от най-доброто му музикално умение);
		return pow(beauty, 5) + poroci;
	}
	virtual int getPoroci()const
	{
		return this->poroci;
	}
	virtual char* getType()const
	{
		char* type = "rock_tack";
		return type;
	}
};
class Group
{
protected:
	char* name;
	Musicant * mus[10];
	int size; // size and count?
	int count;
	void cpy(const Group & other)
	{
		this->name = new char[strlen(other.name) + 1];
		assert(name);
		strcpy_s(this->name, strlen(name) + 1, other.name);
		this->size = other.size;
		this->count = other.count;
		for (int i = 0; i <count; i++)
		{
			this->mus[i] = other.mus[i];
		}
	}
	void del()
	{
		delete[]name;
	}
public:
	Group(char* name = " ")
	{
		this->name = new char[strlen(name) + 1];
		assert(name);
		strcpy_s(this->name, strlen(name) + 1, name);
		this->size = 2;
		this->count = 0;
	}
	~Group()
	{
		del();
	}
	Group(const Group & other)
	{
		cpy(other);
	}
	Group &operator = (const Group & other)
	{
		if (this != &other)
		{
			del();
			cpy(other);
		}
		return *this;
	}
	virtual bool add(Musicant& other) = 0;
	bool remove(char* name)
	{
		int index;
		bool toReturn = false;
		for (int i = 0; i < count; i++)
		{
			if (strcmp(mus[i]->getName(), name) == 0)
			{
				index = i;
				toReturn = true;
				for (int j = index; j < count; j++)
				{
					mus[j] = mus[j + 1];
				}
			}
		}
		return toReturn;
	}
	virtual int getBeauty() const = 0;
};

class RockGroup : public Group //virtual?
{
public:
	RockGroup(char* name = " ") : Group(name)
	{

	}
	virtual bool add(Musicant & other)
	{
		if (strcmp(other.getType(), "rock") == 0) // или имат умение на даден инструмент повече от 100?
		{
			if (count < 10)
			{
				this->mus[count] = &other; //count++ ?
				return true;
			}
			else
				return false;
		}
	}
	/*virtual int getBeauty()const
	{
		int sum = 0;
		for (int i = 0; i < count; i++)
		{
			sum += mus[i].getBeauty();
		}  //return?
	}*/

};

class OtherGroup : public Group //virtual?
{
public:
	OtherGroup(char* name = " ") : Group(name)
	{

	}
	virtual bool add(Musicant & other)
	{
		if (strcmp(other.getType(), "rock_tack") == 0) //..
		{
			if (count < 10)
			{
				this->mus[count] = &other;
				return true;
			}
			else
				return false;
		}
	}
};

/*class FolkRockGroup :public Group, public RockGroup, public OtherGroup
{
public:
	FolkRockGroup(char*name = " ") : Group(name)
	{

	}
	virtual bool add(Musicant & other)
	{
		if (strcmp(other.getType(), "rock_tack") == 0 || strcmp(other.getType(), "rock") == 0)
		{
			if (count < 10)
			{
				this->mus[count] = &other;
				return true;
			}
			else
				return false;
		}
	}
};*/

int main()
{

	system("pause");
	return 0;
}
