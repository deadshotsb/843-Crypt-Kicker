#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <vector>
#include <array>
#include <set>
#include <string.h>
#define ll long long
#define S string
#define v vector
#define pb push_back
#define print cout<<
#define input cin>>
#define S_input(s) getline(cin,s)
using namespace std;
 
void disp(S s2,char map_in[26])
{
    for (auto x:s2)
    {
        if(x!=' ')
            print map_in[int(x)-97];
        else
            print ' ';
    }
    print '\n';
}
 
void disp_impossible(S s2)
{
    for (auto x:s2)
    {
        if(x!=' ')
            print '*';
        else
            print ' ';
    }
    print '\n';
}
 
int setlen(S sl)
{
    return std::set<char>(sl.begin(), sl.end()).size();
}
bool cmstring(S S1,S S2)
{
    if (S1.length() < S2.length())
        return true;
    else if (setlen(S1) < setlen(S2))
        return true;
    else if (S1.length()==S2.length() and S1.compare(S2)<0)
        return true;
    else
        return false;
}
int setstring(S str1,S str2)
{
    int len1=setlen(str1);
    int len2=setlen(str2);
    if (len1==len2)
        return 0;
    else if (len1<len2)
        return -1;
    else
        return 1;
}
int mapped(char map_in[26],char map_out[26],S str,S str2)
{
    int i,len,flag=0;
    len=str.length();
    set<char> A;
    set<char> B;
    for(i=0;i<len;i++)
    {
        if (map_in[int(str[i])-97]=='\0')
        {    
            if (map_out[int(str2[i])-97]=='\0')
            {
                map_in[int(str[i])-97]=str2[i];
                map_out[int(str2[i])-97]=str[i];
                A.insert(str[i]);
                B.insert(str2[i]);
            }
            else if (map_out[int(str2[i])-97]!=str[i])
            flag=1;
        }
        else if (map_in[int(str[i])-97]!=str2[i])
            flag=1;
        if (flag==1)
            break;
    }
    if(flag==1)
    {
        for(auto y:A)
        map_in[int(y)-97]='\0';
        for(auto y:B)
        map_out[int(y)-97]='\0';
        return -1;
    }
    return 0;
}

int mapping(v<S> word,char map_in[26],char map_out[26],v<S> st[16],int lp,int up)
{
    if (lp>up)
        return 0;
    int l,i;
    l=word[lp].length();
    for(i=0;i<st[l-1].size();i++)
    {
        if(setstring(word[lp],st[l-1][i])==-1)
            return -1;
        else if(setstring(word[lp],st[l-1][i])==0)
        {
            if (mapped(map_in,map_out,word[lp],st[l-1][i])==0)
            {
                for(;(lp>up && !(word[lp].compare(word[lp+1])));lp++);
                return mapping(word,map_in,map_out,st,lp+1,up);
            }
        }
    }
    return -1;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T,j,ret;
    input T;
    v<S> st[16];
    S s1,s2,s3;
    for (j=0;j<T;j++)
    {
        input s1;
        st[s1.length()-1].pb(s1);
    }
    for (j=0;j<16;j++)
    {
        if(st[j].size()>0)
            sort(st[j].begin(),st[j].end(),cmstring);
    }
    while (S_input(s2))
    {
        char map_in[26]={'\0'};
        char map_out[26]={'\0'};
        v<S> word;
        stringstream iss(s2);
        while (iss >> s3)
            word.pb(s3);
        sort(word.begin(),word.end(),cmstring);
        if(s2.length()==0)
        {
            print "\n";
            continue;
        }
        ret=mapping(word,map_in,map_out,st,0,word.size()-1);
        if (ret==-1)
            disp_impossible(s2);
        else
            disp(s2,map_in);
    }
    return 0;
}
