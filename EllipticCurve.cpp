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

Point::Point( Curve* _Parent ) : Parent( _Parent ), X( 0 ) , Y( 0 ), Zero( true )
{
}

Point::Point( BigInteger _X, BigInteger _Y, Curve *_Parent ) : X( _X ), Y( _Y ), Parent( _Parent ), Zero( false )
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

Point Point::operator-()
{
    return Point( X, -Y, Parent );
}

// Summing (x_1, y_1) + (x_2, y_2) = (x_3, y_3)
Point Point::operator+( const Point& Other )
{
    Point Result( Parent );
    BigUnsigned N = Parent->GetN();
    BigInteger A = Parent->GetA(), B = Parent->GetB();
    
    BigInteger Lambda = 0, v = 0;
    
    BigInteger x_1 = X, y_1 = Y;
    BigInteger x_2 = Other.X, y_2 = Other.Y;
    
    // The points have to belong to the same curve
    if( Parent != Other.Parent )
    {
        std::cout << "Incompatible curve points!" << std::endl;
        return Point( nullptr );
    }
    
    // O + P = P + O = P
    if( Zero )
        return Other;
    if( Other.Zero )
        return *this;
    
    // The sum is the identity element O
    if( x_1 == x_2 && y_1 == -y_2 )
    {
        Result.Zero = true;
        return Result;
    }
    
    // Normal sum of two points
    if( x_1 != x_2 )
    {
        Lambda = ( y_2 - y_2 ) * modinv( (x_2 - x_1) % N, N );
        v      = ( y_1*x_2 - y_2*x_1 ) * modinv( (x_2 - x_1) % N, N );
    }
    else
    {
        Lambda = ( BigInteger(3) * x_1 * x_1 + A ) * modinv( (BigInteger(2) * y_1) % N, N );
        v      = ( A * x_1 - x_1 * x_1 * x_1 + BigInteger(2) * B ) * modinv( (BigInteger(2) * y_1) % N, N );
    }
    
    BigInteger ResultX = Lambda * Lambda - x_1 - x_2;
    BigInteger ResultY = -Lambda * ResultX - v;
    
    Result.SetPoint( ResultX % N, ResultY % N );
    
    return Result;
}

Point Point::operator*( const BigInteger &n )
{
    if( n == 0 ) return Point( Parent );
    
    else if( n % 2 == 1 )
    {
        return *this + *this * (n - 1);
    }
    else
    {
        return (*this + *this) * (n / 2);
    }
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