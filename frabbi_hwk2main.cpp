#include "frabbi_hwk2.h"
#include <cstdlib>
#include <iostream>
#include <string> 
#include <iterator>
#include <fstream>
#include <list>
#include <sstream>
#include <cstring>
using namespace std;

int main(int argc, char* argv[]){
  list<songs> database;
  list<playlist> playL;
  ifstream input;
  ofstream output;
  int database_index = 0;
  input.open(argv[1]);
  if(input.fail()){
    input.open("songs.txt");
  }
  if(input.fail()){
    cerr<<"File could not be opened!"<<endl;
    exit(1);
  }

  while(!input.eof()){ 
   
    string n, ar, al, g, s, t, y, c, temp;
    getline(input, temp,'"');
    getline(input, n,'"');
    if (n.size()==0)
	break;
    getline(input, temp,'"');
    getline(input, ar,'"');
    getline(input, temp,'"');
    getline(input, al,'"');
    getline(input, temp,'"');
    getline(input, g,'"');
    getline(input, temp,'"');
    getline(input, s,'"');
    getline(input, temp,'"');
    getline(input, t,'"');
    getline(input, temp,'"');
    getline(input, y,'"');
    getline(input, temp,'"');
    getline(input, c,'"'); 
    
    if (n=="Name" && ar=="Artist" && al=="Album" && g=="Genre" && 
         s=="Size"&& t=="Time"&& y=="Year"&& c=="Comments")
      continue; 
    database.push_back(n); 
    list<songs>::iterator iterator_i;
    if (database.size()==1)
	iterator_i= database.begin();
    else{
     int j=0;
     for (iterator_i = database.begin(); iterator_i != database.end(); ++iterator_i){
	if(j==database_index)
		break;
	j++;
     }
    }
    iterator_i->info(n, ar, al, g, s, t, y, c, database_index+1);
  
    database_index ++;  
  }

 
  while(true){
    cout<<"(L/l)            List the names of all playlists"<<endl;
    cout<<"(V/v) <playlist> View a playlist\n";
    cout<<"(C/c) <playlist> Create a new playlist ...\n";
    cout<<"(M/m) <playlist> Modify a playlist ...\n";
    cout<<"(D/d) <playlist> Delete an existing playlist\n";
    cout<<"(S/s) <filename> Save all playlists\n";
    cout<<"(H/h) Help\n";
    cout<<"(Q/q) Exit.\n";

    string s;
    getline(cin, s );
    istringstream is( s );
    string v[20];
    string x;

    bool read1 = (is >> x);  
     if (read1==1) 
	v[0]= x;
    else if(read1==0)
	continue;
    int count=1;
    if (read1==1){
       while ( is >> x ){ 
   	    v[count]=x;
	    count++;
      }
    }
    if (v[0]=="q"||v[0]=="Q")
        break;
    else if (v[0]=="l"||v[0]=="L")
        listPlaylists(playL, cout);
    else if (v[0]=="h"||v[0]=="H")
        help(cout);
    else if ((v[0]=="C"||v[0]=="c") && count>1){
	cout<<v[1]<<endl;
	createP(playL, v[1], database, cout, cin);
    }
    else if ((v[0]=="D"||v[0]=="d") && count>1)
        deleteP(playL, v[1], cout);
    else if ((v[0]=="M"||v[0]=="m") && count>1){
	if (playL.size()==0)
		cout<<"No such playlist exists!\n";
	else{
		        list<playlist>::iterator it_p;
        		for (it_p = playL.begin(); it_p != playL.end(); ++it_p){

			if (it_p->getname()==v[1]){
        			it_p->modifyP(database, cout, cin);
				break;
			}
		}
	} 
    }
    else if ((v[0]=="V"||v[0]=="v") && count>1){
        list<playlist>::iterator it_p;
	bool exists= false;
        for (it_p = playL.begin(); it_p != playL.end(); ++it_p){
		if (v[1]==it_p->getname()){
			it_p->pdisplay(cout);
			exists= true;
			break;
		}
	}	
	if (!exists)
		cout<<"No such playlist exists\n";
	
    }
    else if ((v[0]=="S"||v[0]=="s") && count>1){
	output.open(v[1].c_str());
	outputToFile(output, playL);

	output.close();
   }
  }

  input.close();
  return 0;
}
