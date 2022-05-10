#ifndef __ALGOS_H__
#define __ALGOS_H__

#include <functional>
#include <iterator>

/**
  Default comparator is std::greater, this will check ascending order
*/
template <typename ForwardIterator,
          typename Comp = std::greater<typename ForwardIterator::value_type>>
bool isSorted(ForwardIterator start, ForwardIterator end, Comp comp = Comp{}) {
    if (start != end) {
        ForwardIterator next = std::next(start);
        for (; next != end; ++next, ++start) {
            if (comp(*start, *next)) return false;
        }
    }
    return true;
}

#endif
