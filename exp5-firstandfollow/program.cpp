#include<bits/stdc++.h>
using namespace std;
set<char> ss;
 
string findNonTerminal(string str){
  int i=0;
  string temp ="";
 
  while(str[i]!='-'){
    temp +=str[i];
    i++;
  }
 
  return temp;
}
 
bool solve(string i, string org, string last,map<string,vector<vector<string>>> &mp){
    bool rtake = false;
    for(auto r : mp[i]){
      bool take = true;
     
      for(auto s : r){
        if(s == i)
          break;
       
        if(!take)
          break;
       
        if(!(s[0]>='A'&&s[0]<='Z')&&s[0]!='#'){
            ss.insert(s[0]);
            break;
        }
         
        else if(s[0] == '#'){
          if(org == i||i == last)
            ss.insert(s[0]);
          rtake = true;
          break;
        }
         
      else{
        take = solve(s,org,r[r.size()-1],mp);
        rtake |= take;
      }
    }
  }
 
  return rtake;
}
 
map<string,set<string>> solveFollow(string start, map<string,vector<vector<string>>> mp, map<string,set<char>> first){
  map<string,set<string>> follow;
  int i;
  follow[start].insert("$");
  int count = 10;
 
 
  while(count--){
    for(auto q : mp){
      for(auto r : q.second){
        for(i=0;i<r.size()-1;i++){
 
            string temp1 = r[i];
            string temp2 = r[i+1];
         
            if(temp1[0]>='A' && temp1[0]<='Z'){
                if(!(temp2[0]>='A' && temp2[0]<='Z'))
                    follow[temp1].insert(temp2);
 
           
                else {
                  int j=i+1;
               
                  while(temp2[0]>='A' && temp2[0]<='Z'){
                   
                    if(*first[temp2].begin() == '#'){
                     
                        for(auto g : first[temp2]){
                          if(g=='#')
                            continue;
                         
                          string str = "";
                          str +=g;
                          follow[temp1].insert(str);
                        }
                     
                        j++;
                       
                        if(j<r.size()){
                          temp2 = r[j];
                          if(!(temp2[0]>='A'&&temp2[0]<='Z')){
                            follow[temp1].insert(temp2);
                            break;
                          }
                        }  
                        else{
                          for(auto g : follow[q.first]){
                            string str = "";
                            str += g;
                            follow[temp1].insert(str);
                          }
                            break;
                        }
                  }
                     
                  else{
                    for(auto g : first[temp2]){
                        string str = "";
                        str += g;
                        follow[r[i]].insert(str);
                    }
                    break;
                  }
                }
              }
            }
        }
 
        string lastTemp = r[r.size()-1];
       
        if(lastTemp[0]>='A' && lastTemp[0]<='Z'){
              for(auto g : follow[q.first])
                follow[r[i]].insert(g);
        }
       
      }
    }
  }
 
  return follow;
}
 
 
int main(){
 
ifstream fin("input.txt");
  if(!fin.is_open()){
    cout<<"Error in file opening";
    exit(0);
  }
 
 
  map<string,vector<vector<string>>> mp;
  string start;
  bool flag = false;
  string line;
 
  cout<<"Grammar: "<<'\n';
  while(getline(fin, line)){
    cout<<line<<endl;
    if(flag == false){
      start = findNonTerminal(line);
      flag = true;
    }
   
    vector<string> temp;
    string s = findNonTerminal(line);
    int k = s.size()+2;
   
    for(int i=k;i<line.size();i++){
        if(line[i] == '|'){
            mp[s].push_back(temp);
          temp.clear();
        }else{
          string newStr = "";
          newStr+=line[i];
          if(i+1!=line.size() && line[i+1] == '\''){
              newStr+='\'';
              i++;
          }
          temp.push_back(newStr);
        }
    }
    mp[s].push_back(temp);
  }
 
 
  map<string,set<char>> first;
 
  for(auto q : mp){
    ss.clear();
    solve(q.first,q.first,q.first,mp);
    for(auto g : ss)
      first[q.first].insert(g);
  }
 
  cout<<"\nFIRST: "<<'\n';
  for(auto q : first){
    string ans = "";
    ans += q.first;
    ans += " = {";
    for(char r : q.second){
      ans += r;
      ans += ',';
    }
    ans.pop_back();
    ans+="}";
    cout<<ans<<'\n';
  }
 
 
 
  // //FOLLOW
  map<string,set<string>> follow  = solveFollow(start, mp, first);
 
    cout<<"\nFOLLOW: "<<'\n';
    for(auto q : follow){
      string ans = "";
      ans += q.first;
      ans += " = {";
      for(auto r : q.second){
        ans += r;
        ans += ',';
      }
      ans.pop_back();
      ans+="}";
      cout<<ans<<'\n';
    }
 
  return 0;
}
