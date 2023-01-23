#include <stdio.h>
#include <stdlib.h>
char SpaceDel[200][300];
int strcmp_k(const char *str1, const char *str2);
int strlen_k(const char *str);
int main() {
    int line=0;
    int col=0;
    int colon=0;
    int aCol=0;
    int bCol=0;
    const int line_max=200;
    const int col_max =300;
    char file[line_max][col_max];
    system("netsh wlan show networks mode=bssid > ssid.txt");
    FILE *fptr=NULL;
    if((fptr = fopen("ssid.txt","r"))==NULL)
    {
        printf("Error! File cant not open");
    }
    else
    {
        char c;
        while((c=getc(fptr))!=EOF)
        {
            if(c!='\n')
            {
                file[line][col++]=c;
            }
            else
            {
                file[line][col]='\0';
                col=0;
                line++;
            }
        }
    }
    fclose(fptr);

    /*delete front space and backspace*/
    for(int i=0;i<(line+1);i++)
    {
        char str;
        while((file[i][aCol++])==32){};        //front space delete
        aCol-=1;
        while((str=file[i][aCol++])!='\000')    //store string
        {
            SpaceDel[i][colon++]=str;
            bCol = colon-1;
        }
        while(SpaceDel[i][bCol]==32){SpaceDel[i][bCol--]='\0';}   //backspace delete
        colon=0;
        aCol =0;
    }

    /*find SSID from each line and if SSID was found,store ssid name only in ssid array and  ssid name compare with string(found ssid name)  */
    for(int j=0;j<(line+1);j++)                         //to find SSID from each line
    {
        char SSID[4]={'S','S','I','D'};     //create array to find SSID
        char ssid[30]={'\0'};
        int index=0;
        int sFlag=1;
        colon=0;
        char C;
        while((C=SpaceDel[j][colon++])!='\000' & sFlag==1)   //check line end and sFlag (sFlag is zero when result found)
        {
            if(C==SSID[index]){index++;}           //find SSID from each line
            else
            {
                if(index==4)                //if SSID was found, index will be 4
                {
                    int ssidCol=0;
                    int sCol=0;
                    while(SpaceDel[j][ssidCol]!=':'){ssidCol++;}    //find ':' to store ssid name only
                    while(SpaceDel[j][ssidCol++]!=32){}             //to delete space if space place in front of ssid name
                    while((C=SpaceDel[j][ssidCol++])!='\000')       //store ssid name only in ssid array
                    {

                        ssid[sCol++]=C;
                    }
                    if(!strcmp_k(ssid,"SA Ooredoo"))         //check ssid name
                    {
                        printf("ssid found ");
                        puts(ssid);
                        j=line;                 //to stop finding if required ssid name was found
                    }
                    sFlag=0;
                }
                index  =0;
            }
        }
    }
//    printf("line = %d\n",line);
    return 0;
}

int strcmp_k(const char *str1, const char *str2)    // compare two string
{

    int index = 0;
    int max = 0;
    if (strlen_k(str1) > strlen_k(str2))
    {
        return 1;
    }
    else if (strlen_k(str1) < strlen_k(str2))
    {
        return -1;
    }
    while (str1[index] != '\0' && str1[index] != -52)
    {
        if (str1[index] > str2[index])
        {
            return 1; // str1 > str2
        }
        else if (str1[index] < str2[index])
        {
            return -1; // str1 < str2
        }
        index++;
    }
    return 0; // equal
}

int strlen_k(const char *str)       // string length
{
    int count = 0;
    while (str[count] != '\0' && str[count] != -52)
    {
        count++;
    }
    return count;
}