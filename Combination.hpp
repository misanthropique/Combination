/**
 * Copyright ©2021-2022. Brent Weichel. All Rights Reserved.
 * Permission to use, copy, modify, and/or distribute this software, in whole
 * or part by any means, without express prior written agreement is prohibited.
 */
#pragma once

#include <cstddef>
#include <iterator>
#include <utility>
#include <vector>

/**
 * Class for enumerating over the subset combinations
 * of a set/vector/array/etc. While this class doesn't return the
 * elements of a container that would ideally be the subject of
 * subsetting, it does return a vector of offsets to select elements
 * of the subject class from.
 *
 * As an example of use:
 *     size_t index = 1;
 *     std::vector< char > characters { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
 *     for ( const auto& subset : Combination( characters.size(), 4 ) ) {
 *         std::cout << "The characters in the " << index << "-(st,nd,rd,th) are:";
 *         for ( size_t offset : subset ) {
 *             std::cout << " " << characters[ offset ]; }
 *         std::cout << std::endl; }
 *
 * Note:
 *   - Requires C++14 and above.
 */
class Combination
{
private:
	size_t mNumberElements;
	size_t mSubsetSize;

	void _copyAssign(
		const Combination& other )
	{
		mNumberElements = other.mNumberElements;
		mSubsetSize = other.mSubsetSize;
	}

	void _moveAssign(
		Combination&& other )
	{
		mNumberElements = std::exchange( other.mNumberElements, 0 );
		mSubsetSize = std::exchange( other.mSubsetSize, 0 );
	}

public:
	/**
	 * Iterator class for enumerating over the subsets
	 * of a collection.
	 */
	class const_iterator
	{
	private:
		size_t mNumberElements;
		size_t mSubsetSize;
		std::vector< size_t > mEnumeration;

		const_iterator(
			bool end,
			size_t numberElements,
			size_t subsetSize )
		{
			size_t offset = end * ( numberElements - mSubsetSize );
			mNumberElements = numberElements;
			mSubsetSize = subsetSize;
			mEnumeration.resize( mSubsetSize );
			for ( size_t index( mSubsetSize ); index--;
				mEnumeration[ index ] = offset + index );
		}

		void _copyAssign(
			const const_iterator& other )
		{
			mEnumeration = other.mEnumeration;
			mNumberElements = other.mNumberElements;
			mSubsetSize = other.mSubsetSize;
		}

		void _moveAssign(
			const_iterator&& other )
		{
			mEnumeration = std::move( other.mEnumeration );
			mNumberElements = std::exchange( other.mNumberElements, 0 );
			mSubsetSize = std::exchange( other.mSubsetSize, 0 );
		}

	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type   = std::ptrdiff_t;
		using value_type        = const std::vector< size_t >;
		using pointer           = const std::vector< size_t >*;
		using reference         = const std::vector< size_t >&;

		/**
		 * Default constructor.
		 */
		const_iterator()
		{
			mNumberElements = 0;
			mSubsetSize = 0;
		}

		/**
		 * Move constructor.
		 * @param other R-Value to the iterator to move.
		 */
		const_iterator(
			const_iterator&& other )
		{
			_moveAssign( std::move( other ) );
		}

		/**
		 * Copy constructor.
		 * @param other Const reference to the iterator to copy.
		 */
		const_iterator(
			const const_iterator& other )
		{
			_copyAssign( other );
		}

		/**
		 * Move assignment.
		 * @param other R-Value to the iterator to move.
		 * @return Reference to this iterator instance.
		 */
		const_iterator& operator=(
			const_iterator&& other )
		{
			if ( this != &other )
			{
				_moveAssign( std::move( other ) );
			}

			return *this;
		}

		/**
		 * Copy assignment.
		 * @param other Const reference to the iterator to copy.
		 * @return Reference to this iterator instance.
		 */
		const_iterator& operator=(
			const const_iterator& other )
		{
			if ( this != &other )
			{
				_copyAssign( other );
			}

			return *this;
		}

		/**
		 * Equality operator.
		 * @param other Const reference to the iterator to compare against.
		 * @return Return true if {@param other} compares equal to this iterator instance.
		 */
		bool operator==(
			const const_iterator& other ) const
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
			const const_iterator& other ) const
		{
			return not this->operator==( other );
		}

		/**
		 * Member redirect.
		 * @return Const pointer to the enumeration.
		 */
		pointer operator->() const
		{
			return &mEnumeration;
		}

		/**
		 * Dereference operator.
		 * @return Const reference to the enumeration.
		 */
		reference operator*() const
		{
			return mEnumeration;
		}

		/**
		 * Post-increment operator.
		 * @return iterator to the prior enumeration.
		 */
		const_iterator operator++( int )
		{
			const_iterator previous( *this );
			this->operator++();
			return previous;
		}

		/**
		 * Pre-increment operator.
		 * @return Reference to this iterator instance.
		 */
		const_iterator& operator++()
		{
			size_t index;
			for ( index = 0;
				index < mSubsetSize
					&& mEnumeration[ index ] >= ( mNumberElements - index );
				++index );

			if ( index != mSubsetSize )
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
			const_iterator& other )
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
		_moveAssign( std::move( other ) );
	}

	/**
	 * Copy constructor.
	 * @param other Const reference to the Combination to copy.
	 */
	Combination(
		const Combination& other )
	{
		_copyAssign( other );
	}

	/**
	 * Beginning iterator.
	 * @return Iterator to the beginning of the combination enumeration.
	 */
	const_iterator begin() const
	{
		return const_iterator( false, mNumberElements, mSubsetSize );
	}

	/**
	 * End iterator.
	 * @return Iterator to the end of the combination enumeration.
	 */
	const_iterator end() const
	{
		return const_iterator( true, mNumberElements, mSubsetSize );
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
	 * Move assignment operator.
	 * @param other R-Value to the Combination object to move to this instance.
	 * @return Reference to this Combination object is returned.
	 */
	Combination& operator=(
		Combination&& other )
	{
		if ( this != &other )
		{
			_moveAssign( std::move( other ) );
		}

		return *this;
	}

	/**
	 * Copy assignment operator.
	 * @param other Const reference to the Combination object to copy to this instance.
	 * @return Reference to this Combination object is returned.
	 */
	Combination& operator=(
		const Combination& other )
	{
		if ( this != &other )
		{
			_copyAssign( other );
		}

		return *this;
	}

	/**
	 * The number of elements to choose from.
	 * @return The subset size.
	 */
	size_t subsetSize() const
	{
		return mSubsetSize;
	}
};
