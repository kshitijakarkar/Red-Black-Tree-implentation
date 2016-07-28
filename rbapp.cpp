
/**********************************************************************

@rbapp.cpp  processes the input given through command line or pass as a
file. It splits the strings into commands and data and passes it to
respective functions in rbtree.cpp.

by : Kshitija Karkar

***********************************************************************/

#include<iostream>
#include<string>
#include "rbapp.h"
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

/***********************************
main() to instantiate the object
IN :N.A
OUT : return 0
***********************************/

int main()
{
   RBapp myRBTapp;
   myRBTapp.mainLoop();
   return 0;
}

/***********************************
rbapp() constructor to initialise
the boolean done.
***********************************/
RBapp :: RBapp()
{
   done = false;
}

/*******************************************
mainloop() to process all the commands till
end of file is reached or quit command is 
given.
IN : N.A.
OUT :N.A.
*******************************************/

void RBapp::mainLoop()
{
  
  while(!cin.eof() && !done)
     processCommand();
}

/**********************************************
processCommand() process the input data and 
calls the function according to command given.
IN : N.A.
OUT :N.A.
**********************************************/

void RBapp::processCommand()
{
   string s,s1,s2,first,second;
   getline(cin,s);
   {
     string::size_type pos;
     pos = s.find(' ',0);
     second = s.substr(pos+1);
     first = s.substr(0,pos);
     if(first == "insert")
     {
         // Insert call
        processInsert(second);
     }
     else if(first=="find")
     {
        // Find call
        processFind(second);
     }
     else if(first=="delete")
     { 
         // delete call
        processDelete(second);
     }
     else if(first=="print")
     { 
         // print call
        processPrint();
     }
     else if(first=="quit")
     {
         // Quit 
        processQuit();
     }  
  }   
}

/*******************************************
processInsert() separates key and satellite
data and passes it to rbinsert().
IN : string containing key and satellite data
OUT :N.A.
*******************************************/

void RBapp:: processInsert(string &s)   // insert into red-black tree
{
   string key,satellite;  
   int pos;
   pos=s.find(' ');
   if(pos != -1)
   {
		key=s.substr(0, pos);
		satellite=s.substr(pos+1);
	  	myRBT.rbInsert(key,satellite);
	}
}

/*******************************************
processPrint() calls rbprinttree() to print
the tree in inorder fashion.
IN :N.A
OUT : N.A.
*******************************************/

void RBapp:: processPrint()           // print tree
{
   myRBT.rbPrintTree();
}

/*******************************************
processFind() separates key nd passes it to 
rbind to search for multiple occurrences.
Stores all values in vector and prints it.
IN : string containing key and satellite data
OUT :All the nodes with same key values
*******************************************/

void RBapp:: processFind(string &s)     // find & print all occurances of a key
{
   string key;
   vector <const string *> m;
   vector <const string *> :: iterator it;
   string::size_type pos;
   pos=s.find(' ',0);
   key=s.substr(0,pos);
   m = myRBT.rbFind(key);
   for(it=m.begin();it!=m.end();++it) 
      cout<<key<<" "<<**it<<"\n";
}

/*******************************************
processDelete() separates key and satellite
data and passes it to rbDelete().
IN : string containing key and satellite data
OUT :N.A.
*******************************************/

void RBapp:: processDelete(string &s)   // delete from the red-black tree
{
   string key,satellite;  
   int pos;
   pos=s.find(' ');
   if(pos != -1)
   {
		key=s.substr(0, pos);
		satellite=s.substr(pos+1);
	  	myRBT.rbDelete(key,satellite);
	}
}

/*******************************************
processQuit() exits from the program
IN :N.A
OUT : N.A.
*******************************************/

void RBapp:: processQuit()
{
   done=true;     
}
