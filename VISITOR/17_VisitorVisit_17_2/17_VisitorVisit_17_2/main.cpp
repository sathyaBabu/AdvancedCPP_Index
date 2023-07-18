//
//  main.cpp
//  17_VisitorVisit_17_2
//
//  Created by Sathya Babu on 14/11/21.
// https://gieseanw.wordpress.com/2018/12/29/reuse-double-dispatch/
// https://wandbox.org/permlink/Wr9uxPvI9mMJ0Xiz
#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
//#include "Animal.h"
//#include "AnimalCollection.h"



struct AnimalVisitor;
struct Animal
{
    public:
    virtual ~Animal() = default;
    virtual void Visit(AnimalVisitor* _visitor) = 0;
    virtual void Visit(AnimalVisitor* _visitor) const = 0;
};


namespace animal_serialization
{
    // preconditions: Animal is not null, _outstream is open and ready
    void Save(const Animal* _animal, std::ostream& _outstream);
    
    // precondition: _instream is open and ready
    std::vector<std::unique_ptr<Animal>> Load(std::istream& _istream);
}
//#include "Animal.h"
//#include "AnimalVisitor.hpp"

//#include "Visitor.hpp"


template<class T>
struct SingleVisitor
{
    virtual void Visit(T*) = 0;
    virtual void Visit(const T*) = 0;
};

template<class... T>
struct Visitor : public SingleVisitor<T>...
{
    using SingleVisitor<T>::Visit...;
};

struct Cat;
struct Dog;
struct Horse;
struct Llama;

// strong typedef
struct AnimalVisitor : public Visitor<Cat, Dog, Horse, Llama>
{};

// Mixin class, shall only be used as a base class for classes derived from Animal
template<class T>
struct VisitableAnimal : public Animal
{
    void Visit(AnimalVisitor* _visitor) override
    {
        _visitor->Visit(static_cast<T*>(this));
    }
    
    void Visit(AnimalVisitor* _visitor) const override
    {
        _visitor->Visit(static_cast<const T*>(this));
    }
};


struct Cat : VisitableAnimal<Cat>
{};
struct Dog : VisitableAnimal<Dog>
{};
struct Horse : VisitableAnimal<Horse>
{};
struct Llama : VisitableAnimal<Llama>
{};


struct AnimalCollection
{
    void Add(std::unique_ptr<Animal> _animal);
    void Save(std::ostream& _outstream) const;
    void Load(std::istream& _istream);
private:
    std::vector<std::unique_ptr<Animal>> animals_;
};


void AnimalCollection::Save(std::ostream& _outstream) const
{
    for(const auto& animal : animals_)
    {
        animal_serialization::Save(animal.get(), _outstream);
    }
}

void AnimalCollection::Load(std::istream& _istream)
{
    std::vector<std::unique_ptr<Animal>> loadedAnimals = animal_serialization::Load(_istream);
    animals_ = std::move(loadedAnimals);
}

void AnimalCollection::Add(std::unique_ptr<Animal> _animal)
{
    animals_.push_back(std::move(_animal));
}

//////
///
///



template<class T>
struct SingleDoNothingAnimalVisitor : virtual AnimalVisitor
{
   using AnimalVisitor::Visit;
   void Visit(T*) override{}
   void Visit(const T*) override{}
};

template<class... T>
struct MultipleDoNothingAnimalVisitor : public SingleDoNothingAnimalVisitor<T>...
{
    using SingleDoNothingAnimalVisitor<T>::Visit...;
};

// strong typedef
struct DoNothingAnimalVisitor : public MultipleDoNothingAnimalVisitor<Cat, Dog, Horse, Llama>
{};


namespace
{
    std::string CatString(){return "cat";}
    std::string DogString(){return "dog";}
    std::string HorseString(){return "horse";}
    std::string LlamaString(){return "llama";}

    struct SaveAnimalVisitor : DoNothingAnimalVisitor
    {
        using DoNothingAnimalVisitor::Visit;
        
        std::ostream* outstream_ = nullptr;

        // precondition: _outstream will outlive the SaveAnimalVisitor instance
        explicit SaveAnimalVisitor(std::ostream& _outstream) : outstream_{&_outstream}
        {}

        void Visit(const Cat*) override{
            *outstream_ << CatString() << "\n";
        }

        void Visit(const Dog*) override{
            *outstream_ << DogString() << "\n";
        }
        void Visit(const Horse*) override{
            *outstream_ << HorseString() << "\n";
        }
        void Visit(const Llama*) override{
            *outstream_ << LlamaString() << "\n";
        }
    };
    
    template<class T>
    std::unique_ptr<Animal> CreateAnimal()
    {
        return std::make_unique<T>();
    }
    
    using AnimalCreatorFunction = std::function<std::unique_ptr<Animal>()>;
    std::unordered_map<std::string, AnimalCreatorFunction> animalFactory =
    {
        {CatString(), AnimalCreatorFunction{&CreateAnimal<Cat>}},
        {DogString(), AnimalCreatorFunction{&CreateAnimal<Dog>}},
        {HorseString(), AnimalCreatorFunction{&CreateAnimal<Horse>}},
        {LlamaString(), AnimalCreatorFunction{&CreateAnimal<Llama>}},
    };
}

namespace animal_serialization
{
    void Save(const Animal* _animal, std::ostream& _outstream)
    {
        ::SaveAnimalVisitor saveVisitor{_outstream};
        _animal->Visit(&saveVisitor);
    }
    
    std::vector<std::unique_ptr<Animal>> Load(std::istream& _istream)
    {
        std::vector<std::unique_ptr<Animal>> toReturn;
        std::string line;
        while(std::getline(_istream, line))
            toReturn.push_back(animalFactory.at(line)());
        return toReturn;
    }
}

int main()
{
    AnimalCollection my_animals;
    my_animals.Load(std::cin);
    my_animals.Save(std::cout);
}
