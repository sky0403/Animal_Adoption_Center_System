#include "adoptionCenter.h"
#include <iostream>
using namespace std;


// TASK 4.1: AdoptionCenter constructor
// Initialize all data members to represent an empty database.
// The BSTs need to be initialized with their comparison functions:
// - NAME: Sort by species name (including breed), in increasing lexicographic order
// - AGE: Sort by increasing age
// - HEALTH: Sort by increasing health severity
// - VACCINE: Sort by increasing VaccinationStatus total hash value
//
// The comparison functions when comparing the left animal (a1) and right animal (a2) should return:
// - a negative value if a1 < a2
// - 0 if a1 == a2
// - a positive value if a1 > a2
//
// Hints:
// - You can write lambda functions to pass into the BST constructors
// - For comparing strings, look up the documentation for std::string::compare()
// - Be careful when performing arithmetic calculations with unsigned int

AdoptionCenter::AdoptionCenter():animals(nullptr),numAnimals(0),
      sortedAnimals{
        BST([](const Animal* a, const Animal* b)->int{
            return a->getSpecies().compare(b->getSpecies());
        }),
        BST([](const Animal* a, const Animal* b)->int{
            return (static_cast<int>(a->getAge())%100) - (static_cast<int>(b->getAge())%100);
        }),
        BST([](const Animal* a, const Animal* b)->int{
            return static_cast<int>(a->getHealthCondition().severity) - static_cast<int>(b->getHealthCondition().severity);    
        }),
        BST([](const Animal* a, const Animal* b)->int{
            return static_cast<int>(a->getVaccinationStatus().getTotalHashValue()) - static_cast<int>(b->getVaccinationStatus().getTotalHashValue());
        })
      }
{ 
    // TODO
}

// TASK 4.2: AdoptionCenter destructor
// Deallocate any dynamic memory in this class.
// Hint: This is where the animals should be deallocated.
AdoptionCenter::~AdoptionCenter() {
    // TODO
    for(unsigned int i = 0;i < numAnimals; ++i){
        delete animals[i];
    }
    delete[] animals;
}

// TASK 4.3: AdoptionCenter::addAnimal(Animal*)
// Add an animal to the dynamic-length array data member,
// by increasing its size by 1 and increment numAnimals accordingly.
// Add the animal to the end of the array, 
// such that the array is sorted by increasing ID (assume we only add increasing IDs)
// The animal should also be added to the 4 BSTs.
void AdoptionCenter::addAnimal(Animal* a) {
    // TODO
    Animal** new_array = new Animal*[numAnimals + 1];

    for(unsigned int i = 0; i < numAnimals; ++i){
        new_array[i] = animals[i];
    }
    new_array[numAnimals] = a;

    delete []animals;
    numAnimals ++;
    animals = new Animal*[numAnimals];
    
    //animals = new_array;
    for(unsigned int i = 0; i < numAnimals; ++i){
        animals[i] = new_array[i];
    }
    delete[] new_array;
   
    
    for (unsigned int i = 0; i < ID; i++) {
        sortedAnimals[i].insert(a);
    }

}

// TASK 4.4: AdoptionCenter::removeAnimal(unsigned int)
// Remove an animal from the database by ID.
// If the ID does not exist, do nothing.
// Otherwise, resize the array to decrease its size by 1,
// copy the non-deleted animals over and decrement numAnimals accordingly.
// The animal should also be removed from the 4 BSTs.
// Finally, return true if the animal was successfully removed.
bool AdoptionCenter::removeAnimal(unsigned int id) {
    
    // TODO
    for(unsigned int i = 0; i < numAnimals; ++i){
        if(animals[i]->getID() == id){
            Animal** new_array = new Animal*[numAnimals-1];
            for(int k = 0; k < ID; ++k){
                sortedAnimals[k].remove(animals[i]);
            }

            delete animals[i];
            for(unsigned int j = i; j < numAnimals - 1; ++j){
                animals[j] = animals[j + 1];
            }
            for(unsigned int l = 0; l < numAnimals - 1; ++l){
                new_array[l] = animals[l];
            }
            delete[] animals;
            animals = new_array;
            numAnimals--;
            return true;
        }
    }
    return false;
}

// TASK 4.5: AdoptionCenter::incrementAge()
// Increment the age of all animals by 1.
void AdoptionCenter::incrementAge()
{
    // TODO
    for(unsigned int i = 0; i < numAnimals; ++i){
        animals[i]->incrementAge();
    }
}

// TASK 4.6: AdoptionCenter::setAnimalHealthCondition(unsigned int, const HealthCondition&)
// Modify the animal with the specified ID's health condition to the provided parameter.
// If the animal does not exist, do nothing.
// Else, ensure the BST for health condition is sorted after the modification.
void AdoptionCenter::setAnimalHealthCondition(unsigned int id, const HealthCondition& h)
{
    // TODO
    for(unsigned int i = 0; i < numAnimals; ++i){
        if(animals[i]->getID() == id){
            sortedAnimals[HEALTH].remove(animals[i]);
            animals[i]->setHealthCondition(h);
            sortedAnimals[HEALTH].insert(animals[i]);
        }
    }
}

// TASK 4.7: AdoptionCenter:addAnimalVaccine(unsigned int, const string&)
// Add the provided vaccine to the animal specified by ID.
// If the animal does not exist, do nothing.
// Else, ensure the BST for vaccine status is sorted after the modification.
void AdoptionCenter::addAnimalVaccine(unsigned int id, const string& v)
{
    // TODO
    for(unsigned int i = 0; i < numAnimals; ++i){
        if(animals[i]->getID() == id){
            sortedAnimals[VACCINE].remove(animals[i]);
            animals[i]->addVaccine(v);
            sortedAnimals[VACCINE].insert(animals[i]);
        }
    }
}

// TASK 4.8: AdoptionCenter::setAnimalSpecialNeeds(unsigned int, const std::string&)
// Modify the animal with the specified ID's special needs to the provided parameter.
// If the animal does not exist, do nothing.
void AdoptionCenter::setAnimalSpecialNeeds(unsigned int id, const std::string& n)
{
    // TODO
    for(unsigned int i = 0; i < numAnimals; ++i){
        if(animals[i]->getID() == id){
            animals[i]->setSpecialNeeds(n);
        }
    }
}


/**
 * Provided function to display the animals in the database.
 * @param start: Starting index to print (e.g. start == 5: ignore the first 5 animals that matches the filter)
 * @param stop: Index to stop printing (e.g. stop == 10: print until the 10th animal [exclusive] that matches the filter)
 * @param filter: Only print animals that match this filter.
 * @param criteria: Sorting criteria. By default sort by ID (assuming animals are added in increasing ID)
*/
void AdoptionCenter::display(unsigned int start, unsigned int stop, const Filter& filter, SortCriteria criteria) const {
    unsigned int displayCount = stop - start;
    if (criteria == ID) {
        for (unsigned int i=0; i<numAnimals; ++i) {
            if (filter.match(*animals[i])) {
                animals[i]->display(start, displayCount);
            }
        }
    }
    else {
        sortedAnimals[criteria].print(start, displayCount, filter);
    }
}

/**
 * Provided function to print the vaccines an animal, specified by ID, has taken.
*/
void AdoptionCenter::displayPetVaccines(unsigned int id) const
{
    unsigned int i = 0;
    for (; i<numAnimals; ++i) {
        if (animals[i]->getID() == id) {
            VaccinationStatus v = animals[i]->getVaccinationStatus();
            if (v.numVaccines == 0)
                cout << "No vaccines found." << endl;
            else
                for (unsigned int j = 0; j < VACCINE_TABLE_SIZE; ++j) {
                    if (v.vaccineHashTable[j].length() > 0)
                        cout << v.vaccineHashTable[j] << endl;
                }
            return;
        }
    }
    if (i == numAnimals)
        cout << "ID not found in database." << endl;
}
