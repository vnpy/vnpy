/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef shared_ptr_h_INCLUDED
#define shared_ptr_h_INCLUDED

//
// Implements a subset of shared_prt found at www.boost.org.
// Uses a singly linked circular list instead of a reference counter.
// Avoids extra heap allocation needed to get a shared reference counter,
// but sizeof(shared_ptr) == sizeof(void*) * 3 compared to sizeof(void*) * 2
//
// See "Handles and Exception Safety, Part 4: Tracking References without Counters"
// by Andrew Koenig and Barbara E. Moo, Feb. 2003 C++ Users Journal
//

namespace ibapi {

namespace shared_ptr_defs {

class Use {
public:

   Use() { forward_ = this; back_ = this; }
   ~Use() { remove(); }

   Use(const Use& u) { insert(u); }
   Use& operator=(const Use& u)
   {
      if (this != &u) {
         remove();
         insert(u);
      }
      return *this;
   }
   bool only() const { return this == this->forward_; }
private:
   mutable const Use *forward_;
   mutable const Use *back_;

   void insert(const Use& u) const {
      this->back_ = &u;
      this->forward_ = u.forward_;
      u.forward_->back_ = this;
      u.forward_ = this;
   }

   void remove() const {
      this->forward_->back_ = this->back_;
      this->back_->forward_ = this->forward_;
   }
};

} // end of namespace shared_ptr_defs

template<typename X> class shared_ptr {
public:

   typedef shared_ptr_defs::Use Use;

   template<typename Y> friend class shared_ptr;

   explicit shared_ptr(X* ptr = 0) : ptr_(ptr) {}

   ~shared_ptr() { if (use_.only()) delete ptr_; }

   template<typename Y>
   shared_ptr(const shared_ptr<Y>& other)
      : ptr_(other.ptr_),
        use_(other.use_)
      {}

   shared_ptr& operator=(const shared_ptr& other) {
      if ( &use_ == &other.use_ ) { return *this; }
      if ( use_.only() ) { delete ptr_; }
      use_ = other.use_;
      ptr_ = other.ptr_;
      return *this;
   }

   X& operator*()  const { return *ptr_; }
   X* operator->() const { return ptr_; }
   X* get()        const { return ptr_; }
   bool only() const { return use_.only(); }

   void reset(X* ptr = 0) {
      if ( use_.only() ) { delete ptr_; }
      ptr_ = ptr;
      use_ = Use();
   }

   //封装添加
   bool operator==(const shared_ptr<X> & a)
   {
	   return a.get() == this->get();
   }

   bool operator!=(const shared_ptr<X> & a)
   {
	   return a.get() != this->get();
   }

private:

   X *ptr_;
   Use use_;
};


} //end of namespace ibapi


#else
//#include <memory>
//using std::shared_ptr;
#endif /* shared_ptr_h_INCLUDED */