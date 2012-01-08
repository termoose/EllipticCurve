//
//  main.cpp
//  EllipticCurve
//
//  Created by Ole Andre Birkedal on 12/26/11.
//  Copyright (c) 2011 Extab. All rights reserved.
//

#include <iostream>
#include "EllipticCurve.h"

#include <thread>
#include <vector>

#include <unistd.h>

#include "RSANumbers.h"

#define NUMBER_OF_THREADS 8

using namespace Elliptic;

void ThreadFunction( const BigUnsigned& N, const BigInteger& B );
void ThreadFunction( const BigUnsigned& N, const BigInteger& B )
{
    
    while( 1 )
    {
        try
        {
            Curve E( N );
            Point P = E.GetCurvePoint();
            P * B;

        }
        catch( BigInteger Factor )
        {
            std::cout << "Factor: " << Factor << std::endl;
            
            exit( 1 );
        }
    }
    
    return;
}

int main (int argc, const char * argv[])
{
    std::string NumberString( CUSTOM_LARGE );
    BigUnsigned BigRSA;

    BigRSA = stringToBigUnsigned( NumberString );
    
    std::vector< std::thread > Threads;
    for( unsigned int i = 0; i < NUMBER_OF_THREADS; ++i )
    {
        Threads.push_back( std::thread(ThreadFunction, BigRSA, 2*3*5*7*11*13*17*23*29*31) );
        sleep( 1 );
    }
    
    for( auto &t : Threads )
    {
        t.join();
    }

    return 0;
}

