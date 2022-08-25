
#ifndef _gHash_H
#define _gHash_H


#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>

namespace graphics{



    class  gHash
    {
		uint64_t _value;
      static unsigned counter;

      // Make this version of append private, and don't define it
      // If this isn't defined, then the compiler will auto-convert calls to 
      // append with a void* to bool, which is not what is probably intended
      //void append(const void* data);

    public:

      gHash() : _value(~0ULL) {}
      gHash(const gHash &h) : _value(h._value) {}
      gHash(uint64_t v) : _value(v) {}
      const gHash& operator=(const gHash& h) { _value = h._value;
                                             return *this; }

      void reset() { _value = ~0ULL; }
      void reset(uint64_t v) { _value = v; }

      bool operator==(const gHash& h) const { return _value == h._value; }
      bool operator!=(const gHash& h) const { return _value != h._value; }
      bool operator<(const gHash& h) const { return _value < h._value; }
      uint64_t value() const { return _value; }
      uint64_t getHash() const { return _value; }

      // Should probably deprecate this. If you're using it, it's probably not what you really want
      void append(const void* data, size_t length);


      void append(const std::string& s) { append((void*)s.c_str(), s.size() + 1); }
 
      void append(int);
      void append(unsigned);
      void append(float);
      void append(double);
      void append(const gHash&);
      void append(const std::set<int>& intset);
      void append(const std::map<int, int>& iimap);
      void append(uint64_t);

      template<class T>
      void append(const std::vector<T>& vec)
      {
        register unsigned size = (unsigned)vec.size();
        append(size);
        for (size_t i = 0; i < size;++i){
          append(vec[i]);
        }
      }

      template<class T>
      gHash& operator << (const T& v) { append(v);
                                       return *this; }

      void newvalue() { _value = ++counter; }
    };

}

inline std::ostream& operator << (std::ostream& o, const graphics::gHash& h)
{
  return o << std::hex << h.value() << std::dec;
}

#endif
