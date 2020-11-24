#include <utility>
namespace usu
{

    template <typename T>
    class shared_ptr
    {
        int referenced = 0;

      public:
        T* raw;
        int* ref = &referenced;

        shared_ptr(T* ptr)
        {
            raw = ptr;
            (*ref)++;
        }
        shared_ptr(const shared_ptr& s2)
        {
            raw = s2.raw;
            ref = s2.ref;
            (*ref)++;
            //s2.ref = ref;
        }
        shared_ptr(shared_ptr&& s)
        {
            raw = s.raw;
            ref = s.ref;
            //(*ref)++;

            s.raw = nullptr;
            s.raw = 0;
        }
        ~shared_ptr()
        {
            if (raw != nullptr)
            {
                (*ref)--;
                if (*ref <= 0)
                {
                    raw = nullptr;
                }
            }
        }

        void operator=(shared_ptr&& rhs)
        {
            std::swap(raw, rhs.raw);
            std::swap(ref, rhs.ref);
        }

        shared_ptr& operator=(const shared_ptr& s)
        {
            raw = s.raw;
            ref = s.ref;
            (*ref)++;
            return *this;
        }

        T* operator->() const
        {
            return raw;
        }

        T& operator*()
        {
            return *raw;
        }

        T* get()
        {
            return raw;
        }

        int use_count()
        {
            return *ref;
        }
    };

    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args&&... args)
    {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template <typename T>
    class shared_ptr<T[]>
    {
        T* raw;
        int elements = 0;
        int ref = 0;

      public:
        shared_ptr(T* ptr, int arraySize)
        {
            raw = ptr;
            elements = arraySize;
            ref++;
        }
        ~shared_ptr()
        {
            delete[] raw;
        }
        T& operator[](int index)
        {
            return raw[index];
        }
        int size()
        {
            return elements;
        }
    };
    template <typename T, unsigned int N>
    shared_ptr<T[]> make_shared_array()
    {
        return shared_ptr<T[]>(new T[N], N);
    }

} // namespace usu