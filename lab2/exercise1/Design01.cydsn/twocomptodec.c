#include "twocomptodec.h"

// The next section of code is borrowed from the url: 
// https://stackoverflow.com/questions/2689028/need-fastest-way-to-convert-2s-complement-to-decimal-in-c?rq=1
// =====================================================================
//I nedenstående kode udregnes to kompliment
int binTwosComplementToSignedDecimal(char binary[],int significantBits) 
{
    int power = pow(2,significantBits-1);
    int sum = 0;
    int i;

    for (i=0; i<significantBits; ++i)
    {
        if ( i==0 && binary[i]!='0')
        {
            sum = power * -1;
        }
        else 
        {
            sum += (binary[i]-'0')*power;//The -0 is needed
        }
        power /= 2;
    }

    return sum;
}
//=====================================================================