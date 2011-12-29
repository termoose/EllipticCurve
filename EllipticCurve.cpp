//
//  EllipticCurve.cpp
//  EllipticCurve
//
//  Created by Ole Andre Birkedal on 12/26/11.
//  Copyright (c) 2011 Extab. All rights reserved.
//

#include <iostream>
#include "EllipticCurve.h"
#include "BigIntegerAlgorithms.hh"

using namespace Elliptic;

////
// CurvePoint
////

Point::Point( Curve* _Parent ) : Parent( _Parent ), X( 0 ) , Y( 0 ), Zero( false )
{
}

Point::~Point()
{
}

void Point::SetPoint( const BigInteger& _X, const BigInteger& _Y )
{
    X = _X;
    Y = _Y;
}

Point Point::operator+( const Point& Other )
{
    Point Result( Other.Parent );
    BigUnsigned N = Parent->GetN();
    
    // The points have to belong to the same curve
    if( Parent != Other.Parent )
    {
        std::cout << "Incompatible curve points!" << std::endl;
        return Point( nullptr );
    }
    
    if( X != Other.X ) // P != Q
    {
        BigInteger S = ( (Y - Other.Y) * modinv( X - Other.X, N ) ) % N;
        
        Result.X = ( S * S - X - Other.X ) % N;
        Result.Y = ( S * ( X - Result.X ) - Y ) % N;
        
        return Result;
    }
    else if( !X.isZero() && !Other.X.isZero() ) // P == Q != O
    {
        // Catch this if the modinv method fails, which is when 2Y does not have an inverse mod N
        BigInteger S = ( BigInteger( 3 ) * X * X - Parent->GetA() * modinv( (BigInteger( 2 ) * Y) % N, N ) ) % N;
        
        Result.X = ( S * S - BigInteger( 2 ) * X ) % N;
        Result.Y = ( S * ( X - Result.X ) - Y ) % N;
        
        return Result;
    }
    else // P == Q == O
    {
        // This is the identity element
        Zero = true;
    }
    
    return Result;
}

////
// Elliptic curve
////

Curve::Curve( const BigInteger &_A, const BigInteger &_B, const BigUnsigned &_N ) :
A( _A ), B( _B ), N( _N ), P( this )
{
}


// Random curve
Curve::Curve( const BigUnsigned &_N ) : P( this ), N( _N )
{
    // Select random point
    srand( (unsigned int)time( NULL ) );
    BigInteger X = BigInteger( rand() ) % N;
    BigInteger Y = BigInteger( rand() ) % N;
    
    P.X = X;
    P.Y = Y;

    // Select random coefficients
    A = BigInteger( rand() ) % N;
    B = (Y * Y - X * X * X - A * X) % N;
    
    std::cout << "Initial point: (" << X << ", " << Y << ")" << std::endl;
    std::cout << "Correct point: " << (((Y*Y) % N) == ((X*X*X + A*X + B) % N)) << std::endl;
    std::cout << "Random curve y^2 = x^3 + " << A << "x + " << B << std::endl;
}

Curve::~Curve()
{
    
}