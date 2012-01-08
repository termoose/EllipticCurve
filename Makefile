all:
	clang++ -o Example bigint/BigInteger.cc bigint/BigIntegerAlgorithms.cc bigint/BigIntegerUtils.cc bigint/BigUnsigned.cc bigint/BigUnsignedInABase.cc EllipticCurve.cpp main.cpp -I bigint/ -std=c++0x -stdlib=libc++ -O3
