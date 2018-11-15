#ifndef NEW_AND_DELETE
#define NEW_AND_DELETE

#include <new>

void * operator new(size_t n) throw(std::bad_alloc);
void operator delete(void * p, size_t n) throw();
template<class Container>
void testContainer();
void testNewAndDelete();

#endif //NEW_AND_DELETE