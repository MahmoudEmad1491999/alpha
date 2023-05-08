#include "HelperFuncs.h"
#include "Macros.h"
#include "List.h"


struct SLList* makeSLList(void (*freeElement)(void*))
{
    struct SLList* list = xmalloc(sizeof(struct SLList));
    list->len = 0;
    list->head = list->tail = NULL;
    // if the given function pointer is null free it.
    list->freeElement = freeElement? freeElement: free;
    return list;
}

void freeSLList(struct SLList* list)
{
    if(list)
    {
        struct SLListNode* temp;
        for (int index = 0; index < list->len; index++) {
            list->freeElement(list->head->data);
            temp = list->head;
            list->head = list->head->next;
            free(temp);
        }
        free(list);
    }
}

void SLListAppend(struct SLList *list, void *data)
{
    FAIL_IF_NULL(list);
    /**
     * this is commented because maybe the NULL data pointer has a special meaning.
     */
    // FAIL_IF_NULL(data)    
    
    // get the current last node.
    struct SLListNode* old_tail = list->tail;

    struct SLListNode* new_tail = xmalloc(sizeof(struct SLListNode));
    // assign the address of data.
    new_tail->data =  data;
    // set the next to the new last node to NULL.
    new_tail->next = NULL;
    

    // set the list tail to the new node.
    list->tail = new_tail;
    // if the list is empyt last would be NULL.
    // if not set the next of the previous last to the new last.
    if(old_tail) old_tail->next = new_tail;
    // if so set the head and tail would be both point to the same element. 
    else list->head = list->tail;
    list->len++;
}


void SLListPrepend(struct SLList *list, void *data)
{

    FAIL_IF_NULL(list);
    /**
     * this is commented because maybe the NULL data pointer has a special meaning.
     */
    // FAIL_IF_NULL(data)    
    
    // record the old head of the list.
    struct SLListNode* old_head = list->head;
    // make the new head of the list.
    struct SLListNode* new_head =  xmalloc(sizeof(struct SLListNode));
    // set the new head data to the given data.
    new_head->data = data;
    // set the next node of the new head to the new head.
    new_head->next = old_head;
    
    // set the head of the list to the new head.
    list->head = new_head;
    
    // if the old head was NULL this means the list 
    // was empty so the tail should also point to the head
    if(!old_head) list->tail = list->head;  
    list->len++;
}

void SLListInsert(struct SLList *list, void *data, uint32_t index)
{
    FAIL_IF_NULL(list);
    // the +1 here is to enable the function to append an element
    // to the list.
    FAIL_IF_GREATER_OR_EQUAL(index, list->len+1);

    // if the index is zero use the prepend function instead.
    if(index == 0) {
        SLListPrepend(list, data);
        return;
    }
    // if the index is the last index of the list use append function instead.
    else if(index == list->len)
    {
        SLListAppend(list,data);
        return;
    }
    // else wise 
    else
    {
        // make the new node to be inserted.
        struct SLListNode* new_node = xmalloc(sizeof(struct SLListNode));
        new_node->data = data;
        // use looping to find the node before the node at index.
        struct SLListNode* the_before_node = list->head;
        while(index - 1)
        {
            the_before_node = the_before_node->next;
            index--;
        }
        // record the node at index
        struct SLListNode* the_index_node = the_before_node->next;
        new_node->next = the_index_node;
        the_before_node->next = new_node;
        list->len++;
    }
}

void SLListDelete(struct SLList *list, uint32_t index, void **out) {
    FAIL_IF_NULL(list);
    FAIL_IF_GREATER_OR_EQUAL(index, list->len);
    
    // deleting the first element of the list.
    if (index == 0) {
        struct SLListNode *old_head = list->head;
        // set the new head to the next element of the old head.
        list->head = list->head->next;
        // if the out pointer is not null return the deleted data pointer
        // in it.
        if (out) {
            *out = old_head->data;
        } else { // if out is null free the data.
            // free the data of the old head.
            list->freeElement(old_head->data);
        }
        // free the old head.
        free(old_head);
        list->len--;
        // if the new length is one set the tail to head.
        // if the new length is zero head is going to be NULL,
        // and setting the tail to the head also suffice.
        if (list->len == 1 || list->len == 0)
        {
            list->tail = list->head;
        }
    } else {
        // get the node before node at index.
        struct SLListNode *the_before_node = list->head;
        while (index - 1) {
            the_before_node = the_before_node->next;
            index--;
        }
        struct SLListNode *the_after_node = the_before_node->next->next;
        // if the out pointer is not null return the deleted data pointer
        // in it.
        if (out) {
            *out = the_before_node->next->data;
        } else { // if out is null free the data.
            // free the data associated with the node at index.
            list->freeElement(the_before_node->next->data);
        }

        // free the node at index itself.
        free(the_before_node->next);

        // set the next node of the_before_node to the_after_node.
        the_before_node->next = the_after_node;
        list->len--;
        // we are testing the length as if the index is 1 and the length is
        // 2 then, after the deleting it will be one so the tail is going to
        // be the same as the head of the list. if the new length is one set
        // the tail to head.
        if (list->len == 1)
        {
            list->tail = list->head;
        }
    }
}

void const* SLListAtGet(struct SLList* list, uint32_t index)
{
    FAIL_IF_NULL(list);
    FAIL_IF_GREATER_OR_EQUAL(index, list->len);

    struct SLListNode* the_index_node = list->head;
    while(index)
    {
        the_index_node = the_index_node->next;
        index--;
    }
    return the_index_node->data;
}


void SLListAtSet(struct SLList *list, uint32_t index, void *data, void**old_data)
{
    FAIL_IF_NULL(list);
    FAIL_IF_GREATER_OR_EQUAL(index, list->len);
    // we are not testing for NULL data pointer as NULL pointer may be treated as
    // a special value.
    // FAIL_IF_NULL(data)
    struct SLListNode* the_index_node = list->head;
    while(index)
    {
        the_index_node = the_index_node->next;
        index--;
    }
    if(old_data)
    {
        *old_data = the_index_node->data;
    }
    else {
        list->freeElement(the_index_node->data);
    }
    the_index_node->data = data;
}
