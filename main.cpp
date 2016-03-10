#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <iomanip>
#include <map>

using namespace std;

map<string,string> InsSet=
{
{"ADD","18"} , {"ADDF","58"} , {"ADDR","90"} , {"AND","40"},
{"CLEAR","4"} , {"COMP","28"} , {"COMPF","88"} , {"COMPR","A0"},
{"DIV","24"} , {"DIVF","64"} , {"DIVR","9C"},
{"FIX","C4"} , {"FLOAT","C0"} , {"HIO","F4"},
{"J","3C"} , {"JEQ","30"} , {"JGT","34"} , {"JLT","38"} , {"JSUB","48"},
{"LDA","00"} , {"LDB","68"} , {"LDCH","50"} , {"LDF","70"} , {"LDL","08"} , {"LDS","6C"} , {"LDT","74"} , {"LDX","04"} , {"LPS","D0"},
{"MUL","20"} , {"MULF","60"} , {"MULR","98"},
{"NORM","C8"} , {"OR","44"},
{"RD","D8"} , {"RMO","AC"} , {"RSUB","4C"},
{"SHIFTL","A4"} , {"SHIFTR","A8"} , {"SIO","F0"} , {"SSK","EC"} , {"STA","0C"} , {"SVC","B0"},
{"STB","78"} , {"STCH","54"} , {"STF","80"} , {"STI","D4"} , {"STL","14"} , {"STS","7C"},
{"STSW","E8"} , {"STT","84"} , {"STX","10"} , {"SUB","1C"} , {"SUBF","5C"} , {"SUBR","94"},
{"TD","E0"} , {"TIO","F8"} , {"TIX","2C"} , {"TIXR","B8"},
{"WD","DC"},
};

map<char,string> CharCode =
{
    {'A',"41"},{'B',"42"},{'C',"43"},
    {'D',"44"},{'E',"45"},{'F',"46"},
    {'G',"47"},{'H',"48"},{'I',"49"},
    {'J',"4A"},{'K',"4B"},{'L',"4C"},
    {'M',"4D"},{'N',"4E"},{'O',"4F"},
    {'P',"50"},{'Q',"51"},{'R',"52"},
    {'S',"53"},{'T',"54"},{'U',"55"},
    {'V',"56"},{'W',"57"},{'X',"58"},
    {'Y',"59"},{'Z',"5A"},
};

int calc_objcode(string val)
{
    string tmp="", tmpHex="";
        char c ;
        int i=2 ,n;
        bool flag=true;
        stringstream stream0;

    if(val[0]=='C')
    {
        while(flag)
        {
            c=val[i];
            if(c==val.back()){ flag=false ; }
            else {tmp.push_back(c); i++; }
        }
        i--;
        for(int j=0;j<i;j++) tmpHex+=CharCode[tmp[j]];


        int n;
        stream0<< std::hex << tmpHex ;
        stream0>> n ;

        stream0.clear();
        tmp.clear();
        tmpHex.clear();
        return n;
    }
    else if(val[0]=='X')
    {
        while(flag)
        {
            c=val[i];
            if(c==val.back()){ flag=false ; }
            else {tmpHex.push_back(c); i++; }
        }
        stream0<< std::hex << tmpHex ;
        stream0>> n ;

        stream0.clear();
        tmp.clear();
        tmpHex.clear();
        return n;
    }
    else
    {
        stream0<< std::hex << val ;
        stream0>> n ;

        stream0.clear();
        tmp.clear();
        tmpHex.clear();
        return n;
    }
}
int calc_byte_loc(string val ,int current )
{
    bool flag=true;
    char c;
    int ret=0 ,i=2;
    if(val[0]=='C')
    {
        while(flag)
        {
            c=val[i];
            if(c==val.back()){ flag=false ; }
            else {ret++;i++;}
        }
        return current+ret;
    }
    else if(val[0]=='X')
    {
        while(flag)
        {
            c=val[i];
            if(c==val.back()){ flag=false ; }
            else {ret++;i++;}
        }
        if(ret%2==0) return current+(ret/2);
        else if(ret%2==1)return current+((ret/2)+1);
    }
}


int calc_loc(int loc ,string op ,int value )
{
    int newLoc;
    if(op=="RESB")
    {
        newLoc=loc+value;
    }
    else if(op=="RESW")
    {
        newLoc=loc+(3*value);
    }
    return newLoc;
}
/** atoi: convert string to integer */
int atoi(string s)
{
    int i, n;
    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}

/** decimal to hexa - need edition -
string DecToHex (int i)
{
    string tmp ;
    tmp = itoa (i,nullptr,16);
    return tmp;
}
*/
string intTostring (int i)
{
  char buffer [33];
  string s ;
  //s=itoa (i,buffer,10);
  //itoa (i,buffer,16);
  //itoa (i,buffer,2);
  return s;
}
/** string in hexa to decimal */
/**
string StringHexToDecimal(string s)
{
    int n ;
    n = std::stoi (s,nullptr,16);
    return n ;
}
*/

typedef struct line
{
    int locDec ;
    int objcode ;
    string opcode ;
    string var ;
    string code ;
    string val ;
    string obc;
};

int number_of_lines = 0;

void numberoflines(){
    cout<<"number of lines in text file: " << number_of_lines << endl;
}



int main()
{
    line *lineCode ;
    ifstream inFile("SIC Program") ;
    ofstream PathOne , PathTwo , HTRecord ;

    inFile.open("SIC program.txt");
    PathOne.open("path one.txt");
    PathTwo.open("path two.txt");
    HTRecord.open("HTRECORD.txt");

    string lines , STRING , ProgramName ;

    freopen("whole program.txt","w",stdout);

    if(inFile.is_open()){
        while(!inFile.eof()){
            getline(inFile,lines);
            cout<< lines << endl;
            number_of_lines++;
        }
        inFile.close();
    }
    numberoflines();
    lineCode= new line[number_of_lines];
    inFile.open("SIC program.txt");

    int c=0 , j=0 , k=0 ;
    char checkChar , X  ;
    string word[3] ={"","",""} , fady="" ;

    if(inFile.is_open()){
        while(!inFile.eof()){
            getline(inFile,STRING);
            if(STRING.back()==' ' || STRING.back()=='   ') { STRING.pop_back(); /*cout <<lines << " -->edited line "<< endl;*/ }
            j=0;

  for ( int i=0; i<STRING.length(); i++)
    {
        checkChar = STRING[i];
        if(checkChar != ' ' )
        {
           word[j].push_back(checkChar) ;
           if((STRING[i+1]==' '||STRING[i+1]=='\t')&& (i+1)!=STRING.length()) { j++ ; }
        }
    }

        if(j==0)
        {
            lineCode[k].code= word[0];
            lineCode[k].var=fady;
            lineCode[k].val=fady;
        }
        if(j==2)
        {
            if(word[2].back()=='X')
            {
                X='X';
                word[2].pop_back();
                if(word[2].back()==',')
                    word[2].pop_back();
                else
                    word[2].push_back(X);
            }
            lineCode[k].var= word[0];
            lineCode[k].code= word[1];
            lineCode[k].val= word[2];
        }
        else if (j==1)
        {
            if(word[1].back()=='X')
            {
                X='X';
                word[1].pop_back();
                if(word[1].back()==',')
                    word[1].pop_back();
                else
                    word[1].push_back(X);
            }
            lineCode[k].code= word[0];
            lineCode[k].val= word[1];
            lineCode[k].var=fady;
        }
         k++;
         STRING.clear();
         word[0].clear();
         word[1].clear();
         word[2].clear();
        }
        inFile.close();
    }
    for(int t=0;t<number_of_lines;t++)
    cout <<lineCode[t].var << " " << lineCode[t].code << " " <<lineCode[t].val << endl ;

    /********************************* FRIST PATH ***************************************************/

    int first_loc ;
    std::stringstream stream;

    stream << std::hex << lineCode[0].val; /** getting the start address  in stream<string> */
    stream >> first_loc;  /** getting the start address in decimal<int> */


    int currentLoc=0 ,tmpval;
    string tmpOp ,tmp ;
    lineCode[0].locDec=first_loc;
    lineCode[1].locDec=lineCode[0].locDec;
    for(int t=2;t<number_of_lines;t++)
    {
        if(lineCode[t-1].code=="RESW" || lineCode[t-1].code=="RESB")
        {
            tmpOp=lineCode[t-1].code;
            tmpval=atoi(lineCode[t-1].val);
            currentLoc=lineCode[t-1].locDec;
            lineCode[t].locDec=calc_loc(currentLoc,tmpOp,tmpval);
        }
        else if(lineCode[t-1].code=="BYTE")
        {
            tmp=lineCode[t-1].val;
            currentLoc=lineCode[t-1].locDec;
            lineCode[t].locDec=calc_byte_loc(tmp,currentLoc);
        }
        else
        lineCode[t].locDec=lineCode[t-1].locDec+3;

        cout << std::hex << lineCode[t].locDec << endl ;
    }
    PathOne << "Label\tAddress" << endl ;

    map<string,int> path1;

    for(int t=0;t<number_of_lines;t++)
    {
        if(lineCode[t].var!=fady)
        {
            path1.insert(std::make_pair(lineCode[t].var,lineCode[t].locDec));
            PathOne  << lineCode[t].var  ;
            PathOne << "\t" << std::hex << lineCode[t].locDec << endl ;

        }
    }

    /***************************************************************************************************************************/
    /***************************************** SECOND PATH *****************************************************************/

    string tmpvalue ;
    std::stringstream stream2 ;

    for(int t=0;t<number_of_lines;t++)
    {
        if(lineCode[t].code=="START" || lineCode[t].code=="RESW" || lineCode[t].code=="RESB" || lineCode[t].code=="END")
           {
               lineCode[t].objcode=103 ;
           }
        else if (lineCode[t].code=="WORD" || lineCode[t].code=="BYTE")
        {
            tmpvalue=lineCode[t].val;
            if(lineCode[t].code=="BYTE"&&lineCode[t].val[0]=='C')
            {
                lineCode[t].opcode="104";
                lineCode[t].objcode=calc_objcode(tmpvalue);
            }
            else
            {
                lineCode[t].objcode=calc_objcode(tmpvalue);
                lineCode[t].opcode="00";
            }

        }
        else if(lineCode[t].code=="RSUB")
        {
            lineCode[t].opcode=InsSet[lineCode[t].code];
            lineCode[t].objcode=0;
            cout << "for RSUB " << lineCode[t].opcode << "\t" << lineCode[t].objcode << endl ;
        }
        else
        {
            lineCode[t].opcode=InsSet[lineCode[t].code];
            map<string, int>::iterator p;
            p=path1.find(lineCode[t].val);
            lineCode[t].objcode=p->second;

        }
    }
    PathTwo << "Object Code" << endl ;
    for(int t=0;t<number_of_lines;t++)
    {
        if(lineCode[t].objcode==103) { PathTwo << "------" << endl ; }
        else if(lineCode[t].opcode=="104") { PathTwo << std::hex << lineCode[t].objcode << endl ; }
        else
        {
            PathTwo << lineCode[t].opcode ;
            PathTwo << std::hex << lineCode[t].objcode << endl ;
        }
    }


    /***************************************************************************************************************************/
    /******************************************** H-T RECORD *************************************************************/

    int container=0 , no_record=0 , sub ,StartAdd , ProgramLength  , x=0 , y=1 ,s=0;
    StartAdd=lineCode[0].locDec ;
    ProgramName=lineCode[0].var ;
    ProgramLength=lineCode[number_of_lines-1].locDec-lineCode[0].locDec ;
    bool flag =false ;

    HTRecord << " H " << ProgramName ;
    HTRecord << " 00" << std::hex << StartAdd ;
    HTRecord << " 00" << std::hex << ProgramLength  ;

    for(int t=1;t<number_of_lines;t++)
    {
        if(container<=30)
        {
            if(container==0)s=t;
            sub=lineCode[t].locDec-lineCode[t-1].locDec;
            container+=sub;
            if(container>30){container-=sub;flag=true;s=t;}
            if(t==number_of_lines-1){ flag=true;s=t;}
        }
        if(flag)
        {
            c++;
            if(c==1){ HTRecord << "\n T " ; HTRecord << " "  << std::hex << StartAdd ; }
            else{
            HTRecord << "\n T " ;
            HTRecord << " " << std::hex << lineCode[s].locDec;
            }
            HTRecord << " " << std::hex << container ;

             for(int p=y;p<x;p++)
             {
                if(lineCode[p].objcode==103) { container-=sub ; }
                else if(lineCode[p].opcode=="104") { HTRecord << " "  << std::hex << lineCode[p].objcode ; }
                else
                {
                    HTRecord <<" " << lineCode[p].opcode ;
                    HTRecord << std::hex << lineCode[p].objcode ;
                }
             }

            container=0;
            flag=false;
            y=x;
            x=t;
        }
    }

    HTRecord << "\n E" << " 00" <<  std::hex << StartAdd << endl ;

    return 0;
}
