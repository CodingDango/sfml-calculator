#include "core.hpp"

//===============================================================
// namespace core Function Definitions
//===============================================================

void core::prepareButtons(
  entity::ButtonContainer& container, 
  calc::CalculatorOperationContainer& calc_data
)
{
  const sf::Vector2f STARTING_POINT = {19.60f, 200.0f};
  const int MARGIN_X_PX = 27;
  const int MARGIN_Y_PX = 20;
  const int BUTTONS_PER_ROW = 4;

  float X {STARTING_POINT.x};
  float Y {STARTING_POINT.y};
  int BUTTON_COUNTER {};

  for (int i = 0; i < assets::button_initializers.size(); i++)
  {   
      const auto& btn_initializer = assets::button_initializers[i];

      // Clear button
      if (i == 0)
      {
          BUTTON_COUNTER += 2;
          entity::Button clear_button { [&calc_data](){ calc_data.clear(); } };
          clear_button.setTexture(btn_initializer.texture);
          clear_button.setPosition(STARTING_POINT);
          container.push_back(clear_button);
          continue;
      } else 
          BUTTON_COUNTER++;

      // Updating X and Y values
      if ((BUTTON_COUNTER - 1)% BUTTONS_PER_ROW == 0)
      {   
          // Get height of last element and add the gap or magin
          Y += (container.back().getTexture()->getSize().y) + MARGIN_Y_PX;    
          X = STARTING_POINT.x;
      } 
      else 
      {
          X += (container.back().getTexture()->getSize().x) + MARGIN_X_PX;
      }

      // Add button functionality
      entity::Button button;
      addButtonFunction(button, btn_initializer, calc_data);
      button.setTexture(btn_initializer.texture);
      button.setPosition({X, Y});
      container.push_back(button);
  }
}

void core::addButtonFunction(
  entity::Button& btn, 
  const assets::ButtonInitializerData& initializer,
  calc::CalculatorOperationContainer& calc_data
)
{   
  const std::string btn_value = initializer.value;

  if (btn_value == "del") 
      btn.setClickCallback([&calc_data](){ calc_data.backspace(); });

  else if (btn_value == "=")
      btn.setClickCallback([&calc_data](){ calc_data.equal(); });

  else if (btn_value == "+")
      btn.setClickCallback([&calc_data](){ calc_data.add(); });
  
  else if (btn_value == "-")
      btn.setClickCallback([&calc_data](){ calc_data.subtract(); });

  else if (btn_value == "*")
      btn.setClickCallback([&calc_data](){ calc_data.multiply(); });

  else if (btn_value == "/")
      btn.setClickCallback([&calc_data](){ calc_data.divide(); });

  else 
  {   
      // This is guaranteed to be a digit character. can be period.
      char digit = btn_value[0];
      btn.setClickCallback([&calc_data, digit](){ calc_data.add_digit(digit); });
  }
}

void core::prepareCopyableTexts(entity::CopyableTextContainer& container, calc::CalculatorOperationContainer& calc_data)
{  
    entity::CopyableText input_text {calc_data.input, assets::my_font, 50};
    input_text.setStyle(sf::Text::Bold);
    input_text.setPosition(30, 125);
    container.type_string.push_back(input_text);

    entity::CopyableText result_text {calc_data.result_string, assets::my_font, 40};
    result_text.setStyle(sf::Text::Bold);
    result_text.setFillColor(sf::Color(148, 148, 148, 100));
    result_text.setPosition(30, 26);
    container.type_string.push_back(result_text);

    entity::CopyableText operation_text {calc_data.operation, assets::my_font, 45};
    operation_text.setStyle(sf::Text::Bold);
    operation_text.setFillColor(sf::Color(148, 148, 148, 100));
    operation_text.setPosition(535, 26);
    container.type_char.push_back(operation_text);
}