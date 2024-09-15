//#include<stdio.h>

extern "C" {
    void constructTable();        // Initializes the scan code to ASCII lookup table
    void scans(char* buffer);     // Reads input into the buffer using scan codes
    void* malocator(); 
}




int numeric(char a){
    return (a<='9'&&'0'<=a);
}


int strToInt(char* str){
    int x = 0;
    unsigned i=0;
    
    while (numeric(str[i])){
        x*=10;
        x+=(int) str[i] - '0';
        i++;
    }
    return x;
}

int pow(int a, int b){
    int x=1;
    while(b>0){
        x*=a;
        b--;
    }
    return x;
}

int calcSpace(int a){
    int x=1;
    while (a>=10){
        a/=10;
        x+=1;
    }
    return x;
}

void loadStr(char* string, char* num){
    unsigned i=0;
    while (num[i] !='\0'){
        string[i] = num[i];
        i++;
    }
}

void print(char* string){
    char* vmem = (char*)0xb8000;
    static int i=0;
    int itter=0;
    while (string[itter] != '\0'){
        vmem[i*2] = string[itter];
        // when trying this on the linux system it wil segfault as 
        // programs aren't alowed to access vmem directly
        vmem[i*2+1] = 0x07;
        i++;
        itter++;
    }
}

void toStr(char* string, int input){
    int i=0;
    int divVal, mod, exp;
    int space = calcSpace(input);
    while (i!=space){
        exp = pow(10,space-i-1);
        divVal = input/exp;
        input = input - divVal * exp;
        
        string[i] = (char) (divVal+'0');
        i++;
    }
    string[i] = 0;
}


extern "C" int main(){
    char buff[128];
    constructTable();
    scans(buff);
    print(buff);
    print(" squared is ");
    int usrInt = strToInt(buff);
    int value = usrInt*usrInt;
    toStr(buff,value);
    print(buff);
}
