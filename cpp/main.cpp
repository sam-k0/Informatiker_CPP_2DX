#include "main.h"
#include "Informatikerspiel.h"
#include "gms.h"
#include <windows.h>
#include <stdio.h>

/*! Register Callback */
const int EVENT_OTHER_SOCIAL = 70;

// defines function pointers for the DS map creation
void (*CreateAsynEventWithDSMap)(int, int) = NULL;
int (*CreateDsMap)(int _num, ...) = NULL;
bool (*DsMapAddDouble)(int _index, const char* _pKey, double value) = NULL;
bool (*DsMapAddString)(int _index, const char* _pKey, const char* pVal) = NULL;

// Reg cb - Do not touch
gmx void RegisterCallbacks(char* arg1, char* arg2, char* arg3, char* arg4) {
    void (*CreateAsynEventWithDSMapPtr)(int, int) = (void (*)(int, int))(arg1);
    int(*CreateDsMapPtr)(int _num, ...) = (int(*)(int _num, ...)) (arg2);
    CreateAsynEventWithDSMap = CreateAsynEventWithDSMapPtr;
    CreateDsMap = CreateDsMapPtr;

    bool (*DsMapAddDoublePtr)(int _index, const char* _pKey, double value) = (bool(*)(int,  const char*, double))(arg3);
    bool (*DsMapAddStringPtr)(int _index, const char* _pKey, const char* pVal) = (bool(*)(int, const char*, const char*))(arg4);

    DsMapAddDouble = DsMapAddDoublePtr;
    DsMapAddString = DsMapAddStringPtr;
}


//! Dll global scope
Informatikerspiel* game = new Informatikerspiel();

//! exported dll functions
gmx gmbool initGame()
{
    game->init();
    return gmtrue;
}

gmx double restartGame()
{
    game->clean();
    game->init();
    return gmtrue;
}

gmx double giveCards()
{
    bool res = game->giveCards();
    if(res)
    {
        return gmtrue;
    }
    return gmfalse;
}

gmx double setPlayerPrediction(double pred)
{
    game->setPlayerPrediction((int)pred);
    return gmtrue;
}

gmx double compareCards()
{
    bool res = game->compareCards();

    if(res)
    {
        return gmtrue;
    }
    return gmfalse;
}

gmx double getCurrentCards()
{
    int newmap = CreateDsMap(0);
    DsMapAddString(newmap, "event_type", "GAME_CARDS");
    DsMapAddDouble(newmap, "playerValue", game->getPlayerCard()->value);
    DsMapAddDouble(newmap, "playerColor", game->getPlayerCard()->color);
    DsMapAddDouble(newmap, "enemyValue", game->getEnemyCard()->value);
    DsMapAddDouble(newmap, "enemyColor", game->getEnemyCard()->color);
    CreateAsynEventWithDSMap(newmap, EVENT_OTHER_SOCIAL);
    return gmtrue;
}


// DLL Callback
gmx BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            printf("Attached DLL to process");
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            printf("Attached DLL to process!");
            // Clean up
            game->clean(); // Clean objects
            delete game;  // Destroy the game object itself
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
