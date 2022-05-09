#include<bits/stdc++.h>
using namespace std;

int preced(char x){
  if(x == '+' || x == '-') return 1;
  else if(x == '*' || x== '/') return 2;
  else if(x == '^') return 3;
  return 0;
}

string intoPost(string infix){
  stack<char> s;
  s.push('#');
  string postfix = "";

  for(auto i: infix){
    if(isalnum(i))
      postfix += i;

    else if(i=='(')
      s.push('(');

    else if(i=='^')
      s.push('^');

    else if(i==')'){
      while(s.top()!='#' && s.top()!='('){
        postfix+=s.top();
        s.pop();
      }
      if(s.top()=='(')
        s.pop();
    }

    else{
      if(preced(i) > preced(s.top()))
        s.push(i);
      else{
        while(s.top()!='#' && preced(i) <= preced(s.top())){
            postfix += s.top();
           s.pop();
        }
        s.push(i);
      }
    }
    
  }

  while(s.top() != '#') {
      postfix += s.top();
      s.pop();
  }
   return postfix;
}

int main(){
  string infix = "a+b*(c^d-e)^(f+g*h)-i";
  cout<<"Postfix form is : "<< intoPost(infix)<<endl;
  reverse(infix.begin(), infix.end());

  for(int i=0;i<infix.size();i++){
    if(infix[i] == '(')
      infix[i] = ')';
    if(infix[i] == ')')
      infix[i] = '(';
  }

  cout<<"Prefix form is : "<< intoPost(infix);
}
