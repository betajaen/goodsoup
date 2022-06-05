/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef COMMON_HASHMAP_H
#define COMMON_HASHMAP_H

#include "common/types.h"
#include "common/memory.h"
#include "common/hash.h"
#include "common/buffer.h"

namespace common
{

    uint32 nextPrime(uint32 current);

    template<typename K, typename T>
    struct HashMap {
        private:

            struct Node;

            struct Node {
                uint32 _hash;
                T      _value;
                Node*  _next;
            };

            struct Bucket {
                uint16 _count;
                Node*  _first;
            };

            Buffer<Bucket> _buckets;
            uint32         _count;
            uint32         _nextGrow;
            uint32         _divisor;

            void grow() {
                /* TODO */
            }

        public:

            HashMap() 
                : _count(0), _nextGrow(0) {
            }

            ~HashMap() {
                clear();
            }

            uint32 size() const {
                return _count;
            }

            void clear() {
                for(uint32 i=0; i < _buckets.getSize();i++) {
                    Bucket& bucket = _buckets.get_unchecked(i);
                    Node* node = bucket._first, *next;
                    while(node) {
                        next = node->_next;
                        node->_value.~T();
                        releaseMemory(node);
                        node = next;
                    }
                    bucket._first = NULL;
                    bucket._count = 0;
                }
                _buckets.release();
                _count = 0;
                _nextGrow = 0;
                _divisor = 0;
            }

            void add(const K& key, const T& value) {
                
                if (_count == _nextGrow) {
                    grow();
                }

                uint32 hash = HashFunction<K>(key);
                uint32 bucketId = hash % _divisor;
                
                Bucket& bucket = _buckets.get_unchecked(bucketId);
                Node* node = allocateMemory(1, sizeof(Node), MEMF_ANY);
                node->_hash = hash;
                node->_next = bucket->_first;
                node->_value = value;
                bucket._first = node;
                bucket._count++;

                _count++;
            }

            bool has(const K& key) {
                
                if (_count == 0) {
                    return false;
                }

                uint32 hash = HashFunction<K>(key);
                uint32 bucketId = hash % _divisor;
                
                Bucket& bucket = _buckets.get_unchecked(bucketId);
                
                Node* node = bucket._first;

                while(node != NULL) {
                    if (node->_hash == hash) {
                        return true;
                    }
                    node = node->_next;
                }

                return false;
            }

            bool tryGet(const K& key, T& out_value) {

                if (_count == 0) {
                    return false;
                }

                uint32 hash = HashFunction<K>(key);
                uint32 bucketId = hash % _divisor;
                
                Bucket& bucket = _buckets.get_unchecked(bucketId);
                
                Node* node = bucket._first;

                while(node != NULL) {
                    if (node->_hash == hash) {
                        out_value = node->_value;
                        return true;
                    }
                    node = node->_next;
                }

                return false;
            }

    };
}


#endif
