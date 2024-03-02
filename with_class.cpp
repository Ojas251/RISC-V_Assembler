#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
using namespace std;
class R_format{
public:
    string extractf(string inst){
        smatch match;
        string matchs;
        int value;
        regex pattern("^(\\s*)x(\\d|[1-2]\\d|3[0-1])(?=[ |,])");
        std::regex_search(inst,match,pattern);
        if(match.size() == 0){
            cout<<"Error\n";
            return "-1";
        }
        else{
        matchs=match.str();
        return matchs;
        }
    }
    string extract(string inst){
        smatch match;
        string matchs;
        int value;
        regex pattern("^(\\s*)[,]{0,1}x(\\d|[1-2]\\d|3[0-1])(?=[ ,]|$)");
        std::regex_search(inst,match,pattern);
        if(match.size() == 0){
            cout<<"Error\n";
            return "-1";
        }
        else{
        matchs=match.str();
        return matchs;
        }
    }
};

void R(string Inst){
    R_format inst;
    string reg,matchs;
    int rd_value,rs1_value,rs2_value;
    // for rd
    matchs = inst.extractf(Inst);
    if(matchs=="-1"){
       return;
    }
    size_t pos = Inst.find(matchs);
    Inst = Inst.substr(0, pos) + Inst.substr(pos + matchs.length());
    matchs.erase(0, matchs.find_first_not_of(" \t"));
    matchs.erase(0, matchs.find_first_not_of("x"));
    rd_value=stoi(matchs);
    cout << "rd_value:"<<rd_value<<"\n";

    // for rs1
    cout << Inst<<"\n";
    matchs = inst.extract(Inst);
    if(matchs=="-1"){
       return;
    }
    pos = Inst.find(matchs);
    Inst = Inst.substr(0, pos) + Inst.substr(pos + matchs.length());
    matchs.erase(0, matchs.find_first_not_of(" \t"));
    matchs.erase(0, matchs.find_first_not_of(","));
    matchs.erase(0, matchs.find_first_not_of("x"));
    rs1_value=stoi(matchs);
    cout << "rs1_value:"<<rs1_value<<"\n";

    // for rs2
    cout << Inst<<"\n";
    matchs = inst.extract(Inst);
    if(matchs=="-1"){
       return;
    }
    pos = Inst.find(matchs);
    Inst = Inst.substr(0, pos) + Inst.substr(pos + matchs.length());
    matchs.erase(0, matchs.find_first_not_of(" \t"));
    matchs.erase(0, matchs.find_first_not_of(","));
    matchs.erase(0, matchs.find_first_not_of("x"));
    rs2_value=stoi(matchs);
    cout << "rs2_value:"<<rs2_value<<"\n";
}

int main(){
    vector<pair<string,char>> formats = {
        {"add",'R'},
        {"and",'R'},
        {"or",'R'},
        {"sll",'R'},
        {"addi",'I'}
    };

    ifstream file("help.s");     // file with the instructions
    
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    string line;
    smatch match;
    string matchs;
    regex pattern("^[a-z]{2,5}\\b");
    while (getline(file, line)) {
        cout << line << '\n';
        regex_search(line,match,pattern);
        matchs=match.str();
        cout << matchs <<"\n";

        auto it = find_if(formats.begin(), formats.end(), [&matchs](const auto& pair) {
        return pair.first == matchs; });
        if(it==formats.end()){
            std::cout<< "instruction not found\n";
        }
        size_t pos = line.find(matchs);
        line = line.substr(0, pos) + line.substr(pos + matchs.length());
        cout << it->second<<"new_line:"<<line<<"\n";
        R(line);
    }
    
    file.close();

    return 0;
}