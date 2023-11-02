
#include "evaluator.h"
Evaluator::Evaluator()
{
    symtable = new SymbolTable();
}
Evaluator::~Evaluator()
{
    delete symtable;
}
void Evaluator::parse(vector<string> code)
{   vector<ExprTreeNode*>s;
    ExprTreeNode *root = new ExprTreeNode();
    root->type = "FYI";
    UnlimitedInt *ro_val = new UnlimitedInt(-2);
    UnlimitedInt *den = new UnlimitedInt[1];
    den[0] = 1;
    UnlimitedRational *ori_val = new UnlimitedRational(ro_val, den);
    root->val = ori_val;
    ExprTreeNode *pseudo_root = new ExprTreeNode();

    root->left->type = "VAR";
    root->left->id = "v";
    root->right = pseudo_root;
    for (int i = 2; i < code.size(); i++)
    {
        if (code[i] == "(")
        {
            s.push_back(pseudo_root);
            pseudo_root->left=new ExprTreeNode();
            pseudo_root = pseudo_root->left;
        }
        if (code[i] == "+")
        {
            pseudo_root->type = "ADD";
            s.push_back(pseudo_root);
            pseudo_root->right=new ExprTreeNode();
            pseudo_root = pseudo_root->right;
        }
        if (code[i] == "-")
        {
            pseudo_root->type = "SUB";
            s.push_back(pseudo_root);
            pseudo_root->right=new ExprTreeNode();
            pseudo_root = pseudo_root->right;
        }
        if (code[i] == "*")
        {
            pseudo_root->type = "MUL";
            s.push_back(pseudo_root);
            pseudo_root->right=new ExprTreeNode();
            pseudo_root = pseudo_root->right;
        }
        if (code[i] == "/")
        {
            pseudo_root->type = "DIV";
            s.push_back(pseudo_root);
            pseudo_root->right=new ExprTreeNode();
            pseudo_root = pseudo_root->right;
        }
        if (code[i] == "%")
        {
            pseudo_root->type = "MOD";
            s.push_back(pseudo_root);
            pseudo_root->right=new ExprTreeNode();
            pseudo_root = pseudo_root->right;
        }
        if (code[i] == ")")
        {   if(!s.empty()){
            pseudo_root=s.back();
            s.pop_back();
        }
        }

        if (code[i] > "0" && code[i] < "9")
        {
            pseudo_root->type = "VAL";
            UnlimitedInt *root_val = new UnlimitedInt(code[i]);
            UnlimitedInt *den = new UnlimitedInt[1];
            den[0] = 1;
            UnlimitedRational *actual_val = new UnlimitedRational(root_val, den);
            pseudo_root->val = actual_val;
            ExprTreeNode *parent = s.back();
            pseudo_root=parent;
            delete parent;
        }
        else
        {
            pseudo_root->type = "VAR";
            pseudo_root->id = code[i];
            ExprTreeNode *parent = s.back();
            pseudo_root=parent;
            delete parent;
        }
    }
    expr_trees.push_back(root);
}

void final_ans(ExprTreeNode *node, SymbolTable &symtable)
{
    UnlimitedRational *res = new UnlimitedRational();
    if(node==NULL){
        return;
    }
    if (node->left->type == "VAR")
    {
        res = symtable.search(node->right->id);
        node->left->evaluated_value = res;
    }
    else if (node->left->type == "VAL")
    {
        res = node->left->val;
        node->left->evaluated_value = res;
    }

    if (node->right->type == "VAR")
    {
        res = symtable.search(node->right->id);
        node->right->evaluated_value = res;
    }
    else if (node->right->type == "VAL")
    {
        res = node->right->val;
        node->right->evaluated_value = res;
    }

    else if (node->right->type == "ADD")
    {
        UnlimitedRational *leftValue = node->right->left->val;
        UnlimitedRational *rightValue = node->right->right->val;
        if (leftValue && rightValue)
        {
            res = UnlimitedRational::add(leftValue, rightValue);
            node->right->evaluated_value = res;
        }
    }
    else if (node->right->type == "SUB")
    {
        UnlimitedRational *leftValue = node->right->left->val;
        UnlimitedRational *rightValue = node->right->right->val;
        if (leftValue && rightValue)
        {
            res = UnlimitedRational::sub(leftValue, rightValue);
            node->right->evaluated_value = res;
        }
    }
    else if (node->right->type == "MUL")
    {
        UnlimitedRational *leftValue = node->right->left->val;
        UnlimitedRational *rightValue = node->right->right->val;
        if (leftValue && rightValue)
        {
            res = UnlimitedRational::mul(leftValue, rightValue);
            node->right->evaluated_value = res;
        }
    }
    else if (node->right->type == "DIV")
    {
        UnlimitedRational *leftValue = node->right->left->val;
        UnlimitedRational *rightValue = node->right->right->val;
        if (leftValue && rightValue)
        {
            res = UnlimitedRational::div(leftValue, rightValue);
            node->right->evaluated_value = res;
        }
    }
    symtable.insert(node->left->id, res);
    return final_ans(node->right, symtable);
}
void Evaluator::eval()
{
    ExprTreeNode *root = expr_trees.back();
    
    return final_ans(root, *symtable);
}

