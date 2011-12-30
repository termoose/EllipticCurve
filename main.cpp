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

int main (int argc, const char * argv[])
{
    BigInteger a = 10;
    BigInteger b = 8;
    
    Curve EllipticCurve( 23 );
    Point InitialPoint = EllipticCurve.GetCurvePoint();
    
    std::cout << "Point: (" << InitialPoint.X << ", " << InitialPoint.Y << ")" << std::endl;

    for( int i = 0; i < 50000; ++i )
    {
        InitialPoint = InitialPoint + InitialPoint;
    }
    
    Point SumPoint = InitialPoint + InitialPoint;
    
    std::cout << "SumPoint: (" << SumPoint.X << ", " << SumPoint.Y << ")" << std::endl;
    BigInteger X = SumPoint.X;
    BigInteger Y = SumPoint.Y;
    BigInteger A = EllipticCurve.GetA();
    BigInteger B = EllipticCurve.GetB();
    BigInteger N = EllipticCurve.GetN();
    
    if( !SumPoint.Zero )
        std::cout << "Correct point: " << (((Y*Y) % N) == ((X*X*X + A*X + B) % N)) << std::endl;
    else
        std::cout << "Identity point!" << std::endl;

    return 0;
}

