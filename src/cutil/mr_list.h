#ifndef MACRAYKV_CUTIL_LIST_H_
#define MACRAYKV_CUTIL_LIST_H_
#include "mr_utils.h"
namespace cutil
{
  template <class T, class Allocator>
  class MrList;

  namespace list
  {
    template <class T>
    struct Node 
    {
      typedef Node* ptr_t;
      typedef const Node* const_ptr_t;
      ptr_t next;
      ptr_t prev;
      T data;
    };

    template <class List>
    class ConstIterator
    {
      typedef ConstIterator<List> self_t;
      public:
        typedef typename List::value_iterator value_type;
        typedef typename List::const_pointer pointer;
        typedef typename List::const_reference reference;
      private:
        typedef typename List::iterator iterator;
        typedef Node<value_type> node_t;
        typedef typename node_t::ptr_t node_ptr_t;
        typedef typename node_t::const_ptr_t node_const_ptr_t;
        friend class MrList<value_type, typename List::allocator_t>;
      public:
        ConstIterator() : node_(NULL) 
        {
        }
        ConstIterator(const self_t &other)
        {
          *this = other;
        }
        self_t &operator = (const self_t &other)
        {
          node_ = other.node_;
          return *this;
        }
        ConstIterator(const iterator &other)
        {
          *this = other;
        }
        self_t &operator = (const iterator &other)
        {
          node_ = other.node_;
          return *this;
        }
        ConstIterator(node_ptr_t node)
        {
          node_ = node;
        }
        ConstIterator(node_const_ptr_t node)
        {
          node_ = const_cast<node_ptr_t>(node);
        }
      public:
        reference operator *() const
        {
          // if refer the end()?
          return node_->data;
        }
        pointer operator ->() const
        {
          // if refer the end()?
          return &(node_->data);
        }
        bool operator ==(const self_t &other) const
        {
          return (node_ == other.node_);
        }
        bool operator !=(const self_t &other) const
        {
          return (node_ != other.node_);
        }
        self_t &operator ++()
        {
          // if loop list end will point to head
          node_ = node_->next;
          return *this;
        }
        self_t operator ++(int)
        {
          self_t tmp = *this;
          node_ = node_->next;
          return tmp;
        }
        self_t &operator --()
        {
          node_ = node_->prev;
          return *this;
        }
        self_t operator --(int)
        {
          self_t tmp = *this;
          node_ = node_->prev;
          return tmp;
        }
      private:
        node_ptr_t node_;
    };
    
    template <class List>
    class Iterator
    {
      typedef Iterator<List> self_t;
      public:
        typedef typename List::value_type value_type;
        typedef typename List::pointer pointer;
        typedef typename List::reference reference;
      private:
        typedef typename List::const_iterator const_iterator;
        typedef Node<value_type> node_t;
        typedef typename node_t::ptr_t node_ptr_t;
        typedef typename node_t::const_ptr_t node_const_ptr_t;
        friend class ConstIterator<List>;
        friend class MrList<value_type, typename List::allocator_t>;
      public:
        Iterator() : node_(NULL) {}
        Iterator(const self_t &other)
        {
          *this = other; // not good
        }
        self_t& operator =(const self_t &other)
        {
          node_ = other.node_;
          return *this;
        }
        Iterator(node_ptr_t node)
        {
          node_ = node;
        }
        Iterator(node_const_ptr_t node)
        {
          node_ = const_cast<node_ptr_t>(node);
        }
      public:
        reference operator *() const
        {
          // notice refer the end()
          return node_->data;
        }
        pointer operator ->() const
        {
          // notice refer the end() undefined
          return &(node_->data);
        }
        bool operator ==(const self_t &other) const
        {
          return (node_ == other.node_);
        }
        bool operator !=(const self_t &other) const
        {
          return (node_ != other.node_);
        }
        self_t &operator ++()
        {
          // notice loop list would point to head
          node_ = node_->next;
          return *this;
        }
        self_t operator ++(int)
        {
          // notice loop list would point to head
          self_t tmp = *this;
          node_ = node_->next;
          return tmp;
        }
        self_t operator --()
        {
          node_ = node_->prev;
          return *this;
        }
        self_t operator --(int)
        {
          self_t tmp = *this;
          node_ = node_->prev;
          return tmp;
        }
      private:
        node_ptr_t node_;
    };
  }

  template <class T>
  struct ListTypes
  {
    typedef list::Node<T> AllocType;
  };

  template <class T, 
            class Allocator = hash::SimpleAllocer<typename ListTypes<T>::AllocType> >
  class MrList
  {
    typedef MrList<T, Allocator> self_t;
    public:
      typedef T value_type;
      typedef value_type* pointer;
      typedef value_type& reference;
      typedef const value_type* const_pointer;
      typedef const value_type& const_reference;
      typedef list::Iterator<self_t> iterator;
      typedef list::ConstIterator<self_t> const_iterator;
      typedef Allocator allocator_t;

    private:
      typedef list::Node<value_type> node_t;
      typedef typename node_t::ptr_t node_ptr_t;
      typedef typename node_t::const_ptr_t node_const_ptr_t;

      typedef struct NodeHolder
      {
        node_ptr_t next;
        node_ptr_t prev;
        operator node_ptr_t()
        {
          return reinterpret_cast<node_ptr_t>(this);
        }
        operator node_const_ptr_t() const
        {
          return reinterpret_cast<node_const_ptr_t>(this);
        }
      } node_holder_t;

    private:
      MrList(const self_t &other);
      self_t &operator =(const self_t &other);

    public:
      MrList() : size_(0)
      {
        root_.next = root_;
        root_.prev = root_;
      }
      ~MrList() 
      {
        clear();
      }

    public:
      int push_back(const value_type &value)
      {
        int ret = 0;
        node_ptr_t pnode = allocator_.alloc();
        if (NULL == pnode)
        {
          ret = -1;
        }
        else
        {
          pnode->data = value;
          pnode->prev = root_.prev;
          pnode->next = root_;
          root_->prev->next = pnode;
          root_->prev = pnode;
          size_++;
        }
        return ret;
      }
      int push_front(const value_type &value)
      {
        int ret = 0;
        node_ptr_t* pnode = allocator_.alloc();
        if (NULL == pnode)
        {
          ret = -1;
        }
        else 
        {
          pnode->data = value;
          pnode->prev = root_;
          pnode->next = root_->next;
          root_->next->prev = pnode;
          root_->next = pnode;
          size_++;
        }
        return ret;
      }
      int pop_back(value_type &value)
      {
        int ret = 0;
        if (0 >= size_)
        {
          ret = -1;
        }
        else 
        {
          node_ptr_t pnode = root_.prev;
          root_.prev = pnode->prev;
          pnode->prev->next = root_;
          value = pnode->data;
          allocator_.free(pnode);
          size_--;
        }
        return ret;
      }
      int pop_back()
      {
        int ret = 0;
        if (0 >= size_)
        {
          ret = -1;
        }
        else 
        {
          node_ptr_t pnode = root_.prev;
          root_.prev = pnode->prev;
          pnode->prev->next = root_;
          allocator_.free(pnode);
          size_--;
        }
        return ret;
      }
      int pop_front()
      {
        int ret = 0;
        if (0 >= size_)
        {
          ret = -1;
        }
        else 
        {
          node_ptr_t pnode = root_.next;
          root_.next = pnode->next;
          pnode->next->prev = root_;
          allocator_.free(pnode);
          size_--;
        }
        return ret;
      }
      int pop_front(value_type &value)
      {
        int ret = 0;
        if (0 >= size_)
        {
          ret = -1;
        }
        else 
        {
          node_ptr_t pnode = root_.next;
          root_.next = pnode->next;
          pnode->next->prev = root_;
          value = pnode->data;
          allocator_.free(pnode);
          size_--;
        }
        return ret;
      }

      int insert(iterator iter, const value_type &value)
      {
        int ret = 0;
        node_ptr_t pnode = allocator_.alloc();
        if (NULL == pnode)
        {
          ret = -1;
        }
        else
        {
          pnode->data = value;
          pnode->next = iter.node_;
          pnode->prev = iter.node_->prev;
          iter.node_->prev->next = pnode;
          iter.node_->pre = pnode;
          size_++;
        }
        return ret;
      }

      int erase(iterator iter)
      {
        int ret = 0;
        if (0 >= size_ 
            || NULL == iter.node_
            || iter.node_ == (node_ptr_t)&root_)
        {
          ret = -1;
        }
        else 
        {
          node_ptr_t pnode = iter.node_;
          pnode->next->prev = pnode->prev;
          pnode->prev->next = pnode->next;
          allocator_.free(pnode);
          size_--;
        }
        return ret;
      }
      int erase(const value_type &value)
      {
        int ret = -1;
        for (iterator it = begin(); it != end(); ++it)
        {
          if (it.node_->data == value)
          {
            ret = erase(it);
            break;
          }
        }
        return ret;
      }
      iterator begin()
      { 
        return iterator(root_.next);
      }
      const_iterator begin() const 
      {
        return const_iterator(root_.next);
      }
      iterator end()
      {
        return iterator(root_);
      }
      const_iterator end() const
      {
        return const_iterator(root_);
      }
      void clear()
      {
        node_ptr_t iter = root_.next;
        while (iter != root_)
        {
          node_ptr_t pnode = iter->next;
          allocator_.free(iter);
          iter = pnode;
        }
        size_ = 0;
      }
      bool empty() const
      {
        return (0 == size_);
      }
      int64_t size() const
      {
        return size_;
      }

    private:
      node_holder_t root_;
      int64_t size_;
      allocator_t allocator_;
  };
}
#endif // MACRAYKV_CUTIL_LIST_H_
