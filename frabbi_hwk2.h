#ifndef FRABBI_HWK2_H
#define FRABBI_HWK2_H
#include <string>
#include <list>

using namespace std;
class songs{
	public:
		songs();
		songs( list<songs>::iterator s);
		~songs();
		songs(string n);
		void info (string n, string ar, string al, string g, string s,   
                          string t, string y, string c, int id); 
		int getSong_id();
		void display(ostream &o);
		string getTitle();
		string getartistName();
	private:
		int song_id;
		string title;
		string artist;
		string album;
		string genre;
		int size;
		int min;
		int seconds;
		int year;
		string comments;
};

class playlist{
	public:		
		playlist();
		void pdisplay(ostream &o);
		string getname();
		playlist(string n);
		int playlistSize();        
                int getsize();
		void setname(string n);
		void modifyP(list<songs>& s, ostream &o, istream& i);
		void insertcheck(int id, int pos, list<songs>& s);
		void insertsong(int id, int pos, list<songs>& s);
		void deletesong(int id, ostream &o);
		void outputSongId(ofstream& f);
	private:
		list<songs> item;
		int size;
		string name;
};
void outputToFile(ofstream& f, list<playlist> &p);
void titleKey(string key, list<songs>& s, ostream &o);
void artistKey(string key, list<songs>& s, ostream &o);
void listDatabase(list<songs>& s, int first, int last, ostream &o);
void listPlaylists(list<playlist>& p, ostream &o);
void help(ostream &o);
void createP(list<playlist>& p, string name, list<songs>& s, ostream &o, istream& i);
void deleteP(list<playlist>& p, string name, ostream &o);
#endif
