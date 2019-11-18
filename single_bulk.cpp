//------------------------------------------------------------------------
#include "single_bulk.h"
//------------------------------------------------------------------------
#include <iostream>
#include <fstream>
//------------------------------------------------------------------------

TSingleBulk::TSingleBulk(TBulkManager* Manager, EBulkType Type, std::size_t N)
{
  Manager->Subscribe(this, Type);
  this->N = N;
}
//------------------------------------------------------------------------

void TSingleBulk::Print(std::ostream& Stream)
{
  if (Commands.size() == 0)
    return;
  //---
  //std::cout << "bulk: ";
  Stream << "bulk: ";
  for (auto It = Commands.begin(); It != Commands.end(); ++It)
  {
    //std::cout << *It << " ";
    Stream << *It << " ";
  }
  //std::cout << std::endl;
  Stream << std::endl;
}
//------------------------------------------------------------------------

//void TFixedBulk::ExecCmd(std::string &Cmd)
//{
//  if (Cmd == "{" || Cmd.empty())
//  {
//    PrintAndClear();
//  }
//  else
//  {
//    if (Commands.size() == N)
//    {
//      PrintAndClear();
//    }
//    AddCmd(Cmd);
//  }
//}
//------------------------------------------------------------------------

void TSingleBulk::AddCmd(std::string& Cmd)
{
  if (Commands.empty())
    FirstCmdTime = std::time(nullptr);

  Commands.push_back(Cmd);
  if (N > 0 && Commands.size() == N)
    ReleaseBulk();
}
//------------------------------------------------------------------------

void TSingleBulk::ClearCmds()
{
  Commands.resize(0);
}
//------------------------------------------------------------------------

void TSingleBulk::ReleaseBulk(bool NeedToPrint)
{
  if (NeedToPrint)
  {
    Print(std::cout);
    SaveToFile();
  }
  //---
  ClearCmds();
}
//------------------------------------------------------------------------

#include <windows.h>
void TSingleBulk::SaveToFile()
{
  if (Commands.empty())
    return;
  //---
  char TimeStamp[40];
  std::strftime(TimeStamp, 40, "%H%M%S", std::localtime(&FirstCmdTime));
  std::string BulkTime = TimeStamp;
  std::string FileName = "./logs/bulk";
  FileName += TimeStamp;
  FileName += ".log";
  std::ofstream OutFile(FileName, std::ios::binary);

  try
  {
    Print(OutFile);
  }
  catch (...)
  {
    OutFile.close();
  }
  OutFile.close();

  std::cout << FileName << std::endl;
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------
/*
TDynamicBulk::TDynamicBulk(TBulkManager* Manager)
{
  Manager->Subscribe(this);
}*/
//------------------------------------------------------------------------

//void TDynamicBulk::PrintAndClear()
//{
//  TFixedBulk::PrintAndClear();
//  SetBrackCountersToZero();
//}
//------------------------------------------------------------------------

//void TDynamicBulk::ExecCmd(std::string &Cmd)
//{
//  if (Cmd == "{")
//  {
//    ++OpeningCount;
//  }
//  else if (Cmd == "}")
//  {
//    ++ClosingCount;
//    if (IsClosed())
//    {
//      PrintAndClear();
//    }
//  }
//  else if (Cmd.empty())
//  {
//    SetBrackCountersToZero();
//    ClearCmds();
//  }
//  else
//  {
//    AddCmd(Cmd);
//  }
//}
//------------------------------------------------------------------------

