#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>

#include "symbols.h"


int8_t get_num(char*array, uint8_t size,char x)
{
    for (uint8_t i=0;i<size;i++)
    {
        if (array[i]==x)
        {
            return  i;
        }
    }
    return -1;
}

uint8_t*  convert_str (char*str)
{
    uint8_t* sequence = calloc(1,sizeof (uint8_t));
    uint8_t j =0;
    for (int16_t i=0; i<LenghtInSym*2-1;i++)
    {
        sequence = (uint8_t*)realloc(sequence,sizeof (uint8_t)*(j+1));
        sequence[j] = get_num(symbols,SIZE,str[i]);
        sequence[j+1] = get_num(symbols,SIZE,str[i+1]);
        //printf("S:%d \n",sequence[j]);
        if  (sequence[j+1]>=95 && sequence[j+1]!=255&& sequence[j]==255)
            continue;
        if  (sequence[j]==255&&sequence[j+1]==255)
            continue;
        if  (sequence[j]==255)
            sequence[j]=0;
        //printf("!%d %d\n",j,sequence[j]);
        j++;
    }
    sequence[j] = 159;

    return sequence;
}

uint8_t get_size_arr (uint8_t* array)
{
    uint8_t i =0;
    while(array[i]!=159)
        i++;
    return i;
}

void print_display(uint8_t* display[])
{
    for (uint8_t i=0; i<HeightInPixel;i++)
    {
        for(uint8_t j=0;j<LenghtInPixels;j++)
            printf("%d",display[i][j]);
        printf("\n");
    }
}

uint8_t** create_text(uint8_t** display,uint8_t str_num,  char*str)
{
    uint8_t offsetY, offsetX;

    //calculation for text centering

    offsetX =0;
    if (str_num==1)
    {
        offsetY =1;
    }
    else if(str_num==2)
    {
        offsetY=10;
    }
    else
    {
        printf("Wrong str number!");
        exit(1);
    }

    uint8_t* seq = convert_str(str);
    // print_display(display);

    //     printf("STR:");


    // printf("\n");
    uint8_t SeqSize = get_size_arr(seq);
    if (SeqSize>21)
    {
        printf("To many symbols (21 max)\n");
        exit(-1);
    }
    //for (int i =0; i<SeqSize;i++)
    //   printf("%d ",seq[i]);
    offsetX = LenghtInPixels/2 - (SeqSize*SymLenght)/2;

    for(uint8_t i=0;i<SymHeight;i++)
    {
        for (uint8_t j=0;j<SeqSize;j++)
        {
            uint8_t x=j*SymLenght;
            for(int16_t k=0;k<SymLenght;k++)
            {
                display[i+offsetY][x+k+offsetX]=byte_symbols[seq[j]][i][k];
            }
        }
    }
    //print_display(display);
    return(display);
}

uint8_t** create_progress_bar(uint8_t** display,uint8_t str_num,  uint8_t percent)
{
    uint8_t offsetY;
    if (str_num==3)
    {
        offsetY =19;
    }
    else if(str_num==4)
    {
        offsetY=26;
    }
    else
    {
        printf("Wrong str number!");
        exit(1);
    }
    for(uint8_t i=0;i<ProgbarHeight;i++)
    {
        for(uint8_t j=0;j<LenghtInPixels;j++)
        {
            display[i+offsetY][j]=progress_bar[percent][i][j];
        }
    }
    return display;
}

void write_to_file(char*path,uint8_t* display[])
{
    //write bytes with image to file
    FILE* res =NULL;
    res = fopen(path,"wb");
    if (res == NULL)
    {
        printf("Error opening file");
    }
    for (uint8_t i=0; i<HeightInPixel;i++)
    {
        for(uint8_t j=0;j<LenghtInPixels;j++)
            fwrite(&display[i][j],sizeof (uint8_t),1,res);
    }
    /*
    //complete to 4kb
    uint8_t a = 1;
    for (uint8_t i=0;i<192;i++)
        fwrite(&a,sizeof (uint8_t),1,res);
        */
}


//MAIN
int main(int argc, char **argv)
{

    char*text1 = (char*)calloc(sizeof (char),LenghtInSym*2);
    char*text2 = (char*)calloc(sizeof (char),LenghtInSym*2);
    char*path = (char*)calloc(sizeof (char),BufferSize);
    uint8_t progbar1,progbar2;
    bool isVal1=false,isVal2=false,isVal3=false,isVal4=false,isPath=false;
    char*tmp = (char*)calloc(BufferSize,sizeof (char));
    //arguments
    while (1)
    {
        static struct option options[] =
        {{"text1", required_argument, 0, 0},
        {"text2", required_argument, 0, 0},
        {"progbar1", required_argument, 0, 0},
        {"progbar2", required_argument, 0, 0},
        {"path", required_argument, 0, 0},
        {0, 0, 0, 0}};

        int option_index = 0;
        int8_t c = getopt_long(argc, argv, "f", options, &option_index);

        if (c == -1) break;

        switch (c)
        {
        case 0:
            switch (option_index)
            {
            case 0:
                tmp= optarg;
                strncpy(text1,tmp,LenghtInSym*2);
                isVal1 = true;
                break;
            case 1:
                tmp= optarg;
                strncpy(text2,tmp,LenghtInSym*2);
                isVal2 = true;
                break;
            case 2:
                tmp= optarg;
                if(atoi(tmp)==0&&strcmp(tmp,"0"))
                {
                    printf("Value in progress_bar mode must be a number\n");
                    return 1;
                }
                else
                    progbar1 = atoi(tmp);
                isVal3 =true;
                break;
            case 3:
                tmp= optarg;
                if(atoi(tmp)==0&&strcmp(tmp,"0"))
                {
                    printf("Value in progress_bar mode must be a number\n");
                    return 1;
                }
                else
                    progbar2 = atoi(tmp);
                isVal4 = true;
                break;
            case 4:
                tmp= optarg;
                strncpy(path,tmp,BufferSize);
                isPath = true;
                break;
            }
            break;

        case '?':
            break;

        default:
            printf("getopt returned character code 0%o?\n", c);
        }
    }
    if (optind < argc)
    {
        printf("Has at least one no option argument\n");
        return 1;
    }
    if (!(isVal1||isVal2||isVal3||isVal4)||!isPath)
    {
        //string value only in ""
        printf("Usage: %s --text1 \"text \" --text2 \"text\" --progbar1 \"num\" --progbar2 \"num\" --path \"text\" \n", argv[0]);
        return 1;
    }


    //create and clear image to dispay
    uint8_t** display = (uint8_t**)malloc(HeightInPixel*sizeof (uint8_t*));
    for(int i=0;i<LenghtInPixels;i++)
        display[i]= (uint8_t*)malloc(LenghtInPixels*sizeof (uint8_t));

    for (uint8_t i=0;i<HeightInPixel;i++)
        for(uint8_t j=0;j<LenghtInPixels;j++)
            display[i][j]=1;

    if(isVal1)
    {
        display = create_text(display,1,text1);
    }
    if(isVal2)
    {
        display = create_text(display,2,text2);
    }

    if(isVal3)
    {
        display = create_progress_bar(display,3,progbar1);
    }

    if(isVal4)
    {
        display = create_progress_bar(display,4,progbar2);
    }

    write_to_file(path,display);
    return 0;
}
