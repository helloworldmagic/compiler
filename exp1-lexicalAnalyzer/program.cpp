#include <bits/stdc++.h>
using namespace std;

void placemapelement(unordered_map<string, string>&m1, unordered_map<char, string>&m2){
  string keywords[] = {"int", "float", "char", "string", "double" , "return", "if", "else"};

  for(auto i : keywords)
    m1[i] = "keyword";

  string op = "+-*/=><";
  string other = ",;\(){}[]'':.";

  for(auto i: op)
    m2[i] = "operator";

  for(auto i: other)
    m2[i] = "other";
}


void printsome(string header, unordered_set<string> s){
  cout<<header<<": ";
  for(auto i: s)
    cout<<i<<" ";
  cout<<endl;
}

int main() {
  ifstream f1("input.txt");

  if(!f1.is_open()){
    cout<<"Error in file opening"<<endl;
    exit(0);
  }

  string temp;
  unordered_map<string, string> m1;
  unordered_map<char, string> m2;

  placemapelement(m1, m2);

  unordered_set<string> keyword;
  unordered_set<string> identifiers;
  unordered_set<string> operators;
  unordered_set<string> numeric;

  string t="";
  
  while(getline(f1, temp)){
    cout<<temp<<endl;
    for(auto i: temp){
        if(i!=' ' && m2.find(i)==m2.end()){
          t += i;
        }else{
           if(isdigit(t[0]))
             numeric.insert(t);
            else if(m1[t] == "keyword")
              keyword.insert(t);
            else
              identifiers.insert(t);

            if(m2[i] == "operator"){
              string newtemp = "";
              newtemp += i;
              operators.insert(newtemp);
            }  
            t = "";
        }
    }
  }

  printsome("keywords", keyword);
  printsome("identifiers", identifiers);
  printsome("operator", operators);
  printsome("numeric", numeric);

  return 0;
}
