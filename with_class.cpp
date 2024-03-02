#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <bitset>
using namespace std;
bitset<32> ToBin(string imm) {
    bitset<12> bin(0);
    int neg=0;
    if (imm[0] == '-') {
        imm = imm.substr(1);
        neg=1;
    }
    if (imm[0] == '0' && imm[1] == 'x') {
        for (int i = 2; i < imm.size(); i++) {
            if (imm[i] >= '0' && imm[i] <= '9') {
                bin <<= 4;
                bin |= imm[i] - '0';
            }
            else if (imm[i] >= 'A' && imm[i] <= 'F') {
                bin <<= 4;
                bin |= imm[i] - 'A' + 10;
            }
            else if (imm[i] >= 'a' && imm[i] <= 'f') {
                bin <<= 4;
                bin |= imm[i] - 'a' + 10;
            }
        }
        if (neg==1) {
            bin = ~bin;
            bin = bin.to_ulong() + 1;
        }
    }
    else {
        if (neg==1) bin = stoi('-'+imm);
        else bin = stoi(imm);
    }
    bitset<32> bin32(bin.to_ulong());
    return bin32;
}

void R(string Inst,bitset<32> mc){
    regex pattern(R"(^[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)x(\d|[12]\d|3[01])[ \t]*$)");
    smatch match;
    regex_search(Inst,match,pattern);
    if(match.size()==0){
        cout << "ERROR\n";
        return;
    }
    string rd,rs1,rs2,matchs;
    regex pattern_reg(R"(x(\d|[12]\d|3[01])(?=[ ,]|$))");
    regex_search(Inst, match, pattern_reg);
    rd=match.str(1);
    Inst = match.suffix().str();
    
    regex_search(Inst, match, pattern_reg);
    rs1=match.str(1);
    Inst = match.suffix().str();

    regex_search(Inst, match, pattern_reg); 
    rs2=match.str(1);
    int rd_value,rs1_value,rs2_value;
    
    rd_value=stoi(rd);
    cout << "rd_value:"<<rd_value<<"\n";

    rs1_value=stoi(rs1);
    cout << "rs1_value:"<<rs1_value<<"\n";

    rs2_value=stoi(rs2);
    cout << "rs2_value:"<<rs2_value<<"\n";

    bitset<32> reg_b;
    reg_b=stoi(rd);
    reg_b<<=7;
    mc = mc|reg_b;

    reg_b=stoi(rs1);
    reg_b<<=15;
    mc = mc|reg_b;

    reg_b=stoi(rs2);
    reg_b<<=20;
    mc = mc|reg_b;
    cout<<"final:"<<mc<<"\n";
    
}

int main(){
    vector<pair<string,char>> formats = {
        {"add",'R'},
        {"and",'R'},
        {"or",'R'},
        {"sll",'R'},
        {"addi",'I'}
    };
    vector<pair<string,bitset<32>>> opcode = {
    {"add", bitset<32>("00000000000000000000000000110011")},
    {"and", bitset<32>("00000000000000000000000000110011")},
    {"or", bitset<32>("00000000000000000000000000110011")},
    {"sll", bitset<32>("00000000000000000000000000110011")},
    {"addi", bitset<32>("00000000000000000000000000010011")}
};
    vector<pair<string,bitset<32>>> func3 = {
    {"add", bitset<32>("00000000000000000000000000000000")},
    {"and", bitset<32>("00000000000000000000000000000111")},
    {"or", bitset<32>("00000000000000000000000000000110")},
    {"sll", bitset<32>("00000000000000000000000000000001")},
    {"addi", bitset<32>("00000000000000000000000000000000")}
};
    vector<pair<string,bitset<32>>> func7 = {
        {"add",bitset<32>("00000000000000000000000000000000")},
        {"and",bitset<32>("00000000000000000000000000000000")},
        {"or",bitset<32>("00000000000000000000000000000000")},
        {"sll",bitset<32>("00000000000000000000000000000000")}
    };
    ifstream file("help.s");     // file with the instructions
    
    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    string line;
    char format;
    smatch match;
    string matchs;
    bitset <32> mc;
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
        format=it->second;

        auto opcode_it = find_if(opcode.begin(), opcode.end(), [&matchs](const auto& pair) {
        return pair.first == matchs; });
        if(opcode_it!=opcode.end()){
        mc = mc | opcode_it->second;}

        auto func3_it = find_if(func3.begin(), func3.end(), [&matchs](const auto& pair) {
        return pair.first == matchs; });
        if(func3_it!=opcode.end()){
        func3_it->second<<=12;
        mc = mc | func3_it->second;}


        auto func7_it = find_if(func7.begin(), func7.end(), [&matchs](const auto& pair) {
        return pair.first == matchs; });
        if(func3_it!=opcode.end()){
        func7_it->second<<=25;
        mc = mc | func7_it->second;}
        
        size_t pos = line.find(matchs);
        line = line.substr(0, pos) + line.substr(pos + matchs.length());

        R(line,mc);
    }
    
    file.close();

    return 0;
}