#include "core.hpp"

//===============================================================
// namespace core Function Definitions
//===============================================================

void core::prepareButtons(
  ui::ButtonContainer& container, 
  calc::CalculatorOperationContainer& calc_data
)
{
    int blocks_occupied = 0;
    int current_col = 0;
    int current_row = 0;

    for (int i = 0; i < assets::button_initializers.size(); i++)
    {   
        const auto& btn_initializer = assets::button_initializers[i];

        int x_pos = core::config::GRID_STARTING_POINT.x + current_col * (core::config::BLOCK_SIZE.x + core::config::MARGIN_X_PX);
        int y_pos = core::config::GRID_STARTING_POINT.y + current_row * (core::config::BLOCK_SIZE.y + core::config::MARGIN_Y_PX);

        const sf::Vector2u btn_texture_size = btn_initializer.texture.getSize();
        int cols_taken_up = std::round(btn_texture_size.x / core::config::BLOCK_SIZE.x);

        blocks_occupied += cols_taken_up;
        current_col = (current_col + cols_taken_up) % core::config::BLOCKS_PER_ROW;
        current_row = blocks_occupied / core::config::BLOCKS_PER_ROW;

        ui::Button button;
        button.setPosition(x_pos, y_pos);

        button.setTexture(btn_initializer.texture);
        core::addButtonFunction(button, btn_initializer, calc_data);
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