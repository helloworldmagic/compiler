#include<bits/stdc++.h>
using namespace std;

int preced(char ch) {
   if(ch == '+' || ch == '-') return 1;          
   else if(ch == '*' || ch == '/') return 2;         
   else if(ch == '^') return 3;
   return 0;
}

string inToPost(string intermidate) {
   stack<char> s;
   s.push('#');              
   string postfix = "";     

   for(auto i: intermidate) {
      if(isalnum(i))
         postfix += i;
      
      else if(i == '(')
         s.push('(');
      
      else if(i == '^')
         s.push('^');
        
      else if(i == ')') {
         while(s.top() != '#' && s.top() != '(') {
            postfix += s.top();
            s.pop();
         }
         s.pop();
      }
        
      else {
         if(preced(i) > preced(s.top()))
            s.push(i);
         else {
            while(s.top() != '#' && preced(i) <= preced(s.top())) {
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

int main() {
   string intermidate = "x^y/(5*z)+2";
   cout << "Postfix Form Is: "<< inToPost(intermidate)<<endl;
}
