
/*  ###############################################################
    ##
    ##     C Tree Builder
    ##
    ##     File:         tree.c
    ##
    ##     Revision 0.0.0.2  1996/04/03  10:26:06  kurt
    ##     Added line,column to some printouts;
    ##     addresses of nodes printed out, too.
    ##     -- Kurt Cockrum <kurt@grogatch.seaslug.org>
    ##
    ##     Revision 0.0.0.1  1996/04/03  10:08:46  kurt
    ##     o    missing return in make_for
    ##     o misc. cleanups
    ##     -- Kurt Cockrum <kurt@grogatch.seaslug.org>
    ##
    ##     Revision 0.0.0.0  1996/03/30  02:49:41  kurt
    ##     o    added right curly brackets inside comments for benefit of vi
    ##     o    Addresses of tree nodes are printed in messages;
    ##         minor content changes to some messages
    ##     o    Threw away ntype[]
    ##     o   Rev. 0.0 from
    ##         -rw-r--r--  1 1047 1047 44198 Aug  7 19:32
    ##             ftp://ftp.cs.wisc.edu/coral/tmp/spf/ctree.0.01.tar.gz
    ##     -- Kurt Cockrum <kurt@grogatch.seaslug.org>
    ##
    ##     Programmer:   Shaun Flisakowski
    ##     Date:         Jan 21, 1995
    ##
    ##
    ###############################################################  */

#include    <stdio.h>
#include    <string.h>
#include    <stdlib.h>
#include    <assert.h>

#include    "tree.h"
#include    "gram_parser.cpp.h"
#include    "globals.h"
#include    "token.h"
#include    "prnttree.h"

/*  ###############################################################  */
if_node *make_if(tn_t type, context_t *contxt)
{
    if_node *tmp_node;

    tmp_node = (if_node *) HeapAlloc(Parse_TOS->node_heap);
    if (tmp_node == NULL)
    {
        fputs("Error: Out of memory in make_if.\n",stderr);
        exit(1);
    }

    tmp_node->hdr.which = IF_T;
    tmp_node->hdr.type  = type;
    tmp_node->cond  = (treenode *) NULL;
    tmp_node->then_n = (treenode *) NULL;
    tmp_node->else_n = (treenode *) NULL;

	tmp_node->hdr.c_contxt = malloc(sizeof(context_t));
	tmp_node->hdr.c_contxt->labels = malloc(sizeof(symtab_t));
	*(tmp_node->hdr.c_contxt->labels) = *(contxt->labels);
	tmp_node->hdr.c_contxt->syms = malloc(sizeof(symtab_t));
	*(tmp_node->hdr.c_contxt->syms) = *(contxt->syms);
	tmp_node->hdr.c_contxt->tags = malloc(sizeof(symtab_t));
	*(tmp_node->hdr.c_contxt->tags) = *(contxt->tags);

    return tmp_node;
}

/*  ###############################################################  */
for_node *make_for(tn_t type, context_t *contxt)
{
    for_node *tmp_node;

    tmp_node = (for_node *) HeapAlloc(Parse_TOS->node_heap);

    if (tmp_node == NULL)
    {
        fputs("Error: Out of memory in make_for.\n",stderr);
        exit(1);
    }

    tmp_node->hdr.which = FOR_T;
    tmp_node->hdr.type = type;
    tmp_node->init = (treenode *) NULL;
    tmp_node->test = (treenode *) NULL;
    tmp_node->incr = (treenode *) NULL;
    tmp_node->stemnt = (treenode *) NULL;

	tmp_node->hdr.c_contxt = malloc(sizeof(context_t));
	tmp_node->hdr.c_contxt->labels = malloc(sizeof(symtab_t));
	*(tmp_node->hdr.c_contxt->labels) = *(contxt->labels);
	tmp_node->hdr.c_contxt->syms = malloc(sizeof(symtab_t));
	*(tmp_node->hdr.c_contxt->syms) = *(contxt->syms);
	tmp_node->hdr.c_contxt->tags = malloc(sizeof(symtab_t));
	*(tmp_node->hdr.c_contxt->tags) = *(contxt->tags);

    return tmp_node;
}

/*  ###############################################################  */
leafnode *make_leaf(tn_t type, context_t *contxt)
{
    leafnode *tmp_node;

    tmp_node = (leafnode *) HeapAlloc(Parse_TOS->node_heap);

    if (tmp_node == NULL)
    {
        fputs("Error: Out of memory in make_leaf.\n",stderr);
        exit(1);
    }

    tmp_node->hdr.which = LEAF_T;
    tmp_node->hdr.type = type;
    tmp_node->syment = NULL;

	tmp_node->hdr.c_contxt = malloc(sizeof(context_t));
	tmp_node->hdr.c_contxt->labels = malloc(sizeof(symtab_t));
	*(tmp_node->hdr.c_contxt->labels) = *(contxt->labels);
	tmp_node->hdr.c_contxt->syms = malloc(sizeof(symtab_t));
	*(tmp_node->hdr.c_contxt->syms) = *(contxt->syms);
	tmp_node->hdr.c_contxt->tags = malloc(sizeof(symtab_t));
	*(tmp_node->hdr.c_contxt->tags) = *(contxt->tags);

    return tmp_node;
}

/*  ###############################################################  */
treenode *make_node(tn_t type, context_t *contxt)
{
    treenode *tmp_node;

    tmp_node = (treenode *) HeapAlloc(Parse_TOS->node_heap);

    if (tmp_node == NULL)
    {
        fputs("Error: Out of memory in make_node.\n",stderr);
        exit(1);
    }

    tmp_node->hdr.which = NODE_T;
    tmp_node->hdr.type  = type;

    tmp_node->lnode = (treenode *) NULL;
    tmp_node->rnode = (treenode *) NULL;

	tmp_node->hdr.c_contxt = malloc(sizeof(context_t));
	tmp_node->hdr.c_contxt->labels = malloc(sizeof(symtab_t));
	*(tmp_node->hdr.c_contxt->labels) = *(contxt->labels);
	tmp_node->hdr.c_contxt->syms = malloc(sizeof(symtab_t));
	*(tmp_node->hdr.c_contxt->syms) = *(contxt->syms);
	tmp_node->hdr.c_contxt->tags = malloc(sizeof(symtab_t));
	*(tmp_node->hdr.c_contxt->tags) = *(contxt->tags);

    return tmp_node;
}

/*  ###############################################################  */
treenode *copy_tree(treenode *root)
{
    leafnode *leaf, *newleaf;
    if_node  *ifn, *newif;
    for_node *forn, *newfor;
    treenode *newnode;

    if (!root)
        return(NULL);

    switch (root->hdr.which){

    case LEAF_T:
        leaf = (leafnode *) root;
        newleaf = make_leaf(leaf->hdr.type, leaf->hdr.c_contxt);
        newleaf->hdr.line = leaf->hdr.line;
        newleaf->hdr.col = leaf->hdr.col;
        newleaf->hdr.tok = leaf->hdr.tok;
        newleaf->data = leaf->data;
        return((treenode *)newleaf);

    case NODE_T:
        newnode = make_node(root->hdr.type, root->hdr.c_contxt);
        newnode->hdr.line = root->hdr.line;
        newnode->hdr.col = root->hdr.col;
        newnode->hdr.tok = root->hdr.tok;
        newnode->lnode = copy_tree(root->lnode);
        newnode->rnode = copy_tree(root->rnode);
        return(newnode);

    case IF_T:
        ifn = (if_node *) root;
        newif = make_if(ifn->hdr.type, ifn->hdr.c_contxt);
        newif->hdr.line = ifn->hdr.line;
        newif->hdr.col = ifn->hdr.col;
        newif->hdr.tok = ifn->hdr.tok;
        newif->cond = copy_tree(ifn->cond);
        newif->then_n = copy_tree(ifn->then_n);
        newif->then_n = copy_tree(ifn->else_n);
        return((treenode *)newif);

    case FOR_T:
        forn = (for_node *) root;
        newfor = make_for(forn->hdr.type, forn->hdr.c_contxt);
        newfor->hdr.line = forn->hdr.line;
        newfor->hdr.col = forn->hdr.col;
        newfor->hdr.tok = forn->hdr.tok;
        newfor->init = copy_tree(forn->init);
        newfor->test = copy_tree(forn->test);
        newfor->incr = copy_tree(forn->incr);
        newfor->stemnt = copy_tree(forn->stemnt);
        return((treenode *)newfor);
        break;

    default:
    case NONE_T:
        newnode = make_node(TN_EMPTY, root->hdr.c_contxt);
        newnode->hdr.which = NONE_T;
        return (newnode);
    }
}

/*  ###############################################################  */
void free_tree(treenode *root)
{
    leafnode *leaf;
    if_node  *ifn;
    for_node *forn;

    if (!root)
        return;

    switch (root->hdr.which){

    case LEAF_T:
        leaf = (leafnode *) root;
        if (leaf->hdr.tok == STRING)
            free(leaf->data.str);
        break;

    case NODE_T:
        free_tree(root->lnode);
        free_tree(root->rnode);
        break;

    case IF_T:
        ifn = (if_node *) root;
        free_tree(ifn->cond);
        free_tree(ifn->then_n);
        free_tree(ifn->else_n);
        break;

    case FOR_T:
        forn = (for_node *) root;
        free_tree(forn->init);
        free_tree(forn->test);
        free_tree(forn->incr);
        free_tree(forn->stemnt);
        break;

    default:
    case NONE_T:
        break;
    }

    HeapFree(Parse_TOS->node_heap,root);
}

/*  ###############################################################  */
leafnode *leftmost(treenode *root)
{
    if_node *ifn;
    for_node *forn;

    switch (root->hdr.which){

    case LEAF_T:
        return((leafnode *) root);
        break;

    case NODE_T:
        if (root->lnode)
            return(leftmost(root->lnode));
        else if (root->rnode)
            return(leftmost(root->rnode));
        fprintf(stderr,
            "Tree node %s with no children reached in leftmost.\n",
                print_ptr(root));
        break;

    case IF_T:
        ifn = (if_node *) root;
        if (ifn->cond)
            return(leftmost(ifn->cond));
        else if (ifn->then_n)
            return(leftmost(ifn->then_n));
        else if (ifn->else_n)
            return(leftmost(ifn->else_n));
        fprintf(stderr,
            "If-node %s with no children reached in leftmost.\n",
                print_ptr(root));
        break;

    case FOR_T:
        forn = (for_node *) root;
        if (forn->init)
            return(leftmost(forn->init));
        else if (forn->test)
            return(leftmost(forn->test));
        else if (forn->incr)
            return(leftmost(forn->incr));
        else if (forn->stemnt)
            return(leftmost(forn->stemnt));
        fprintf(stderr,
            "For-node %s with no children reached in leftmost.\n",
                print_ptr(root));
        break;

    case NONE_T:
    default:
        fprintf(stderr, "Internal error: unknown node %s in leftmost;\n"
         "  type is: %s\n", print_ptr(root), name_of_nodetype(root->hdr.which));
        break;
    }

    return((leafnode *) NULL);
}

/*  ###############################################################  */
leafnode *rightmost(treenode *root)
{
    if_node *ifn;
    for_node *forn;

    switch (root->hdr.which){

    case LEAF_T:
        return((leafnode *) root);
        break;

    case NODE_T:
        if (root->rnode)
            return(rightmost(root->rnode));
        else if (root->lnode)
            return(rightmost(root->lnode));
        fprintf(stderr,
            "\nTree node %s with no children reached in rightmost.\n",
                print_ptr(root));
        break;

    case IF_T:
        ifn = (if_node *) root;
        if (ifn->else_n)
            return(rightmost(ifn->else_n));
        else if (ifn->then_n)
            return(rightmost(ifn->then_n));
        else if (ifn->cond)
            return(rightmost(ifn->cond));
        fprintf(stderr,
            "\nIf node %s with no children reached in rightmost.\n",
                print_ptr(root));
        break;

    case FOR_T:
        forn = (for_node *) root;
        if (forn->stemnt)
            return(rightmost(forn->stemnt));
        else if (forn->incr)
            return(rightmost(forn->incr));
        else if (forn->test)
            return(rightmost(forn->test));
        else if (forn->init)
            return(rightmost(forn->init));
        fprintf(stderr,
            "\nFor node %s with no children reached in rightmost.\n",
                print_ptr(root));
        break;

    case NONE_T:
    default:
        fprintf(stderr, "Internal error: unknown node %s in rightmost;\n"
        "  type is: %s\n", print_ptr(root), name_of_nodetype(root->hdr.which));
        break;
    }

    return((leafnode *) NULL);
}

/*  ###############################################################  */
/* Scans the typedef declaration node N for the ident
   naming the new type. --jsh */
void
find_typedef_name(treenode *n, treenode *def, FindFunction find)
{
    if (!n)
        return;

    switch(n->hdr.which)
    {
        case LEAF_T:
            (find)((leafnode*) n, def, NULL);
            break;

        case NODE_T:
        {
            switch(n->hdr.type)
            {
            case TN_DECL:
                find_typedef_name(n->rnode,def,find);
                break;

            case TN_ARRAY_DECL:
                find_typedef_name(n->lnode,def,find);
                break;

            case TN_PNTR:
                fprintf(stderr,
                    "Internal error: TN_PNTR reached in find_typedef_name!\n");
                break;

            case TN_DECL_LIST:
            case TN_DECLS:
                find_typedef_name(n->lnode,def,find);
                find_typedef_name(n->rnode,def,find);
                break;

            case TN_FUNC_DECL:
                if (n->lnode->hdr.type == TN_DECL)
                    find_typedef_name(n->lnode,def,find);
                else
                    find_typedef_name(n->rnode,def,find);
                break;

            default:
                fprintf(stderr,
                        "Internal error: "
                        "unknown node type (%s) in find_typedef_name\n",
                        name_of_node(n->hdr.type));
                break;
            }
        }
        break;

        case IF_T:
        case FOR_T:
        case NONE_T:
        default:
            fprintf(stderr,
                "Internal error: unknown node %s in find_typedef_name;\n"
                "  type is: %s\n", print_ptr(n), name_of_nodetype(n->hdr.which));
            break;
    }
}

/*  ###############################################################  */
void  find_ident_name(treenode *n, treenode *def,
                      treenode *container, FindFunction find)
{
    if (!n)
        return;

    switch(n->hdr.which)
    {
    case LEAF_T:
        (find)((leafnode*) n,def,container);
        break;

    case NODE_T:
    {
        switch(n->hdr.type)
        {
        case TN_IDENT:
            (find)((leafnode*) n,def,container);
            break;

        case TN_DECL:
            find_ident_name(n->rnode,def,container,find);
            break;

        case TN_COMP_DECL:
            find_ident_name(n->rnode,def,container,find);
            break;

        case TN_ASSIGN:
        case TN_ARRAY_DECL:
            find_ident_name(n->lnode,def,container,find);
            break;

        case TN_FIELD_LIST:
        case TN_DECL_LIST:
        case TN_DECLS:
        case TN_PARAM_LIST:
            find_ident_name(n->lnode,def,container,find);
            find_ident_name(n->rnode,def,container,find);
            break;

        case TN_ELLIPSIS:
            break;

        case TN_PNTR:
            break;

        case TN_FUNC_DECL:
            find_ident_name(n->lnode,def,container,find);
            break;

        default:
            fprintf(stderr,
                    "Internal error: "
                    "unknown node type (%s) in find_ident_name\n",
                    name_of_node(n->hdr.type));
            break;
        }
    }
    break;

    case IF_T:
    case FOR_T:
    case NONE_T:
    default:
        fprintf(stderr,
            "Internal error: unknown node %s in find_ident_name;\n"
            "  type is: %s\n", print_ptr(n), name_of_nodetype(n->hdr.which));
        break;
    }
}

/*  ###############################################################  */
/* Scans the function declaration node N for the ident
   naming the new function. */
leafnode *find_func_name(treenode *n)
{
  for_node *f;

  while((n != 0) && (n->hdr.which != LEAF_T))
  {
    switch(n->hdr.which)
    {
    case LEAF_T:
      return (leafnode *)n;

    case NODE_T:
      switch(n->hdr.type)
        {
        case TN_DECL:
          n = n->rnode;
          break;

        case TN_PNTR:
          fprintf(stderr,
            "Internal error: TN_PNTR reached in find_func_name!\n");
          n = NULL;
          break;

        case TN_FUNC_DECL:
          n = n->lnode;
          break;

        default:
          fprintf(stderr,
                    "Internal error: "
                    "unknown node type (%s) in find_func_name\n",
                    name_of_node(n->hdr.type));
          n = NULL;
          break;
        }
      break;

    case FOR_T:
        f = (for_node *) n;
        switch(n->hdr.type)
          {
          case TN_FUNC_DEF:
            n = f->test;
            break;

          default:
            break;
          }
        break;

    case IF_T:
    case NONE_T:
    default:
        fprintf(stderr,
            "Internal error: unknown node %s in find_func_name;\n"
            "  type is: %s\n", print_ptr(n), name_of_nodetype(n->hdr.which));
        n = NULL;
        break;
    }
  }

  return (leafnode*) n;
}

/*  ###############################################################  */
void  find_params(treenode *decl, FindFunction find)
{
    if (!decl)
        return;

    switch(decl->hdr.which)
    {
    case NODE_T:
    {
        switch(decl->hdr.type)
        {
        case TN_DECL:
            find_ident_name(decl,decl,NULL,find);
            break;

        case TN_DECL_LIST:
        case TN_DECLS:
            find_params(decl->lnode,find);
            find_params(decl->rnode,find);
            break;

        case TN_PARAM_LIST:
            find_ident_name(decl->lnode,decl->lnode,NULL,find);
            find_ident_name(decl->rnode,decl->rnode,NULL,find);
            break;

        case TN_FUNC_DECL:
            find_params(decl->rnode,find);
            break;

        default:
            fprintf(stderr,
                    "Internal error: "
                    "unknown node type (%s) in find_params\n",
                    name_of_node(decl->hdr.type));
            break;
        }
    }
    break;

    case LEAF_T:
    case IF_T:
    case FOR_T:
    case NONE_T:
    default:
        fprintf(stderr,
         "Internal error: unknown node %s in find_params;\n"
         "  type is: %s\n", print_ptr(decl), name_of_nodetype(decl->hdr.which));
        break;
    }
}

/*  ###############################################################  */
void  find_components(treenode *decl, treenode *def,
                      treenode *container, FindFunction find)
{
    if (!decl)
        return;

    switch(decl->hdr.which)
    {
        case NODE_T:
        {
            switch(decl->hdr.type)
            {
            case TN_COMP_DECL:
            case TN_DECL:
                find_ident_name(decl,decl,container,find);
                break;

            case TN_DECL_LIST:
            case TN_DECLS:
                find_components(decl->lnode,def,container,find);
                find_components(decl->rnode,def,container,find);
                break;

            case TN_FIELD_LIST:
                find_components(decl->lnode,def,container,find);
                find_components(decl->rnode,def,container,find);
                break;

            case TN_FUNC_DECL:
                find_components(decl->rnode,def,container,find);
                break;

            default:
                fprintf(stderr,
                    "Internal error: "
                    "unknown node type (%s) in find_components\n",
                    name_of_node(decl->hdr.type));
                break;
            }
        }
    break;

    case LEAF_T:
    case IF_T:
    case FOR_T:
    case NONE_T:
    default:
        fprintf(stderr,
         "Internal error: unknown node %s in find_components;\n"
         "  type is: %s\n", print_ptr(decl), name_of_nodetype(decl->hdr.which));
        break;
    }
}

/*  ###############################################################  */
#define    SHOW(X)    #X

char*
name_of_node(tn_t val)
{
    switch (val)
    {
    case TN_EMPTY:
        return SHOW(TN_EMPTY);

    case TN_FUNC_DEF:
        return SHOW(TN_FUNC_DEF);
    case TN_FUNC_DECL:
        return SHOW(TN_FUNC_DECL);
    case TN_FUNC_CALL:
        return SHOW(TN_FUNC_CALL);
    case TN_BLOCK:
        return SHOW(TN_BLOCK);
    case TN_DECL:
        return SHOW(TN_DECL);
    case TN_ARRAY_DECL:
        return SHOW(TN_ARRAY_DECL);

    case TN_TRANS_LIST:
        return SHOW(TN_TRANS_LIST);
    case TN_DECL_LIST:
        return SHOW(TN_DECL_LIST);
    case TN_DECLS:
        return SHOW(TN_DECLS);
    case TN_STEMNT_LIST:
        return SHOW(TN_STEMNT_LIST);
    case TN_EXPR_LIST:
        return SHOW(TN_EXPR_LIST);
    case TN_NAME_LIST:
        return SHOW(TN_NAME_LIST);
    case TN_ENUM_LIST:
        return SHOW(TN_ENUM_LIST);
    case TN_FIELD_LIST:
        return SHOW(TN_FIELD_LIST);
    case TN_PARAM_LIST:
        return SHOW(TN_PARAM_LIST);
    case TN_IDENT_LIST:
        return SHOW(TN_IDENT_LIST);

    case TN_COMP_DECL:
        return SHOW(TN_COMP_DECL);
    case TN_BIT_FIELD:
        return SHOW(TN_BIT_FIELD);
    case TN_PNTR:
        return SHOW(TN_PNTR);

    case TN_TYPE_LIST:
        return SHOW(TN_TYPE_LIST);
    case TN_TYPE_NME:
        return SHOW(TN_TYPE_NME);

    case TN_INIT_LIST:
        return SHOW(TN_INIT_LIST);
    case TN_INIT_BLK:
        return SHOW(TN_INIT_BLK);

    case TN_OBJ_DEF:
        return SHOW(TN_OBJ_DEF);
    case TN_OBJ_REF:
        return SHOW(TN_OBJ_REF);

    case TN_CAST:
        return SHOW(TN_CAST);
    case TN_IF:
        return SHOW(TN_IF);
    case TN_ASSIGN:
        return SHOW(TN_ASSIGN);
    case TN_JUMP:
        return SHOW(TN_JUMP);
    case TN_FOR:
        return SHOW(TN_FOR);
    case TN_WHILE:
        return SHOW(TN_WHILE);
    case TN_DOWHILE:
        return SHOW(TN_DOWHILE);
    case TN_SWITCH:
        return SHOW(TN_SWITCH);
    case TN_LABEL:
        return SHOW(TN_LABEL);
    case TN_STEMNT:
        return SHOW(TN_STEMNT);

    case TN_INDEX:
        return SHOW(TN_INDEX);
    case TN_DEREF:
        return SHOW(TN_DEREF);
    case TN_SELECT:
        return SHOW(TN_SELECT);

    case TN_EXPR:
        return SHOW(TN_EXPR);
    case TN_COND_EXPR:
        return SHOW(TN_COND_EXPR);

    case TN_COMMENT:
        return SHOW(TN_COMMENT);
    case TN_CPP:
        return SHOW(TN_CPP);

    case TN_ELLIPSIS:
        return SHOW(TN_ELLIPSIS);
    case TN_IDENT:
        return SHOW(TN_IDENT);
    case TN_TYPE:
        return SHOW(TN_TYPE);
    case TN_STRING:
        return SHOW(TN_STRING);

    case TN_INT:
        return SHOW(TN_INT);

    case TN_REAL:
        return SHOW(TN_REAL);

    default:
        return "<Unknown Node Name>";
    }
}

char*
name_of_nodetype(node_type val)
{
    switch (val)
    {
    case NONE_T:
        return SHOW(NONE_T);
    case LEAF_T:
        return SHOW(LEAF_T);
    case IF_T:
        return SHOW(IF_T);
    case FOR_T:
        return SHOW(FOR_T);
    case NODE_T:
        return SHOW(NODE_T);
    default:
        return "<Unknown Node Type>";
    }

#undef SHOW
}

/*  ###############################################################  */
