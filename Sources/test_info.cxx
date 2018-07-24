#include <iostream>
#include <string>
#include <stack>
#include "info_tree"
#include "inforeader"
using namespace std;
using namespace hw2;
  

int main(void)
{
	string* fn=new string("dir.txt");
	stack<info_tree*> used_nodes;
	char last_command;
	char command='z';
	string name,commandline;
	info_tree* temp;
	char namec[30];
	bool work=true;
    info_tree *main_tree=readfile(fn,NULL);
    info_tree* current=main_tree;
    command=disp(main_tree);
    while(work)
    {
       switch (command)
       {
       case 'b':
              
       break;
       case 'd':
              used_nodes.push(current);
              current=main_tree;
              last_command=command;
              command=disp(current);
              getchar();
       break;
       case 'f':
              temp=command_n(current);
              if (temp!=NULL)
                {
                	used_nodes.push(current);
                	current=temp;
                	last_command=command;
                	command=disp(current);
                	getchar();
                }
                else{
                	cout<<"There is no such a node"<<endl;
                	cout<<"enter your choice"<<endl;
         	        command=getchar();
         	        getchar();
                }
       break;
       
       case 'g':
             cout<<"  :type node (full name) to search"<<endl;
             cin.getline(namec,30);
             name.assign(namec);
             temp=command_g(current,&name);
             if (temp!=NULL)
                {
                	used_nodes.push(current);
                	current=temp;
                	last_command=command;
                	command=disp(current);
                	getchar();
                }
                else{
                	cout<<"There is no such a node"<<endl;
                	cout<<"enter your choice"<<endl;
         	        command=getchar();
         	        getchar();
                }
       break;
       
       case 'l':
              if(used_nodes.size()>0)
              {
              	temp=used_nodes.top();
              	used_nodes.pop();
              	used_nodes.push(current);
              	current=temp;
              	last_command=command;
                command=disp(current);
                getchar();
              }
              else{
                	cout<<"There is no such a node"<<endl;
                	cout<<"enter your choice"<<endl;
         	        command=getchar();
         	        getchar();
                }
       break;
       
       case 'm':
             cout<<"  :type node to search"<<endl;
             cin.getline(namec,30);
             name.assign(namec);
             temp=command_m(current,&name);
             if (temp!=NULL)
                {
                	used_nodes.push(current);
                	current=temp;
                	last_command=command;
                	command=disp(current);
                	getchar();
                }
                else{
                	cout<<"There is no such a node"<<endl;
                	cout<<"enter your choice"<<endl;
         	        command=getchar();
         	        getchar();
                }
       break;
       
       case 'n':
              temp=command_n(current);
              if (temp!=NULL)
                {
                	used_nodes.push(current);
                	current=temp;
                	last_command=command;
                	command=disp(current);
                	getchar();
                }
                else{
                	cout<<"There is no such a node"<<endl;
                	cout<<"enter your choice"<<endl;
         	        command=getchar();
         	        getchar();
                }
       break;
       
       case 'p':
              temp=command_m(current,&name);
             if (temp!=NULL)
                {
                	used_nodes.push(current);
                	current=temp;
                	last_command=command;
                	command=disp(current);
                	getchar();
                }
                else{
                	cout<<"There is no such a node"<<endl;
                	cout<<"enter your choice"<<endl;
         	        command=getchar();
         	        getchar();
                }
       break;
       
       case 'q':
             cout<<"Closing the program !!"<<endl;
             work=false;
             break;
             
       case 'u':
             temp=command_u(current);
             if (temp!=NULL)
                {
                	used_nodes.push(current);
                	current=temp;
                	last_command=command;
                	command=disp(current);
                	getchar();
                }
                else{
                	cout<<"There is no such a node"<<endl;
                	cout<<"enter your choice"<<endl;
         	        command=getchar();
         	        getchar();
                }
       break;
       
       default:
       exit;
       }
    }
	return(0);
}
