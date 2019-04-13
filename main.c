#include <stdio.h>

char cipherRot(int k, int flag);

int main(void){
    int UI = 0;
    int k = 0; //key
    int flag = 0; //flag for encryption or decrpytion, used for introduction message printed in output file. 
       
    /*User interface: menu of options to run switch case function*/
    printf("\nAll input should be entered into 'input.txt' & all output will be sent to 'output.txt'\nEnter '1' for rotation encryption of a message, enter '2' for rotation decryption of a cipher: ");
    scanf("%d", &UI);
    
    /*User interface: calls encryption/decryption functions based on a list of options and user input*/
    switch(UI){
        //Call Rotation Encryption
        case 1:
        printf("\nRunning rotation encryption\nEnter rotation key: "); //allows for user input of desired rotation key
        scanf("%d", &k); 
        flag = 0;
        cipherRot(k, flag);
        break;
        
        //Call Rotation Decryption
        case 2:
        printf("\nRunning rotation decryption\nEnter rotation key: "); //allows for user input of desired rotation key
        scanf("%d", &k); 
        flag = 1;
        cipherRot(k, flag);
        break;
        
        default:
        printf("\nInvalid selection, please enter between 1 & 4" );
        
        break;
          
    }    

return 0;
}

/*Rotation encryption funciton definition*/
char cipherRot(int k, int flag){
    char c, eN; //c is character from message & eN is is the encrypted character
    int eLibU[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90}; //library of encryption values from A to Z
    int eLibL[] = {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122}; //library of encryption values from a to z
    int asc[1024]; //ascii array
    int i = 0, e;
    
    
    /*Open message file and output file*/
    FILE *input, *output;        //File points to input and output
    input = fopen("input.txt", "r");   //open file name and read format
    output = fopen("output.txt", "w");
    
    if(input == NULL) {         //Error message incase input file directory not found
        perror("fopen()");
    return 0;
    }
    if(output == NULL) {         //Error message incase output file directory not found
        perror("fopen()");
    return 0;
    }
    
    /*if & if else functions print text to output file for either an encryption or decryption senario based on the flag declared in switch case UI selection*/
    if(flag = 0){
        fprintf(output, "%s %s %d\n", "Key", "is:", k); //prints key value to output
        fprintf(output, "%s %s\n", "Encrypted", "Message: "); //prints message before encrypted text
    }
    else if(flag = 1){
        fprintf(output, "%s %s %d\n", "Key", "used:", k); //prints key value to output
        fprintf(output, "%s %s\n", "Decrypted", "Message: "); //prints message before encrypted text   
    }



    
    
     /*while loop scans input file for characters, prints them to terminal, 
     encrypts them with key value, writes this to an output, and loops until no characters are left in the input file*/   
    while(!feof(input)){ //loops until no characters are left in the input file
        fscanf(input,"%c", &c); //Scans file for characters and stores them as a variable c
         i++; //increments array pointer with every loop and assigns the input read ascii value to it, i.e. asc[0] = "first input character read from file"
        
        if(c >= 65 && c <= 90){  //if upper case
            
            asc[i] = c;     //assigns array at array point i with value c
            c = c - 65;     //A = 0
            e = c + k;  //encryption algorithm 
            if(e >= 26){     //if array pointer value is exceeded
                e = e - 26;    //starts array pointers over again plus difference between total value (>26) and max pointer value (26)    
              }
             eN = eLibU[e]; //selects encrypted value from upper case array
        }  
        
        else if(c >= 97 && c <= 122){  //if lower case 
            
            asc[i] = c;     //assigns array at array point i with value c
            c = c - 97;     //a = 0
            e = c + k;  //encryption algorithm 
            if(e >= 26){     //if array pointer value is exceeded
                e = e - 26;    //starts array pointers over again plus difference between total value (>26) and max pointer value (26)    
              }
             eN = eLibL[e]; //selects encrypted value from upper case array
        }   

        /*The following 3 'else if' statements leave common punctuation unmodified*/
        else if(c == 46){ //if full stop
            asc[i] = 46;  //sets ASCII value full stop
            eN = 46;  //sets ASCII value to full stop
        }
        
         else if(c == 44){ //if comma
            asc[i] = 44;  //sets ASCII value to comma
            eN = 44;  //sets ASCII value to comma
        }
        
        else if(c == 39){ //if apostrophe 
            asc[i] = 39;  //sets ASCII value to apostrophe
            eN = 39;  //sets ASCII value to apostrophe
        }  
          else if(c == 58){ //if colon
            asc[i] = 58;  //sets ASCII value to colon
            eN = 58;  //sets ASCII value to colon
        }  
               
        else if(c < 65 || (c >= 91 && c <= 96) || c > 122 ){ //excludes any ASCII value that isn't a letter
           
            asc[i] = 32;  //sets ASCII value to space
            eN = 32;  //sets ASCII value to space
        }   

        printf("%c %d encrypted: %d %c\n", asc[i], asc[i], eN, eN);
        
        fputc(eN, output); //prints encrypted message to output file
        
    }
        
    fclose(input); //closes input file
    fclose(output);
    
   return 0; 

}

