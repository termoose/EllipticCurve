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

/*
namespace Elliptic
{
    // Forward declaration
    template< typename T >
    class Curve;
    
    ////
    // Class for the curve points
    ////
    template< typename T >
    class Point
    {
    public:
        Point( Curve< T >* _Parent = nullptr ) : Zero( false ), x( 0 ), y( 0 ), Parent( _Parent )
        {
        }
        
        ~Point() { }
        
        Point operator+( const Point< T >& Other )
        {
            Elliptic::Point< T > Result( Other.Parent );
            
            // Only add the points if they belong to the same curve
            if( Parent != Other.Parent )
            {
                std::cerr << "Incompatible curve points!" << std::endl;
                return Point< T >( nullptr );
            }
            
            if( x != Other.x )
            {
                
            }
            
            return Point< T >( nullptr );
        }
        
        // Curve points
        T x;
        T y;
        
        bool Zero;
        Curve< T >* Parent;
    };
    
    ////
    // Class for the elliptic curve
    ////
    template< typename T >
    class Curve
    {
    public:
        Curve( const T& _N ) : N( _N ), P( this )
        {
            srand( (unsigned int)time(nullptr) );
            
            // T needs to have a constructor that takes type "int" as argument
            T X = T( rand() ) % N;
            T Y = T( rand() ) % N;
            
            P.x = X;
            P.y = Y;
            
            // Select random coefficients
            A = T( rand() ) % N;
            B = (Y * Y - X * X * X - A * X) % N;
            
            std::cout << "Initial point: (" << X << ", " << Y << ")" << std::endl;
            std::cout << "Correct point: " << (((Y*Y) % N) == ((X*X*X + A*X + B) % N)) << std::endl;
            std::cout << "Random curve y^2 = x^3 + " << A << "x + " << B << std::endl;
        }
        
        ~Curve() { }
        
        T GetA() { return A; }
        T GetB() { return B; }
        T GetN() { return N; }
        
        Point< T > GetPoint() { return P; }
        
    private:
        // The ring size Z/NZ
        T N;
        
        // Coefficients of y^2 = x^3 + Ax + B
        T A;
        T B;
        
        Point< T > P;
    };
    
};*/

namespace Elliptic
{
    class Curve;

    class Point
    {
    public:
        Point( Curve *Parent = nullptr );
        ~Point();
        
        void SetPoint( const BigInteger &_X, const BigInteger &_Y );
        
        Point operator+( const Point &Other );
        
        bool IsZero() { return Zero; }
        
        BigInteger X;
        BigInteger Y;

    private:    
        Curve *Parent;
        
        bool Zero;
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
