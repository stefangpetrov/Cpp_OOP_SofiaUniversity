#include "CommandHandler.h"
#include "CommandChecker.h"

void CommandHandler::handleCommand(const char* command)
{
    char* _command = new char[strlen(command) + 1];
    strcpy(_command, command);

    if (checker::isRegistration(_command))
    {
        registration(_command + strlen("registration "));
    }
    else if (checker::isChallenge(_command))
    {
        challenge(_command + strlen("challenge "));
    }
    else if (checker::isFinish(_command))
    {
        finish(_command + strlen("finish "));
    }
    else if (checker::isProfileInfo(_command))
    {
        profileInfo(_command + strlen("profile_info "));
    }
    else if (checker::isListBy(_command))
    {
        listBy(_command + strlen("list_by "));
    }
    else if (checker::isLoad(_command))
    {
        load(_command + strlen("load "));
    }
    else
    {
        cout << "Invalid command!" << endl;
    }

    if (_command != nullptr)
        delete[] _command;
}

void CommandHandler::registration(const char* userInfo)
{
    allUsers.add(userInfo);
    
}

void CommandHandler::challenge(const char* challengeInfo)
{
    char* tokArray = new char[strlen(challengeInfo) + 1];
    strcpy(tokArray, challengeInfo);

    char* tok;
    tok = strtok(tokArray, " ");
    char* challengerName = nullptr;
    char* challengeTag = nullptr;

    if (tok != NULL)
    {
        challengerName = new char[strlen(tok) + 1];
        strcpy(challengerName, tok);
    }

    //
    if (challengerName != nullptr)
    {
        
        if (allUsers.contains(challengerName))
        {
            tok = strtok(NULL, " ");

            if (tok != NULL)
            {
                challengeTag = new char[strlen(tok) + 1];
                strcpy(challengeTag, tok);
            }


            if (challengeTag != nullptr)
            {
                if (challengeTag[0] != '#' || (strlen(challengeTag) < 2 || strlen(challengeTag) > 31))
                {
                    cout << "Challenge must start with # and be 31 symbols long!" << endl;
                    return;
                }
                else
                {
                    tok = strtok(NULL, " ");
                    if (tok != NULL)
                    {

                        while (tok != NULL)
                        {

                            if (!allUsers.contains(tok))
                            {

                                cout << tok << " is not a registered user. Try challenging some registered users." << endl;
                                if (challengerName != nullptr)
                                    delete[] challengerName;
                                if (challengeTag != nullptr)
                                    delete[] challengeTag;
                                return;
                            }
                            tok = strtok(NULL, " ");
                        }

                        delete[] tokArray;
                        tokArray = new char[strlen(challengeInfo) + 1];
                        strcpy(tokArray, challengeInfo);
                        

                        tok = strtok(tokArray, " ");
                        
                        tok = strtok(NULL, " ");
                        tok = strtok(NULL, " ");

                        while (tok != NULL)
                        {
                            //cout<<tok<<endl;
                            for (size_t i = 0; i < allUsers.getSize(); i++)
                            {
                                if (strcmp(allUsers[i].getName(), tok) == 0)
                                {
                                    allUsers[i].addUnfinishedChallenge(challengeTag);
                                    
                                    
                                }
                            }
                            tok = strtok(NULL, " ");
                        }

                        allChallenges.add(challengeTag);
                        
                        
                    }
                    else
                    {
                        cout << "You haven't specified who you want to challenge! Try again." << endl;
                        return;
                    }


                }
            }
            
        }
        else
        {
            cout << "No such user"<<endl;
            return;
        }
    }
    else
    {
        cout << "Enter a user" << endl;
    }

    if (challengerName != nullptr)
        delete[] challengerName;
    if (challengeTag != nullptr)
        delete[] challengeTag;
}

void CommandHandler::finish(const char* finishInfo)
{
    char* infoToChar = nullptr;
    infoToChar = new char[strlen(finishInfo) + 1];
    strcpy(infoToChar, finishInfo);

    char* tok = strtok(infoToChar, " ");
    char* tag = nullptr;
    char* userId = nullptr;
    char* rateToChar = nullptr;
    float rate;
    int userID = 0;

    if (tok != NULL)
    {
        tag = new char[strlen(tok) + 1];
        strcpy(tag, tok);
    }
    else
    {
        cout << "Please write a valid tag!";
        return;
    }

    if (!allUsers.containsID(userID))
    {
        cout << "No such user registered" << endl;
        return;
    }
    if (!allChallenges.contains(tag))
    {
        cout << "No such challenge" << endl;
        return;
    }
    tok = strtok(NULL, " ");
    if (tok != NULL)
    {
        userId = new char[strlen(tok) + 1];
        strcpy(userId, tok);

        int length = strlen(userId);

        for (int i = 0; i < length; i++)
        {
            if (userId[i] < '0' || userId[i] > '9')
            {
                cout << "No such ID" << endl;
                if (userId != nullptr)
                    delete[] userId;
                if (rateToChar != nullptr)
                    delete[] rateToChar;
                if (tag != nullptr)
                    delete[] tag;
                if (infoToChar != nullptr)
                    delete[] infoToChar;

                return;
            }
            int currentDigit = userId[i] - '0';
            userID += currentDigit * pow(10, length - i - 1);
        }


        tok = strtok(NULL, " ");
        if (tok != NULL)
        {
            rateToChar = new char[strlen(tok) + 1];
            
            strcpy(rateToChar, tok);
            rate = strtod(rateToChar, NULL);

            if (rate >= -5 && rate <= 10)
            {
                for (size_t i = 0; i < allUsers.getSize(); i++)
                {
                    if (allUsers[i].getId() == userID)
                    {
                        allUsers[i].removeChallenge(tag);
                    }
                }

                for (size_t i = 0; i < allChallenges.getSize(); i++)
                {
                    if (strcmp(allChallenges[i].getName(), tag) == 0)
                    {
                        allChallenges[i].ChangeRating(rate);
                    }
                }
            }
            else
            {
                cout << "Try givin the challenge a valid rating. Hint [-5, 10]." << endl;
            }
            
            
        }
        else
        {
            cout << "Write proper rate." << endl;
        }
    }
    else
    {
        cout << "Write a proper ID!" << endl;
        return;
    }

    if (userId != nullptr)
        delete[] userId;
    if (rateToChar != nullptr)
        delete[] rateToChar;
    if (tag != nullptr)
        delete[] tag;
    if (infoToChar != nullptr)
        delete[] infoToChar;
}

void CommandHandler::profileInfo(const char* name)
{
    if (allUsers.contains(name))
    {
        for (size_t i = 0; i < allUsers.getSize(); i++)
        {
            if (strcmp(allUsers[i].getName(), name) == 0)
            {
                allUsers[i].print();
            }

        }
    }
    else
    {
        cout << "No such user!" << endl;
    }
}

void CommandHandler::listBy(const char* listInfo)
{
    int size = allChallenges.getSize();

    if (strcmp(listInfo, "newest") == 0)
    {

        for (int i = size - 1; i >= 0; i--)
        {
            allChallenges[i].print();
        }

    }
    else if (strcmp(listInfo, "oldest") == 0)
    {
        for (int i = 0; i < size; i++)
        {
            allChallenges[i].print();
        }
    }
    else if (strcmp(listInfo, "most_popular") == 0)
    {
        for (int i = 0; i < size; i++)
        {
            Challenge currentPopular = allChallenges[i];
            for (int j = i + 1; j < size; j++)
            {
                if (allChallenges[j].getNumberOfChallenges() > allChallenges[i].getNumberOfChallenges())
                {
                    currentPopular = allChallenges[j];
                }

            }
            currentPopular.print();

        }

    }
    else
    {
        cout << "Invalid command!" << endl;
    }
}

void CommandHandler::load(const char* fileInfo)
{
    fstream file;

    char* fileToChar = nullptr;
    fileToChar = new char[strlen(fileInfo) + 1];
    strcpy(fileToChar, fileInfo);

    char* tok = strtok(fileToChar, ".");
    char* ext = nullptr;
    char* fileN = nullptr;

    if (tok != NULL)
    {
        fileN = new char[strlen(tok) + 1];
        strcpy(fileN, tok);
    }

    tok = strtok(NULL, " ");

    if (tok != NULL)
    {
        ext = new char[strlen(tok) + 1];
        strcpy(ext, tok);
    }

    if (strcmp(fileN, "users") == 0)
    {
        if (strcmp(ext, "txt") == 0)
        {
            file.open("users.txt");
            if (file.is_open())
            {
                char c;
                while (!file.eof())
                {

                    char* userInfo = new char[8];
                    int allocated = 8;
                    int index = 0;
                    while (file.get(c))
                    {
                        if ('\n' == c || '\r' == c)
                        {
                            break;
                        }
                        else
                        {
                            if (index == allocated)
                            {
                                allocated *= 2;
                                char* buffer = new char[allocated];

                                for (int i = 0; i < index; i++)
                                {
                                    buffer[i] = userInfo[i];
                                }
                                delete[] userInfo;
                                userInfo = buffer;

                            }
                            userInfo[index] = c;
                            index++;
                        }
                    }

                    userInfo[index] = '\0';

                    cout << userInfo << endl;
                    allUsers.add(userInfo);

                    delete[] userInfo;
                }
                file.close();
            }
            else
            {
                cout << "file could not open!" << endl;
                return;
            }
            
        }
        else
        {
            cout << "Wrong ext" << endl;
            return;
        }
    }

    else if (strcmp(fileN, "challenges") == 0)
    {
        if (strcmp(ext, "bin") == 0)
        {
            ifstream fileToOpen("challenges.bin", ios::binary);
            char value;

            if (fileToOpen.is_open())
            {
                while (!fileToOpen.eof())
                {
                    char* challengeInfo = new char[8];
                    int allocated = 8;
                    int index = 0;
                    while (fileToOpen.read((char*)&value, sizeof(char)))
                    {
                        if ('\n' == value || '\r' == value)
                        {
                            break;
                        }
                        else
                        {
                            if (index == allocated)
                            {
                                allocated *= 2;
                                char* buffer = new char[allocated];

                                for (int i = 0; i < index; i++)
                                {
                                    buffer[i] = challengeInfo[i];
                                }
                                delete[] challengeInfo;
                                challengeInfo = buffer;

                            }
                            challengeInfo[index] = value;
                            index++;
                        }


                    }

                    challengeInfo[index] = '\0';

                    if(challengeInfo[0] != '\0')
                        this->challenge(challengeInfo);

                    delete[] challengeInfo;
                }
            }
            else
            {
                cout << "file is not correct" << endl;
                return;
            }

            fileToOpen.close();
        }
        else
        {
            cout << "Wrong ext" << endl;
            return;
        }

    }
    else
    {
        cout << "Wrong file name!" << endl;
    }

}

