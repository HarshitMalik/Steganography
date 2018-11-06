#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

bool msg_bin[480]={0};
bool temp[8];
char sec_msg[60];


void dec_to_bin(int n)
{
 int index=7,i;
 for(i=0;i<7;i++)
      temp[i]=0; 
 while(n)
 {
      temp[index--]=n%2;
      n/=2;
 }
}

void inp_msg()
{
      printf("Please type your secret message :\n");
      printf("*****************************************************\n");
      printf("Please do not include any blank spaces but however you can use\nboth upper and lower case letters and any other special character \nlike underscore,full stop,comma etc :\n");
      printf("*****************************************************\n");
      scanf("%s",sec_msg);
}

void encode_msg()
{
      int i,k=0,t;

      for(i=0;sec_msg[i]!='\0';i++)
      {
            dec_to_bin(sec_msg[i]);
            for(t=0;t<8;t++)
                  msg_bin[k++]=temp[t];
      }
}

void decode_msg()
{
      int t=0,k,i;
      for(i=0;i<480;i+=8)
      {
            k=(msg_bin[i]*128+msg_bin[i+1]*64+msg_bin[i+2]*32+msg_bin[i+3]*16+msg_bin[i+4]*8+msg_bin[i+5]*4+msg_bin[i+6]*2+msg_bin[i+7]);
            if(k)
                sec_msg[t++]=k;
            else{
                  sec_msg[t]='\0';
                  break;
            }

      }
}

void main()
{
	int i,choice,value;
  char cArray[100];
  char cPathInput[100],cPathOutput[100];
  unsigned char cImage[480][640],cImage2[480][640];
  int iHeight,iWidth,iRow,iCol;
  FILE *filepointer = NULL, *filepointerout = NULL;
    
  printf("\n******* Steganography *******");
  printf("\n Enter your choice : \n");
  printf("1) Encode Message into image\n2) Decode Message from image\n");
  scanf("%d",&choice);
  if(choice==1)
  {
        printf("Enter Input file name (eg input.pgm) : \n");
        scanf("%s",cPathInput);
        filepointer=fopen(cPathInput,"r");
        
        if(filepointer==NULL)
          printf("Cannot open file");
        else
        {
          printf("Enter Output File Path along with outputfile name (eg output.pgm) : \n");
          scanf("%s",cPathOutput);
     
          filepointerout=fopen(cPathOutput,"w"); 
          fgets(cArray,99,filepointer);
          fputs(cArray,filepointerout);
  
          fgets(cArray,99,filepointer);
          fputs(cArray,filepointerout);

          fscanf(filepointer,"%d %d\n",&iWidth,&iHeight);
          fprintf(filepointerout,"%d %d\n",iWidth,iHeight);
      
          fgets(cArray,99,filepointer);
          fputs(cArray,filepointerout);
      
          for(iRow=0;iRow<iHeight;iRow++)
          {
            for(iCol=0;iCol<iWidth;iCol++)
            {
                  fscanf(filepointer,"%d ",&value);
                    if(value!=EOF)
                        cImage[iRow][iCol]=value;
            }
           }
           inp_msg();
           encode_msg();
          for(iRow=0;iRow<iHeight;iRow++)
          {     
            if(msg_bin[iRow]==0)
              cImage[iRow][0]=(cImage[iRow][0]&(0xfe));
            else
               cImage[iRow][0]=(cImage[iRow][0]|0x01);  
           }
          for(iRow=0;iRow<iHeight;iRow++)
           {
             for(iCol=0;iCol<iWidth;iCol++)
                  fprintf(filepointerout,"%d ",cImage[iRow][iCol]);                 
             fputc('\n',filepointerout);
           }
        printf("Secret message encoded into image succesfully !\n");
        fclose(filepointerout);
        fclose(filepointer);
       }
      }
      else if(choice==2)
      {
        printf("Enter Input file name (eg output.pgm) : \n");
        scanf("%s",cPathInput);
        filepointer=fopen(cPathInput,"r");
        if(filepointer==NULL)
          printf("Cannot open file");
        else
        {

         fgets(cArray,99,filepointer);
         fgets(cArray,99,filepointer);
         fscanf(filepointer,"%d %d\n",&iWidth,&iHeight);      
         fgets(cArray,99,filepointer);
      
        for(iRow=0;iRow<iHeight;iRow++)
        {
           for(iCol=0;iCol<iWidth;iCol++)
            {
                  fscanf(filepointer,"%d ",&value);
                    if(value!=EOF)
                        cImage[iRow][iCol]=value;
            }
        }

        for(iRow=0;iRow<iHeight;iRow++)
        {     
              msg_bin[iRow]=(cImage[iRow][0]&0x01)  ; 
        }
      decode_msg();
      printf("Message decoded succesfully !\n");
      printf("\nDecode message : \n%s\n",sec_msg);
      fclose(filepointer);
      }
     }
     else
        printf("Wrong Choice");
}
