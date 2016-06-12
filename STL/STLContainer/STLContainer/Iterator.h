#pragma once

struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag {};
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};

template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct Iterator
{
	typedef Category IteratorCategory;
	typedef T ValueType;
	typedef Distance DifferenceType;
	typedef Pointer Pointer;
	typedef Reference Reference;
};

template<class Iterator>
struct IteratorTraits
{
	typedef typename Iterator::IteratorCategory IteratorCategory;
	typedef typename Iterator::ValueType ValueType;
	typedef typename Iterator::DifferenceType DifferenceType;
	typedef typename Iterator::Pointer Pointer;
	typedef typename Iterator::Reference Reference;
};

//偏特化原生指针
template<class T>
struct IteratorTraits<T*>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T ValueType;
	typedef ptrdiff_t DifferenceType;
	typedef T* Pointer;
	typedef T& Reference;
};

//偏特化const原生指针
template<class T>
struct IteratorTraits<const T*>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T ValueType;
	typedef ptrdiff_t DifferenceType;
	typedef const T* Pointer;
	typedef const T& Reference;
};

//Distance的实现
template<class InputIterator>
inline typename IteratorTraits<InputIterator>::DifferenceType
__Distance(InputIterator first, InputIterator last, InputIteratorTag)
{
	IteratorTraits<InputIterator>::Difference n = 0;
	while (first != last)
	{
		++first;
		++n;
	}
	return n;
}

template<class RandomAccessIterator>
inline typename IteratorTraits<RandomAccessIterator>::DifferenceType
__Distance(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIteratorTag)
{
	return last - first;
}

template<class InputIterator>
inline typename IteratorTraits<InputIterator>::DifferenceType
Distance(InputIterator first, InputIterator last)
{
	return __Distance(first, last, Iterator<InputIterator>::IteratorCategory());
}

//Advance的实现

template<class InputIterator, class Distance>
inline void __Advance(InputIterator& i, Distance n, InputIteratorTag)
{
	while (n--)
	{
		++i;
	}
}

template<class BidirectionalIterator, class Distance>
inline void __Advance(BidirectionalIterator& i, Distance n, BidirectionalIteratorTag)
{
	if (n >= 0)
	{
		while (n--)
		{
			++i;
		}
	}
	else
	{
		while (n++)
		{
			--i;
		}
	}
}

template <class BidirectionalIterator, class Distance>
inline void __Advance(BidirectionalIterator& i, Distance n, RandomAccessIteratorTag)
{
	i += n;
}

template<class InputIterator, class Distance>
inline void Advance(InputIterator& i, Distance n)
{
	__Advance(i, n, IteratorTraits<InputIterator>::IteratorCategory());
}

//返回迭代器的类型
template<class Iterator>
inline typename IteratorTraits<Iterator>::IteratorCategory
IteratorCategory(const Iterator&)
{
	return IteratorTraits<Iterator>::IteratorCategory();
}

template<class Iterator>
inline typename IteratorTraits<Iterator>::ValueType*
DistanceType(const Iterator&)
{
	return static_cast<typename IteratorTraits<Iterator>::Difference*>(0);
}

template<class Iterator>
inline typename IteratorTraits<Iterator>::ValueType*
ValueType(const Iterator&)
{
	return static_cast<typename IteratorTraits<Iterator>::ValueType*> (0);
}

template <class Iterator>
class ReverseIterator
{
protected:
	Iterator _current;
public:
	typedef typename IteratorTraits<Iterator>::IteratorCategory IteratorCategory;
	typedef typename IteratorTraits<Iterator>::ValueType ValueType;
	typedef typename IteratorTraits<Iterator>::DifferenceType DifferenceType;
	typedef typename IteratorTraits<Iterator>::Pointer Pointer;
	typedef typename IteratorTraits<Iterator>::Reference Reference;

	typedef Iterator IteratorType;
	typedef ReverseIterator<Iterator> Self;

public:
	ReverseIterator() {}
	explicit ReverseIterator(IteratorType x) : _current(x) {}

	Reference operator*() const {
		Iterator tmp = _current;
		return *--tmp;
	}

	Pointer operator->() const { return &(operator*()); }

	Self& operator++() {
		--_current;
		return *this;
	}
	Self operator++(int) {
		Self tmp = *this;
		--_current;
		return tmp;
	}
	Self& operator--() {
		++_current;
		return *this;
	}
	Self operator--(int) {
		Self tmp = *this;
		++_current;
		return tmp;
	}

	bool operator != (Self& s)
	{
		return _current != s._current;
	}

	bool operator == (Self& s)
	{
		return _current == s._current;
	}
};