#include <fstream>
#include <iostream>
#include <string>
#include <process.h>
#include "info_tree"
#include "inforeader"
using namespace std;
using namespace hw2;

  namespace hw2
  {     
  	     void Adjust_Nodes(string* link,info_tree* up,int type)
         {
         	int middle=link->find(":",0);
         	int cont=link->find("]");
         	string *d_n=new string(link->substr(link->find("[")+1,middle-2));
         	string *dis_n=new string(link->substr(cont+1,link->find(")")-cont-1));
         	if(*d_n=="")
         	*d_n=up->Get_docname();
         	char typec='c';
         	if (type==0)
         	typec='m';
         	string *n_n=new string(link->substr(middle+2,cont-middle-2));
         	info_tree *new_item=new info_tree(0,n_n,d_n,typec);
         	new_item->Set_node_disname(dis_n);
         	up->Set_Subtree(new_item);
         	readfile(d_n,new_item);
         }
         
  		info_tree* readfile(string* filename,info_tree* node_n)
  		{
             ifstream infile;
              infile.open(filename->c_str());   
             if (!infile) 
             { 
              cout << "Unable to open file: " << &filename << endl;
              return NULL;
             }
            string line;
            char cline[80];
         	infile.getline(cline,80);
         	line.assign(cline);
         	int line_count=0,begin,end,middle; 
         	info_tree *start;
         	while(begin=line.find("[",0)>-1)
         	{
         		infile.getline(cline,80);
         	    line.assign(cline);
         		line_count++;
         	}
         	if(node_n==NULL)
         	{
         	middle=line.find(":",0);
         	string* n_n=new string(line.substr(begin+1,middle-begin-1));
         	end=line.find("]",0);
            string* dis_n=new string(line.substr(middle+1,end-middle-1));
            string* fn=new string(*filename);
         	start=new info_tree(infile.tellg(),n_n,fn,-1);
         	start->Set_node_disname(dis_n);
         	}
         	else{
         		bool pass=true;
         		while(pass)
         		{
         			int begin=line.find("[",0);
         			if(begin>-1 && line.find("(",0)==string::npos)
         			{
         			  int middle=line.find(":",0);
         	          string* n_n=new string(line.substr(begin+1,middle-begin-1));
         		      if(*n_n==node_n->Get_name())
         		      {
         		    	start=node_n;
         		    	start->Set_Node_adress(infile.tellg());
         		    	pass=false;
         		      }
         			}
         		    infile.getline(cline,80);
         	        line.assign(cline);
         		}
         	}
         	while(line.find("* Menu",0)==string::npos && line.find("%%",0)==string::npos)
         	{ 
         	    if(line.find("([",0)!=string::npos)
         	    {
         	      begin=line.find("(",0);
                  end=line.find(")",1);
                  string str=line.substr(begin,end-begin);
         	      Adjust_Nodes(&str,start,1);
         	      
         	    }
         		infile.getline(cline,80);
         	    line.assign(cline);
         	}
         	if(line.find("%%",0)==string::npos)
         	{ 
         		 infile.getline(cline,80);
         		 infile.getline(cline,80);
         		 line.assign(cline);
         		
         		while(line.find("*",0)!=string::npos)
         		{
         	    begin=line.find("(",0);
         		end=line.find(")",1);
         		string str=line.substr(begin,end-begin+1);
         	    Adjust_Nodes(&str,start,0);
         	    infile.getline(cline,80);
         	    line.assign(cline);
         		}
         	}
         	infile.close();
         	return start;	
         }
         char disp(info_tree* dis)
         {
         	system("cls");
         	cout<<"node:"<<dis->Get_disname()<<", document:"<<dis->Get_docname()<<endl;
            string dis_n_p="-",dis_n_n="-",dis_n_u="-";
            if(dis->Get_docname()!="dir.txt")
            {
             if(dis->Get_next()!=NULL)
             dis_n_n=dis->Get_next()->Get_disname();
             if(dis->Get_prev()!=NULL)
             dis_n_n=dis->Get_prev()->Get_disname();
             if(dis->Get_up()!=NULL)
             dis_n_n=dis->Get_up()->Get_disname();
            }
         	cout<<"next:"<<dis_n_n<<", prev:"<<dis_n_p<<", up:"<<dis_n_u<<endl;
            
         	 ifstream infile;
              infile.open(dis->Get_docname().c_str());   
             if (!infile) 
             { 
              cout << "Unable to open file: " <<dis->Get_docname()<< endl;
              return 'a';
             }
            string line;
            char cline[80];
            int begin,end;
            infile.seekg(dis->Get_adress());
         	infile.getline(cline,80);
         	line.assign(cline);
         	int linecount=1;
         	while(line.find("%%",0)==string::npos)
         	{ 
         	  if(linecount%59!=0)
         	  {
         	    if(line.find("([",0)!=string::npos)
         	    {
         	      begin=line.find("]",0);
                  end=line.find(")",1);
                  string str=line.substr(begin+1,end-begin-1);
                  if(line.find("*",0)!=string::npos)
                  str="\n*  "+str;
                  cout<<str<<line.substr(end+1,line.length()-end)<<endl;
                  infile.getline(cline,80);
         	      line.assign(cline);
         	    }
         		else{
         			cout<<"\n"<<line;
         			infile.getline(cline,80);
         	        line.assign(cline);
         		    }
         		    linecount++;
         	  }
         	  else{
         	  	cout<<"press 'f' to see more "<<endl;
         	  	char command=getchar();
         	  	getchar();
         	  	if (command=='f')
         	  	linecount++;
         	  	else{
         	  	return command;
         	  	}
         	  }
         	}
         	cout<<"enter your choice"<<endl;
         	char command=getchar();
         	getchar();
         	return command;
         }
         
         info_tree* command_m(info_tree* subject,string* searched)
         {
           info_tree *ret=subject->Get_Subtree(searched,0);
           return ret;
         }
         info_tree* command_n(info_tree* subject)
         {
         	info_tree *ret=subject->Get_next();
         	return ret;
         }
         info_tree* command_p(info_tree* subject) 
         {
         	info_tree *ret=subject->Get_prev();
         	return ret;
         }
         info_tree* command_g(info_tree* subject,string* searched)
         {
           info_tree *ret=subject->Get_Subtree(searched,1);
           return ret;
         }
         info_tree* command_u(info_tree* subject)
         {
         	info_tree *ret=subject->Get_up();
         	return ret;
         }
         
         
        
         
  }
  