#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // get a command line argument and make a key for cipher
    if (argc == 2) 
    {
        int key = atoi(argv[1]);
        key = key % 26;
        
        // encrypt given text by the key
        FILE* file = fopen("test.txt", "r");
        if(file == NULL)
        {
            return 1;
        }
        
        // get file size
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        // allocate and read file into memory block
        char* text = malloc(size * sizeof(char) + 1);
        fread(text, 1, size, file);
        
        // encryption
        for (int i = 0; i < size; i++)
        {
            if (text[i] >= 'a' && text[i] <= 'z') // lowercase letter
                if ((text[i] + key) > 122)
                    printf("%c", text[i] + key - 122 + 96);
                else
                    printf("%c", text[i] + key);
            else if (text[i] >= 'A' && text[i] <= 'Z') // uppercase letters
                if ((text[i] + key) > 90)
                    printf("%c", text[i] + key - 90 + 64);
                else
                    printf("%c", text[i] + key);
            else // non-alphabetical
                printf("%c", text[i]);
        }
        printf("\n");
     
        // housekeeping
        fclose(file);
        free(text);
        return 0;
    }
     
    // stops the program if !1 command line arg.
    else 
        printf("One command line argument, please!\n");
    return 1;
}

