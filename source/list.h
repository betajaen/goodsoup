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

#ifndef GS_QUEUE_H
#define GS_QUEUE_H

#include "types.h"

namespace gs
{

	template<typename T>
	class Queue
	{
	private:
		T* head, *tail;
	public:

		Queue() {
			head = NULL;
			tail = NULL;
		}

		~Queue() {
			head = NULL;
			tail = NULL;
		}

		void clear() {
			head = NULL;
			tail = NULL;
		}

		bool isEmpty() const {
			return head == NULL;
		}

		bool hasAny() const {
			return head != NULL;
		}

		T* peekFront() {
			return head;
		}

		T* pullFront() {
			T* h = head;

			if (h != NULL) {
				head = h->next;
				h->next = NULL;

				if (head == NULL) {
					tail = NULL;
				}

			}

			return h;
		}

        T* pullBack() {
            T* t = tail;

            if (t != NULL) {
                T* n = head;
                while(n != NULL) {

                    if (n->next == t) {
                        tail = n;
                        tail->next = NULL;
                        break;
                    }

                    n = n->next;
                }
            }

            return t;
        }

		void pushBack(T* newTail) {
			if (tail == NULL) {
				head = tail = newTail;
			}
			else {
				tail->next = newTail;
				tail = newTail;
			}
		}

        void pushFront(T* newHead) {
            if (head == NULL) {
                head = tail = newHead;
            }
            else {
                newHead->next = head;
                head = newHead;
            }
        }

	};

	template<typename T>
	class List {

		T* head, *tail;

	public:

		List() {
			head = NULL;
			tail = NULL;
		}

		T* peekFront() {
			return head;
		}

		T* pullFront() {
			T* h = head;

			if (h != NULL) {
				head = h->next;
				h->next = NULL;

				if (head == NULL) {
					tail = NULL;
				}
				else {
					head->prev = NULL;
				}
			}

			return h;
		}

		T* peekBack() {
			return tail;
		}

		T* pullBack() {
			T* t = tail;

			if (t != NULL) {
				tail = t->prev;

				if (tail != NULL) {
					tail->next = NULL;
				}
			}

			return t;
		}


		void pushFront(T* newHead) {
			if (head == NULL) {
				head = tail = newHead;
			}
			else {
				head->prev = newHead;
				newHead->next = head;
				head = newHead;
			}
		}

		void pushBack(T* newTail) {
			if (tail == NULL) {
				head = tail = newTail;
			}
			else {
				newTail->prev = tail;
				tail->next = newTail;
				tail = newTail;
			}
		}

		void pull(T* item) {

			if (item == head) {
				pullFront();
			}
			else if (item == tail) {
				pullBack();
			}
			else {
				T* before = item->prev;
				T* after = item->next;
				before->next = after;
				after->prev = before;
			}
		}

	};

}


#endif
