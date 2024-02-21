#ifndef STENTRY_H
#define STENTRY_H

#include <stdio.h>
#include <string.h>

#define TYPE_SIZE 5

typedef enum {
    STE_INTEGER,
    STE_STRING,
    STE_BOOLEAN,
    STE_FLOAT,
    STE_NONE
} STE_TYPE;

static char *STE_TYPE_STR[TYPE_SIZE] = {"integer", "string", "boolean", "float", "none"};
static char str[128];

class STEntry {
public:

    char Name[64];
    STE_TYPE Type;  //it is an int
    STEntry *Next;

    STEntry() {
        Next = NULL;
        Type = STE_NONE;
        Name[0] = 0; //empty String
    }

    STEntry(char *name, STE_TYPE type) {
        Next = NULL;
        Type = type;
        strcpy(Name, name);
    }

    char *toString() {
        if ((Type > STE_NONE) || Type < STE_INTEGER) Type = STE_NONE;
        sprintf(str, "(%s,%s)", Name, STE_TYPE_STR[Type]);
        return str;
    }

    void print(FILE *fp) {
        fprintf(fp, "%s ", toString());
    }

    static STE_TYPE getType(char *str) {
        int i;
        for (i = 0; i < TYPE_SIZE; i++) {
            if (strcmp(STE_TYPE_STR[i], str) == 0) return ((STE_TYPE) i);
        }
        return STE_NONE;

    }
};

#endif // STENTRY_H