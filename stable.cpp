#include "stable.h"
#include <iostream>
#include <cctype> // Include the cctype header for the tolower() function

using namespace std;

void STable::init(int size)
{
    Size = size;
    Table = new STList[size];
    fold_case = 0; // sensitive
}
/**
 * @brief STable::STable : Default constructor, call init with DEFAULT_SIZE
 */
STable::STable()
{
    init(DEFAULT_SIZE);
}
/**
 * @brief STable::STable  constructor with Number of slots = size, call init with size
 * @param size
 */
STable::STable(unsigned long size)
{
    init(size);
}
/**
 * @brief STable::Reset   Recreate the Table by calling clear then call init
 * @param size
 */
void STable::Reset(unsigned long size)
{
    Clear();
    init(size);
}
/**
 * @brief STable::ElfHash : symbolTableHash Function
 * @param str  : Key which is the Variable Name to be added to the Symbol Table
 * @return
 */
unsigned long STable::ElfHash( char *str )
{
    if (fold_case)
    { // If fold_case is true, convert the string to lowercase before hashing
        for (int i = 0; str[i] != '\0'; i++)
        {
            str[i] = tolower(str[i]);
        }
    }

    unsigned long   h = 0, high; // h=0, g
    unsigned char *s = (unsigned char *) str;
    while ( *s )
    {
        h = ( h << 4 ) + *s++;  //1/4 of bits
        if ( high = h & 0xF0000000 )
            h ^= high >> 24; // h = h ^ (g >>24)
        h &= ~high; // in book this is h = h^g
    }
    return h%Size;
}
/**
 * @brief STable::AddEntry : Adds the Entry, call symbolTableHash to find index, then call Add to the List in Table[index] to add it
 * @param name : Name of Entry to be added
 * @param type : type of Entry. See the Main function for example how to find it
 * @return  true if added and false otherwise, the List Table[index] Already returns this for you
 */
bool STable::AddEntry(char *name, STE_TYPE type)
{
    if (fold_case)
    { // If fold_case is true, convert the name to lowercase before adding
        for (int i = 0; name[i] != '\0'; i++)
        {
            name[i] = tolower(name[i]);
        }
    }
    unsigned long index = ElfHash(name);
    bool Added = Table[index].AddEntry(name, type);
    return Added;
}
/**
 * @brief STable::FindAndPrintEntry Finds and prints the Entry if it is found
 *                if Not found print the Message Not found, see the example result
 * @param name  : name to search for
 * @param fp  : File pointer to print : See Example in reults
 */
void  STable::FindAndPrintEntry(char *name, FILE *fp)// may be find and print entry
{
    if (fold_case)
    { // If fold_case is true, convert the name to lowercase before searching
        for (int i = 0; name[i] != '\0'; i++)
        {
            name[i] = tolower(name[i]);
        }
    }

    unsigned long index = ElfHash(name);
    STEntry *ste = Table[index].FindEntry(name);
    if(ste) fprintf(fp,"%s: Found = %s\n", name, ste->toString()); // to be fixed , se
    else fprintf(fp,"%s: not found \n",name);

}
/**
 * @brief STable::PrintAll : Prints all Elements. Print the Count of each list and the Entries.
 *                            See the Sample Result (fout.txt) to format your output
 *                            Loop through the Slots (Lists) and Call Table[i].printAll
 * @param fp
 */

void STable::PrintAll(FILE *fp)
{
    unsigned long i;
    for (i =0; i < Size; i++)
    {
        fprintf(fp,"T[%d]: %d ste:\t", i, Table[i].Count());
        Table[i].PrintAll(fp);
    }

}
/**
 * @brief STable::Clear : Delete All Elements, use a loop and call the Table[i].clear. Then Delete the Array Table
 */
void STable::Clear()
{
    unsigned long i;
    for (i =0; i < Size; i++)
    {
        Table[i].Clear();
    }
    delete[]Table;

}
STable::~STable()
{
    Clear();
}

STable::STable(int fold_case_flag)
{
    // Constructor to create a new SymbolTable instance
    // with the specified fold_case_flag value
    init(DEFAULT_SIZE);
    fold_case = fold_case_flag;
}


STEntry* STable::Get_symbol(char* str)
{
    // Function to get the symbol table entry by its name

    if (fold_case)
    { // If fold_case is true, convert the name to lowercase before searching
        for (int i = 0; str[i] != '\0'; i++) {
            str[i] = tolower(str[i]);
        }
    }

    // Get the hash value (index) for the given name 'str'
    unsigned long index = ElfHash(str);

    // Look for the entry with the given name 'str' in the STList at the computed index
    // 'FindEntry' function is called, which performs a linear search in the STList
    // to find the entry with the matching name.
    STEntry* entry = Table[index].FindEntry(str);

    // Return the pointer to the found entry if it exists, or nullptr if not found.
    cout << "The entry name is " << entry->Name <<endl;
    return entry;
}


STEntry* STable::Put_symbol(char* str, STE_TYPE type)
{
    // Function to put a new symbol in the symbol table

    if (fold_case) { // If fold_case is true, convert the name to lowercase before adding
        for (int i = 0; str[i] != '\0'; i++)
        {
            str[i] = tolower(str[i]);
        }
    }

    // Get the hash value (index) for the given name 'str'
    unsigned long index = ElfHash(str);

    // Look for the entry with the given name 'str' in the STList at the computed index
    // 'FindEntry' function is called, which performs a linear search in the STList
    // to find the entry with the matching name.
    STEntry* entry = Table[index].FindEntry(str);

    // Check if the entry with the given name 'str' already exists in the symbol table
    if (entry == NULL)// If the entry does not exist
    {
        bool added = Table[index].AddEntry(str, type);

        // If the AddEntry function returns true, it means that the addition was successful,
        // and the pointer to the newly added entry is assigned to the entry variable.
        if (added)
        {
            cout << "New entry added for " << str << " with type " << STE_TYPE_STR[type] << endl;
        }

    }
    else
    {
        cout << "There is already an entry for " << str << " with type " << STE_TYPE_STR[entry->Type] << endl;
    }

    // Return the pointer to the added or pre-existing entry.
    return entry;
}


void STable::ClearSymbolTable()
{
   // Loop through each STList in the Table and call its Clear() function to remove all entries

    for (unsigned long i = 0; i < Size; i++)
    {
        Table[i].Clear();
    }
}

void STable::PrintSymbolStats()
{
    // Print the number of entries in the symbol table

    int totalEntries = 0;
    for (unsigned long i = 0; i < Size; i++)
    {
        totalEntries += Table[i].Count();
    }

    printf("Total number of entries in the symbol table: %d\n", totalEntries);

    // Print the number of free slots in each STList
    int freeSlots = 0;
    for (unsigned long i = 0; i < Size; i++)
    {
        freeSlots += (DEFAULT_SIZE - Table[i].Count());
    }
    printf("Total number of free slots in the symbol table: %d\n", freeSlots);

    // Print the length of the search chains in each STList
    int maxLength = 0;
    for (unsigned long i = 0; i < Size; i++)
    {
        int chainLength = Table[i].Count();
        if (chainLength > maxLength)
        {
            maxLength = chainLength;
        }
    }
    printf("Maximum length of the search chains in the symbol table: %d\n", maxLength);
}


