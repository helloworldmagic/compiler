#include<bits/stdc++.h>
using namespace std;

string findNonTerminal(string str){
  int i=0;
  string temp ="";
  while(str[i]!='-'){
    temp +=str[i];
    i++;
  }
  return temp;
}

void shiftreduceParsing(unordered_map<string, string>&grammer, string input, string start){
    cout<<"Stack\t\t\t\t"<<"Input\t\t\t\t"<<"Action"<<endl;
    string temp = input;
    string stack = "$";
    string str1 = "";
    string str2 = "";
    bool isthere = false;

    int limit = 0;
  
    while(limit<10 && temp != ""){
      if(temp == "$"){
          str1 += "$" + start;
          if(stack == str1){
              cout<<stack<<"\t\t\t\t"<<temp<<"\t\t\tAccepted"<<endl;
              break;
          }
        limit++;  
      }else{
        cout<<stack<<"\t\t\t\t"<<temp<<"\t\t\tShift"<<endl;
        stack = stack+temp[0];
        temp = temp.substr(1, temp.size()-1);
      }

        int i = stack.size()-1;
        while(i>=0){
          str2 = stack[i] + str2;
          if(grammer.find(str2)!=grammer.end()){
              cout<<stack<<"\t\t\t\t"<<temp<<"\t\t\tReduce by "<<grammer[str2]<<"->"<<str2<<endl;
              for(int i=0;i<str2.size();i++)
                  stack.pop_back();
              stack = stack + grammer[str2];
              str2 = "";
              i = stack.size();
          }
          i--;
        }
      
        stack = stack + grammer[str2];
        str2="";
        
    }

    if(limit == 10)
        cout<<stack<<"\t\t\t\t"<<temp<<"\t\t\tError"<<endl;
}


int main(){
    ifstream f1("grammer.txt");
    ifstream f2("input.txt");
  
    unordered_map<string, string>grammer;
    string input;
    string temp;
    string start;
    bool flag = false;
  
    while(getline(f1, temp)){
      if(!flag){
        start = findNonTerminal(temp);
        flag=true;
      }
      
      string s = findNonTerminal(temp);
      int k = s.size()+2;
      string str="";
      for(int i=k;i<temp.size();i++){
          if(temp[i] == '|'){
              grammer[str] = s;
              str="";
          }
          else
            str += temp[i];
      }
      
      if(str != ""){
          grammer[str] = s;
      }
    }
  
    getline(f2, input);
    shiftreduceParsing(grammer, input, start);
}
