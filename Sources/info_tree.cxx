#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "info_tree"
using namespace hw2;

namespace hw2{

    info_tree::
    info_tree(int addr,string* n_n,string* d_n,int type) 
    {
       info_node *new_node=new info_node(addr,*n_n,*d_n);
       root=new_node; 
       root->type=type;
    }
    
    info_tree::
    ~info_tree(void)
    {
    	delete (root);
    	for(int i=0;i<sub_info_tree.size();i++)
    	{
    		sub_info_tree.pop_back();
    	}
    }
    
    info_tree::
    info_tree(const info_tree& item)
    { 
   	   root=new info_node(item.root);
   	   sub_info_tree=item.sub_info_tree;
    }
    
    info_tree* info_tree::
    Get_Subtree(string* dis_n,int type)
    {
       info_tree *temp;
       string nn; 
       if (type ==0)
       {
         for(int i=0;i<sub_info_tree.size();i++)
         {
       	  temp=sub_info_tree.at(i);
       	  nn=temp->root->dis_n;
       	  if(nn.find(*dis_n,0)!=string::npos && temp->root->type=='m')
       	  return temp;
         }
       }
       else{
       	for(int i=0;i<sub_info_tree.size();i++)
         {
       	  temp=sub_info_tree.at(i);
       	  if(temp->root->type=='m')
       	  break;
       	  nn=temp->root->dis_n;
       	  if(nn==*dis_n && temp->root->type=='c')
       	  return temp;
         }
       }
       return NULL;
    }
    
   info_tree* info_tree::Get_next()
   {
   	info_tree *ret_tree;
        if(root->index!=(root->_up)->sub_info_tree.size() && root->index>-1)
   	    {
   	    	ret_tree= (root->_up)->sub_info_tree.at(root->index+1);
   	    	return ret_tree;
   	    }
        return NULL;	    
   }
   
   info_tree* info_tree::Get_prev()
   {
   	 info_tree *ret_tree;
   	    if(root->index!=0 && root->index>-1)
   	    {
   	    	ret_tree=(root->_up)->sub_info_tree.at(root->index-1);
   	    	return ret_tree;
   	    } 
   	    return NULL;
   }
   
   info_tree* info_tree::Get_up()
   {
   	  info_tree *ret_tree;
   	  if(root->_up!=NULL)
   	  {
   	  	ret_tree=root->_up;
   	  	return ret_tree;
   	  }
   	  return NULL;
   }
   
   void info_tree::Set_Subtree(info_tree* item)
    {
    	sub_info_tree.push_back(item);
    	item->root->_up=this;
    	(*item).root->index=sub_info_tree.size();
    }
    
   void info_tree::Set_Node_adress(int addr)
    {
        root->addr=addr;
    }
    
   void info_tree::Set_Node_name(string* name)
   {
   	    root->node_n=*name;
   }
   
   void info_tree::Set_node_disname(string* disname)
   {
   	    root->dis_n=*disname;
   }
   
   void info_tree::Set_node_docname(string* docname)
   {
   	    root->doc_n=*docname;
   }
   
   string info_tree::Get_disname()
   {
   	    return root->dis_n;
   }
   
   string info_tree::Get_docname()
   {
   	    return root->doc_n;
   }
   
   string info_tree::Get_name()
   {
   	    return root->node_n;
   }
   int info_tree::Get_adress()
   {
   	return root->addr;
   }
   
   
}
