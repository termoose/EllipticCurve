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
    Curve EllipticCurve( 997*991 );
    Point InitialPoint = EllipticCurve.GetCurvePoint();

    InitialPoint.Print();
    
    Point nPoint = InitialPoint * 2 * 3 * 5 * 7 * 11 * 13 * 17;
    nPoint.Print();

    return 0;
}

