#ifndef MACRAYKV_CUTIL_HASH_HASHUTILS_H_
#define MACRAYKV_CUTIL_HASH_HASHUTILS_H_
#include "memory_mod_define.h"
#include "memory.h"
namespace cutil
{
  namespace hash
  {
    struct DefaultSimpleAllocerAllocator
    {
      public:
        DefaultSimpleAllocerAllocator(int32_t mod_id = cutil::MemoryModIds::DEFAULT_MOD)
          : mod_id_(mod_id)
        {
        }
        void *alloc(const int64_t size) 
        {
          return tc_malloc(size, mod_id_);
        }
        void free(void *p)
        {
          tc_free(p);
        }
      private:
        int32_t mod_id_;
    };

    template <class T, int32_t NODE_NUM>
    class SimpleAllocerBlock;

    template <class T, int32_t NODE_NUM>
    struct SimpleAllocerNode
    {
      typedef SimpleAllocerNode<T, NODE_NUM> Node;
      typedef SimpleAllocerBlock<T, NODE_NUM> Block;

      T data;
      uint32_t magic1;
      Node *next;
      Block *block;
      uint32_t magic2;
    };

    template <class T, int32_t NODE_NUM>
    struct SimpleAllocerBlock
    {
      typedef SimpleAllocerNode<T, NODE_NUM> Node;
      typedef SimpleAllocerBlock<T, NODE_NUM> Block;

      int32_t ref_cnt;
      int32_t cur_pos;
      char node_buffer[NODE_NUM * sizeof(Node)];
      Node *nodes;
      Block *next;
    };

    template <bool B, class T>
    struct NodeNumTraits
    {
    };
    
    template <class T>
    struct NodeNumTraits<false, T>
    {
      static const int32_t NODE_NUM = 8; // left it to raywill
    };

    template <class T>
    struct NodeNumTraits<true, T>
    {
      static const int32_t NODE_NUM = 1; // left it to raywill
    };

    template <class T,
             int32_t NODE_NUM = NodeNumTraits<true, T>::NODE_NUM, //true or false would be decided by raywill
             class Allocer = DefaultSimpleAllocerAllocator>
    class SimpleAllocer
    {
      typedef SimpleAllocerNode<T, NODE_NUM> Node;
      typedef SimpleAllocerBlock<T, NODE_NUM> Block;
      const static uint32_t NODE_MAGIC1 = 0x89abcdef;
      const static uint32_t NODE_MAGIC2 = 0x12345678;
      public:
        SimpleAllocer() : block_list_head_(NULL), free_list_head_(NULL)
        {
        }
        ~SimpleAllocer()
        {
          clear();
        }
        void clear()
        {
          Block *iter = block_list_head_;
          while (NULL != iter)
          {
            Block *next = iter->next;
            if (0 != iter->ref_cnt)
            {
              // log iter->ref_cnt iter->cur_pos
            }
            else
            {
              allocer_.free(iter);
            }
            iter = next;
          }
          block_list_head_ = NULL;
          free_list_head_ = NULL;
        }

        T *alloc()
        {
          T *ret = NULL;
          if (NULL != free_list_head_)
          {
            Node *node = free_list_head_;
            if (NODE_MAGIC1 != node->magic1
                || NODE_MAGIC2 != node->magic2
                || NULL == node->block)
            {
              //log magic broken magic1 magic2
            }
            else 
            {
              free_list_head_ = node->next;
              node->block->ref_cnt++;
              ret = &(node->data);
            }
          }
          else
          {
            Block *block = block_list_head_;
            if (NULL == block
                || block->cur_pos >= (int32_t)NODE_NUM)
            {
              if (NULL == (block = (Block*)allocer_.alloc(sizeof(Block))))
              {
                //log alloc block fail
              }
              else
              {
                block->ref_cnt = 0;
                block->cur_pos = 0;
                block->nodes = (Node*)(block->nodes_buffer);
                block->next = block_list_head_;
                block_list_head_ = block;
              }
            }
            if (NULL != block)
            {
              Node *node = block->nodes + block->cur_pos;
              block->cur_pos++;
              block->ref_cnt++;
              node->magic1 = NODE_MAGIC1;
              node->next = NULL;
              node->block = block;
              node->magic2 = NODE_MAGIC2;
              ret = &(node->data);
            }
          }
          return (new(ret) T());
        }

        void free(T *data)
        {
          if (NULL == data)
          {
            //log invalid ptr
          }
          else
          {
            Node *node = (Node*)data;
            if (NODE_MAGIC1 != node->magic1
                || NODE_MAGIC2 != node->magic2)
            {
              //log wrong magic number
            }
            else
            {
              data->~T();
              node->block->ref_cnt--;
              node->next = free_list_head_;
              free_list_head_ = node;
            }
          }
        }

        void gc()
        {
          if (NULL != free_list_head_ 
              && NULL != block_list_head_)
          {
            Block *block_iter = block_list_head_;
            Block *block_next = NULL;
            Block *block_prev = NULL;
            while (NULL != block_iter)
            {
              block_next = block_iter->next;
              if (0 == block_iter->cur_pos)
              {
                Node *node_iter = free_list_head_;
                Node *node_prev = free_list_head_;
                volatile int32_t counter = 0;
                while (NULL != node_iter
                       && counter < NODE_NUM)
                {
                  if (block_iter == node_iter->block)
                  {
                    if (free_list_head_ == node_iter)
                    {
                      free_list_head_ = node_iter->next;
                    }
                    else
                    {
                      node_prev->next = node_iter->next;
                    }
                    counter++;
                  }
                  else
                  {
                    node_prev = node_iter;
                  }
                  node_iter = node_iter->next;
                }

                if (block_list_head_ == block_iter)
                {
                  block_list_head_ = block_iter->next;
                }
                else
                {
                  block_prev->next = block_iter->next;
                }
                //delete block_iter
                allocer_.free(block_iter);
                //free succ block nums
                block_iter = NULL;
              }
              else
              {
                block_prev = block_iter;
              }
              block_iter = block_next;
            }
          }
        }
      private:
        Block *block_list_head_;
        Node *free_list_head_;
        Allocer allocer_;
    };
  }
}
#endif //MACRAYKY_CUTIL_HASH_HASHUTILS_H_
