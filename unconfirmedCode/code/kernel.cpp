//#include<stdio.h>
#define MEMORY_LENGTH sizeof(1) * 1024
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

int mask[MEMORY_LENGTH/sizeof(1)];
int static data[MEMORY_LENGTH];
void setBit(int *arr, int pos, int value){
    arr[pos/sizeof(1)] |= 1<<pos%sizeof(1);
}

void* mallocinator(int size){
    int index=0;
    static int firstRun = 0;
    int offset;

    if (firstRun){
        zeroinator(mask, MEMORY_LENGTH/sizeof(1)); // this line is wrong;
        firstRun=1;
    }
    

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
        for (int i=index;i<=index+count;i++){
            setBit(mask, index, 1);
        }
        return &data + index;
    }
    else{
        return 0;
    }
}
void freeinator(void* base, int size){
    int maskBase = base - &data;
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
    char buff[128];
    int* a = (int*) mallocinator(20);

    for(int i=0;i<10;i++){
        a[i] = pow(i, 2);
        intToStr(buff, a[i]);
        print(buff);
        buff[0] = ' ';
        buff[1] = 0;
        print(buff);
    }
    // loadStr(buff, "hello world");
    // print(buff);
}
