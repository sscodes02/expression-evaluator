
#include "symtable.h"
SymbolTable::SymbolTable(){
    size=0;
    root=nullptr;
}
SymbolTable::~SymbolTable(){
  delete root;
}
void in(SymEntry*node,string k, UnlimitedRational* v){
if(node==NULL){
SymEntry* newNode=new SymEntry(k,v);
node=newNode;   
}

if(node->val<v){
in(node->right,k,v);
}
else if(node->val>v){
    in(node->left,k,v);
}
}
SymEntry* findsucc(SymEntry*node){
while(node->left!=NULL){
    node=node->left;
}
return node;
}
void swap(SymEntry*a,SymEntry*b){
  SymEntry*temp=a;
  a=b;
  b=temp;  
}
void del(SymEntry*node,string k){
    if(node==NULL){
        return ;
    }
    if(node->key>k){
        del(node->left,k);
    }
    else if(node->key<k){
        del(node->right,k);
    }
    if(node->left==NULL&&node->right==NULL){
        delete node->val;
        delete node;
        
    }
    else if(node->left==NULL){
      SymEntry*temp=node->right;
      swap(node,temp);
      delete node->val;
      delete node;
    }
    else if(node->right==NULL){
       SymEntry*temp=node->left;
      swap(node,temp);
      delete node->val;
      delete node;  
    }
    else{
      SymEntry* succ= findsucc(node->right);
        swap(succ,node);
        delete node->val;
        delete node;
    }

}


UnlimitedRational* find(SymEntry*node,string k){
    if(node==NULL || node->key==k){
        return node->val;
    }
    else if(k>node->key){
        return find(node->right,k);
    }
    else{
        return find(node->left,k);
    }
}
void SymbolTable::insert(string k, UnlimitedRational* v){
   return in(root,k,v);
   size++;
}
void SymbolTable::remove(string k){
   return  del(root,k);
   size--;
}
UnlimitedRational*SymbolTable::search(string k){
    return find(root,k);
}
int SymbolTable::get_size(){
    return size;
}
SymEntry*SymbolTable::get_root(){
    return root;
}
