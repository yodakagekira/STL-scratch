#include "unique_ptr.hpp"

// Explicit instantiations (example)
template class unique_ptr<int>;
template class unique_ptr<double>;
template unique_ptr<int>    make_unique<int>();
template unique_ptr<double> make_unique<double>();