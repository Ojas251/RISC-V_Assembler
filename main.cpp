#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream>
#include <stdint.h>
using namespace std;

vector<pair<string,long int>> labels;

regex add(R"(^[ \t]*add[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)x(\d|[12]\d|3[01])[ \t]*$)");
regex _and(R"(^[ \t]*and[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)x(\d|[12]\d|3[01])[ \t]*$)");
regex _or(R"(^[ \t]*or[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)x(\d|[12]\d|3[01])[ \t]*$)");
regex sll(R"(^[ \t]*sll[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)x(\d|[12]\d|3[01])[ \t]*$)");
regex slt(R"(^[ \t]*slt[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)x(\d|[12]\d|3[01])[ \t]*$)");
regex sra(R"(^[ \t]*sra[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)x(\d|[12]\d|3[01])[ \t]*$)");
regex srl(R"(^[ \t]*srl[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)x(\d|[12]\d|3[01])[ \t]*$)");
regex sub(R"(^[ \t]*sub[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)x(\d|[12]\d|3[01])[ \t]*$)");
regex _xor(R"(^[ \t]*xor[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)x(\d|[12]\d|3[01])[ \t]*$)");
regex mul(R"(^[ \t]*mul[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)x(\d|[12]\d|3[01])[ \t]*$)");
regex _div(R"(^[ \t]*div[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)x(\d|[12]\d|3[01])[ \t]*$)");
regex rem(R"(^[ \t]*rem[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)x(\d|[12]\d|3[01])[ \t]*$)");
regex sb(R"(^[ \t]*sb[ \t]+x(\d|[12]\d|3[01])[ \t]*[ ,][ \t]*(-?[1-9]\d*|0|-?0x[\dA-Fa-f]{1,8})[ \t]*\([ \t]*x(\d|[12]\d|3[01])[ \t]*\)[ \t]*$)");
regex sw(R"(^[ \t]*sw[ \t]+x(\d|[12]\d|3[01])[ \t]*[ ,][ \t]*(-?[1-9]\d*|0|-?0x[\dA-Fa-f]{1,8})[ \t]*\([ \t]*x(\d|[12]\d|3[01])[ \t]*\)[ \t]*$)");
regex sd(R"(^[ \t]*sd[ \t]+x(\d|[12]\d|3[01])[ \t]*[ ,][ \t]*(-?[1-9]\d*|0|-?0x[\dA-Fa-f]{1,8})[ \t]*\([ \t]*x(\d|[12]\d|3[01])[ \t]*\)[ \t]*$)");
regex sh(R"(^[ \t]*sh[ \t]+x(\d|[12]\d|3[01])[ \t]*[ ,][ \t]*(-?[1-9]\d*|0|-?0x[\dA-Fa-f]{1,8})[ \t]*\([ \t]*x(\d|[12]\d|3[01])[ \t]*\)[ \t]*$)");
regex lb(R"(^[ \t]*lb[ \t]+x(\d|[12]\d|3[01])[ \t]*[ ,][ \t]*(-?[1-9]\d*|0|-?0x[\dA-Fa-f]{1,8})[ \t]*\([ \t]*x(\d|[12]\d|3[01])[ \t]*\)[ \t]*$)");
regex lw(R"(^[ \t]*lw[ \t]+x(\d|[12]\d|3[01])[ \t]*[ ,][ \t]*(-?[1-9]\d*|0|-?0x[\dA-Fa-f]{1,8})[ \t]*\([ \t]*x(\d|[12]\d|3[01])[ \t]*\)[ \t]*$)");
regex lh(R"(^[ \t]*lh[ \t]+x(\d|[12]\d|3[01])[ \t]*[ ,][ \t]*(-?[1-9]\d*|0|-?0x[\dA-Fa-f]{1,8})[ \t]*\([ \t]*x(\d|[12]\d|3[01])[ \t]*\)[ \t]*$)");
regex ld(R"(^[ \t]*ld[ \t]+x(\d|[12]\d|3[01])[ \t]*[ ,][ \t]*(-?[1-9]\d*|0|-?0x[\dA-Fa-f]{1,8})[ \t]*\([ \t]*x(\d|[12]\d|3[01])[ \t]*\)[ \t]*$)");
regex addi(R"(^[ \t]*addi[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)(-?[1-9]\d*|0|-?0x[\dA-Fa-f]{1,8})[ \t]*$)");
regex andi(R"(^[ \t]*andi[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)(-?[1-9]\d*|0|-?0x[\dA-Fa-f]{1,8})[ \t]*$)");
regex ori(R"(^[ \t]*ori[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)(-?[1-9]\d*|0|-?0x[\dA-Fa-f]{1,8})[ \t]*$)");
regex jalr(R"(^[ \t]*jalr[ \t]+x(\d|[12]\d|3[01])[ \t]*[ ,][ \t]*(-?[1-9]\d*|0|-?0x[\dA-Fa-f]{1,8})[ \t]*\([ \t]*x(\d|[12]\d|3[01])[ \t]*\)[ \t]*$)");
regex beq(R"(^[ \t]*beq[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)([a-zA-Z_]\w*)[ \t]*$)");
regex bne(R"(^[ \t]*bne[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)([a-zA-Z_]\w*)[ \t]*$)");
regex bge(R"(^[ \t]*bge[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)([a-zA-Z_]\w*)[ \t]*$)");
regex blt(R"(^[ \t]*blt[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)([a-zA-Z_]\w*)[ \t]*$)");
regex lui(R"(^[ \t]*lui[ \t]+x(\d|[12]\d|3[01])[ \t]*[ ,][ \t]*([1-9]\d*|0|0x[\dA-Fa-f]{1,8})[ \t]*$)");
regex auipc(R"(^[ \t]*auipc[ \t]+x(\d|[12]\d|3[01])[ \t]*[ ,][ \t]*([1-9]\d*|0|0x[\dA-Fa-f]{1,8})[ \t]*$)");
regex jal(R"(^[ \t]*jal[ \t]+x(\d|[12]\d|3[01])[ \t]*[ ,][ \t]*([a-zA-Z_]\w*)[ \t]*$)");


long int pc=0, ic=0;

ofstream& clear(ofstream& mcFile) {
    mcFile.close(); // Close the file
    mcFile.open("output.mc", ofstream::out | ofstream::trunc); // Reopen the file in truncate mode
    if (!mcFile.is_open()) {
        cout << "Error occurred while clearing file.\n";
        return mcFile; // Return false indicating failure
    }
    
    cout << "File has been cleared.\n";
    return mcFile; // Return true indicating success
}
bitset<32> ToBin(string imm,int para,ofstream& mcFile) {
    bitset<32> bin(0);
    int neg=0,i;
     long int up12,low12,up20,low20,immval;
    up12=2047; 
    low12=-2048;
    up20=524287;
    low20=-524288;
    if (imm[0] == '-') {
        imm = imm.substr(1);
        neg=1;
    }
    if (imm[0] == '0' && imm[1] == 'x') {
        for ( i = 2; i < imm.size(); i++) {
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
   immval=static_cast<long>(bin.to_ulong());
    //cout<<"imm:"<<immval<<endl;
    if(para==12){
        if(immval>up12 || immval<low12){
                    clear(mcFile);
                    mcFile << "instruction has out of bounds immediate ";
                    mcFile.close();
                    exit(EXIT_FAILURE);
        }
    }
    else{
        if(immval>up20 || immval<low20){
              clear(mcFile);
                    mcFile << "Instruction has out of bounds immediate value ";
                    mcFile.close();
                    exit(EXIT_FAILURE);
        }
    }
    bitset<32> bin32(bin.to_ulong());
    return bin32;
}

string toHex(int ic){
    stringstream ss;
    ss << hex << ic;
    while (ss.str().length() < 10) ss.str("0" + ss.str());
    ss << "0x";
    return ss.str();
}

string BinToHex(bitset<32> bin) {
    stringstream ss;
    ss << hex << bin.to_ulong();
    while (ss.str().length() < 8) ss.str("0" + ss.str());
    return ss.str();
}

bitset<32> R(string Inst, bitset<32> mc){
    smatch match;
    bitset<32> rd,rs1,rs2,matchs;
    regex pattern_reg(R"(x(\d|[12]\d|3[01])(?=[ ,]|$))");
    regex_search(Inst, match, pattern_reg);
    rd=stoi(match.str(1));
    Inst = match.suffix();
    
    regex_search(Inst, match, pattern_reg);
    rs1=stoi(match.str(1));
    Inst = match.suffix();

    regex_search(Inst, match, pattern_reg); 
    rs2=stoi(match.str(1));

    rs1<<=15;
    mc = mc|rs1;

    rs2<<=20;
    mc = mc|rs2;

    rd<<=7;
    mc = mc|rd;
    return mc;    
}

bitset<32> I(bitset<32> inst, string asm_instr,ofstream& mcFile) {
    smatch match;
    regex pattern(R"(x([1-2]\d|3[01]|\d))");
    regex_search(asm_instr, match, pattern);
    bitset<32> rd(stoi(match.str().substr(1)));
    rd<<=7;
    asm_instr = match.suffix();
    regex_search(asm_instr, match, pattern);
    bitset<32> rs1(stoi(match.str().substr(1)));
    rs1<<=15;
    asm_instr = match.suffix();
    regex pattern_imm(R"((-?0x[\dA-Fa-f]{1,8}|-?[1-9]\d*|0))");
    regex_search(asm_instr, match, pattern_imm);
    bitset<32> imm(ToBin(match.str(),12,mcFile));
    imm<<=20;
    inst|=rd;
    inst|=rs1;
    inst|=imm;
    // cout<<inst<<endl;
    return inst;
}


bitset<32> U(bitset<32> inst, string asm_instr,ofstream& mcFile) {
    smatch match;
    regex pattern(R"(x([1-2]\d|3[01]|\d))");
    regex_search(asm_instr, match, pattern);
    bitset<32> rd(stoi(match.str().substr(1)));
    rd<<=7;
    asm_instr = match.suffix();
    regex pattern_imm(R"((0x[\dA-Fa-f]{1,8}|[1-9]\d*|0))");
    regex_search(asm_instr, match, pattern_imm);
    bitset<32> imm(ToBin(match.str(),20,mcFile));
    cout << imm << endl;
    imm<<=12;
    inst|=rd;
    inst|=imm;
    // cout<<inst<<endl;
    return inst;
}

bitset<32> S(bitset<32> inst, string asm_instr,ofstream& mcFile) {
    smatch match;
    regex pattern(R"(x([1-2]\d|3[01]|\d))");
    regex_search(asm_instr, match, pattern);
    bitset<32> rs2(stoi(match.str().substr(1)));
    rs2<<=20;
    asm_instr = match.suffix();
    regex pattern_imm(R"((-?0x[\dA-Fa-f]{1,8}|-?[1-9]\d*|0))");
    regex_search(asm_instr, match, pattern_imm);
    bitset<32> imm(ToBin(match.str(),12,mcFile));
    bitset<32> imm1=(imm>>5)<<25, imm2=(imm & bitset<32>(31))<<7;
    asm_instr = match.suffix();
    regex_search(asm_instr, match, pattern);
    bitset<32> rs1(stoi(match.str().substr(1)));
    rs1<<=15;
    inst|=rs1;
    inst|=rs2;
    inst|=imm1;
    inst|=imm2;
    // cout<<inst<<endl;
    return inst;
}




bitset<32> SB(bitset<32> inst, string asm_instr ){
    smatch match;
    regex pattern(R"(x([1-2]\d|3[01]|\d))");
    regex_search(asm_instr, match, pattern);
    bitset<32> rs1(stoi(match.str().substr(1)));
    rs1<<=15;
    asm_instr = match.suffix();
    regex_search(asm_instr, match, pattern);
    bitset<32> rs2(stoi(match.str().substr(1)));
    rs2<<=20;
    asm_instr = match.suffix();
    regex patt_label(R"([_a-zA-Z]\w*)");
    regex_search(asm_instr,match,patt_label);
    string matchs;
    matchs=match.str();
    auto it = find_if(labels.begin(), labels.end(), [matchs](const pair<string, long int>& p) {
        return p.first == matchs;
    });
    long int offset ;
    if (it != labels.end()) {
        offset=it->second;
    } else {
        cout<< "Label of the branch instruction not found." << endl;
        return inst;
    }
    offset = offset - ic;    // by how much the branching is to be done; checking if it's in range?
    bitset<32> off(offset);
    bitset<32> off1=off;
    off1>>=12;
    off1<<=31;
    inst = inst | off1;  // 12th bit
    off1 = off;
    off1>>=5;
    off1<<=26;
    off1>>=1;
    inst = inst | off1;  // 10 - 5 bits
    off1 = off;
    off1>>=1;
    off1<<=28;
    off1>>=20;
    inst = inst | off1; // 4 - 1 bits
    off1 = off;
    off1>>=11;
    off1<<=31;
    off1>>=24;
    inst = inst | off1;
    inst = inst | rs1 ; // rs1
    inst = inst | rs2 ; // rs2
    return inst;
}
bitset<32> UJ(bitset<32> inst, string asm_instr){
    smatch match;
    regex pattern(R"(x([1-2]\d|3[01]|\d))");
    regex_search(asm_instr, match, pattern);
    bitset<32> rd(stoi(match.str().substr(1)));
    rd<<=7;
    asm_instr = match.suffix();
    regex patt_label(R"([_a-zA-Z]\w*)");
    regex_search(asm_instr,match,patt_label);
    string matchs;
    matchs=match.str();
    auto it = find_if(labels.begin(), labels.end(), [matchs](const pair<string, long int>& p) {
        return p.first == matchs;
    });
    long int offset ;
    if (it != labels.end()) {
        offset=it->second;
    } else {
        cout<< "Label of the branch instruction not found." << endl;
        return inst;
    }
    offset = offset - ic;
    bitset<32> off(offset);
    bitset<32> off1=off;
    off1>>=20;
    off1<<=31;
    inst=inst | off1;  // 20th bit
    off1=off;
    off1>>=1;
    off1<<=22;
    off1>>=1;
    inst=inst | off1; // 10-1 bits
    off1=off;
    off1>>=11;
    off1<<=31;
    off1>>=11;
    inst=inst | off1; // 11th bit
    off1=off;
    off1>>=12;
    off1<<=24;
    off1>>=12;
    inst=inst | off1; // 19-12 bits
    inst = inst | rd ; // rd
    return inst;
}

bitset<32> I_L(bitset<32> inst, string asm_instr,ofstream& mcFile){
    smatch match;
    regex pattern(R"(x([1-2]\d|3[01]|\d))"); 
    regex_search(asm_instr, match, pattern);
    bitset<32> rd(stoi(match.str().substr(1)));
    rd<<=7;
    asm_instr = match.suffix();
   string matchs;
   regex pattern2(R"((-?0x[\dA-Fa-f]{1,8}|-?[1-9]\d*|0)\()");
    regex_search(asm_instr,match,pattern2);
    if(match.size()==0){
        cout<<"no match\n";
    }
    matchs=match.str();
    matchs.erase(matchs.size()-1,1);
    regex pattern3(R"(0x)");
    regex_search(matchs,match,pattern3);
    long long int offset;
    long long int offsetupper = 2047 ;
    long long int offsetlower = -2048 ;
    if(match.size()!=0){
         offset = stoi(matchs, nullptr, 16);
    }
    else{
        offset = stoi(matchs, nullptr, 10);
    }
    if(offset > offsetupper || offset < offsetlower){
        cout<<"ERROR\n";
        return inst;
    }
     bitset<32> off(offset);
    off<<=20;
    regex pattern1(R"(\(x([1-2]\d|3[01]|\d)\))");  
    regex_search(asm_instr, match, pattern1);
    if(!match.empty()){          
    matchs=match.str();
    matchs.erase(0,1);
    matchs.erase(matchs.size()-1,1);
    matchs.erase(0,1);
    cout<< matchs<<endl;
    bitset<32> rs1(stoi(matchs));
    rs1<<=15;
    //cout << "rs1:"<<rs1<<",offset:"<<off<<endl;
    inst = inst | off;
    inst = inst | rs1;
    inst = inst | rd;}
    return inst;

}

bitset<32> mcode(string asm_inst,ofstream& mcFile){
    bitset<32> inst(0);
    if (regex_match(asm_inst, add)) {
        inst = bitset<32>("00000000000000000000000000110011");
        inst = R(asm_inst, inst);
        }
    else if (regex_match(asm_inst, _and)) {
        inst = bitset<32>("00000000000000000111000000110011");
        inst = R(asm_inst, inst);
        }
    else if (regex_match(asm_inst, _or)) {
        inst = bitset<32>("00000000000000000110000000110011");
        inst = R(asm_inst, inst);
        }
    else if (regex_match(asm_inst, sll)) {
        inst = bitset<32>("00000000000000000001000000110011");
        inst = R(asm_inst, inst);
        }
    else if (regex_match(asm_inst, slt)) {
        inst = bitset<32>("00000000000000000010000000110011");
        inst = R(asm_inst, inst);
        }
    else if (regex_match(asm_inst, sra)) {
        inst = bitset<32>("01000000000000000101000000110011");
        inst = R(asm_inst, inst);
        }
    else if (regex_match(asm_inst, srl)) {
        inst = bitset<32>("00000000000000000101000000110011");
        inst = R(asm_inst, inst);
        }
    else if (regex_match(asm_inst, sub)) {
        inst = bitset<32>("01000000000000000000000000110011");
        inst = R(asm_inst, inst);
        }
    else if (regex_match(asm_inst, _xor)) {
        inst = bitset<32>("00000000000000000100000000110011");
        inst = R(asm_inst, inst);
        }
    else if (regex_match(asm_inst, mul)) {
        inst = bitset<32>("00000010000000000000000000110011");
        inst = R(asm_inst, inst);
        }
    else if (regex_match(asm_inst, _div)) {
        inst = bitset<32>("00000010000000000100000000110011");
        inst = R(asm_inst, inst);
        }
    else if (regex_match(asm_inst, rem)) {
        inst = bitset<32>("00000010000000000110000000110011");
        inst = R(asm_inst, inst);
        }
    else if (regex_match(asm_inst, sb)) {
        inst = bitset<32>("00000000000000000000000000100011");
        inst = S(inst, asm_inst,mcFile);
        }
    else if (regex_match(asm_inst, sw)) {
        inst = bitset<32>("00000000000000000010000000100011");
       inst = S(inst, asm_inst,mcFile);
        }
    else if (regex_match(asm_inst, sd)) {
        inst = bitset<32>("00000000000000000011000000100011");
        inst = S(inst, asm_inst,mcFile);
        }
    else if (regex_match(asm_inst, sh)) {
        inst = bitset<32>("00000000000000000001000000100011");
        inst = S(inst, asm_inst,mcFile);
        }
    else if (regex_match(asm_inst, lb)) {
        inst = bitset<32>("00000000000000000000000000000011");
        inst = I_L(inst, asm_inst,mcFile);
        }
    else if (regex_match(asm_inst, lw)) {
        inst = bitset<32>("00000000000000000010000000000011");
       inst = I_L(inst, asm_inst,mcFile);
        }
    else if (regex_match(asm_inst, ld)) {
        inst = bitset<32>("00000000000000000011000000000011");
        inst = I_L(inst, asm_inst,mcFile);
        }
    else if(regex_match(asm_inst,lh)) {
        inst = bitset<32>("00000000000000000001000000000011");
         inst = I_L(inst, asm_inst,mcFile);
        }
    else if (regex_match(asm_inst, addi)) {
        inst = bitset<32>("00000000000000000000000000010011");
        inst = I(inst, asm_inst,mcFile);
        }
    else if (regex_match(asm_inst, andi)) {
        inst = bitset<32>("00000000000000000111000000010011");
        inst = I(inst, asm_inst,mcFile);
        }
    else if (regex_match(asm_inst, ori)) {
        inst = bitset<32>("00000000000000000110000000010011");
        inst = I(inst, asm_inst,mcFile);
        }
    else if (regex_match(asm_inst, jalr)) {
        inst = bitset<32>("00000000000000000000000001100111");
        inst = I_L(inst, asm_inst,mcFile);
        }
    else if (regex_match(asm_inst, bne)) {
        inst = bitset<32>("00000000000000000001000001100011");
        inst = SB(inst,asm_inst);
        }
    else if (regex_match(asm_inst, beq)) {
        inst = bitset<32>("00000000000000000000000001100011");
        inst = SB(inst,asm_inst);
        }
    else if (regex_match(asm_inst, bge)) {
        inst = bitset<32>("00000000000000000101000001100011");
        inst = SB(inst,asm_inst);
        }
    else if (regex_match(asm_inst, blt)) {
        inst = bitset<32>("00000000000000000100000001100011");
        inst = SB(inst,asm_inst);
        }
    else if (regex_match(asm_inst, lui)) {
        inst = bitset<32>("00000000000000000000000000110111");
        inst = U(inst, asm_inst,mcFile);
        }
    else if (regex_match(asm_inst, auipc)) {
        inst = bitset<32>("00000000000000000000000000010111");
        inst = U(inst, asm_inst,mcFile);
        }
    else if (regex_match(asm_inst, jal)) {
        inst = bitset<32>("00000000000000000000000001101111");
        inst = UJ(inst, asm_inst);
        }
    else {
        inst = bitset<32>(0);
        cout << "Error: Instruction ("<< asm_inst <<") not found/ Invalid instruction" << endl;
        }
    return inst;
}

int data_lab(string line,long int text){
    smatch match;
    string matchs;
    regex patt_var_name(R"([_a-zA-Z]\w*(?=\s*:))");
    sregex_iterator next(line.begin(), line.end(), patt_var_name);
    sregex_iterator end;
    while (next != end) {
    match = *next;
    matchs = match.str();
    auto it = find_if(labels.begin(), labels.end(), [matchs](const pair<string, long int>& p) {
        return p.first == matchs;
    });
    if(it!=labels.end()){
        return -1;
    }
    labels.push_back(make_pair(matchs,text));
    next++;
    } 
    return 0;             

}


int main() {
    ifstream file("input.asm");     // file with the instructions
    ofstream mcFile("output.mc");
    int dcount=0;    
    if (!file.is_open()) {
        cout << "Error opening file\n";
        return 0;
    }
    mcFile << "<DATA SEGMENT>" << endl;
    string line;
    char format;
    smatch match,matchtemp;
    string matchs;
    //bitset <32> mc;
    long int text=0x0; 
    long long int data=0x10000000;
    int64_t datav;
    long int uplimitdec= 2147483647;
    long int lowlimitdec = -2147483648;
    long long int uplimitdecd=9223372036854775807;
    int64_t lowlimitdecd = INT64_C(-9223372036854775807);
    int lowlimitdech=-32768;
    int uplimitdech=32767;
    int lowlimitdecb=-128;
    int uplimitdecb=127;
    int flag;

    string hexdata,hexdatav;

   
    regex patt_all(R"(^\s*(\.text\s*|\.data\s*|[_a-zA-Z]\w*:|([_a-zA-Z]\w*\s*:\s*)?\.word|([_a-zA-Z]\w*\s*:\s*)?\.dword|([_a-zA-Z]\w*\s*:\s*)?\.byte|([_a-zA-Z]\w*\s*:\s*)?\.half|([_a-zA-Z]\w*\s*:\s*)?\.asciz))");
    
    regex patt_text(R"(^\s*\.text\s*)"); 
   
    regex patt_data(R"(^\s*\.data\s*)");
    
    regex patt_label(R"([_a-zA-Z]\w*:)"); 

    regex patt_word(R"(^\s*([_a-zA-Z]\w*\s*:\s*){0,}\s*\.word\s*(?=(-?(0x(\d|[a-f]|[A-F])+|\d+)\s*(,)?\s*)*$))");

    regex patt_dword(R"(^\s*([_a-zA-Z]\w*\s*:\s*){0,}\s*\.dword\s*(?=(-?(0x(\d|[a-f]|[A-F])+|\d+)\s*(,)?\s*)*$))");
    
    regex patt_byte(R"(^\s*([_a-zA-Z]\w*\s*:\s*){0,}\s*\.byte\s*(?=(-?(0x(\d|[a-f]|[A-F])+|\d+)\s*(,)?\s*)*$))");
   
    regex patt_half(R"(^\s*([_a-zA-Z]\w*\s*:\s*){0,}\s*\.half\s*(?=(-?(0x(\d|[a-f]|[A-F])+|\d+)\s*(,)?\s*)*$))");
    
    regex patt_asciz(R"(^\s*([_a-zA-Z]\w*\s*:\s*){0,}\s*\.asciz\s*(?=(".*")$))");
    
    regex patt_int(R"(-?(0x(\d|[a-f]|[A-F])+|\d+)\s*)");
    
    regex patt_str(R"(".*")");

    regex patt_comments("#.*");
   
    regex pattern(R"(^\s*[a-z]{2,5}\b)");

    regex pattern3(R"(0x)");

    regex patt_err(R"(^\s*$)");
   
    ofstream tempFile("temp.asm");
    //ofstream mcFile("output.mc");

    while(getline(file,line)){
        line = regex_replace(line, patt_comments, "");
        regex_search(line,match,patt_all);
        
        if(match.size()!=0){
            dcount=0;
            regex_search(line,match,patt_text);
            if(match.size()!=0){
                dcount++;
               line = match.suffix();
               cout<< line<<endl;
               regex_search(line,match,pattern);
               if(match.size()!=0){
                  tempFile<<line<<"\n";
                  text=text+4;
                  line = match.suffix();
                }
                regex_search(line,match,patt_err);
                if(match.size()==0){
                    mcFile<<"ERROR\n";
                }

               continue;
            }
         
            regex_search(line,match,patt_data);
            if (match.size()!=0){
                dcount++;
                //cout << "yes\n"<<line<<endl;
                line = match.suffix();      
                regex_search(line,match,pattern);
                if(match.size()!=0){
                  //cout<< line<<endl;
                  tempFile<<line<<"\n";
                  text=text+4;
                  line = match.suffix();  
                }
                regex_search(line,match,patt_err);
                if(match.size()==0){
                    clear(mcFile);
                    mcFile << line << "\n";
                    mcFile << "Instruction is gibberish ";
                    mcFile.close();
                    exit(EXIT_FAILURE);
                }
                continue;
            }
            
            regex_search(line,match,patt_word);
            if(match.size()!=0){
                dcount++;
                flag=data_lab(line,text);         //here
                if(flag==-1){
                    clear(mcFile);
                    mcFile << "Label Already Exists";
                    mcFile.close();
                    exit(EXIT_SUCCESS);
                }
                line=match.suffix();
                sregex_iterator next(line.begin(), line.end(), patt_int);
                sregex_iterator end;
                while (next != end) {
                    match = *next;
                    matchs = match.str();
                    matchtemp=match;
                    int datav;
                    if (regex_search(matchs, match, pattern3)){ 
                        try {
                        datav = std::stoi(matchs, nullptr, 16); // Convert hexadecimal string to integer
                    } catch (const std::out_of_range& e) {
                    // stoi failed due to out of range value
                    clear(mcFile);
                    mcFile << "Error: word data out of range\n";
                    mcFile.close();
                    exit(EXIT_FAILURE);
                    }
                    } else {
                    try {
                    datav = std::stoi(matchs); // Convert decimal string to integer
                    } catch (const std::out_of_range& e) {
                    // stoi failed due to out of range value
                    clear(mcFile);
                    mcFile << "Error: word data out of range\n";
                    mcFile.close();
                    exit(EXIT_FAILURE);
                    }
                    }
                    if (datav < lowlimitdec || datav > uplimitdec) {
                        clear(mcFile);
                        mcFile << "Error word out of bounds\n";
                        mcFile.close();
                        exit(EXIT_SUCCESS);
                        ++next;
                        continue;
                    }
                    stringstream ss;
                    ss << hex << data;
                    string hexdata = ss.str();

                    stringstream ss1;
                    ss1 << hex << datav;
                    while (ss1.str().length() < 8) ss1.str("0" + ss1.str());
                    string hexdatav = ss1.str();

                    if (hexdatav.size() > 8) hexdatav.erase(0, hexdatav.size()-8);

                    mcFile << "0x" << hexdata << " " << "0x" << hexdatav << "\n";
                    data += 4;
                    next++;
                }
                line=matchtemp.suffix();
                regex_search(line,match,patt_err);
                if(match.size()==0){
                    mcFile<<"ERROR\n";
                }
                continue;
            }
           
             regex_search(line,match,patt_dword);
            if(match.size()!=0){
                dcount++;
                flag=data_lab(line,text);         //here
                if(flag==-1){
                     clear(mcFile);
                    mcFile << "Label Already Exists";
                    mcFile.close();
                    exit(EXIT_SUCCESS);
                }
                line=match.suffix();
                sregex_iterator next(line.begin(), line.end(), patt_int);
                sregex_iterator end;
                while (next != end) {
                    match = *next;
                    matchs = match.str();
                    matchtemp=match;
                    long long int datav;
                  if (regex_search(matchs, match, pattern3)){ 
                        try {
                        datav = std::stoll(matchs, nullptr, 16); // Convert hexadecimal string to integer
                    } catch (const std::out_of_range& e) {
                    // stoi failed due to out of range value
                    clear(mcFile);
                    mcFile << "Error: dword data out of range\n";
                    mcFile.close();
                    exit(EXIT_FAILURE);
                    }
                    } else {
                    try {
                    datav = std::stoll(matchs); // Convert decimal string to integer
                    } catch (const std::out_of_range& e) {
                    // stoll failed due to out of range value
                    clear(mcFile);
                    mcFile << "Error: dword data out of range\n";
                    mcFile.close();
                    exit(EXIT_FAILURE);
                    }
                    }
                    if (datav < lowlimitdecd || datav > uplimitdecd) {
                        mcFile << "Error\n";
                        ++next;
                        continue;
                    }
                    stringstream ss;
                    ss << hex << data;
                    string hexdata = ss.str();

                    stringstream ss1;
                    ss1 << hex << datav;
                    while (ss1.str().length() < 16) ss1.str("0" + ss1.str());
                    string hexdatav = ss1.str();

                    if (hexdatav.size() > 16) hexdatav.erase(0, hexdatav.size()-16);

                    mcFile << "0x" << hexdata << " " << "0x" << hexdatav << "\n";
                    data += 8;
                    next++;
                }
                 line=matchtemp.suffix();
                regex_search(line,match,patt_err);
                if(match.size()==0){
                    mcFile<<"ERROR\n";
                }
                continue;
            }
            regex_search(line,match,patt_half);
            if(match.size()!=0){
                dcount++;
                flag=data_lab(line,text);         //here
                if(flag==-1){
                      clear(mcFile);
                    mcFile << "Label Already Exists";
                    mcFile.close();
                    exit(EXIT_SUCCESS);
                }
                line=match.suffix();
                sregex_iterator next(line.begin(), line.end(), patt_int);
                sregex_iterator end;
                while (next != end) {
                    match = *next;
                    matchs = match.str();
                    matchtemp=match;
                    int datav;
                     if (regex_search(matchs, match, pattern3)){ 
                        try {
                        datav = std::stoi(matchs, nullptr, 16); // Convert hexadecimal string to integer
                    } catch (const std::out_of_range& e) {
                    // stoi failed due to out of range value
                    clear(mcFile);
                    mcFile << "Error: half data out of range\n";
                    mcFile.close();
                    exit(EXIT_FAILURE);
                    }
                    } else {
                    try {
                    datav = std::stoi(matchs); // Convert decimal string to integer
                    } catch (const std::out_of_range& e) {
                    // stoi failed due to out of range value
                    clear(mcFile);
                    mcFile << "Error: half data out of range\n";
                    mcFile.close();
                    exit(EXIT_FAILURE);
                    }
                    }
                    if (datav < lowlimitdech || datav > uplimitdech) {
                        mcFile << "Error\n";
                        clear(mcFile);
                        mcFile << "Error half value out of bounds\n";
                        mcFile.close();
                        exit(EXIT_SUCCESS);
                        ++next;
                        continue;
                    }
                    stringstream ss;
                    ss << hex << data;
                    string hexdata = ss.str();

                    stringstream ss1;
                    ss1 << hex << datav;
                    while (ss1.str().length() < 4) ss1.str("0" + ss1.str());
                    string hexdatav = ss1.str();
                    if (hexdatav.size() > 4) hexdatav.erase(0, hexdatav.size()-4);


                    mcFile << "0x" << hexdata << " " << "0x" << hexdatav << "\n";
                    data += 2;
                    next++;
                }
                line=matchtemp.suffix();
                regex_search(line,match,patt_err);
                if(match.size()==0){
                    mcFile<<"ERROR\n";
                }
                continue;
            }
            
            regex_search(line,match,patt_byte);
            if(match.size()!=0){
                dcount++;
                flag=data_lab(line,text);         //here
                if(flag==-1){
                      clear(mcFile);
                    mcFile << "Label Already Exists";
                    mcFile.close();
                    exit(EXIT_SUCCESS);
                }
                line=match.suffix();
                sregex_iterator next(line.begin(), line.end(), patt_int);
                sregex_iterator end;
                while (next != end) {
                    match = *next;
                    matchs = match.str();
                    matchtemp=match;
                    int datav;
                     if (regex_search(matchs, match, pattern3)){ 
                        try {
                        datav = std::stoi(matchs, nullptr, 16); // Convert hexadecimal string to integer
                    } catch (const std::out_of_range& e) {
                    // stoi failed due to out of range value
                    clear(mcFile);
                    mcFile << "Error:   Byte data out of range\n";
                    mcFile.close();
                    exit(EXIT_FAILURE);
                    }
                    } else {
                    try {
                    datav = std::stoi(matchs); // Convert decimal string to integer
                    } catch (const std::out_of_range& e) {
                    // stoi failed due to out of range value
                    clear(mcFile);
                    mcFile << "Error: Byte data out of range\n";
                    mcFile.close();
                    exit(EXIT_FAILURE);
                    }
                    }
                    if (datav < lowlimitdecb || datav > uplimitdecb) {
                        mcFile << "Error\n";
                        clear(mcFile);
                        mcFile << "Error: Byte data out of range\n";
                        mcFile.close();
                        exit(EXIT_FAILURE);
                        ++next;
                        continue;
                    }
                    stringstream ss;
                    ss << hex << data;
                    string hexdata = ss.str();

                    stringstream ss1;
                    ss1 << hex << datav;
                    while (ss1.str().length() < 2) ss1.str("0" + ss1.str());
                    string hexdatav = ss1.str();
                    if (hexdatav.size() > 2) hexdatav.erase(0, hexdatav.size()-2);

                    mcFile << "0x" << hexdata << " " << "0x" << hexdatav << "\n";
                    data += 1;
                    next++;
                }
                line=matchtemp.suffix();
                regex_search(line,match,patt_err);
                if(match.size()==0){
                    mcFile<<"ERROR\n";
                }
                continue;
            }
            
            regex_search(line,match,patt_asciz);
            
            if(match.size()!=0){
                dcount++;
                flag=data_lab(line,text);         //here
                if(flag==-1){
                     clear(mcFile);
                    mcFile << "Label Already Exists";
                    mcFile.close();
                    exit(EXIT_SUCCESS);
                }
                regex_search(line,match,patt_str);
                line=match.suffix();
                matchs=match.str();
                matchs.erase(0,1);
                matchs.erase(matchs.size() - 1, 1);
                int size = matchs.size()+1;
                stringstream ss;
                ss << hex << data;
                hexdata = ss.str();
                stringstream hexstr;
                while(matchs.size()) {
                    hexstr << hex << (unsigned int)matchs[0];
                    matchs.erase(0, 1);
                }
                mcFile << "0x" << hexdata << " " << "0x" << hexstr.str() << "00" << "\n";
                
                data=data+size;
                line=match.suffix();
                regex_search(line,match,patt_err);
                if(match.size()==0){
                    mcFile<<"ERROR\n";
                }
                continue;
            }
            regex_search(line,match,patt_label);
            if(match.size()!=0){
                dcount++; 
               sregex_iterator next(line.begin(), line.end(), patt_label);
               sregex_iterator end;
               while (next != end) { 
               match = *next;
               matchs=match.str();
               size_t found = matchs.find(":");
                if (found != std::string::npos) {
                matchs.erase(found);
               }
               bool exists = false;
               for(auto i:labels) if(i.first == matchs) exists = true;
               if(!exists) labels.push_back(make_pair(matchs,text));
               else {
                    clear(mcFile);
                    mcFile<<"Label already exists"<<endl;
                    mcFile.close();
                    exit(EXIT_FAILURE);
               }
                next++;
                line=match.suffix();
               }
               
               regex_search(line,match,pattern);
                if(match.size()!=0){
                  tempFile<<line<<"\n";
                  text=text+4;
                  line=match.suffix();
                }
                
                regex_search(line,match,patt_err);
                if(match.size()==0){
                    clear(mcFile);
                    mcFile << line << "\n";
                    mcFile << "Instruction is gibberish ";
                    mcFile.close();
                    exit(EXIT_FAILURE);
                }
               continue;
            }
              if(dcount==0){
            clear(mcFile);
            mcFile << "Wrong syntax of data";
            mcFile.close();
            exit(EXIT_FAILURE);
        }
        }
        else{
              if (!regex_search(line, match, patt_err)){
              regex_search(line,match,pattern);
              if(match.size()!=0){
                  tempFile<<line<<"\n";
                  text=text+4;
              }
               else {
                  clear(mcFile);
            mcFile << line << "\n";
            mcFile << "Instruction is gibberish ";
            mcFile.close();
            exit(EXIT_FAILURE);
              }
            }
           }
    }
    cout<<"labels:\n";
    for(int i=0;i<labels.size();i++){
        cout << labels[i].first<<","<<labels[i].second<<"\n";
    }
    
    file.close();
    tempFile.close();
    ifstream file1("temp.asm");
    mcFile << "<TEXT SEGMENT>" << endl;
    bitset<32> mc(0);
    while (getline(file1, line)) {
        //cout << line << endl;
        mc = mcode(line,mcFile);
          if (mc == bitset<32>(0)) {
            clear(mcFile);
            mcFile << line << "  ";
            mcFile  << "Wrong syntax/Invalid instruction";
            mcFile << "\n";
            mcFile.close();
            exit(EXIT_SUCCESS);
        }
        mcFile << toHex(ic) << " 0x" << BinToHex(mc) << endl;
        //cout << toHex(ic) << " " << hex<< mc.to_ullong() << endl;
        ic+=4;
    }
    mcFile << "<HEAP SEGMENT>" << endl << "0x10008000 0x00000000"<< endl << "<STACK SEGMENT>" << endl << "0x7FFFFFDC 0x00000000" << endl;
    mcFile.close();
    file1.close();
}
