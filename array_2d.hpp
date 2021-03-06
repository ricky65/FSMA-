/* //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 * The following code declares class array_2d, an STL-like container which is a wrapper for built-in 2 dimensional arrays.
 *
 * Project homepage: https://github.com/ricky65/FSMA/
 *
 * Documentation can be located here: https://github.com/ricky65/FSMA/blob/master/README.md
 *
 * (C) Copyright Riccardo Marcangelo 2011 - 2017.
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ARRAY_2D
#define ARRAY_2D

#include <algorithm>
#include <stdexcept>
#include <iterator>

namespace fsma 
{
template <class T, std::size_t D1, std::size_t D2> 
struct array_2d
{
	typedef T value_type;
	typedef T * iterator;
	typedef const T * const_iterator;
	typedef T& reference;
	typedef const T& const_reference;
	typedef std::reverse_iterator<iterator>  reverse_iterator;
	typedef std::reverse_iterator<const_iterator>  const_reverse_iterator;
	typedef std::size_t size_type; //the type of the  subscript
	
	T elems[D1][D2];
	//No explicit construct/copy/destroy needed

	
	//iterator support
	iterator		begin()		   { return *elems; }//equivalent to &elems[0][0]
	const_iterator  begin()  const { return *elems; }
	const_iterator  cbegin() const { return *elems; }

	iterator end()				{ return begin() + size(); }
	const_iterator end()  const { return begin() + size(); }
	const_iterator cend() const { return begin() + size(); }

	//reverse iterator support
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
	const_reverse_iterator crbegin() const {return const_reverse_iterator(end());}

	reverse_iterator rend() {return reverse_iterator(begin()); }
	const_reverse_iterator rend() const {return const_reverse_iterator(begin());}
	const_reverse_iterator crend() const {return const_reverse_iterator(begin());}

	//front() and back()
	//return front element
	reference front() {return (elems[0][0]);}
	const_reference front() const {return elems[0][0];}
	
	//return back element
	reference back() {return (elems [D1 - 1][D2 - 1]);}
	const_reference back() const {return (elems [D1 - 1][D2 - 1]);}
	
	//capacity
	size_type size_1d() const //number of elements in 1st dimension (number of elements in a row)
	{return D1;}	
	size_type size_2d() const //number of elements in 2nd dimension (number of elements in a column)
	{return D2;}
	
	size_type size_row() const //synonym for size_1d()
	{return D1;}	
	size_type size_col() const //synonym for size_2d()
	{return D2;}

	size_type size() const//number of elements in array
	{return D1*D2;}
	size_type max_size() const 
	{return D1*D2;}
    bool      empty()    const { return false; }

	//element access
	reference operator()(int row, int col) { return elems[row][col]; } //non range checked access
	const_reference operator()(int row, int col ) const { return elems[row][col]; } //non range checked access

	reference at (int row, int col)// range-checked access
	{
		if (D1 <= row || D2 <= col)
			throw std::out_of_range ("array_2d: index out of range");
		return elems[row][col]; 
	};

	const_reference at (int row, int col) const// range-checked access
	{ 
		if (D1 <= row || D2 <= col)
			throw std::out_of_range ("array_2d: index out of range");
		return elems[row][col]; 
	};
	
	//data access
	T * data() { return *(elems); }// return address of first element
	const T * data() const { return *(elems); }// return address of first element

	//swap the contents of the arrays.
	void swap (array_2d<T,D1,D2>& y) {
		   std::swap_ranges(begin(),end(),y.begin());
	}

	// assignment with type conversion
	template <typename T2>
	array_2d <T,D1,D2>& operator= (const array_2d<T2,D1,D2>& rhs) {
		std::copy(rhs.begin(),rhs.end(), begin());
		return *this;
	}

	// assign one value to all elements
	void assign (const T& value) { fill ( value ); }    // A synonym for fill
	void fill   (const T& value)
	{
		std::fill_n(&elems[0][0],size(),value);
	}	

};

// comparisons
template <class T, std::size_t D1, std::size_t D2>
bool operator== (const array_2d<T,D1,D2>& x, const array_2d<T,D1,D2>& y) {
	return std::equal(x.begin(), x.end(), y.begin());
}

template <class T, std::size_t D1, std::size_t D2>
bool operator< (const array_2d<T,D1,D2>& x, const array_2d<T,D1,D2>& y) {
	return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}

template <class T, std::size_t D1, std::size_t D2>
bool operator!= (const array_2d<T,D1,D2>& x, const array_2d<T,D1,D2>& y) {
	return !(x==y);
}

template <class T, std::size_t D1, std::size_t D2>
bool operator> (const array_2d<T,D1,D2>& x, const array_2d<T,D1,D2>& y) {
	return y<x;
}

template <class T, std::size_t D1, std::size_t D2>
bool operator<= (const array_2d<T,D1,D2>& x, const array_2d<T,D1,D2>& y) {
	return !(y<x);
}

template <class T, std::size_t D1, std::size_t D2>
bool operator>= (const array_2d<T,D1,D2>& x, const array_2d<T,D1,D2>& y) {
	return !(x<y);
}

}// namespace fsma

#endif /* ARRAY_2D */
