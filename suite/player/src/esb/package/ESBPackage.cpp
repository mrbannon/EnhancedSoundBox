#include "esb/package/ESBPackage.h"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <sstream>
#include <string>


// Commands.
const static std::string COMMAND_ACTOR = "actor";
const static std::string COMMAND_ACTOR_MOVE_PAN = "actor_move_pan";
const static std::string COMMAND_ACTOR_MOVE_PRESENCE = "actor_move_presence";
const static std::string COMMAND_ACTOR_MOVE_REGISTER = "actor_move_register";
const static std::string COMMAND_ACTOR_SET_PAN = "actor_set_pan";
const static std::string COMMAND_ACTOR_SET_PRESENCE = "actor_set_presence";
const static std::string COMMAND_ACTOR_SET_REGISTER = "actor_set_register";
const static std::string COMMAND_AUDIO_FILE_PATH = "audio_file_path";
const static std::string COMMAND_PROJECT_NAME = "project_name";


///////////////////////////////////////////////////////////////////////////////
// PUBLIC
///////////////////////////////////////////////////////////////////////////////
ESBPackage::ESBPackage(std::string aFilePath, ESBActorManager* apESBActorManager):
mpESBActorManager(apESBActorManager),
mFilePath(aFilePath),
mPackageName(),
mAudioFilePath()
{
    std::ifstream file(mFilePath);
    std::string line; 
    while(std::getline(file, line))
    {
        // Trim.
        boost::algorithm::trim(line);

        // Get rid of comments.
        if(line.length() > 0 && line.at(0) != '#')
        {
            processLine(line);
        }
    }

    // Output.
    printMessage("File path: " + mFilePath);
    printMessage("Project name: " + mPackageName);
    printMessage("Audio file path: " + mAudioFilePath);
}

ESBPackage::~ESBPackage(void)
{

}


///////////////////////////////////////////////////////////////////////////////
// PRIVATE
///////////////////////////////////////////////////////////////////////////////
void ESBPackage::processLine(std::string aLine)
{
    // Get command.
    unsigned int position = aLine.find(':');
    std::string command = aLine.substr(0, position);
    boost::algorithm::trim(command);

    // Get the parameters.
    std::string parametersString = aLine.substr(position + 1, aLine.length());
    std::vector<std::string> parameters;
    std::istringstream stringStream(parametersString);
    std::string currentParameter;
    while(getline(stringStream, currentParameter, ','))
    {
        boost::algorithm::trim(currentParameter);
        parameters.push_back(currentParameter);
    }

    // Process the command.
    processCommand(command, &parameters);
}


void ESBPackage::processCommand(std::string aCommand, std::vector<std::string>* apParameters)
{
    if(aCommand == COMMAND_ACTOR)
    {
        mpESBActorManager->createActor(apParameters->at(0), apParameters->at(1), apParameters->at(2));
    }
    else if(aCommand == COMMAND_ACTOR_MOVE_PAN)
    {
        mpESBActorManager->moveActorEventPan(apParameters->at(0), 
                                             std::stof(apParameters->at(1), nullptr), 
                                             std::stoi(apParameters->at(2), nullptr), 
                                             std::stof(apParameters->at(3), nullptr), 
                                             std::stoi(apParameters->at(4), nullptr));

    }
    else if(aCommand == COMMAND_ACTOR_MOVE_PRESENCE)
    {
        mpESBActorManager->moveActorEventPresence(apParameters->at(0), 
                                                  std::stof(apParameters->at(1), nullptr), 
                                                  std::stoi(apParameters->at(2), nullptr), 
                                                  std::stof(apParameters->at(3), nullptr), 
                                                  std::stoi(apParameters->at(4), nullptr));
        
    }
    else if(aCommand == COMMAND_ACTOR_MOVE_REGISTER)
    {
        mpESBActorManager->moveActorEventRegister(apParameters->at(0), 
                                                  std::stof(apParameters->at(1), nullptr), 
                                                  std::stoi(apParameters->at(2), nullptr), 
                                                  std::stof(apParameters->at(3), nullptr), 
                                                  std::stoi(apParameters->at(4), nullptr));
        
    }
    else if(aCommand == COMMAND_ACTOR_SET_PAN)
    {
        mpESBActorManager->setActorEventPan(apParameters->at(0), 
                                            std::stof(apParameters->at(1), nullptr), 
                                            std::stoi(apParameters->at(2), nullptr));
    }
    else if(aCommand == COMMAND_ACTOR_SET_PRESENCE)
    {
        mpESBActorManager->setActorEventPresence(apParameters->at(0), 
                                                 std::stof(apParameters->at(1), nullptr), 
                                                 std::stoi(apParameters->at(2), nullptr));
    }
    else if(aCommand == COMMAND_ACTOR_SET_REGISTER)
    {
        mpESBActorManager->setActorEventRegister(apParameters->at(0), 
                                                 std::stof(apParameters->at(1), nullptr), 
                                                 std::stoi(apParameters->at(2), nullptr));
    }
    else if(aCommand == COMMAND_AUDIO_FILE_PATH)
    {
        mAudioFilePath = apParameters->at(0);
    }
    else if(aCommand == COMMAND_PROJECT_NAME)
    {
        mPackageName = apParameters->at(0);
    }
    else
    {
        printErrorMessage("unknown command " + aCommand);
    }
}