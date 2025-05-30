#include "datatypes.h"
#include <iostream>
using namespace std;

/**
 * Returns the ASCII sum of all characters in a string
 * To be used as the indexing key of a string into the hash table,
 * e.g. k = sumStringChars(str)
*/
unsigned int sumStringChars(const string& str) 
{
    unsigned int sum = 0;
    for (unsigned int i=0; i<str.length(); ++i)
        sum += static_cast<unsigned int>(str[i]);
    return sum;
}


// TASK 1.1: VaccinationStatus default constructor
VaccinationStatus::VaccinationStatus() {
    // TODO
    for(unsigned int i = 0;i < VACCINE_TABLE_SIZE;++i){
        vaccineHashTable[i] = "";
    }
    numVaccines = 0;
}

// TASK 1.2: VaccinationStatus::addVaccine(const string&)
// - If the table is not at least half empty, output the first error message and return.
// - Else, calculate k = sumStringChars(v) and hash(k) = k % VACCINE_TABLE_SIZE
//   Follow the quadratic probing formula: h(i) = [hash(k) + i^2] % VACCINE_TABLE_SIZE
//   to add the vaccine to the table.
//   If the vaccine already exists, output the second error message and return.
void VaccinationStatus::addVaccine(const string& v)
{
    if (numVaccines >= VACCINE_TABLE_SIZE/2/* TODO: Table is not half-empty */) {
        cout << "This system does not support having taken more than " << numVaccines << " vaccines." << endl;
        return;
    }

    // TODO: Quadratic probing
    unsigned int k = sumStringChars(v);
    unsigned int hash = k % VACCINE_TABLE_SIZE;
    unsigned int i = 0;
    unsigned int h = (hash + i * i)% VACCINE_TABLE_SIZE;

    while(vaccineHashTable[h] != ""){
        if (vaccineHashTable[h] == v/* TODO: Vaccine exists */) {
            cout << "This animal has already taken " << v << "." << endl;
            return;
        }
        i++;
        h = (hash + i * i)% VACCINE_TABLE_SIZE;
    }
    // TODO: Quadratic probing
    vaccineHashTable[h] = v;
    numVaccines++;
}

// TASK 1.3: VaccinationStatus::hasVaccine(const string&) const
// Returns true if the vaccine exists in the table, false otherwise
bool VaccinationStatus::hasVaccine(const string& v) const
{
    // TODO
    unsigned int k = sumStringChars(v);
    unsigned int hash = k % VACCINE_TABLE_SIZE;
    unsigned int i = 0;
    unsigned int h = (hash + i * i)% VACCINE_TABLE_SIZE;

    while(vaccineHashTable[h] != ""){
        if(vaccineHashTable[h] == v){
            return true;
        }
        i++;
        h = (hash + i * i)% VACCINE_TABLE_SIZE;
    }
    return false;
}


/**
 * Returns a value representing the current hash table
 * Used for comparing 2 animals with different vaccination status
*/
unsigned int VaccinationStatus::getTotalHashValue() const 
{
    unsigned int hash = 0;
    for (unsigned int i=0; i<VACCINE_TABLE_SIZE; ++i)
        hash += sumStringChars(vaccineHashTable[i]);
    return hash * numVaccines;
}
