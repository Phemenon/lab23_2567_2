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

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source;
    source.open(filename);
    string text;

    while(getline(source, text))
    {
        char s[100] = "";
        for(unsigned i = 0 ; i < text.size(); i++){
            s[i] = text[i];
        }

        char base[] = "%[^:]: %d %d %d";
        char n[100];
        int a, b, c, sum = 0;

        sscanf(s, base, n, &a, &b, &c);
        sum = a + b + c;
        char g = score2grade(sum);
        
        string name = "";
        for(int i = 0; n[i] != '\0'; i++){
            name = name + n[i];
        }

        names.push_back(name);
        scores.push_back(sum);
        grades.push_back(g);

    }
    
}

void getCommand(string &command, string &key){
    cout<<"Please input your command: \n";
    string t;
    getline(cin, t);
    
    int first = t.find_first_of(" ");
    command = t.substr(0, first);
    key = t.substr(first + 1, t.size());
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    for(unsigned i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] <<"\n";
            cout << names[i] << "'s grade = " << grades[i] <<"\n";
            cout << "---------------------------------\n";
            return;
        }
    }
    cout << "---------------------------------\nCannot found.\n---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    cout << "---------------------------------\n";
    bool find = false;
    for(unsigned i = 0; i < scores.size(); i++){
        if(grades[i] == key[0]){
            cout << names[i] << " (" << scores[i] << ")\n";
            find = true;
        }
    }
    if(find == false){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
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
