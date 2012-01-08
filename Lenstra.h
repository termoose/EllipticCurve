//
//  Lenstra.h
//  EllipticCurve
//
//  Created by Ole Andre Birkedal on 1/7/12.
//  Copyright (c) 2012 Extab. All rights reserved.
//

#ifndef EllipticCurve_Lenstra_h
#define EllipticCurve_Lenstra_h

#include <thread>
#include <vector>

#include "EllipticCurve.h"

class Lenstra
{
public:
    Lenstra();
    ~Lenstra();
    
private:
    std::vector< std::thread > Threads;
};

#endif
