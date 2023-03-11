#include <../electron_controller.h>

bool ElectronController::Connect()
{

    return player->Connect();
}

void ElectronController::Init()
{
    AddTask(Happy_start(true));
    AddTask(Happy_cycle());
    AddTask(Happy_end());
    RunTask();
}
void ElectronController::RunTask()
{
    if (!robotTasks.empty()) {
        player->Play(robotTasks.front());
        robotTasks.pop();
    }
    if (!robotTasks.empty()) {      
            RunTask();      
    }
    else {
        if (isCalling) {
            CallingTask();
        }
        else {
            AssignTasks(-1);
        }
        
        RunTask();
    }
    
}
void ElectronController::CallingTask()
{
    if (callNum == 0) {
        AddTask(Alarmed_start());
    }
    else if (callNum < 10) {
        if (callNum % 2 == 0) {
            AddTask(Alarmed_cycle_calling());
        }
        else {
            AddTask(Alarmed_cycle());
        }
    }
    else if (callNum == 10) {
        AddTask(Angry_start());
    }
    else
    {
        if(callNum % 2 == 0) {
            AddTask(Angry_cycle_calling());
        }
        else {
        AddTask(Angry_cycle());
        }
    }
    callNum++;
}
void ElectronController::AssignTasks(int num)
{
    int randNum = rand() % 115 +9;
    if (num != -1) {
        randNum = num;
    }
    if (randNum == 1) {
        AddTask(Happy_start(false));
        int randNum1 = rand() % 2+1;      
        AddTask(Happy_cycle());      
        AddTask(Happy_end());
    }
    else if (randNum == 2) {
        AddTask(Angry_start());
        int randNum1 = rand() % 2 + 1;
        for (int i = 0; i < randNum1; i++) {
            AddTask(Angry_cycle());
        }
        AddTask(Angry_end());
    }
    else if (randNum == 3) {
        AddTask(Alarmed_start());
        int randNum1 = rand() % 2 + 1;
        for (int i = 0; i < randNum1; i++) {
            AddTask(Alarmed_cycle());
        }
        AddTask(Alarmed_end());
    }
    else if(randNum == 9) {
        AddTask(Sad_start(false));
        int randNum1 = rand() % 2+1;
        for (int i = 0; i < randNum1; i++) {
            AddTask(Sad_cycle());
        }
        AddTask(Sad_end());
    }
    else if (randNum == 10) {
        AddTask(Disdain_start());
        int randNum1 = rand() % 2+1;
        for (int i = 0; i < randNum1; i++) {
            AddTask(Disdain_cycle());
        }
        AddTask(Disdain_end());
    }
   
    else if (randNum >= 10&& randNum < 30) {
        AddTask(Stay_ss1());
    }
    else if (randNum >= 30 && randNum < 50) {
        AddTask(Stay_ss2());
    }
    else if (randNum >= 55 && randNum < 60) {
        AddTask(LookLeft_start());
        int randNum1 = rand() % 2 + 1;
        for (int i = 0; i < randNum1; i++) {
            AddTask(LookLeft_cycle());
        }
        AddTask(Lookleft_end());
    }
    else if (randNum >= 65 && randNum < 70) {
        AddTask(LookRight_start());
        int randNum1 = rand() % 2+1;
        for (int i = 0; i < randNum1; i++) {
            AddTask(LookRight_cycle());
        }
        AddTask(LookRight_end());
    }
    else
    {
        AddTask(Stay_ss());
    }
    
}

void ElectronController::AddTask(ElectronPlayer::RobotTask task)
{
    AddTask(task, false);
}

void ElectronController::AddTask(ElectronPlayer::RobotTask task,bool needQueue)
{
    if (needQueue) {
        ClearTask();
        robotTasks.push(task);
    }
    else {     
        robotTasks.push(task);
    }
}

void ElectronController::ClearTask()
{
    queue<ElectronPlayer::RobotTask> empty;
    swap(empty, robotTasks);
}

void ElectronController::MsgFromTCP(const char* msg,
    SOCKET s)
{
    const char* sendToClientBuff = "";
    if (strcmp(msg, "0") == 0) {
        sendToClientBuff = "0";
    }
    else if (strcmp(msg, "$happy") == 0) {
        ClearTask();
        AssignTasks(1);
        sendToClientBuff = "Get it,Happy";
    }
    else  if (strcmp(msg, "$angry") == 0) {
        ClearTask();
        AssignTasks(2);
        sendToClientBuff = "Get it,Angry";
    }
    else  if (strcmp(msg, "$alarmed") == 0) {
        ClearTask();
        AssignTasks(3);
        sendToClientBuff = "Get it,Alarmed";
    }
    else  if (strcmp(msg, "$sad") == 0) {
        ClearTask();
        AssignTasks(9);
        sendToClientBuff = "Get it,Sad";
    }
    else  if (strcmp(msg, "$disdain") == 0) {
        ClearTask();
        AssignTasks(10);
        sendToClientBuff = "Get it,Disdain";
    }
   
    else  if (strcmp(msg, "CALL_STATE_RINGING") == 0) {
        isCalling = true;
        ClearTask();
        CallingTask();
        sendToClientBuff = "Get it,ring";
    }
    else  if (strcmp(msg, "CALL_STATE_OFFHOOK") == 0) {
        isCalling = false;
        callNum = 0;
        ClearTask();
        AssignTasks(1);
        sendToClientBuff = "Get it,offhook";
    }
    else  if (strcmp(msg, "CALL_STATE_IDLE") == 0) {
        isCalling = false;
        callNum = 0;
        ClearTask();
        AssignTasks(9);
        sendToClientBuff = "Get it,idle";
    }
    else {
        sendToClientBuff = "???WTF";
    }
    send(s, sendToClientBuff, sizeof(sendToClientBuff), 0);
}

void ElectronController::Disconnect()
{
    ClearTask();
    AddTask(Sad_start(true));
    AddTask(Sad_cycle());
    AddTask(Sad_end());
    player->Relax();
    player->Disconnect();
}

ElectronPlayer::RobotTask ElectronController::Stay_ss()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{0, 5, 5, 5, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 5, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 5, 15, 0 });     
    return ElectronPlayer::RobotTask{ "media/Emoji/stay/stay.mp4", "" ,tasks, 2.0, false };

}
ElectronPlayer::RobotTask ElectronController::Stay_ss1()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 12, 5, 11, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 12, 5, 11, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 12, 5, 11, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    return ElectronPlayer::RobotTask{ "media/Emoji/stay/stay_1.mp4", "media/ding.mp3" ,tasks, 2.0, false };
}
ElectronPlayer::RobotTask ElectronController::Stay_ss2()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });

    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 5, 9, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 5, 9, 15, 0 });

    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });

    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 5, 9, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 5, 9, 15, 0 });

    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });

    return ElectronPlayer::RobotTask{ "media/Emoji/stay/stay_2.mp4", "media/bigu1.mp3" ,tasks, 2.0, false };
}

ElectronPlayer::RobotTask ElectronController::LookLeft_start()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 5, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 5, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 5, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 15, 170, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 25, 170, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 25, 170, 3, 15, 30 });
    return ElectronPlayer::RobotTask{ "media/Emoji/stay/look_left/look_left1.mp4", "" ,tasks, 2.0, true };
}

ElectronPlayer::RobotTask ElectronController::LookLeft_cycle()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 15, 170, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 15, 170, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 15, 170, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 25, 170, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 25, 170, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 25, 170, 3, 15, 30 });

    return ElectronPlayer::RobotTask{ "media/Emoji/stay/look_left/look_left2.mp4", "" ,tasks, 2.0, true };
}

ElectronPlayer::RobotTask ElectronController::Lookleft_end()
{
    vector<ElectronPlayer::RobotPose_t> tasks; 
    tasks.push_back(ElectronPlayer::RobotPose_t{ -10, 25, 5, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -10, 25, 5, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -10, 25, 5, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -10, 25, 5, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    return ElectronPlayer::RobotTask{ "media/Emoji/stay/look_left/look_left3.mp4", "" ,tasks, 2.0, false };
}

ElectronPlayer::RobotTask ElectronController::LookRight_start()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 5, 3, 170, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 5, 3, 170, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 5, 3, 170, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 5, 20, 160, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 5, 20, 160, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 5, 20, 160, -30 });
    return ElectronPlayer::RobotTask{ "media/Emoji/stay/look_right/look_right_1.mp4", "" ,tasks, 2.0, true };
}

ElectronPlayer::RobotTask ElectronController::LookRight_cycle()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 5, 3, 170, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 5, 3, 170, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 5, 3, 170, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 5, 20, 160, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 5, 20, 160, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 5, 20, 160, -30 });


    return ElectronPlayer::RobotTask{ "media/Emoji/stay/look_right/look_right_2.mp4", "" ,tasks, 2.0, true };
}

ElectronPlayer::RobotTask ElectronController::LookRight_end()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ -10, 5, 5, 3, 15, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -10, 5, 5, 3, 15, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -10, 5, 5, 3, 15, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -10, 5, 5, 3, 15, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    
    return ElectronPlayer::RobotTask{ "media/Emoji/stay/look_right/look_right_3.mp4", "" ,tasks, 2.0, false };
}

ElectronPlayer::RobotTask ElectronController::Happy_start(bool isOpen)
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 160, 5, 160, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 160, 5, 160, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 20, 160, 20, 160, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 20, 160, 20, 160, 0 });


    return ElectronPlayer::RobotTask{ "media/Emoji/happy/happy_1.mp4", isOpen?"media/open.mp3":"" ,tasks, 2.0, true};
}

ElectronPlayer::RobotTask ElectronController::Happy_cycle()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 160, 5, 160, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 160, 5, 160, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 20, 160, 20, 160, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 20, 160, 20, 160, 0 });

    return ElectronPlayer::RobotTask{ "media/Emoji/happy/happy_2.mp4", "" ,tasks, 2.0, true };
}

ElectronPlayer::RobotTask ElectronController::Happy_end()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 20, 160, 20, 160, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    return ElectronPlayer::RobotTask{ "media/Emoji/happy/happy_3.mp4", "" ,tasks, 2.0, false };
}

ElectronPlayer::RobotTask ElectronController::Sad_start(bool isClose)
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 15, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 15, 5, 5, 3, 15, 0 });
    return ElectronPlayer::RobotTask{ "media/Emoji/sad/sad_1.mp4", isClose ? "media/close.mp3" : "" ,tasks, 2.0, false };
}

ElectronPlayer::RobotTask ElectronController::Sad_cycle()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 15, 5, 5, 3, 15, -15 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 15, 5, 5, 3, 15, -15 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 15, 5, 5, 3, 15, 15 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 15, 5, 5, 3, 15, 15 });


    return ElectronPlayer::RobotTask{ "media/Emoji/sad/sad_2.mp4", "" ,tasks, 2.0, true };
}

ElectronPlayer::RobotTask ElectronController::Sad_end()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    return ElectronPlayer::RobotTask{ "media/Emoji/sad/sad_3.mp4", "" ,tasks, 2.0, false };
}

ElectronPlayer::RobotTask ElectronController::Disdain_start()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 90, 3, 15, 30 });
    return ElectronPlayer::RobotTask{ "media/Emoji/disdain/disdain_1.mp4", "" ,tasks, 2.0, false };
}

ElectronPlayer::RobotTask ElectronController::Disdain_cycle()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 90, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 90, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 20, 90, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 20, 90, 3, 15, 30 });

    return ElectronPlayer::RobotTask{ "media/Emoji/disdain/disdain_2.mp4", "" ,tasks, 2.0, true };
}

ElectronPlayer::RobotTask ElectronController::Disdain_end()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ -15, 5, 90, 3, 15, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
        
    return ElectronPlayer::RobotTask{ "media/Emoji/disdain/disdain_3.mp4", "" ,tasks, 2.0, false };
}

ElectronPlayer::RobotTask ElectronController::Angry_start()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 5, 10, 15, -20 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 5, 10, 15, -20 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 160, 10, 160, 20 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 160, 10, 160, 20 });
    return ElectronPlayer::RobotTask{ "media/Emoji/angry/angry_1.mp4", "" ,tasks, 2.0, true };
}

ElectronPlayer::RobotTask ElectronController::Angry_cycle()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 5, 10, 15, -20 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 5, 10, 15, -20 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 160, 10, 160, 20 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 160, 10, 160, 20 });


    return ElectronPlayer::RobotTask{ "media/Emoji/angry/angry_2.mp4", "" ,tasks, 2.0, true };
}

ElectronPlayer::RobotTask ElectronController::Angry_cycle_calling()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 5, 10, 15, -20 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 5, 10, 15, -20 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 160, 10, 160, 20 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 160, 10, 160, 20 });
    return ElectronPlayer::RobotTask{ "media/call.mp4", "media/bigu2.mp3" ,tasks, 2.0, true };
}

ElectronPlayer::RobotTask ElectronController::Angry_end()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 160, 10, 160, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 6, 90, 7, 90, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    return ElectronPlayer::RobotTask{ "media/Emoji/angry/angry_3.mp4", "" ,tasks, 2.0, false };
}

ElectronPlayer::RobotTask ElectronController::Alarmed_start()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 6, 90, 7, 90, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 160, 10, 160, 0 });
    return ElectronPlayer::RobotTask{ "media/Emoji/alarmed/alarmed_1.mp4", "" ,tasks, 2.0, false };
}

ElectronPlayer::RobotTask ElectronController::Alarmed_cycle()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 160, 10, 160, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 160, 10, 160, -30});
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 25, 160, 25, 160, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 25, 160, 25, 160, 30 });

    return ElectronPlayer::RobotTask{ "media/Emoji/alarmed/alarmed_2.mp4", "" ,tasks, 2.0, true };
}

ElectronPlayer::RobotTask ElectronController::Alarmed_cycle_calling()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 160, 10, 160, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 160, 10, 160, -30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 25, 160, 25, 160, 30 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 25, 160, 25, 160, 30 });

    return ElectronPlayer::RobotTask{ "media/call.mp4", "media/bigu2.mp3" ,tasks, 2.0, true };
}

ElectronPlayer::RobotTask ElectronController::Alarmed_end()
{
    vector<ElectronPlayer::RobotPose_t> tasks;
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 10, 160, 10, 160, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 6, 90, 7, 90, 0 });
    tasks.push_back(ElectronPlayer::RobotPose_t{ 0, 5, 5, 3, 15, 0 });
    return ElectronPlayer::RobotTask{ "media/Emoji/alarmed/alarmed_3.mp4", "" ,tasks, 2.0, false };
}


