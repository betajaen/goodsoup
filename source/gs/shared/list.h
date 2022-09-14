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

#ifndef T
#error "T must be defined before including common/list.h"
#endif

#ifndef LIST_NAME
#define LIST_NAME GS_CONCAT2(T, List)
#endif

typedef struct LIST_NAME {
		T *head, *tail;
} LIST_NAME;

static inline T* GS_CONCAT2(LIST_NAME, PeekHead)(LIST_NAME* list) {
	return list->head;
}

static inline T* GS_CONCAT2(LIST_NAME, PeekTail)(LIST_NAME* list) {
	return list->tail;
}

static inline T* GS_CONCAT2(LIST_NAME, PullFront)(LIST_NAME* list) {
	T* h = list->head;

	if (h != NULL) {
		list->head = h->next;
		
		if (list->head == NULL) {
			list->tail = NULL;
		}
		else {
			list->head->prev = NULL;
		}
		
		h->prev = NULL;
		h->next = NULL;
	}

	return h;
}

static inline void GS_CONCAT2(LIST_NAME, PushFront)(LIST_NAME* list, T* newHead) {
	if (list->head == NULL) {
		list->head = list->tail = newHead;
	}
	else {
		list->head->prev = newHead;
		newHead->next = list->head;
		list->head = newHead;
	}
}

static inline T* GS_CONCAT2(LIST_NAME, PullBack)(LIST_NAME* list) {
	T* t = list->tail;

	if (t != NULL) {
		list->tail = t->prev;

		if (list->tail != NULL) {
			list->tail->next = NULL;
		}

		t->prev = NULL;
		t->next = NULL;
	}

	return t;
}

static inline void GS_CONCAT2(LIST_NAME, PushBack)(LIST_NAME* list, T* newTail) {
	if (list->tail == NULL) {
		list->head = list->tail = newTail;
	}
	else {
		newTail->prev = list->tail;
		list->tail->next = newTail;
		list->tail = newTail;
	}
}

static inline void GS_CONCAT2(LIST_NAME, Remove)(LIST_NAME* list, T* item) {
	if (item != NULL) {
		
		if (item == list->head) {
			pullFront();
		}
		else if (item == list->tail) {
			pullBack();
		}
		else {
			T* before = item->prev;
			T* after = item->next;
			before->next = after;
			after->prev = before;
		}

		item->prev = NULL;
		item->next = NULL;
	}
}

#undef T
#undef LIST_NAME