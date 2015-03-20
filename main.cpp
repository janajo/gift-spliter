//
//  main.cpp
//  jana_fortney_hw07
//
//
//
//  Created by Jana Fortney on 10/12/14.
//  Copyright (c) 2014 Jana Fortney. All rights reserved.
//


#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<string>
#include<cmath>
#include<iterator>
#include <fstream>
using namespace std;

vector<vector<int> > getSubsets(vector<int> a)
{
    
    if(a.size() == 1)
    {
        vector<vector<int> > temp;
        temp.push_back(a);  //creates vector with number
        
        vector<int> b;
        temp.push_back(b);  //creates without number
        
        return temp;
        
    }
    else
    {
        
 
        
        int last = a[a.size() - 1];
        
        a.pop_back();
        
        vector<vector<int> > without = getSubsets(a);
        
        vector<vector<int> > with = without;  // makes a dup vectpr
        
        for(int i=0;i<without.size();i++)
        {
            
            with[i].push_back(last); // adds a number to all of with vector
            
        }
        
        vector<vector<int> > total;  // all vectors, those with and without the new number
        
        for(int j=0;j<without.size();j++)
        {
            total.push_back(without[j]);
        }
        
        for(int k=0;k<with.size();k++)
        {
            total.push_back(with[k]);
        }
        
        
        
       
        //cout<<total.size()<<"\n";
        return total;
    }
    
    
}




int main()
{
    vector<int> grandpa;

    int num;
    ifstream fin("/Users/janafortney/Desktop/item.txt");
    while (!fin.eof())
    {
        fin>>num;
        grandpa.push_back(num);
    }
    
    grandpa.erase (grandpa.begin()+ (0)); // erases the number of elements used. not needed since I used vectors
    
    /*
     for(int g=0; g<grandpa.size(); g++)
    {
        cout<<grandpa[g]<< " ";
        
    }
    cout<<"\n";
    
     ///Used to show all numbers going in
     
     */
    
    vector<vector<int> > answer;
    
    answer= getSubsets(grandpa);
    vector<int>Alice;
    vector<int> Bob = grandpa;
    int diff;
    bool flag=false;
    bool flag1=true;
    int Acount=0;
    int Bcount=0;
    int min=10000;
    vector<int> AliceTemp;
    vector<int> BobTemp;
    
    
   /* for (int m = 0; m < answer.size(); m++)
    {
        Alice.clear();
        flag1=false;
        
        Alice=answer[m]; /// alice equals a sub set
        Bob=grandpa;
        
        flag1=Alice.empty();
        
        if(flag1==false || grandpa.size()<=1) // will skip any distribution where there in someone getting nothing
        {
            for(int k=0; k<Alice.size(); k++)
            {
                cout<<Alice[k]<< " ";
            }
            cout<<"\n";
        }
    
    }
    
    used to show all subsets
    
*/
    int setcount=0;
    
    for (int m = 0; m < answer.size(); m++)
    {
        Alice.clear();
        flag1=false;

        Alice=answer[m]; /// alice equals a sub set
        Bob=grandpa;
       
        flag1=Alice.empty();
        
        if(flag1==false || grandpa.size()<=1) // will skip any distribution where there in someone getting nothing
        {
       
        for(int i=0; i<Bob.size(); i++)
        {
            
            for(int j=0; j<Alice.size(); j++)
            {
                
                if(Bob[i]==Alice[j])
                {
                    
                    flag=true; //erases numbers from bob's array when they are found in alice's
                    
                }
                if (flag==true)
                {
                    Bob.erase (Bob.begin()+ (i));
                    flag=false;
                }

                
            }
            
            
           
            

          
        }
        
        
        //adding alice
        for(int g=0; g<Alice.size(); g++)
        {
            Acount+=Alice[g];
            
        }
        cout<<"\n";
        
        //adding bob
        for(int k=0; k<Bob.size(); k++)
        {
           
            Bcount+=Bob[k];
        }
        

            setcount++;
            cout<<"Set count is "<<setcount<<"\n";
            
        diff=Acount-Bcount;
        diff=abs(diff);
        
        if (diff<= min)  /// overwrites vectors if there is a new minimum of differance
        {
            AliceTemp=Alice;
            BobTemp=Bob;
            min=diff;
            
            
        }
        
        Acount=0;  //setting totals back to zero after each subset is compared
        Bcount=0;
        
        cout<<"\n";
        

        }// end of bool flag1

        
    }
    
    //resetting counters to zero for final count
    Acount=0;
    Bcount=0;
    
    //printing alice temp
   cout<<"Printing alice temp"<<"\n";
    for(int g=0; g<AliceTemp.size(); g++)
    {
        cout<<AliceTemp[g]<< " ";
       
    }
    
    //readds alice since the counter is set to zero after a subset

    for(int g=0; g<AliceTemp.size(); g++)
    {
        Acount+=AliceTemp[g];
        
    }
    
    cout<<"\n";
    //priniting bob
    cout<<"Printing bob temp"<<"\n";
    for(int k=0; k<BobTemp.size(); k++)
    {
        cout<<BobTemp[k]<< " ";
      
    }
    //readding bob
    for(int k=0; k<BobTemp.size(); k++)
    {
        
        Bcount+=BobTemp[k];
    }

    
    // finding diff
    diff=Acount-Bcount;
    diff=abs(diff);
    
    //vectors to hold positions in
    vector<int> AliceTemp3;
    vector<int> BobTemp3;
    
    
    //showing what position in the original vector the numbers fall
    for(int i=0; i<grandpa.size();i++)
    {
        for(int j=0; j<AliceTemp.size();j++)
        {
            if(grandpa[i]== AliceTemp[j])
            {
                AliceTemp3.push_back(i);
            }
        }
    
    }
    
    for(int i=0; i<grandpa.size();i++)
    {
        for(int j=0; j<BobTemp.size();j++)
        {
            if(grandpa[i]== BobTemp[j])
            {
                BobTemp3.push_back(i);
            }
        }
        
    }
    
    
    //printing to file
    ofstream fout("/Users/janafortney/Desktop/divide.txt");
    
    fout<< Acount<<" "<< Bcount<<" "<< diff<<"\n";
    
    
    for(int i=0; i<AliceTemp3.size(); i++) // displays terms
    {
        fout <<AliceTemp3[i]<<"   ";
    }
    fout<<"\n";
    for(int i=0; i<BobTemp3.size(); i++) // displays terms
    {
        fout <<BobTemp3[i]<<"   ";
    }
    
    
    
    fout.close();

    
    
    
        
    return 0;
}

