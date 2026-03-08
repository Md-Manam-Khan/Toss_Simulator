#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;
class Toss
{
private:
    long long randomNumber, majorityWinner1 = 0, majorityWinner2 = 0;
    random_device rd;
    mt19937 gen;
public:
    Toss() : gen(rd())
    {
    }
    void getWinner(long long participantNumbers)
    {
        uniform_int_distribution<> dist(0, participantNumbers - 1);
        randomNumber = (dist(gen));
    }
    long long getIndex() const
    {
        return randomNumber;
    }
    int bestOfThreeWinner(long long participantNumbers)
    {
        uniform_int_distribution<> dist(0, participantNumbers - 1);
        randomNumber = (dist(gen));
        return randomNumber;
    }
    void bestOfThree(const vector<string> &participantNames)
    {
        long long comp = 3, hold;
        majorityWinner1 = 0;
        majorityWinner2 = 0;
        while (comp--)
        {
            hold = bestOfThreeWinner(2);
            if (hold == 0)
            {
                majorityWinner1++;
            }
            else
            {
                majorityWinner2++;
            }
        }
        if (majorityWinner1 > majorityWinner2)
        {
            randomNumber = 0;
        }
        else
        {
            randomNumber = 1;
        }
    }
    void announcement(const vector<string> &participantNames)
    {
        cout<<endl<< endl<<"\033[32mThe winner of the toss is "<<participantNames[randomNumber]<<"\033[0m"<<endl;
    }
    void bestOfThreeAnnouncement(const vector<string> &participantNames)
    {
        cout<<endl<<endl<<"\033[32mThe winner of best of 3 is "<<participantNames[randomNumber]<<"\033[0m"<<endl;
    }
    void animation()
    {
        auto startTime = high_resolution_clock::now();
        string frames[] = {"--", "\\", "|", "/"};
        long long frameCount = 0;
        cout<<endl<<"\033[35mFlipping coin:\033[0m";
        while (true)
        {
            auto currentTime = high_resolution_clock::now();
            auto elapsedTime = duration_cast<milliseconds>(currentTime - startTime).count();
            if (elapsedTime >= 5000)
            {
                break;
            }
            cout<<frames[frameCount]<<flush;
            frameCount = (frameCount + 1) % 4;
            this_thread::sleep_for(milliseconds(100));
        }
    }
};
int main()
{
    long long i, choice, people, mode;
    string choiceString, peopleString, modeString;
    cout<<"\tWelcome"<<endl<<endl<< "Rules: "<<endl;
    cout<<endl<<"1. Any number of people can participate (ideally 2).";
    cout<<endl<<"2. All participants must pick a name to represent themselves";
    cout<<endl<<endl<<"\tUnderstood???... Let's go!!!";
    startPage:
    cout<<endl<<endl<<"1. Start"<<endl<<"2. End";
    cout<<endl<<endl<< "\033[33mI choose: \033[0m";
    cin >> choiceString;
    cin.ignore();
    try
    {
        choice = stoi(choiceString);
        switch (choice)
        {
        case 2:
        {
            cout<<endl<<"\033[5;30mSee you soon... bye\033[0m"<<endl;
            return 0;
        }
        case 1:
        {
            modePage:
            cout<<endl<<"Choose mode:\n1. Regular\n2. Ranked\n3. Best of 3\n4. Main menu";
            cout<<endl<<endl<< "\033[33mI choose: \033[0m";
            cin >> modeString;
            cin.ignore();
            try
            {
                mode = stoi(modeString);
                switch (mode)
                {
                case 1:
                {
                    cout<<endl<<"\033[34mHuh classic ^(__)^\033[0m"<<endl;
                    participantPage:
                    cout<<endl<<"\033[33mChoose number of participants: \033[0m";
                    cin>>peopleString;
                    cin.ignore();
                    try
                    {
                        people = stoi(peopleString);
                        if (people < 2)
                        {   
                            cout<<endl<<"\033[5;31mAt least 2 participants required\033[0m"<<endl;    
                            goto participantPage;
                        }
                        switch (people)
                        {
                        default:
                        {
                            Toss t;
                            vector<string> participantNames(people);
                            cout<<endl<<"\033[33mInput participant titles: \033[0m"<<endl;
                            for (i = 0; i < people; i++)
                            {
                                cout<<endl<<"participant no. "<<i+1<<" title: ";
                                getline(cin, participantNames[i]);
                            }
                            t.getWinner(people);
                            t.animation();
                            t.announcement(participantNames);
                            break;
                        }   
                    }
                        break;
                    }
                    catch (...)
                    {
                        cout<<endl<<"\033[5;031mError... Input a valid number :)\033[0m";
                        cout<<endl<<"\033[31mTry again!\033[0m"<<endl;
                        goto participantPage;
                    }
                }
                case 2:
                {
                    Toss t2;
                    cout<<endl<<"\033[34mFight to the top it seems haha!\033[0m";
                    elimination:
                    cout<<endl<<endl<<"\033[33mNumber of people fighting: \033[0m";
                    cin >> peopleString;
                    cin.ignore();
                    try
                    {
                        people = stoi(peopleString);
                        if (people < 2)
                        {
                            cout<<endl<<"\033[5;31mAt least 2 participants required\033[0m"<<endl;   
                            goto elimination;
                        }
                        switch (people)
                        {
                        default:
                        {
                            vector<string> participants, ranking;
                            participants.resize(people);
                            cout<<endl<<"\033[33mInput participant titles:\033[0m"<<endl;
                            for (i = 0; i < people; i++)
                            {
                                cout<<endl<<"participant no. "<<i + 1<<" title: ";
                                getline(cin, participants[i]);
                            }
                            long long position = 1;
                            while (participants.size() > 1)
                            {
                                t2.getWinner(participants.size());
                                t2.animation();
                                long long index = t2.getIndex();
                                cout<<endl<<endl<<"\033[32mPosition "<<position<<" goes to: "<<participants[index]<<"\033[0m"<<endl;
                                ranking.push_back(participants[index]);
                                participants.erase(participants.begin() + index);
                                position++;
                            }
                            ranking.push_back(participants[0]);
                            cout <<endl<<"\033[36mLast position goes to: "<<participants[0]<<"\033[0m"<<endl;
                            cout <<endl<<"\033[5;33mFinal Ranking:\033[0m"<<endl;
                            for (i = 0; i < ranking.size(); i++)
                            {
                                cout << i + 1 << ". " << ranking[i] << endl;
                            }
                        }
                        break;   
                    }   
                }  
                catch (...)
                {    
                    cout<<endl<<"\033[5;31mInput a valid number will you >()<\033[0m";
                    goto elimination;                   
                }
                    break;
                }
                case 3:
                {
                    Toss t1;
                    cout<<endl<<"\033[34mI see... best of three between two rivals huh\033[0m";
                    vector<string> participantNames(2);
                    cout<<endl<<endl<<"\033[33mInput participant titles:\033[0m"<<endl;
                    for (i = 0; i < 2; i++)
                    {
                        cout<<endl<<"participant no. "<<i+1<<" title: ";
                        getline(cin, participantNames[i]);
                    }
                    t1.animation();
                    cout<<endl<<endl<<"\033[34mFlipping again\033[0m"<<endl;
                    t1.animation();
                    cout<<endl<<endl<<"\033[34mFlipping again\033[0m"<<endl;
                    t1.animation();
                    t1.bestOfThree(participantNames);
                    t1.bestOfThreeAnnouncement(participantNames);
                    break;
                }
                case 4:
                {
                    goto startPage;
                    break;
                }
                default:
                {
                    cout<<endl<<"\033[5;031mError... Input between 1 to 3 :)\033[0m"<<endl;
                    goto modePage;
                }    
            } 
        } 
        catch (...) 
        {   
            cout<<endl<<"\033[5;031mError... Input between 1 to 3 :)\033[0m"<<endl;  
            goto modePage;
        } 
        break;  
    }   
    default:
    {  
        cout<<endl<<"\033[5;031mError... Input 1 or 2 :)\033[0m";   
        goto startPage;    
    }       
}   
again:      
cout<<endl<<"\033[33mWanna go again\033[0m:\n1. Yes\n2. No";
cout<<endl<<endl<<"I choose: ";
cin >> choiceString;
cin.ignore();
try        
{         
    choice = stoi(choiceString);    
    switch (choice)           
    {        
        case 1:    
        {        
            goto modePage;
            break;      
        }    
        case 2:   
        {    
            cout<<endl<<"\033[5;33mSee you soon... bye\033[0m"<<endl;  
            return 0; 
        }   
        default:  
        {
            goto again;    
        }        
    }    
}       
catch (...)        
{        
    cout<<endl<< "\033[5;031mError... Input 1 or 2 :)\033[0m" << endl;        
    goto again;       
}    
}
    catch (...)
    {
        cout<<endl<<"\033[5;031mError... Input 1 or 2 :)\033[0m";
        goto startPage;
    }
}