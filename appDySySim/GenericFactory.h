#ifndef GENERICFACTORY_H
#define GENERICFACTORY_H

#include <iostream>
#include <map>
#include <memory>

/// GenericFactory: BASETYPE class must provide a virtual memberfunction
/// create(). The KEYTYPE class must be able to be used as a key in a std::map,
/// it must:
///   - implement copy and assignment semantics
///   - provide bool operator< () const;
template <class BASETYPE, typename KEYTYPE = std::string>
class GenericFactory
{
public:
   GenericFactory() = default;
   GenericFactory(const GenericFactory &other) = delete;
   GenericFactory &operator=(const GenericFactory &other) = delete;
   virtual ~GenericFactory();

   bool add(const KEYTYPE &key, BASETYPE *tbm);
   BASETYPE *create(const KEYTYPE &key) const;

   int size() const { return registry_.size(); }

private:
   using registry_t = std::map<const KEYTYPE, BASETYPE *>;
   registry_t registry_;
};

// template <class BASETYPE, typename KEYTYPE>
// GenericFactory<BASETYPE, KEYTYPE>::GenericFactory()
// {
// }

template <class BASETYPE, typename KEYTYPE>
GenericFactory<BASETYPE, KEYTYPE>::~GenericFactory()
{
}

template <class BASETYPE, typename KEYTYPE>
bool GenericFactory<BASETYPE, KEYTYPE>::add(const KEYTYPE &key, BASETYPE *pTbm)
{
   if (registry_.find(key) != end(registry_))
   {
      return false;
   }
   registry_[key] = pTbm;
   return true;
}

template <class BASETYPE, typename KEYTYPE>
BASETYPE *GenericFactory<BASETYPE, KEYTYPE>::create(const KEYTYPE &key) const
{
   BASETYPE *pB = nullptr;

   auto iterf = registry_.find(key);

   if (iterf != end(registry_)) {
      pB = iterf->second->create();
   }

   return pB; // client code is responsible for checking 0 value!
}

#endif
