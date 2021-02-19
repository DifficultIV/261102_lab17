#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string file,vector<string> &name,vector<int> &score,vector<char> &grade){
    char format[] = "%[^:]: %d %d %d";
    char namee[100];
    int a,b,c;
    int sum;
    string text;
    ifstream source;
    const char *f = file.c_str();
    source.open(f);
    while(getline(source,text)){
        const char *t = text.c_str();
        sscanf(t,format,namee,&a,&b,&c);
        sum = a+b+c;
        name.push_back(namee);
        score.push_back(sum);
        grade.push_back(score2grade(sum));
    }
    source.close();
}

void getCommand(string &command,string &key){
    cout << "Please input your command: ";
    char x2[100];
    char y2[100];
    char format[] = "%s %[^\n]";
    string text;
    getline(cin,text);
    const char * textConverted = text.c_str();
    sscanf(textConverted,format,x2,y2);
    command = x2;
    key = y2;
}

void searchName(vector<string> &name,vector<int> &score,vector<char> &grade,string key){
    cout << "---------------------------------" << endl;
    int count = 0;
    for(unsigned int i =0;i < name.size();i++){
        if(toUpperStr(key) == toUpperStr(name[i])){
            cout << name[i] << "'s score = " << score[i] << endl;
            cout << name[i] << "'s grade = " << grade[i] << endl;
            count++;
        }
    }
    if(count == 0) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
    }


void searchGrade(vector<string> &name,vector<int> &score,vector<char> &grade,string key){
    cout << "---------------------------------" << endl;
    int count = 0;
    const char *k = key.c_str();
    for(unsigned int i =0;i < name.size();i++){
        if(*k == grade[i]){
            cout << name[i] <<" (" << score[i] << ")" << endl;
            count++;
        }
    }
    if(count == 0) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
