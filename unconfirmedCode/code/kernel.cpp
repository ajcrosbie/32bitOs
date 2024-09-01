//#include<stdio.h>

extern "C" {
    void constructTable();        // Initializes the scan code to ASCII lookup table
    void scans(char* buffer);     // Reads input into the buffer using scan codes
}

int calcSquare(int x){
    return x*x;
}

int numeric(char a){
    return (a<='9'&&'0'<=a);
}

int div (int a, int b){
    int i=0;
    while (a>=b){
        i++;
        a -=b;
    }
    return i;
}

int strToInt(char* str){
    int x = 0;
    unsigned i=0;
    
    while (numeric(str[i])){
        x*=10;
        x+=(int)str[i] - 48;
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
    while (a>=pow(10,x)){
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
    int i=0;
    while (string[i] != '\0'){
        vmem[i*2] = string[i];// when trying this on the linux system it will segfault as programs aren't allowed to access vmem directly
        vmem[i*2+1] = 0x07;
        i++;
    }
}

extern "C" int main(){
    char buff[128];
    buff[10] = 0;
    // print("hello world");
    constructTable();
    scans(buff);
    
    print(buff);
}