////////////////////////////////////////////////////////////////////////////////
// File Name: factory_test.cpp                                                //
// Author: Lior Cohen                                                         //
// Date 03/08/2020                                                            //
// Purpose: test file for the factory assignment                              //
// Code Reviewer: Yaacov Evenchik                                             //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

#include "factory.hpp"

using namespace std;
using namespace ilrd;

class AnimalParams
{
public:
    AnimalParams(string name, int num_of_legs, string speak):
         m_name(name), m_num_of_legs(num_of_legs), m_speak(speak)
    {}

    string m_name;
    int m_num_of_legs;
    string m_speak;
private:
    
};

class IAnimal
{
public:
    IAnimal(string name, int num_of_legs, string speak):
                  m_params(AnimalParams(name, num_of_legs, speak))
    {}

    inline string& GetName()
    {
        return (m_params.m_name);
    }

    inline int GetNumOfLegs()
    {
        return (m_params.m_num_of_legs);
    }

    inline string& GetSpeak()
    {
        return (m_params.m_speak);
    }

    virtual void Print()
    {}
private:
    AnimalParams m_params;
};

class Cat : public IAnimal
{
public:
    Cat(string name, int num_of_legs, string speak):
           IAnimal(name, num_of_legs, speak)
    {}

    void Print()
    {
        cout << "The cat name is: " << this->GetName() << endl;
        cout << this->GetName() << " has " << this->GetNumOfLegs() << " legs" << endl;
        cout << this->GetName() << " speaks by doing: " << this->GetSpeak() << endl;
    }

private:
    Cat(const Cat& _other);
    Cat &operator=(const Cat& _other);
};

class Spider : public IAnimal
{
public:
    Spider(string name, int num_of_legs, string speak):
           IAnimal(name, num_of_legs, speak)
    {}

    void Print()
    {
        cout << "The spider name is: " << this->GetName() << endl;
        cout << this->GetName() << " has " << this->GetNumOfLegs() << " legs" << endl;
        cout << this->GetName() << " speaks by doing: " << this->GetSpeak() << endl;
    }

private:
    Spider(const Cat& _other);
    Spider &operator=(const Cat& _other);
};

IAnimal* CreateCat(AnimalParams params)
{
    Cat *cat = new Cat(params.m_name, params.m_num_of_legs, params.m_speak);
    cat->Print();

    return (cat);
}

IAnimal* CreateSpider(AnimalParams params)
{
    Spider *spider = new Spider(params.m_name, params.m_num_of_legs, params.m_speak);
    spider->Print();

    return (spider);
}

int main()
{
    system("clear");
    cout << "\nMAIN\n" << endl;

    string cat_name = "Kitty";
    string spider_name = "Spidi";

    Factory<string, IAnimal, AnimalParams> animal_factory;

    animal_factory.Add("cat", CreateCat);
    animal_factory.Add("spider", CreateSpider);

    AnimalParams new_params("try", 2, " try");

    AnimalParams main_spider("Spidi", 8, " ");
    AnimalParams main_cat(cat_name, 4, "Meao");

    IAnimal *Spider = animal_factory.Create("spider", main_spider);
    IAnimal *cat = animal_factory.Create("cat", main_cat);


    return (0);
}
