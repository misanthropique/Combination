/**
 * Copyright ©2021. Brent Weichel. All Rights Reserved.
 * Permission to use, copy, modify, and/or distribute this software, in whole
 * or part by any means, without express prior written agreement is prohibited.
 */
#pragma once

#include <cstddef>
#include <iterator>
#include <utility>
#include <vector>

class Combination
{
private:
	size_t mNumberElements;
	size_t mSubsetSize;

public:
	/**
	 * Iterator class for enumerating over the subsets
	 * of a collection.
	 */
	class iterator
	{
	private:
		size_t mNumberElements;
		size_t mSubsetSize;
		std::vector< size_t > mEnumeration;

		iterator(
			bool begin,
			size_t numberElements,
			size_t subsetSize )
		{
			
		}

	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = std::vector< size_t >;
		using pointer = std::vector< size_t >*;
		using reference = std::vector< size_t >&;

		/**
		 * Deleted default constructor.
		 */
		iterator() = delete;

		/**
		 * Move constructor.
		 * @param other R-Value to the iterator to move.
		 */
		iterator(
			iterator&& other )
		{
			mEnumeration = std::move( other.mEnumeration );
			mNumberElements = std::exchange( other.mNumberElements, 0 );
			mSubsetSize = std::exchange( other.mSubsetSize, 0 );
		}

		/**
		 * Copy constructor.
		 * @param other Const reference to the iterator to copy.
		 */
		iterator(
			const iterator& other )
		{
			mEnumeration = other.mEnumeration;
			mNumberElements = other.mNumberElements;
			mSubsetSize = other.mSubsetSize;
		}

		/**
		 * Move assignment.
		 * @param other R-Value to the iterator to move.
		 * @return Reference to this iterator instance.
		 */
		iterator& operator=(
			iterator&& other )
		{
			if ( this != &other )
			{
				mEnumeration = std::move( other.mEnumeration );
				mNumberElements = std::exchange( other.mNumberElements, 0 );
				mSubsetSize = std::exchange( other.mSubsetSize, 0 );
			}

			return *this;
		}

		/**
		 * Copy assignment.
		 * @param other Const reference to the iterator to copy.
		 * @return Reference to this iterator instance.
		 */
		iterator& operator=(
			const iterator& other )
		{
			if ( this != &other )
			{
				mEnumeration = other.mEnumeration;
				mNumberElements = other.mNumberElements;
				mSubsetSize = other.mSubsetSize;
			}

			return *this;
		}

		/**
		 * Equality operator.
		 * @param other Const reference to the iterator to compare against.
		 * @return Return true if {@param other} compares equal to this iterator instance.
		 */
		bool operator==(
			const iterator& other ) const
		{
			return ( mNumberElements == other.mNumberElements )
				and ( mSubsetSize == other.mSubsetSize )
				and ( mEnumeration == other.mEnumeration );
		}

		/**
		 * Inequality operator.
		 * @param other Const reference to the iterator to compare against.
		 * @return Return true if {@param other} compares not equal to this iterator instance.
		 */
		bool operator!=(
			const iterator& other ) const
		{
			return not this->operator==( other );
		}

		/**
		 * Member redirect.
		 * @return Const pointer to the enumeration.
		 */
		const pointer operator->()
		{
			return &mEnumeration;
		}

		/**
		 * Dereference operator.
		 * @return Const reference to the enumeration.
		 */
		const reference operator*() const
		{
			return mEnumeration;
		}

		/**
		 * Post-increment operator.
		 * @return iterator to the prior enumeration.
		 */
		iterator operator++( int )
		{
			iterator previous( *this );
			this->operator++();
			return previous;
		}

		/**
		 * Pre-increment operator.
		 * @return Reference to this iterator instance.
		 */
		iterator& operator++()
		{
			size_t index;
			for ( index = 0;
				index < mNumberElements
					&& mEnumeration[ index ] >= ( mNumberElements - index );
				++index );

			if ( index != mNumberElements )
			{
				for ( mEnumeration[ index ]++; index--;
					mEnumeration[ index ] = mEnumeration[ index + 1 ] + 1 );
			}

			return *this;
		}

		/**
		 * Swap this iterator with another.
		 * @param other Reference to the iterator to swap with.
		 */
		void swap(
			iterator& other )
		{
			std::swap( mNumberElements, other.mNumberElements );
			std::swap( mSubsetSize, other.mSubsetSize );
			std::swap( mEnumeration, other.mEnumeration );
		}
	};

	/**
	 * Default constructor.
	 * @param numberElements Number of elements to choose from. [default: 0]
	 * @param subsetSize Numer of element to choose. [default: 0]
	 */
	Combination(
		size_t numberElements = 0,
		size_t subsetSize = 0 )
	{
		mNumberElements = numberElements;
		mSubsetSize = subsetSize;
	}

	/**
	 * Move constructor.
	 * @param other R-Value to the Combination to move.
	 */
	Combination(
		Combination&& other )
	{
		mNumberElements = std::exchange( other.mNumberElements, 0 );
		mSubsetSize = std::exchange( other.mSubsetSize, 0 );
	}

	/**
	 * Copy constructor.
	 * @param other Const reference to the Combination to copy.
	 */
	Combination(
		cont Combination& other )
	{
		mNumberElements = other.mNumberElements;
		mSubsetSize = other.mSubsetSize;
	}

	/**
	 * The number of elements.
	 * @return The number of elements.
	 */
	size_t numberElements() const
	{
		return mNumberElements;
	}

	/**
	 * The number of elements to choose from.
	 * @return The subset size.
	 */
	size_t subsetSize() const
	{
		return mSubsetSize;
	}

	/**
	 * Beginning iterator.
	 * @return Iterator to the beginning of the combination enumeration.
	 */
	iterator begin() const
	{
		return iterator( true, mNumberElements, mSubsetSize );
	}

	/**
	 * End iterator.
	 * @return Iterator to the end of the combination enumeration.
	 */
	iterator end() const
	{
		return iterator( false, mNumberElements, mSubsetSize );
	}
};
