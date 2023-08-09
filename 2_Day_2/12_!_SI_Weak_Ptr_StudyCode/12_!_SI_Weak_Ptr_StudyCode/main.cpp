//
//  main.cpp
//  12_!_SI_Weak_Ptr_StudyCode
//
//  Created by Sathya Babu on 01/08/23.
//

#include <iostream>
#include <memory>

struct USB;
struct SSD;

struct MotherBoard{

  ~MotherBoard(){
    std::cout << "MotherBoard gone" << std::endl;
  }
  void setUSB(const std::shared_ptr<USB> usb ){
    myUSB=usb;
  }
  void setSSD(const std::shared_ptr<SSD> ssd ){
    mySSD=ssd;
  }
 
    /***********************************here   **********************/
    std::weak_ptr<const SSD> mySSD;
   // std::shared_ptr<const USB> myUSB; // put this line in remark SSD  USB  MotherBoard gone
    std::weak_ptr<const USB> myUSB; //  open this line
    // Above line in remark SSD gone
   

    
    /*
     std::shared_ptr<const USB> myUSB; // put this line in remark SSD  USB  MotherBoard gone
     next line keep it on std::weak_ptr
     SSD gone
     USB gone
     MotherBoard gone

     */
};

struct USB{

  USB(std::shared_ptr<MotherBoard> m):myMotherBoard(m){}
  ~USB(){
    std::cout << "USB gone" << std::endl;
  }

  std::shared_ptr<const MotherBoard> myMotherBoard;
};

struct SSD{
  SSD(std::shared_ptr<MotherBoard> m):myMotherBoard(m){}
  ~SSD(){
    std::cout << "SSD gone" << std::endl;
  }
  std::shared_ptr<const MotherBoard> myMotherBoard;
};

int main(){
  std::cout << std::endl;
  {
    std::shared_ptr<MotherBoard> motherBoard= std::shared_ptr<MotherBoard>( new MotherBoard);
    std::shared_ptr<USB> usb= std::shared_ptr<USB>( new USB(motherBoard) ); // reg USb to MB
    std::shared_ptr<SSD> ssd= std::shared_ptr<SSD>( new SSD(motherBoard) ); // reg SSD to MB
    motherBoard->setUSB(usb);
    motherBoard->setSSD(ssd);
  }
  std::cout << std::endl;
}

/*
 SSD gone
 USB gone
 MotherBoard gone
 */
