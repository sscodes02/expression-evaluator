
#include "exprtreenode.h"
ExprTreeNode::ExprTreeNode(){
    type="";
    val=nullptr;
    evaluated_value=nullptr;
    id="";
    left=nullptr;
    right=nullptr;
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    type=t;
    if(t=="VAL"){
        UnlimitedInt*den= new UnlimitedInt[1];
        den[0]=1;
        val=new UnlimitedRational(v,den);
    }
    if(t=="VAR"){
       id=v->to_string();
    }
    else{
     id="";
    }
    evaluated_value=nullptr;
    left=nullptr;
    right=nullptr;    
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
 type=t;
    if(t=="VAL"){
    val=new UnlimitedRational(*v);
    } 
    else{
        val=nullptr;
    } 
    if(t=="VAR"){
    id=v->get_p_str();
    }
    else{
     id="";
    }
    evaluated_value=nullptr;
   
    left=nullptr;
    right=nullptr; 
}
ExprTreeNode::~ExprTreeNode(){
    delete val;
    delete evaluated_value;
}