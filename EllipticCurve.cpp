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


////
// CurvePoint
////
/*
CurvePoint::CurvePoint( EllipticCurve *Parent ) : ParentCurve( Parent ), X( 0 ) , Y( 0 ), Zero( false )
{
}

CurvePoint::~CurvePoint()
{
}

void CurvePoint::SetPoint( const BigInteger &_X, const BigInteger &_Y )
{
    X = _X;
    Y = _Y;
}

CurvePoint CurvePoint::operator+( const CurvePoint &Other )
{
    CurvePoint Result( Other.ParentCurve );
    BigUnsigned N = Other.ParentCurve->GetN();
    
    // The points have to belong to the same curve
    if( ParentCurve != Other.ParentCurve )
    {
        std::cout << "Incompatible curve points!" << std::endl;
        return CurvePoint( nullptr );
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
        //std::cout << "Calculate modinv( " << BigInteger( 2 ) * Y << ", " << N << " )" << std::endl;
        BigInteger S = ( BigInteger( 3 ) * X * X - ParentCurve->GetA() * modinv( BigInteger( 2 ) * Y, N ) ) % N;
        
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

EllipticCurve::EllipticCurve( const BigInteger &_A, const BigInteger &_B, const BigUnsigned &_N ) :
A( _A ), B( _B ), N( _N ), P( this )
{
}


// Random curve
EllipticCurve::EllipticCurve( const BigUnsigned &_N ) : P( this ), N( _N )
{
    // Select random point
    srand( (unsigned int)time( NULL ) );
    BigInteger X = BigInteger( rand() ) % N;
    BigInteger Y = BigInteger( rand() ) % N;
    
    P.X = X;
    P.Y = Y;

    // Select random coefficients
    A = BigInteger( rand() ) % N;
    B = Y * Y - X * X * X - A * X;
    
    std::cout << "Random curve y^2 = x^3 + " << A << "x - " << -B << std::endl;
}

EllipticCurve::~EllipticCurve()
{
    
}*/