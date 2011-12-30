//
//  EllipticCurve.h
//  EllipticCurve
//
//  Created by Ole Andre Birkedal on 12/26/11.
//  Copyright (c) 2011 Extab. All rights reserved.
//

#ifndef EllipticCurve_EllipticCurve_h
#define EllipticCurve_EllipticCurve_h

#include "BigIntegerLibrary.hh"

namespace Elliptic
{
    class Curve;

    class Point
    {
    public:
        Point( BigInteger _X, BigInteger _Y, Curve *_Parent = nullptr );
        Point( Curve *_Parent = nullptr );
        ~Point();
        
        void SetPoint( const BigInteger &_X, const BigInteger &_Y );
        
        BigInteger GetOrder() const;
        
        Point operator-( void );
        Point operator+( const Point& Other );
        Point operator*( const BigInteger& n );
        
        BigInteger X;
        BigInteger Y;
        
        bool Zero;

    private:    
        Curve *Parent;

    };

    class Curve
    {
    public:
        Curve( const BigInteger &_A, const BigInteger &_B, const BigUnsigned &_N );
        Curve( const BigUnsigned &_N );
        ~Curve();
        
        Point GetCurvePoint() { return P; }
        
        BigInteger GetA() const { return A; }
        BigInteger GetB() const { return B; }
        BigUnsigned GetN() const { return N; }
        
    private:
        // Coefficients of y^2 = x^3 + ax + b
        BigInteger A;
        BigInteger B;
        
        // The ring size Z/NZ
        BigUnsigned N;
        
        // Initial point
        Point P;
    };
    
}

#endif
