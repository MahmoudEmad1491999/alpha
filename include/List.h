#ifndef LIST_H
#define LIST_H
#include <stdint.h>

/**
 * Purpose: This structure represent a node in the chain of nodes
 *          of any Singly Linked List.
 * @data    is a pointer to the data object whatever the data
 *          type of it is.
 * @next    is a pointer to the next node in the chain of nodes.
 */
struct SLListNode
{
    void* data;
    struct SLListNode* next;
};

/**
 * Purpose: This Structure represent Singly Linked List.
 * @head    pointer to the head node, NULL if empty.
 * @tail    pointer to the tail node, NULL if empty.
 *          head equal tail when the length of the list is 1.
 * @len     the number of nodes in the list.
 * @freeElement     the freeing function to use when removing elements,
 *                  or removing the whole list.
 *
 */
struct SLList
{
    struct SLListNode* head;
    struct SLListNode* tail;
    uint32_t len;
    void (*freeElement)(void*);
};



//single list operations.
// append O(1), preprend O(1), insert O(n), delete O(n), at O(n)


/**
 * Purpose: this function is used to make Singly linked list objects.
 * @freeElement     the freeing function to use when removing elements,
 *                  or removing the whole list.
 * @return          pointer to the newly created Singly Linked List object.
 */
struct SLList* makeSLList(void (*freeElement)(void*));

/**
 * Purpose: this function is used to free the Singly Linked List Object,
 *          and the underlying data elements too.
 * @list    pointer to the list to be freed.
 */
void freeSLList(struct SLList* list);

/**
 * Purpose: this function is used to add an element to the end of
 *          of the singly linked list.
 * @list    the singly linked list to add an element to.
 * @data    pointer to the data element to be stored
 */
void SLListAppend(struct SLList* list, void* data);

/**
 * Purpose: this function is used to add an element to the beginning of
 *          of the singly linked list.
 * @list    the singly linked list to add an element to.
 * @data    pointer to the data element to be stored
 */
void SLListPrepend(struct SLList* list, void* data);

/**
 * Purpose: this function is used to insert an element in the singly linked
 *          list at a specific index and shift all the following indices forward.
 *          
 * @list    the singly linked list to remove an element from.
 * @data    pointer to the data element to be stored.
 * @index   the index at which to add the data element.
 * NOTES:   1)inserting in an index out of the index range [0, len],
 *          will fail and exit the whole program.
 *          2)from the previous note we can have the effect of appending an 
 *          element to the list using this function and index = len.
 */
void SLListInsert(struct SLList* list, void* data, uint32_t index);

/**
 * Purpose: this function is used to delete an element from the singly linked
 *          list and possibly returning it in the out parameter.
 *
 * @list    the singly linked list to remove an element from.
 * @out     the address to to store the pointer to the deleted
 *          data element from the list.
 * @index   the index of the element to delete.
 *
 * NOTE:    deleteing from an index outside the index range [0, len -1],
 *          will fail and exit the whole program.
 */
void SLListDelete(struct SLList* list, uint32_t index, void** out);

/**
 * Purpose: this function is to get the data stored at the index node of 
 *          the singly linked list. as a read only data.
 * @list    the singly linked list to get the node and data from.
 * @index   the index of the node.
 *
 * @return  pointer to the const data.
 */

void const* SLListAtGet(struct SLList* list, uint32_t index);
/*
 * Purpose: this function is used to set the data payload at the index
 *          node and free the old data object if any.
 * @list    the singly linked list to operate on.
 * @index   the index of the node that will hold the new data.
 * @data    pointer to the new data object.
 * @old_data    pointer to the place where to store the old data instead of freeing it.
 *              if null the data will be freed.
 * */
void SLListAtSet(struct SLList* list, uint32_t index, void* data, void** old_data);

#endif
