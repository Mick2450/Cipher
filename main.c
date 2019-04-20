#include <stdio.h>
#include <string.h>

char cipherRot(int k, int flag); //rotation cipher function prototype
char cipherSub(int flag, char userKey[26]);


int main(void){
    int UI = 0;
    int k = 0, i = 0; //rotation key
    int flag = 0; //flag for encryption or decrpytion, used for introduction message printed in output file.
    char userKey[26] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90};
       
    /*User interface: menu of options to run switch case function*/
    printf("\nAll input should be entered into 'input.txt' & all output will be sent to 'output.txt'\nEnter '1' for rotation encryption of a message, enter '2' for rotation decryption of a cipher, enter '3' for substitution decryption of cipher,  enter '4' for substitution encryption of cipher: ");
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
        
        //Call Substitution Decryption
        case 3:
        printf("\nRunning substitution decryption"); 
        flag = 0;
        cipherSub(flag, userKey);
        break;
        
        //Call Substitution Encryption
        case 4:
        printf("\nRunning substitution decryption\n");
        for(i = 0; i <= 25; i++){
           
           printf("Enter rotation key to correspond with alphabetical order (enter '0' to stop entering key): ");
           while(scanf("%d") != 0){ //trying to add exit ability
                scanf("%c", &userKey[i]); 
            }
        }
    
        flag = 1;
        cipherSub(flag, userKey);
        break;
        
        default:
        printf("\nInvalid selection, please enter between 1 & 4" );
        break;
          
    }    

return 0;
}



/*----------------Rotation encryption/decryption function definition ------------------*/
char cipherRot(int k, int flag){
    char c, eN; //c is character from message & eN is is the encrypted character
    int eLibU[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90}; //library of encryption values from A to Z
    int eLibL[] = {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122}; //library of encryption values from a to z
    int decr[26];
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
/*----------------END of Rotation encryption/decryption function definition ------------------*/


/*----------------START of Subsitution encryption/decryption function definition ------------------*/
char cipherSub(int flag, char userKey[26]){
        char c = 0, eN = 0, eNFinal = 0; //c is character from message & eN is is the encrypted character
    int eLibU[] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90}; //library of encryption values from A to Z
    int asc[1024] = {0}; //ascii array
    int i = 0, e = 0, count = 0, j = 0;
    int freq[1000] = {0};
    char array[1024] = {0};
    int max = 0, maxLoc, loc;
    int decrypted[1024] = {0}; // array used to store decrypted message
    int key[26] = {0}; //key  
    int k = 0, arr = 0, alph = 0, location = 0;
    int AlphFreq[] = {69, 84, 65, 79, 73, 78, 83, 72, 82, 68, 76, 85, 67, 77, 87, 70, 71, 89, 80, 66, 86, 75, 74, 88, 81, 90}; //array with descending order of charcter frequency in Ennglish alphabet
    char original[1024] = {0};
    int decryptLoc[1024] = {0};
    
      
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
    
   
        
     /*----while loop scans input file for characters, prints them to terminal, 
     encrypts them with key value, writes this to an output, and loops until no characters are left in the input file*/   
     while(!feof(input)){ //loops until no characters are left in the input file
        fscanf(input,"%c", &c); //Scans file for characters and stores them as a variable c
         i++; //increments array pointer with every loop and assigns the input read ascii value to it, i.e. asc[0] = "first input character read from file"
       
       if(c >= 65 && c <= 90){  //if upper case
            
            asc[i] = c;     //assigns array at array point i with value c
            c = c - 65;     //A = 0
            e = c; //encryption algorithm 
            if(e >= 26){     //if array pointer value is exceeded
                e = e - 26;    //starts array pointers over again plus difference between total value (>26) and max pointer value (26)    
              }
             eN = eLibU[e]; //selects encrypted value from upper case array
             array[i] = eN;
             freq[i] = -1;
        }  
        
        else if(c >= 97 && c <= 122){  //if lower case 
            
            asc[i] = c;     //assigns array at array point i with value c
            c = c - 32;     //a = 0
            e = c - 65; //encryption algorithm 
            if(e >= 26){     //if array pointer value is exceeded
                e = e - 26;    //starts array pointers over again plus difference between total value (>26) and max pointer value (26)    
              }
             eN = eLibU[e]; //selects ascii value from upper case array
             array[i] = eN; //stores selected ascii value in an array
             freq[i] = -1;  //Initialise frequency to -1
        }   

        /*The following 3 'else if' statements leave common punctuation unmodified*/
        else if(c == 46){ //if full stop
            asc[i] = 46;  //sets ASCII value full stop
            eN = 46;  //sets ASCII value to full stop
        }
        else if(c == 63){ //if question mark
            asc[i] = 63;  //sets ASCII value full stop
            eN = 63;  //sets ASCII value to full stop
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
        original[i-1] = eN;
    
    }
/*----------------------------END of input reading While loop----------------------*/
      
   /*------Determines frequency of character occurrence from input text for statistical analysis------*/   

    for(i=0; i <= 1024; i++){
      
        count = 1;
        for(j=i+1; j <= 1024 ; j++){
            if(array[i]==array[j]){
                count++;
                freq[j] = 0;
            }
        }

        if(freq[i] != 0){
            freq[i] = count;
        }
    }




    /*------------------------------------------------------------------------*/
   
    /*------------------Orders characters in an array (array[i]) in descending frequency of occurence----------------------------*/

    for (i=0; i<=1024; ++i){    
        for (j=i+1; j<=1024; ++j){
            if (freq[i] < freq[j]){
                int tmp = freq[i];
                freq[i] = freq[j];
                freq[j] = tmp;
                
                int tmp2 = array[i];
                array[i] = array[j];
                array[j] = tmp2;
            }
        }
    }



    printf ("\nDescending order of letter frequency"); 
    for (i=0; i<strlen(array); i++){
        if(freq[i] != 0 && array[i] >= 65 && array[i] <= 90){
            printf ("\n%c occurs %d times", array[i], freq[i]); //array[i] is now ordered in terms of frequency of letter occurence from input text
        }
        
    }
    
    
    //printf("\n%c\n", array[22]); //array[0] is the most commonly occuring letter, can test if array is working here
 /*------------------------------------------------------------------------*/

 /*-----Creation of key for each alphabet by comparing frequency of input text character occurrence with frequency of character occurrence in the english language------------------*/
    if(flag = 0){
       
    for(i=0; i<strlen(array); i++){
        if(freq[i] != 0 && array[i] >=65 && array[i] <=90){
        
        arr = array[i];
        alph = AlphFreq[i];
        location = arr - 65;
        
        key[location] = alph - arr;
        if(key[location] >= 26){     //if array pointer value is exceeded
            key[location] = key[location] - 26;    //starts array pointers over again plus difference between total value (>26) and max pointer value (26)    
        }
        printf("\n%c is rotated %d", arr, key[location]); //prints key based on statistical analysis
        }
    }
}   
    if(flag = 1){
        key[26] = userKey[26];
        
    }

 /*------------------------------------------------------------------------*/
  
/*--------------Decryption/Encryption of input Based on statistical analysis------------------*/
    for(i=0; i<strlen(original); i++){
            
            location = original[i] - 65;
            k = key[location];
            decrypted[i] = original[i] + k;
            e = decrypted[i];         
            
             if(e >= 90){     //if array pointer value is exceeded
                e = e - 65;    //starts array pointers over again plus difference between total value (>26) and max pointer value (26)    
              }
               if(original[i] == 44){
                  e = 44;
              }
              
              if(original[i] == 32){
                  e = 32;
              }
              if(original[i] == 39){
                  e = 39;
              }
               if(original[i] == 46){
                  e = 46;
              }
                if(original[i] == 63){
                  e = 63;
              }
             
            eNFinal = e;
            
       
            printf("\n%c (%d) is %c (%d)", original[i], original[i], eNFinal, eNFinal);
            fputc(eNFinal, output); //prints encrypted message to output file
   
    }   
 /*------------------------------------------------------------------------*/
        
    fclose(input); //closes input file
    fclose(output); //closes output file
    
    return 0;     
}
   
/*----------------END of Subsitution encryption/decryption function definition ------------------*/
