#ifndef GENERICFACTORY_H
#define GENERICFACTORY_H

#include <iostream>
#include <map>
#include <memory>

/// GenericFactory: BASETYPE class must provide a virtual memberfunction
/// create(). The KEYTYPE class must be able to be used as a key in a std::map,
/// it must provide:
///   - copy and assignment semantics
///   - bool operator<() const;
template <class BASETYPE, typename KEYTYPE = std::string>
class GenericFactory
{
public:
   GenericFactory() = default;
   GenericFactory(const GenericFactory &) = delete;
   GenericFactory &operator=(const GenericFactory &) = delete;
   virtual ~GenericFactory() = default;

   bool add(const KEYTYPE &key, std::shared_ptr<BASETYPE> tbm);
   bool isAvailable(const KEYTYPE &key) const
   {
      return registry_.find(key) != end(registry_);
   }
   std::shared_ptr<BASETYPE> get(const KEYTYPE &key) const;
   std::shared_ptr<BASETYPE> create(const KEYTYPE &key) const;
   int size() const { return registry_.size(); }

private:
   using registry_t = std::map<const KEYTYPE, std::shared_ptr<BASETYPE>>;
   registry_t registry_;
};

/// Registers new BASETYPE derived pointer value if unique.
/// Client code is responsible for checking if this has happened.
template <class BASETYPE, typename KEYTYPE>
bool GenericFactory<BASETYPE, KEYTYPE>::add(const KEYTYPE &key,
                                            std::shared_ptr<BASETYPE> pTbm)
{
   if (isAvailable(key)) {
      return false;
   }
   registry_[key] = pTbm;
   return true;
}

/// Returns pointer to added object (if key is registrated).
/// Client code is responsible for checking returned pointer value,
/// Only use this value if it does not equals the nullptr value.
template <class BASETYPE, typename KEYTYPE>
std::shared_ptr<BASETYPE>
GenericFactory<BASETYPE, KEYTYPE>::get(const KEYTYPE &key) const
{
   std::shared_ptr<BASETYPE> pB = nullptr;

   auto iterf = registry_.find(key);
   if (iterf != end(registry_)) {
      pB = iterf->second;
   }
   return pB;
}

/// Returns pointer to created object (if key is registrated).
/// Client code is responsible for checking returned pointer value,
/// Only use this value if it does not equals the nullptr value.
template <class BASETYPE, typename KEYTYPE>
std::shared_ptr<BASETYPE>
GenericFactory<BASETYPE, KEYTYPE>::create(const KEYTYPE &key) const
{
   std::shared_ptr<BASETYPE> pB = nullptr;

   auto iterf = registry_.find(key);
   if (iterf != end(registry_)) {
      pB = iterf->second->create();
   }
   return pB;
}

#endif
