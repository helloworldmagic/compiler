#include <bits/stdc++.h>
using namespace std;
 
vector<string> insertUniqueProd(string str){
      vector<string> tempstr;
      int i=0;
 
      while(str[i] != '>'){
        i++;
      }
      i++;
      string temp= "";
  
      while(i<= str.size()){
          if(i== str.size()){
            tempstr.push_back(temp);
            break;
          }
          else if(str[i] == '|'){
            tempstr.push_back(temp);
            temp = "";
          }
          else
            temp += str[i];
            i++;
      }
  return tempstr;
}
 
 
 
string findCommonPrefix(vector<string>temp){
      int n = temp.size();
      if (n <= 1)
        return "";
 
      sort(temp.begin(), temp.end());
 
      int i=0;
      while(i<n-1){
         if(temp[i][0] == temp[i+1][0])
           break;
        i++;
      }
 
      if(i == n-1)
        return "";
 
      int j = n-1;
      while(j > 0){
        if(temp[j][0] == temp[j-1][0])
          break;
        j--;
      }
 
      string first = temp[i], last = temp[j];
      int minlen = min(first.size(), last.size());
     
      int k = 0;
 
      while (k<minlen && first[i] == last[i])
        k++;
 
      string str = first.substr(0, k);
      return str;
     
}
 
string findNonTerminal(string str){
  int i=0;
  string temp ="";
 
  while(str[i]!='-'){
    temp +=str[i];
    i++;
  }
  return temp;
}
 
pair<string, string> eliminatingLeftFactor(string commonPrefix, string nonTerminal, vector<string> temp){
        int cpsize = commonPrefix.size();
        string temp1 = nonTerminal+"->"+ commonPrefix + nonTerminal + "\'";
        string temp2 = nonTerminal + "\'" + "->";
       
        for(auto k:temp){
            if(k.size()<cpsize)
              temp1 += "|" + k;
            else if(commonPrefix!= k.substr(0, cpsize))
              temp1 += "|" + k;
            else{
              string kstring = k.substr(cpsize, k.size()-cpsize);
              if(kstring  == "")
                temp2+="#";
             
              temp2 += kstring + "|";
            }
        }
        temp2 = temp2.substr(0, temp2.size()-1);
 
  return make_pair(temp1, temp2);
}
 
 
vector<string> LeftFactoring(vector<string>&production){
   vector<string> ans;
 
    for(auto i:production){
      bool isFactoring = false;
      vector<string> temp = insertUniqueProd(i);
      string commonPrefix = findCommonPrefix(temp);
      string nonTerminal = findNonTerminal(i);
     
      if(commonPrefix == "")
        ans.push_back(i);
      else{
        pair<string, string> eliminateFactorString = eliminatingLeftFactor(commonPrefix, nonTerminal, temp);
        string temp1 = eliminateFactorString.first;
        string temp2 = eliminateFactorString.second;
        
        ans.push_back(temp1);
        ans.push_back(temp2);
      }
    }
  
    return ans;
}
 
int main() {
  ifstream f1("input.txt");
 
  if(!f1.is_open()){
    cout<<"Error in File Opening";
    exit(0);
  }
 
  string temp;
  vector<string> production;
 
  cout<<"Before Left Factoring: \n";
  while(getline(f1, temp)){
    cout<<temp<<endl;
    production.push_back(temp);
  }
 
  vector<string> ans = LeftFactoring(production);
 
  cout<<"\nAfter left Factoring : \n";
 
  for(auto i: ans)
    cout<<i<<endl;
}
