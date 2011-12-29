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
    
    Curve< BigInteger > Curve( 50 );
    
    Point< BigInteger > Point = Curve.GetPoint();
    
    std::cout << "Point (" << Point.x << ", " << Point.y << ")" << std::endl;

    return 0;
}

