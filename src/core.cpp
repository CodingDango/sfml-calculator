#include "core.hpp"

//===============================================================
// namespace core Function Definitions
//===============================================================

void core::prepareButtons(
  ui::ButtonContainer& container, 
  calc::CalculatorOperationContainer& calc_data
)
{
  float current_x_pos_px { core::config::STARTING_POINT.x };
  float current_y_pos_px { core::config::STARTING_POINT.y };
  size_t button_counter { 0 };

  for (int i = 0; i < assets::button_initializers.size(); i++)
  {   
      const auto& btn_initializer = assets::button_initializers[i];

      // Clear button
      if (i == 0)
      {
          button_counter += 2;
          ui::Button clear_button { [&calc_data](){ calc_data.reset(); } };
          clear_button.setTexture(btn_initializer.texture);
          clear_button.setPosition(core::config::STARTING_POINT);
          container.addButton(clear_button);
          continue;
      } 
      else 
          BUTTON_COUNTER++;

      // Updating X and Y values
      if ((button_counter - 1)% core::ui::BUTTONS_PER_ROW == 0)
      {   
          // Get height of last element and add the gap or magin
          Y += (container.back().getTexture()->getSize().y) + core::config::MARGIN_Y_PX;    
          X = core::config::STARTING_POINT.x;
      } 
      else 
          X += (container.back().getTexture()->getSize().x) + core::config::MARGIN_X_PX;
      
      // Add button functionality
      ui::Button button;
      addButtonFunction(button, btn_initializer, calc_data);
      button.setTexture(btn_initializer.texture);
      button.setPosition({X, Y});
      container.addButton(button);
  }
}

void core::addButtonFunction(
  ui::Button& btn, 
  const assets::ButtonInitializerData& initializer,
  calc::CalculatorOperationContainer& calc_data
)
{   
  const std::string& btn_value = initializer.value;

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

void core::prepareCopyableTexts(ui::CopyableTextContainer& container, calc::CalculatorOperationContainer& calc_data)
{  
    ui::CopyableText input_text {
        calc_data.input, 
        assets::my_font,
        core::config::INPUT_TEXT_FONT_SIZE,
        core::config::TEXT_CHAR_LIMIT,
        true
    };

    input_text.setStyle(core::config::TEXT_STYLE);
    input_text.setPosition(core::config::INPUT_TEXT_POSITION);
    input_text.setHoverColor(core::config::TEXT_HOVER_FILL_COLOR);
    container.m_string_texts.push_back(input_text);

    ui::CopyableText result_text {
        calc_data.result_string, 
        assets::my_font, 
        core::config::RESULT_TEXT_FONT_SIZE,
        core::config::TEXT_CHAR_LIMIT,
        true
    };

    result_text.setStyle(core::config::TEXT_STYLE);
    result_text.setNormalFillColor(core::config::RESULT_TEXT_FILL_COLOR);
    result_text.setHoverColor(core::config::TEXT_HOVER_FILL_COLOR);
    result_text.setPosition(core::config::RESULT_TEXT_POSITION);
    container.m_string_texts.push_back(result_text);

    ui::CopyableText operation_text {
        calc_data.operation, 
        assets::my_font, 
        core::config::OPERATION_TEXT_FONT_SIZE,
        core::config::TEXT_CHAR_LIMIT,
        false
    };

    operation_text.setStyle(core::config::TEXT_STYLE);
    operation_text.setNormalFillColor(core::config::OPERATION_TEXT_FILL_COLOR);
    operation_text.setHoverColor(core::config::TEXT_HOVER_FILL_COLOR);
    operation_text.setPosition(core::config::OPERATION_TEXT_POSITION);
    container.m_char_texts.push_back(operation_text);
} 