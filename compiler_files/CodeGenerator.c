#include "CodeGenerator.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NR_BUCKETS 1024

#define bool int
#define true 1
#define false 0

typedef struct arrayObject *arrayObjectPtr;
typedef struct arrayObject {
    char key[500];
    int cellSize;
    int numberOfDimensions;
    char demensionsArr[500];
    arrayObjectPtr next;
    arrayObjectPtr prev;
} ArrayObject;

typedef struct arrays_symbol_table {
    ArrayObject *arrays;
    int arraysCounter;
} ArraysSymbolTable;

ArraysSymbolTable *arraysSymbolTable = NULL;

arrayObjectPtr
add_array_to_arrays_mapping(arrayObjectPtr list, char *key, int cellSize, char *demensionsArr, int numberOfDimensions) {
    arrayObjectPtr p, q;
    arraysSymbolTable->arraysCounter += 1;

    /* allocate memory for new record */
    if ((p = (arrayObjectPtr) malloc(sizeof(ArrayObject))) == NULL) {
        printf("Cannot allocate memory\n");
        exit(1);
    }

    strcpy(p->key, key);
    p->cellSize = cellSize;
    strcpy(p->demensionsArr, demensionsArr);
    p->numberOfDimensions = numberOfDimensions;
//    printf("===============\n");
//    printf("Array definition Key is: %s\n", p->key);
//    printf("Array cell size is: %s\n", p->value);
//    printf("===============\n");
    if (list == NULL) { /* in the case if "p" is the first element in the list */
        p->next = 0;
        p->prev = 0;
        return p;
    } else {
        q = list;
        while (q->next != NULL) { /* moving to the end of the list */
            q = q->next;
        }
        p->next = q->next;
        q->next = p;
        p->prev = q;
        return list;
    }
}

int get_arrays_cell_size(char *array_identifier) {
    arrayObjectPtr curNode;
    curNode = arraysSymbolTable->arrays;

    // Iterate till last element until key is not found
    while (curNode != NULL && strcmp(curNode->key, array_identifier) != 0)
        curNode = curNode->next;
    return (curNode != NULL) ? curNode->cellSize : -1;
}

int get_number_of_dimensions_for_array(char *identifier) {
    arrayObjectPtr curNode;
    curNode = arraysSymbolTable->arrays;

    // Iterate till last element until key is not found
    while (curNode != NULL && strcmp(curNode->key, identifier) != 0)
        curNode = curNode->next;
    if (curNode != NULL)
        return curNode->numberOfDimensions;
    return -1;
}

char *get_array_dimensions(char *identifier) {
    arrayObjectPtr curNode;
    curNode = arraysSymbolTable->arrays;

    // Iterate till last element until key is not found
    while (curNode != NULL && strcmp(curNode->key, identifier) != 0)
        curNode = curNode->next;
    if (curNode != NULL)
        return &curNode->demensionsArr;
    return NULL;
}

typedef struct structObject *structObjectPtr;
typedef struct structObject {
    char key[500];
    char value[1000];
    int size;
    structObjectPtr next;
    structObjectPtr prev;
} StructObject;

typedef struct structs_symbol_table {
    StructObject *vars;
    int variables_counter;
} StructsSymbolTable;

StructsSymbolTable *structsSymbolTable = NULL;

structObjectPtr add_struct_to_structs_mapping(structObjectPtr list, char *key, char *value) {
    structObjectPtr p, q;
    structsSymbolTable->variables_counter += 1;

    /* allocate memory for new record */
    if ((p = (structObjectPtr) malloc(sizeof(StructObject))) == NULL) {
        printf("Cannot allocate memory\n");
        exit(1);
    }

    strcpy(p->key, key);
    strcpy(p->value, value);
    p->size = 1;
//    printf("===============\n");
//    printf("Struct definition Key is: %s\n", p->key);
//    printf("Struct definition value is: %s\n", p->value);
//    printf("Struct definition size is: %d\n", p->size);
//    printf("===============\n");
    if (list == NULL) { /* in the case if "p" is the first element in the list */
        p->next = 0;
        p->prev = 0;
        return p;
    } else {
        q = list;
        while (q->next != NULL) { /* moving to the end of the list */
            q = q->next;
        }
        p->next = q->next;
        q->next = p;
        p->prev = q;
        return list;
    }
}

char *get_struct_value_str(const char *key) {
    structObjectPtr curNode;
    curNode = structsSymbolTable->vars;

    // Iterate till last element until key is not found
    while (curNode != NULL && strcmp(curNode->key, key) != 0)
        curNode = curNode->next;
    return (curNode != NULL) ? curNode->value : NULL;
}

const int CODE_INIT_FRAME_IN_BYTES = 4;
typedef struct variable *varPtr;
typedef struct variable {
    int address;
    char str[100];
    char typeAsString[100];
    tn_t type;
    varPtr prev;
    varPtr next;
    int size;
} Variable;

// This struct holds a linked list of variables called vars, and a counter for current number of variables
typedef struct symbol_table {
    Variable *vars;
    int variables_counter;
} Symbol_table;

Symbol_table *symbolTalble = NULL;
Variable *UKNOWN_VARIABLE = NULL;

varPtr add_variable_to_symbol_table(char *identifier, tn_t type, varPtr list) {
    varPtr p, q;
    symbolTalble->variables_counter += 1;

    /* allocate memory for new record */
    if ((p = (varPtr) malloc(sizeof(Variable))) == NULL) {
        printf("Cannot allocate memory\n");
        exit(1);
    }
    p->address = CODE_INIT_FRAME_IN_BYTES + symbolTalble->variables_counter; /* store input in new record */
    // printf("add_variable_to_symbol_table5:\n");
    strcpy(p->str, identifier);
    p->type = type;
    p->size = 1;
    // printf("===============\n");
    // printf("Key is: %s\n", p->str);
    // printf("ADDR: %d\n", p->address);
    // printf("===============\n");
    if (list == NULL) { /* in the case if "p" is the first element in the list */
        p->next = 0;
        p->prev = 0;
        return p;
    } else {
        q = list;
        while (q->next != NULL) { /* moving to the end of the list */
            q = q->next;
        }
        p->next = q->next;
        q->next = p;
        p->prev = q;
        return list;
    }
}

int get_variable_from_table(char *identifier) {
    varPtr curNode;
    curNode = symbolTalble->vars;

    // Iterate till last element until key is not found
    while (curNode != NULL && strcmp(curNode->str, identifier) != 0)
        curNode = curNode->next;
    return (curNode != NULL) ? curNode->address : -1;
}

void set_variable_size(char *identifier, int calculated_size) {
    varPtr curNode;
    curNode = symbolTalble->vars;

    // Iterate till last element until key is not found
    while (curNode != NULL && strcmp(curNode->str, identifier) != 0)
        curNode = curNode->next;
    if (curNode != NULL)
        curNode->size = calculated_size;
}

int get_variable_size(char *identifier) {
    varPtr curNode;
    curNode = symbolTalble->vars;

    // Iterate till last element until key is not found
    while (curNode != NULL && strcmp(curNode->str, identifier) != 0)
        curNode = curNode->next;
    if (curNode != NULL)
        return curNode->size;
    return -2;
}

void reverse_string(char *str) {
    int i, end_index;
    char temp;

    end_index = strlen(str) - 1;

    for (i = 0; i <= end_index / 2; ++i) {
        temp = str[i];
        str[i] = str[end_index - i];
        str[end_index - i] = temp;
    }
}

void reverse_by_chanks(char *str) {
    char singleChankHolder[100] = "";
    char temp2[100] = "";
    char reversedString[100] = "";

    for (int i = 0; i < strlen(str); i++) {
        strcpy(singleChankHolder, "");
        do {
            strncat(singleChankHolder, &str[i], 1);
            i++;

        } while (str[i] != '!' && i < strlen(str));
        strncat(singleChankHolder, &str[i], 1);
        strcpy(temp2, reversedString);
        strcpy(reversedString, singleChankHolder);
        strncat(reversedString, temp2, strlen(temp2));
    }
    strcpy(str, reversedString);
}

char struct_name[500] = "";
char break_dest[50] = "";
const char SUPPERATOR = '!';
const char ARRAY_IDENT_SUPP[2] = "_0";
int last_loop_end_lable_line_num = -1;
//char array_identifier[500] = "";
int current_dimension = -1;

int set_struct_name(treenode *root) {
    char namesFromEnd[1000] = "";
    char nameFromBegining[500] = ""; // it will collect all the left kids
    treenode *tracker = root; // pointer to perform tree traversal
    int should_continue_go_down = 1;
    int index_depth = 0; // indicator for array index depth
    int search_dpeth = 1;
    //banana
    while (tracker != NULL && tracker->lnode != NULL && tracker->rnode != NULL && should_continue_go_down) {
        // printf("ROUNDS\n");
        if (tracker->lnode->hdr.type == TN_INDEX)
            index_depth = search_dpeth;
        if (tracker->lnode->hdr.which == LEAF_T && tracker->rnode->hdr.which == LEAF_T) {
            should_continue_go_down = 0;
            // printf("struct nameFromBegining is %s\n", struct_name);
            // printf("Setting should_continue_go_down to 0 \n");
            if (tracker->lnode->hdr.type == TN_IDENT) {
                strncat(nameFromBegining, ((leafnode *) tracker->lnode)->data.sval->str,
                        strlen(((leafnode *) tracker->lnode)->data.sval->str));
                strncat(nameFromBegining, &SUPPERATOR, 1);
                // printf("Im ident! %s\n",((leafnode *)left_node)->data.sval->str);
                if (index_depth == 0) {
                    if (((leafnode *) tracker->rnode)->hdr.type != TN_INT) {
                        strncat(nameFromBegining, ((leafnode *) tracker->rnode)->data.sval->str,
                                strlen(((leafnode *) tracker->rnode)->data.sval->str));
                        strncat(nameFromBegining, &SUPPERATOR, 1);
                        // printf("struct nameFromBegining h: %s\n", struct_name);
                    }
                } else {
                    strncat(nameFromBegining, &ARRAY_IDENT_SUPP, 2);
                    strncat(nameFromBegining, &SUPPERATOR, 1);
                    // printf("struct nameFromBegining h1: %s\n", struct_name);
                }
            }
        } else {
            if (tracker->hdr.type != TN_INDEX && tracker->rnode->hdr.type == TN_IDENT) {
                strncat(namesFromEnd, ((leafnode *) tracker->rnode)->data.sval->str,
                        strlen(((leafnode *) tracker->rnode)->data.sval->str));
                strncat(namesFromEnd, &SUPPERATOR, 1);
            }
        }

        tracker = tracker->lnode;
        search_dpeth += 1;
    }
    reverse_by_chanks(namesFromEnd);

    // non leafs, means in situation like that: bs.G.iiii -> it's the
    strncat(nameFromBegining, namesFromEnd, strlen(namesFromEnd));
    strcpy(struct_name, nameFromBegining);
    // printf("Struct nameFromBegining %s\n", nameFromBegining);
    return index_depth;
}

//banana
//e!_0!dddd!
int get_n_dimension(char *array_identifier, int expected_dimension) {
    char singleChankHolder[100] = "";
    char temp2[100] = "";
    int dimension_counter = 0;
    char array_dimensions[500] = "";
    strcpy(array_dimensions, get_array_dimensions(array_identifier));

    for (int i = strlen(array_dimensions) - 2; i >= 0 && dimension_counter < expected_dimension; i--) {
        strcpy(singleChankHolder, "");
        do {
            strncat(singleChankHolder, &array_dimensions[i], 1);
            i--;
        } while (array_dimensions[i] != '!' && i >= 0 && i < strlen(array_dimensions));
        // strncat(singleChankHolder, &array_dimensions[i], 1);
        dimension_counter++;
    }
    reverse_string(singleChankHolder);
    return atoi(singleChankHolder);
}

int get_number_of_dimensions(char *array_dimensions) {
    int dimensions_counter = 0;
    int index = 0;
    while (index < strlen(array_dimensions)) {
        if (array_dimensions[index] == '!') {
            dimensions_counter++;
        }
        index++;
    }
    return dimensions_counter;
}

char *get_array_identifier(treenode *root) {
    char array_idnt[500] = "";
    treenode *tracker = root;

    while (tracker != NULL &&
           tracker->lnode != NULL &&
           tracker->rnode != NULL &&
           tracker->hdr.which != LEAF_T &&
           ((tracker->lnode->hdr.type == TN_IDENT && tracker->lnode->hdr.which == LEAF_T) ||
            (tracker->rnode->hdr.which == LEAF_T && tracker->lnode->hdr.type == TN_INDEX)))
//           (tracker->rnode->hdr.which == LEAF_T || tracker->rnode->hdr.type == TN_EXPR))
        tracker = tracker->lnode;

    if (tracker != NULL && tracker->hdr.type == TN_IDENT) {
        strcpy(array_idnt, ((leafnode *) tracker)->data.sval->str);
        strncat(array_idnt, &SUPPERATOR, 1);
//        strncat(array_idnt, &ARRAY_IDENT_SUPP, 2);
//        strncat(array_idnt, &SUPPERATOR, 1);
    }
//    reverse_by_chanks(array_idnt);
    char *blaaa = array_idnt;
    return blaaa;
}

void set_node_dimension(treenode *root) {
    current_dimension = 0;
    treenode *tracker = root;

    while (tracker != NULL && tracker->lnode != NULL && tracker->rnode != NULL &&
           tracker->hdr.which != LEAF_T && tracker->rnode->hdr.which == LEAF_T) {
        tracker = tracker->lnode;
        current_dimension++;
    }
}

bool is_constant(const treenode *root) {
    if (root == NULL || root->hdr.which == LEAF_T && root->hdr.type != TN_IDENT)
        return true;
    if (root->hdr.type == TN_IDENT)
        return false;
    return (is_constant(root->lnode) && is_constant(root->rnode));
}

bool both_childs_are_leafs(const treenode *root) {
    return root != NULL && root->rnode != NULL && root->lnode != NULL && root->rnode->hdr.which == LEAF_T &&
           root->lnode->hdr.which == LEAF_T;
}

int node_int_val(const leafnode *leaf) {
    return leaf->data.ival;
}

float node_float_val(const leafnode *leaf) {
    return leaf->data.fval;
}

double node_double_val(const leafnode *leaf) {
    return leaf->data.dval;
}

bool has_immidiate_expression(const treenode *root) {
    return both_childs_are_leafs(root);
}

const char *get_immidiate_value(const treenode *root) {
    leafnode *left = root->lnode;
    leafnode *right = root->rnode;
    char result[50];
    memset(result, 0, sizeof(result));

    if (left->hdr.type == TN_INT && right->hdr.type == TN_INT) {
        int leftChildVal = left->data.ival;
        int rightChildVal = right->data.ival;
        itoa(leftChildVal - rightChildVal, result, 10);
    } else if (left->hdr.type == TN_REAL && right->hdr.type == TN_REAL) {
        double leftChildVal = left->data.ival;
        double rightChildVal = right->data.ival;
        itoa(leftChildVal - rightChildVal, result, 10);
    } else if (left->hdr.type == TN_REAL && right->hdr.type == TN_INT) {
        double leftChildVal = left->data.ival;
        int rightChildVal = right->data.ival;
        itoa(leftChildVal - rightChildVal, result, 10);
    } else if (left->hdr.type == TN_INT && right->hdr.type == TN_REAL) {
        int leftChildVal = left->data.ival;
        double rightChildVal = right->data.ival;
        itoa(leftChildVal - rightChildVal, result, 10);
    }

    result[strcspn(result, "\n")] = 0;
    char *res = result;
    return res;
}

// returns true weather subtree contains just immediate values
bool is_immediate_value(treenode *root) {
    if (root == NULL || (((leafnode *) (root))->hdr.type == TN_INT || ((leafnode *) (root))->hdr.type == TN_REAL))
        return true;
    if (root->hdr.type != TN_INT && root->hdr.type != TN_REAL && root->hdr.type != TN_EXPR)
        return false;
    return (is_immediate_value(root->lnode) && is_immediate_value(root->rnode));
}
#define INT_MAX		2147483647
float evaluate_expression(treenode *root) {
    float evaluated_expression = 0;
    float leftSubtreeVal, rightSubtreeVal;
    leafnode *leaf;
    if (!root)
        return evaluated_expression;

    switch (root->hdr.which) {
        case LEAF_T:
            leaf = (leafnode *) root;
            switch (leaf->hdr.type) {
                case TN_INT:
                    return leaf->data.ival;
                    break;
                case TN_REAL:
                    return leaf->data.dval;
                    break;
                case TN_IDENT:
                    return INT_MAX;
                    break;
//                default:
//                    printf("barak unhandled leaf bro, ist's type is: %d\n", leaf->hdr.type);
            }
            break;
        case NODE_T:
            switch (root->hdr.tok) {
                case PLUS:
                    /* Plus token "+" */
                    return evaluate_expression(root->lnode) + evaluate_expression(root->rnode);
                    break;
                case MINUS:
                    /* Minus token "-" */
                    /* e.g. x-y; */
                    return evaluate_expression(root->lnode) - evaluate_expression(root->rnode);
                    break;

                case DIV:
                    /* Divide token "/" */
                    leftSubtreeVal = evaluate_expression(root->lnode);
                    rightSubtreeVal = evaluate_expression(root->rnode);
                    return (rightSubtreeVal == 0) ? 0 : leftSubtreeVal / rightSubtreeVal;
                    break;

                case STAR:
                    leftSubtreeVal = evaluate_expression(root->lnode);
                    rightSubtreeVal = evaluate_expression(root->rnode);
                    return leftSubtreeVal * rightSubtreeVal;
                    break;
                case AND:
                    return evaluate_expression(root->lnode) && evaluate_expression(root->rnode);
                    break;
                case OR:
                    /* Or token "||" */
                    return evaluate_expression(root->lnode) || evaluate_expression(root->rnode);
                    break;

                case NOT:
                    /* Not token "!" */
                    return !(evaluate_expression(root->lnode) == evaluate_expression(root->rnode));
                    break;

                case GRTR:
                    /* Greater token ">" */
                    return evaluate_expression(root->lnode) > evaluate_expression(root->rnode);
                    break;

                case LESS:
                    /* Less token "<" */
                    return evaluate_expression(root->lnode) < evaluate_expression(root->rnode);
                    break;

                case EQUAL:
                    /* Equal token "==" */
                    return evaluate_expression(root->lnode) == evaluate_expression(root->rnode);
                    break;

                case NOT_EQ:
                    /* Not equal token "!=" */
                    return evaluate_expression(root->lnode) != evaluate_expression(root->rnode);
                    break;

                case LESS_EQ:
                    /* Less or equal token "<=" */
                    return evaluate_expression(root->lnode) <= evaluate_expression(root->rnode);
                    break;

                case GRTR_EQ:
                    /* Greater or equal token ">=" */
                    return evaluate_expression(root->lnode) >= evaluate_expression(root->rnode);
                    break;
                case IDENT:
                    return INT_MAX;
                    break;
                default:
                    break;
//                    printf("UNHANDLED TYPE: %d\n", root->hdr.tok);
            }
            break;
    }
    return evaluated_expression;
}

// returns true weather right operand is 0, for cases such as a -= 0
bool is_sub_tree_value_is_zero(const treenode *root) {
    if (root->hdr.type == TN_EXPR)
        return evaluate_expression(root) == 0;

    return root != NULL &&
                // for leaf
                (root->hdr.which == LEAF_T &&
                ((root->hdr.type == TN_INT  && ((leafnode *)root)->data.ival == 0)      ||
                 (root->hdr.type == TN_REAL && ((leafnode *)root)->data.dval == 0.0)    ||
                 (root->hdr.type == TN_IDENT)))                                         ||

                 // For tree
                (root->hdr.which != LEAF_T && root->rnode != NULL && ((leafnode *) root->rnode)->data.ival == 0);
}

// returns true weather right operand is 0, for cases such as a -= 0
bool is_sub_tree_value_is_one(const treenode *root) {
    if (root->hdr.type == TN_EXPR)
        return evaluate_expression(root) == 1;

    return root != NULL &&
           // for leaf
           (root->hdr.which == LEAF_T &&
            ((root->hdr.type == TN_INT  && ((leafnode *)root)->data.ival == 1)      ||
             (root->hdr.type == TN_REAL && ((leafnode *)root)->data.dval == 1.0)    ||
             (root->hdr.type == TN_IDENT)))                                         ||

           // For tree
           (root->hdr.which != LEAF_T && root->rnode != NULL && ((leafnode *) root->rnode)->data.ival == 1);
}
bool can_reduce_fractures(const treenode* root) {
    float leftSubtreeVal, rightSubtreeVal;
    switch (root->hdr.tok) {
        case DIV:
            // We are div, can reduce with mul
            if (root->rnode != NULL &&
                root->lnode != NULL && root->lnode->hdr.tok == STAR && root->lnode->rnode != NULL) {
                leftSubtreeVal = evaluate_expression(root->lnode->rnode);
                rightSubtreeVal = evaluate_expression(root->rnode);
                return leftSubtreeVal == rightSubtreeVal;
            }
        break;
        case MINUS:
            if (root->rnode != NULL &&
                root->lnode != NULL && root->lnode->hdr.tok == PLUS && root->lnode->rnode != NULL) {
                leftSubtreeVal = evaluate_expression(root->lnode->rnode);
                rightSubtreeVal = evaluate_expression(root->rnode);
                return leftSubtreeVal == rightSubtreeVal;
            }
        break;
    }
    return false;
}

// returns true weather right operand is 1, for cases such as a *= 1
bool is_right_operand_is_one(const treenode *root) {
    if (root->hdr.type == TN_EXPR)
        return evaluate_expression(root) == 1;

    return (root != NULL && ((leafnode *) root)->data.ival == 1);
}

// returns true weather subtree contains just immediate values
bool is_immidiate_value_is_zero(treenode *root) {
    if (root == NULL || root->hdr.which == LEAF_T)
        return (((leafnode *) (root))->hdr.type == TN_INT && ((leafnode *) (root))->data.ival == 0 ||
                ((leafnode *) (root))->hdr.type == TN_REAL && ((leafnode *) (root))->data.dval == 0);
    if (root->hdr.type == TN_EXPR)
        return evaluate_expression(root) == 0;
    if (root->hdr.type != TN_INT && root->hdr.type != TN_REAL)
        return false;
    return (is_immidiate_value_is_zero(root->lnode) && is_immidiate_value_is_zero(root->rnode));
}

void print_immediate_value_II(treenode *root) {
    if (root == NULL || (((leafnode *) (root))->hdr.type == TN_INT)) {
        printf("LDC %d\n", ((leafnode *) (root))->data.ival);
    }

    if (root == NULL || ((leafnode *) (root))->hdr.type == TN_REAL) {
        printf("LDC %f\n", ((leafnode *) (root))->data.dval);
    }
//    if(root->hdr.type != TN_INT && root->hdr.type != TN_REAL && root->hdr.type != TN_EXPR)
//        return 0;
//    if(root->hdr.type==TN_EXPR)
//    {
//        return();
//    }
//    return (root.)
//    return get_immediate_value_II(root->rnode) + get_immediate_value_II(root->lnode);
}
void print_evaluated_value(const treenode *root) {
    float ceilVal = ceil(evaluate_expression(root));
    float floorVal = floor(evaluate_expression(root));
    if (ceilVal == floorVal){
        int integerVal = ceilVal;
        printf("LDC %d\n", integerVal);
    }
    else
        printf("LDC %f\n", evaluate_expression(root));
}
void print_immediate_value(const treenode *root);

void print_immediate_sub_tree(const treenode *root);


void print_correct_method(const treenode* root){
    switch (root->hdr.tok) {
        case MINUS:
            printf("SUB\n");
            break;
        case DIV:
            printf("DIV\n");
            break;
        case STAR:
            printf("MUL\n");
            break;
        case PLUS:
            printf("ADD\n");
            break;
        default:
            break;
    }
}

int get_number_of_variables_in_sub_tree(treenode* root) {
    if (root == NULL || root->hdr.which == LEAF_T && root->hdr.type != TN_IDENT)
        return 0;
    else if (root->hdr.which == LEAF_T && root->hdr.type == TN_IDENT)
        return 1;
    return get_number_of_variables_in_sub_tree(root->rnode) +
                get_number_of_variables_in_sub_tree(root->lnode);
}

void print_ident_address(treenode* root) {
    if (root == NULL)
        return;
    if (root->hdr.which == LEAF_T && root->hdr.type == TN_IDENT)
    {
        printf("LDC %d\n", get_variable_from_table(((leafnode*)root)->data.sval->str));
        printf("IND\n");
        return;
    }
    if (root->hdr.which != LEAF_T){
        print_ident_address(root->lnode);
        print_ident_address(root->rnode);
    }
}

int get_number_of_neg_in_a_row(treenode* root){
    if (root == NULL || root->hdr.which == LEAF_T && root->hdr.tok != MINUS)
        return 0;
    else if (root->hdr.tok == MINUS && (root->lnode == NULL || root->rnode != NULL))
        return 1 + get_number_of_neg_in_a_row(root->rnode);
}
/*
*	This recursive function is the main method for Code Generation
*	Input: treenode (AST)
*	Output: prints the Pcode on the console
*/
int code_recur(treenode *root) {
    if (symbolTalble == NULL)
        print_symbol_table(root);
    if_node *ifn;
    for_node *forn;
    leafnode *leaf;
    Variable target_var;
    Variable src_var;
    treenode *right_node;
    treenode *left_node;

    if (!root)
        return SUCCESS;

    switch (root->hdr.which) {
        case LEAF_T:
            leaf = (leafnode *) root;
            switch (leaf->hdr.type) {
                // case TN_LABEL:
                // 	/* Maybe you will use it later */
                // 	break;

                case TN_IDENT:
                    if (strcmp(leaf->data.sval->str, "printf") != 0 && strcmp(leaf->data.sval->str, "main") != 0) {
                        //lihi here
                        // printf("HEERE!!!\n");
                        // printf("Need to load variable identified as: %s%s\n", leaf->data.sval->str, " from memory");
                        // src_var = get_variable_from_table(leaf->data.sval->str);
                        // if you remove this comment you should check b = a<6;
//                        if (should_print_id_and_ind == 1) {
                        if (get_variable_from_table(struct_name) != -1) {
                            printf("LDC %d\n", get_variable_from_table(struct_name));
                        } else {
                            char index[50] = "";
                            strcpy(index, "");
                            strncat(index, leaf->data.sval->str, strlen(leaf->data.sval->str));
                            if (get_variable_from_table(index) != -1) {
                                printf("LDC %d\n", get_variable_from_table(index));
                            } else {
                                strncat(index, &SUPPERATOR, 1);
                                if (get_variable_from_table(index) != -1)
                                    printf("LDC %d\n", get_variable_from_table(index));
                                else {
                                    strncat(index, &ARRAY_IDENT_SUPP, 2);
                                    if (get_variable_from_table(index) != -1)
                                        printf("LDC %d\n", get_variable_from_table(index));
                                }
                            }
                        }
//                        }
                    }
                    /*
                            *	In order to get the identifier name you have to use:
                            *	leaf->data.sval->str
                            */
                    break;

                    // case TN_COMMENT:
                    // 	/* Maybe you will use it later */
                    // 	break;

                    // case TN_ELLIPSIS:
                    // 	/* Maybe you will use it later */
                    // 	break;

                case TN_STRING:
                    /* Maybe you will use it later */
                    break;

                case TN_TYPE:
                    /* Maybe you will use it later */
                    break;

                case TN_INT:
                    /*
                            *	In order to get the int value you have to use:
                            *	leaf->data.ival
                            */
                    printf("LDC %d\n", leaf->data.ival);
                    break;

                case TN_REAL:
                    /*
                            *	In order to get the real value you have to use:
                            *	leaf->data.dval
                            */
                    printf("LDC %f\n", leaf->data.dval);
                    break;
                default:
                    printf("barak unhandled leaf bro, it's type is: %d\n", leaf->hdr.type);
            }
            break;

        case IF_T:
            ifn = (if_node *) root;
            switch (ifn->hdr.type) {
                case TN_IF:
                    if (ifn->else_n == NULL) {
                        /* if case */
                        code_recur(ifn->cond);
                        switch (ifn->cond->hdr.type) {
                            case TN_IDENT:
                                leaf = (leafnode *) ifn->cond;
//                                printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                printf("IND\n");
                                break;
                            default:
                                // printf("BBBBB\n type is: %d\n", ifn->cond->hdr.which);
                                break;
                        }
                        printf("FJP end_if_%d\n", root->hdr.line);
                        code_recur(ifn->then_n);
                        printf("end_if_%d%s\n", root->hdr.line, ":");
                    } else {
                        code_recur(ifn->cond);
                        printf("FJP else_%d\n", root->hdr.line);
                        code_recur(ifn->then_n);
                        printf("ujp end_%d\n", root->hdr.line);
                        printf("else_%d%s\n", root->hdr.line, ":");
                        code_recur(ifn->else_n);
                        printf("end_%d%s\n", root->hdr.line, ":");
                    }

                    return 0;

                case TN_COND_EXPR:
                    code_recur(ifn->cond);
                    printf("FJP else_condition_%d%s%d\n", ifn->cond->hdr.line, "_", ifn->cond->hdr.col);
                    code_recur(ifn->then_n);
                    printf("ujp after_condition_%d%s%d\n", ifn->cond->hdr.line, "_", ifn->cond->hdr.col);
                    printf("else_condition_%d%s%d%s\n", ifn->cond->hdr.line, "_", ifn->cond->hdr.col, ":");
                    code_recur(ifn->else_n);
                    printf("ujp after_condition_%d%s%d\n", ifn->cond->hdr.line, "_", ifn->cond->hdr.col);
                    printf("after_condition_%d%s%d%s\n", ifn->cond->hdr.line, "_", ifn->cond->hdr.col, ":");
                    break;

                default:
                    /* Maybe you will use it later */
                    code_recur(ifn->cond);
                    code_recur(ifn->then_n);
                    code_recur(ifn->else_n);
            }
            break;

        case FOR_T:
            forn = (for_node *) root;
            switch (forn->hdr.type) {

                case TN_FUNC_DEF:
                    /* Function definition */
                    /* e.g. int main(...) { ... } */
                    /* Look at the output AST structure! */
                    code_recur(forn->init);
                    code_recur(forn->test);
                    code_recur(forn->incr);
                    code_recur(forn->stemnt);
                    break;
                case TN_FOR:
                    /* For case*/
                    /* e.g. for(i=0;i<5;i++) { ... } */
                    /* Look at the output AST structure! */
                    last_loop_end_lable_line_num = root->hdr.line;
                    strcpy(break_dest, "end_of_for_");
                    code_recur(forn->init);
                    printf("entering_for_%d%s\n", root->hdr.line, ":");
                    code_recur(forn->test);
                    printf("FJP end_of_for_%d\n", root->hdr.line);
                    code_recur(forn->stemnt);
                    code_recur(forn->incr);
                    printf("ujp entering_for_%d\n", root->hdr.line);
                    printf("end_of_for_%d%s\n", root->hdr.line, ":");
                    break;
                default:
                    /* Maybe you will use it later */
                    code_recur(forn->init);
                    code_recur(forn->test);
                    code_recur(forn->stemnt);
                    code_recur(forn->incr);
            }
            break;

        case NODE_T:
            switch (root->hdr.type) {
                case TN_DEREF:
                    /* pointer derefrence - for HW2! */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    printf("IND\n");
                    break;
                case TN_PARBLOCK:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_PARBLOCK_EMPTY:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_TRANS_LIST:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_FUNC_DECL:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_FUNC_CALL:
                    /* Function call */
                    // printf("HI\n");
                    if (strcmp(((leafnode *) root->lnode)->data.sval->str, "printf") == 0) {
                        /* printf case */
                        /* The expression that you need to print is located in */
                        /* the currentNode->right->right sub tree */
                        /* Look at the output AST structure! */
                        // code_recur(root->lnode);

                        memset(struct_name, 0, sizeof(struct_name));
                        code_recur(root->rnode);
                        printf("PRINT\n");
                    } else {
                        /* other function calls - for HW3 */
                        code_recur(root->lnode);
                        code_recur(root->rnode);
                    }
                    break;

                case TN_BLOCK:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_ARRAY_DECL:
                    /* array declaration - for HW2 */
                    // printf("BBBBBBBB\n");
                    // code_recur(root->lnode);
                    // code_recur(root->rnode);
                    break;

                case TN_EXPR_LIST:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    // printf("before\n");
                    if (root->rnode != NULL && root->rnode != NULL && root->rnode->lnode != NULL &&
                        root->rnode->rnode == NULL && root->rnode->lnode->hdr.type == TN_IDENT &&
                        root->rnode->lnode->hdr.which == LEAF_T) {
                        printf("LDC %d\n", get_variable_from_table(((leafnode *) root->rnode->lnode)->data.sval->str));
                        printf("IND\n");
                    }
                    code_recur(root->rnode);


                    // trying new statement
                    if (get_variable_from_table(struct_name) != -1)
                        printf("LDC %d\n", get_variable_from_table(struct_name));
                    if (root->rnode != NULL && (root->rnode->hdr.type != TN_INT &&
                                                root->rnode->hdr.type != TN_REAL &&
                                                root->rnode->hdr.type != TN_EXPR))
                        printf("IND\n");
                    break;

                case TN_NAME_LIST:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_ENUM_LIST:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_FIELD_LIST:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_PARAM_LIST:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_IDENT_LIST:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_TYPE_LIST:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_COMP_DECL:
                    /* struct component declaration - for HW2 */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_DECL:
                    if (root->lnode != NULL &&
                        root->lnode->lnode != NULL &&
                        root->lnode->lnode->hdr.type == TN_TYPE &&
                        root->rnode != NULL &&
                        (root->rnode->hdr.type == TN_IDENT ||
                         root->rnode->hdr.type == TN_DECL))  //(root->rnode->hdr.which == LEAF_T))
                    {

                    } else {
                        code_recur(root->lnode);
                        code_recur(root->rnode);
                    }
                    break;

                    break;
                case TN_DECL_LIST:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_DECLS:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_STEMNT_LIST:
                    /* Maybe you will use it later */
                    // printf("hello\n");
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_STEMNT:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_BIT_FIELD:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_PNTR:
                    /* pointer - for HW2! */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_TYPE_NME:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_INIT_LIST:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_INIT_BLK:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_OBJ_DEF:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_OBJ_REF:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_CAST:
                    /* Maybe you will use it later */
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;

                case TN_JUMP:
                    if (root->hdr.tok == RETURN) {
                        /* return jump - for HW2! */
                        code_recur(root->lnode);
                        code_recur(root->rnode);
                    } else if (root->hdr.tok == BREAK) {
                        /* break jump - for HW2! */
                        printf("UJP %s%d\n", break_dest, last_loop_end_lable_line_num);
                        code_recur(root->lnode);
                        code_recur(root->rnode);
                    } else if (root->hdr.tok == GOTO) {
                        /* GOTO jump - for HW2! */
                        code_recur(root->lnode);
                        code_recur(root->rnode);
                    }
                    break;

                case TN_SWITCH:
                    /* Switch case - for HW2! */
                    code_recur(root->lnode);
                    if (root->lnode != NULL) {
                        if (root->lnode->hdr.type == TN_IDENT) {
                            leaf = ((leafnode *) root->lnode);
                            printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                            printf("IND\n");
                        } else {
                            code_recur(root->lnode);
                        }
                    }
                    last_loop_end_lable_line_num = root->hdr.line;
                    strcpy(break_dest, "end_switch_");
                    code_recur(root->rnode);
                    printf("end_switch_%d%s\n", root->hdr.line, ":");
                    break;

                case TN_INDEX:
                    /* call for array - for HW2! */
//                    set_array_identifier(root);

//                    char* array_indexes = get_array_indexes(root);
//                    char* array_dimensions = get_array_dimensions(root);
                    code_recur(root->lnode);
                    memset(struct_name, 0, sizeof(struct_name));
                    char bla[500] = "";
                    code_recur(root->rnode);
                    set_node_dimension(root);
                    strcpy(bla, get_array_identifier(root));
                    int number_of_dimensions = get_number_of_dimensions_for_array(get_array_identifier(root));
                    if (root->lnode != NULL && root->lnode->hdr.type != TN_DEREF) {
                        int ixaValue = get_arrays_cell_size(get_array_identifier(root));

                        // prepares data for single cell generation
                        int index;
                        for (index = current_dimension; index < number_of_dimensions; index++) {
                            if (get_n_dimension(bla, index) != 0)
                                ixaValue *= get_n_dimension(bla, index);
                        }

                        // In case right node is an array, we have to print it's value and not just the address,
                        // that's why we use IND here, for example a[a[2]]
                        if (root->rnode != NULL && root->rnode->hdr.type == TN_INDEX) {
                            printf("IND\n");
                        }
                        // it must be here, because we have to print the value of the ideentifier, such as a[i]
                        // when i = 7, means we want a[7]
                        if (root->rnode != NULL && root->rnode->hdr.type == TN_IDENT)
                            printf("IND\n");
//                        printf("Array identifier is: %s\n", array_identifier);
                        if ((root->lnode != NULL && root->lnode->hdr.type == TN_IDENT) ||
                            (root->lnode != NULL &&
                             //root->lnode->hdr.which == LEAF_T &&
                             root->rnode != NULL && root->rnode->hdr.which == LEAF_T))
                            printf("IXA %d\n", ixaValue);
                    } else
                        printf("IXA 1\n");
                    break;

                case TN_SELECT:
                    /* struct case - for HW2! */
                    if (root->hdr.tok == ARROW) {
                        /* Struct select case "->" */
                        /* e.g. struct_variable->x; */
                        code_recur(root->lnode);
                        code_recur(root->rnode);
                    } else {
                        /* Struct select case "." */
                        /* e.g. struct_variable.x; */
                        memset(struct_name, 0, sizeof(struct_name));
                        int res = set_struct_name(root);
                        if (res != 0) {
                            // printf("tn array is in depth: %d\n", res);
                            left_node = root->lnode;
                            res -= 1;
                            while (left_node != NULL && res > 0) {
                                left_node = left_node->lnode;
                                res -= 1;
                            }

                            // printf("res is: %d\n", res);
                            // Im not sure we have to use it.. if just print fail
                            if (get_variable_from_table(struct_name) != -1) {
                                printf("LDC %d\n", get_variable_from_table(struct_name));
                                memset(struct_name, 0, sizeof(struct_name));
                            }
                            code_recur(root->lnode);
                        }
                    }
                    break;
                case TN_ASSIGN:
                    switch (root->hdr.tok) {
                        case EQ:
                            /* Regular assignment "=" */
                            /* e.g. x = 5; */
                            if (root->lnode != NULL &&
                                root->rnode != NULL &&
                                root->lnode->hdr.type == TN_IDENT &&
                                root->rnode->hdr.type == TN_EXPR &&
                                root->rnode->lnode != NULL && root->rnode->rnode == NULL &&
                                (root->rnode->hdr.tok == INCR || root->rnode->hdr.tok == DECR) &&
                                root->rnode->lnode->hdr.type != TN_DEREF &&
                                strcmp(((leafnode *) root->rnode->lnode)->data.sval->str,
                                       ((leafnode *) root->lnode)->data.sval->str) == 0) {
                                // because of c++ and c diffrences: x=x++ increments x in c++ and does nothing in c
                            } else if (root->rnode != NULL && is_immediate_value(root->rnode)) {
                                code_recur(root->lnode);
                                print_immediate_sub_tree(root);
                                printf("STO\n");
                                break;
                            } else {
                                code_recur(root->lnode);
                                // printf("struct name isa: %s\n", struct_name);
                                if (root->lnode != NULL && root->lnode->hdr.type == TN_SELECT)
                                    // root->lnode->lnode != NULL && root->lnode->lnode->hdr.type != TN_INDEX)
                                {
                                    if (get_variable_from_table(struct_name) != -1) {
                                        // printf("we would like to have the address of: %s\n", struct_name);
                                        printf("LDC %d\n", get_variable_from_table(struct_name));
                                        memset(struct_name, 0, sizeof(struct_name));
                                    }
                                }
                                code_recur(root->rnode);
                                if (root->rnode != NULL && root->rnode->hdr.type == TN_IDENT) {
                                    // WE REPLACED ldc here with IND because of case such as e = a
                                    // NO NEED TO GET THE IDENTIFIER HERE JUST NEED THE ADDRESS
                                    leaf = (leafnode *) root->rnode;
                                    printf("IND\n");
                                }
                                // We dont really know what this if means, but in case such as a = a + 6 we found double STO, so we removed it
//                                if (root->lnode != NULL && root->lnode->hdr.type == TN_IDENT &&
//                                    root->rnode->lnode != NULL && root->rnode->lnode->hdr.type == TN_IDENT &&
//                                    root->rnode != NULL && root->rnode->hdr.type == TN_EXPR &&
//                                    (root->rnode->hdr.tok != INCR && root->rnode->hdr.tok != DECR))
//                                    printf("STO\n");
                                if (root->rnode != NULL && root->rnode->hdr.type == TN_INDEX)
                                    printf("IND\n");
                            }
                            printf("STO\n");
                            break;
                        case PLUS_EQ:
                            /* Plus equal assignment "+=" */
                            /* e.g. x += 5; */
                            if (is_immediate_value(root->rnode) && is_sub_tree_value_is_zero(root->rnode)) {
                            } else {
                                code_recur(root->lnode);
                                if (root->lnode != NULL && root->lnode->hdr.type == TN_IDENT) {
                                    leaf = (leafnode *) root->lnode;
                                    printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                    printf("IND\n");
                                }
                                if (root->rnode != NULL && is_immediate_value(root->rnode)) {
                                    print_immediate_sub_tree(root);
                                }
                                else {
                                    code_recur(root->rnode);
                                    if (root->rnode != NULL && root->rnode->hdr.type == TN_IDENT) {
                                        leaf = (leafnode *) root->rnode;
                                        printf("IND\n");
                                    }
                                }
                                printf("ADD\n");
                                printf("STO\n");
                            }
                            break;
                        case MINUS_EQ:
                            /* Minus equal assigment "-=" */
                            /* e.g. x-= 5; */
                            if (is_immediate_value(root->rnode) && is_sub_tree_value_is_zero(root->rnode)) {
                            }
                            else {
                                    code_recur(root->lnode);
                                    if (root->lnode != NULL && root->lnode->hdr.type == TN_IDENT) {
                                        leaf = (leafnode *) root->lnode;
                                        printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                        printf("IND\n");
                                    }
                                    if (root->rnode != NULL && is_immediate_value(root->rnode)) {
                                        print_immediate_sub_tree(root);
                                    }
                                    else {
                                        code_recur(root->rnode);
                                        if (root->rnode != NULL && root->rnode->hdr.type == TN_IDENT) {
                                            leaf = (leafnode *) root->rnode;
                                            printf("IND\n");
                                        }
                                    }
                                    printf("SUB\n");
                                    printf("STO\n");
                                }
                            break;
                        case STAR_EQ:
                            /* Multiply equal assignment "*=" */
                            /* e.g. x *= 5; */
                            if (is_constant(root->rnode)) {
                                if (is_sub_tree_value_is_zero(root->rnode) ||
                                        is_sub_tree_value_is_one(root->rnode)) {
                                    if (is_sub_tree_value_is_zero(root->rnode)) {
                                        code_recur(root->lnode);
                                        printf("LDC 0\n");
                                        printf("STO\n");
                                    } else {
//                                        DOING NOTHING
                                    }
                                    break;
                                }
                                else {
                                    code_recur(root->lnode);
                                    print_ident_address(root);
                                    print_immediate_sub_tree(root);
                                }
                            } else {
                                code_recur(root->lnode);
                                if (root->rnode != NULL && evaluate_expression(root->rnode) == 0){
                                    if (root->rnode->hdr.type == TN_IDENT && root->rnode->hdr.which == LEAF_T) {
                                        print_ident_address(root);
                                        printf("MUL\n");
                                    }
                                    else
                                        printf("LDC 0\n");
                                    printf("STO\n");
                                    break;
                                }
                                else if (root->lnode != NULL && root->lnode->hdr.type == TN_IDENT) {
                                    leaf = (leafnode *) root->lnode;
                                    printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                    printf("IND\n");
                                }
                                if (root->rnode != NULL && is_immediate_value(root->rnode)){
                                    if (evaluate_expression(root->rnode) != 0)
                                        print_immediate_sub_tree(root);
                                } else {
                                    code_recur(root->rnode);
                                    if (root->rnode != NULL && root->rnode->hdr.type == TN_IDENT) {
                                        leaf = (leafnode *) root->rnode;
                                        printf("IND\n");
                                    }
                                }
                            }
                            printf("MUL\n");
                            printf("STO\n");
                            break;
                        case DIV_EQ:
                            /* Divide equal assignment "/=" */
                            /* e.g. x /= 5; */
                            if (is_right_operand_is_one(root->rnode)) {
                            } else {
                                code_recur(root->lnode);
                                if (root->lnode != NULL && root->lnode->hdr.type == TN_IDENT) {
                                    leaf = (leafnode *) root->lnode;
                                    printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                    printf("IND\n");
                                }
                                if (root->rnode != NULL && is_immediate_value(root->rnode)) {
                                    print_immediate_sub_tree(root);
                                }
                                else {
                                    code_recur(root->rnode);
                                    if (root->rnode != NULL && root->rnode->hdr.type == TN_IDENT) {
                                        leaf = (leafnode *) root->rnode;
                                        printf("IND\n");
                                    }
                                }
                                printf("DIV\n");
                                printf("STO\n");
                            }
                            break;
                        default:
                            printf("BUG, didn't handle assigment token: %d\n, ", root->hdr.tok);
                            break;
                    }
                    break;
                case TN_EXPR:
                    switch (root->hdr.tok) {
                        case CASE:
                            /* you should not get here */
                            printf("DPL\n");
                            code_recur(root->lnode);
                            code_recur(root->rnode);
                            printf("EQU \n");
                            break;

                        case INCR:
                            /* Increment token "++" */
                            if (root->lnode == NULL && root->rnode == NULL) {
                                leaf = (leafnode *) root;
                            } else if (root->lnode == NULL &&
                                       root->rnode != NULL &&
                                       root->rnode->hdr.type == TN_IDENT) {
                                leaf = (leafnode *) root->rnode;
                                printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                printf("IND\n");
                                printf("INC 1\n");
                                printf("STO\n");
                                printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                printf("IND\n");
                            } else if (root->lnode == NULL &&
                                       root->rnode != NULL &&
                                       root->rnode->hdr.type == TN_INDEX) {
                                // PRINT CELL ID IN ORDER TO INC
                                code_recur(root->rnode);
                                printf("DPL\n");
                                printf("IND\n");
                                printf("INC 1\n");
                                printf("STO\n");
                            } else if (root->rnode == NULL &&
                                       root->lnode != NULL &&
                                       root->lnode->hdr.type == TN_INDEX) {
                                // PRINT CELL ID IN ORDER TO INC
                                code_recur(root->lnode);
                                printf("DPL\n");
                                printf("IND\n");
                                printf("INC 1\n");
                                printf("STO\n");
                            } else if (root->lnode != NULL &&
                                       ((leafnode *) root->lnode)->hdr.type == TN_IDENT &&
                                       root->rnode == NULL) {
                                leaf = (leafnode *) root->lnode;
                                printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                printf("IND\n");
                                printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                printf("IND\n");
                                printf("INC 1\n");
                                printf("STO\n");
                            }
                            break;

                        case DECR:
                            /* Decrement token "--" */
                            if (root->lnode == NULL && root->rnode == NULL) {
                                leaf = (leafnode *) root;
                            } else if (root->lnode == NULL &&
                                       root->rnode != NULL &&
                                       root->rnode->hdr.type == TN_IDENT) {
                                leaf = (leafnode *) root->rnode;
                                printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                printf("IND\n");
                                printf("DEC 1\n");
                                printf("STO\n");
                                printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                printf("IND\n");
                            } else if (root->lnode == NULL &&
                                       root->rnode != NULL &&
                                       root->rnode->hdr.type == TN_INDEX) {
                                // PRINT CELL ID IN ORDER TO INC
                                code_recur(root->rnode);
                                printf("DPL\n");
                                printf("IND\n");
                                printf("DEC 1\n");
                                printf("STO\n");
                            } else if (root->rnode == NULL &&
                                       root->lnode != NULL &&
                                       root->lnode->hdr.type == TN_INDEX) {
                                // PRINT CELL ID IN ORDER TO INC
                                code_recur(root->lnode);
                                printf("DPL\n");
                                printf("IND\n");
                                printf("DEC 1\n");
                                printf("STO\n");
                            } else if (root->lnode != NULL &&
                                       ((leafnode *) root->lnode)->hdr.type == TN_IDENT &&
                                       root->rnode == NULL) {
                                leaf = (leafnode *) root->lnode;
                                printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                printf("IND\n");
                                printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                printf("LDC %d\n", get_variable_from_table(leaf->data.sval->str));
                                printf("IND\n");
                                printf("DEC 1\n");
                                printf("STO\n");
                            }

                            break;

                        case PLUS:
                            /* Plus token "+" */
                            code_recur(root->lnode);
                            if (root->lnode != NULL &&
                                (root->lnode->hdr.type == TN_IDENT ||
                                 root->lnode->hdr.type == TN_INDEX ||
                                 root->lnode->hdr.type == TN_SELECT))
                                printf("IND\n");
                            code_recur(root->rnode);
                            if (root->rnode != NULL &&
                                (root->rnode->hdr.type == TN_IDENT ||
                                 root->rnode->hdr.type == TN_INDEX ||
                                 root->rnode->hdr.type == TN_SELECT))
                                printf("IND\n");
                            print_correct_method(root);
                            break;
                        case MINUS:
                            /* Minus token "-" */
                            /* e.g. x-y; */
                            while (root->lnode != NULL && root->lnode->lnode != NULL &&
                                   root->rnode != NULL && can_reduce_fractures(root))
                                root = root->lnode->lnode;
                            if (get_number_of_variables_in_sub_tree(root) == 0 && !is_sub_tree_value_is_zero(root)){
                                print_evaluated_value(root);
                                break;
                            }
                            if (get_number_of_variables_in_sub_tree(root) == 1 && is_sub_tree_value_is_zero(root)) {
                                print_ident_address(root);
                                int number_of_neg_in_a_row = get_number_of_neg_in_a_row(root);
                                if (number_of_neg_in_a_row % 2 != 0)
                                    printf("NEG\n");
                                break;
                            }
                            code_recur(root->lnode);
                            if (root->lnode != NULL &&
                                root->lnode->hdr.type == TN_IDENT)
                                printf("IND\n");
                            code_recur(root->rnode);
                            if (root->rnode != NULL &&
                                root->rnode->hdr.type == TN_IDENT)
                                printf("IND\n");
                            if (root->lnode == NULL)
                                printf("NEG\n");
                            else
                                printf("SUB\n");
                            break;

                        case DIV:
                            /* Divide token "/" */
                            while (root->lnode != NULL && root->lnode->lnode != NULL &&
                                   root->rnode != NULL && can_reduce_fractures(root))
                                root = root->lnode->lnode;
                            if (root->hdr.which == LEAF_T){
                                code_recur(root);
                                printf("IND\n");
                                break;
                            }
                            code_recur(root->lnode);
                            if (root->lnode != NULL &&
                                root->lnode->hdr.type == TN_IDENT)
                                printf("IND\n");
                            code_recur(root->rnode);
                            if (root->rnode != NULL &&
                                root->rnode->hdr.type == TN_IDENT)
                                printf("IND\n");
                            print_correct_method(root);
                        break;

                        case STAR:
                            /* multiply token "*" */
                            if (is_right_operand_is_one(root->rnode)) {
                                printf("LDC 1\n");
                                break;
                            }
                            else if (is_immidiate_value_is_zero(root->rnode) && get_number_of_variables_in_sub_tree(root) == 0){
                                printf("LDC 0\n");
                                break;
                            }
                            else if (evaluate_expression(root) != 0 && get_number_of_variables_in_sub_tree(root) == 0)
                                print_evaluated_value(root);
                            else
                            {
                                code_recur(root->lnode);
                                if (root->lnode != NULL &&
                                    root->lnode->hdr.type == TN_IDENT)
                                    printf("IND\n");
                                code_recur(root->rnode);
                                if (root->rnode != NULL &&
                                    root->rnode->hdr.type == TN_IDENT)
                                    printf("IND\n");
                                print_correct_method(root);
                            }
                            break;
                        case AND:
                            /* And token "&&" */
                            code_recur(root->lnode);
                            if (root->lnode != NULL &&
                                (root->lnode->hdr.type == TN_IDENT ||
                                 root->lnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            code_recur(root->rnode);
                            if (root->rnode != NULL &&
                                (root->rnode->hdr.type == TN_IDENT ||
                                 root->rnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            printf("AND\n");
                            break;
                        case OR:
                            /* Or token "||" */
                            code_recur(root->lnode);
                            if (root->lnode != NULL &&
                                (root->lnode->hdr.type == TN_IDENT ||
                                 root->lnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            code_recur(root->rnode);
                            if (root->rnode != NULL &&
                                (root->rnode->hdr.type == TN_IDENT ||
                                 root->rnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            printf("OR\n");
                            break;

                        case NOT:
                            /* Not token "!" */
                            code_recur(root->lnode);
                            if (root->lnode != NULL &&
                                (root->lnode->hdr.type == TN_IDENT ||
                                 root->lnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            code_recur(root->rnode);
                            if (root->rnode != NULL &&
                                (root->rnode->hdr.type == TN_IDENT ||
                                 root->rnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            printf("NOT\n");
                            break;

                        case GRTR:
                            /* Greater token ">" */
                            code_recur(root->lnode);
                            if (root->lnode != NULL &&
                                (root->lnode->hdr.type == TN_IDENT ||
                                 root->lnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            code_recur(root->rnode);
                            if (root->rnode != NULL &&
                                (root->rnode->hdr.type == TN_IDENT ||
                                 root->rnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            printf("GRT\n");
                            break;

                        case LESS:
                            /* Less token "<" */
                            code_recur(root->lnode);
                            if (root->lnode != NULL &&
                                (root->lnode->hdr.type == TN_IDENT ||
                                 root->lnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            code_recur(root->rnode);
                            if (root->rnode != NULL &&
                                (root->rnode->hdr.type == TN_IDENT ||
                                 root->rnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            printf("LES\n");
                            break;

                        case EQUAL:
                            /* Equal token "==" */
                            code_recur(root->lnode);
                            if (root->lnode != NULL &&
                                (root->lnode->hdr.type == TN_IDENT ||
                                 root->lnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            code_recur(root->rnode);
                            if (root->rnode != NULL &&
                                (root->rnode->hdr.type == TN_IDENT ||
                                 root->rnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            printf("EQU\n");
                            break;

                        case NOT_EQ:
                            /* Not equal token "!=" */
                            code_recur(root->lnode);
                            if (root->lnode != NULL &&
                                (root->lnode->hdr.type == TN_IDENT ||
                                 root->lnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            code_recur(root->rnode);
                            if (root->rnode != NULL &&
                                (root->rnode->hdr.type == TN_IDENT ||
                                 root->rnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            printf("NEQ\n");
                            break;

                        case LESS_EQ:
                            /* Less or equal token "<=" */
                            code_recur(root->lnode);
                            if (root->lnode != NULL &&
                                (root->lnode->hdr.type == TN_IDENT ||
                                 root->lnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            code_recur(root->rnode);
                            if (root->rnode != NULL &&
                                (root->rnode->hdr.type == TN_IDENT ||
                                 root->rnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            printf("LEQ\n");
                            break;

                        case GRTR_EQ:
                            /* Greater or equal token ">=" */
                            code_recur(root->lnode);
                            if (root->lnode != NULL &&
                                (root->lnode->hdr.type == TN_IDENT ||
                                 root->lnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            code_recur(root->rnode);
                            if (root->rnode != NULL &&
                                (root->rnode->hdr.type == TN_IDENT ||
                                 root->rnode->hdr.type == TN_INDEX))
                                printf("IND\n");
                            printf("GEQ\n");
                            break;
                        default:
                            code_recur(root->lnode);
                            code_recur(root->rnode);
                            break;
                    }
                    break;

                case TN_WHILE:
                    /* While case */
                    last_loop_end_lable_line_num = root->hdr.line;
                    strcpy(break_dest, "end_while_");
                    printf("while_statement_%d%s\n", root->hdr.line, ":");
                    code_recur(root->lnode);
                    printf("FJP end_while_%d\n", root->hdr.line);
                    code_recur(root->rnode);
                    printf("UJP while_statement_%d\n", root->hdr.line);
                    printf("end_while_%d%s\n", root->hdr.line, ":");
                    break;

                case TN_DOWHILE:
                    /* Do-While case */
                    last_loop_end_lable_line_num = root->hdr.line;
                    strcpy(break_dest, "end_do_while_");
                    printf("do_while_statement_%d%s\n", root->hdr.line, ":");
                    code_recur(root->rnode);
                    code_recur(root->lnode);
                    printf("FJP end_do_while_%d\n", root->hdr.line);
                    printf("UJP do_while_statement_%d\n", root->hdr.line);
                    printf("end_do_while_%d%s\n", root->hdr.line, ":");
                    break;

                case TN_LABEL:
                    code_recur(root->lnode);
                    printf("FJP case_%d\n", root->hdr.line);
                    code_recur(root->rnode);
                    printf("case_%d%s\n", root->hdr.line, ":");
                    break;

                default:
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;
            }
            break;

        case NONE_T:
            printf("Error: Unknown node type!\n");
            exit(FAILURE);
    }

    return SUCCESS;
}

void print_immediate_sub_tree(const treenode *root) {
    if (is_immidiate_value_is_zero(root->rnode)) {
        printf("LDC 0\n");
    } else{
        print_immediate_value(root);
    }
}

void print_immediate_value(const treenode *root) {
    float ceilVal = ceil(evaluate_expression(root->rnode));
    float floorVal = floor(evaluate_expression(root->rnode));
    if (ceilVal == floorVal){
        int integerVal = ceilVal;
        printf("LDC %d\n", integerVal);
    }
    else
        printf("LDC %f\n", evaluate_expression(root->rnode));
}

char struct_definition[5000] = "";
const char PAIR_SUP = '~';
const char STR_END = '\0';
int should_print_id = 1;

int add_simple_struct_to_symbol_table(char *string, char *structIdentifier, char *middleName, int start_index) {
    int i = start_index;
    tn_t vartype = 0;
    char typeC[1000] = "";
    char name[1000] = "";
    int type = 0;
    int was_found = 0;

    while (i < strlen(string) && was_found == 0) {
        if (string[i] == PAIR_SUP) {
            // printf("typeC is %s\n", typeC);
            type = atoi(typeC);
            switch (type) {
                case 0:
                    break;
                case INT:
                    vartype = TN_INT;
                    break;
                case DOUBLE:
                case FLOAT:
                    vartype = TN_REAL;
                    break;
                default:
                    printf("UNHANDLED TOKEN%d\n", type);
                    break;
            };
            strcpy(typeC, "");
            i++;
            strncat(name, structIdentifier, strlen(structIdentifier));
            strncat(name, middleName, strlen(middleName));
            strncat(name, &SUPPERATOR, 1);

            while (string[i] != SUPPERATOR) {
                strncat(name, &string[i], 1);
                i++;
            }
            // printf("name is:%s\n", name);
            strncat(name, &SUPPERATOR, 1);
            symbolTalble->vars = add_variable_to_symbol_table(name, vartype, symbolTalble->vars);
            strcpy(name, "");
            was_found = 1;
        } else {
            strncat(typeC, &string[i], 1);
            i++;
        }
    }
    return i;
}

char old_middle_name[1000] = "";
char curr_middle_name[1000] = "";

int is_pointer_defenition(const treenode *root);

void add_complex_data_type(char *string, char *structIdnt, int startIndex, int endIndex) {
    int i = startIndex;
    int complex_counter = 0;
    int complex_start_index = 0;
    int complex_end_index = 0;
    int complex_identifier_start_index = 0;
    int complex_identifier_end_index = 0;
    while (i < endIndex) {
        if (string[i] == '%') {
            strcpy(old_middle_name, curr_middle_name);
            i++;
            strncat(curr_middle_name, &SUPPERATOR, 1);
            while (string[i] != '%') {
                strncat(curr_middle_name, &string[i], 1);
                i++;
            }
        } else if (string[i] == '#') {
            complex_start_index = i;
            complex_counter = 1;
            i++;
            while (complex_counter != 0) {
                i++;
                if (string[i] == '#') {
                    if (string[i + 1] != '%')
                        complex_counter--;
                    else
                        complex_counter++;
                }
            }
            complex_end_index = i;
            // printf("FOUND DECLERATION OF COMPLEX, which starts at: %d\n", complex_start_index);
            // printf("                                  AND ENDS AT: %d\n", complex_end_index);
            // printf("middle name is: %s\n", middle_name);
            add_complex_data_type(string, structIdnt, complex_start_index + 1, complex_end_index);
            strcpy(curr_middle_name, old_middle_name);
        } else {
            // printf("before a/dd_simple_struct_to_symbol_table, index of i is: %d\n", i);
            i = add_simple_struct_to_symbol_table(string, structIdnt, curr_middle_name, i);
            // printf("after ad/d_simple_struct_to_symbol_table, index of i is: %d\n", i);
        }
        i++;
    }
}

void add_struct_to_symbolTable(char *string, char *structIdnt, char *structName) {
    int i = 0;
    int complex_counter = 0;
    int complex_start_index = 0;
    int complex_end_index = 0;

    i = 0;
    while (i < strlen(string)) {
        if (string[i] == '#') {
            complex_start_index = i;
            complex_counter = 1;
            i++;
            while (complex_counter != 0) {
                i++;
                if (string[i] == '#') {
                    if (string[i + 1] != '%')
                        complex_counter--;
                    else
                        complex_counter++;
                }
            }
            complex_end_index = i;
            // printf("FOUND DECLERATION OF COMPLEX, which starts at: %d\n", complex_start_index);
            // printf("                                  AND ENDS AT: %d\n", complex_end_index);
            // printf("CALLING TO A FRIEND WHICH WILL HANDLE IT!\n");
            add_complex_data_type(string, structIdnt, complex_start_index + 1, complex_end_index);
        } else {
            i = add_simple_struct_to_symbol_table(string, structIdnt, "", i);
        }
        // printf("ADTER i = %d\n", i);
        i++;
    }
    // set_struct_size(&tbl, structName, complex_type_size);
    // printf("Setting the size of var: %s\n", structIdnt);
    // printf("To be: %d\n", complex_type_size);
    // set_variable_size(structIdnt, complex_type_size);
    strcpy(old_middle_name, "");
    strcpy(curr_middle_name, "");
}

void add_single_cell_to_array(char *id, char *typeAsString, tn_t typeAsEnum) {
    if (typeAsEnum == TN_DECL)
        add_struct_to_symbolTable(get_struct_value_str(typeAsString), id, typeAsString);
    else {
        symbolTalble->vars = add_variable_to_symbol_table(id, typeAsEnum, symbolTalble->vars);
    }
}

void
add_array_to_symbol_table(int size, char *typeAsString, tn_t typeAsEnum, char *identitfier, char *dimensionsArray,
                          int numberOfDimensions) {
    char snum[1000];
    int i = 0;
    char temp[1000];
    char fixedIdentifier[1000] = "";
    int complex_type_size = 0;
    int tempIndex = 0;

    // printf("received id is: %s\n", identitfier);
    // printf("fixed id is:! %s\n", fixedIdentifier);
    // printf("about to init an array in size of: %d\n", size);
    // printf("array typeString: %s\n", typeAsString);
    // printf("array typeAsEnum: %d\n", typeAsEnum);
    // printf("identifier is: %s\n", fixedIdentifier);

    // removed this if statement since the size and dimenstions of the array was not appered in mapping


//            symbolTalble->vars = add_variable_to_symbol_table(fixedIdentifier, typeAsEnum, symbolTalble->vars);
    // printf("Setting the size of var: %s\n", identitfier);
    // printf("To be: %d\n", complex_type_size);
//            if (typeAsEnum != TN_DECL) {
//
//            }
//            else{
//
//            }
//        }

    for (i = 0; i < size; i++) {
        strcpy(fixedIdentifier, "");
        strcpy(fixedIdentifier, identitfier);
        strncat(fixedIdentifier, &SUPPERATOR, 1);
        strncat(fixedIdentifier, "_", 1);
        itoa(i, snum, 10);
        strncat(fixedIdentifier, snum, 1000);
        add_single_cell_to_array(fixedIdentifier, typeAsString, typeAsEnum);
        if (i == 0) {
            strcpy(fixedIdentifier, "");
            strcpy(fixedIdentifier, identitfier);
            strncat(fixedIdentifier, &SUPPERATOR, 1);
            if (typeAsEnum != TN_DECL) {
                // printf("dimensionsArray: %s\n", dimensionsArray);
                // printf("<add_array_to_symbol_table()> ID is: %s\n", fixedIdentifier);
//                    strcpy(fixedIdentifier, identitfier);
//                    strncat(fixedIdentifier, &SUPPERATOR, 1);
//                    add_single_cell_to_array(fixedIdentifier, typeAsString, typeAsEnum);
                set_variable_size(fixedIdentifier, 1);
                arraysSymbolTable->arrays = add_array_to_arrays_mapping(arraysSymbolTable->arrays, fixedIdentifier, 1,
                                                                        dimensionsArray, numberOfDimensions);
            } else {
                tempIndex = 0;
                strcpy(temp, get_struct_value_str(typeAsString));
                while (tempIndex < strlen(temp)) {
                    if (temp[tempIndex] == PAIR_SUP)
                        complex_type_size += 1;
                    tempIndex++;
                }
//                    add_single_cell_to_array(identitfier, typeAsString, typeAsEnum);
                set_variable_size(fixedIdentifier, complex_type_size);
                arraysSymbolTable->arrays = add_array_to_arrays_mapping(arraysSymbolTable->arrays, fixedIdentifier,
                                                                        complex_type_size, dimensionsArray,
                                                                        numberOfDimensions);
            }
        }
    }
}

int is_simple_premitive_var_decleration(treenode *root) {
    treenode *left_node = (treenode *) root->lnode;
    treenode *right_node = (treenode *) root->rnode;

    // First case, handling simple variable initialization
    return left_node != NULL && left_node->hdr.type == TN_TYPE_LIST &&
           left_node->lnode != NULL && left_node->lnode->hdr.type == TN_TYPE &&
           (right_node != NULL && right_node->hdr.type == TN_IDENT ||
            // for case such as int a;
            (right_node != NULL && right_node->hdr.type == TN_ASSIGN && right_node->lnode != NULL &&
             right_node->lnode->hdr.type == TN_IDENT)); // for case such as int a = 5;
}

int is_complex_var_dec(treenode *root) {
    treenode *left_node = (treenode *) root->lnode;
    treenode *right_node = (treenode *) root->rnode;

    // First case, handling simple variable initialization
    return left_node != NULL && left_node->hdr.type == TN_TYPE_LIST &&
           left_node->lnode != NULL && left_node->lnode->hdr.type == TN_OBJ_REF &&
           (right_node != NULL && right_node->hdr.type == TN_IDENT); // for case such as BakBak a;
}

int is_complex_var_preprocessing_stage(treenode *root) {
    treenode *left_node = (treenode *) root->lnode;
    treenode *right_node = (treenode *) root->rnode;
    return left_node != NULL && left_node->hdr.type == TN_TYPE_LIST &&
           left_node->lnode != NULL && left_node->lnode->hdr.type == TN_OBJ_DEF; // for case such as BakBak a;
}

int is_array_decleration(treenode *root) {
    treenode *left_node = (treenode *) root->lnode;
    treenode *right_node = (treenode *) root->rnode;

    return left_node != NULL && left_node->hdr.type == TN_TYPE_LIST &&
           right_node != NULL && right_node->hdr.type == TN_ARRAY_DECL;
}

int is_decleration_of_array_of_pointers(const treenode *root) {
    return root != NULL &&
           root->hdr.type == TN_DECL &&
           root->lnode != NULL &&
           root->rnode != NULL &&
           root->rnode->lnode != NULL &&
           root->lnode->lnode != NULL &&
           root->rnode->lnode->hdr.type == TN_PNTR &&
           ((leafnode *) root->lnode->lnode)->hdr.type == TN_TYPE &&
           root->rnode->rnode->hdr.type == TN_ARRAY_DECL;
}

int is_pointer_defenition(const treenode *root) {
    return root != NULL &&
           root->hdr.type == TN_DECL &&
           root->lnode != NULL &&
           root->rnode != NULL &&
           root->rnode->lnode != NULL &&
           root->lnode->lnode != NULL &&
           root->rnode->lnode->hdr.type == TN_PNTR &&
           ((leafnode *) root->lnode->lnode)->hdr.type == TN_TYPE;
}

int is_pointer_decleration(const treenode *root) {
    return root != NULL &&
           root->hdr.type == TN_DECL &&
           root->lnode != NULL &&
           root->rnode != NULL &&
           root->rnode->lnode != NULL &&
           root->rnode->lnode->lnode != NULL &&
           root->rnode->lnode->lnode->hdr.type == TN_PNTR &&
           root->lnode->lnode != NULL &&
           ((leafnode *) root->lnode->lnode)->hdr.type == TN_TYPE;
}

/*
*	This function prints all the variables on your symbol table with their data
*	Input: treenode (AST)
*	Output: prints the Sumbol Table on the console
*/
void print_symbol_table(treenode *root) {
    if (symbolTalble == NULL) {
        // printf("---------------------------------------\n");
        // printf("Showing the Symbol Table:\n");
        symbolTalble = (Symbol_table *) malloc(sizeof(Symbol_table));
        symbolTalble->variables_counter = 0;
        symbolTalble->vars = NULL;
        UKNOWN_VARIABLE = (Variable *) malloc(sizeof(Variable));
        UKNOWN_VARIABLE->address = 0;
        structsSymbolTable = (StructsSymbolTable *) malloc(sizeof(StructsSymbolTable));
        structsSymbolTable->vars = NULL;
        structsSymbolTable->variables_counter = 0;
        arraysSymbolTable = (ArraysSymbolTable *) malloc(sizeof(ArraysSymbolTable));
        arraysSymbolTable->arrays = NULL;
        arraysSymbolTable->arraysCounter = 0;
    }

    treenode *right_node;
    treenode *left_node;
    leafnode *leaf;
    for_node *forn;

    switch (root->hdr.which) {
        case NODE_T:
            switch (root->hdr.type) {
                case TN_TRANS_LIST:
                    print_symbol_table(root->lnode);
                    print_symbol_table(root->rnode);
                    break;
                case TN_DECL:
                    left_node = (treenode *) root->lnode;
                    right_node = (treenode *) root->rnode;

                    // First case, handling simple variable initialization
                    if (is_simple_premitive_var_decleration(root)) {
                        tn_t varType = 0;
                        left_node = (treenode *) left_node->lnode;
                        switch (((leafnode *) left_node)->hdr.tok) {
                            case INT:
                                varType = TN_INT;
                                break;
                            case FLOAT:
                            case DOUBLE:
                                varType = TN_REAL;
                                break;
                            default:
                                printf("Unhandled type: %d\n", ((leafnode *) left_node)->hdr.tok);
                                break;
                        }
                        if (right_node->hdr.type == TN_IDENT)
                            leaf = (leafnode *) right_node;
                        else if (right_node->hdr.type == TN_ASSIGN)
                            leaf = (leafnode *) right_node->lnode;

                        // printf("ID = %s\n", leaf->data.sval->str);
                        symbolTalble->vars = add_variable_to_symbol_table(leaf->data.sval->str, varType,
                                                                          symbolTalble->vars);
                    } else if (is_complex_var_preprocessing_stage(root)) {
                        // printf("COMPLEX Preprocessing\n");
                        left_node = (treenode *) left_node->lnode;
                        strcpy(struct_definition, "");
                        if (left_node->rnode != NULL) {
                            print_symbol_table(left_node->rnode);
                        }
                        // printf("ID IS: %s\n", ((leafnode *)left_node->lnode)->data.sval->str);
                        // printf("Struct definition is: %s\n", struct_definition);
                        structsSymbolTable->vars = add_struct_to_structs_mapping(structsSymbolTable->vars,
                                                                                 ((leafnode *) left_node->lnode)->data.sval->str,
                                                                                 struct_definition);
                    } else if (is_complex_var_dec(root)) {
                        // printf("Complex initialization\n");
                        leaf = (leafnode *) root->lnode->lnode->lnode;
                        // printf("struct type is: %s\n", leaf->data.sval->str);
                        // printf("struct identifier is %s\n", ((leafnode*)root->rnode)->data.sval->str);
                        // printf("struct string is: %s\n", get(&tbl, leaf->data.sval->str));
                        add_struct_to_symbolTable(get_struct_value_str(leaf->data.sval->str),
                                                  ((leafnode *) right_node)->data.sval->str, leaf->data.sval->str);
                    } else if (is_array_decleration(root)) {
                        // printf("DEclaring an array!\n");
                        char identifier[500] = "";
                        char typeAsString[50] = "";
                        tn_t type_as_enum = 0;
                        int array_size = 1;
                        int dimensionsCounter = 0;
                        char dimensionsArr[1000] = "";
                        char singleDimensionSize[10];
                        leaf = (treenode *) left_node->lnode;
                        switch (leaf->hdr.tok) {
                            case INT:
                                strcpy(typeAsString, "TN_INT\0");
                                type_as_enum = TN_INT;
                                // printf("Im an int!!!! %d\n", type_as_enum);
                                break;
                            case DOUBLE:
                            case FLOAT:
                                strcpy(typeAsString, "TN_REAL");
                                // printf("Im real man!!!!\n");
                                type_as_enum = TN_REAL;
                                break;
                            case STRUCT:
                                // printf("id is: %s\n", ((leafnode *)root->lnode->lnode->lnode)->data.sval->str);
                                strcpy(typeAsString, ((leafnode *) root->lnode->lnode->lnode)->data.sval->str);
                                type_as_enum = TN_DECL;
                                break;
                            default:
                                printf("type is: %d\n", leaf->hdr.tok);
                                break;
                        }
                        if (right_node->lnode != NULL) {
                            left_node = right_node;
                            while (left_node != NULL && left_node->lnode != NULL && left_node->rnode != NULL) {
                                strncat(dimensionsArr,
                                        itoa(((leafnode *) left_node->rnode)->data.cval, singleDimensionSize, 10),
                                        strlen(itoa(((leafnode *) left_node->rnode)->data.cval, singleDimensionSize,
                                                    10)));
                                strncat(dimensionsArr, &SUPPERATOR, 1);
                                array_size *= ((leafnode *) left_node->rnode)->data.cval;
                                dimensionsCounter += 1;
                                if (((leafnode *) left_node->lnode)->hdr.type == TN_IDENT) {
                                    strcpy(identifier, ((leafnode *) left_node->lnode)->data.sval->str);
                                    break;
                                }
                                left_node = left_node->lnode;
                            }

                            reverse_by_chanks(dimensionsArr);
                            add_array_to_symbol_table(array_size, typeAsString, type_as_enum, identifier,
                                                      dimensionsArr, dimensionsCounter);
                        }
                    } else if (is_decleration_of_array_of_pointers(root)) {
                        // printf("DEclaring an array!\n");
                        char identifier[500] = "";
                        char typeAsString[50] = "";
                        tn_t type_as_enum = 0;
                        int array_size = 1;
                        int dimensionsCounter = 0;
                        char dimensionsArr[1000] = "";
                        char singleDimensionSize[10];
                        leaf = (treenode *) left_node->lnode;
                        switch (leaf->hdr.tok) {
                            case INT:
                                strcpy(typeAsString, "TN_INT\0");
                                type_as_enum = TN_INT;
                                // printf("Im an int!!!! %d\n", type_as_enum);
                                break;
                            case DOUBLE:
                            case FLOAT:
                                strcpy(typeAsString, "TN_REAL");
                                // printf("Im real man!!!!\n");
                                type_as_enum = TN_REAL;
                                break;
                            case STRUCT:
                                // printf("id is: %s\n", ((leafnode *)root->lnode->lnode->lnode)->data.sval->str);
                                strcpy(typeAsString, ((leafnode *) root->lnode->lnode->lnode)->data.sval->str);
                                type_as_enum = TN_DECL;
                                break;
                            default:
                                printf("type is: %d\n", leaf->hdr.tok);
                                break;
                        }

                        if (right_node->rnode != NULL && right_node->rnode->rnode != NULL) {
                            array_size = ((leafnode *) right_node->rnode->rnode)->data.cval;
                            strcpy(identifier, ((leafnode *) right_node->rnode->lnode)->data.sval->str);
                            add_array_to_symbol_table(array_size, typeAsString, TN_PNTR, identifier,
                                                      dimensionsArr, 1);
                        } else if (is_pointer_defenition(root)) {
                            symbolTalble->vars = add_variable_to_symbol_table(
                                    ((leafnode *) right_node->rnode)->data.sval->str, TN_PNTR, symbolTalble->vars);
                        } else if (is_pointer_decleration(root)) {
                            symbolTalble->vars = add_variable_to_symbol_table(
                                    ((leafnode *) right_node->lnode->rnode)->data.sval->str, TN_PNTR,
                                    symbolTalble->vars);
                        }
                    }

                    // if (left_node->hdr.type == TN_TYPE_LIST)
                    // {
                    // 	if (left_node->lnode != NULL &&
                    // 		left_node->lnode->hdr.type == TN_OBJ_DEF)
                    // 	{

                    // 	}
                    // 	else if (right_node != NULL &&
                    // 			 right_node->hdr.type == TN_ARRAY_DECL)
                    // 	{
                    //
                    // 	}
                    // }

                    // else
                    // {
                    //

                    // }

                    break;
                case TN_BLOCK:
                    if (root->lnode != NULL)
                        print_symbol_table(root->lnode);
                    if (root->rnode != NULL)
                        print_symbol_table(root->rnode);
                    break;
                case TN_FUNC_DECL:
                    break;
                case TN_TYPE_LIST:
                    if (root->lnode != NULL) {
                        leaf = (leafnode *) (root->lnode);
                        switch (leaf->hdr.tok) {
                            case INT:
                                strcat(struct_definition, "298");
                                strncat(struct_definition, &PAIR_SUP, 1);
                                break;
                            case FLOAT:
                            case DOUBLE:
                                strcat(struct_definition, "296");
                                strncat(struct_definition, &PAIR_SUP, 1);
                                break;
                            case STRUCT:
                                if (leaf->hdr.type == TN_OBJ_REF) {
                                    if (get_struct_value_str(((leafnode *) root->lnode->lnode)->data.sval->str) !=
                                        NULL) {
                                        // printf("ADDING THE FOLLOWING: %s\n", get(&tbl, ((leafnode *)root->lnode->lnode)->data.sval->str), strlen(get(&tbl, ((leafnode *)root->lnode->lnode)->data.sval->str)));
                                        strncat(struct_definition,
                                                get_struct_value_str(((leafnode *) root->lnode->lnode)->data.sval->str),
                                                strlen(get_struct_value_str(
                                                        ((leafnode *) root->lnode->lnode)->data.sval->str)));
                                        strncat(struct_definition, "#", 1);
                                    }
                                } else {
                                    printf("NEED TO FIGURE IT OUT\n");
                                }

                                break;
                            default:
                                printf("Unhandled leaf token, it's: %d\n", leaf->hdr.tok);
                                break;
                        }
                    }
                    break;
                case TN_DECL_LIST:
                    print_symbol_table(root->lnode);
                    print_symbol_table(root->rnode);
                    break;
                case TN_STEMNT_LIST:
                    if (root->lnode != NULL)
                        print_symbol_table(root->lnode);
                    if (root->rnode != NULL)
                        print_symbol_table(root->rnode);
                    break;

                case TN_STEMNT:
                    if (root->lnode != NULL)
                        print_symbol_table(root->lnode);
                    else if (root->rnode != NULL)
                        print_symbol_table(root->rnode);
                    break;
                case TN_ASSIGN:
                    break;
                case TN_FUNC_CALL:
                    break;
                case TN_COMP_DECL:
                    /* struct component declaration - for HW2 */
                    if (root->rnode != NULL & root->rnode->hdr.which == LEAF_T &&
                        root->lnode != NULL && root->lnode->hdr.type == TN_TYPE_LIST &&
                        root->lnode->lnode != NULL && root->lnode->lnode->hdr.type == TN_OBJ_REF) {
                        strncat(struct_definition, "#", 1);
                        strncat(struct_definition, "%", 1);
                        strncat(struct_definition, ((leafnode *) root->rnode)->data.sval->str,
                                strlen(((leafnode *) root->rnode)->data.sval->str));
                        strncat(struct_definition, "%", 1);
                        should_print_id = 0;
                    } else if (root->lnode != NULL && root->lnode->lnode != NULL &&
                               root->lnode->lnode->hdr.type == TN_OBJ_REF && root->rnode != NULL &&
                               root->rnode->lnode != NULL && root->rnode->lnode->hdr.type == TN_PNTR) {
                        int numberOfPs = 0;
                        treenode *node = root->rnode->lnode;
                        while (node != NULL) {
                            node = node->rnode;
                            numberOfPs++;
                        }
                        strncat(struct_definition, "^", 1);
                        strncat(struct_definition, ((leafnode *) root->rnode)->data.sval->str,
                                strlen(((leafnode *) root->rnode)->data.sval->str));
                        strncat(struct_definition, "^", 1);
                    }
                    print_symbol_table(root->lnode);
                    print_symbol_table(root->rnode);
                    strncat(struct_definition, &STR_END, 1);
                    should_print_id = 1;

                    break;
                case TN_FIELD_LIST:
                    print_symbol_table(root->lnode);
                    print_symbol_table(root->rnode);
                    break;
                case TN_ARRAY_DECL:
                    /* array declaration - for HW2 */
                    // printf("declearing an array \n");
                    code_recur(root->lnode);
                    code_recur(root->rnode);
                    break;
                default:
                    break;
            }
            break;
        case FOR_T:
            // printf("Apperently for and main represents the same fucking way \n");
            forn = (for_node *) root;
            if (forn != NULL)
                print_symbol_table(forn->stemnt);

            break;

        case LEAF_T:
            switch (root->hdr.tok) {
                case IDENT:
                    if (should_print_id == 1) {
                        // printf("%s before \n", struct_definition);
                        strcat(struct_definition, ((leafnode *) root)->data.sval->str);
                        strncat(struct_definition, &SUPPERATOR, 1);
                        // printf("%s after \n", struct_definition);
                        should_print_id = 1;
                    }
                    break;
                default:
                    printf("UNHANDLED LEAF TOKEN is: %d\n", root->hdr.tok);
                    break;
            }
            break;

        default:
            break;
    }
}
