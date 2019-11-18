#ifndef SINGLE_BULK_H
#define SINGLE_BULK_H
//------------------------------------------------------------------------
#include <vector>
#include <ctime>
//------------------------------------------------------------------------
#include "bulk_manager.h"
//------------------------------------------------------------------------

class TSingleBulk : public TBulkObserver
{
private:

  /*! Stores not-manage commands */
  /*! std::vector<std::string> Commands */
  std::vector<std::string> Commands;

  /*! \brief Maximal size of fixed bulk */
  /*! std::size_t N */
  std::size_t N;

  /*! \brief True if commands are adressed to this bulk */
  /*! bool IsActive */
  bool IsActive;

  /*! \brief Stores first command time in this bulk */
  /*! std::chrono::time_point<std::chrono::system_clock> */
  std::time_t FirstCmdTime;

  /*! \brief Prints this bulk in specified stream (stdout or file) */
  /*! void Print(std::ostream& Stream) */
  void Print(std::ostream& Stream);

  /*! \brief Saves bulk commands info into file */
  /*! void SaveToFile() */
  void SaveToFile();

public:

  /*! \brief Default constructor is used in child class */
  /*! TSingleBulk() */
  TSingleBulk() {N = 0;}

  /*! \brief Constructor sets default fields */
  /*! TFixedBulk(TBulkManager* Manager, EBulkType Type, std::size_t N) */
  TSingleBulk(TBulkManager* Manager, EBulkType Type, std::size_t N = 0);


  /*! \brief Execute command. With special logic inside */
  /*! virtual  void ExecCmd(std::string& Cmd) */
  virtual void AddCmd(std::string& Cmd) override;

  /*! \brief Adds cmd to commands-vector */
  /*! void AddCmd(std::string& Cmd) */
  //void AddCmd(std::string& Cmd);

  /*! \brief Clears commands-vector */
  /*! void ClearCmds() */
  void ClearCmds();

  /*! \brief Sets IsActive variable */
  /*! void SetActive(bool Value) */
  void SetActive(bool Value);

  virtual void ReleaseBulk(bool NeedToPrint = true);
};
//------------------------------------------------------------------------

//struct TDynamicBulk : public TFixedBulk
//{
//private:

//  /*! \brief If true means that this bulk is inner inside {...} */
//  /*! bool IsInner */
//  //bool IsInner;

//public:

//  /*! Constructor sets default fields. N sets to zero, because is unused */
//  /*! TDynamicBulk(TBulkManager* Manager, std::size_t N = 0) */
//  TDynamicBulk(TBulkManager* Manager);

//  /*! \brief Prints this bulk */
//  /*! virtual void Print() */
//  //virtual void Print();

//  /*! Execute command. With special logic inside */
//  /*! void ExecCmd(std::string& Cmd) */
//  //virtual void ExecCmd(std::string& Cmd) final;

//  virtual void ReleaseBulk(bool NeedToPrint = true);
//};

//------------------------------------------------------------------------
#endif // SINGLE_BULK_H
