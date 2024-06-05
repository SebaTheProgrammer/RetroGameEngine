// Utilities.cpp

#include "Utilities.h"

// Function definitions
int GetRowStartIndex( int col )
{
    return ( ( col - 1 ) * col ) / 2;
}

int GetRowEndIndex( int col )
{
    return GetRowStartIndex( col ) + col - 1;
}