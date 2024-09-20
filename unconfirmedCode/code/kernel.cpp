//#include<stdio.h>
#define MEMORY_LENGTH 128
extern "C" {
    void constructTable();        // Initializes the scan code to ASCII lookup table
    void scans(char* buffer);     // Reads input into the buffer using scan codes
}

void intToStr(char* buff, int a);
void zeroinator(int *arr,int length){
    for(int i=0;i<length;i++){
        arr[i]=0;
    }
}
void setValue(int *arr, int start, int end, int value){
    for(int i=start;i<end;i++){
        arr[i] = value;
    }
}

void* mallocinator(int size){
    int index=0;
    int offset;
    int static mask[MEMORY_LENGTH/sizeof(1)];
    zeroinator(mask, MEMORY_LENGTH/sizeof(1)); // this line is wrong;
    int static data[MEMORY_LENGTH];
    int count =0;
    while(index!=MEMORY_LENGTH && count !=size){
        offset=(index+count)/sizeof(1);
        if(mask[offset]>>((index+count) - offset*sizeof(1))&1){
            index=index+count; 
            count=0;
        }
        else{
            count++;
        }
    }
    if (count == size){
        setValue(mask, index, index+count, 1);
        return &data + index;
    }
    else{
    return 0;
    }
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

void intToStr(char* string, int input){
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
}
