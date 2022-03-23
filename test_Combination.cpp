/**
 * Copyright ©2022. Brent Weichel. All Rights Reserved.
 * Permission to use, copy, modify, and/or distribute this software, in whole
 * or part by any means, without express prior written agreement is prohibited.
 */
#include <gtest/gtest.h>
#include <utility>

#include "Combination.hpp"

/**
 * Notes:
 *   - Requires that gtest is installed on the system.
 *
 * To compile the test
 *     $ g++ test_Combination.cpp -L/usr/lib/ -lgtest -lgtest_main -pthread -o test_all
 *
 * Then to run the test
 *     $ ./test_all
 */

TEST( Combination, DefaultConstructor )
{
	Combination combination;

	EXPECT_EQ( 0, combination.numberElements() );
	EXPECT_EQ( 0, combination.subsetSize() );
}

TEST( Combination, MoveConstructor )
{
	Combination moveCombination( 7, 4 );

	EXPECT_EQ( 7, moveCombination.numberElements() );
	EXPECT_EQ( 4, moveCombination.subsetSize() );

	Combination defaultCombination( std::move( moveCombination ) );

	EXPECT_EQ( 7, defaultCombination.numberElements() );
	EXPECT_EQ( 4, defaultCombination.subsetSize() );

	EXPECT_EQ( 0, moveCombination.numberElements() );
	EXPECT_EQ( 0, moveCombination.subsetSize() );
}

TEST( Combination, CopyConstructor )
{
	Combination copyCombination( 7, 4 );

	EXPECT_EQ( 7, copyCombination.numberElements() );
	EXPECT_EQ( 4, copyCombination.subsetSize() );

	Combination defaultCombination( copyCombination );

	EXPECT_EQ( 7, defaultCombination.numberElements() );
	EXPECT_EQ( 4, defaultCombination.subsetSize() );

	EXPECT_EQ( 7, copyCombination.numberElements() );
	EXPECT_EQ( 4, copyCombination.subsetSize() );
}

TEST( Combination, beginShouldReturnConstIteratorEqualToEndForDefaultConstructedCombination )
{
	Combination defaultCombination;

	EXPECT_EQ( defaultCombination.begin(), defaultCombination.end() );
}

TEST( Combination, beginShouldReturnConstIteratorEqualToEndForNumberElementsLessThanSubsetSize )
{
	Combination defaultCombination( 3, 7 );

	EXPECT_EQ( defaultCombination.begin(), defaultCombination.end() );
}

TEST( Combination, beginShouldReturnConstIteratorEqualToEndForNumberElementsEqualsZero )
{
	Combination defaultCombination( 0, 7 );

	EXPECT_EQ( defaultCombination.begin(), defaultCombination.end() );
}

TEST( Combination, beginShouldReturnIteratorNotEqualToEndForNumberElementsGreaterThanOrEqualToSubsetSizeAndNumberElementsGreaterThanZero )
{
	Combination defaultCombination( 7, 4 );

	EXPECT_NE( defaultCombination.begin(), defaultCombination.end() );
}

TEST( Combination, numberElementsShouldReturnZeroForDefaultConstructedCombination )
{
	Combination defaultCombination;

	EXPECT_EQ( 0, defaultCombination.numberElements() );
}

TEST( Combination, numberElementsShouldReturnSetValueForParameterDefaultConstructor )
{
	Combination defaultCombination( 7, 0 );

	EXPECT_EQ( 7, defaultCombination.numberElements() );
}

TEST( Combination, MoveAssignment )
{
	Combination defaultCombination;
	Combination moveAssign( 7, 4 );

	EXPECT_EQ( 7, moveAssign.numberElements() );
	EXPECT_EQ( 4, moveAssign.subsetSize() );
	EXPECT_EQ( 0, defaultCombination.numberElements() );
	EXPECT_EQ( 0, defaultCombination.subsetSize() );

	defaultCombination = std::move( moveAssign );

	EXPECT_EQ( 0, moveAssign.numberElements() );
	EXPECT_EQ( 0, moveAssign.subsetSize() );
	EXPECT_EQ( 7, defaultCombination.numberElements() );
	EXPECT_EQ( 4, defaultCombination.subsetSize() );
}

TEST( Combination, CopyAssignment )
{
	Combination defaultCombination;
	Combination copyAssign( 7, 4 );

	EXPECT_EQ( 7, copyAssign.numberElements() );
	EXPECT_EQ( 4, copyAssign.subsetSize() );
	EXPECT_EQ( 0, defaultCombination.numberElements() );
	EXPECT_EQ( 0, defaultCombination.subsetSize() );

	defaultCombination = copyAssign;

	EXPECT_EQ( 7, copyAssign.numberElements() );
	EXPECT_EQ( 4, copyAssign.subsetSize() );
	EXPECT_EQ( 7, defaultCombination.numberElements() );
	EXPECT_EQ( 4, defaultCombination.subsetSize() );
}

TEST( Combination, subsetSizeShouldReturnZeroForDefaultConstructedCombination )
{
	Combination defaultCombination;

	EXPECT_EQ( 0, defaultCombination.subsetSize() );
}

TEST( Combination, subsetSizeShouldReturnSetValueForParameterDefaultConstructor )
{
	Combination defaultCombination( 7, 4 );

	EXPECT_EQ( 4, defaultCombination.subsetSize() );
}

int main( int argc, char** argv )
{
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}
