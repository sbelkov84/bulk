//------------------------------------------------------------------------
#include "single_bulk.h"
//------------------------------------------------------------------------
#include <iostream>
#include <string>
//------------------------------------------------------------------------

#include <thread>
int main(int argc, char** argv)
{
  std::string BulkSize;
  if (argc > 1)
    BulkSize.append(argv[1]);

  /*! \brief Maximal size of fixed bulk */
  /*! std::size_t N */
  std::size_t N = 0;
  
  try 
  {
    N = stoi(BulkSize); 
  }
  catch (...)
  {
    std::cout << "Please set BulkSize cmd parameter greater than 0" << std::endl;
    return 1;
  }


  if (N == 0)
  {
    std::cout << "Please set BulkSize cmd parameter greater than 0" << std::endl;
    return 1;
  }

  TBulkManager BulkManager;
  TSingleBulk FixedBulk(&BulkManager, eBulkTypeFixed, N);
  TSingleBulk DynamicBulk(&BulkManager, eBulkTypeDynamic);

  std::string Cmd;
  while (std::getline(std::cin, Cmd))
  {
    BulkManager.ExecCmd(Cmd);
  }

  return 0;
}
