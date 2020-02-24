
#include <stdio.h>
#include <stdlib.h> // For error exit()

//Creates the formats to put the 32 bit strings into
typedef unsigned char byte; // declare "byte" to mean "unsigned char"

struct R_Format { byte rs, rt, rd, shamt, funct; };
struct I_Format { byte rs, rt; short immediate; };
struct J_Format { unsigned int address; };

//Structure for determining what format to use based on opcode
struct instruction {
	byte opcode;
	union {
		struct R_Format r_fmt;
		struct I_Format i_fmt;
		struct J_Format j_fmt;
	};
};


int main(void) {
	printf("CS350 Final Project for %s\n\n", "Kevin Cho");
	struct instruction data[100];//initializes structure
	int program_counter[100];//initializes program counter
	program_counter[0] = 305397760; 
	
	//This code checks for the file 
	printf("Loading data.txt\n");
	char *datafile_name = "data.txt";
	FILE *datafile = fopen(datafile_name, "r");
	if (!datafile) {
		printf("; open failed; program ends\n");
		exit(EXIT_FAILURE);
	}
	
	//This section counts the lines of data in the file
	int datalines=0;
    char c;
    while((c=fgetc(datafile))!=EOF){
        if (c=='\n') { datalines++; }
        }
    printf("Read %d lines of data\n", datalines);
    fclose(datafile);
   
    datafile = fopen(datafile_name, "r"); //reopens file to scan from top of data
	
	//Scans the data.txt for the hex values
	int eof_checker = 0;
	int instruction32bit;
    while (eof_checker < datalines){// This loop will scan until end of file
		fscanf(datafile,"%x \n", &instruction32bit);
		byte temp_opcode = (instruction32bit >> 26) & 0x000003F; //000003f is 111111 which is 6 bits for the mask
	    
	    //if and else to determine formats
        if (temp_opcode == 0x00){
            data[eof_checker].opcode = temp_opcode;
            data[eof_checker].r_fmt.rs = (instruction32bit >> 21) & 0x000001F; //mask for 5 bits
            data[eof_checker].r_fmt.rt = (instruction32bit >> 16) & 0x000001F;
            data[eof_checker].r_fmt.rd = (instruction32bit >> 11) & 0x000001F;
            data[eof_checker].r_fmt.shamt = (instruction32bit >> 6) & 0x000001F;
            data[eof_checker].r_fmt.funct = (instruction32bit) & 0x000003F; //mask for 6 bits
            }
            
        else if (temp_opcode <= 0x03){
            data[eof_checker].opcode = temp_opcode;
            data[eof_checker].j_fmt.address= (instruction32bit) & 0x3ffffff;//Mask for 26 bits 
        }
        else{
            data[eof_checker].opcode = temp_opcode;
            data[eof_checker].i_fmt.rs = (instruction32bit >> 21) & 0x000001F;
            data[eof_checker].i_fmt.rt = (instruction32bit >> 16) & 0x000001F;
            data[eof_checker].i_fmt.immediate = (instruction32bit) & 0x0000ffff; //mask for 16 bits 
        }
    program_counter[eof_checker + 1] = program_counter[eof_checker] + 0x00000004;
    eof_checker++;
	}
	
	fclose(datafile);
	
	//outputs the mips instruction based on the instructions in the formats
	int user_counter;
	printf("Enter program counter (just the hex digits no 0x or x in front):\n"); //asks users what location they what to display first
	scanf("%x", &user_counter);
	printf("\n");
	printf("Location      Instruction\n");
	for(eof_checker = 0; eof_checker < datalines; eof_checker++){
	    if(user_counter - program_counter[eof_checker] == 0x00){//checks if user input matches an existing location
    	    printf("x%x     ", program_counter[eof_checker]);
    	    user_counter = user_counter +0x00000004; //increments user_counter with the program counter to print until end of data
    	    
    	    //switch for r-format
    	    if (data[eof_checker].opcode == 0){
    	        if(data[eof_checker].r_fmt.funct == 0x00){//This is for the special cases of nop and sll
    	            switch(data[eof_checker].r_fmt.shamt){
    	                case 0x00:
    	                    printf("nop     ");
    	                    break;
    	               default:
    	                    printf("sll     ");
    	                    break;
    	            }
    	            switch(data[eof_checker].r_fmt.rd){
    	            case(0x00):
    	                printf("$0,  ");
                        break;
    	            case(0x01):
    	                printf("$at, ");
                        break;
                    case(0x02):
    	                printf("$v0, ");
                        break;
                    case(0x03):
    	                printf("$v1, ");
                        break;
                    case(0x04):
    	                printf("$a,  ");
                        break;
                    case(0x05):
    	                printf("$a1, ");
                        break;
                    case(0x06):
    	                printf("$a2, ");
                        break;
                    case(0x07):
    	                printf("$a3, ");
                        break;
                    case(0x08):
    	                printf("$t0, ");
                        break;
                    case(0x09):
    	                printf("$t1, ");
                        break;
                    case(0x0a):
    	                printf("$t2, ");
                        break;
                    case(0x0b):
    	                printf("$t3, ");
                        break;
                    case(0x0c):
    	                printf("$t4, ");
                        break;
                    case(0x0d):
    	                printf("$t5, ");
                        break;
                    case(0x0e):
    	                printf("$t6, ");
                        break;
                    case(0x0f):
    	                printf("$t7, ");
                        break;
                    case(0x10):
    	                printf("$s0, ");
                        break;
                    case(0x11):
    	                printf("$s1, ");
                        break;
                    case(0x12):
    	                printf("$s2, ");
                        break;
                    case(0x13):
    	                printf("$s3, ");
                        break;
                    case(0x14):
    	                printf("$s4, ");
                        break;
                    case(0x15):
    	                printf("$s5, ");
                        break;
                    case(0x16):
    	                printf("$s6, ");
                        break;
                    case(0x17):
    	                printf("$s7, ");
                        break;
                    case(0x18):
    	                printf("$t8, ");
                        break;
                    case(0x19):
    	                printf("$t9, ");
                        break;
                    case(0x1a):
    	                printf("$k0, ");
                        break;
                    case(0x1b):
    	                printf("$k1, ");
                        break;
                    case(0x1c):
    	                printf("$gp, ");
                        break;
                    case(0x1d):
    	                printf("$sp, ");
                        break;
                    case(0x1e):
    	                printf("$fp, ");
                        break;
                    case(0x1f):
    	                printf("$ra, ");
                        break;
                    default:
    	                printf("ERROR, ");
                    
    	        }
    	            switch(data[eof_checker].r_fmt.rt){
    	            case(0x00):
    	                printf("$0,  ");
                        break;
    	            case(0x01):
    	                printf("$at, ");
                        break;
                    case(0x02):
    	                printf("$v0, ");
                        break;
                    case(0x03):
    	                printf("$v1, ");
                        break;
                    case(0x04):
    	                printf("$a,  ");
                        break;
                    case(0x05):
    	                printf("$a1, ");
                        break;
                    case(0x06):
    	                printf("$a2, ");
                        break;
                    case(0x07):
    	                printf("$a3, ");
                        break;
                    case(0x08):
    	                printf("$t0, ");
                        break;
                    case(0x09):
    	                printf("$t1, ");
                        break;
                    case(0x0a):
    	                printf("$t2, ");
                        break;
                    case(0x0b):
    	                printf("$t3, ");
                        break;
                    case(0x0c):
    	                printf("$t4, ");
                        break;
                    case(0x0d):
    	                printf("$t5, ");
                        break;
                    case(0x0e):
    	                printf("$t6, ");
                        break;
                    case(0x0f):
    	                printf("$t7, ");
                        break;
                    case(0x10):
    	                printf("$s0, ");
                        break;
                    case(0x11):
    	                printf("$s1, ");
                        break;
                    case(0x12):
    	                printf("$s2, ");
                        break;
                    case(0x13):
    	                printf("$s3, ");
                        break;
                    case(0x14):
    	                printf("$s4, ");
                        break;
                    case(0x15):
    	                printf("$s5, ");
                        break;
                    case(0x16):
    	                printf("$s6, ");
                        break;
                    case(0x17):
    	                printf("$s7, ");
                        break;
                    case(0x18):
    	                printf("$t8, ");
                        break;
                    case(0x19):
    	                printf("$t9, ");
                        break;
                    case(0x1a):
    	                printf("$k0, ");
                        break;
                    case(0x1b):
    	                printf("$k1, ");
                        break;
                    case(0x1c):
    	                printf("$gp, ");
                        break;
                    case(0x1d):
    	                printf("$sp, ");
                        break;
                    case(0x1e):
    	                printf("$fp, ");
                        break;
                    case(0x1f):
    	                printf("$ra, ");
                        break;
                    default:
    	                printf("ERROR, ");
                    
    	        }
    	            printf("%d   (rs/f: x%02x x%02x = dec %d, %d)\n", data[eof_checker].r_fmt.shamt, data[eof_checker].r_fmt.rs, data[eof_checker].r_fmt.funct, data[eof_checker].r_fmt.rs, data[eof_checker].r_fmt.funct );
    	            
    	        }
    	        else{//normal cases of r-format
        	        switch(data[eof_checker].r_fmt.funct) {
                        case 0x08:
                            printf("jr      ");
                            break;
                        case 0x18:
                            printf("mult    ");
                            break;
                        case 0x1a:
                            printf("div     ");
                            break;
                        case 0x20:
                            printf("add     ");
                            break;
                        case 0x22:
                            printf("sub     ");
                            break;
                        case 0x24:
                            printf("and     ");
                            break;
                        case 0x25:
                            printf("or      ");
                            break;
                        case 0x27:
                            printf("nor     ");
                            break;
                        case 0x26:
                            printf("xor     ");
                            break;
                        case 0x2a:
                            printf("slt     ");
                            break;
                        default :
                            printf("broken  ");
        	        }
        	        switch(data[eof_checker].r_fmt.rd){
        	            case(0x00):
        	                printf("$0,  ");
                            break;
        	            case(0x01):
        	                printf("$at, ");
                            break;
                        case(0x02):
        	                printf("$v0, ");
                            break;
                        case(0x03):
        	                printf("$v1, ");
                            break;
                        case(0x04):
        	                printf("$a,  ");
                            break;
                        case(0x05):
        	                printf("$a1, ");
                            break;
                        case(0x06):
        	                printf("$a2, ");
                            break;
                        case(0x07):
        	                printf("$a3, ");
                            break;
                        case(0x08):
        	                printf("$t0, ");
                            break;
                        case(0x09):
        	                printf("$t1, ");
                            break;
                        case(0x0a):
        	                printf("$t2, ");
                            break;
                        case(0x0b):
        	                printf("$t3, ");
                            break;
                        case(0x0c):
        	                printf("$t4, ");
                            break;
                        case(0x0d):
        	                printf("$t5, ");
                            break;
                        case(0x0e):
        	                printf("$t6, ");
                            break;
                        case(0x0f):
        	                printf("$t7, ");
                            break;
                        case(0x10):
        	                printf("$s0, ");
                            break;
                        case(0x11):
        	                printf("$s1, ");
                            break;
                        case(0x12):
        	                printf("$s2, ");
                            break;
                        case(0x13):
        	                printf("$s3, ");
                            break;
                        case(0x14):
        	                printf("$s4, ");
                            break;
                        case(0x15):
        	                printf("$s5, ");
                            break;
                        case(0x16):
        	                printf("$s6, ");
                            break;
                        case(0x17):
        	                printf("$s7, ");
                            break;
                        case(0x18):
        	                printf("$t8, ");
                            break;
                        case(0x19):
        	                printf("$t9, ");
                            break;
                        case(0x1a):
        	                printf("$k0, ");
                            break;
                        case(0x1b):
        	                printf("$k1, ");
                            break;
                        case(0x1c):
        	                printf("$gp, ");
                            break;
                        case(0x1d):
        	                printf("$sp, ");
                            break;
                        case(0x1e):
        	                printf("$fp, ");
                            break;
                        case(0x1f):
        	                printf("$ra, ");
                            break;
                        default:
        	                printf("ERROR, ");
                        
        	        }
        	        switch(data[eof_checker].r_fmt.rs){
        	            case(0x00):
        	                printf("$0,  ");
                            break;
        	            case(0x01):
        	                printf("$at, ");
                            break;
                        case(0x02):
        	                printf("$v0, ");
                            break;
                        case(0x03):
        	                printf("$v1, ");
                            break;
                        case(0x04):
        	                printf("$a,  ");
                            break;
                        case(0x05):
        	                printf("$a1, ");
                            break;
                        case(0x06):
        	                printf("$a2, ");
                            break;
                        case(0x07):
        	                printf("$a3, ");
                            break;
                        case(0x08):
        	                printf("$t0, ");
                            break;
                        case(0x09):
        	                printf("$t1, ");
                            break;
                        case(0x0a):
        	                printf("$t2, ");
                            break;
                        case(0x0b):
        	                printf("$t3, ");
                            break;
                        case(0x0c):
        	                printf("$t4, ");
                            break;
                        case(0x0d):
        	                printf("$t5, ");
                            break;
                        case(0x0e):
        	                printf("$t6, ");
                            break;
                        case(0x0f):
        	                printf("$t7, ");
                            break;
                        case(0x10):
        	                printf("$s0, ");
                            break;
                        case(0x11):
        	                printf("$s1, ");
                            break;
                        case(0x12):
        	                printf("$s2, ");
                            break;
                        case(0x13):
        	                printf("$s3, ");
                            break;
                        case(0x14):
        	                printf("$s4, ");
                            break;
                        case(0x15):
        	                printf("$s5, ");
                            break;
                        case(0x16):
        	                printf("$s6, ");
                            break;
                        case(0x17):
        	                printf("$s7, ");
                            break;
                        case(0x18):
        	                printf("$t8, ");
                            break;
                        case(0x19):
        	                printf("$t9, ");
                            break;
                        case(0x1a):
        	                printf("$k0, ");
                            break;
                        case(0x1b):
        	                printf("$k1, ");
                            break;
                        case(0x1c):
        	                printf("$gp, ");
                            break;
                        case(0x1d):
        	                printf("$sp, ");
                            break;
                        case(0x1e):
        	                printf("$fp, ");
                            break;
                        case(0x1f):
        	                printf("$ra, ");
                            break;
                        default:
        	                printf("ERROR, ");
                        
        	        }
        	        switch(data[eof_checker].r_fmt.rt){
        	            case(0x00):
        	                printf("$0 ");
                            break;
        	            case(0x01):
        	                printf("$at ");
                            break;
                        case(0x02):
        	                printf("$v0 ");
                            break;
                        case(0x03):
        	                printf("$v1 ");
                            break;
                        case(0x04):
        	                printf("$a  ");
                            break;
                        case(0x05):
        	                printf("$a1 ");
                            break;
                        case(0x06):
        	                printf("$a2 ");
                            break;
                        case(0x07):
        	                printf("$a3 ");
                            break;
                        case(0x08):
        	                printf("$t0 ");
                            break;
                        case(0x09):
        	                printf("$t1 ");
                            break;
                        case(0x0a):
        	                printf("$t2 ");
                            break;
                        case(0x0b):
        	                printf("$t3 ");
                            break;
                        case(0x0c):
        	                printf("$t4 ");
                            break;
                        case(0x0d):
        	                printf("$t5 ");
                            break;
                        case(0x0e):
        	                printf("$t6 ");
                            break;
                        case(0x0f):
        	                printf("$t7 ");
                            break;
                        case(0x10):
        	                printf("$s0 ");
                            break;
                        case(0x11):
        	                printf("$s1 ");
                            break;
                        case(0x12):
        	                printf("$s2 ");
                            break;
                        case(0x13):
        	                printf("$s3 ");
                            break;
                        case(0x14):
        	                printf("$s4 ");
                            break;
                        case(0x15):
        	                printf("$s5 ");
                            break;
                        case(0x16):
        	                printf("$s6 ");
                            break;
                        case(0x17):
        	                printf("$s7 ");
                            break;
                        case(0x18):
        	                printf("$t8 ");
                            break;
                        case(0x19):
        	                printf("$t9 ");
                            break;
                        case(0x1a):
        	                printf("$k0 ");
                            break;
                        case(0x1b):
        	                printf("$k1 ");
                            break;
                        case(0x1c):
        	                printf("$gp ");
                            break;
                        case(0x1d):
        	                printf("$sp ");
                            break;
                        case(0x1e):
        	                printf("$fp ");
                            break;
                        case(0x1f):
        	                printf("$ra ");
                            break;
                        default:
        	                printf("ERROR ");
                        
        	        }
        	        printf("(s/f: x%02x x%02x = dec %d, %d)\n", data[eof_checker].r_fmt.shamt, data[eof_checker].r_fmt.funct, data[eof_checker].r_fmt.shamt, data[eof_checker].r_fmt.funct );
    	        }
    	    }
    	    //switch for j-format
    	    else if (data[eof_checker].opcode <= 0x03){
    	        switch(data[eof_checker].opcode){
    	            case(0x02):
    	                printf("j       x%07x\n", data[eof_checker].j_fmt.address);
                        break;
    	            default:
    	                printf("jal     x%07x\n", data[eof_checker].j_fmt.address);
                        break;
    	        }
    	   }
    	    //switch for i-format
    	    else{
    	        switch(data[eof_checker].opcode){
    	            case(0x04):
    	                printf("beq     ");
                        break;
    	            case(0x05):
    	                printf("bne     ");
                        break;
                    case(0x08):
    	                printf("addi    ");
                        break;
                    case(0x0a):
    	                printf("slti    ");
                        break;
                    case(0x0c):
    	                printf("andi    ");
                        break;
                    case(0x0d):
    	                printf("ori     ");
                        break;
                    case(0x0e):
    	                printf("xori    ");
                        break;
                    case(0x0f):
    	                printf("lui     ");
                        break;
                    case(0x23):
    	                printf("lw      ");
                        break;
                    case(0x2b):
    	                printf("sw      ");
                        break;
                    default:
                        printf("Broken ");
                        break;
    	        }
    	        switch(data[eof_checker].i_fmt.rs){
    	            case(0x00):
    	                printf("$0,  ");
                        break;
    	            case(0x01):
    	                printf("$at, ");
                        break;
                    case(0x02):
    	                printf("$v0, ");
                        break;
                    case(0x03):
    	                printf("$v1, ");
                        break;
                    case(0x04):
    	                printf("$a,  ");
                        break;
                    case(0x05):
    	                printf("$a1, ");
                        break;
                    case(0x06):
    	                printf("$a2, ");
                        break;
                    case(0x07):
    	                printf("$a3, ");
                        break;
                    case(0x08):
    	                printf("$t0, ");
                        break;
                    case(0x09):
    	                printf("$t1, ");
                        break;
                    case(0x0a):
    	                printf("$t2, ");
                        break;
                    case(0x0b):
    	                printf("$t3, ");
                        break;
                    case(0x0c):
    	                printf("$t4, ");
                        break;
                    case(0x0d):
    	                printf("$t5, ");
                        break;
                    case(0x0e):
    	                printf("$t6, ");
                        break;
                    case(0x0f):
    	                printf("$t7, ");
                        break;
                    case(0x10):
    	                printf("$s0, ");
                        break;
                    case(0x11):
    	                printf("$s1, ");
                        break;
                    case(0x12):
    	                printf("$s2, ");
                        break;
                    case(0x13):
    	                printf("$s3, ");
                        break;
                    case(0x14):
    	                printf("$s4, ");
                        break;
                    case(0x15):
    	                printf("$s5, ");
                        break;
                    case(0x16):
    	                printf("$s6, ");
                        break;
                    case(0x17):
    	                printf("$s7, ");
                        break;
                    case(0x18):
    	                printf("$t8, ");
                        break;
                    case(0x19):
    	                printf("$t9, ");
                        break;
                    case(0x1a):
    	                printf("$k0, ");
                        break;
                    case(0x1b):
    	                printf("$k1, ");
                        break;
                    case(0x1c):
    	                printf("$gp, ");
                        break;
                    case(0x1d):
    	                printf("$sp, ");
                        break;
                    case(0x1e):
    	                printf("$fp, ");
                        break;
                    case(0x1f):
    	                printf("$ra, ");
                        break;
                    default:
    	                printf("ERROR, ");
                    
    	        }
    	        switch(data[eof_checker].i_fmt.rt){
    	            case(0x00):
    	                printf("$0,  ");
                        break;
    	            case(0x01):
    	                printf("$at, ");
                        break;
                    case(0x02):
    	                printf("$v0, ");
                        break;
                    case(0x03):
    	                printf("$v1, ");
                        break;
                    case(0x04):
    	                printf("$a,  ");
                        break;
                    case(0x05):
    	                printf("$a1, ");
                        break;
                    case(0x06):
    	                printf("$a2, ");
                        break;
                    case(0x07):
    	                printf("$a3, ");
                        break;
                    case(0x08):
    	                printf("$t0, ");
                        break;
                    case(0x09):
    	                printf("$t1, ");
                        break;
                    case(0x0a):
    	                printf("$t2, ");
                        break;
                    case(0x0b):
    	                printf("$t3, ");
                        break;
                    case(0x0c):
    	                printf("$t4, ");
                        break;
                    case(0x0d):
    	                printf("$t5, ");
                        break;
                    case(0x0e):
    	                printf("$t6, ");
                        break;
                    case(0x0f):
    	                printf("$t7, ");
                        break;
                    case(0x10):
    	                printf("$s0, ");
                        break;
                    case(0x11):
    	                printf("$s1, ");
                        break;
                    case(0x12):
    	                printf("$s2, ");
                        break;
                    case(0x13):
    	                printf("$s3, ");
                        break;
                    case(0x14):
    	                printf("$s4, ");
                        break;
                    case(0x15):
    	                printf("$s5, ");
                        break;
                    case(0x16):
    	                printf("$s6, ");
                        break;
                    case(0x17):
    	                printf("$s7, ");
                        break;
                    case(0x18):
    	                printf("$t8, ");
                        break;
                    case(0x19):
    	                printf("$t9, ");
                        break;
                    case(0x1a):
    	                printf("$k0, ");
                        break;
                    case(0x1b):
    	                printf("$k1, ");
                        break;
                    case(0x1c):
    	                printf("$gp, ");
                        break;
                    case(0x1d):
    	                printf("$sp, ");
                        break;
                    case(0x1e):
    	                printf("$fp, ");
                        break;
                    case(0x1f):
    	                printf("$ra, ");
                        break;
                    default:
    	                printf("ERROR, ");
                    
    	        }
    	        if (data[eof_checker].opcode <= 0x05){//this if statement is for the output:target address of beq and bne
    	        printf("x%04x   : dec %d   target= x%x \n", data[eof_checker].i_fmt.immediate & 0x000ffff, data[eof_checker].i_fmt.immediate, (program_counter[eof_checker+1] + data[eof_checker].i_fmt.immediate*4));
    	    }
    	            else{
    	                printf("x%04x   : dec %d \n", data[eof_checker].i_fmt.immediate & 0x000ffff, data[eof_checker].i_fmt.immediate);
    	                }
    	        }
	    }

	    else if(eof_checker == datalines-1){
	        printf("ERROR: No matching location\n");
	   }
	}

	
    printf("\n");
	printf("End of program\n");
	system("pause"); //Allows user to read output
}
	




