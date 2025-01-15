#pragma once

#include "Hook.h"
#include "game_struct.h" 
#include "offsets.h"
#include "global.h"
#include "Vector3.h"
#include "opengl.h"
#include <random>



extern bool EAimbot;
extern Hook_t* HookAimBot;

HOOK_FUNCTION_VC __update_pointers_game__(Hook_t* hook, PRegisters registers)
{
    bool b = hmutex.try_lock();

    Player = (PEntity) * (DWORD*)(BASE + Offsets.Player);
    BotList = (PBot)(BASE + Offsets.Botlist); 

    if (b)
        hmutex.unlock();

}

HOOK_FUNCTION_VC H_Fire(Hook_t* hook, PRegisters registers)
{
    if (registers->edi == (DWORD32)Player)
    {
        DWORD* ammo = (DWORD*)*(DWORD*)(registers->esi + 0x14);
        *ammo = 10000;
    }

}

HOOK_FUNCTION_VC H_FireRate(Hook_t* hook, PRegisters registers)
{
    if (registers->edi == (DWORD32)Player)
        registers->ecx = 0;
}

HOOK_FUNCTION_VC H_Damage(Hook_t* hook, PRegisters registers)
{
    if ((registers->edi) == (DWORD32)Player)
        registers->esi = 1000;
    else
        registers->esi = 0;
}

HOOK_FUNCTION_VC H_ForAimbot(Hook_t* hook, PRegisters registers)
{
    if (!BotList || !Player)
        return;

    if (!BotList->BotList)
        return;

    if (BotList->NumberOfBot != 0)
    {
        float mg = 9999999;
        PEntity target = nullptr;

        for (BYTE b = 0; b < BotList->NumberOfBot; b++)
        {
  
                vec2 Top_Left = OpenGlESP.WorldToScreen({ BotList->BotList[b]->X,BotList->BotList[b]->Y,BotList->BotList[b]->Z });
                if (Top_Left.x==0 && Top_Left.y==0)
                    continue;

                float bmg = Vector3::magnitude({ Player->X,Player->Y,Player->Z }, { BotList->BotList[b]->X,BotList->BotList[b]->Y,BotList->BotList[b]->Z});
                if (bmg < mg && (BotList->BotList[b]->Health > 0 && BotList->BotList[b]->Health <= 100))
                {
                    mg = bmg;
                    target = BotList->BotList[b];
                 }
         
            
        }

        if (target)
        {
            float ox =  float(Player->XO - target->XO);
            float oy =  float(target->YO - Player->YO);
            float oz =  float(Player->ZO - target->ZO);

            float RX = Rad2Deg(atan2f(oz,ox));
            float RY = Rad2Deg(asinf((oy)/mg)); 

            if (RX < 0)
                RX = -RX;
            else if (RX > 0)
                RX = (360 - RX);

          Player->RotX = RX;
          Player->RotY = RY;
            
        }
        
    }
}


GLubyte * generateRainbowColor() {
    GLubyte r = rand() % 256;
    GLubyte g = rand() % 256;
    GLubyte b = rand() % 256;

    return new GLubyte[3]{(GLubyte)(r / 255), (GLubyte)(g / 255), (GLubyte)(b / 255)};
}


HOOK_FUNCTION_VC H_wglSwapBuffers(Hook_t* hook, PRegisters registers)
{
    if (!BotList || !Player)
        return;
    else if (BotList->NumberOfBot != 0)
    {

        OpenGlESP.Setup();
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        for (BYTE b = 0; b < BotList->NumberOfBot; b++)
        {

            float distance = Vector3::magnitude({ Player->X,Player->Y,Player->Z }, { BotList->BotList[b]->X,(BotList->BotList[b]->Y),BotList->BotList[b]->Z });
           if(BotList->BotList[b]->Health < 0 || BotList->BotList[b]->Health > 100 || (distance < 2.5))
                continue;

            #define SQUARE_SIZE 1.0f
            #define LINE_WIDTH 1.5f

           
          
           vec3 BotVec{ BotList->BotList[b]->X ,BotList->BotList[b]->Y,BotList->BotList[b]->Z };
           float scale = (BotVec.z / (BotVec.z+ SQUARE_SIZE)) / 5.0f;
           float ox = float(Player->X - BotVec.x );
           float oy = float(Player->Y - BotVec.y);
           float oz = float(Player->Z - BotVec.z);

           vec2 TopLeft = OpenGlESP.WorldToScreen({ BotVec.x,BotVec.y,(BotVec.z- SQUARE_SIZE) });
           vec2 BottomRight = OpenGlESP.WorldToScreen({ BotVec.x,(BotVec.y-4.5f),(BotVec.z + SQUARE_SIZE) });
            if ((!TopLeft.x && !TopLeft.y) || (!BottomRight.x && !BottomRight.y) || (TopLeft.x > viewport[2] || TopLeft.y > viewport[3] || (TopLeft.x < 0 && BottomRight.x < 0) || (TopLeft.y < 0 && BottomRight.y < 0)))
               continue;
           
           vec2 Center = OpenGlESP.WorldToScreen({ BotVec.x,BotVec.y-4.5f,BotVec.z });

           GLubyte  color[3]{ 255, 255, 255 };

          // 2D Square ESP

          // float height = BottomRight.y - TopLeft.y;
          //  float width = height / 2.15f;

          

          //  OpenGlESP.DrawSquare(false, { Center.x - (width/2),Center.y}, width, -height, LINE_WIDTH, color);

         //   OpenGlESP.DrawLine({ (float)(viewport[2] / 2),(float)(viewport[3]) }, Center, LINE_WIDTH, color);

            vec2 Top_Left = OpenGlESP.WorldToScreen({(BotVec.x + SQUARE_SIZE),(BotVec.y),(BotVec.z - SQUARE_SIZE)});
            vec2 Top_Right      =  OpenGlESP.WorldToScreen({ (BotVec.x+ SQUARE_SIZE),(BotVec.y),(BotVec.z+ SQUARE_SIZE) });
           
            vec2 Bottom_Left    =  OpenGlESP.WorldToScreen({ (BotVec.x+ SQUARE_SIZE),(BotVec.y-4.5f),(BotVec.z - SQUARE_SIZE) });
            vec2 Bottom_Right   =  OpenGlESP.WorldToScreen({ (BotVec.x+ SQUARE_SIZE),(BotVec.y-4.5f),(BotVec.z + SQUARE_SIZE) });
            
            vec2 Top_Left2 = OpenGlESP.WorldToScreen({ (BotVec.x - SQUARE_SIZE),(BotVec.y),(BotVec.z - SQUARE_SIZE) });
            vec2 Top_Right2 = OpenGlESP.WorldToScreen({ (BotVec.x - SQUARE_SIZE),(BotVec.y),(BotVec.z + SQUARE_SIZE) });

            vec2 Bottom_Left2 = OpenGlESP.WorldToScreen({ (BotVec.x - SQUARE_SIZE),(BotVec.y - 4.5f),(BotVec.z - SQUARE_SIZE) });
            vec2 Bottom_Right2 = OpenGlESP.WorldToScreen({ (BotVec.x - SQUARE_SIZE),(BotVec.y - 4.5f),(BotVec.z + SQUARE_SIZE) });

            if ((!Top_Left.x && !Top_Left.y) || (!Bottom_Right.x && !Bottom_Right.y) || (Top_Left.x > viewport[2] || Top_Left.y > viewport[3] || (Top_Left.x < 0 && Bottom_Right.x < 0) || (Top_Left.y < 0 && Bottom_Right.y < 0)))
                continue;
            
            float height = (Top_Left.y - Bottom_Left.y);
            float height2 = (Top_Right.y - Bottom_Right.y); 

            float height3 = (Top_Left2.y - Bottom_Left2.y);
            float height4 = (Top_Right2.y - Bottom_Right2.y);
         
            OpenGlESP.DrawLine(Top_Left, Top_Right, LINE_WIDTH, color);
            OpenGlESP.DrawLine(Bottom_Left, Bottom_Right, LINE_WIDTH, color);

            OpenGlESP.DrawLine(Top_Left, { Bottom_Left.x, (Top_Left.y-height) }, LINE_WIDTH, color);
           
            OpenGlESP.DrawLine(Top_Right, { Bottom_Right.x, (Top_Right.y - height2) }, LINE_WIDTH, color);

            OpenGlESP.DrawLine(Top_Left2, Top_Right2, LINE_WIDTH, color);
            OpenGlESP.DrawLine(Bottom_Left2, Bottom_Right2, LINE_WIDTH, color);

            OpenGlESP.DrawLine(Top_Left2, { Bottom_Left2.x, (Top_Left2.y - height3) }, LINE_WIDTH, color);

            OpenGlESP.DrawLine(Top_Right2, { Bottom_Right2.x, (Top_Right2.y - height4) }, LINE_WIDTH, color);
           
            OpenGlESP.DrawLine(Top_Right2, Top_Right, LINE_WIDTH, color);
            OpenGlESP.DrawLine(Bottom_Right2, Bottom_Right, LINE_WIDTH, color);
            OpenGlESP.DrawLine(Bottom_Left2, Bottom_Left, LINE_WIDTH, color);
            OpenGlESP.DrawLine(Top_Left2, Top_Left, LINE_WIDTH, color);

            OpenGlESP.DrawLine(Top_Left2, Top_Left, LINE_WIDTH, color);

            OpenGlESP.DrawLine({ (float)(viewport[2] / 2),(float)(viewport[3]) }, Bottom_Right, LINE_WIDTH, color);
              
        }

        OpenGlESP.RestoreGL();
    }
}


void StartEngine()
{
    
    OpenGlESP.SetViewMatrix(0x0057E010);
    OpenGlESP.SetProjectionMatrix(0x0057E0B0);

    Hook((DWORD32)(BASE + Offsets.Event_ChangeParty), (DWORD32) __update_pointers_game__, 5, "Update Pointer Game");
    Hook((DWORD32)(BASE + Offsets.Event_Fire), (DWORD32)H_Fire, 6, "FireEvent");
    Hook((DWORD32)(BASE + Offsets.Event_FireRate), (DWORD32)H_FireRate, 5, "FireRateEvent");
    Hook((DWORD32)(BASE + Offsets.Event_Damage), (DWORD32)H_Damage, 5, "DamageEevent");
    
   
    if (EAimbot) {
      HookAimBot = Hook((DWORD32)(NTapi::GetFuncAddress(NTapi::GetModuleAddress("OPENGL32.dll"), "glClearColor") + 5), (DWORD32)H_ForAimbot, 5, "HookForAimbot",true);
    }
    else {
      HookAimBot = Hook((DWORD32)(NTapi::GetFuncAddress(NTapi::GetModuleAddress("OPENGL32.dll"), "glClearColor") + 5), (DWORD32)H_ForAimbot, 5, "HookForAimbot", false);
    }
    

    Hook((DWORD32)(NTapi::GetFuncAddress(NTapi::GetModuleAddress("OPENGL32.dll"), "wglSwapBuffers") + 11), (DWORD32)H_wglSwapBuffers, 6, "HookForwglSwapBuffers");
    
}

void StopEngine()
{
    HookStore.DetachAllHooks();
}