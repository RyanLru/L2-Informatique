#include "algorithms.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void array_create(struct array *self) {
    self->size = 0;
    self->capacity = 0;
    self->data = NULL;
}

void array_create_from(struct array *self, const int *other, size_t size) {
    self->size = size;
    self->capacity = size;
    self->data = calloc(self->size, sizeof(int));
    for(size_t i = 0; i < size; i++){
        self->data[i] = other[i];
    }
}

void array_destroy(struct array *self) {
    if (self->data != NULL) {
        free(self->data);
    }
    self->data = NULL;
    self->size = 0;
    self->capacity = 0;
}

bool array_empty(const struct array *self) {
    if(self->size != 0){
        return false;
    }
    return true;
}

size_t array_size(const struct array *self) {
    if(self != NULL){
        return self->size;
    }
    return -1;
}

bool array_equals(const struct array *self, const int *content, size_t size) {
    if(self->size == size){
        for(size_t i = 0; i < size ; i++){
            if(self->data[i] != content[i]){
                return false;
            }
        }
        return true;
    }
  return false;
}


void array_push_back(struct array *self, int value) {
    if (self->size == self->capacity) {
        self->capacity += 1;
        int *data = calloc(self->capacity, sizeof(int));
        memcpy(data, self->data, self->size * sizeof(int));
        free(self->data);
        self->data = data;
    }
    self->data[self->size] = value;
    self->size += 1 ;
}

void array_pop_back(struct array *self) {
    if(self != NULL){
        self->capacity = self->size-1;
        self->size = self->size-1;
    }
}

void array_insert(struct array *self, int value, size_t index) {
    if(self != NULL && self->size >= index) {
        self->capacity += 1;
        self->size += 1;
        int *data = calloc(self->size, sizeof(int));
        for (size_t i = 0; i < self->size; i++) {
            if (i == index) {
                data[i] = value;
            } else if (i > index) {
                data[i] = self->data[i - 1];
            } else {
                data[i] = self->data[i];
            }
        }
        free(self->data);
        self->data = data;
    }
}

void array_remove(struct array *self, size_t index) {
    if (self != NULL && self->size > index) {
        int *data = calloc(self->size - 1, sizeof(int));
        for (size_t i = 0, j = 0; i < self->size; i++) {
            if (i != index) {
                data[j] = self->data[i];
                j++;
            }
        }
        free(self->data);
        self->data = data;
        self->size -= 1;
    }
}

int array_get(const struct array *self, size_t index) {
    if(index < self->size){
        return self->data[index];
    }
  return 0;
}

void array_set(struct array *self, size_t index, int value) {
    if(self != NULL && self->size > index){
        self->data[index] = value;
    }
}

size_t array_search(const struct array *self, int value) {
    if(self != NULL){
        for(size_t i = 0 ; i < self->size ;i++){
            if(self->data[i] == value){
                return i;
            }
        }
    }
    return self->size;
}


size_t array_search_sorted(const struct array *self, int value) {
    if(self != NULL){
        for(size_t i = 0; i < self->size ; i++){
            if(self->data[i] > value){
                return self->size;
            }
            if(self->data[i] == value){
                return i;
            }
        }
    }
  return self->size;
}

bool array_is_sorted(const struct array *self) {
    if(self != NULL){
        int max = 0;
        for(size_t i = 0; i < self->size; i++){
            if(self->data [i] < max){
                return false;
            }
            max = self->data[i];
        }
        return true;
    }

    return false;
}


ptrdiff_t array_partition(struct array *self, ptrdiff_t i, ptrdiff_t j) {
    if(self != NULL){
        ptrdiff_t pivot = i;
        ptrdiff_t left = i+1;
        ptrdiff_t right = j;
        while(left <= right){
            if(self->data[left] > self->data[pivot] && self->data[right] < self->data[pivot]){
                int tmp = self->data[left];
                self->data[left] = self->data[right];
                self->data[right] = tmp;
            }
            if(self->data[left] <= self->data[pivot]){
                left += 1;
            }
            if(self->data[right] >= self->data[pivot]){
                right -= 1;
            }
        }
        int tmp = self->data[pivot];
        self->data[pivot] = self->data[right];
        self->data[right] = tmp;
        return right;
    }
    return -1;
}


void array_quick_sort(struct array *self) {
    if(self != NULL){
        ptrdiff_t i = 0;
        ptrdiff_t j = self->size-1;
        ptrdiff_t pivot = array_partition(self, i, j);
        if (i < pivot - 1) {
            struct array left_array;
            left_array.size = pivot - i;
            left_array.capacity = left_array.size;
            left_array.data = self->data + i;
            array_quick_sort(&left_array);
        }

        if (pivot + 1 < j) {
            struct array right_array;
            right_array.size = j - pivot;
            right_array.capacity = right_array.size;
            right_array.data = self->data + pivot + 1;
            array_quick_sort(&right_array);
        }
    }
}


void array_heap_sort(struct array *self) {
    if(self != NULL){
        
    }

}

bool array_is_heap(const struct array *self) {
    if (self != NULL) {
        for (size_t i = 0; i < self->size; i++) {
            size_t left_child = 2 * i + 1;
            size_t right_child = 2 * i + 2;
            if (left_child < self->size && self->data[i] < self->data[left_child]) {
                return false;
            }
            if (right_child < self->size && self->data[i] < self->data[right_child]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

void array_heap_add(struct array *self, int value) {
    if(self == NULL){
        return ;
    }
    if (self->size == 0 && self->capacity == 0) {
        self->capacity = 1;
        self->data = malloc(self->capacity * sizeof(int));
        self->data[0] = value;
        self->size++;
        return;
    }

    if(self->size >= self->capacity){
        self->capacity *= 2;
        int *data = calloc(self->capacity, sizeof(int));
        memcpy(data, self->data, self->size * sizeof(int));
        free(self->data);
        self->data = data;
    }

    size_t i = self->size;
    self->data[i] = value;
    self->size++;

    while (i > 0) {
        size_t j = (i - 1) / 2;
        if (self->data[i] < self->data[j]) {
            break;
        }
        int tmp = self->data[i];
        self->data[i] = self->data[j];
        self->data[j] = tmp;
        i = j;
    }
}

int array_heap_top(const struct array *self) {
    if (self != NULL) {
        return self->data[0];
    }
    return 0;
}

void array_heap_remove_top(struct array *self) {
    if(self != NULL){
        self->data[0] = self->data[self->size-1];
        self->size -= 1;
        size_t i = 0;
        while (i < self->size) {
            size_t j = 2 * i + 1;
            if (j >= self->size) {
                break;
            }
            if (j + 1 < self->size && self->data[j + 1] > self->data[j]) {
                j++;
            }
            if (self->data[i] > self->data[j]) {
                break;
            }
            int tmp = self->data[i];
            self->data[i] = self->data[j];
            self->data[j] = tmp;
            i = j;
        }
    }
}

/*
 * list
 */



void list_create(struct list *self) {
    self->first = NULL;
    self->last = NULL;
}

void list_create_from(struct list *self, const int *other, size_t size) {
    self->first = NULL;
    self->last = NULL;
    for(size_t i = 0; i < size; i++){
        struct list_node *node = malloc(sizeof(struct list_node));
        node->data = other[i];
        node->next = NULL;
        node->prev = NULL;
        if(self->first == NULL){
            self->first = node;
            self->last = node;
        } else {
            self->last->next = node;
            node->prev = self->last;
            self->last = node;
        }
    }
}

void list_destroy(struct list *self) {
    if(self != NULL){
        struct list_node *current = self->first;
        while (current != NULL) {
            struct list_node *next = current->next;
            free(current);
            current = next;
        }
        self->first = NULL;
        self->last = NULL;
    }
}

bool list_empty(const struct list *self) {
    if (self != NULL){
        if(self->first == NULL && self->last == NULL) {
            return true;
        }
    }
    return false;
}

size_t list_size(const struct list *self) {
    if(self != NULL){
        size_t size = 0;
        struct list_node *node = self->first;
        while(node != NULL){
            size += 1;
            node = node->next;
        }
        return size;
    }
    return -1;
}

bool list_equals(const struct list *self, const int *data, size_t size) {
    if(self != NULL){
        if(list_size(self) == size){
            struct list_node *node = self->first;
            for(size_t i = 0; i < size; i++){
                if(node->data != data[i]){
                    return false;
                }
                node = node->next;
            }
            return true;
        }
    }
    return false;
}

void list_push_front(struct list *self, int value) {
    struct list_node *node = malloc(sizeof(struct list_node));
    node->data = value;
    node->next = NULL;
    node->prev = NULL;

    if(self->first != NULL) {
        node->next = self->first;
        self->first->prev = node;
        self->first = node;
    }
    else{
        self->first = node;
        self->last = node;
    }

}

void list_pop_front(struct list *self) {
    if(self != NULL){
        struct list_node *node = self->first;
        if(self->first->next != NULL){
            self->first = self->first->next;
            self->first->prev = NULL;
        }
        else{
            self->first->next = NULL;
            self->first = NULL;
            self->last = NULL;
        }
        free(node);
    }
}

void list_push_back(struct list *self, int value) {
    if(self != NULL){
        struct list_node *node = malloc(sizeof(struct list_node));
        node->data = value;
        node->next = NULL;
        node->prev = NULL;

        if(self->last != NULL){
            self->last->next = node;
            node->prev = self->last;
            self->last = node;
        }
        else{
            self->first = node;
            self->last = node;
        }
    }
}

void list_pop_back(struct list *self) {
    if(self != NULL){
        struct list_node *node = self->last;
        if(self->last->prev != NULL){
            self->last = self->last->prev;
            self->last->next = NULL;
        }
        else{
            self->last->prev = NULL;
            self->first = NULL;
            self->last = NULL;
        }
        free(node);
    }
}


void list_insert(struct list *self, int value, size_t index) {
    if(self != NULL){
        size_t pos = 0;
        struct list_node *node = self->first;
        struct list_node *insert = malloc(sizeof(struct list_node));
        insert->data = value;

        if (index == 0) {
            list_push_front(self, value);
            free(insert);
        }
        else{
            while(node != NULL){
                if(pos == index){
                    insert->next = node;
                    insert->prev = node->prev;
                    node->prev->next = insert;
                    node->prev = insert;
                }
                pos ++;
                node = node->next;
            }
            if(index == pos){
                list_push_back(self, value);
                free(insert);
            }
        }

    }
}


void list_remove(struct list *self, size_t index) {
    if (self != NULL) {
        struct list_node *node = self->first;
        size_t pos = 0;

        while (node != NULL && pos < index) {
            node = node->next;
            pos++;
        }

        if (node != NULL) {
            if (node->prev != NULL) {
                node->prev->next = node->next;
            } else {
                self->first = node->next;
            }

            if (node->next != NULL) {
                node->next->prev = node->prev;
            } else {
                self->last = node->prev;
            }

            free(node);
        }
    }
}

int list_get(const struct list *self, size_t index) {
    if(self != NULL){
        size_t pos = 0;
        struct list_node *node = self->first;
        while(node != NULL){
            if(index == pos){
                return node->data;
            }
            pos ++;
            node = node->next;
        }
    }
    return 0;
}

void list_set(struct list *self, size_t index, int value) {
    if(self != NULL){
        size_t pos = 0;
        struct list_node *node = self->first;
        while(node != NULL){
            if(index == pos){
                node->data = value;
            }
            pos ++;
            node = node->next;
        }
    }
}

size_t list_search(const struct list *self, int value) {
    size_t pos = 0;
    if(self != NULL){
        struct list_node *node = self->first;
        while(node != NULL){
            if(node->data == value){
                return pos;
            }
            pos ++;
            node = node->next;
        }
    }
    return pos;
}

bool list_is_sorted(const struct list *self) {
    if(self != NULL){
        size_t pos = 0;
        struct list_node *node = self->first;
        while(node != NULL){
            if(node->next != NULL){
                if(node->data > node->next->data){
                    return false;
                }
            }
            pos ++;
            node = node->next;
        }
    }
    return true;
}

void list_split(struct list *self, struct list *out1, struct list *out2) {
    if(self != NULL){
        size_t pos = 0;
        struct list_node *node = self->first;
        while(node != NULL){
            if(pos < list_size(self)/2){
                list_push_back(out1, node->data);
            }
            else{
                list_push_back(out2, node->data);
            }
            pos ++;
            node = node->next;
        }
        list_destroy(self);
    }
}

void list_merge(struct list *self, struct list *in1, struct list *in2) {
    if(self != NULL){
        struct list_node *node1 = in1->first;
        struct list_node *node2 = in2->first;
        while(node1 != NULL && node2 != NULL){
            if(node1->data < node2->data){
                list_push_back(self, node1->data);
                node1 = node1->next;
            }
            else{
                list_push_back(self, node2->data);
                node2 = node2->next;
            }
        }
        while(node1 != NULL){
            list_push_back(self, node1->data);
            node1 = node1->next;
        }
        while(node2 != NULL){
            list_push_back(self, node2->data);
            node2 = node2->next;
        }

        list_destroy(in1);
        list_destroy(in2);
    }
}

void list_merge_sort(struct list *self) {
    if(self != NULL){
        if(list_size(self) > 1){
            struct list *out1 = malloc(sizeof(struct list));
            struct list *out2 = malloc(sizeof(struct list));
            list_create(out1);
            list_create(out2);
            list_split(self, out1, out2);
            list_merge_sort(out1);
            list_merge_sort(out2);
            list_merge(self, out1, out2);
            list_destroy(out1);
            list_destroy(out2);
            free(out1);
            free(out2);
        }
    }

}


/*
 * tree
 */

void tree_create(struct tree *self) {
    self->root = NULL;
}


void tree_destroy(struct tree *self) {
}


bool tree_contains(const struct tree *self, int value) {
    if(self->root != NULL){
        struct tree_node *node = self->root;
        while(node != NULL){
            if(node->data == value){
                return true;
            }
            if(node->data > value){
                node = node->left;
            }
            else{
                node = node->right;
            }
        }
    }
    return false;
}


bool tree_insert(struct tree *self, int value) {
    if (self != NULL) {
        if (self->root == NULL) {
            struct tree_node *node = malloc(sizeof(struct tree_node));
            node->data = value;
            node->left = NULL;
            node->right = NULL;
            self->root = node;
            return true;
        } else {
            struct tree_node *node = self->root;
            while (node != NULL) {
                if (node->data == value) {
                    return false;
                }
                if (node->data > value) {
                    if (node->left == NULL) {
                        struct tree_node *new_node = malloc(sizeof(struct tree_node));
                        new_node->data = value;
                        new_node->left = NULL;
                        new_node->right = NULL;
                        node->left = new_node;
                        return true;
                    } else {
                        node = node->left;
                    }
                } else {
                    if (node->right == NULL) {
                        struct tree_node *new_node = malloc(sizeof(struct tree_node));
                        new_node->data = value;
                        new_node->left = NULL;
                        new_node->right = NULL;
                        node->right = new_node;
                        return true;
                    } else {
                        node = node->right;
                    }
                }
            }
        }
    }

    return false;
}



bool tree_remove(struct tree *self, int value) {
    if(self != NULL) {
        if(tree_contains(self, value) == false){
            return false;
        }
        struct tree_node *node = self->root;
        struct tree_node *parent = NULL;
        while (node->data != value) {
            parent = node;
            if (node->data > value) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        if (node->left == NULL && node->right == NULL) {
            if (parent != NULL) {
                if (parent->left == node) {
                    parent->left = NULL;
                } else {
                    parent->right = NULL;
                }
            } else {
                self->root = NULL;
            }
            free(node);
            return true;
        }
        if (node->left == NULL) {
            if (parent != NULL) {
                if (parent->left == node) {
                    parent->left = node->right;
                } else {
                    parent->right = node->right;
                }
            } else {
                self->root = node->right;
            }
            free(node);
            return true;
        }
        if (node->right == NULL) {
            if (parent != NULL) {
                if (parent->left == node) {
                    parent->left = node->left;
                } else {
                    parent->right = node->left;
                }
            } else {
                self->root = node->left;
            }
            free(node);
            return true;
        }
        struct tree_node *min = node->right;
        struct tree_node *min_parent = node;
        while (min->left != NULL) {
            min_parent = min;
            min = min->left;
        }
        node->data = min->data;
        if (min_parent->left == min) {
            min_parent->left = min->right;
        } else {
            min_parent->right = min->right;
        }
        free(min);
        return true;
    }
    return false;
}

bool tree_empty(const struct tree *self) {
    if(self->root != NULL){
        return false;
    }
    return true;
}

size_t tree_size(const struct tree *self) {
    if (self == NULL || self->root == NULL) {
        return 0;
    } else {
        return 1 + tree_size(&(struct tree){self->root->left}) + tree_size(&(struct tree){self->root->right});
    }
}


size_t tree_height(const struct tree *self) {
    if (self == NULL || self->root == NULL) {
        return 0;
    } else {
        size_t left = tree_height(&(struct tree){self->root->left});
        size_t right = tree_height(&(struct tree){self->root->right});
        if (left > right) {
            return 1 + left;
        } else {
            return 1 + right;
        }
    }
}


void tree_walk_pre_order(const struct tree *self, tree_func_t func, void *user_data)  {
    if(self != NULL){
        func(self->root->data, user_data);
        if(self->root->left != NULL)
            tree_walk_pre_order(&(struct tree){self->root->left}, func, user_data);
        if(self->root->right != NULL)
            tree_walk_pre_order(&(struct tree){self->root->right}, func, user_data);
    }
}

void tree_walk_in_order(const struct tree *self, tree_func_t func, void *user_data) {
    if(self != NULL){
        if(self->root->left != NULL)
            tree_walk_in_order(&(struct tree){self->root->left}, func, user_data);
        func(self->root->data, user_data);
        if(self->root->right != NULL)
            tree_walk_in_order(&(struct tree){self->root->right}, func, user_data);
    }

}

void tree_walk_post_order(const struct tree *self, tree_func_t func, void *user_data) {
    if(self != NULL){
        if(self->root->left != NULL)
            tree_walk_post_order(&(struct tree){self->root->left}, func, user_data);
        if(self->root->right != NULL)
            tree_walk_post_order(&(struct tree){self->root->right}, func, user_data);
        func(self->root->data, user_data);
    }

}
