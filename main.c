#include <stdio.h>

int Encryption(void);
//int Decryption(void);

int main(){
    int select = 0;
    
    printf("Enter '1' for message rotation encryption: \n");
    scanf("%d", &select);
    printf("Enter '2' for cipher rotation decryption: \n");
    scanf("%d", &select);
    
    
    
    switch(select){
        case 1:
        Encryption();
        break;
        /*case 2:
        return Decryption(void);
        break;*/
        
        
        
        
    }
    
    void Encryption(void){

    char c, eN; //c is character from message & eN is is the encrypted character
    int eLib[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90}; //library of encryption values from A to Z
    int asc[1024];
    int i , e;
    int k = 5;  //key
    
    //Open message file
    FILE *input, *output;        //File points to input and output
    input = fopen("Task 1 message input", "r");   //open file name and read format
    output = fopen("Task 1 cipher output", "w");
    
    if(input == NULL) {         //Error message incase input file directory not found
        perror("fopen()");
    return 0;
    }
    if(output == NULL) {         //Error message incase output file directory not found
        perror("fopen()");
    return 0;
    }
    
       
    for(i = 0; i <= 15; i++){ // incrementing array pointer
        
        /*Scans file for characters and stores them as a variable c*/
        fscanf(input,"%c", &c); 
        if(c >= 65 && c <= 90){  // upper case
            asc[i] = c;     //assigns array at array point i with value c
            c = c - 65;     //A = 0
            e = c + k;  //encryption algorithm 
            if(e > 26){     //if array pointer value is exceeded
                e = e - 26;    //starts array pointers over again plus difference between total value (>26) and max pointer value (26)    
              }
             eN = eLib[e]; //selects encrypted value from array
        }   

        else if(c >= 97 && c <=122){  //lower case
            asc[i] = c - 32;  //
            c = c - 97; 
            e = c + k;
            if(e > 26){     //if array pointer value is exceeded
                e = e - 26;     //starts array pointers over again plus difference between total value (>26) and max pointer value (26)    
            }
        eN = eLib[e];  //selects encrypted value from array 

        }           
        
        
        else if(c < 65 || (c >= 91 && c <= 96) || c > 122 ){ //excludes any ASCII value that isn't a letter
            asc[i] = 32;  //sets ASCII value to space
            eN = 32;  //sets ASCII value to space
        }   

        printf("%c encrypted: %c\n", asc[i], eN);
        
        fputc(eN, output); //prints encrypted message to output file
    }
    
    fclose(input); //closes input file
    fclose(output);
    
   return 0; 

}
}
