/*Sojung Son, 20170337, assignment 1*/

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>


/*global variables*/

int line=1, word=0, cha=0;
     //variables to count lines, words, and characters

int juseokline;
     //variable to check the line where the comment starts,
     //which is essential to print the error line

int i= 1, j = 1;
     //i is a variable which is added to line/word/ cha when it is needed
     //0 when it is in comment and 1 when it is not

     //j is a variable which is used to detect
     //if the code read all of the file

     //the code will not read the file in the main function
     //when the file is ended

     //j=0 when the code is finished in following functions:
     //Juseok/Juseokend/spacee/spacej/linee/linej

     //otherwise j=1


/*declare functions before main*/
/*I wrote down <WHAT FUNCTIONS DO> here*/
/*I wrote the global variables used in the functions down
  with the fucntion's codes*/
int Juseok();
//ftn to define if the comment starts or not
//it is called when i=1(not comment) and c is '/'
//if the comment starts, the ftn returns 0
//if not, then returns 1

int Juseokend();
//ftn to define if the comment ends or not
//it is called when i=0(comment) and c is '*'
//if the comment ends, the ftn returns 0
//if not, then returns 0

void spacee();
//ftn to look what comes next '\n'
//called when i=1 and c='\n'
//e means nothing, but i wanted to be similar with spacej
//(space'e')

void spacej();
//ftn to look what comes next '\n'
//called when i=0 and c='\n'
//j means juseok(space'j')

void linee();
//ftn to look what comes next space (' ')
//called when i=1 and isspace(C)=1
//the final e means the same as spacee


void linej();
//ftn to look what comes next space (' ')
//called when i=0 and isspace(c)=1
//space'j' means juseok




int main(){   //main ftn


  //it reads the file and count the line,word, and character
  //uses global variabel line, word, cha, i, j, and juseokline
  
  char c;
  c=getchar();
  // c is a character called from the file
  //read the first character of the file
  

  switch(c){
  case '/' : 
    cha+=1; word+=1;
    i=Juseok();
    if(i==0) word-=1;
    break;
  case '\n':    
    //'\n' should come earlier than isspace()
    //because \n is counted as space, too
   line+=1; cha+=1; 
   linee();       
   break;        
  case EOF:       //empty file
    line=0; word=0; cha=0; //0 line, word, cha
    break;      
  default:
    cha+=1;      
    if(isspace(c)) spacee(); //i=1 so go to spacee
    else word+=1;           //word starts, so add 1
    break;
  }
      
  
  while((c=getchar())!=EOF&&j==1){
    //until the file ends


    switch (c) {
    case '/' :
      cha+=i;    
      if (i==1) i=Juseok(); //if i=1, comment may start
                          //so find out the i
      break;      
    case '*' :      //c is '*', 42 is ASCII code of '*'
      cha +=i;    // '*' is a character
      if (i==0) i=Juseokend(); //if i=0, comment may end
                             //so find out the i
      break;  
    case '\n' :   //c is '\n'
      line+=1;    //new line starts, so add 1 to line
      cha+=1;    
      if(i==1) linee(); //if i=1, go to ftn linee
      else linej();     //if i=0, go to ftn linej
      break; 
    default:
      cha+=i;
      if(isspace(c)) {  //if c is space
        if(i==1) spacee();  //if it is not comment, go to spacee
        else spacej();      //if it is comment, go to spacej
      }
      break; 
    }  //end of switch
  
  }  //end of while

  

  switch(i){  //i wil be 0 or 1 : 0 means the comment did not end yet
  case 0 :  //comment did not end-> error!
    fprintf(stderr, "Error: line %d: unterminated comment\n", juseokline);
    //send the file to error file and print the string
    return EXIT_FAILURE;
    break; //get out of switch
  default:  //comment ended (or did not appear)
    printf("%d %d %d\n", line, word, cha);
    //print the string
    return EXIT_SUCCESS;
    break;  //get out of switch
  }//end of switch
  
}//end of main




int Juseok(){


  //declare fth Juseok
  //int type because it returns 0 or 1
  //which is integer
  //return value will go into i

  //use global variable line,char,word, i, j, and juseokline

  char d;
  d = getchar();

  switch (d) {
  case '*' :
    //it means the comment started
    cha-=1;
    //subtract 1 from cha
    //because now we know that '/' is part of comment
    juseokline=line;  //remember the starting line of '/*'
    i=0;
    return 0;  //comment started so i should be 0
    break;    
  case '/' ://if d is '/'
    cha+=1; 
    return Juseok();
    //check again if it is the start of comment
    break; 
  case EOF : 
    j=0;    
    return 1; //comment did not start, no error
    break;     
  case '\n' :  
    line+=1; cha+=1;  
    linee();    
    return i;
    //I wrote i b/c i might have changed in linee
    break;     
  default:
    cha+=1;
    if(isspace(d)) {spacee(); return i;}
    //if it is space, since i=1, go to ftn spacee
    else return 1;    //i would not have changed so return 1
  }//end of switch
  
}//end of ftn Juseok

 
int Juseokend(){

  //declare ftn Juseok
  //int type b/c it returns 0 or 1
  //which is integer
  //return value of i

  //use global variable line, i, j, cha
  

  char d;
  d = getchar();
  //read the character after '*'
  //stil comment

  switch(d) {
  case '/' :     //comment will end from the next character
    cha+=1; //comment will act as space
    i=1;
    spacee();
    //since the comment act as space, spacee ftn should be called
    //since the comment has ended(i=1) spacee ftn should be called
    return i; //i might have changed in spacee()
    break;
  case EOF : 
    j=1;
    return i;  //i=0 in this case 
    break;
  case '*' : /*c is * */
    return Juseokend();
    /*check again because the comment might end*/
    break;
  case '\n' :
    line+=1;cha+=1;
    linej(); /*i=0 in this case*/
    return i;
    break;
  default :
    if(isspace(d)) {spacej(); return i;}
    else return 0;
  }
}

  

void linee(){

  /*no return value so type is void*/
  /*use global variable line, word, cha, i, j*/

  char d;
  d = getchar();

  switch(d) {
  case '/' :
    word+=1;cha+=1;
    i=Juseok();
    if (i==0) word-=1;
    break;
  case EOF :
    j=0;
    break;
  case '\n' :
    line+=1;cha+=1;
    linee();
    break;
  default :
    cha+=1;
    if(isspace(d)) spacee();
    else word+=1;
    /* the word starts because it is a new line*/
    /* so add 1 to word*/
    break;
  }
}


void spacee(){

  /*use global variable line, word, cha, i, j*/
  
  char d;
  d= getchar();

  switch(d) {
  case '/' :
    word+=1; cha+=1;
    i=Juseok();
    if (i==0) word-=1;
    break;
  case EOF :
    j=0;
    break;
  case '\n' :
    line+=1;cha+=1;
    linee();
    break;
  default :
    cha+=1;
    if(isspace(d)) spacee();
    else word+=1;
    /*new word start after space*/
    break;
  }
}


void spacej(){

  /*use global variable line,cha, i, j*/
  
  char d;
  d=getchar();

  switch(d) {
  case '*' :
    i=Juseokend();
    break;
  case EOF :
    j=0;
    break;
  case '\n' :
    line+=1;cha+=1;
    linej();
    break;
  default :
    if(isspace(d)) spacej();
    break;
  }  
}


void linej(){

  /*use global variable line,cha, i, j*/

  char d;
  d=getchar();

  switch(d) {
  case '*' :
    i=Juseokend();
    break;
  case EOF :
    j=0;
    break;
  case '\n' :
    line+=1;cha+=1;
    linej();
    break;
  default :
    if(isspace(d)) spacej();
    break;
  }
}

   
    
  
      
