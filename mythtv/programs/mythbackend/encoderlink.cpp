#include <unistd.h>
#include <iostream>

using namespace std;

#include "encoderlink.h"
#include "tv.h"

EncoderLink::EncoderLink(QSocket *lsock, QString lhostname)
{
    sock = lsock;
    hostname = lhostname;
    tv = NULL;
    local = false;
}

EncoderLink::EncoderLink(TVRec *ltv)
{
    sock = NULL;
    tv = ltv;
    local = true;
}

EncoderLink::~EncoderLink()
{
    if (local)
        delete tv;
}

bool EncoderLink::isBusy(void)
{
    bool retval = true;

    if (local)
    {
        if (tv->IsRecording() || tv->GetState() == kState_WatchingLiveTV)
            retval = true;
    }
    else
    {
    }

    return retval;
}

TVState EncoderLink::GetState(void)
{
    TVState retval = kState_Error;

    if (local)
        retval = tv->GetState();
    else
    {
    }

    return retval;
}

int EncoderLink::AllowRecording(ProgramInfo *rec, int timeuntil)
{
    int retval = 0;

    if (local)
        retval = tv->AllowRecording(rec, timeuntil);
    else
    {
    }

    return retval;
}

void EncoderLink::StartRecording(ProgramInfo *rec)
{
    if (local)
        tv->StartRecording(rec);
}

bool EncoderLink::IsReallyRecording(void)
{
    if (local)
        return tv->IsReallyRecording();

    return false;
}

float EncoderLink::GetFramerate(void)
{
    if (local)
        return tv->GetFramerate();
    return -1;
}

long long EncoderLink::GetFramesWritten(void)
{
    if (local)
        return tv->GetFramesWritten();
    return -1;
}

long long EncoderLink::GetFilePosition(void)
{
    if (local)
        return tv->GetFilePosition();
    return -1;
}

long long EncoderLink::GetFreeSpace(long long totalreadpos)
{
    if (local)
        return tv->GetFreeSpace(totalreadpos);
    return -1;
}

long long EncoderLink::GetKeyframePosition(long long desired)
{
    if (local)
        return tv->GetKeyframePosition(desired);
    return -1;
}

void EncoderLink::SetupRingBuffer(QString &path, long long &filesize,
                                  long long &fillamount, bool pip)
{
    if (local)
        tv->SetupRingBuffer(path, filesize, fillamount, pip);
}

void EncoderLink::SpawnLiveTV(void)
{
    if (local)
        tv->SpawnLiveTV();
}

void EncoderLink::StopLiveTV(void)
{
    if (local)
        tv->StopLiveTV();
}

void EncoderLink::PauseRecorder(void)
{
    if (local)
        tv->PauseRecorder();
}

void EncoderLink::ToggleInputs(void)
{
    if (local)
        tv->ToggleInputs();
}

void EncoderLink::ChangeChannel(bool direction)
{
    if (local)
        tv->ChangeChannel(direction);
}

void EncoderLink::SetChannel(QString name)
{
    if (local)
        tv->SetChannel(name);
}

bool EncoderLink::CheckChannel(QString name)
{
    if (local)
        return tv->CheckChannel(name);
    return false;
}

void EncoderLink::GetChannelInfo(QString &title, QString &subtitle, 
                                 QString &desc, QString &category, 
                                 QString &starttime, QString &endtime, 
                                 QString &callsign, QString &iconpath,
                                 QString &channelname)
{
    if (local)
        tv->GetChannelInfo(title, subtitle, desc, category, starttime,
                           endtime, callsign, iconpath, channelname);
}

void EncoderLink::GetInputName(QString &inputname)
{
    if (local)
        tv->GetInputName(inputname);
}

void EncoderLink::SpawnReadThread(QSocket *sock)
{
    if (local)
        tv->SpawnReadThread(sock);
}

void EncoderLink::KillReadThread(void)
{
    if (local)
        tv->KillReadThread();
}

void EncoderLink::PauseRingBuffer(void)
{
    if (local)
        tv->PauseRingBuffer();
}

void EncoderLink::UnpauseRingBuffer(void)
{
    if (local)
        tv->UnpauseRingBuffer();
}

void EncoderLink::PauseClearRingBuffer(void)
{
    if (local)
        tv->PauseClearRingBuffer();
}

long long EncoderLink::SeekRingBuffer(long long curpos, long long pos, 
                                      int whence)
{
    if (local)
        return tv->SeekRingBuffer(curpos, pos, whence);
    return -1;
}
