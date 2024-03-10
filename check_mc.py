def mcode(mc_file):
    insts = []
    with open(mc_file, 'r') as mc_file:
        start = False
        for line in mc_file:
            if not start:
                if line.strip() == "":
                    start = True
                continue
            if line.strip():
                adr, inst = line.strip().split()
                insts.append(str(inst))
    return insts

def compare(mc_insts, dumped_file):
    wrong = []
    i = 0
    success = True
    with open(dumped_file, 'r') as dumped_file:
        for line in dumped_file:
            if str(line.strip().lower()) != mc_insts[i].lower():
                print(f"M Code: {mc_insts[i].upper()} Dumped: {line.upper()}")
                success = False
            i += 1
    return success

mc_insts = mcode("output.mc")
if compare(mc_insts, "dump.txt") : print("All Good!")
