# Compilers-SymbolTabel-
This project is an implementation of a symbol table data structure. A symbol table maps strings (identifiers) to records containing information about the identifier. Symbol tables are essential components of compilers, interpreters, and other software systems that need to manage named entities.

**Key features:**

* The symbol table can be configured to be case-sensitive or case-insensitive.
* It supports the following operations:
    * `GetSymbol(str)`: Look up the string `str` in the symbol table and return the corresponding entry, or `NULL` if not found.
    * `PutSymbol(str)`: Look up the string `str` in the symbol table. If found, return the corresponding entry. Otherwise, create a new entry, insert it into the table, and return a pointer to it.
    * `ClearSymbolTable()`: Remove all entries from the symbol table and reclaim their memory space.
    * `PrintSymbolStats()`: Print statistics on the utilization of the symbol table, such as the number of entries, the number of free slots, and the length of the search chains.

**Implementation:**
The symbol table is implemented using a hash table.
