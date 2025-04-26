#include "assets.hpp"
#include "utils.hpp"

//===============================================================
// namespace assets Definitions
//===============================================================

const std::vector<assets::ButtonInitializerData> assets::button_initializers = {

  // First row
  ButtonInitializerData("clear", utils::loadTexture("../assets/op-btns/oper-clear.png")),
  ButtonInitializerData("del", utils::loadTexture("../assets/op-btns/oper-del.png")),
  ButtonInitializerData("/", utils::loadTexture("../assets/op-btns/oper-divide.png")),
      
  // Second row
  ButtonInitializerData("7", utils::loadTexture("../assets/num-btns/num-7.png")),
  ButtonInitializerData("8", utils::loadTexture("../assets/num-btns/num-8.png")),
  ButtonInitializerData("9", utils::loadTexture("../assets/num-btns/num-9.png")), 
  ButtonInitializerData("*", utils::loadTexture("../assets/op-btns/oper-multiply.png")),

  // Third row
  ButtonInitializerData("4", utils::loadTexture("../assets/num-btns/num-4.png")),
  ButtonInitializerData("5", utils::loadTexture("../assets/num-btns/num-5.png")),
  ButtonInitializerData("6", utils::loadTexture("../assets/num-btns/num-6.png")),
  ButtonInitializerData("-", utils::loadTexture("../assets/op-btns/oper-subtract.png")),

  // Fourth row
  ButtonInitializerData("1", utils::loadTexture("../assets/num-btns/num-1.png")),
  ButtonInitializerData("2", utils::loadTexture("../assets/num-btns/num-2.png")),
  ButtonInitializerData("3", utils::loadTexture("../assets/num-btns/num-3.png")),
  ButtonInitializerData("+", utils::loadTexture("../assets/op-btns/oper-add.png")),

  // Fifth row
  ButtonInitializerData("empty", utils::loadTexture("../assets/num-btns/num-empty.png")),
  ButtonInitializerData("0", utils::loadTexture("../assets/num-btns/num-0.png")),
  ButtonInitializerData(".", utils::loadTexture("../assets/num-btns/char-dot.png")),
  ButtonInitializerData("=", utils::loadTexture("../assets/op-btns/oper-equals.png")),
}; 

const sf::Font assets::my_font { 
  utils::loadFont("../assets/fonts/YuGothM.ttc")
};
