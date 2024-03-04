#include <iostream>
#include <regex>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

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
regex jalr(R"(^[ \t]*jalr[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)(-?[1-9]\d*|0|-?0x[\dA-Fa-f]{1,8})[ \t]*$)");
regex beq(R"(^[ \t]*beq[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)([a-zA-Z_]\w*)[ \t]*$)");
regex bne(R"(^[ \t]*bne[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)([a-zA-Z_]\w*)[ \t]*$)");
regex bge(R"(^[ \t]*bge[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)([a-zA-Z_]\w*)[ \t]*$)");
regex blt(R"(^[ \t]*blt[ \t]+x(\d|[12]\d|3[01])([ \t]*,[ \t]*x(\d|[12]\d|3[01])[ \t]*,[ \t]*|[ \t]+x(\d|[12]\d|3[01])[ \t]+)([a-zA-Z_]\w*)[ \t]*$)");
regex lui(R"(^[ \t]*lui[ \t]+x(\d|[12]\d|3[01])[ \t]*[ ,][ \t]*([1-9]\d*|0|0x[\dA-Fa-f]{1,8})[ \t]*$)");
regex auipc(R"(^[ \t]*auipc[ \t]+x(\d|[12]\d|3[01])[ \t]*[ ,][ \t]*([1-9]\d*|0|0x[\dA-Fa-f]{1,8})[ \t]*$)");
regex jal(R"(^[ \t]*jal[ \t]+x(\d|[12]\d|3[01])[ \t]*[ ,][ \t]*([a-zA-Z_]\w*)[ \t]*$)");


long int pc=0, ic=0;

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

string toHex(int ic){
    stringstream ss;
    ss << "0x" << hex << ic;
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

bitset<32> I(bitset<32> inst, string asm_instr) {
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
    bitset<32> imm(ToBin(match.str()));
    imm<<=20;
    inst|=rd;
    inst|=rs1;
    inst|=imm;
    // cout<<inst<<endl;
    return inst;
}


bitset<32> U(bitset<32> inst, string asm_instr) {
    smatch match;
    regex pattern(R"(x([1-2]\d|3[01]|\d))");
    regex_search(asm_instr, match, pattern);
    bitset<32> rd(stoi(match.str().substr(1)));
    rd<<=7;
    asm_instr = match.suffix();
    regex pattern_imm(R"((0x[\dA-Fa-f]{1,8}|[1-9]\d*|0))");
    regex_search(asm_instr, match, pattern_imm);
    bitset<32> imm(ToBin(match.str()));
    cout << imm << endl;
    imm<<=12;
    inst|=rd;
    inst|=imm;
    // cout<<inst<<endl;
    return inst;
}

bitset<32> S(bitset<32> inst, string asm_instr) {
    smatch match;
    regex pattern(R"(x([1-2]\d|3[01]|\d))");
    regex_search(asm_instr, match, pattern);
    bitset<32> rs2(stoi(match.str().substr(1)));
    rs2<<=20;
    asm_instr = match.suffix();
    regex pattern_imm(R"((-?0x[\dA-Fa-f]{1,8}|-?[1-9]\d*|0))");
    regex_search(asm_instr, match, pattern_imm);
    bitset<32> imm(ToBin(match.str()));
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


bitset<32> mcode(string asm_inst){
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
        inst = S(inst, asm_inst);
        }
    else if (regex_match(asm_inst, sw)) {
        inst = bitset<32>("00000000000000000010000000100011");
        inst = S(inst, asm_inst);
        }
    else if (regex_match(asm_inst, sd)) {
        inst = bitset<32>("00000000000000000011000000100011");
        inst = S(inst, asm_inst);
        }
    else if (regex_match(asm_inst, sh)) {
        inst = bitset<32>("00000000000000000001000000100011");
        inst = S(inst, asm_inst);
        }
    else if (regex_match(asm_inst, lb)) {
        inst = bitset<32>("00000000000000000000000000000011");
        // inst = S(inst, asm_inst);
        }
    else if (regex_match(asm_inst, lw)) {
        inst = bitset<32>("00000000000000000010000000000011");
        }
    else if (regex_match(asm_inst, ld)) {
        inst = bitset<32>("00000000000000000011000000000011");
        }
    else if(regex_match(asm_inst,lh)) {
        inst = bitset<32>("0000000000000000000100000000011"); 
        }
    else if (regex_match(asm_inst, addi)) {
        inst = bitset<32>("0000000000000000000000000010011");
        inst = I(inst, asm_inst);
        }
    else if (regex_match(asm_inst, andi)) {
        inst = bitset<32>("00000000000000000111000000010011");
        inst = I(inst, asm_inst);
        }
    else if (regex_match(asm_inst, ori)) {
        inst = bitset<32>("00000000000000000110000000010011");
        inst = I(inst, asm_inst);
        }
    else if (regex_match(asm_inst, jalr)) {
        inst = bitset<32>("00000000000000000000000001100111");
        }
    else if (regex_match(asm_inst, bne)) {
        inst = bitset<32>("00000000000000000001000001100011");
        }
    else if (regex_match(asm_inst, beq)) {
        inst = bitset<32>("00000000000000000000000001100011");
        }
    else if (regex_match(asm_inst, bge)) {
        inst = bitset<32>("00000000000000000101000001100011");
        }
    else if (regex_match(asm_inst, blt)) {
        inst = bitset<32>("00000000000000000100000001100011");
        }
    else if (regex_match(asm_inst, lui)) {
        inst = bitset<32>("00000000000000000000000000110111");
        inst = U(inst, asm_inst);
        }
    else if (regex_match(asm_inst, auipc)) {
        inst = bitset<32>("00000000000000000000000000010111");
        inst = U(inst, asm_inst);
        }
    else if (regex_match(asm_inst, jal)) {
        inst = bitset<32>("00000000000000000000000001101111");
        }
    else {
        inst = bitset<32>(0);
        cout << "Error: Instruction not found/ Invalid instruction" << endl;
        }
    return inst;
}

int main() {
    ifstream file("assembly.s");     // file with the instructions
    ofstream outputFile("mc.txt");
    
    if (!file.is_open()) {
        cout << "Error opening file\n";
        return 0;
    }

    string line;
    bitset<32> mc(0);
    while (getline(file, line)) {
        // cout << line << endl;
        mc = mcode(line);
        outputFile << toHex(ic) << " " << BinToHex(mc) << endl;
        // cout << toHex(ic) << " " << hex<< mc.to_ullong() << endl;
        ic+=4;
    }
    
    outputFile.close();
    file.close();
}




