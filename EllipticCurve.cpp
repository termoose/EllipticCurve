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

Point::Point( Curve* _Parent, bool _Zero ) : Parent( _Parent ), X( 0 ) , Y( 0 ), Zero( _Zero )
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
    return Point( X, (-Y) % Parent->GetN(), Parent );
}

// Summing (x_1, y_1) + (x_2, y_2) = (x_3, y_3)
Point Point::operator+( const Point& Other )
{
    Point Result( Parent );
    BigUnsigned N = Parent->GetN();
    BigInteger A = Parent->GetA(), B = Parent->GetB();
    
    BigInteger Lambda, v;
    
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
    
    // The sum is the identity element O (Infinity)
    if( X == Other.X && (Y + Other.Y).isZero() )
    {
        return Point( Parent, true );
    }

    // Normal sum of two points
    if( X != Other.X )
    {
        BigInteger Divider, factor;

        try
        {
            Divider = modinv( (Other.X - X), N, factor );
        }
        catch( const char *Message )
        {
            throw factor;
        }

        Lambda = ( Other.Y - Y ) * Divider;
        v      = ( X*Other.X - Other.Y*X ) * Divider;
    }
    else
    {
        BigInteger Divider, factor;
        
        try 
        {
            Divider = modinv( (BigInteger(2) * Y), N, factor );
        }
        catch ( const char *Message )
        {
            throw factor;
        }

        Lambda = ( BigInteger(3) * X * X + A ) * Divider;
        v      = ( A * X - X * X * X + BigInteger(2) * B ) * Divider;
    }
    
    BigInteger ResultX = Lambda * Lambda - X - Other.X;
    
    Result.SetPoint( ResultX % N, (-Lambda * ResultX - v) % N );
    
    return Result;
}

Point Point::operator*( const BigInteger &n )
{
    if( n == 0 || Zero ) return Point( Parent, true );
    
    else if( n % 2 == 1 )
    {
        return *this + *this * (n - 1);
    }
    else
    {
        return (*this + *this) * (n / 2);
    }
}

void Point::Print()
{
    std::cout << "(" << X << ", " << Y << ") " << "On curve: " << Parent->TestPoint( *this ) << std::endl;
}

////
// Elliptic curve
////

Curve::Curve( const BigInteger &_A, const BigInteger &_B, const BigUnsigned &_N ) :
A( _A ), B( _B ), N( _N ), P( this, false )
{
}


// Random curve
Curve::Curve( const BigUnsigned &_N ) : P( this, false ), N( _N )
{
    // Select random point, FIXME: use thread id as random seed, should mean
    // less collisions
    srand( (unsigned int)time( NULL ) );
    P.X = BigInteger( rand() ) % N;
    P.Y = BigInteger( rand() ) % N;


    // Select random coefficients
    A = BigInteger( rand() ) % N;
    B = (P.Y * P.Y - P.X  * P.X  * P.X  - A * P.X) % N;
    
    //std::cout << "A: " << A << " B: " << B << std::endl;
}

bool Curve::TestPoint( const Elliptic::Point &P )
{
    if( P.Zero )
        return true;

    return (((P.Y*P.Y) % N) == ((P.X*P.X*P.X + A*P.X + B) % N));
}

Curve::~Curve()
{
    
}