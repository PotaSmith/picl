#ifndef PICL_NODE_BUILD_H
# define PICL_NODE_BUILD_H
# include "picl-node.h"


# define NODE_BUFF_DATA_SIZE 1000
# define NODE_BUFF_STACK_DATA_SIZE 100


struct PiclNode_FuncHead
{
    struct PiclStr *name;
    struct PiclNodeArray *args;
    struct PiclNodeArray *keyword_args;
};
struct PiclNode_FuncBody
{
    struct PiclNodeArray *body;
    struct PiclNodeArray *lets;
};

struct PiclNodeBuff
{
    struct PiclNode *data[NODE_BUFF_DATA_SIZE];
    int size;
};
struct PiclNodeBuffStack
{
    struct PiclNodeBuff data[NODE_BUFF_STACK_DATA_SIZE];
    int size;

    struct PiclNodeBuff *current_buf;
};


void PiclNode_delete(struct PiclNode *node);
void PiclNodeArray_delete(struct PiclNodeArray *nodes);


struct PiclNodeBuffStack *PiclNodeBuffStack_new();
struct PiclNodeArray *PiclNodeArray_pop(struct PiclNodeBuffStack *node_buff_stack);
void PiclNodeBuffStack_push(struct PiclNodeBuffStack *node_buff_stack, struct PiclNode *node);
void PiclNodeBuff_new(struct PiclNodeBuffStack *node_buff_stack);


struct PiclNode_FuncHead *PiclNode_FuncHead_new(struct PiclStr *name, struct PiclNodeArray *args, struct PiclNodeArray *keyword_args);
struct PiclNode_FuncBody *PiclNode_FuncBody_new(struct PiclNodeArray *body, struct PiclNodeArray *lets);


struct PiclNode *PiclNode_newClassKind(NodeType node_type, struct PiclStr *name, struct PiclNodeArray *extentions, struct PiclNodeArray *members);
struct PiclNode *PiclNode_newField(MemberScope scope, struct PiclStr *name, struct PiclNode *value);
struct PiclNode *PiclNode_newMethod(MemberScope scope, struct PiclNode_FuncHead *head, struct PiclNode_FuncBody *body);
struct PiclNode *PiclNode_newAlias(struct PiclStr *name, struct PiclNode *value);
struct PiclNode *PiclNode_newCatch(struct PiclNode_FuncHead *head, struct PiclNode_FuncBody *body);
struct PiclNode *PiclNode_newFunction(struct PiclNode_FuncHead *head, struct PiclNode_FuncBody *body);
struct PiclNode *PiclNode_newLet(struct PiclNode_FuncHead *head, struct PiclNodeArray *nodes);
struct PiclNode *PiclNode_newCallFunc(NodeType node_type, struct PiclNode *func, struct PiclNodeArray *args);

struct PiclNode *PiclNode_newNodes(NodeType node_type, struct PiclNodeArray *nodes);

struct PiclNode *PiclNode_newOneArgListStmt(NodeType node_type, struct PiclStr *name, struct PiclNodeArray *nodes);
struct PiclNode *PiclNode_newTwoArgListStmt(NodeType node_type, struct PiclStr *name1, struct PiclStr *name2, struct PiclNodeArray *nodes);
struct PiclNode *PiclNode_setListStmtCond(struct PiclNode *list_stmt, struct PiclNode *cond);
struct PiclNode *PiclNode_newCondBinary(NodeType node_type, struct PiclNode *cond, struct PiclNodeArray *left, struct PiclNodeArray *right);
struct PiclNode *PiclNode_newCondUnary(NodeType node_type, struct PiclNode *cond, struct PiclNodeArray *nodes);

struct PiclNode *PiclNode_newBinary(NodeType node_type, struct PiclNode *left, struct PiclNode *right);
struct PiclNode *PiclNode_newUnary(NodeType node_type, struct PiclNode *value);
struct PiclNode *PiclNode_newAtom(NodeType node_type);
struct PiclNode *PiclNode_newIdent(NodeType node_type, struct PiclStr *name);
struct PiclNode *PiclNode_newNaming(NodeType node_type, struct PiclStr *name, struct PiclNode *node);
struct PiclNode *PiclNode_newStr(struct PiclStr *value);
struct PiclNode *PiclNode_newInt(PiclInt value);





#endif /* PICL_NODE_BUILD_H */
