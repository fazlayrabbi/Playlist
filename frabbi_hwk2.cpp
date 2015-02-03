#include "frabbi_hwk2.h"
#include <iostream>
#include <string> 
#include <cstdlib>
#include <list>
#include <sstream>
#include <cstring>
#include <iterator>
#include <fstream>
using namespace std;

songs::songs(string n) {title=n;}
songs::songs(){}
songs::songs(list<songs>::iterator s){
		song_id= s->song_id;
		title= s->title;
		artist= s->artist;
		album= s->album;
		genre= s->genre;
		size= s->size;
		min= s->min;
		seconds= s->seconds;
		year= s->year;
		comments= s->comments;
}
songs::~songs(){}
void songs::info(string n, string ar, string al, string g, string s, string t, string y, string c, int id){	
	title= n;
	artist= ar;
	album= al;
	genre= g;
	if(s.size()>0)
		size= atoi(s.c_str());
	else if(s.size()==0)
		size= '\0';
	if(t.size()>0){
		int temp= atoi(t.c_str());
		min= temp / 60;
		seconds= temp % 60;
	}
        else if(t.size()==0){
		min= '\0';
		seconds= '\0';
        }
	if(y.size()>0)
		year= atoi(y.c_str());
	else if(y.size()==0)
		year= '\0';
	comments= c;
        song_id= id;
}

string songs::getartistName(){ return artist;}
string songs::getTitle(){ return title;}

int songs::getSong_id(){
	return song_id;
}

void songs::display(ostream &o){
	if (artist.size()==20)
		o<<artist<<" ";
	else if(artist.size()<20){
		string display;
		for (int i=0; i<(20 - artist.size()); i++)
			display.insert(0," ");
		o<<artist<<display<<" ";
	}
	else if(artist.size()>20){
		string display=artist;
		display.erase(20, artist.size()-20);
		o<<display<<" ";
	}	
	

	if (title.size()==30)
		o<<title<<" ";
	else if(title.size()<30){
		string display;
		for (int i=0; i<(30 - title.size()); i++)
			display.insert(0," ");
		o<<title<<display<<" ";
	}
	else if(title.size()>30){
		string display=title;
		display.erase(30, title.size()-30);
		o<<display<<" ";
	}	
	
	if (album.size()==10)
		o<<album<<" ";
	else if(album.size()<10 && album.size()>0){
		string display;
		for (int i=0; i<(10 - album.size()); i++)
			display.insert(0," ");
		o<<album<<display<<" ";
	}
	else if(album.size()>10){
		string display=album;
		display.erase(10, album.size()-10);
		o<<display<<" ";
	}
	else if(album.size()==0)
		o<<"           ";

	if(min=='\0' && seconds=='\0')
		o<<"      ";
	
	else if(min<10 && seconds<10)
		o<<"0"<<min<<":"<<"0"<<seconds<<" ";
	else if(min<10 && seconds>9)
		o<<"0"<<min<<":"<<seconds<<" ";
	else if(min>9 && seconds<10)
		o<<min<<":"<<"0"<<seconds<<" ";
	else if(min>9 && seconds>9)
		o<<min<<":"<<seconds<<" ";

	if (year!='\0')
		o<<year;
        else
		o<<"    ";

	o<<endl;
}

playlist::playlist(){size=0;}
playlist::playlist(string n){
	name=n;
	size=0;
}
void playlist::setname(string n){name= n;}
int playlist::playlistSize(){

	return size;
}

string playlist::getname(){
	return name;
}

void playlist::outputSongId(ofstream& f){
	list<songs>::iterator iterator_s;
	for (iterator_s = item.begin(); iterator_s != item.end(); ++iterator_s){
			f<<" "<<iterator_s->getSong_id();
		}
}
void playlist::pdisplay(ostream &o){
	if (size>0){
	list<songs>::iterator iterator_i;
	int i=0;
	for (iterator_i= item.begin(); iterator_i != item.end(); ++iterator_i){
		if (i+1<10){
			o<<"    "<<i+1;
			o<<" ";
			iterator_i->display(o);			
		}
		else if (i+1<100  && i+1>9){
			o<<"   "<< i+1;
			o<<" ";
			iterator_i->display(o);			
		}
		else if (i+1<1000 && i+1>99){
			o<<"  "<< i+1; 
			o<<" ";			
			iterator_i->display(o);			
		}
		else if (i+1<10000 && i+1>999){
			o<<" "<< i+1; 
			o<<" ";			
			iterator_i->display(o);			
		}
		else if (i+1<100000 && i+1>9999){
			o<< i+1;
			o<<" ";
			iterator_i->display(o);			
		}
		i++;
	}
	}
}


int playlist::getsize(){ return size;}

void playlist::insertsong(int id, int pos, list<songs>& s){
	if (size==0 || size+1==pos){
		int i=0;
		list<songs>::iterator iterator_s;
		for (iterator_s = s.begin(); iterator_s != s.end(); ++iterator_s) {
				if (i==id-1)
					break;
				i++;
			}
		item.push_back(iterator_s);
		size++;
	}
	else{	
		int i=0;
		list<songs>::iterator iterator_s;
		for (iterator_s = s.begin(); iterator_s != s.end(); ++iterator_s) {
			if (i==id-1)
				break;
			i++;
		}
		i=0;
		list<songs>::iterator iterator_i;
		for (iterator_i = item.begin(); iterator_i != item.end(); ++iterator_i) {
			if (i==pos-1)
				break;
			i++;
		}
		item.insert(iterator_i, iterator_s);
		
		
		size++;	
	}
}

void playlist::deletesong(int id, ostream &o){
	bool found=true;
	bool match= false;
	while(found){
		found= false;
		list<songs>::iterator iterator_i;
		for (iterator_i = item.begin(); iterator_i != item.end(); ++iterator_i) {
			if (iterator_i->getSong_id()==id){
				iterator_i= item.erase(iterator_i);
				size--;
				found= true;
				match= true;
			}
		}
	}
	if(!match)
		o<<"Song ID not found\n";
	else
		o<<"Deleted!\n";
}

void outputToFile(ofstream& f, list<playlist> &p){
	f<<"Number of playlist: "<<p.size()<<endl;
	list<playlist>::iterator iterator_i;
	for (iterator_i = p.begin(); iterator_i != p.end(); ++iterator_i){
		f<<iterator_i->getsize()<<":";
		
		iterator_i->outputSongId(f);
		f<<endl;
	}	


}
void listPlaylists(list<playlist>& p, ostream &o ){
	list<playlist>::iterator iterator_i;
	for (iterator_i = p.begin(); iterator_i != p.end(); ++iterator_i)
		o<<"name: "<<iterator_i->getname()<<"    size:"<< iterator_i->playlistSize()<<endl;
}

void help(ostream &o){
       o<<endl;
       o<<"When you enter your input for menu, please make sure that\n";
       o<<"you do not enter more than one space after typing in your \n"; 
       o<<"initial character. If you do so, it may result in undesirable\n";
       o<<"result."<<endl;
       o<<endl;
}

void createP(list<playlist>& p, string name, list<songs>& s, ostream &o, istream& i){

	int match= 0;
	
	list<playlist>::iterator iterator_i;
	for (iterator_i = p.begin(); iterator_i != p.end(); ++iterator_i){
		if(name==iterator_i->getname()){
			
			match= 1;
			
			break;
			
		}
	}

	if (match==0){

		p.push_front(name);
		iterator_i = p.begin();

		iterator_i->setname(name);

		iterator_i->modifyP( s, o, i);
	}
}

void deleteP(list<playlist>& p, string name, ostream &o){
	bool found= 0;
	list<playlist>::iterator iterator_i;
	for (iterator_i = p.begin(); iterator_i != p.end(); ++iterator_i){
            if(iterator_i->getname()==name){
                 iterator_i= p.erase(iterator_i);  
		 found=1;
            }
        }
	if (!found)
            o<<"No such playlist exists!\n";
}

void playlist::modifyP(list<songs>& s, ostream &o, istream& i){
  while(true){
	o<<"(L/l) <first> <last>  List songs from database from first to last\n";
	o<<"(A/a) <artist_key>    List all songs whose artist contains artist_key as a substring\n";
	o<<"(T/t) <title_key>     List all songs whose title contains title_key as a substring\n";
	o<<"Insert <songid> <pos> Insert the songid into playlist at position <pos>\n";
	o<<"Delete <songid>       Delete songid fom playlist\n";
	o<<"Show                  Display the songs in the playlist\n";
	o<<"(M/m)                 Go back to main menu\n";
	
        string input;
        getline(i, input);
        istringstream is( input );
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

	if (v[0]=="m"||v[0]=="M")
	        break;
	else if ((v[0]=="t"||v[0]=="T") && count>1)
		titleKey(v[1], s, o);
	else if ((v[0]=="l"||v[0]=="L") && count>2){
		int first= atoi(v[1].c_str());
		int last= atoi(v[2].c_str());
		if (first<= last)
	        	listDatabase(s,first,last, o);
        }
	else if ((v[0]=="a"||v[0]=="A") && count>1)
		artistKey(v[1], s, o);
	else if ((v[0]=="Insert"||v[0]=="insert") && count>2){
		int temp1= atoi(v[1].c_str()); 
		int temp2= atoi(v[2].c_str());
		insertcheck(temp1, temp2, s);
	}
	else if (v[0]=="show"||v[0]=="Show")
        	pdisplay(o);
	else if ((v[0]=="Delete"||v[0]=="delete") && count>1){
		int temp =atoi(v[1].c_str());
		deletesong(temp, o);
	}
        o<<endl;
  }
}

void listDatabase(list<songs>& s, int first, int last, ostream &o){
	if (first <=0)
		first=1;
	if (first>s.size())
		first=s.size();

	if (last>s.size())
		last=s.size();
	list<songs>::iterator iterator_i;
	int countf=1; 
	for (iterator_i = s.begin(); iterator_i != s.end(); iterator_i++){
		if (countf==first)
			break;
		countf++;
	}
	
	int i=first-1;
	for (iterator_i; iterator_i != s.end(); ++iterator_i){
		if (countf-1==last)
			break;
		
		if (i+1<10){
			o<<"    "<<i+1;
			o<<" ";
			iterator_i ->display(o);
			
		}
		else if (i+1<100  && i+1>9){
			o<<"   "<< i+1;
			o<<" ";
			iterator_i ->display(o);
			
		}
		else if (i+1<1000 && i+1>99){
			o<<"  "<< i+1; 
			o<<" ";			
			iterator_i ->display(o);
			
		}
		else if (i+1<10000 && i+1>999){
			o<<" "<< i+1; 
			o<<" ";			
			iterator_i ->display(o);
			
		}
		else if (i+1<100000 && i+1>9999){
			o<< i+1;
			o<<" ";
			iterator_i ->display(o);
			
		}
		countf++;
		i++;
	}
}

void artistKey(string key, list<songs>& s, ostream &o){
	int index=0;
	string temp;
	
	int i=0;
  	char str[70];
	strcpy(str, key.c_str());
  	char c;
  	while (str[i])
  	{
    		c=str[i];
    		str[i]= tolower(c);
    		i++;
  	}

	key= str;
	list<songs>::iterator iterator_i;
	for (iterator_i = s.begin(); iterator_i != s.end(); ++iterator_i){
		int j=0;
		temp= iterator_i->getartistName();
		strcpy(str, temp.c_str());
  		while (str[j])
  		{
    			c=str[j];
    			str[j] =tolower(c);
    			j++;
  		}
		temp= str;
		if (key.size()>temp.size())
			continue;
		
		else if (  temp.find(key) != string::npos){
				index++;
				if (index<10){
					o<<"    "<<index;
					o<<" ";
					iterator_i->display(o);
			
				}
				else if (index<100  && index>9){
					o<<"   "<< index;
					o<<" ";
					iterator_i->display(o);
			
				}
				else if (index<1000 && index>99){
					o<<"  "<< index; 
					o<<" ";			
					iterator_i->display(o);
			
				}
				else if (index<10000 && index>999){
					o<<" "<< index; 
					o<<" ";			
					iterator_i->display(o);
			
				}
				else if (index<100000 && index>9999){
					o<< index;
					o<<" ";
					iterator_i->display(o);
			
				}		
		}
	}
  
} 

void titleKey(string key, list<songs>& s, ostream &o){
	int index=0;
	string temp;	
	int i=0;
  	char str[300];
	strcpy(str, key.c_str());
  	char c;
  	while (str[i])
  	{
    		c=str[i];
    		str[i]= tolower(c);
    		i++;
  	}

	key= str;
	list<songs>::iterator iterator_i;
	for (iterator_i = s.begin(); iterator_i != s.end(); ++iterator_i){
		int j=0;
		temp= iterator_i->getTitle();
		strcpy(str, temp.c_str());
  		while (str[j])
  		{
    			c=str[j];
    			str[j] =tolower(c);
    			j++;
  		}
		temp= str;
		if (key.size()>temp.size())
			continue;
		
		else if (temp.find(key) != string::npos){
				index++;
				if (index<10){
					o<<"    "<<index;
					o<<" ";
					iterator_i->display(o);
			
				}
				else if (index<100  && index>9){
					o<<"   "<< index;
					o<<" ";
					iterator_i->display(o);
			
				}
				else if (index<1000 && index>99){
					o<<"  "<< index; 
					o<<" ";			
					iterator_i->display(o);
			
				}
				else if (index<10000 && index>999){
					o<<" "<< index; 
					o<<" ";			
					iterator_i->display(o);
			
				}
				else if (index<100000 && index>9999){
					o<< index;
					o<<" ";
					iterator_i->display(o);
			
				}		
		}	
	}
} 

void playlist::insertcheck(int id, int pos, list<songs>& s){
	if ((pos>0 && pos<=getsize()+1) && (id>0 && id<=s.size()))
		insertsong(id, pos, s);
}
