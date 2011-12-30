//
//  main.cpp
//  EllipticCurve
//
//  Created by Ole Andre Birkedal on 12/26/11.
//  Copyright (c) 2011 Extab. All rights reserved.
//

#include <iostream>
#include "EllipticCurve.h"

using namespace Elliptic;

Point ntimes( Point P, BigInteger n );

Point ntimes( Point P, BigInteger n )
{
    if( n == 0 ) return P;
    
    else if( n % 2 == 1 )
    {
        return P + ntimes( P, n - 1 );
    }
    else
    {
        return ntimes( P + P, n / 2 );
    }
}

int main (int argc, const char * argv[])
{
    Curve EllipticCurve( 23 );
    Point InitialPoint = EllipticCurve.GetCurvePoint();

    std::cout << "Point: (" << InitialPoint.X << ", " << InitialPoint.Y << ")" << std::endl;

    Point SumPoint( InitialPoint.Parent );
    
    for( int i = 0; i < 10; ++i )
    {

        SumPoint = SumPoint + InitialPoint;
        std::cout << "(" << SumPoint.X << ", " << SumPoint.Y << ")" << " ";
        BigInteger X = SumPoint.X;
        BigInteger A = EllipticCurve.GetA();
        BigInteger B = EllipticCurve.GetB();
        BigInteger Y = SumPoint.Y;
        BigInteger N = EllipticCurve.GetN();
        std::cout << "Correct point: " << (((Y*Y) % N) == ((X*X*X + A*X + B) % N)) << std::endl;
    }
    
    //InitialPoint = InitialPoint * 500000;
    
    //Point SumPoint = InitialPoint;
    
    std::cout << "SumPoint: (" << SumPoint.X << ", " << SumPoint.Y << ")" << std::endl;
    BigInteger X = SumPoint.X;
    BigInteger A = EllipticCurve.GetA();
    BigInteger B = EllipticCurve.GetB();
    BigInteger Y = SumPoint.Y;
    BigInteger N = EllipticCurve.GetN();
    
    if( !SumPoint.Zero )
        std::cout << "Correct point: " << (((Y*Y) % N) == ((X*X*X + A*X + B) % N)) << std::endl;
    else
        std::cout << "Identity point!" << std::endl;

    return 0;
}

