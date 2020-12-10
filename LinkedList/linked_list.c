#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"

// List Default Constructor
// Creates structs for list, initializes pointers as NULL
List *list_create(void)
    {
     List* list = malloc(sizeof(List));
     list->first = NULL;
     list->last = NULL;
     list->count = 0;
     return list;
    }

// Node Create Constructor
// Allocates memory for new node, initializes references as Null
// returns reference to created node
ListNode *list_create_node(int value)
    {
     ListNode *listNode = malloc(sizeof(ListNode));
     listNode->next = NULL;
     listNode->prev = NULL;
     listNode->value = value;
     return listNode;
    }

// Method for accessing count in list structure
// Returns list count
int list_count(List *list)
    {
     return list->count;
    }

// Returns first node
ListNode *list_first(List *list)
    {
     return list->first;
    }

// Returns the last node
ListNode *list_last(List *list)
    {
     return list->last;
    }

// Search method for node,
// Passed list and value, iterates through list
// returns node if found, else returns NULL
ListNode *list_find(List *list, int value)
    {
     ListNode* workingRef = list->first;
    
     while(workingRef != NULL)
        {
         if( workingRef->value == value )
            {
             return workingRef;
            }
         workingRef = workingRef->next;
        }
     
     return NULL;
    }

// Inserts node after the node containing value
// Passed the list, the node being inserted, and value which node goes after
// the passed value insert at the end of the list.
void list_insert_after( List *list, ListNode *node, int value )
    {
     list->count = list->count + 1;
     ListNode* findVal = list_find(list, value);
    
     if( findVal == NULL )
        {
         if( list->last != NULL )
             {
              list->last->next = node;
              node->prev = list->last;
              list->last = node;
             }
         else
             {
              list->first = node;
              list->last = node;
             }
        }
    else
        {
         if( list->first == list->last )
            {
             findVal->next = node;
             node->prev = findVal;
             list->last = node;
            }
        else
            {
             if( findVal == list->last )
                {
                 findVal->next = node;
                 node->prev = findVal;
                 list->last = node;
                }
             else
                {
                 ListNode* findNext = findVal->next;
                 findVal->next = node;
                 findNext->prev = node;
                 node->next = findNext;
                 node->prev = findVal;
                }
            }
        }
    }

// Finds a node containing value, calls removeNode
// Returns true if successful, else returns false
bool list_remove_value( List* list, int value )
    {
     ListNode* foundNode = list_find(list,value);
    
     if( foundNode != NULL )
        {
         list_remove_node( list, foundNode );
         return true;
        }
     else
        {
         return false;
        }
    }

// Helper method for remove_value
// Finds node in list, unlinks it, and frees it
// Returns the value of the removed node
int list_remove_node( List *list, ListNode* node )
    {
     list->count--;
    
     if(list->first == node)
        {
         list->first = node->next;
        }
     if(list->last == node)
        {
         list->last = node->prev;
        }
     if(node->next != NULL)
        {
         node->next->prev = node->prev;
        }
     if(node->prev != NULL)
        {
         node->prev->next = node->next;
        }
    
     int value = node->value;
     free(node);
     return value;
    }

// Finds node that contains value, inserts given node before that
// If there is no node containing the value, node is inserted at beginning of list
void list_insert_before( List *list, ListNode *node, int value )
    {
     list->count = list->count + 1;
     ListNode* findNode = list_find(list, value);
    
     if( findNode == NULL)
        {
         if( list->first == NULL )
            {
             list->first = node;
             list->last = node;
            }
         else
            {
             list->first->prev = node;
             node->next = list->first;
             list->first = node;
            }
        }
    else
        {
         if( list->first != list->last )
            {
             if( findNode == list->first )
                {
                 findNode->prev = node;
                 node->next = findNode;
                 list->first = node;
                }
             else
                {
                 ListNode* findNext = findNode->prev;
                 findNode->prev = node;
                 findNext->next = node;
                 node->prev = findNext;
                 node->next = findNode;
                }
            }
         else
            {
             findNode->prev = node;
             node->next = findNode;
             list->first = node;
            }
        }
    }

// Calls list_clear to remove nodes, then frees list structure
List *list_destroy(List *list)
    {
     list_clear(list);
     free(list);
     return NULL;
    }

// Frees nodes in the list
void list_clear( List *list )
    {
     if( list->first != NULL )
        {
         ListNode* workingRef = list->first;
         while( workingRef != NULL )
            {
             ListNode* temp = workingRef->next;
             list_remove_node( list, workingRef );
             workingRef = temp;
            }
        }
    }
