#ifndef STRDECT_INL
#define STRDECT_INL

#include <algorithm>

template <typename Container, typename ValueType>
bool StrDect(const Container& container, const ValueType& value) { return std::find(std::begin(container), std::end(container), value) != std::end(container); }

#endif
