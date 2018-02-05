/*
 * Copyright (C) 2015 Martijn van Dorp
 *
 * This file is part of CFlat.Core.
 *
 * CFlat.Core is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CFlat.Core is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//! @file Pointers.h

#ifndef CFLAT_CORE_LANGUAGE_POINTERS_H
#define CFLAT_CORE_LANGUAGE_POINTERS_H

#include "CFlat/Language/Assert.h"
#include "CFlat/Language/Functions.h"
#include "CFlat/Language/Integer.h"

#include <utility>

namespace CFlat
{
/* Forward declarations */
    template<typename T>
    class weak_ptr;

    /* Types */
    template<typename T>
    class IDeleter {
    public:
        inline virtual ~IDeleter()
        {
        }

        virtual void operator()(T* ptr) const = 0;
    };

    template<typename T>
    class NoOpDeleter : public IDeleter<T> {
    public:
        inline void operator()(T*) const override
        {
        }

        template<typename U>
        void operator()(U *) const
        {
        }
    };

    template<typename T>
    class DefaultDeleter : public IDeleter<T> {
    public:
        inline DefaultDeleter() {}

        template<typename U>
        inline DefaultDeleter(const DefaultDeleter<U>&) {}

        inline void operator()(T* ptr) const override
        {
            delete ptr;
        }

        template<typename U>
        inline void operator()(U *ptr) const
        {
            delete ptr;
        }
    };

    template<typename T>
    class DefaultDeleter<T[]> : public IDeleter<T> {
    public:
        inline DefaultDeleter() {}

        template<typename U>
        inline DefaultDeleter(const DefaultDeleter<U[]>&) {}

        inline void operator()(T* ptr) const override
        {
            delete[] ptr;
        }

        template<typename U>
        inline void operator()(U *ptr) const
        {
            delete[] ptr;
        }
    };

    template<typename T, typename TDeleter>
    class DeleterWrapper : public IDeleter<T> {
    private:
        TDeleter _deleter;

    public:
        inline explicit DeleterWrapper(TDeleter deleter) : _deleter(deleter)
        {
        }

        inline void operator()(T* ptr) const override
        {
            _deleter(ptr);
        }
    };

    template<typename T>
    class refcount_t {
    private:
        /* Fields */
        long _useCount;
        long _weakCount;
        T* _ptr;
        IDeleter<T> *_deleter;

    public:
        /* Constructors */
        inline explicit refcount_t(IDeleter<T> *deleter) :
            _useCount(1),
            _weakCount(1),
            _ptr(nullptr),
            _deleter(deleter)
        {
            assert(deleter != nullptr);
        }

        // TODO: Find a neater way to handle overloading here
        // template<typename Deleter, typename = std::enable_if_t<std::is_convertible<Deleter, IDeleter<T>*>::value>>
        template<typename Deleter>
        inline refcount_t(T* p, Deleter deleter) :
            refcount_t(p, deleter, std::is_convertible<Deleter, IDeleter<T>*>())
        {
        }
        
        inline refcount_t(T* p, IDeleter<T> *deleter, std::true_type) :
            _useCount(1),
            _weakCount(1),
            _ptr(p),
            _deleter(deleter)
        {
            assert(deleter != nullptr);
        }

        template<typename Deleter>
        inline refcount_t(T* p, Deleter deleter, std::false_type) :
            _useCount(1),
            _weakCount(1),
            _ptr(p),
            _deleter(new DeleterWrapper<T, Deleter>(deleter))
        {
        }

        template<typename U>
        inline refcount_t(const refcount_t<U>& other) :
            _useCount(other._useCount),
            _weakCount(other._weakCount),
            _ptr(other._ptr),
            _deleter(other._deleter)
        {
        }

        /* Methods */
        inline T* Get() const
        {
            return _ptr;
        }

        inline IDeleter<T>* GetDeleter()
        {
            return _deleter;
        }

        inline const IDeleter<T>* GetDeleter() const
        {
            return _deleter;
        }

        inline long UseCount() const
        {
            return _useCount;
        }

        inline long WeakCount()const
        {
            return _weakCount;
        }

        inline void Dispose()
        {
            this->GetDeleter()->operator()(this->Get());
        }

        inline void Delete()
        {
            delete this->GetDeleter();
            delete this;
        }

        inline void AddRef()
        {
            _useCount++;
        }

        inline void Release()
        {
            _useCount--;

            if (_useCount <= 0) {
                this->Dispose();
                this->WeakRelease();
            }
        }

        inline void WeakAddRef()
        {
            _weakCount++;
        }

        inline void WeakRelease()
        {
            _weakCount--;

            if (_weakCount <= 0) {
                this->Delete();
            }
        }
    };

    template<typename T, typename TDeleter = DefaultDeleter<T>>
    class unique_ptr_base {
    private:
        template<typename U, typename UDeleter>
        friend class unique_ptr_base;

        /* Fields */
        T* _ptr;
        TDeleter _deleter;

    public:
        /* Constructor */
        inline unique_ptr_base(T *ptr) :
            _ptr(ptr),
            _deleter(TDeleter())
        {
            static_assert(!std::is_pointer<TDeleter>::value, "Deleter is null pointer.");
        }

        template<typename Deleter>
        inline unique_ptr_base(T *ptr, Deleter deleter) :
            _ptr(ptr),
            _deleter(deleter)
        {
        }

        inline unique_ptr_base(const unique_ptr_base& ptr) = delete;

        /* Destructor */
        inline virtual ~unique_ptr_base()
        {
            this->Reset();
        }

        /* Operators */
        inline explicit operator bool() const
        {
            return this->Get() != nullptr;
        }

        /* Methods */
        inline T* Get() const
        {
            return _ptr;
        }

        inline TDeleter& GetDeleter()
        {
            return _deleter;
        }

        inline const TDeleter& GetDeleter() const
        {
            return _deleter;
        }

        inline void Reset(T* p = nullptr)
        {
            if (this->Get() != p) {
                this->GetDeleter()(this->Get());

                _ptr = p;
            }
        }

        inline void Swap(unique_ptr_base& r)
        {
            std::swap(_ptr, r._ptr);
            std::swap(_deleter, r._deleter);
        }

        static inline void Swap(const unique_ptr_base& lhs, const unique_ptr_base& rhs)
        {
            lhs.Swap(rhs);
        }

        inline T* Release()
        {
            T* ptr = this->Get();

            _ptr = nullptr;

            return ptr;
        }
    };

    template<typename T, typename TDeleter = DefaultDeleter<T>>
    class unique_ptr : public unique_ptr_base<T, TDeleter> {
    private:
        template<typename U, typename UDeleter>
        friend class unique_ptr;

    public:
        /* Constructors */
        inline unique_ptr() : unique_ptr_base<T, TDeleter>(nullptr)
        {
        }

        inline unique_ptr(std::nullptr_t) : unique_ptr_base<T, TDeleter>(nullptr)
        {
        }

        inline explicit unique_ptr(T* ptr) : unique_ptr_base<T, TDeleter>(ptr)
        {
        }

        template<typename Deleter>
        inline unique_ptr(T* ptr, Deleter deleter) : unique_ptr_base<T, TDeleter>(ptr, deleter)
        {
        }

        template<typename U, typename UDeleter>
        inline unique_ptr(unique_ptr<U, UDeleter>&& ptr) : unique_ptr_base<T, TDeleter>(ptr.Release(), ptr.GetDeleter())
        {
        }

        /* Copy constructor */
        inline unique_ptr(const unique_ptr& ptr) = delete;

        /* Move constructor */
        inline unique_ptr(unique_ptr&& ptr) : unique_ptr_base<T, TDeleter>(ptr.Release(), ptr.GetDeleter())
        {
        }
        
        /* Operators */
        inline unique_ptr& operator=(const unique_ptr& r) = delete;

        inline unique_ptr& operator=(unique_ptr&& r)
        {
            this->Reset(r.Release());
            this->GetDeleter() = std::move(r.GetDeleter());

            return *this;
        }

        inline unique_ptr& operator=(std::nullptr_t)
        {
            this->Reset();

            return *this;
        }

        template<typename U, typename UDeleter>
        inline unique_ptr& operator=(unique_ptr<U, UDeleter>&& r)
        {
            this->Reset(r.Release());
            this->GetDeleter() = std::move(r.GetDeleter());

            return *this;
        }

        inline T& operator*() const
        {
            return *this->Get();
        }

        inline T* operator->() const
        {
            return this->Get();
        }
    };

    template<typename T, typename TDeleter>
    class unique_ptr<T[], TDeleter> : public unique_ptr_base<T, TDeleter> {
    private:
        template<typename U, typename UDeleter>
        friend class unique_ptr;

    public:
        /* Constructors */
        inline unique_ptr() : unique_ptr_base<T, TDeleter>(nullptr)
        {
        }

        inline unique_ptr(std::nullptr_t) : unique_ptr_base<T, TDeleter>(nullptr)
        {
        }

        inline explicit unique_ptr(T* ptr) : unique_ptr_base<T, TDeleter>(ptr)
        {
        }

        template<typename Deleter>
        inline unique_ptr(T* ptr, Deleter deleter) : unique_ptr_base<T, TDeleter>(ptr, deleter)
        {
        }

        template<typename U, typename UDeleter>
        inline unique_ptr(unique_ptr<U[], UDeleter>&& ptr) : unique_ptr_base<T, TDeleter>(ptr.Release(), ptr.GetDeleter())
        {
        }

        /* Copy constructor */
        inline unique_ptr(const unique_ptr& ptr) = delete;

        /* Move constructor */
        inline unique_ptr(unique_ptr&& ptr) : unique_ptr_base<T, TDeleter>(ptr.Release(), ptr.GetDeleter())
        {
        }

        /* Operators */
        inline unique_ptr& operator=(const unique_ptr& r) = delete;

        inline unique_ptr& operator=(unique_ptr&& r)
        {
            this->Reset(r.Release());
            this->GetDeleter() = std::move(r.GetDeleter());

            return *this;
        }

        inline unique_ptr& operator=(std::nullptr_t)
        {
            this->Reset();

            return *this;
        }

        template<typename U, typename UDeleter>
        inline unique_ptr& operator=(unique_ptr<U[], UDeleter>&& r)
        {
            this->Reset(r.Release());
            this->GetDeleter() = std::move(r.GetDeleter());

            return *this;
        }

        inline T& operator[](uintsize index) const
        {
            return this->Get()[index];
        }
    };

    template<typename T>
    class shared_ptr {
    private:
        /* Fields */
        T* _ptr;
        refcount_t<T>* _counter;

        /* Friends */
        template<typename U> friend class shared_ptr;
        template<typename U> friend class weak_ptr;

    public:
        /* Constructors */
        inline shared_ptr() :
            _ptr(nullptr),
            _counter(nullptr)
        {
        }

        inline shared_ptr(std::nullptr_t) :
            _ptr(nullptr),
            _counter(nullptr)
        {
        }

        template<typename Deleter>
        inline shared_ptr(std::nullptr_t, Deleter deleter) :
            _ptr(nullptr),
            _counter(nullptr)
        {
        }

        inline explicit shared_ptr(T* p) :
            _ptr(p),
            _counter(p ? new refcount_t<T>(p, new DefaultDeleter<T>()) : nullptr)
        {
        }

        template<typename Deleter>
        inline shared_ptr(T* p, Deleter deleter) :
            _ptr(p),
            _counter(p ? new refcount_t<T>(p, deleter) : nullptr)
        {
        }

        template<typename U>
        inline shared_ptr(const shared_ptr<U>& ptr) :
            _ptr(ptr._ptr),
            _counter(ptr._counter)
        {
            if (_counter) { _counter->AddRef(); }
        }

        template<typename U>
        inline shared_ptr(shared_ptr<U>&& ptr) :
            _ptr(nullptr),
            _counter(nullptr)
        {
            std::swap(_ptr, ptr._ptr);
            std::swap(_counter, ptr._counter);
        }

        template<typename U>
        inline explicit shared_ptr(const weak_ptr<U>& ptr) :
            _ptr(ptr.Expired() ? nullptr : ptr._counter->Get()),
            _counter(ptr.Expired() ? nullptr : ptr._counter)
        {
            if (_counter) { _counter->AddRef(); }
        }

        template<typename U>
        inline explicit shared_ptr(weak_ptr<U>&& ptr) :
            _ptr(nullptr),
            _counter(nullptr)
        {
            if (!ptr.Expired) {
                _ptr = _counter->Get();

                std::swap(_counter, ptr._counter);
            }
        }

        template<typename U, typename UDeleter>
        inline shared_ptr(unique_ptr<U, UDeleter>&& ptr) :
            _ptr(ptr.Get()),
            _counter(ptr.Get() ? new refcount_t<T>(ptr.Get(), ptr.GetDeleter()) : nullptr)
        {
            ptr.Release();
        }

        /* Copy constructor */
        inline shared_ptr(const shared_ptr& ptr) :
            _ptr(ptr._ptr),
            _counter(ptr._counter)
        {
            if (_counter) { _counter->AddRef(); }
        }

        /* Move constructor */
        inline shared_ptr(shared_ptr&& ptr) :
            _ptr(nullptr),
            _counter(nullptr)
        {
            std::swap(_ptr, ptr._ptr);
            std::swap(_counter, ptr._counter);
        }

        /* Destructor */
        inline ~shared_ptr()
        {
            if (_counter) { _counter->Release(); }
        }

        /* Operators */
        inline shared_ptr& operator=(const shared_ptr& r)
        {
            if (_counter != r._counter) {
                if (r._counter) { r._counter->AddRef(); }
                if (_counter) { _counter->Release(); }

                _ptr = r._ptr;
                _counter = r._counter;
            }

            return *this;
        }

        inline shared_ptr& operator=(shared_ptr&& r)
        {
            if (_counter != r._counter) {
                std::swap(_ptr, r._ptr);
                std::swap(_counter, r._counter);
            }

            return *this;
        }

        template<typename U>
        inline shared_ptr& operator=(const shared_ptr<U>& r)
        {
            if (_counter != r._counter) {
                if (r._counter) { r._counter->AddRef(); }
                if (_counter) { _counter->Release(); }

                _ptr = r._ptr;
                _counter = r._counter;
            }

            return *this;
        }

        template<typename U>
        inline shared_ptr& operator=(shared_ptr<U>&& r)
        {
            if (_counter != r._counter) {
                std::swap(_ptr, r._ptr);
                std::swap(_counter, r._counter);
            }

            return *this;
        }

        inline T& operator*() const
        {
            return* _ptr;
        }

        inline T* operator->() const
        {
            return _ptr;
        }

        inline explicit operator bool() const
        {
            return _ptr != nullptr;
        }

        /* Properties */
        inline long UseCount()const
        {
            return _counter ? _counter->UseCount() : 0;
        }

        inline bool Unique() const
        {
            return this->UseCount() == 1;
        }

        /* Methods */
        inline T* Get() const
        {
            return _ptr;
        }

        inline void Reset(T* p = nullptr)
        {
            if (_ptr != p) {
                if (_counter) { _counter->Release(); }

                _ptr = p;
                _counter = p ? new refcount_t<T>(p, new DefaultDeleter<T>()) : nullptr;
            }
        }

        template<typename Deleter>
        inline void Reset(T* p, Deleter deleter)
        {
            if (_ptr != p) {
                if (_counter) { _counter->Release(); }

                _ptr = p;
                _counter = p ? new refcount_t<T>(p, deleter) : nullptr;
            }
        }

        inline void Swap(shared_ptr& r)
        {
            std::swap(_ptr, r._ptr);
            std::swap(_counter, r._counter);
        }

        static inline void Swap(const shared_ptr& lhs, const shared_ptr& rhs)
        {
            lhs.Swap(rhs);
        }
    };

    template<typename T>
    class shared_ptr<T[]> {
    private:
        /* Fields */
        T* _ptr;
        refcount_t<T>* _counter;

        /* Friends */
        template<typename U> friend class shared_ptr;
        template<typename U> friend class weak_ptr;

    public:
        /* Constructors */
        inline shared_ptr() :
            _ptr(nullptr),
            _counter(nullptr)
        {
        }

        inline shared_ptr(std::nullptr_t) :
            _ptr(nullptr),
            _counter(nullptr)
        {
        }

        template<typename Deleter>
        inline shared_ptr(std::nullptr_t, Deleter deleter) :
            _ptr(nullptr),
            _counter(nullptr)
        {
        }

        inline explicit shared_ptr(T* p) :
            _ptr(p),
            _counter(p ? new refcount_t<T>(p, new DefaultDeleter<T[]>()) : nullptr)
        {
        }

        template<typename Deleter>
        inline shared_ptr(T* p, Deleter deleter) :
            _ptr(p),
            _counter(p ? new refcount_t<T>(p, deleter) : nullptr)
        {
        }

        template<typename U>
        inline shared_ptr(const shared_ptr<U>& ptr) :
            _ptr(ptr._ptr),
            _counter(ptr._counter)
        {
            if (_counter) { _counter->AddRef(); }
        }

        template<typename U>
        inline shared_ptr(shared_ptr<U>&& ptr) : shared_ptr(std::move(ptr))
        {
        }

        template<typename U>
        inline explicit shared_ptr(const weak_ptr<U>& ptr) :
            _ptr(ptr.Expired() ? nullptr : ptr._counter->Get()),
            _counter(ptr.Expired() ? nullptr : ptr._counter)
        {
            if (_counter) { _counter->AddRef(); }
        }

        template<typename U>
        inline explicit shared_ptr(weak_ptr<U>&& ptr) :
            _ptr(nullptr),
            _counter(nullptr)
        {
            if (!ptr.Expired) {
                _ptr = _counter->Get();

                std::swap(_counter, ptr._counter);
            }
        }
        
        template<typename U, typename UDeleter>
        inline shared_ptr(unique_ptr<U, UDeleter>&& ptr) :
            _ptr(ptr.Get()),
            _counter(ptr.Get() ? new refcount_t<T>(ptr.Get(), ptr.GetDeleter()) : nullptr)
        {
            ptr.Release();
        }

        /* Copy constructor */
        inline shared_ptr(const shared_ptr& ptr) :
            _ptr(ptr._ptr),
            _counter(ptr._counter)
        {
            if (_counter) { _counter->AddRef(); }
        }

        /* Move constructor */
        inline shared_ptr(shared_ptr&& ptr) :
            _ptr(nullptr),
            _counter(nullptr)
        {
            std::swap(_ptr, ptr._ptr);
            std::swap(_counter, ptr._counter);
        }

        /* Destructor */
        inline ~shared_ptr()
        {
            if (_counter) { _counter->Release(); }
        }

        /* Operators */
        inline shared_ptr& operator=(const shared_ptr& r)
        {
            if (_counter != r._counter) {
                if (r._counter) { r._counter->AddRef(); }
                if (_counter) { _counter->Release(); }

                _ptr = r._ptr;
                _counter = r._counter;
            }

            return *this;
        }

        inline shared_ptr& operator=(shared_ptr&& r)
        {
            if (_counter != r._counter) {
                std::swap(_ptr, r._ptr);
                std::swap(_counter, r._counter);
            }

            return *this;
        }

        template<typename U>
        inline shared_ptr& operator=(const shared_ptr<U>& r)
        {
            if (_counter != r._counter) {
                if (r._counter) { r._counter->AddRef(); }
                if (_counter) { _counter->Release(); }

                _ptr = r._ptr;
                _counter = r._counter;
            }

            return *this;
        }

        template<typename U>
        inline shared_ptr& operator=(shared_ptr<U>&& r)
        {
            if (_counter != r._counter) {
                std::swap(_ptr, r._ptr);
                std::swap(_counter, r._counter);
            }

            return *this;
        }

        inline T& operator[](uintsize index) const
        {
            return this->Get()[index];
        }

        inline explicit operator bool() const
        {
            return _ptr != nullptr;
        }

        /* Properties */
        inline long UseCount()const
        {
            return _counter ? _counter->UseCount() : 0;
        }

        inline bool Unique() const
        {
            return this->UseCount() == 1;
        }

        /* Methods */
        inline T* Get() const
        {
            return _ptr;
        }

        inline void Reset(T* p = nullptr)
        {
            if (_ptr != p) {
                if (_counter) { _counter->Release(); }

                _ptr = p;
                _counter = p ? new refcount_t<T>(p, new DefaultDeleter<T[]>()) : nullptr;
            }
        }

        template<typename Deleter>
        inline void Reset(T* p, Deleter deleter)
        {
            if (_ptr != p) {
                if (_counter) { _counter->Release(); }

                _ptr = p;
                _counter = p ? new refcount_t<T>(p, deleter) : nullptr;
            }
        }

        inline void Swap(shared_ptr& r)
        {
            std::swap(_ptr, r._ptr);
            std::swap(_counter, r._counter);
        }

        static inline void Swap(const shared_ptr& lhs, const shared_ptr& rhs)
        {
            lhs.Swap(rhs);
        }
    };

    template<typename T>
    class weak_ptr {
    private:
        /* Fields */
        refcount_t<T>* _counter;

        /* Friends */
        template<typename U> friend class shared_ptr;

    public:
        /* Constructors */
        inline weak_ptr() : _counter(nullptr)
        {
        }

        template<typename U>
        inline weak_ptr(const weak_ptr<U>& r) : _counter(r._counter)
        {
            if (_counter) { _counter->WeakAddRef(); }
        }

        template<typename U>
        inline weak_ptr(const shared_ptr<U>& r) : _counter(r._counter)
        {
            if (_counter) { _counter->WeakAddRef(); }
        }

        /* Copy constructor */
        inline weak_ptr(const weak_ptr& r) : _counter(r._counter)
        {
            if (_counter) { _counter->WeakAddRef(); }
        }

        /* Move constructor */
        inline weak_ptr(weak_ptr&& r) : _counter(nullptr)
        {
            std::swap(_counter, r._counter);
        }

        /* Destructor */
        inline ~weak_ptr()
        {
            if (_counter) { _counter->WeakRelease(); }
        }

        /* Operators */
        inline weak_ptr& operator=(const weak_ptr& r)
        {
            if (_counter != r._counter) {
                if (r._counter) { r._counter->WeakAddRef(); }
                if (_counter) { _counter->WeakRelease(); }

                _counter = r._counter;
            }

            return *this;
        }

        inline weak_ptr& operator=(weak_ptr&& r)
        {
            if (_counter != r._counter) {
                std::swap(_counter, r._counter);
            }

            return *this;
        }

        template<typename U>
        inline weak_ptr& operator=(const weak_ptr<U>& r)
        {
            if (_counter != r._counter) {
                if (r._counter) { r._counter->WeakAddRef(); }
                if (_counter) { _counter->WeakRelease(); }

                _counter = r._counter;
            }

            return *this;
        }

        template<typename U>
        inline weak_ptr& operator=(const shared_ptr<U>& r)
        {
            if (_counter != r._counter) {
                if (r._counter) { r._counter->WeakAddRef(); }
                if (_counter) { _counter->WeakRelease(); }

                _counter = r._counter;
            }

            return *this;
        }

        /* Properties */
        inline long UseCount() const
        {
            return _counter ? _counter->UseCount() : 0;
        }

        inline bool Expired() const
        {
            return this->UseCount() == 0;
        }

        inline bool Unique() const
        {
            return this->UseCount() == 1;
        }

        /* Methods */
        inline shared_ptr<T> Lock() const
        {
            return this->Expired() ? shared_ptr<T>() : shared_ptr<T>(*this);
        }

        inline void Reset()
        {
            if (_counter) { _counter->WeakRelease(); }

            _counter = nullptr;
        }

        inline void Swap(weak_ptr& r)
        {
            std::swap(_counter, r._counter);
        }

        static inline void Swap(const weak_ptr& lhs, const weak_ptr& rhs)
        {
            lhs.Swap(rhs);
        }
    };

    /* Compare two unique_ptr objects */
    template<typename T, typename TDeleter, typename U, typename UDeleter>
    inline bool operator ==(const unique_ptr<T, TDeleter>& lhs, const unique_ptr<U, UDeleter>& rhs)
    {
        return lhs.Get() == rhs.Get();
    }

    template<typename T, typename TDeleter, typename U, typename UDeleter>
    inline bool operator !=(const unique_ptr<T, TDeleter>& lhs, const unique_ptr<U, UDeleter>& rhs)
    {
        return !operator==(lhs, rhs);
    }

    template<typename T, typename TDeleter, typename U, typename UDeleter>
    inline bool operator <(const unique_ptr<T, TDeleter>& lhs, const unique_ptr<U, UDeleter>& rhs)
    {
        return lhs.Get() < rhs.Get();
    }

    template<typename T, typename TDeleter, typename U, typename UDeleter>
    inline bool operator >(const unique_ptr<T, TDeleter>& lhs, const unique_ptr<U, UDeleter>& rhs)
    {
        return operator<(rhs, lhs);
    }

    template<typename T, typename TDeleter, typename U, typename UDeleter>
    inline bool operator <=(const unique_ptr<T, TDeleter>& lhs, const unique_ptr<U, UDeleter>& rhs)
    {
        return !operator>(lhs, rhs);
    }

    template<typename T, typename TDeleter, typename U, typename UDeleter>
    inline bool operator >=(const unique_ptr<T, TDeleter>& lhs, const unique_ptr<U, UDeleter>& rhs)
    {
        return !operator<(lhs, rhs);
    }

    /* Compare a unique_ptr with a null pointer */
    template<typename T, typename TDeleter>
    inline bool operator ==(const unique_ptr<T, TDeleter>& lhs, const std::nullptr_t& rhs)
    {
        return lhs.Get() == rhs;
    }

    template<typename T, typename TDeleter>
    inline bool operator ==(const std::nullptr_t& lhs, const unique_ptr<T, TDeleter>& rhs)
    {
        return lhs == rhs.Get();
    }

    template<typename T, typename TDeleter>
    inline bool operator !=(const unique_ptr<T, TDeleter>& lhs, const std::nullptr_t& rhs)
    {
        return !operator==(lhs, rhs);
    }

    template<typename T, typename TDeleter>
    inline bool operator !=(const std::nullptr_t& lhs, const unique_ptr<T, TDeleter>& rhs)
    {
        return !operator==(lhs, rhs);
    }

    template<typename T, typename TDeleter>
    inline bool operator <(const unique_ptr<T, TDeleter>& lhs, const std::nullptr_t& rhs)
    {
        return lhs.Get() < rhs;
    }

    template<typename T, typename TDeleter>
    inline bool operator <(const std::nullptr_t& lhs, const unique_ptr<T, TDeleter>& rhs)
    {
        return lhs < rhs.Get();
    }

    template<typename T, typename TDeleter>
    inline bool operator >(const unique_ptr<T, TDeleter>& lhs, const std::nullptr_t& rhs)
    {
        return operator<(rhs, lhs.Get());
    }

    template<typename T, typename TDeleter>
    inline bool operator >(const std::nullptr_t& lhs, const unique_ptr<T, TDeleter>& rhs)
    {
        return operator<(rhs.Get(), lhs);
    }

    template<typename T, typename TDeleter>
    inline bool operator <=(const unique_ptr<T, TDeleter>& lhs, const std::nullptr_t& rhs)
    {
        return !operator>(lhs.Get(), rhs);
    }

    template<typename T, typename TDeleter>
    inline bool operator <=(const std::nullptr_t& lhs, const unique_ptr<T, TDeleter>& rhs)
    {
        return !operator>(lhs, rhs.Get());
    }

    template<typename T, typename TDeleter>
    inline bool operator >=(const unique_ptr<T, TDeleter>& lhs, const std::nullptr_t& rhs)
    {
        return !operator<(lhs.Get(), rhs);
    }

    template<typename T, typename TDeleter>
    inline bool operator >=(const std::nullptr_t& lhs, const unique_ptr<T, TDeleter>& rhs)
    {
        return !operator<(lhs, rhs.Get());
    }

    /* Compare two shared_ptr objects */
    template<typename T, typename U>
    inline bool operator ==(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
        return lhs.Get() == rhs.Get();
    }

    template<typename T, typename U>
    inline bool operator !=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
        return !operator==(lhs, rhs);
    }

    template<typename T, typename U>
    inline bool operator <(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
        return lhs.Get() < rhs.Get();
    }

    template<typename T, typename U>
    inline bool operator >(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
        return operator<(rhs, lhs);
    }

    template<typename T, typename U>
    inline bool operator <=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
        return !operator>(lhs, rhs);
    }

    template<typename T, typename U>
    inline bool operator >=(const shared_ptr<T>& lhs, const shared_ptr<U>& rhs)
    {
        return !operator<(lhs, rhs);
    }

    /* Compare a shared_ptr with a null pointer */
    template<typename T>
    inline bool operator ==(const shared_ptr<T>& lhs, const std::nullptr_t& rhs)
    {
        return lhs.Get() == rhs;
    }

    template<typename T>
    inline bool operator ==(const std::nullptr_t& lhs, const shared_ptr<T>& rhs)
    {
        return lhs == rhs.Get();
    }

    template<typename T>
    inline bool operator !=(const shared_ptr<T>& lhs, const std::nullptr_t& rhs)
    {
        return !operator==(lhs, rhs);
    }

    template<typename T>
    inline bool operator !=(const std::nullptr_t& lhs, const shared_ptr<T>& rhs)
    {
        return !operator==(lhs, rhs);
    }

    template<typename T>
    inline bool operator <(const shared_ptr<T>& lhs, const std::nullptr_t& rhs)
    {
        return lhs.Get() < rhs;
    }

    template<typename T>
    inline bool operator <(const std::nullptr_t& lhs, const shared_ptr<T>& rhs)
    {
        return lhs < rhs.Get();
    }

    template<typename T>
    inline bool operator >(const shared_ptr<T>& lhs, const std::nullptr_t& rhs)
    {
        return operator<(rhs, lhs.Get());
    }

    template<typename T>
    inline bool operator >(const std::nullptr_t& lhs, const shared_ptr<T>& rhs)
    {
        return operator<(rhs.Get(), lhs);
    }

    template<typename T>
    inline bool operator <=(const shared_ptr<T>& lhs, const std::nullptr_t& rhs)
    {
        return !operator>(lhs.Get(), rhs);
    }

    template<typename T>
    inline bool operator <=(const std::nullptr_t& lhs, const shared_ptr<T>& rhs)
    {
        return !operator>(lhs, rhs.Get());
    }

    template<typename T>
    inline bool operator >=(const shared_ptr<T>& lhs, const std::nullptr_t& rhs)
    {
        return !operator<(lhs.Get(), rhs);
    }

    template<typename T>
    inline bool operator >=(const std::nullptr_t& lhs, const shared_ptr<T>& rhs)
    {
        return !operator<(lhs, rhs.Get());
    }
}

#endif
